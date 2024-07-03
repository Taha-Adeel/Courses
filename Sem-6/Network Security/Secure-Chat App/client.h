#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <signal.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

class Client
{
private:
    int client_socket;          // socket descriptor
    std::string cert_file;      // certificate file
    std::string key_file;       // private key file
    std::string root_cert_file; // root CA certificate
    SSL_CTX *ctx;               // SSL context
    SSL *ssl;

    bool is_connected = false;   // is connected to server
    std::string server_hostname; // hostname of the server

    int create_socket(std::string hostname, int port = 4421)
    {
        struct sockaddr_in addr;
        struct hostent *server;

        server = gethostbyname(hostname.c_str());
        if (server == NULL)
        {
            std::cerr << "ERROR, no such host" << std::endl;
            exit(0);
        }

        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        addr.sin_addr.s_addr = inet_addr(inet_ntoa(*(struct in_addr *)*server->h_addr_list));

        int s = socket(AF_INET, SOCK_STREAM, 0);
        if (s < 0)
        {
            perror("Unable to create socket");
            exit(EXIT_FAILURE);
        }

        if (connect(s, (struct sockaddr *)&addr, sizeof(addr)) < 0)
        {
            perror("Unable to connect");
            exit(EXIT_FAILURE);
        }
        else
        {
            std::cout << "Connected to server" << std::endl;
            is_connected = true;
        }

        return s;
    }

    SSL_CTX *create_context()
    {
        SSL_library_init();
        SSL_load_error_strings();
        OpenSSL_add_all_algorithms();

        const SSL_METHOD *method;
        SSL_CTX *ctx;

        method = TLS_client_method();

        ctx = SSL_CTX_new(method);

        // std::cout << "Client Socket Ciphers before changing: " << SSL_CTX_get_ciphers(ctx) << std::endl;
        // std::cout << "Changing ciphers: " << SSL_CTX_set_cipher_list(ctx, "AES256-SHA256") << std::endl;
        // std::cout << "Client Socket Ciphers after changing: " << SSL_CTX_get_ciphers(ctx) << std::endl;

        if (!ctx)
        {
            perror("Unable to create SSL context for client");
            ERR_print_errors_fp(stderr);
            exit(EXIT_FAILURE);
        }
        std::cout << "Context Created" << std::endl;

        return ctx;
    }

    void configure_context()
    {
        /* Set the key and cert */
        if (SSL_CTX_use_certificate_file(ctx, cert_file.c_str(), SSL_FILETYPE_PEM) <= 0)
        {
            ERR_print_errors_fp(stderr);
            exit(EXIT_FAILURE);
        }

        if (SSL_CTX_use_PrivateKey_file(ctx, key_file.c_str(), SSL_FILETYPE_PEM) <= 0)
        {
            ERR_print_errors_fp(stderr);
            exit(EXIT_FAILURE);
        }

        if (SSL_CTX_load_verify_locations(ctx, root_cert_file.c_str(), NULL) <= 0)
        {
            ERR_print_errors_fp(stderr);
            exit(EXIT_FAILURE);
        }

        if (SSL_CTX_check_private_key(ctx) <= 0)
        {
            ERR_print_errors_fp(stderr);
            exit(EXIT_FAILURE);
        }

        SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER, NULL);
    }

    SSL *create_ssl()
    {
        SSL *ssl = SSL_new(ctx);
        if (!ssl)
        {
            perror("Unable to create SSL object for client");
            ERR_print_errors_fp(stderr);
            exit(EXIT_FAILURE);
        }

        SSL_set_fd(ssl, client_socket);
        // std::cout << "Client Socket Ciphers: " << SSL_get_ciphers(ssl) << std::endl;

        // SSL_set_ciphersuites(ssl, "DES-CBC3-SHA");
        // std::cout << SSL_get_cipher(ssl) << std::endl;

        // adaptor->SetCipherList(ctx, std::string("ALL"));
        // sslSocket = static_cast<SSLSocket *>(adaptor->Connect(ctx, "localhost", 8888));

        if (SSL_connect(ssl) != 1)
        {
            perror("Unable to connect to server :((( ");
            ERR_print_errors_fp(stderr);
            exit(EXIT_FAILURE);
            throw std::runtime_error("Unable to connect to server :((( ");
        }

        return ssl;
    }

    void SSL_read_from_server()
    {
        char buf[1024];
        int bytes;

        while (true)
        {
            if (!is_connected)
                exit(0);
            bytes = SSL_read(ssl, buf, sizeof(buf));
            // bytes = read(client_socket, buf, sizeof(buf));
            if (bytes > 0)
            {
                buf[bytes] = 0;
                std::cout << "Server: " << buf << std::endl;
                if (strcmp(buf, "chat_close") == 0)
                {
                    is_connected = false;
                    exit(0);
                }
            }
            else
            {
                ERR_print_errors_fp(stderr);
                exit(0);
            }
        }
    }

    /*void read_from_server()
    {
        char buf[1024];
        int bytes;

        while (true)
        {
            if (!is_connected)
                exit(0);
            // bytes = SSL_read(ssl, buf, sizeof(buf));
            bytes = read(client_socket, buf, sizeof(buf));
            if (bytes > 0)
            {
                buf[bytes] = 0;
                std::cout << "Server: " << buf << std::endl;

                if (strcmp(buf, "chat_START_SSL_ACK") == 0)
                {
                    is_connected = false;
                    break;
                }
                if (strcmp(buf, "chat_close") == 0)
                {
                    is_connected = false;
                    exit(0);
                }
            }
            else
            {
                ERR_print_errors_fp(stderr);
                exit(0);
            }
        }
    }*/

    void SSL_write_to_server()
    {
        char buf[1024];
        int bytes;

        while (true)
        {
            if (!is_connected)
                break;
            std::cout << "Client: " << std::endl;
            std::cin.getline(buf, sizeof(buf));

            // bytes = write(ssl, buf, strlen(buf));
            bytes = SSL_write(ssl, buf, strlen(buf));
            if (!is_connected)
                break;
            bytes = write(client_socket, buf, strlen(buf));
            if (strcmp(buf, "chat_close") == 0)
            {
                is_connected = false;
                break;
            }
            if (bytes < 0)
            {
                ERR_print_errors_fp(stderr);
            }
        }
    }

    /*void write_to_server()
    {
        char buf[1024];
        int bytes;

        while (true)
        {
            if (!is_connected)
                break;
            std::cout << "Client: " << std::endl;
            std::cin.getline(buf, sizeof(buf));

            // bytes = SSL_write(ssl, buf, strlen(buf));
            bytes = write(client_socket, buf, strlen(buf));
            if (!is_connected)
                break;
            bytes = write(client_socket, buf, strlen(buf));
            if (strcmp(buf, "chat_close") == 0)
            {
                is_connected = false;
                break;
            }
            if (bytes < 0)
            {
                ERR_print_errors_fp(stderr);
            }
        }
    }*/

    void upgrade_connection()
    {
        ctx = create_context();
        configure_context();
        ssl = create_ssl();
    }

public:
    Client(std::string hostname) : server_hostname(hostname), cert_file("alice.crt"), key_file("aliceKey.pem"), root_cert_file("int.crt")
    {
        client_socket = create_socket(hostname);
        upgrade_connection();
    }

    ~Client()
    {
        close(client_socket);
        SSL_free(ssl);
        SSL_CTX_free(ctx);
    }

    void run()
    {
        std::cout << "Client running" << std::endl;

        // Fork the process to perform read and write operations independently
        /*pid_t pid1 = fork();
        if (pid1 == 0)
        {
            read_from_server();
        }
        else
        {
            write_to_server();
            int returnStatus;
            waitpid(pid1, &returnStatus, 0);
        }*/

        pid_t pid2 = fork();
        if (pid2 == 0)
        {
            SSL_read_from_server();
        }
        else
        {
            SSL_write_to_server();
        }

        std::cout << "Chat closed" << std::endl;
    }
};

#endif
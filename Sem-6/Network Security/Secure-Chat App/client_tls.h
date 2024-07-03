#ifndef CLIENT_TLS_H
#define CLIENT_TLS_H

#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <signal.h>
#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#define SERVER_PORT 4431

class Client
{
private:
	// Connection variables
	BIO *bio;					 // BIO object (wrapper for socket)
	std::string server_hostname; // hostname of the server
	int server_port;			 // port of the server
	bool is_connected;				 // flag to check if the client is connected to the server

	// TLS variables

	// Connection functions
	void open_connection();

	// Wrapper functions to send and receive messages
	void send_message(std::string message);
	std::string receive_message();

	// Protocol function
	bool handle_protocol_message(std::string message);

	// Handshakes
	void hello_handshake();
	void ssl_handshake(){};

	// TLS functions
	void init_openssl();

public:
	Client(std::string server_hostname, int server_port = SERVER_PORT);
	~Client();

	void run();
};


// Constructor to initialize the client and establish a TCP connection to the server
Client::Client(std::string server_hostname, int server_port = SERVER_PORT)
	: server_hostname(server_hostname), server_port(server_port)
{
	// Open the connection to the server
	open_connection();
}

// Destructor to close the connection
Client::~Client()
{
	BIO_free_all(bio);
}

// Run the client
void Client::run()
{
	std::cout << "Client started" << std::endl;

	// Perform the hello handshake
	hello_handshake();

	// Start the chat
	int is_child = fork();
	if(is_child == 0)
	{
		// Read messages from the user and send them to the server
		while(is_connected)
		{
			std::string message;
			std::getline(std::cin, message);
			send_message(message);
		}
	}
	else{
		// Read messages from the server and print them to the console
		while(is_connected)
		{
			std::string message = receive_message();
			if(!handle_protocol_message(message))
				std::cout << "Server: " << message << std::endl;
		}	
	}

	std::cout << "Client stopped" << std::endl;
}

// Open a connection to the server
void Client::open_connection()
{
	// Creates a new BIO object and connects to the server
	bio = BIO_new_connect((server_hostname + ":" + std::to_string(server_port)).c_str());

	// Check if the BIO object was created successfully
	if (bio == NULL)
	{
		std::cerr << "Error creating BIO object" << std::endl;
		exit(EXIT_FAILURE);
	}

	// Check if the connection was successful
	if (BIO_do_connect(bio) <= 0)
	{
		std::cerr << "Error connecting to server" << std::endl;
		exit(EXIT_FAILURE);
	}

	is_connected = true;
}

// Wrapper function to send a message to the server
void Client::send_message(std::string message)
{
	// Check if the client is connected to the server
	if (!is_connected)
	{
		std::cerr << "Client is not connected to the server" << std::endl;
		exit(EXIT_FAILURE);
	}

	// Send the message to the server
	std::cout << "Sending message: " << message << std::endl;
	int status = BIO_write(bio, message.c_str(), message.length());

	// Check if the message was sent successfully
	if(status == 0)
	{	
		is_connected = false;
		std::cerr << "Server connection is closed" << std::endl;
		exit(EXIT_FAILURE);
	}
	else if(status < 0)
	{
		if(!BIO_should_retry(bio))
		{
			std::cerr << "Error sending message to server" << std::endl;
			exit(EXIT_FAILURE);
		}
		// Handle retry
		send_message(message);
	}
}

// Wrapper function to receive a message from the server
std::string Client::receive_message()
{
	// Check if the client is connected to the server
	if (!is_connected)
	{
		std::cerr << "Client is not connected to the server" << std::endl;
		exit(EXIT_FAILURE);
	}

	// Receive the message from the server
	char buffer[1024];
	int status = BIO_read(bio, buffer, 1024);

	// Check if the message was received successfully
	if(status == 0)
	{	
		is_connected = false;
		std::cerr << "Server connection is closed" << std::endl;
		exit(EXIT_FAILURE);
	}
	else if(status < 0)
	{
		if(!BIO_should_retry(bio))
		{
			std::cerr << "Error receiving message from server" << std::endl;
			exit(EXIT_FAILURE);
		}
		// Handle retry
		return receive_message();
	}

	std:: cout << "Received message: " << buffer << std::endl;
	return std::string(buffer);
}

// Handle the protocol messages
bool Client::handle_protocol_message(std::string message)
{	
	if(message == "chat_hello")
		send_message("chat_ok_reply");
	else if(message == "chat_close"){
		send_message("chat_close_ok");
		is_connected = false;
	}
	else if(message == "chat_close_ok")
		is_connected = false;
	else
		return false;

	return true;
}

// Perform the hello handshake
void Client::hello_handshake()
{
	send_message("chat_hello");
	std::string response = receive_message();
	if(response != "chat_ok_reply"){
		std::cerr << "Hello handshake failed" << std::endl;
		exit(EXIT_FAILURE);
	}

	std::cout << "Hello handshake successful" << std::endl;
}

void Client::init_openssl()
{
	SSL_load_error_strings();
	ERR_load_BIO_strings();
	OpenSSL_add_all_algorithms();
}

#endif
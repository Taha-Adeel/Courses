// Write a peer-to-peer application (secure_chat_app) for chatting which uses TLS 1.2 and TCP as the underlying protocols for secure and reliable communication.  Note that the secure_chat_app works like HTTPS except that here it’s a peer-to-peer paradigm where Alice plays the role of the client and Bob plays the role of the server and vice versa.  That means the same program should have different functions for server and client code which can be chosen using command line options “-s” and “-c <serverhostname>” respectively. Feel free to define your own chat headers (if necessary) and add them to the chat payload before giving it to TLS/TCP. Make sure that your application uses only the hostnames for communication between Alice and Bob but not hard-coded IP addresses (refer gethostbyname(3)). The application should perform the following operations:
// Establish a TCP connection between Alice and Bob. Bob starts the app using “secure_chat_app -s”, and Alice starts the app using “secure_chat_app -c bob1” 
// Alice sends a chat_hello application layer control message to Bob and Bob replies with a chat_ok_reply message. It works like a handshake between peers at the application layer. Note that these control messages are sent in plain-text.
// Alice initiates a secure chat session by sending out a chat_START_SSL application layer control message and getting chat_START_SSL_ACK from Bob. Your program should then load the respective private keys and certificates for both Alice and Bob. Furthermore, each of them should have pre-loaded the certificates of the root CA and the intermediate CA in their respective trust stores. 

#include <iostream>
#include <cstring>

#include "server.h"
#include "client.h"

int main(int argc, char *argv[])
{
	if (argc < 2) {
		std::cerr << "Usage: " << argv[0] << " [-s|-c <serverhostname>]" << std::endl;
		return 1;
	}

	if (strcmp(argv[1], "-s") == 0) {
		std::cout << "Starting server..." << std::endl;
		try{
			Server server;
			server.run();
		} catch (std::exception &e) {
			std::cerr << "Server exception: " << e.what() << std::endl;
		}
	} else if (strcmp(argv[1], "-c") == 0) {
		if (argc < 3) {
			std::cerr << "Usage: " << argv[0] << " [-s|-c <serverhostname>]" << std::endl;
			return 1;
		}
		std::cout << "Starting client connection to " << argv[2] << std::endl;
		try{
			Client client(argv[2]);
			client.run();
		} catch (std::exception &e) {
			std::cerr << "Client exception: " << e.what() << std::endl;
		}
	} else {
		std::cerr << "Invalid argument" << std::endl;
		std::cerr << "Usage: " << argv[0] << " [-s|-c <serverhostname>]" << std::endl;
		return 1;
	}

	return 0;
}
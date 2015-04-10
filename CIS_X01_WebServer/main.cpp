#include <iostream>
#include <string>
#include "core.hpp"
#include "socket.hpp"

using namespace X01;

// Our HTTP response header. Note the two \r\n's at the end
#define HEADER "HTTP/1.1 200 OK\r\nContent-Type:text/html; charset=UTF-8\r\nConnection: close\r\n\r\n"

// Our really simple HTML page
#define HTML "<html><body><h1>The website!</h1></body></html>\r\n"

// A buffer to hold incoming data
char buffer[1024];
int len;

int main(int argc, char* argv[]) {
	// Initialize Winsock
	Winsock winsock;

	// See the readme for details about try, catch, and exceptions
	try {

		// Create a Socket
		Socket server;

		// Make up a simple HTTP response with an HTML page
		std::string response;
		response = HEADER;
		response += HTML;

		// Start a server on 
		server.listen("127.0.0.1", 1234);
		std::cout << "Listening...";

		// A socket pointer for the client
		Socket* client;

		// accept() will only return a new socket when a client connects - we wait here
		while (client = server.accept()) {
			std::cout << "Accepted from " << client->remote_host() << "\n";

			// Wait until data is available
			while (!client->data_available()) {
				// NOOP
				// No operation - We didn't just forget to write something here
			}
		
			// Read the data into a buffer.
			client->recv(buffer, 1023, &len);
			std::cout << "Received: \r\n" << buffer << "\r\n";

			// Send the response we made earlier
			client->send(response);

			// Close the socket properly
			client->close();

			// Delete the memory the socket was using
			delete client;
		}

		std::cout << "Done\n";

	// If we have any exceptions in the code, this is where we'll end up
	} catch (std::exception e) {
		std::cout << "EXCEPTION: " << e.what() << "\n\n";
	}

	// Returning 0 means the program finished correctly
	return 0;
}
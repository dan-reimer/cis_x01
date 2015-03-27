#include <iostream>
#include "core.hpp"
#include "socket.hpp"

using namespace X01;

#define REQ "GET / HTTP/1.1\nHost:bccmdev.localhost\nConnection:keep-alive\n\n"

char buffer[1024];
int len;

int main(int argc, char* argv[]) {
	Winsock winsock;

	try {
		Socket tcp;
		tcp.connect("127.0.0.1", 80);
		tcp.send(REQ, strlen(REQ));

		while (tcp.connected()) {
			if (!tcp.data_available()) {
				_sleep(50);
				continue;
			}
			tcp.recv(buffer, 1023, &len);

			buffer[len] = '\0';
			std::cout << buffer;
		}

	} catch (std::exception e) {
		std::cout << "EXCEPTION: " << e.what() << "\n\n";
	}

	return 0;
}
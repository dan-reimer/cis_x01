#include <iostream>
#include <string>
#include "socket.hpp"

using namespace X01;

Socket::Socket() {
	_socket = INVALID_SOCKET;
	_connected = false;
}
Socket::~Socket() {
	if (_socket != INVALID_SOCKET) {
		closesocket(_socket);
	}

	_socket = INVALID_SOCKET;
}
void Socket::_throw_ws_error(const std::string& error) {
	std::string error_number = std::to_string(static_cast<long long>(WSAGetLastError()));
	throw new std::runtime_error(error + " (" + error_number + ")");
}
void Socket::_create_socket(int family, int socktype, int protocol) {
	_socket = ::socket(family, socktype, protocol);
	if (_socket == INVALID_SOCKET) {
		_throw_ws_error("Could not create socket!");
	}
}



Socket& Socket::connect(const std::string& host, int port) {

	hostent *dest_host;
	dest_host = gethostbyname(host.c_str());
	if (!dest_host) _throw_ws_error("Could not get host!");

	addrinfo hints, *result;
	memset(&hints, 0, sizeof(addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	getaddrinfo("127.0.0.1", std::to_string(static_cast<long long>(port)).c_str(), &hints, &result);

	_create_socket(result->ai_family, result->ai_socktype, result->ai_protocol);

	if (::connect(_socket, result->ai_addr, result->ai_addrlen) < 0) {
		_throw_ws_error("Error connecting!");
	}

	_connected = true;

	_dest_host = host;
	_dest_port = port;

	return *this;
}
Socket& Socket::close() {
	closesocket(_socket);
	return *this;
}
Socket& Socket::send(const void* data, int length) {
	int sent = ::send(_socket, (const char*)data, length, 0);
	if (sent == SOCKET_ERROR) {
		_throw_ws_error("Error sending data!");
	}

	std::cout << "Sent " << sent << " bytes\n";

	return *this;
}
Socket& Socket::recv(void* data, int max_length, int *actual_length) {
	if (!data_available()) return *this;

	int received = ::recv(_socket, (char*)data, max_length, 0);
	if (received < 0) _throw_ws_error("Error receiving data!");
	if (received == 0) {
		close();
		_connected = false;
	}

	if (actual_length) *actual_length = received;

	return *this;
}
bool Socket::data_available() {
	fd_set readfds;
	timeval timeout;

	FD_ZERO(&readfds);
	FD_SET(_socket, &readfds);
	timeout.tv_sec = 0;
	timeout.tv_usec = 0;

	int result = select(_socket, &readfds, NULL, NULL, &timeout);
	if (result < 0) _throw_ws_error("Error polling sockets!");
	return result > 0;
}
bool Socket::connected() {
	return _connected;
}



Winsock::Winsock() {
	_wsa_startup_result = WSAStartup(MAKEWORD(2,2), &_wsa_data);
	if (_wsa_startup_result != 0) {
		throw new std::runtime_error("Could not start winsock!");
	}
}
Winsock::~Winsock() {
	WSACleanup();
}
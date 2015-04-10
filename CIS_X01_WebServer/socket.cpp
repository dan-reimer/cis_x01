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

	addrinfo hints, *result;
	memset(&hints, 0, sizeof(addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	getaddrinfo(host.c_str(), std::to_string(static_cast<long long>(port)).c_str(), &hints, &result);

	_create_socket(result->ai_family, result->ai_socktype, result->ai_protocol);

	if (::connect(_socket, result->ai_addr, result->ai_addrlen) < 0) {
		_throw_ws_error("Error connecting!");
	}

	_connected = true;

	_dest_host = host;
	_dest_port = port;

	return *this;
}
Socket& Socket::listen(const std::string& local_host, int port) {
	addrinfo hints, *result;
	memset(&hints, 0, sizeof(addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	getaddrinfo(local_host == "" ? NULL : local_host.c_str(), std::to_string(static_cast<long long>(port)).c_str(), &hints, &result);

	_create_socket(result->ai_family, result->ai_socktype, result->ai_protocol);

	if (::bind(_socket, result->ai_addr, result->ai_addrlen) < 0) {
		_throw_ws_error("Error binding socket!");
	}

	if (::listen(_socket, 20) < 0) {
		_throw_ws_error("Error listening on socket!");
	}

	_listening = true;

	_src_host = local_host;
	_src_port = port;

	return *this;
}
Socket* Socket::accept() {
	sockaddr remote_addr;
	socklen_t addr_size;
	Socket* socket;
	SOCKET temp_sock;

	addr_size = sizeof(remote_addr);
	temp_sock = ::accept(_socket, &remote_addr, &addr_size);

	socket = new Socket();
	socket->_socket = temp_sock;
	socket->_connected = true;

	getpeername(temp_sock, &remote_addr, &addr_size);

	char buffer[256];
	struct sockaddr_in* sin = (struct sockaddr_in*)&remote_addr;
	inet_ntop(sin->sin_family, &sin->sin_addr, buffer, sizeof(buffer));
	socket->_dest_host = buffer;
	socket->_dest_port = sin->sin_port;

	return socket;
}
Socket& Socket::close() {
	closesocket(_socket);
	_connected = false;
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
	}

	if (actual_length) *actual_length = received;

	return *this;
}
Socket& Socket::send(const std::string& data) {
	return this->send(data.c_str(), data.length());
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
bool Socket::listening() {
	return _listening;
}

const std::string& Socket::remote_host() {
	return _dest_host;
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
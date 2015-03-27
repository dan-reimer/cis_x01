#ifndef _SOCKET_HPP
#define _SOCKET_HPP 1

#pragma comment(lib, "Ws2_32.lib")

#undef UNICODE
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdexcept>
#include <string>
#include <vector>

namespace X01 {

	class Socket {
	protected:
		std::string _src_host;
		std::string _dest_host;
		int _src_port;
		int _dest_port;

		int _ai_family;
		int _ai_type;
		int _ai_protocol;

		SOCKET _socket;
		bool _connected;

		void _throw_ws_error(const std::string& error);
		void _create_socket(int family, int socktype, int protocol);
	public:
		Socket();
		~Socket();

		static void initialize();
		static void shutdown();

		Socket& connect(const std::string& host, int port);
		Socket& close();

		Socket& send(const void* data, int length);
		Socket& recv(void* data, int max_length, int *actual_length);

		bool data_available();
		bool connected();
	};







	class Winsock {
	protected:
		int _wsa_startup_result;
		WSADATA _wsa_data;
	public:
		Winsock();
		~Winsock();
	};
};

#endif

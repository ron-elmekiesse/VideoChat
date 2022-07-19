#include <iostream>


#include "AutoInitWinSock/AutoInitWinSock.hpp"
#include "Socket/Socket.hpp"

int wmain()
{
	try
	{
		std::string str{"Hello"};
		Buffer buf{};
		AutoInitWinSock auto_init_win_sock{};
		const AutoCloseSocket auto_close_socket{AF_INET, SOCK_STREAM, IPPROTO_TCP};
		Socket s{auto_close_socket, AF_INET, "127.0.0.1", 8080};
		//s << std::vector<uint8_t>(str.begin(), str.end());
		s << str;
		s >> buf;
		std::cout << std::string(buf.begin(), buf.end()) << std::endl;
	}
	catch (const VideoChatClientException& exc)
	{
		std::cout << exc << std::endl;
	}
	return 0;
}

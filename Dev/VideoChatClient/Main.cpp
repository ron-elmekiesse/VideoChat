#include <iostream>


#include "AutoInitWinSock/AutoInitWinSock.hpp"
#include "Socket/Socket.hpp"


#include "opencv2/opencv.hpp"

int wmain()
{
	try
	{
		AutoInitWinSock auto_init_win_sock{};
		const AutoCloseSocket auto_close_socket{AF_INET, SOCK_STREAM, IPPROTO_TCP};
		Socket s{auto_close_socket, AF_INET, "127.0.0.1", 8080};
		//s << std::vector<uint8_t>(str.begin(), str.end());
		s << "Hello";
		Buffer buf{};
		s >> buf;
		std::cout << buf.data() << std::endl;
	}
	catch (const VideoChatClientException& exc)
	{
		std::cerr << exc << std::endl;
	}
	catch (...)
	{
		std::cerr << "An unknown exception has occurred" << std::endl;
	}
	return 0;
}

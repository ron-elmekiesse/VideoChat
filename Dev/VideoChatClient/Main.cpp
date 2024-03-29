#include <iostream>

#include "AutoInitWinSock/AutoInitWinSock.hpp"
#include "Input/ImageInput.hpp"
#include "Socket/Socket.hpp"
#include "Output/TextOutput.hpp"
#include "ThreadsEntryPoint/ThreadsEntryPoint.hpp"
#include "Input/TextInput.hpp"

int wmain()
{
	AutoInitWinSock auto_init_win_sock{};
	const AutoCloseSocket auto_close_socket{AF_INET, SOCK_STREAM, IPPROTO_TCP};
	Socket s{auto_close_socket, AF_INET, "127.0.0.1", 8080};
	//TextOutput text_output{};

	//ThreadsEntryPoint::server_listener(s, 1, text_output);

	TextInput text_input{};
	ThreadsEntryPoint::client_sender(s, 1, "king ron", 1337, text_input);

	//ImageInput im{};
	//im.take_input();

	//try
	//{
	//	AutoInitWinSock auto_init_win_sock{};
	//	const AutoCloseSocket auto_close_socket{AF_INET, SOCK_STREAM, IPPROTO_TCP};
	//	Socket s{auto_close_socket, AF_INET, "127.0.0.1", 8080};
	//	//s << Buffer(str.begin(), str.end());
	//	s << "Hello";
	//	Buffer buf{};
	//	s >> buf;
	//	std::cout << buf.data() << std::endl;
	//}
	//catch (const VideoChatClientException& exc)
	//{
	//	std::cerr << exc << std::endl;
	//}
	//catch (...)
	//{
	//	std::cerr << "An unknown exception has occurred" << std::endl;
	//}

	return 0;
}

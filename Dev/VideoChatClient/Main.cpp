#include <iostream>

#include "AutoInitWinSock/AutoInitWinSock.hpp"
#include "Input/ImageInput.hpp"
#include "Socket/Socket.hpp"
#include "Output/TextOutput.hpp"
#include "ThreadsEntryPoint/ThreadsEntryPoint.hpp"
#include "Input/TextInput.hpp"
#include "ClientStartup/ClientStartup.hpp"

int wmain()
{
	const AutoInitWinSock auto_init_win_sock{};
	const AutoCloseSocket auto_close_socket{AF_INET, SOCK_STREAM, IPPROTO_TCP};
	Socket s{auto_close_socket, AF_INET, "127.0.0.1", 8080};

	const std::string username = ClientStartup::take_username();
	const uint32_t user_id = ClientStartup::send_client_hello(s, username);
	const uint32_t meeting_id = ClientStartup::client_startup_menu(s, user_id, username);


	const TextOutput text_output{};
	std::thread listener{ThreadsEntryPoint::server_listener, s, meeting_id, text_output};

	TextInput text_input{};
	std::thread sender{ThreadsEntryPoint::client_sender, s, meeting_id, username, user_id, text_input};

	listener.join();
	sender.join();

	return 0;
}

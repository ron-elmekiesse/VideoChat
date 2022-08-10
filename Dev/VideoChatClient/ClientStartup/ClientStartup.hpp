#pragma once

#include <cstdint>
#include <iostream>

#include "PacketCreator/PacketCreator.hpp"
#include "Socket/Socket.hpp"

namespace ClientStartup
{
	std::string take_username();

	uint32_t send_client_hello(Socket& socket, const std::string& username);
	uint32_t client_startup_menu(Socket& socket, const uint32_t uuid, const std::string& username);

	constexpr uint32_t UNKNOWN_MEETING_ID = static_cast<uint32_t>(~0);
	constexpr uint32_t UNKNOWN_USER_ID = static_cast<uint32_t>(~0);
}

#pragma once

#include <iostream>

#include "VideoChatClientException/VideoChatClientException.hpp"
#include "Socket/Socket.hpp"
#include "Input/IInput.hpp"
#include "Output/IOutput.hpp"
#include "Common/Common.hpp"
#include "PacketUtils/PacketUtils.hpp"
#include "PacketCreator/PacketCreator.hpp"

namespace ThreadsEntryPoint
{
	void server_listener(Socket& socket, uint32_t meeting_id, const IOutput& output_device);

	void client_sender(Socket& socket, uint32_t meeting_id, const std::string& name, uint32_t user_unique_id, IInput& input_device);
}
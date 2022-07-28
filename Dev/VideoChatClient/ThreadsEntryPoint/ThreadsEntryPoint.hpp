#pragma once

#include <iostream>

#include "VideoChatClientException/VideoChatClientException.hpp"
#include "Socket/Socket.hpp"
#include "Input/IInput.hpp"
#include "Output/IOutput.hpp"
#include "Common/Common.hpp"
#include "PacketUtils/PacketUtils.hpp"

namespace ThreadsEntryPoint
{
	void server_listener(Socket& socket, uint32_t meeting_id, const IOutput& output_device);
}
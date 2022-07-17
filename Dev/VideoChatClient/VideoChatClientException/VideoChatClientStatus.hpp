#pragma once

#include <ostream>

enum class VideoChatClientStatus
{
	VIDEO_CHAT_CLIENT_SUCCESS = 0,
	AUTO_CLOSE_SOCKET_SOCKET_FAILED,
	AUTO_INIT_WINSOCK_WSA_STARTUP_FAILED,
};

const char* to_string(VideoChatClientStatus e)
{
	switch (e)
	{
	case VideoChatClientStatus::VIDEO_CHAT_CLIENT_SUCCESS: return "VIDEO_CHAT_CLIENT_SUCCESS";
	case VideoChatClientStatus::AUTO_CLOSE_SOCKET_SOCKET_FAILED: return "AUTO_CLOSE_SOCKET_SOCKET_FAILED";
	case VideoChatClientStatus::AUTO_INIT_WINSOCK_WSA_STARTUP_FAILED: return "AUTO_INIT_WINSOCK_WSA_STARTUP_FAILED";
	default: return "unknown";
	}
}

std::ostream& operator<<(std::ostream& os, const VideoChatClientStatus& status)
{
	return os << to_string(status);
}

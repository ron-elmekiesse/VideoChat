#pragma once
#include <ostream>

enum class VideoChatClientStatus
{
	AUTO_CLOSE_SOCKET_SOCKET_FAILED,
};

const char* to_string(const VideoChatClientStatus& e)
{
	switch (e)
	{
	case VideoChatClientStatus::AUTO_CLOSE_SOCKET_SOCKET_FAILED: return "AUTO_CLOSE_SOCKET_SOCKET_FAILED";
	default: return "unknown";
	}
}

std::ostream& operator<<(std::ostream& os, const VideoChatClientStatus& status)
{
	return os << to_string(status);
}

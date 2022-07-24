#pragma once

#include <ostream>

enum class VideoChatClientStatus
{
	VIDEO_CHAT_CLIENT_SUCCESS = 0,
	AUTO_CLOSE_SOCKET_SOCKET_FAILED,
	AUTO_INIT_WINSOCK_WSA_STARTUP_FAILED,
	SOCKET_SEND_FAILED,
	SOCKET_CONNECT_SOCKET_FAILED,
	SOCKET_RECV_FAILED,
	IMAGE_INPUT_OPEN_CAPTURE_FAILED,
	IMAGE_INPUT_READ_FRAME_FAILED,
	IMAGE_OUTPUT_CORRUPTED_IMAGE,
	AUDIO_INPUT_AUDIO_DEVICE_NOT_AVAILABLE,
};

inline const char* to_string(VideoChatClientStatus e)
{
	switch (e)
	{
	case VideoChatClientStatus::VIDEO_CHAT_CLIENT_SUCCESS: return "VIDEO_CHAT_CLIENT_SUCCESS";
	case VideoChatClientStatus::AUTO_CLOSE_SOCKET_SOCKET_FAILED: return "AUTO_CLOSE_SOCKET_SOCKET_FAILED";
	case VideoChatClientStatus::AUTO_INIT_WINSOCK_WSA_STARTUP_FAILED: return "AUTO_INIT_WINSOCK_WSA_STARTUP_FAILED";
	case VideoChatClientStatus::SOCKET_SEND_FAILED: return "SOCKET_SEND_FAILED";
	case VideoChatClientStatus::SOCKET_CONNECT_SOCKET_FAILED: return "SOCKET_CONNECT_SOCKET_FAILED";
	case VideoChatClientStatus::SOCKET_RECV_FAILED: return "SOCKET_RECV_FAILED";
	case VideoChatClientStatus::IMAGE_INPUT_OPEN_CAPTURE_FAILED: return "IMAGE_INPUT_OPEN_CAPTURE_FAILED";
	case VideoChatClientStatus::IMAGE_INPUT_READ_FRAME_FAILED: return "IMAGE_INPUT_READ_FRAME_FAILED";
	case VideoChatClientStatus::IMAGE_OUTPUT_CORRUPTED_IMAGE: return "IMAGE_OUTPUT_CORRUPTED_IMAGE";
	case VideoChatClientStatus::AUDIO_INPUT_AUDIO_DEVICE_NOT_AVAILABLE: return "AUDIO_INPUT_AUDIO_DEVICE_NOT_AVAILABLE";
	default: return "unknown";
	}
}


inline std::ostream& operator<<(std::ostream& os, const VideoChatClientStatus& status)
{
	return os << to_string(status);
}

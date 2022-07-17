#pragma once
#include <cstdint>
#include <ostream>
#include <exception>
#include "VideoChatClientStatus.hpp"

class VideoChatClientException : public std::exception
{
	friend std::ostream& operator<<(std::ostream& os, const VideoChatClientException& obj)
	{
		return os
			<< "VideoChatClientException{status: " << obj.m_status
			<< " error: " << obj.m_last_error << "}";
	}

public:
	VideoChatClientException(VideoChatClientStatus status, uint32_t last_error) :
		std::exception(), m_status(status), m_last_error(last_error)
	{
	}

	~VideoChatClientException() override = default;

	VideoChatClientException(const VideoChatClientException& video_chat_client_exception) = default;
	VideoChatClientException(VideoChatClientException&& video_chat_client_exception) noexcept = default;

	VideoChatClientStatus get_status() const
	{
		return m_status;
	}

	uint32_t get_last_error() const
	{
		return m_last_error;
	}


private:
	const VideoChatClientStatus m_status;
	const uint32_t m_last_error;
};

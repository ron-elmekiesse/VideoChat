#pragma once

#include <cstdint>
#include <WinSock2.h>

#include "VideoChatClientException/VideoChatClientException.hpp"

class AutoCloseSocket
{
public:
	AutoCloseSocket(const SOCKET socket);
	AutoCloseSocket(int32_t address_family, int32_t type, int32_t protocol);
	virtual ~AutoCloseSocket();
	AutoCloseSocket(const AutoCloseSocket&) = delete;
	AutoCloseSocket& operator=(const AutoCloseSocket&) = delete;

	const SOCKET get() const;

private:
	static SOCKET _s_create_socket(int32_t address_family, int32_t type, int32_t protocol);

private:
	const SOCKET m_socket;
};

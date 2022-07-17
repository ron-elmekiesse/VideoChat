#pragma once

#include <cstdint>
#include <WinSock2.h>

#include "VideoChatClientException/VideoChatClientException.hpp"

class AutoCloseSocket
{
public:
	AutoCloseSocket(const SOCKET& socket);
	AutoCloseSocket(uint32_t address_family, uint32_t type, uint32_t protocol);
	virtual ~AutoCloseSocket();
	AutoCloseSocket(const AutoCloseSocket&) = delete;
	AutoCloseSocket& operator=(const AutoCloseSocket&) = delete;

	const SOCKET& get() const;

private:
	static SOCKET _s_create_socket(uint32_t address_family, uint32_t type, uint32_t protocol);

private:
	const SOCKET& m_socket;
};

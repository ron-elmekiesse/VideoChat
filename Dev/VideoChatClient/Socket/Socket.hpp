#pragma once

#define WIN32_LEAN_AND_MEAN

#include <vector>
#include <WinSock2.h>
#include <ws2tcpip.h>

#include "VideoChatClientException/VideoChatClientException.hpp"
#include "AutoCloseSocket/AutoCloseSocket.hpp"


typedef std::vector<uint8_t> Buffer;

class Socket
{
	friend Socket& operator<<(Socket& socket, const Buffer& buffer);
	friend Socket& operator>>(Socket& socket, Buffer& buffer);
	static constexpr uint32_t MAX_PACKET_SIZE = 4194304; // 4MB

public:
	Socket(const AutoCloseSocket& socket, uint16_t sin_family, const std::string& ip, uint16_t port);
	virtual ~Socket() = default;

private:
	uint32_t _recv_once(Buffer& buffer, uint32_t pos) const;

private:
	const AutoCloseSocket& m_socket;
	const uint16_t m_sin_family;
	const std::string& m_ip;
	const uint16_t m_port;
};

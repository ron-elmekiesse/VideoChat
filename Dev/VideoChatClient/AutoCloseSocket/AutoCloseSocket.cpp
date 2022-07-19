#include "AutoCloseSocket.hpp"

AutoCloseSocket::AutoCloseSocket(const SOCKET socket) :
	m_socket(socket)
{
}

AutoCloseSocket::AutoCloseSocket(int32_t address_family, int32_t type, int32_t protocol) :
	m_socket(_s_create_socket(address_family, type, protocol))
{
}


AutoCloseSocket::~AutoCloseSocket()
{
	try
	{
		(void)closesocket(m_socket);
	}
	catch (...)
	{
	}
}

const SOCKET AutoCloseSocket::get() const
{
	return m_socket;
}

SOCKET AutoCloseSocket::_s_create_socket(int32_t address_family, int32_t type, int32_t protocol)
{
	SOCKET sock = socket(address_family, type, protocol);

	if (INVALID_SOCKET == sock)
	{
		throw VideoChatClientException(VideoChatClientStatus::AUTO_CLOSE_SOCKET_SOCKET_FAILED, WSAGetLastError());
	}

	return sock;
}

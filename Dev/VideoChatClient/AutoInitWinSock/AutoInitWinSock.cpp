#include "AutoInitWinSock.hpp"

AutoInitWinSock::AutoInitWinSock()
{
	WSADATA wsa_data{};
	if (0 == WSAStartup(MAKEWORD(2, 2), &wsa_data))
	{
		throw VideoChatClientException(VideoChatClientStatus::AUTO_INIT_WINSOCK_WSA_STARTUP_FAILED, GetLastError());
	}
	if (LOBYTE(wsa_data.wVersion) != 2 || HIBYTE(wsa_data.wVersion) != 2)
	{
		throw VideoChatClientException(VideoChatClientStatus::AUTO_INIT_WINSOCK_WSA_STARTUP_FAILED, GetLastError());
	}
}

AutoInitWinSock::~AutoInitWinSock()
{
	try
	{
		(void)WSACleanup();
	}
	catch (...)
	{
	}
}

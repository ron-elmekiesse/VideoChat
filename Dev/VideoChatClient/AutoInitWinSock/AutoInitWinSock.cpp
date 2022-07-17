#include "AutoInitWinSock.hpp"

AutoInitWinSock::AutoInitWinSock()
{
	WSADATA wsaData{};
	if (0 == WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		throw VideoChatClientException(VideoChatClientStatus::AUTO_INIT_WINSOCK_WSA_STARTUP_FAILED, GetLastError());
	}
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
	{
		throw VideoChatClientException(VideoChatClientStatus::AUTO_INIT_WINSOCK_WSA_STARTUP_FAILED, GetLastError());
	}
}

AutoInitWinSock::~AutoInitWinSock()
{
	try
	{
		WSACleanup();
	}
	catch (...)
	{
	}
}

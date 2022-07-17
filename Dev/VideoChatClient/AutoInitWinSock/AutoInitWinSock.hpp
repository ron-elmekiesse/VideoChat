#pragma once

#include <WinSock2.h>

#include "../VideoChatClientException/VideoChatClientException.hpp"

class AutoInitWinSock
{
public:
	AutoInitWinSock();
	virtual ~AutoInitWinSock();
	AutoInitWinSock(const AutoInitWinSock&) = delete;
	AutoInitWinSock& operator=(const AutoInitWinSock&) = delete;
};

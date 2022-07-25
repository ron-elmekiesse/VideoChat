#include "Socket.hpp"

Socket::Socket(const AutoCloseSocket& socket, const uint16_t sin_family, const std::string& ip, const uint16_t port) :
	m_socket(socket)
{
	// Connect to server:
	sockaddr_in client_service{};
	client_service.sin_family = sin_family;
	inet_pton(sin_family, ip.c_str(), &client_service.sin_addr.s_addr);
	client_service.sin_port = htons(port);

	if (SOCKET_ERROR == connect(m_socket.get(), reinterpret_cast<SOCKADDR*>(&client_service), sizeof(client_service)))
	{
		throw VideoChatClientException(VideoChatClientStatus::SOCKET_CONNECT_SOCKET_FAILED, GetLastError());
	}
}

Socket& operator<<(Socket& socket, const Buffer& buffer)
{
	// Send data:
	int32_t err = send(socket.m_socket.get(),
	                   reinterpret_cast<const char*>(buffer.data()),
	                   static_cast<int>(buffer.size()),
	                   0);
	if (SOCKET_ERROR == err)
	{
		throw VideoChatClientException(VideoChatClientStatus::SOCKET_SEND_FAILED, GetLastError());
	}
	return socket;
}

Socket& operator<<(Socket& socket, const std::string& str)
{
	return socket << Buffer(str.begin(), str.end());
}

Socket& operator>>(Socket& socket, Buffer& buffer)
{
	// Receive data:
	buffer.resize(Socket::MAX_PACKET_SIZE);

	int32_t bytes_read = recv(socket.m_socket.get(),
	                          reinterpret_cast<char*>(buffer.data()),
	                          static_cast<int>(buffer.size()),
	                          0);

	if (bytes_read < 0)
		throw VideoChatClientException(VideoChatClientStatus::SOCKET_RECV_FAILED, GetLastError());

	buffer.resize(bytes_read);
	return socket;
}

Socket& operator>>(Socket& socket, PacketUtils::PacketHeaders& headers)
{
	int32_t bytes_read = recv(socket.m_socket.get(),
	                          reinterpret_cast<char*>(&headers),
	                          sizeof(PacketUtils::PacketHeaders),
	                          0);

	if (bytes_read < 0)
		throw VideoChatClientException(VideoChatClientStatus::SOCKET_RECV_FAILED, GetLastError());
	return socket;
}

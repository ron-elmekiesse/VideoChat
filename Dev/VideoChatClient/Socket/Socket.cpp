#include "Socket.hpp"

Socket::Socket(const AutoCloseSocket& socket, uint16_t sin_family, const char* ip, uint16_t port) :
	m_socket(socket),
	m_sin_family(sin_family),
	m_ip(ip),
	m_port(port)
{
	// Connect to server:
	sockaddr_in client_service{};
	client_service.sin_family = m_sin_family;
	inet_pton(m_sin_family, m_ip, &client_service.sin_addr.s_addr);
	client_service.sin_port = htons(m_port);

	if (SOCKET_ERROR == connect(m_socket.get(), reinterpret_cast<SOCKADDR*>(&client_service), sizeof(client_service)))
	{
		throw VideoChatClientException(VideoChatClientStatus::SOCKET_CONNECTING_SOCKET_FAILED, GetLastError());
	}
}

Socket& operator<<(Socket& socket, const Buffer& buffer)
{
	// Send data:
	int32_t err = send(socket.m_socket.get(), reinterpret_cast<const char*>(buffer.data()),
	                   static_cast<int>(buffer.size()), 0);
	if (SOCKET_ERROR == err)
	{
		throw VideoChatClientException(VideoChatClientStatus::SOCKET_SENDING_DATA_FAILED, GetLastError());
	}
	return socket;
}

Socket& operator>>(Socket& socket, Buffer& buffer)
{
	// Receive data:
	int32_t bytes_read{};
	uint32_t total_bytes_read{};

	buffer.resize(socket.MAX_PACKET_SIZE);

	do
	{
		bytes_read = recv(socket.m_socket.get(), reinterpret_cast<char*>(buffer.data()),
		                  static_cast<int>(buffer.size()), 0);
		if (bytes_read > 0)
			total_bytes_read += bytes_read;
		else if (bytes_read == 0)
			// Connection closed
			continue;
		else
			throw VideoChatClientException(VideoChatClientStatus::SOCKET_RECV_FAILED, GetLastError());
	}
	while (bytes_read > 0);

	buffer.resize(total_bytes_read);
	return socket;
}

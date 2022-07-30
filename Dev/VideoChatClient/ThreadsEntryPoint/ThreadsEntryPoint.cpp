#include "ThreadsEntryPoint.hpp"

void ThreadsEntryPoint::server_listener(Socket& socket, uint32_t meeting_id, const IOutput& output_device)
{
	PacketUtils::PacketHeaders packet_headers{};
	
	try
	{
		while (true)
		{
			socket >> packet_headers;

			PacketUtils::validate_packet(packet_headers, meeting_id); // Throws if invalid packet.

			Buffer data(packet_headers.data_size);

			socket >> data;

			output_device.show_output(data);
		}
	}
	catch (const VideoChatClientException& exc)
	{
		std::cerr << exc << std::endl;
	}
	catch (...)
	{
		std::cerr << "Listener got an Unknown Exception!" << std::endl;
	}
}
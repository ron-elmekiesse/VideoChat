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

			output_device.show_output(data, packet_headers);
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

void ThreadsEntryPoint::client_sender(Socket& socket, uint32_t meeting_id, const std::string& name,
                                      uint32_t user_unique_id, IInput& input_device)
{
	PacketCreator packet_creator{meeting_id, name, user_unique_id};

	try
	{
		while (true)
		{
			input_device.take_input();

			packet_creator.create(input_device.get_type(), input_device.get_data());

			socket << packet_creator.get_raw_packet();
		}
	}
	catch (const VideoChatClientException& exc)
	{
		std::cerr << exc << std::endl;
	}
	catch (...)
	{
		std::cerr << "Sender got an Unknown Exception!" << std::endl;
	}
}

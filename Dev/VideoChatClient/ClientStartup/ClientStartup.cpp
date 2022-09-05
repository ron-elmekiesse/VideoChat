#include "ClientStartup.hpp"

std::string ClientStartup::take_username()
{
	std::string username{};
	do
	{
		std::cout << "Please enter your name (up to " << PacketUtils::PACKET_HEADERS_NAME_SIZE - 1 << " chars): " <<
			std::endl;
		std::getline(std::cin, username);
	}
	while (username.length() > (PacketUtils::PACKET_HEADERS_NAME_SIZE - 1));

	return std::string(username); // To prevent huge chunks of allocated memory staying alive
}

static uint32_t recv_server_hello_packet(Socket& socket)
{
	PacketUtils::PacketHeaders headers{};
	socket >> headers;
	PacketUtils::validate_packet(headers, ClientStartup::UNKNOWN_MEETING_ID, PacketUtils::PacketTypes::ServerHello);
	return headers.user_unique_id;
}

uint32_t ClientStartup::send_client_hello(Socket& socket, const std::string& username)
{
	PacketCreator packet_creator{UNKNOWN_MEETING_ID, username, UNKNOWN_USER_ID};

	packet_creator.create(PacketUtils::PacketTypes::ClientHello, {});
	socket << packet_creator.get_raw_packet();

	return recv_server_hello_packet(socket);
}

static uint32_t recv_enter_meeting_packet(Socket& socket)
{
	PacketUtils::PacketHeaders headers{};
	socket >> headers;
	PacketUtils::validate_packet(headers, PacketUtils::PacketTypes::ServerEnterMeeting);
	return headers.meeting_id;
}

static uint32_t send_enter_meeting_packet(Socket& socket,
                                          const uint32_t uuid,
                                          const std::string& username,
                                          const PacketUtils::PacketTypes packet_type,
                                          const uint32_t meeting_id)
{
	PacketCreator packet_creator{meeting_id, username, uuid};

	packet_creator.create(packet_type, {});
	socket << packet_creator.get_raw_packet();


	return recv_enter_meeting_packet(socket);
}

uint32_t take_meeting_id()
{
	uint32_t meeting_id = 0;
	do
	{
		std::cout << "Enter the meeting ID: ";
		std::cin >> meeting_id;
	}
	while (!meeting_id);

	return meeting_id;
}


uint32_t ClientStartup::client_startup_menu(Socket& socket, const uint32_t uuid, const std::string& username)
{
	uint32_t choice = 0;

	while (true)
	{
		std::cout << "Press " << StartupMenuUserChoice::NewMeeting <<
			" to create a new meeting or " << StartupMenuUserChoice::ExistingMeeting <<
			" for an existing meeting: ";
		std::cin >> choice;

		switch (choice)
		{
		case StartupMenuUserChoice::NewMeeting:
			return send_enter_meeting_packet(socket,
			                                 uuid,
			                                 username,
			                                 PacketUtils::PacketTypes::CreateNewMeeting,
			                                 UNKNOWN_MEETING_ID);
		case StartupMenuUserChoice::ExistingMeeting:
			return send_enter_meeting_packet(socket,
			                                 uuid,
			                                 username,
			                                 PacketUtils::PacketTypes::ConnectToExistingMeeting,
			                                 take_meeting_id());
		default:
			std::cout << "Invalid choice! Try again." << std::endl;
			break;
		}
	}
}

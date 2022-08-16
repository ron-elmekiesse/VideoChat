#include "PacketUtils.hpp"

void PacketUtils::validate_packet(const PacketUtils::PacketHeaders& packet_headers, uint32_t meeting_id,
                                  PacketUtils::PacketTypes packet_type)
{
	if (0 != std::memcmp(MAGIC, packet_headers.magic, PACKET_HEADERS_MAGIC_SIZE))
	{
		throw VideoChatClientException(VideoChatClientStatus::PACKET_UTILS_VALIDATE_PACKET_INVALID_MAGIC);
	}

	if (packet_type != PacketTypes::Uninitialized && packet_headers.packet_type != packet_type)
	{
		throw VideoChatClientException(VideoChatClientStatus::PACKET_UTILS_VALIDATE_PACKET_INVALID_PACKET_TYPE);
	}

	if (meeting_id && meeting_id != packet_headers.meeting_id)
	{
		throw VideoChatClientException(VideoChatClientStatus::PACKET_UTILS_VALIDATE_PACKET_INVALID_MEETING_ID);
	}
}

void PacketUtils::validate_packet(const PacketHeaders& packet_headers, PacketTypes packet_type)
{
	return PacketUtils::validate_packet(packet_headers, 0, packet_type);
}

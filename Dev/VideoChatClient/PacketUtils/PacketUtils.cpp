#include "PacketUtils.hpp"

void PacketUtils::validate_packet(const PacketHeaders& packet_headers, uint32_t meeting_id)
{
	if (meeting_id != packet_headers.meeting_id)
	{
		throw VideoChatClientException(VideoChatClientStatus::PACKET_UTILS_VALIDATE_PACKET_INVALID_MEETING_ID);
	}
	else if (0 != std::memcmp(MAGIC, packet_headers.magic, PACKET_HEADERS_MAGIC_SIZE))
	{
		throw VideoChatClientException(VideoChatClientStatus::PACKET_UTILS_VALIDATE_PACKET_INVALID_MAGIC);
	}
}
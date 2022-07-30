#pragma once

#include <cstring>
#include <cstdint>

#include "VideoChatClientException/VideoChatClientException.hpp"
#include "VideoChatClientException/VideoChatClientStatus.hpp"

namespace PacketUtils
{
	constexpr uint32_t PACKET_HEADERS_MAGIC_SIZE = 4;
	constexpr uint32_t PACKET_HEADERS_NAME_SIZE = 64;
	static constexpr char MAGIC[PACKET_HEADERS_MAGIC_SIZE] = { 'R', 'T', 'V', 'C' };

	enum class PacketDataTypes : uint16_t
	{
		UninitializedDataType = 0,
		TextDataType,
		ImageDataType,
		AudioDataType,
	};

	#pragma pack(1) // Tell the compiler to do not pad the struct at all.
	
	struct PacketHeaders // 82 bytes
	{
		char magic[PACKET_HEADERS_MAGIC_SIZE]; // 4 bytes
		uint32_t meeting_id; // 4 bytes
		uint32_t user_unique_id; // 4 bytes
		char name[PACKET_HEADERS_NAME_SIZE]; // 64 bytes
		PacketDataTypes data_type; // 2 byte
		uint32_t data_size; // 4 bytes
	};
	
	#pragma pack() // Continue using the normal padding.

	void validate_packet(const PacketHeaders& packet_headers, uint32_t meeting_id);
}
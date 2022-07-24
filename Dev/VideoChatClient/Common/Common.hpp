#pragma once

#include <cstdint>
#include <vector>

using Buffer = std::vector<uint8_t>;

constexpr uint32_t PACKET_HEADERS_MAGIC_SIZE = 4;
constexpr uint32_t PACKET_HEADERS_NAME_SIZE = 64;

enum class PacketDataTypes : uint16_t
{
	UninitializedDataType = 0,
	TextDataType,
	ImageDataType,
	AudioDataType,
};

struct PacketHeaders // 82 bytes
{
	char magic[PACKET_HEADERS_MAGIC_SIZE]; // 4 bytes
	uint32_t meeting_id; // 4 bytes
	uint32_t user_unique_id; // 4 bytes
	char name[PACKET_HEADERS_NAME_SIZE]; // 64 bytes
	PacketDataTypes data_type; // 2 byte
	uint32_t data_size; // 4 bytes
};

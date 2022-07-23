#pragma once

#include <cstdint>
#include <vector>

using Buffer = std::vector<uint8_t>;


enum class PacketDataTypes : uint16_t
{
	UninitDataType = 0,
	TextDataType,
	ImageDataType,
	AudioDataType,
};

struct PacketHeaders // 82 bytes
{
	char magic[4]; // 4 bytes
	uint32_t meeting_id; // 4 bytes
	uint32_t user_unique_id; // 4 bytes
	char name[64]; // 64 bytes
	PacketDataTypes data_type; // 2 byte
	uint32_t data_size; // 4 bytes
};

static constexpr char MAGIC[4] = {'R', 'T', 'V', 'C'};

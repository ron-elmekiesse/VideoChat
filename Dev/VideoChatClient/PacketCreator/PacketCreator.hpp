#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <cstdint>
#include <string>
#include <iterator>

#include "Common/Common.hpp"

class PacketCreator
{
public:
	PacketCreator(uint32_t meeting_id, const std::string& name, uint32_t user_unique_id);
	virtual ~PacketCreator() = default;
	PacketCreator(const PacketCreator& packet_creator) = delete;
	PacketCreator& operator=(const PacketCreator&) = delete;

	void create(PacketDataTypes data_type, const Buffer& data);
	const Buffer& get_raw_packet();

private:
	void _set_headers(PacketHeaders& headers, const PacketDataTypes& data_type, const Buffer& data) const;

private:
	uint32_t m_meeting_id;
	const std::string& m_name;
	uint32_t m_user_unique_id;
	Buffer m_raw_packet;
};

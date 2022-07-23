#include "PacketCreator.hpp"

#include <iterator>

PacketCreator::PacketCreator(uint32_t meeting_id, const std::string& name, uint32_t user_unique_id) :
	m_meeting_id(meeting_id),
	m_name(name),
	m_user_unique_id(user_unique_id),
	m_raw_packet()
{}

void PacketCreator::create(PacketDataTypes data_type, const Buffer& data)
{
	m_raw_packet = {};
	PacketHeaders headers{};
	_set_headers(headers, data_type, data);
	m_raw_packet.resize(sizeof(PacketHeaders) + data.size());

	const auto ptr = reinterpret_cast<unsigned char*>(&headers);
	std::copy(ptr, ptr + sizeof(headers), std::back_inserter(m_raw_packet));
	std::copy(data.begin(), data.end(), std::back_inserter(m_raw_packet));
}

void PacketCreator::_set_headers(PacketHeaders& headers, const PacketDataTypes& data_type, const Buffer& data) const
{
	std::strncpy(headers.magic, MAGIC, sizeof(MAGIC));
	headers.meeting_id = m_meeting_id;
	headers.user_unique_id = m_user_unique_id;
	std::strncpy(headers.name, m_name.c_str(), sizeof(headers.name) - 1); // to obtain null terminator.
	headers.data_type = data_type;
	headers.data_size = static_cast<uint32_t>(data.size());
}


const Buffer& PacketCreator::get_raw_packet()
{
	return m_raw_packet;
}

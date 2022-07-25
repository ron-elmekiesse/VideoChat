#pragma once

#include <cstdint>
#include <vector>

#include "Common/Common.hpp"
#include "PacketUtils/PacketUtils.hpp"

class IInput
{
public:
	IInput(PacketUtils::PacketDataTypes input_type) :
		m_input_type(input_type)
	{}

	virtual ~IInput() = default;
	IInput(const IInput&) = delete;
	IInput& operator=(const IInput&) = delete;

	virtual void take_input() = 0;

	Buffer& get_data()
	{
		return m_data;
	}

	PacketUtils::PacketDataTypes get_type() const
	{
		return m_input_type;
	}

protected:
	const PacketUtils::PacketDataTypes m_input_type;
	Buffer m_data;
};

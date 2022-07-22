#pragma once

#include <cstdint>
#include <vector>

#include "Common/Common.hpp"

class IInput
{
public:
	IInput() = default;
	virtual ~IInput() = default;
	IInput(const IInput&) = delete;
	IInput& operator=(const IInput&) = delete;

	virtual void take_input() = 0;

	Buffer& get_data()
	{
		return m_data;
	}

protected:
	Buffer m_data;
};

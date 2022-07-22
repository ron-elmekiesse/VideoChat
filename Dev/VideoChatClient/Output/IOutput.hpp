#pragma once

#include <cstdint>
#include <vector>

#include "Common/Common.hpp"

class IOutput
{
public:
	IOutput() = default;
	virtual ~IOutput() = default;
	IOutput(const IOutput&) = delete;
	IOutput& operator=(const IOutput&) = delete;

	virtual void show_output(Buffer& out) = 0;
};

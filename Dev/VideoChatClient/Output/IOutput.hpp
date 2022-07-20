#pragma once

#include <cstdint>
#include <vector>

typedef std::vector<uint8_t> Buffer;

class IOutput
{
public:
	IOutput() = default;
	virtual ~IOutput() = default;

	virtual void show_output(Buffer& out) = 0;
};

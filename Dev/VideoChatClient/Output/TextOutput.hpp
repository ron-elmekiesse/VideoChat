#pragma once

#include <iostream>
#include <algorithm>

#include "IOutput.hpp"

class TextOutput : public IOutput
{
public:
	void show_output(Buffer& out, const PacketUtils::PacketHeaders& packet_headers) const override;
};

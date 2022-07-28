#pragma once

#include <iostream>
#include <string>

#include "IOutput.hpp"

class TextOutput : public IOutput
{
public:
	void show_output(Buffer& out) const override;
};

#pragma once

#include <iostream>
#include <string>

#include "IInput.hpp"

class TextInput : public IInput
{
public:
	void take_input() override;
};

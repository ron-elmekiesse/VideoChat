#pragma once

#include <iostream>
#include <string>

#include "IInput.hpp"

class TextInput : public IInput
{
public:
	TextInput();
	void take_input() override;
};

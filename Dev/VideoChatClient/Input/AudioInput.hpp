#pragma once

#include <iostream>
#include <string>
#include <Windows.h>
#include <SFML/Audio.hpp>

#include "IInput.hpp"

class AudioInput : public IInput
{
public:
	AudioInput();
	void take_input() override;

private:
	static constexpr uint32_t SAMPLING_DURATION = 5000;
};

#pragma once

#include <iostream>
#include <string>
#include <SFML/Audio.hpp>
#include <Windows.h>

#include "IOutput.hpp"

class AudioOutput : public IOutput
{
public:
	void show_output(Buffer& out) override;

private:
	static constexpr uint32_t SAMPLE_RATE = 44100;
	static constexpr uint32_t MONO_SOUND = 44100;
};

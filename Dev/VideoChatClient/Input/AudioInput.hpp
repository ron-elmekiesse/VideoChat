#pragma once

#include <iostream>
#include <fstream>
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
	void _write_sound_buffer_to_memory(const sf::SoundBuffer& sound_buffer);
	static constexpr char TEMP_AUDIO_FILE_NAME[] = "temp.ogg";
};

#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <SFML/Audio.hpp>

#include "IInput.hpp"
#include "VideoChatClientException/VideoChatClientException.hpp"

class AudioInput : public IInput
{
public:
	AudioInput();
	void take_input() override;

private:
	void _write_sound_buffer_to_memory(const sf::SoundBuffer& sound_buffer);

private:
	static constexpr uint32_t SAMPLING_DURATION = 5000;
	static constexpr char TEMP_AUDIO_FILE_NAME[] = "temp.ogg";
};

//class AudioBuffer
//{
//public:
//	AudioBuffer(const Buffer& buf);
//	AudioBuffer(uint32_t sample_rate, uint32_t channels_count, uint32_t sample_count, const sf::Int16* samples);
//
//	void serialize(Buffer& buf);
//	uint32_t get_sample_rate() const { return m_sample_rate; }
//	uint32_t get_channels_count() const { return m_channels_count; }
//	uint32_t get_sample_count() const { return m_sample_count; }
//	const sf::Int16* get_samples() const { return m_samples; }
//
//private:
//	uint32_t m_sample_rate;
//	uint32_t m_channels_count;
//	uint32_t m_sample_count;
//	const sf::Int16* m_samples;
//};

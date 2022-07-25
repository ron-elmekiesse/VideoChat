#include "AudioOutput.hpp"


void AudioOutput::show_output(Buffer& out)
{
	sf::SoundBuffer buffer{};
	//AudioBuffer audio_buffer{out};
	/*buffer.loadFromSamples(audio_buffer.get_samples(),
	                       audio_buffer.get_sample_count(),
	                       audio_buffer.get_channels_count(),
	                       audio_buffer.get_sample_rate());*/
	buffer.loadFromMemory(out.data(), out.size());

	sf::Sound sound{};
	sound.setBuffer(buffer);
	sound.play();
	Sleep(buffer.getDuration().asMilliseconds());
}

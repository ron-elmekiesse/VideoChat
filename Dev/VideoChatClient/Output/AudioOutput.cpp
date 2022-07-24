#include "AudioOutput.hpp"


void AudioOutput::show_output(Buffer& out)
{
	sf::SoundBuffer buffer{};
	buffer.loadFromSamples(reinterpret_cast<const sf::Int16*>(out.data()), out.size() / 2,
	                       MONO_SOUND, SAMPLE_RATE);

	sf::Sound sound{};
	sound.setBuffer(buffer);
	sound.play();
	Sleep(buffer.getDuration().asMilliseconds());
}

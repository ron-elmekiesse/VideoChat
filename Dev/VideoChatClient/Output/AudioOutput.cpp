#include "AudioOutput.hpp"


void AudioOutput::show_output(Buffer& out)
{
	sf::SoundBuffer buffer{};
	buffer.loadFromMemory(out.data(), out.size());

	sf::Sound sound{};
	sound.setBuffer(buffer);
	sound.play();
	Sleep(buffer.getDuration().asMilliseconds());
}

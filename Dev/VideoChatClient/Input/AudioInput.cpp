#include "AudioInput.hpp"

#include "VideoChatClientException/VideoChatClientException.hpp"


AudioInput::AudioInput()
{
	const std::vector<std::string> available_devices = sf::SoundRecorder::getAvailableDevices();
	for (const auto& available_device : available_devices)
	{
		std::cout << available_device << std::endl;
	}
	if (available_devices.empty() || !sf::SoundBufferRecorder::isAvailable())
	{
		throw VideoChatClientException(VideoChatClientStatus::AUDIO_INPUT_AUDIO_DEVICE_NOT_AVAILABLE);
	}
}

void AudioInput::take_input()
{
	sf::SoundBufferRecorder recorder{};
	recorder.start();
	Sleep(SAMPLING_DURATION);
	recorder.stop();

	const auto buffer = recorder.getBuffer();
	const auto samples = reinterpret_cast<const uint8_t*>(buffer.getSamples());
	m_data = Buffer(samples, samples + buffer.getSampleCount() * 2);
}

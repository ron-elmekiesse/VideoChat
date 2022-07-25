#include "AudioInput.hpp"


AudioInput::AudioInput() :
	IInput(PacketDataTypes::AudioDataType)
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

	_write_sound_buffer_to_memory(recorder.getBuffer());
}

void AudioInput::_write_sound_buffer_to_memory(const sf::SoundBuffer& sound_buffer)
{
	(void)sound_buffer.saveToFile(TEMP_AUDIO_FILE_NAME);

	std::ifstream file(TEMP_AUDIO_FILE_NAME, std::ios::binary);
	if (!file)
	{
		throw VideoChatClientException(VideoChatClientStatus::AUDIO_INPUT_COULD_NOT_OPEN_FILE);
	}
	m_data = Buffer(std::istreambuf_iterator<char>(file), {});
	file.close();
}

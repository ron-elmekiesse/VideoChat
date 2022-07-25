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

	//const sf::SoundBuffer& buffer = recorder.getBuffer();
	/*AudioBuffer audio_buffer{
		buffer.getSampleRate(),
		buffer.getChannelCount(),
		static_cast<uint32_t>(buffer.getSampleCount()),
		buffer.getSamples()
	};*/
	//audio_buffer.serialize(m_data);
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

//
//AudioBuffer::AudioBuffer(const Buffer& buf) :
//	m_samples(reinterpret_cast<const sf::Int16*>(buf.data() + 3 * sizeof(uint32_t)))
//{
//	auto buf_as_uints32 = reinterpret_cast<const uint32_t*>(buf.data());
//	m_sample_rate = buf_as_uints32[0];
//	m_channels_count = buf_as_uints32[1];
//	m_sample_count = buf_as_uints32[2];
//}
//
//AudioBuffer::AudioBuffer(uint32_t sample_rate, uint32_t channels_count, uint32_t sample_count, const sf::Int16* samples)
//	:
//	m_sample_rate(sample_rate),
//	m_channels_count(channels_count),
//	m_sample_count(sample_count),
//	m_samples(samples)
//{}
//
//void AudioBuffer::serialize(Buffer& buf)
//{
//	buf = Buffer{};
//	auto samples_rate_ptr = reinterpret_cast<uint8_t*>(&m_sample_rate);
//	auto channels_count_ptr = reinterpret_cast<uint8_t*>(&m_channels_count);
//	auto sample_count_ptr = reinterpret_cast<uint8_t*>(&m_sample_count);
//	auto samples_ptr = reinterpret_cast<const uint8_t*>(m_samples);
//
//	std::copy(samples_rate_ptr, samples_rate_ptr + sizeof(uint32_t), std::back_inserter(buf));
//	std::copy(channels_count_ptr, channels_count_ptr + sizeof(uint32_t), std::back_inserter(buf));
//	std::copy(sample_count_ptr, sample_count_ptr + sizeof(uint32_t), std::back_inserter(buf));
//	std::copy(samples_ptr, samples_ptr + m_sample_count, std::back_inserter(buf));
//}

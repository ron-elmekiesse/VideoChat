#include "ImageInput.hpp"

#include "VideoChatClientException/VideoChatClientException.hpp"

ImageInput::ImageInput() :
	IInput(PacketUtils::PacketTypes::SendImagePacketType),
	m_capture()
{
	m_capture.open(cv::CAP_ANY);
	if (!m_capture.isOpened())
	{
		throw VideoChatClientException(VideoChatClientStatus::IMAGE_INPUT_OPEN_CAPTURE_FAILED);
	}
	m_capture.set(cv::CAP_PROP_FRAME_WIDTH, IMAGE_WIDTH);
	m_capture.set(cv::CAP_PROP_FRAME_HEIGHT, IMAGE_HEIGHT);
}

void ImageInput::take_input()
{
	cv::Mat frame{};

	m_capture.read(frame);

	if (frame.empty())
	{
		throw VideoChatClientException(VideoChatClientStatus::IMAGE_INPUT_READ_FRAME_FAILED);
	}
	cv::imencode(".jpg", frame, m_data);
}

#include "ImageOutput.hpp"

#include "VideoChatClientException/VideoChatClientException.hpp"

void ImageOutput::show_output(Buffer& out, const PacketUtils::PacketHeaders& packet_headers) const
{
	try
	{
		cv::Mat img = cv::imdecode(out, cv::IMREAD_COLOR);
		cv::imshow(packet_headers.name, img);
	}
	catch (...)
	{
		throw VideoChatClientException(VideoChatClientStatus::IMAGE_OUTPUT_CORRUPTED_IMAGE);
	}
}

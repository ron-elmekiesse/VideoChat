#include "ImageOutput.hpp"

#include "VideoChatClientException/VideoChatClientException.hpp"

void ImageOutput::show_output(Buffer& out)
{
	try
	{
		cv::Mat img = cv::imdecode(out, cv::IMREAD_COLOR);
		cv::imshow("Image", img);
	}
	catch (...)
	{
		throw VideoChatClientException(VideoChatClientStatus::IMAGE_OUTPUT_CORRUPTED_IMAGE, 0); //TODO
	}
}

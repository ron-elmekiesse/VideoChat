#include <opencv2/opencv.hpp>

#include "Input/IInput.hpp"

class ImageInput : public IInput
{
public:
	ImageInput();
	void take_input() override;
	static constexpr uint32_t IMAGE_WIDTH = 1280;
	static constexpr uint32_t IMAGE_HEIGHT = 720;

protected:
	cv::VideoCapture m_capture;
};

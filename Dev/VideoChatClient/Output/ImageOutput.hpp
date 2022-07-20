#pragma once
#include <opencv2/opencv.hpp>

#include "Output/IOutput.hpp"

class ImageOutput : public IOutput
{
public:
	void show_output(Buffer& out) override;
};

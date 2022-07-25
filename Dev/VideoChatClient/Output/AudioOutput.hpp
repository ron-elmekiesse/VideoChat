#pragma once

#include <iostream>
#include <string>
#include <SFML/Audio.hpp>
#include <Windows.h>

#include "IOutput.hpp"

class AudioOutput : public IOutput
{
public:
	void show_output(Buffer& out) override;
};

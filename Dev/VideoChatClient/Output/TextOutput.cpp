#include "TextOutput.hpp"

void TextOutput::show_output(Buffer& out)
{
	std::cout << out.data() << std::endl;
}

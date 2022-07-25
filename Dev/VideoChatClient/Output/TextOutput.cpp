#include "TextOutput.hpp"

void TextOutput::show_output(Buffer& out) const
{
	std::cout << out.data() << std::endl;
}

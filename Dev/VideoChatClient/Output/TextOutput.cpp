#include "TextOutput.hpp"

void TextOutput::show_output(Buffer& out) const
{
	// Display the Buffer content without Null-Terminator.
	std::for_each(out.begin(), out.end(), [](const auto& chr) {std::cout << chr; });
	std::cout << std::endl;
}

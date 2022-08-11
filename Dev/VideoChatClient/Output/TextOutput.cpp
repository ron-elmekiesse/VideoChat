#include "TextOutput.hpp"

void TextOutput::show_output(Buffer& out, const PacketUtils::PacketHeaders& packet_headers) const
{
	// Display the Buffer content without the need of Null-Terminator.
	std::cout << packet_headers.name << " send: ";
	std::for_each(out.begin(), out.end(), [](const auto& chr) { std::cout << chr; });
	std::cout << std::endl;
}

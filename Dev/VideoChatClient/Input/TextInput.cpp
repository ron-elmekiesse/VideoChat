#include "TextInput.hpp"

TextInput::TextInput() :
	IInput(PacketUtils::PacketTypes::SendText)
{}

void TextInput::take_input()
{
	std::string input{};
	while (!input.length())
	{
		(void)std::getline(std::cin, input);
	}
	m_data = Buffer(input.begin(), input.end());
}

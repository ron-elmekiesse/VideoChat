#include "TextInput.hpp"

TextInput::TextInput() :
	IInput(PacketUtils::PacketTypes::SendText)
{}

void TextInput::take_input()
{
	std::cout << "Enter your message: ";

	std::string input{};
	while (!input.length())
	{
		(void)std::getline(std::cin, input);
	}
	m_data = Buffer(input.begin(), input.end());
}

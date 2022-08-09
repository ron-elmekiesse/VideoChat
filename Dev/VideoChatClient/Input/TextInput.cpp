#include "TextInput.hpp"

TextInput::TextInput() :
	IInput(PacketUtils::PacketTypes::SendTextPacketType)
{}

void TextInput::take_input()
{
	std::string input{};
	(void)std::getline(std::cin, input);
	m_data = Buffer(input.begin(), input.end());
}

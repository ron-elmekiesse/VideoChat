#include <cstdint>
#include <vector>

typedef std::vector<uint8_t> Buffer;

class IInput
{
public:
	IInput() = default;
	virtual ~IInput() = default;

	virtual void take_input() = 0;

	Buffer& get_data()
	{
		return m_data;
	}

protected:
	Buffer m_data;
};

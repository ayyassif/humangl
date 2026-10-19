#include "Debugger.hpp"

Debugger::Debugger(std::string_view label,
				   std::string_view color,
				   std::ostream& output)
	: m_label(label), m_color(color), m_output(output)
{
}

Debugger& Debugger::operator<<(char value)
{
	if (value == '\n')
		finishLine();
	else
	{
		startLine();
		m_output.put(value);
	}
	return *this;
}

Debugger& Debugger::operator<<(StreamManipulator manipulator)
{
	if (manipulator == endlManipulator())
	{
		if (m_lineStarted)
			m_output << RESET;
		manipulator(m_output);
		m_lineStarted = false;
	}
	else
	{
		startLine();
		manipulator(m_output);
	}
	return *this;
}

Debugger::StreamManipulator Debugger::endlManipulator()
{
	return static_cast<StreamManipulator>(std::endl<char, std::char_traits<char>>);
}

void Debugger::startLine()
{
	if (m_lineStarted)
		return;

	m_output << m_color << '[' << m_label << "] ";
	m_lineStarted = true;
}

void Debugger::finishLine()
{
	if (m_lineStarted)
		m_output << RESET;
	m_output.put('\n');
	m_lineStarted = false;
}

void Debugger::writeText(std::string_view text)
{
	for (char character : text)
	{
		if (character == '\n')
			finishLine();
		else
		{
			startLine();
			m_output.put(character);
		}
	}
}











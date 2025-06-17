#include "stdafx.h"
#include "string_utilities.h"
#include <stdarg.h>
#include <cctype>
#include <functional>
#include <algorithm>

static constexpr char WhitespaceChars[] = " \t\n\r\f\v";

void _string_format(const std::string_view fmt, std::string* result, va_list args)
{
	char buffer[1024];
	_vsnprintf(buffer, sizeof(buffer), fmt.data(), args);
	*result = buffer;
}

std::string string_format(const std::string_view fmt, ...)
{
	std::string result;
	va_list ap;

	va_start(ap, fmt);
	_string_format(fmt, &result, ap);
	va_end(ap);

	return result;
}

// trim from end
std::string& rtrim(std::string& s)
{
	s.erase(s.find_last_not_of(WhitespaceChars) + 1);
	return s;
}

// trim from start
std::string& ltrim(std::string& s)
{
	s.erase(0, s.find_first_not_of(WhitespaceChars));
	return s;
}

void strtolower(std::string& str)
{
	for (size_t i = 0; i < str.length(); ++i)
		str[i] = (char) tolower(str[i]);
};

void strtoupper(std::string& str)
{
	for (size_t i = 0; i < str.length(); ++i)
		str[i] = (char) toupper(str[i]);
}

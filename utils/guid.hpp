#pragma once
#ifndef _COLA_UTILS_GUID_HPP_
#define _COLA_UTILS_GUID_HPP_

#include <sstream>
#include <random>
#include <string>

namespace cola
{
	inline unsigned int random_char()
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis(0, 255);
		return dis(gen);
	}

	inline std::string guid_hex(unsigned int const len)
	{
		std::ostringstream oss;
		for (unsigned int i = 0; i < len; ++i)
		{
			auto const rc = random_char();
			std::ostringstream hex_stream;
			hex_stream << std::hex << rc;
			auto hex = hex_stream.str();
			oss << (hex.length() < 2 ? '0' + hex : hex);
		}
		return oss.str();
	}
}

#endif // !_COLA_UTILS_GUID_HPP_

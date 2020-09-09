#pragma once
#ifndef _COLA_UTILS_RAW_ARRAY_HPP_
#define _COLA_UTILS_RAW_ARRAY_HPP_

#include <algorithm>

namespace cola
{
	template <typename T, size_t N, typename U, size_t M>
	inline bool equals(T(&a)[N], U(&b)[M])
	{
		if (N != M)
			return false;
	}
}

#endif // !_COLA_UTILS_RAW_ARRAY_HPP_

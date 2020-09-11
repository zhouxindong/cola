#pragma once
#ifndef _COLA_UTILS_RAW_ARRAY_HPP_
#define _COLA_UTILS_RAW_ARRAY_HPP_

#include <algorithm>

namespace cola
{
	// raw array equals
	template <typename T, size_t N, typename U, size_t M>
	inline bool equals(T(&a)[N], U(&b)[M])
	{
		if (N != M)
			return false;

		for (size_t i = 0; i < N; ++i)
		{
			if (a[i] != b[i])
				return false;
		}
		return true;
	}
}


#endif // !_COLA_UTILS_RAW_ARRAY_HPP_

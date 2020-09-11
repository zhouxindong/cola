#pragma once
#ifndef _COLA_UTILS_CONTAINER_HPP_
#define _COLA_UTILS_CONTAINER_HPP_

#include <algorithm>
#include <functional>
#include <type_traits>

namespace cola
{
	// erase-remove style for container
	//template <typename Container>
	//inline Container& erase_remove(Container& c,
	//	std::function<bool(typename Container::value_type)> f)
	//{
	//	c.erase(std::remove_if(c.begin(), c.end(), f), c.end());
	//	return c;
	//}

	template <typename Container>
	inline Container& erase_remove(Container& c,
		std::function<bool(std::add_lvalue_reference_t<typename Container::value_type>)> f)
	{
		c.erase(std::remove_if(c.begin(), c.end(), f), c.end());
		return c;
	}

	// replace new value for set element
	template <typename Container>
	inline bool replace_key(Container& c,
		const typename Container::key_type& old_key,
		const typename Container::key_type& new_key)
	{
		typename Container::iterator pos;
		pos = c.find(old_key);
		if (pos != c.end())
		{
			c.insert(typename Container::value_type(new_key, pos->second));
			c.erase(pos);
			return true;
		}
		else
			return false;
	}
}

#endif // !_COLA_UTILS_CONTAINER_HPP_

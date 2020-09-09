#pragma once
#ifndef _COLA_BASE_TYPE_INFO_HPP_
#define _COLA_BASE_TYPE_INFO_HPP_

#include <typeinfo>
#include <cassert>

namespace cola
{
	class Type_info
	{
	public: // ctor
		Type_info(); // needed for containers
		Type_info(const std::type_info&); // non-explicit

	public:
		const std::type_info& get() const; // access for the wrapped std::type_info
		
		// compatibility functions
		bool before(const Type_info& rhs) const;
		const char* name() const;

	private:
		const std::type_info* info_;
	};
}

inline cola::Type_info::Type_info()
{
	class Nil {};
	info_ = &typeid(Nil);
	assert(info_);
}

inline cola::Type_info::Type_info(const std::type_info& ti)
	: info_(&ti)
{
	assert(info_);
}

inline const std::type_info& cola::Type_info::get() const
{
	assert(info_);
	return *info_;
}

inline bool cola::Type_info::before(const Type_info& rhs) const
{
	assert(info_);
	return info_->before(*rhs.info_) != 0;
}

inline const char* cola::Type_info::name() const
{
	assert(info_);
	return info_->name();
}

namespace cola
{
	// comparison operators
	inline bool operator==(const Type_info& lhs, const Type_info& rhs)
	{
		return (lhs.get() == rhs.get()) != 0;
	}

	inline bool operator<(const Type_info& lhs, const Type_info& rhs)
	{
		return lhs.before(rhs);
	}

	inline bool operator!=(const Type_info& lhs, const Type_info& rhs)
	{
		return !(lhs == rhs);
	}

	inline bool operator>(const Type_info& lhs, const Type_info& rhs)
	{
		return rhs < lhs;
	}

	inline bool operator<=(const Type_info& lhs, const Type_info& rhs)
	{
		return !(lhs > rhs);
	}

	inline bool operator>=(const Type_info& lhs, const Type_info& rhs)
	{
		return !(lhs < rhs);
	}
}

#endif // !_COLA_BASE_TYPE_INFO_HPP_

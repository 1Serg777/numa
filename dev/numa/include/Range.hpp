#pragma once

#include <type_traits>
#include <limits>

namespace numa
{
	template<
		typename T,
		std::enable_if_t<
			std::is_floating_point_v<typename T> || std::is_integral_v<typename T>,
			bool> = true>
	class Range
	{
	public:

		using type = typename T;

		Range() = default;

		Range(type min, type max)
			: min(min), max(max)
		{
		}

		bool WithinRangeInclusive(type check) const
		{
			if (min <= check && check <= max)
				return true;
			return false;
		}
		bool WithinRangeExclusive(type check) const
		{
			if (min < check && check < max)
				return true;
			return false;
		}

		type Clamp(type value) const
		{
			if (value < min) return min;
			if (value > max) return max;
			return value;
		}

		type RangeLength() const
		{
			return max - min;
		}

		type GetMinRange() const
		{
			return min;
		}
		type GetMaxRange() const
		{
			return max;
		}

	private:

		type min{ std::numeric_limits<type>::max() };
		type max{ std::numeric_limits<type>::lowest() };
	};
}
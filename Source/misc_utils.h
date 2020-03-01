#pragma once
#include "utilities.h"

namespace Utils
{
	struct djb2hash
	{
		size_t operator()(const char* cp) const
		{
			size_t hash = 5381;
			while (*cp)
				hash = 33 * hash ^ (unsigned char)*cp++;
			return hash;
		}
	};

	struct charPtrKeyEq
	{
		bool operator()(const char* first, const char* second) const
		{
			return !strcmp(first, second);
		}
	};
}
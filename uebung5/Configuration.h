#ifndef _CONFIGURATION_H
#define _CONFIGURATION_H

#include <cmath>

#define log2(x) static_cast<unsigned>(log((x)) / log(2))
#define pow2(x) (1 << (x))

struct Configuration
{
	typedef enum {
		DIRECT_MAPPED,
		FULLY_ASSOCIATIVE,
		SET_ASSOCIATIVE
	} Associativity;
	// cacheSize in KB, cacheLineSize in Byte addressSize in Bit.
	// values should be power of two
	Configuration(
		Associativity associativity,
		unsigned cacheSize = 256, 
		unsigned cacheLineSize = 64, 
		unsigned addressSize = 64,
		unsigned associativityLevel = 4) : 
			associativity(associativity),
			cacheLineSize(cacheLineSize),
			addressSize(addressSize),
			associativityLevel(associativityLevel)

	{
		cacheLines = cacheSize * 1024 / cacheLineSize;
		offsetBits = log2(cacheLineSize);
		maxOffset = cacheLineSize - 1;

		switch (associativity)
		{
			case Associativity::DIRECT_MAPPED:
				indexBits = log2(cacheLines);
				tagBits = addressSize - indexBits - offsetBits;
				break;
			case Associativity::SET_ASSOCIATIVE:
				indexBits = log2(cacheLines / associativity);
				break;
			case Associativity::FULLY_ASSOCIATIVE:
				indexBits = 0;
				tagBits = addressSize - offsetBits; 
				break;
		}
		maxIndex = pow2(indexBits) - 1;
		maxTag = pow2(tagBits) - 1;
	}
	Associativity associativity;

	unsigned tagBits;
	unsigned indexBits;
	unsigned offsetBits;
	unsigned cacheLines;
	unsigned cacheLineSize;
	const unsigned addressSize;
	unsigned associativityLevel;

	unsigned maxTag;
	unsigned maxIndex;
	unsigned maxOffset;
};

#endif /* _CONFIGURATION_H */

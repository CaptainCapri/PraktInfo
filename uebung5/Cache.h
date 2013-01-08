#ifndef _CACHE_H
#define _CACHE_H

#include <cassert>
#include <climits>
#include <map>

#include "Configuration.h"

#define pow2(x) (1 << (x))

class Cache
{
public:
	Cache(const Configuration& config) : m_HitCounter(0), m_MissCounter(0), m_Config(config)
	{
	}

	~Cache()
	{
	}

	void read(unsigned long long adress, unsigned size)
	{
		unsigned keyOffset = adress & ( pow2(m_Config.offsetBits) - 1 );
		assert(keyOffset <= m_Config.maxOffset);

		unsigned keyIndex = (adress >> m_Config.offsetBits) & ( pow2(m_Config.indexBits) - 1 );
		assert(keyIndex <= m_Config.maxIndex);

		unsigned keyTag	= unsigned(adress >> (m_Config.offsetBits + m_Config.indexBits));
		assert(keyTag <= m_Config.maxTag);

		CacheLine *cacheLine = &m_Data[keyIndex][keyTag];

		for (unsigned i = 0; i < size; i++)
		{
			(*cacheLine)[keyOffset].valid ? m_HitCounter++ : m_MissCounter++;
			
			keyOffset++;

			if (keyOffset > m_Config.maxOffset) 
			{
				keyOffset = 0;
				keyTag++;

				if (keyTag > m_Config.maxTag)
				{
					keyTag = 0;
					keyIndex++;

					if (keyIndex > m_Config.maxIndex)
					{
						keyIndex = 0;
					}
				}

				cacheLine = &m_Data[keyIndex][keyTag];
			}
		}
	}

	void store(unsigned long long adress, unsigned size)
	{
		unsigned keyOffset = adress & ( pow2(m_Config.offsetBits) - 1 );
		assert(keyOffset <= m_Config.maxOffset);

		unsigned keyIndex = (adress >> m_Config.offsetBits) & ( pow2(m_Config.indexBits) - 1 );
		assert(keyIndex <= m_Config.maxIndex);

		unsigned keyTag	= unsigned(adress >> (m_Config.offsetBits + m_Config.indexBits));
		assert(keyTag <= m_Config.maxTag);

		CacheLine *cacheLine = &m_Data[keyIndex][keyTag];

		for (unsigned i = 0; i < size; i++)
		{
			(*cacheLine)[keyOffset].valid = true;
			
			keyOffset++;

			if (keyOffset > m_Config.maxOffset) 
			{
				keyOffset = 0;
				keyTag++;

				if (keyTag > m_Config.maxTag)
				{
					keyTag = 0;
					keyIndex++;

					if (keyIndex > m_Config.maxIndex)
					{
						keyIndex = 0;
					}
				}

				cacheLine = &m_Data[keyIndex][keyTag];
			}
		}
	}

	void modify(unsigned long long adress, unsigned size)
	{
		store(adress, size);
	}

	void load(unsigned long long adress, unsigned size)
	{
		read(adress, size);
	}

	unsigned getHitCount() const
	{
		return m_HitCounter;
	}

	unsigned getMissCount() const
	{
		return m_MissCounter;
	}

private:

	unsigned m_HitCounter;
	unsigned m_MissCounter;
	const Configuration m_Config;

	struct CacheEntry
	{
		CacheEntry() : valid(false)
		{
		}
		bool valid;
	};
	
	typedef std::map<unsigned, CacheEntry> CacheLine;
	std::map<unsigned, std::map<unsigned, CacheLine> > m_Data;
};

#endif /* _CACHE_H */

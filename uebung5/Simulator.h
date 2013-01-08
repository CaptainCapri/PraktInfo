#ifndef _SIMULATOR_H
#define _SIMULATOR_H

#include <iostream>

#include "Cache.h"
#include "Configuration.h"
#include "Parser.h"
#include "TraceElement.h"

class Simulator
{
public:
	Simulator(const Configuration& instructionCache, const Configuration& dataCache, const char* filename) :
		m_InstructionCache(instructionCache),
		m_DataCache(dataCache),
		m_Parser(filename)
	{
	}

	~Simulator()
	{
	}

	void run()
	{
		while (true)
		{
			try 
			{
				TraceElement traceElement = m_Parser.getNextElement();
				switch (traceElement.type)
				{
					case TraceElement::Type::INSTR:
						m_InstructionCache.read(traceElement.address, traceElement.size);
						break;
					case TraceElement::Type::LOAD:
						m_DataCache.load(traceElement.address, traceElement.size);
						break;
					case TraceElement::Type::SAVE:
						m_DataCache.store(traceElement.address, traceElement.size);
						break;
					case TraceElement::Type::MOD:
						m_DataCache.modify(traceElement.address, traceElement.size);
						break;
				}
			}
			catch(Parser::EOFException)
			{
				//finished cache simulation
				break;
			}
			
		}
	}

	void printResults() 
	{
		unsigned iHits = m_InstructionCache.getHitCount();
		unsigned iMiss = m_InstructionCache.getMissCount();

		unsigned dHits = m_DataCache.getHitCount();
		unsigned dMiss = m_DataCache.getMissCount();

		std::cout << "## Instruction Cache ##" << std::endl;
		std::cout << "Hits:\t\t" << iHits << std::endl;
		std::cout << "Hit Ratio:\t" << iHits / double(iMiss + iHits) * 100 << "%" << std::endl;

		std::cout << "Miss:\t\t" << iMiss << std::endl;
		std::cout << "Miss Ratio:\t" << iMiss / double(iMiss + iHits) * 100 << "%" << std::endl;

		std::cout << "Total:\t\t" << iMiss + iHits << std::endl;

		std::cout << std::endl;

		std::cout << "## Data Cache ##" << std::endl;
		std::cout << "Hits:\t\t" << dHits << std::endl;
		std::cout << "Hit Ratio:\t" << dHits / double(dMiss + dHits) * 100 << "%" << std::endl;

		std::cout << "Miss:\t\t" << dMiss << std::endl;
		std::cout << "Miss Ratio:\t" << dMiss / double(dMiss + dHits) * 100 << "%" << std::endl;

		std::cout << "Total:\t\t" << dMiss + dHits << std::endl;

	}

private:
	Cache m_InstructionCache;
	Cache m_DataCache;
	Parser m_Parser;
};


#endif /* _SIMULATOR_H */

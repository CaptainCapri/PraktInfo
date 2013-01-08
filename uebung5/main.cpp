#include <string>
#include <iostream>

#include "Cache.h"
#include "Configuration.h"
#include "Parser.h"
#include "Simulator.h"

int main(int argc, const char* argv[])
{
	
	Configuration config(Configuration::Associativity::DIRECT_MAPPED);
	
	Simulator sim(config, config, "trace-ls.txt");
	sim.run();

	sim.printResults();
	
	return 0;
}
#ifndef _PARSER_H
#define _PARSER_H

#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "TraceElement.h"

class Parser
{
public:
	Parser(std::string fileName) : 
		m_Stream(fileName.c_str(), std::ifstream::in)
	{
		if (!m_Stream.is_open())
			std::cout << "Error initializing ifstream: Maybe wrong path given" << std::endl;
		
		//read first line from stream to remove header of trace-file
		std::string firstLine;
		std::getline(m_Stream, firstLine);
		if (firstLine.find("valgrind --tool=lackey") == std::string::npos)
			std::cout << "Error wrong file loaded" << std::endl;
		else
			std::cout << "found lackey file" << std::endl;
	}

	~Parser()
	{
		m_Stream.close();
	}

	const TraceElement getNextElement()
	{
		// extract all string parts from line
		
		char typeChar;
		std::string line;
		std::string addressCommaAndSize;
		std::string addressString;
		std::string sizeString;

		while(true)
		{
			if (m_Stream.eof()) throw EOFException();
			std::getline(m_Stream, line);
			//std::cout << line;

			while (line.length() <= 0) 
			{
				if (m_Stream.eof()) throw EOFException();
				std::getline(m_Stream, line);
				//std::cout << line;
			}

			if (line[0] == ' ') line = line.substr(1);
		
			if (line.length() <= 0) continue;

			typeChar = line[0];

			size_t pos = line.find_last_of(" ");
			if (pos == line.npos || pos+1 == line.npos) continue;

			line = line.substr(pos+1);

			pos = line.find(",");
			if (pos == line.npos || pos+1 == line.npos) continue;
			addressString = line.substr(0, pos-1);
			sizeString = line.substr(pos+1);

			break;
		}
		// this is a trick to avoid long if/else statement: type is typeof(char)
		// so static_cast is working :)
		TraceElement::Type type = static_cast<TraceElement::Type>(typeChar);
		
		// use stringstream to convert string to uint64_t(ulonglong)
		unsigned long long address;
		std::stringstream ss;
		ss << std::hex << addressString;
		ss >> address;
		
		//clear stream to use it for conversion of string to size_t
		ss.clear();
		size_t size;
		ss << sizeString;
		ss >> size;
		

		return TraceElement(type, address, size);
	}

	struct EOFException : public std::exception
	{
		const char* what()
		{
			return "eof reached";
		}

	};
	
private:
	std::ifstream m_Stream;
};


#endif /* _PARSER_H */

#ifndef _TRACE_ELEMENT_H
#define _TRACE_ELEMENT_H


struct TraceElement
{
	typedef enum { INSTR = 'I', LOAD = 'L', SAVE = 'S', MOD  = 'M'} Type;
	TraceElement(Type type, unsigned long long address, size_t size) :
		type(type),
		address(address),
		size(size)
	{
	}

	Type type;
	unsigned long long address;
	size_t size;
};


#endif /* _TRACE_ELEMENT_H */

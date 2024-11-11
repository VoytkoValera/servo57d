#include <SEGGER_RTT.h>
#include <stdio.h>

#include "log.h"

void print_log(const char * sFormat, ...)
{	
	va_list ParamList;
	va_start(ParamList, sFormat);
	SEGGER_RTT_vprintf(0, sFormat, &ParamList);
	va_end(ParamList);
}
#ifndef __AIRPORT__
#define __AIRPORT__

#include "functionsLib.h"

typedef struct
{
	char* name;
	char* address;
}Airport;

int isSameAirport(const Airport *a1, const Airport *a2);
int isAirportName(const Airport *a1, const char name[]);
void freeAirport(Airport* a1);
#endif

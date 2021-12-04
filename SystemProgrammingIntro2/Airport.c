#include <string.h>
#include "Airport.h"

int isSameAirport(const Airport *a1, const Airport *a2)
{
	return strcmp(a1->name, a2->name) == 0;
}
int isAirportName(const Airport *a1, const char name[])
{
	return strcmp(a1->name, name) == 0;
}
void doPrintAirport(Airport* pai)
{
	printf("Airport name: %s\n", pai->name);
	printf("Airport address: %s\n", pai->address);
}

void freeAirport(Airport* a1)
{
	free(a1->address);
	free(a1->name);
	free(a1);
}
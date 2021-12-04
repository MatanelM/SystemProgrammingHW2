#include <string.h>
#include "Flight.h"

const char* airplaneTypes[] = { "Passengers", "Container", "Military" };

int isFlightFromSourceName(const Flight *pf, const char from[])
{
	return strcmp(pf->from.name, from) == 0;
}
int isFlightFromDestName(const Flight *pf, const char to[])
{
	return strcmp(pf->to.name, to) == 0;
}
int isPlaneCodeInFlight(const Flight *pf, const char code[])
{
	return strcmp(pf->airplane.code, code) == 0;
}
int isPlaneTypeInFlight(const Flight *pf, const AirplaneType type)
{
	return pf->airplane.type == type;
}
void freeFlight(Flight* pf)
{
	free(pf->from);
	free(pf->to);
	freeAirplane(&(pf->airplane));
	free(pf);
}

void freeAirplane(Airplane* a1)
{
	free(a1->code);
	free(a1);

}
// add more here for flight

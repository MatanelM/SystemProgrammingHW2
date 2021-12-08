
#ifndef __AIRLINE__
#define __AIRLINE__


#include "functionsLib.h"
#include "Flight.h"

typedef struct
{
	char name[L_255];
	Flight* flights[MAX_FLIGHTS];
	int numOfFlights;
	// add more as required
}Airline;

Airline* initAirline();
int addFlight(Airline *pai, Flight *pf);
void doPrintFlightsWithPlaneCode(const Airline *pai, const char code[L_CODE]);
void doPrintFlightsWithPlaneType(const Airline *pai, const AirplaneType type);
int doCountFlightsFromName(const Airline *pai, const char name[L_255]);
void doPrintFlight(const Flight *pf);
void doPrintAirline(const Airline *pai);
void freeAirline(Airline* pai);
// add more functions declarations as required

#endif

#ifndef __MENUFUNCTIONS__
#define __MENUFUNCTIONS__
#define _CRT_SECURE_NO_WARNINGS

#include "AirportManager.h"
#include "Airline.h"
#include "functionsLib.h"
#include "Airport.h"
#include "Flight.h"

int f_addFlight(AirportManager* pam, Airline* pai);

int f_addAirport(AirportManager* pam);

int f_printAirline(Airline* pai);

int f_printAirlineManager(AirportManager* pam);

int f_printNumberOfFlightFromLocation(Airline* pai);

int f_printFlightsWithAirplaneCode(Airline* pai);

int f_printFlightsWithAirplaneType(Airline* pai);

int f_calculateSizes(void);


#endif
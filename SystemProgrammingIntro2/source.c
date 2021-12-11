#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "AirportManager.h"
#include "Airport.h"
#include "Airline.h"
#include "Flight.h"
#include "functionsLib.h"

int f_addFlight(AirportManager* pam, Airline* pai);
int f_addAirport(AirportManager* pam);
int f_printAirline(Airline* pai);
int f_printAirlineManager(AirportManager* pam);
int f_printNumberOfFlightFromLocation(Airline* pai);
int f_printFlightsWithAirplaneCode(Airline* pai);
int f_printFlightsWithAirplaneType(Airline* pai);
int f_calculateSizes(void);

int main(void)
{
	int p = 1;

	AirportManager* pam = initAirportManager();
	if (!pam)
	{
		return 1;
	}

	Airline* pai = initAirline();
		

	printf("Would you like to add an airport? (1 - Yes)\n");
	scanf_s("%d", &p);
	while (p == 1)
	{
		clearBuffer();
		f_addAirport(pam);
		printf("Would you like to add another airport? (1 - Yes, other - No)\n");
		scanf_s("%d", &p);
	}
	
	char menu[L_1024] = "Please pick one:\n";
	char* pmenu = menu;
	strcat(menu, "1. Add flight\n");
	strcat(menu, "2. Add Airport\n");
	strcat(menu, "3. Print Airline\n");
	strcat(menu, "4. Print Airline Manager\n");
	strcat(menu, "5. Print Number Of Flight From Location\n");
	strcat(menu, "6. Print Flights With Airplane Code\n");
	strcat(menu, "7. Print Flights With Airplane Type\n");
	strcat(menu, "8. Exit\n");
	strcat(menu, "============================================\n");
	strcat(menu, "\n");

		
	printf("\nWelcome, ");
	do
	{
		printf(	"%s", menu);

		scanf_s("%d", &p);
		clearBuffer();
		switch (p)
		{
		case 1: f_addFlight(pam, pai); break;
		case 2: f_addAirport(pam);  break;
		case 3: f_printAirline(pai); break;
		case 4: f_printAirlineManager(pam);  break;
		case 5: f_printNumberOfFlightFromLocation(pai); break;
		case 6: f_printFlightsWithAirplaneCode(pai); break;
		case 7: f_printFlightsWithAirplaneType(pai); break;
		case 321: f_calculateSizes(); break;
		case 8: break;
		default: printf("Pick a number between 1-8!\n\n"); break;
		}
		printf("\n");
		// clearBuffer(); // when returning from function - promising the empty buffer
	} while (p != 8);
	printf("Goodbye\n");

	return 0;
}

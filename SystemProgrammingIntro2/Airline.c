
#include <string.h>
#include "functionsLib.h"
#include "Airline.h"

<<<<<<< Updated upstream
=======
Airline* initAirline()
{
	int flag = 0;
	Airline* pai = malloc(sizeof(Airline));//should be casting before malloc?
	
	if (!pai)
	{
		printError();
		return 0;
	}
	char* name = NULL;
	do 
	{
		char* name = inputWithMessage("Insert Ailine name please: \n");
		printf("this is the saved name: %s\n", name);
		if (!name) {
			printf("Error: cannot assign memory.\n");
			free(pai);
			
		}
		trim(&name);

		if (strlen(name) == 0) {
			flag = 1;
			printf("Error: Name cannot be empty.\n");
			free(pai);
		}
	} while (flag != 0);
	
	pai->numOfFlights = 0;
	pai->name = name;

	return pai;
}

>>>>>>> Stashed changes
int addFlight(Airline *pai, Flight *pf)
{
	int max = pai->numOfFlights;
	if (max < MAX_FLIGHTS)
	{
		(pai->flights)[max] = pf;
		pai->numOfFlights = max + 1;
		return 0;
	}
	printf("Error: Airline flights has reached to limit.\n");
	return 0;
}
void doPrintFlightsWithPlaneCode(const Airline *pai, const char code[L_CODE])
{
	int flag = 0;
	for (int i = 0; i < pai->numOfFlights; i++)
	{
		Flight* pf = pai->flights[i];
		Airplane a1 = (pai->flights[i])->airplane;

		if (strcmp(a1.code, code) == 0)
		{
			doPrintFlight(pf);
			if (!flag) flag = 1;
		}
	}
	if (!flag)
	{
		printf("There are currently no flight planned with the given code.\n");
	}
}
void doPrintFlightsWithPlaneType(const Airline *pai, const AirplaneType type)
{

}
int doCountFlightsFromName(const Airline *pai, const char name[L_255])
{
	int count = 0;
	int max = pai->numOfFlights;
	for (int i = 0; i < max; i++)
	{
		Flight* pf = (pai->flights)[i];
		count += isFlightFromSourceName(pf, name);
	}
	return count;
}

void doPrintFlight(const Flight *pf)
{
	printf("Flight with airplane %s, type ", (pf->airplane).code);
	switch ((pf->airplane).type)
	{
	case PASSENGERS:printf("Passengers"); break;
	case CONTAINER: printf("Container"); break;
	case MILITARY: printf("Military"); break;
	default: break;
	}
	printf("\n");
	printf("From: %s\n", (pf->from).name);
	printf("To: %s\n", (pf->to).name);
	printf("On date: %d/%d/%d\n", (pf->date).day, (pf->date).month, (pf->date).year);
}
void doPrintAirline(const Airline *pai)
{
	int max = pai->numOfFlights;
	printf("Airport Name: %s\n", pai->name);
	
	for (int i = 0; i < max; i++)
	{
		printf("%d - ", i);
		Flight* pf = (pai->flights)[i];
		doPrintFlight(pf);
	}
	printf("\nTotal num of flights: %d", pai->numOfFlights);
	printf("\n---------------------------------\n");
}

void freeAirline(Airline* pai)
{
	free(pai);
}
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "functionsLib.h"

void printError()
{
	printf("Error: cannot assign memory.");
}

void clearBuffer() 
{
	char c;
	while ((c = getchar()) != '\n' && c != EOF) {}
}

char* inputDate()
{
	char* date = calloc(L_255, 1);
	date = inputWithMessage("Insert a Date in dd$$mm%%yyyy format: ");
	int isValid = isStringDateValid(&date);
	if (date)
	{
		if (isValid)
		{
			return date;
		}
		else
		{
			free(date);
			return EMPTY;
		}
	}
	
	return NULL;
}

char* addressReqs[4] = {"Country", "City", "Street", "Number"};

char* inputAddress()
{
	char *pAddress[4];

	char* all = calloc(L_1024, 1);
	if (all) 
	{
		for (int i = 0; i < 4; i++)
		{
			printf("Insert %s please: ", addressReqs[i]);
			pAddress[i] = input();
			if (pAddress[i]) 
			{
				trim(&pAddress[i]);
				strip(&pAddress[i]);
				capitalize(&pAddress[i]);
				capitalizeWordAlternatively(&pAddress[i]);
				replaceSpaceWithHashtag(&pAddress[i]);
				strcat(all, pAddress[i]);
				if (i != 3)
					strcat(all, " ");
			}
			else
			{
				printf("Memory is full. Error assigning more memory.");
				return NULL;
			}
			
		}
		replaceSpaceWithAtSign(&all);
		printf("this is the address being inserted: %s\n", all);
		return all;
	}
	return NULL;
	
}

const int maxDays[L_MONTHS] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int isStringDateValid(char* *pd)
{
	char temp[L_255];
	strcpy(temp, (char *)(*pd));
	int isLengthValid = strlen(temp) == 12;
	if (!isLengthValid) return 0;
	char* day = strtok(temp, "$$");
	char* month = strtok(NULL, "$$");
	char* year = strtok(NULL, "$$");

	Month m = atoi(month) - 1;
	unsigned int isDayValid = isDayInMonth(atoi(day), m);
	unsigned int isMonthValid = isMonthInCalendar(atoi(month));
	unsigned int isYearValid = isYearFromCurrent(atoi(year));
	return isDayValid && isMonthValid && isYearValid;
}

int isYearFromCurrent(int year)
{
	return year >= YEAR;
}

int isMonthInCalendar(int month)
{
	return month > 0 && month <= L_MONTHS;
}

int isDayInMonth(int day, Month month)
{
	return day > 0 && day <= maxDays[month];
}


int isupper(char c)
{
	return c >= 'A' && c <= 'Z';
}

int islower(char c)
{
	return c >= 'a' && c <= 'z';
}

int toupper(char c)
{
	return c - 32;
}
int tolower(char c)
{
	return c + 32;
}


void trim(char* *theWord)
{
	int white_start = 0; 
	int white_end = 0;
	int size = 0;

	for (int i = 0; ((char *)*theWord)[i]; i++) 
	{
		size++;
	}

	for (int i = 0; ((char *)*theWord)[i] && ((char *)*theWord)[i] == ' '; i++)
	{
		white_start++;
	}
	for (int i = size -1 ; i >=0 && ((char *)*theWord)[i] == ' '; i--)
	{
		white_end++;
	}

	((char *)*theWord)[size-white_end] = 0;
	(char *)*theWord += white_start;
}

void strip(char* *theWord) // by copying and pasting 
{
	int flag = 0; // indicates one space
	int size = 0;

	for (int i = 0; ((char *)*theWord)[i]; i++)
	{
		size++;
	}
	int i = 0; // copy position
	int index = 0; // pasting position
	while (((char *)*theWord)[i])
	{
		int isSpace = ((char *)*theWord)[i] == ' ';
	   	if (isSpace && !flag)
		{
			flag = 1; // found a space
			((char *)*theWord)[index] = ((char *)*theWord)[i]; // copy space
			index++;
		}
		else if ( !isSpace )
		{
			((char *)*theWord)[index] = ((char *)*theWord)[i]; // copy from i position to ind position
			index++;
		}
		if (!isSpace && flag) flag = 0; 
		
		i++;
	}
	((char *)*theWord)[index] = 0;
}

void capitalize(char* *theWord)
{
	char* newWord = calloc(strlen(*theWord), 1);
	if (!newWord) { printError(); return; }
	char* word = strtok((char *)(*theWord), " ");
	char* temp = word;
	char firstLetter;
	while (word != NULL)
	{
		strcpy(temp, word);
		word = strtok(NULL, " ");
		if (word == NULL)
		{ // temp has the last word
			firstLetter = temp[0];
			if (isupper(firstLetter))
				temp[0] = tolower(firstLetter);
		}
		else
		{ // there is another word
			firstLetter = temp[0];
			if (islower(firstLetter))
				temp[0] = toupper(firstLetter);
		}
		strcat(newWord, temp);
		if ( word != NULL )
			strcat(newWord, " ");
	}
	strcpy((char *)(*theWord), newWord);
}

void replaceSpaceWithChar(char* *theWord, const char c)
{
	for (int i = 0; (*theWord)[i]; i++)
	{
		if ((*theWord)[i] == ' ')
		{
			(*theWord)[i] = c;
		}
	}
}

// assuming the word is already stripped and trimmed
void capitalizeWordAlternatively(char* *theWord)
{
	int numOfWords = 1;
	for (unsigned int i = 0; i < strlen((char *)(*theWord)); i++)
	{
		if (((char *)(*theWord))[i] == ' ')
		{
			numOfWords++;
		}
	}
	if (numOfWords > 1)
	{
		char* newWord = calloc(strlen(*theWord), 1);
		if (!newWord) { printError(); return; }
		char* word = strtok((char *)(*theWord), " ");
		int sizeOfWord = 0;
		while (word != NULL)
		{
			sizeOfWord = strlen(word);
			if (sizeOfWord % 2 == 0)
			{
				for (int i = 0; i < sizeOfWord; i++)
				{
					if (i % 2 == 0) 
					{
						if (islower(word[i]))word[i] = toupper(word[i]);
					}
					else
					{
						if (isupper(word[i]))word[i] = tolower(word[i]);
					}
				}
			}
			strcat(newWord, word);
			word = strtok(NULL, " ");
			if (word != NULL)
				strcat(newWord, " ");
		}
		strcpy((char *)(*theWord), newWord);
	}
}

void replaceSpaceWithHashtag(char* *theWord)
{
	char c = '#';
	replaceSpaceWithChar(theWord, c);
}

void replaceSpaceWithAtSign(char* *theWord)
{
	char c = '@';
	replaceSpaceWithChar(theWord, c);
}

char* inputWithMessage(char* msg)
{
	printf("%s\n", msg);
	return input();
}


char* input()
{
	char* str = calloc(L_255, 1);
	if (str != NULL )
	{
		if (fgets(str, L_255, stdin))
		{
			str[strcspn(str, "\n")] = 0;
			return str;
		}
		*str = '\0';
	}
	return NULL;
}

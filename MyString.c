/**
 * @file MyString.c
 * @author  Idan Refaeli <idan.refaeli@mail.huji.ac.il>
 * @version 1.0
 * @date 04 Aug 2015
 *
 * @brief Program that counts the number of instances of a string in other string.
 *
 * @section LICENSE
 * This program is a free software
 *
 * @section DESCRIPTION
 * The program counts the instances of str2 in str1, depends on isCyclic.
 * Input  : strings str1, str2, int isCyclic.
 * Process: Counting the number of instances of str2 in str1. If isCyclic = 1, the search for str2
 * 			in str1 will be cyclic.
 * Output : The number of instances of str2 in str1.
 */

// ------------------------------ includes ------------------------------
#include <stdio.h>
#include "MyString.h"

// ------------------------------ functions -----------------------------
/**
 * @brief The main function. Asks for 2 strings str1 and str2 and call countSubStr to check the
 * 		  amount of times str2 is a substring of str1. Asks also for isCyclic in order to determine
 * 		  to check for cyclic appearance.
 * @return 0 to stop the process.
 */
int main ()
{
	char str1[50] = {0}, str2[50] = {0};
	int isCyclic;
	printf("Enter in the next format: <str1> <str2> <isCyclic>");
	scanf("%s %s %d", &str1, &str2, &isCyclic);
	int num = countSubStr(str1, str2, isCyclic);
	printf("%s, %s\n", str1, str2);
	printf("%d", num);
	return 0;
}

/**
 * @brief Check if the string str2 is substring of str1 in the current location of str1 given
 * 		  (where currentCharStr1 is pointing).
 * @param currentCharStr1 - pointer to the current char of str1 from the loop of countSubStr.
 * 							This char should be the same as the first char of str2.
 * @param str1 - The string
 * @param str2 - The substring
 * @return 1 if str2 is substring of str1 in the given location, 0 otherwise.
 */
static int checkSequence(const char* currentCharStr1, const char* str1, const char* str2,
						 int isCyclic)
{
	// The first char of str2 and currentCharStr1 are the same, so continue to check from the
	// second char of str2 and currentCharStr1 + 1.
	const char *currentCharStr2 = str2 + 1;
	currentCharStr1++;

	while (*currentCharStr1 == *currentCharStr2 && *currentCharStr2 !='\0')
	{
		// As long as the current chars are the same, continue to the next chars.
		currentCharStr1++;
		currentCharStr2++;

		// Only if isCyclic = 1 and current char of str1 reached the end of str1, make
		// currentCharStr1 as the first char of str1.
		if(isCyclic && *currentCharStr1 == '\0')
		{
			currentCharStr1 = str1;
		}
	}

	// If currentCharStr2 == '\0', means str2 is indeed a substring of str1, so return 1.
	// Otherwise, return 0.
	if (*currentCharStr2 == '\0')
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

unsigned int countSubStr(const char* str1, const char* str2, int isCyclic)
{
	const char *currentCharStr1 = str1;
	unsigned int counter = 0, match = 0;

	while(*currentCharStr1 != '\0')
	{
		// For each char of str1, check if it is the same as the first char of str2.
		// If so, check if str2 is a substring of str1 where currentCharStr1 is currently pointing
		// using checkSequence.
		if (*currentCharStr1 == *str2)
		{
			match = checkSequence(currentCharStr1, str1, str2, isCyclic);

			// If match = 1, means str2 is a substring of str1 where currentCharStr1 is currently
			// pointing, so increase the counter.
			if (match)
			{
				counter++;
			}
		}

		currentCharStr1++;
	}

	return counter;
}

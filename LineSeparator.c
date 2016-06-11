/**
 * @file LineSeperator.c
 * @author  Idan Refaeli <idan.refaeli@mail.huji.ac.il>
 * @version 1.0
 * @date 03 Aug 2015
 * 
 * @brief Perceptron program. Flagging given data by 1 or -1 using linear separator.
 *
 * @section LICENSE
 * This program is a free software
 *
 * @section DESCRIPTION
 * The program gets a series of vectors, where the first of them are practice vectors. Using the
 * practice vectors it calculates the separate vector and then use it to flag the other remaining
 * vectors.
 * 
 * Input  : File containing practice vectors, vectors to flag, the dimension of the vector space
 * 			and number of practice vectors.
 * Process: The program calculates the separate vector and use it to flag the vectors to flag.
 * Output : The flags of the vectors.
 */

// ------------------------------ includes ------------------------------
#include "LineSeparator.h"

// ------------------------------ functions -----------------------------

/**
 * @brief The main function. Runs the perceptron using the other functions.
 * @param argc - Number of given command argumants. Should be 1.
 * @param argv[] - Command argumants. Should contain the data file name.
 * @return 0 to tell the process to end.
 */
int main (int argc, char* argv[])
{
	unsigned int dimension = 0, numOfPracticeVectors = 0;

	// Check if the number of given command arguments is correct.
	if (argc != NUM_OF_ARGUMENTS)
	{
		printf("Usage: LinSeperator <input file>");
		return 1;
	}

	// Try to open the file and check if the file opened properly.
	FILE* data = fopen(argv[FILE_ARGUMENT], "r");
	if (!data)
	{
		printf("Unable to open input file: %s", argv[FILE_ARGUMENT]);
		return 1;
	}

	// Get the dimension of the vector space and the number of practice vectors from the data file.
	dimension = getInfo(data);
	numOfPracticeVectors = getInfo(data);

	// Create the separate Vector and calculate it.
	Vector separateVector = { {0}, 0};
	getSeperateVector(data, dimension, numOfPracticeVectors, &separateVector);

	// Flag each vector from the given data file and print the flag.
	flagVectors(data, dimension, &separateVector);

	// Close the file
	fclose(data);

	return 0;
}

unsigned int getInfo(FILE* data)
{
	// Use fgets to take the next line on file and put it in buff, and convert to int using atoi.
	char buff[MAX_MUM_OF_CHARS_IN_LINE] = {'0'};
	fgets(buff, MAX_MUM_OF_CHARS_IN_LINE, data);
	const int info = atoi(buff);
	return info;
}

int getVector(FILE* data, const unsigned int dimension, Vector* vector)
{
	assert(dimension > 0); //Proceed only when the dimension is legal.
	char buff[MAX_MUM_OF_CHARS_IN_LINE];
	char *token = NULL;
	unsigned int i;

	// If all vectors read from file, return 0.
	if (fgets(buff, MAX_MUM_OF_CHARS_IN_LINE, data) == NULL)
	{
		return 0;
	}

	// Take all the coordinates separated by commas, convert to double using atof and put them
	// the _vector array of the Vector struct.
	token = strtok(buff, COMMA);
	for (i = 0; i < dimension; i++)
	{
		vector -> _vector[i] = atof(token);
		token = strtok(NULL, COMMA);
	}

	// If the last token is not null, means there is a flag, means this is a practice vector.
	if (token != NULL)
	{
		vector -> _flag = atof(token);
	}

	return 1;
}

void getSeperateVector(FILE* data, const unsigned int dimension,
					   const unsigned int numOfPracticeVectors, Vector* separateVector)
{
	Vector currentPracticeVector = { {0}, 0};
	unsigned int i;
	int flag = 0;
	double product = 0;

	for (i = 0; i < numOfPracticeVectors; i++)
	{
		// For each practice vector, calculate its inner product with the current separate vector.
		// If the product is negative or zero, flag it with -1, otherwise flag it with 1/
		getVector(data, dimension, &currentPracticeVector);
		product = innerProduct(separateVector, &currentPracticeVector, dimension);
		if (product < INNER_PRODUCT_ACCURACY)
		{
			flag = NEGATIVE_FLAG;
		}
		else
		{
			flag = POSITIVE_FLAG;
		}

		// If the calculated flag is not the same as the given flag, update the separate vector
		// using the formula for updating given.
		if (flag != currentPracticeVector._flag)
		{
			scalarMultiply(&currentPracticeVector, (double)currentPracticeVector._flag, dimension);
			addVectors(separateVector, &currentPracticeVector, dimension);
		}
	}
}

void flagVectors(FILE* data, const unsigned int dimension, Vector* separateVector)
{
	Vector currentVector = { {0}, 0};
	double product = 0.0;

	while (getVector(data, dimension, &currentVector))
	{
		// While there are still vectors to flag on the data file, calculate their inner product
		// with the separate vector. If the product is negative or zero, flag them with -1,
		// otherwise flag them with 1.
		product = innerProduct(separateVector, &currentVector, dimension);
		if (product < INNER_PRODUCT_ACCURACY)
		{
			currentVector._flag = NEGATIVE_FLAG;
		}
		else
		{
			currentVector._flag = POSITIVE_FLAG;
		}

		printf("%d\n", currentVector._flag);
	}
}

double innerProduct(const Vector* v1, const Vector* v2, const unsigned int dimension)
{
	unsigned int i;
	double product = 0.0;
	for (i = 0; i < dimension; i++)
	{
		// Calculate the inner product using the inner product formula.
		product += (v1 -> _vector[i])*(v2 -> _vector[i]);
	}

	return product;
}

void scalarMultiply(Vector* v1, const double scalar, const unsigned int dimension)
{
	unsigned int i;

	for (i = 0; i < dimension; i++)
	{
		// Multiply by scalar according scalar multiply rule.
		v1 -> _vector[i] *= scalar;
	}
}

void addVectors(Vector* v1, const Vector* v2, const unsigned int dimension)
{
	unsigned int i;

	for (i = 0; i < dimension; i++)
	{
		// Add the 2 vectors according adding vectors rule.
		v1 -> _vector[i] += v2 -> _vector[i];
	}
}

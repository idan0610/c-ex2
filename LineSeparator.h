/**
 * @file LineSeperator.h
 * @author  Idan Refaeli <idan.refaeli@mail.huji.ac.il>
 * @version 1.0
 * @date 03 Aug 2015
 * 
 * @brief Perceptron program. Flagging given data by 1 or -1 using linear separator.
 * 		  Header file for perceptron.c.
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
#ifndef LINESEPARATOR_H_
#define LINESEPARATOR_H_

// ------------------------------ includes ------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// -------------------------- const definitions -------------------------
#define NUM_OF_ARGUMENTS 2
#define FILE_ARGUMENT 1
#define MAX_MUM_OF_CHARS_IN_LINE 150
#define MAX_DIMENSION 75
#define POSITIVE_FLAG 1
#define NEGATIVE_FLAG -1
#define INNER_PRODUCT_ACCURACY 0.00001
const char COMMA[2] = ",";

// -------------------------- structs -----------------------------------
/**
 * @brief struct representing a vector.
 */
typedef struct Vector
{
	double _vector[MAX_DIMENSION]; // The vector's coordinates
	int _flag; // The flag of the vector (-1 or 1)
} Vector;

// ------------------------------ functions -----------------------------

/**
 * @brief Used to get the dimension of the vector space and the number of practice vectors from
 * 		  the given file.
 * @param data - The file containing the data about the vectors.
 * @return The dimension of the vector space.
 */
unsigned int getInfo(FILE* data);

/**
 * @brief Get the next vector from the given data file and put it inside the given pointer's vector
 * 		  given.
 * @param data - The file containing the data about the vectors.
 * @param dimension - The dimension of the vector space.
 * @param vector - pointer to the vector that will contain the new vector from the file.
 * @return 1 if the operation succeeded, 0 if no more vectors left in the data file.
 */
int getVector(FILE* data, const unsigned int dimension, Vector* vector);

/**
 * @brief Calculating the separating vector of the perceptron and putting it inside the given
 * 		  pointer's vector.
 * @param data - The file containing the data about the vectors.
 * @param dimension - The dimension of the vector space.
 * @param numOfPracticeVectors - Number of practice vectors.
 * @param separateVector - pointer to the vector that will be the separate vector.
 * @return The separate vector.
 */
void getSeperateVector(FILE* data, const unsigned int dimension,
					   const unsigned int numOfPracticeVectors, Vector* separateVector);

/**
 * @brief Used to flag all the vectors from the data file with the calculated separate vector.
 * @param data - The file containing the data about the vectors.
 * @param dimension - The dimension of the vector space.
 * @param separateVector - pointer to the separate vector.
 */
void flagVectors(FILE* data, const unsigned int dimension, Vector* separateVector);

/**
 * @brief Calculate and return the inner product of the 2 given vectors.
 * @param v1 - pointer to the first vector
 * @param v2 - pointer to the second vector
 * @param dimension - The dimension of the vector space.
 * @return The inner product.
 */
double innerProduct(const Vector* v1, const Vector* v2, const unsigned int dimension);

/**
 * @brief Multiplying the given scalar and given vector and save the answer in the given vector
 * @param v1 - The vector
 * @param scalar - The scalar
 * @param dimension - The dimension of the vector space.
 */
void scalarMultiply(Vector* v1, const double scalar, const unsigned int dimension);

/**
 * @brief Adding 2 given vectors and save the answer in the first given vector.
 * @param v1 - The first vector.
 * @param v2 - The second vector.
 * @param dimension - The dimension of the vector space.
 */
void addVectors(Vector* v1, const Vector* v2, const unsigned int dimension);

#endif /* LINESEPARATOR_H_ */

/*
 * mainTest.h
 *
 *  Created on: 27 oct. 2017
 *      Author: dene2303
 */

#ifndef INCLUDES_MAINTEST_H_
#define INCLUDES_MAINTEST_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "mainTest.h"
#include "main_accordeur.h"
#include "genCos.h"
#include "findErrAccordage.h"
#include "CONSTANTES.h"

typedef enum{PASS, FAIL} Success;

typedef struct{
    Success passed;
    char *test;
    char *message;
} TestResult;

float generateRandomFloat(double min, double max);
void generateRandomSignalValues(float* signal, short length);

void printValuesTxtFile(float* values, short length, char* filePathName);

/*
 * Test procedures
 */
TestResult sampleTest(void);

// Test pure cosine functions
TestResult verifyCosFunction(float (*cosFunction)(float));
TestResult testCosTable(void);
TestResult testCosTaylor(void);

// Sin Signal generation tests
TestResult testGenCosTable(void);
TestResult testGenCosTaylor(void);
TestResult testGenCosDiff(void);
TestResult testGenCosRotate(void);


TestResult testprintValuesTxtFile(void);
//TestResult testFaireAutocorr_fft(void);


// Add test procedures to this array to execute them
TestResult (*testRoutines[]) (void) = {
    sampleTest,
    testCosTable,
    testCosTaylor,
    testprintValuesTxtFile,
    testGenCosTable
    //testFaireAutocorr_fft
};

#endif /* INCLUDES_MAINTEST_H_ */

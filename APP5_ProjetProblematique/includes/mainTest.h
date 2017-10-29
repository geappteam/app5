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

TestResult testGenCos(void);
TestResult verifyCosFunction(float (*cosFunction)(float));
TestResult testCosTable(void);
TestResult testCosTaylor(void);
TestResult sampleTest(void);
TestResult testprintValuesTxtFile(void);
//TestResult testFaireAutocorr_fft(void);


TestResult (*testRoutines[]) (void) = {
    sampleTest,
    testGenCos,
    testCosTable,
    testCosTaylor,
    testprintValuesTxtFile,
    //testFaireAutocorr_fft
};


#endif /* INCLUDES_MAINTEST_H_ */

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


TestResult testCos(void);
TestResult sampleTest(void);
TestResult testFaireAutocorr_fft(void);


TestResult (*testRoutines[]) (void) = {
    testCos,
    sampleTest,
    testFaireAutocorr_fft
};


#endif /* INCLUDES_MAINTEST_H_ */

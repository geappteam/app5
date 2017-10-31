/*
 * mainTest.c
 *
 *  Created on: 27 oct. 2017
 *      Author: dene2303
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "main_accordeur.h"
#include "mainTest.h"
#include "genCos.h"
#include "findErrAccordage.h"
#include "CONSTANTES.h"
#include "filtreFIR.h"
#include "mainTest.h"
#include "coeffsFIR.dat"

extern float DeltaAngle[6];

#ifdef TEST_BUILD
void main(){

    int nbOfTests = sizeof(testRoutines)/sizeof(TestResult (*) (void));
    printf("Starting %d tests\r\n", nbOfTests);


    int nbPassed = 0;
    int nbFailed = 0;
    int i;
    for(i = 0; i < nbOfTests; ++i) {

        TestResult result = (*testRoutines[i])();

        printf("\r\nTest #%d %s : ", i+1, result.test);

        if(result.passed == PASS) {
            printf("Passed\r\n");
            ++nbPassed;
        }
        else {
            printf("Failed\r\n");
            ++nbFailed;
        }

        printf("%s\r\n", result.message);

    }

    printf("\r\nEnd of tests: %d passed, %d failed\r\n\r\n", nbPassed, nbFailed);

    exit(0);
}
#endif

float generateRandomFloat(double min, double max){
    srand(time(NULL));
    return (rand()/(double)RAND_MAX)*(max-min)+min;
}

void generateRandomSignalValues(float* signal, short length){
    float value;
    int i;
    for(i = 0; i<length; i++)
        value = generateRandomFloat(MIN_SIG_MAG, MAX_SIG_MAG);
        signal[i] = value;
}

void printValuesTxtFile(float* values, short length, char* filePathName){
    FILE *f = fopen(filePathName, "w");
    if (f == NULL){
        printf("Error opening file!\n");
        return ;
    }

    int i;

    for(i = 0 ; i < length ; ++i)
        fprintf(f, "%f\r\n", values[i]);

    fclose(f);
}


TestResult verifyCosFunction(float (*cosFunction)(float)){

    TestResult res = {
        PASS,
        "Cosine function test",
        NULL
    };

    const float tolerance = 0.1;

    float in_angles[] = {0, PI/6, PI/3, PI/4, PI/2, 3*PI/4, 5*PI/4, 7*PI/4, 2*PI};
    float out_expected[sizeof(in_angles)/sizeof(float)];
    float out_cos[sizeof(in_angles)/sizeof(float)];

    int i;
    for (i = 0; i < sizeof(in_angles)/sizeof(float); ++i){
        out_expected[i] = cos(in_angles[i]);
        out_cos[i] = cosFunction(in_angles[i]);

        if(fabs(out_cos[i] - out_expected[i]) > tolerance)
            res.passed = FAIL;
    }

    char *message = (char*)malloc(sizeof(out_cos)/sizeof(float) * sizeof(char) * 48);
    memset(message, '\0', sizeof(message));

    for(i = 0; i < sizeof(out_cos)/sizeof(float); ++i) {
        char line[48]={'\0'};
        snprintf(line, sizeof(line), "\tcos( %.4f ) = %.4f (%.4f)\r\n", in_angles[i], out_cos[i], out_expected[i]);
        strncat(message, line, sizeof(line));
    }

    res.message = message;

    return res;
}

TestResult testCosTable() {
    TestResult res = verifyCosFunction(cosTable);

    res.test = "Table Cosine function";

    return res;
}

TestResult testCosTaylor() {
    TestResult res = verifyCosFunction(cosTaylor);

    res.test = "Taylor Series Cosine function";

    return res;
}

TestResult sampleTest(){
    TestResult res = {
        PASS,
        "Sample Test Name",
        "Test result description."
    };
    return res;
}

TestResult testprintValuesTxtFile(){
    TestResult res = {
        FAIL,
        "testprintValuesTxtFile",
        "Test if the function properly print values in a txt file."
    };

    float values[] = {1.00, 4.60, 558.323, 32.9201};
    printValuesTxtFile(values, sizeof(values)/sizeof(float), "test.txt");

    return res;
}

TestResult testFaireAutocorr_fft(){
    TestResult res = {
        FAIL,
        "faireAutocorr_fft",
        " Test the autocorrelation implemented in C.\n Export a 'txt' file to compare algorithms in Matlab."
    };

    // Buffer samples initialized
    float samples[L_TAMPON];
    generateRandomSignalValues(samples, L_TAMPON);

    // Print values used for autocorrelation for Matlab
    printValuesTxtFile(samples, L_TAMPON, "../Matlab/pre_autocorrelation_values_C.txt");

    // Hanning window applied
//    int i;
//    for (i=0;i<L_TAMPON;i++) {
//        samples[i] = FENETRE_HAN[i]*samples[i]; //TODO: DEBUG
//    }

    //Function tested
    float autocorr[L_TAMPON];
    faireAutocorr_fft(samples, autocorr);

    // Print results for Matlab comparisons
    printValuesTxtFile(autocorr, L_TAMPON, "../Matlab/autocorrelation_results_C.txt");

    return res;
}


TestResult testGenCosTab(void){
    TestResult res = {
       PASS,
       "Cosine Discrete signal from Table",
       "\tSignal corresponds"
    };

    char *message = (char*)malloc(64);
    memset(message, '\0', 64);

    const float tolerance = 0.1f;
    const int nbSamples = 512;

    int corde = 0;

    // Creating a signal for every string
    for (corde = 0; corde < 6; ++corde) {

        float angleR = 0;
        float angleT = 0;

        int s;
        for (s = 0; s < nbSamples; ++s){
            float expected = genCos(DeltaAngle[corde], &angleR);
            float result = genCosTab(DeltaAngle[corde], &angleT);

            if (fabs(result-expected) > tolerance) {
                res.passed = FAIL;
                snprintf(message, 64, "Failed to generate sample %d of string %d", s, corde);
                res.message = message;
                return res;
            }
        }
    }

    return res;
}

TestResult testGenCosTaylor(void){
    TestResult res = {
       PASS,
       "Cosine Discrete signal from Taylor Series",
       "\tSignal corresponds"
    };

    char *message = (char*)malloc(64);
    memset(message, '\0', 64);

    const float tolerance = 0.05f;
    const int nbSamples = 512;

    int corde = 0;

    // Creating a signal for every string
    for (corde = 0; corde < 6; ++corde) {

        float angleR = 0;
        float angleT = 0;

        int s;
        for (s = 0; s < nbSamples; ++s){
            float expected = genCos(DeltaAngle[corde], &angleR);
            float result = genCosTaylor(DeltaAngle[corde], &angleT);

            if (fabs(result-expected) > tolerance) {
                res.passed = FAIL;
                snprintf(message, 64, "Failed to generate sample %d of string %d", s, corde);
                res.message = message;
                return res;
            }
        }
    }

    return res;
}

TestResult testGenCosDiff(void){
    TestResult res = {
       PASS,
       "Cosine Discrete signal from Difference equation",
       "\tSignal corresponds"
    };

    char *message = (char*)malloc(64);
    memset(message, '\0', 64);

    const float tolerance = 0.5f;
    const int nbSamples = 512;

    int corde = 0;

    // Creating a signal for every string
    for (corde = 0; corde < 6; ++corde) {

        float angleR = 0;
        float expected;
        float result;

        int s;
        for (s = 0; s < nbSamples; ++s){
            expected = genCos(DeltaAngle[corde], &angleR);
            result = genCosDiff(corde);

            if (fabs(result-expected) > tolerance) {
                res.passed = FAIL;
                snprintf(message, 64, "Failed to generate sample %d of string %d", s, corde);
                res.message = message;
                return res;
            }
        }

        angleR = angleR+0;
    }

    return res;
}

TestResult testGenCosRotate(void){
    TestResult res = {
       PASS,
       "Cosine Discrete signal from Rotating vector algorithm",
       "\tSignal corresponds"
    };

    char *message = (char*)malloc(64);
    memset(message, '\0', 64);

    const float tolerance = 0.2f;
    const int nbSamples = 512;

    int corde = 0;

    // Creating a signal for every string
    for (corde = 0; corde < 6; ++corde) {

        float angleR = 0;
        float expected;
        float result;

        float compReel = 1.0f;
        float compImag = 0.0f;

        int s;
        for (s = 0; s < nbSamples; ++s){
            expected = genCos(DeltaAngle[corde], &angleR);
            result = genCosRotate(corde, &compReel, &compImag);

            if (fabs(result-expected) > tolerance) {
                res.passed = FAIL;
                snprintf(message, 64, "Failed to generate sample %d of string %d", s, corde);
                res.message = message;
                return res;
            }
        }

        angleR = angleR+0;
    }

    return res;
}

TestResult filtreC_FIR() {
    TestResult res = {
       PASS,
       "Optimized FIR filter in C",
       "\tSignals match"
    };

    short * sampleBuffer0  = (short*)memalign(128*sizeof(short), 128*sizeof(short));
    short * sampleBuffer1  = (short*)memalign(128*sizeof(short), 128*sizeof(short));

    memset(sampleBuffer0, 0, 128*sizeof(short));
    memset(sampleBuffer1, 0, 128*sizeof(short));

    short * cPtr0 = sampleBuffer0;
    short * cPtr1 = sampleBuffer1;

    srand(time(NULL));
    int i;
    for (i = 0; i < 1024; ++i)
    {
        short input = rand() - (RAND_MAX>>1);

        short out0;
        short out1;

        standardFIR(cPtr0, input, CoeffsFIR, FIRNbCOEFFS, sampleBuffer0, 128, &out0);
        hp_optimizedFIR(cPtr1, input, CoeffsFIR, FIRNbCOEFFS_FOLDED, sampleBuffer1, 128, &out1);

        if (*cPtr0 != *cPtr1) {
            res.message = "Failed to put input in circular buffer";
            res.passed = FAIL;
            return res;
        }

        if (out0 != out1) {
            res.message = "Filter gives different results";
            res.passed = FAIL;
            return res;
        }
    }

    free(sampleBuffer0);
    free(sampleBuffer1);

    return res;
}

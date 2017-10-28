/*
 * mainTest.c
 *
 *  Created on: 27 oct. 2017
 *      Author: dene2303
 */

#include "mainTest.h"

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


TestResult testCos(){
    TestResult res = {
        PASS,
        "Cosine function testCos()",
        "Test result description."
    };

    const float tolerance = 0.05;

    float in_angles[] = {0, PI/4, PI/2};
    float out_expected[] = {1, 0.70710678118, 0};
    float out_cos[sizeof(in_angles)/sizeof(float)];

    int i;
    for (i = 0; i < sizeof(in_angles)/sizeof(float); ++i){
        float anglePtr = 0;
        out_cos[i] = genCos(in_angles[i], &anglePtr);

        if(abs(out_cos[i] - out_expected[i]) > tolerance)
            res.passed = FAIL;
    }

    char *message = (char*)malloc(sizeof(out_cos)/sizeof(float) * sizeof(char) * 30);

    for(i = 0; i < sizeof(out_cos)/sizeof(float); ++i) {
        char line[30]={0};
        snprintf(line, 30, "\tcos( %.4f ) = %.4f\r\n", in_angles[i], out_expected[i]);
        strncat(message, line, 30);
    }

    res.message = message;

    return res;
}

TestResult testCosTable(){
    TestResult res = {
        PASS,
        "Table Cosine function",
        "\0"
    };

    const float tolerance = 0.05;

    float in_angles[] = {0, PI/4, PI/2};
    float out_expected[] = {1, 0.70710678118, 0};
    float out_cos[sizeof(in_angles)/sizeof(float)];

    int i;
    for (i = 0; i < sizeof(in_angles)/sizeof(float); ++i){
        out_cos[i] = cosTable(in_angles[i]);

        if(abs(out_cos[i] - out_expected[i]) > tolerance)
            res.passed = FAIL;
    }

    char *message = (char*)malloc(sizeof(out_cos)/sizeof(float) * sizeof(char) * 30);

    for(i = 0; i < sizeof(out_cos)/sizeof(float); ++i) {
        char line[30]={0};
        snprintf(line, 30, "\tcos( %.4f ) = %.4f\r\n", in_angles[i], out_expected[i]);
        strncat(message, line, 30);
    }

    res.message = message;

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

TestResult testFaireAutocorr_fft(){
    TestResult res = {
        FAIL,
        "faireAutocorr_fft",
        " Test the autocorrelation implemented in C.\n Export a 'txt' file to compare algorithms in Matlab."
    };

    // Buffer samples
    float samples[L_TAMPON];

    //TODO: LOAD MATLAB VALUES INSTEAD
    //...

    // Autocorrelation's results
    float autocorr[L_TAMPON];

    // Hanning window applied
    int i;
    for (i=0;i<L_TAMPON;i++) {
//        samples[i] = FENETRE_HAN[i]*samples[i]; //TODO: DEBUG
    }

    //Function tested
    faireAutocorr_fft(samples, autocorr);

    FILE *f = fopen("test_autocorrelation_results_C.txt", "w");
    if (f == NULL)
    {
        printf("Error opening file!\n");
        return res;
    }

    // Print in text file for Matlab
    for(i = 0 ; i < L_TAMPON ; ++i)
        fprintf(f, "%f\n", autocorr[i]);

    fclose(f);

    return res;
}

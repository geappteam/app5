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

    const float tolerance = 0.01;

    float in_angles[] = {0, PI/6, PI/3, PI/4, PI/2, 3*PI/4, 5*PI/4, 7*PI/4, 2*PI};
    float out_expected[sizeof(in_angles)/sizeof(float)];
    float out_cos[sizeof(in_angles)/sizeof(float)];

    int i;
    for (i = 0; i < sizeof(in_angles)/sizeof(float); ++i){
        out_expected[i] = cos(in_angles[i]);
        out_cos[i] = cosFunction(in_angles[i]);

        if(abs(out_cos[i] - out_expected[i]) > tolerance)
            res.passed = FAIL;
    }

    char *message = (char*)malloc(sizeof(out_cos)/sizeof(float) * sizeof(char) * 30);
    memset(message, '\0', sizeof(message));

    for(i = 0; i < sizeof(out_cos)/sizeof(float); ++i) {
        char line[30]={'\0'};
        snprintf(line, 30, "\tcos( %.4f ) = %.4f\r\n", in_angles[i], out_expected[i]);
        strncat(message, line, 30);
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


TestResult testGenCosTable(void){
    TestResult res = {
       PASS,
       "Cosine Discrete signal from Table",
       NULL
    };

    char message[256];
    memset(message, '\0', sizeof(message));

    float tolerance = 0.05f;

    float refSample[512];
    float testSample[sizeof(refSample)];

    int corde = 0;

    // Creating a signal for every string
    for (corde = 0; corde < sizeof(refSample); ++corde);

    res.message = message;
    return res;
}

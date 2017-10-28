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
    float angle = 1.0;
    genCos(1.0, &angle);

    TestResult res = {
        PASS,
        "Cosine function testCos()",
        "Test result description."
    };

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

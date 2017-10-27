/*
 * mainTest.h
 *
 *  Created on: 27 oct. 2017
 *      Author: dene2303
 */

#ifndef INCLUDES_MAINTEST_H_
#define INCLUDES_MAINTEST_H_


typedef enum{PASS, FAIL} Success;

typedef struct{
    Success passed;
    char test[32];
    char message[64];
} TestResult;

#endif /* INCLUDES_MAINTEST_H_ */

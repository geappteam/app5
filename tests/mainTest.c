/*
 * mainTest.c
 *
 *  Created on: 27 oct. 2017
 *      Author: dene2303
 */

#include <stdio.h>
#include "mainTest.h"
#include "main_accordeur.h"


#ifdef TEST_BUILD
void main(){

    printf("Starting tests\r\n");


}
#endif


TestResult testCos(){
    TestResult res;

    res.passed = PASS;

    return res;
}

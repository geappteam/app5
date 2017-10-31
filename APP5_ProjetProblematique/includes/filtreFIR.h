/*
 * filtreFIR.h
 *
 *  Created on: Oct 31, 2017
 *      Author: MoronixProduct3
 */

#ifndef SOURCE_C_FILTREFIR_H_
#define SOURCE_C_FILTREFIR_H_

// C functions
short* standardFIR(short *cPtr, short ech, const short coeffs[], short N, short tampon[], short L, short* y);
short* hp_optimizedFIR(short *cPtr, short ech, const short coeffsPlie[], short Nplie, short tampon[], short L, short* y);

// ASM function
short* hp_asmFIR(short *cPtr, short ech, const short coeffsPlie[], short Nplie, short tampon[], short L, short* y);

#endif /* SOURCE_C_FILTREFIR_H_ */

/*
 * filtreFIR.c
 *
 *  Created on: Oct 31, 2017
 *      Author: dene2303
 *
 *  This file provides the implementation of the original FIR filter along side an optimized version
 */

short* standardFIR(short *cPtr, short ech, const short coeffs[], short N, short tampon[], short L, short* y)
{
    int k;
    int out=0; // Doit être un int pour accepter le Q30
    short *p;

    /******************************************************************************
    Enregistrement du nouvel échantillon dans le tampon
    ******************************************************************************/
    cPtr++;
    if (cPtr == tampon+L) // Si adresse de l'éch. courant à la fin du tampon
        cPtr = tampon;
    *cPtr = ech;          // Enregistrement de l'éch. courant dans le tampon

    /******************************************************************************
    Filtrage du tampon par convolution
    ******************************************************************************/
    p = cPtr;
    for (k=0; k<N; k++) {    // Pour tous les échantillons du tampon
        // Convolution y[n] = sommation(h[k]x[n-k])
        out = out + coeffs[k] * (*p--);   // cette multiplication donne Q30

        if (p < tampon)   // Si l'adresse de l'éch. courant sortie du tampon
            p = tampon+L-1;    // Remettre l'adresse à la fin du tampon
    }

    *y = out >> 15; // décalage arithméthique à droite pour passer de Q30 à Q15

    return cPtr;
}

short* hp_optimizedFIR(short *cPtr, short ech, const short coeffsPlie[], short Nplie, short tampon[], short L, short* y)
{
    ++cPtr;                                 if (cPtr >= tampon+L) cPtr = tampon;
    *cPtr = ech;

    int sum = 0;

    short * tail = cPtr - 2*(Nplie-1);      if(tail < tampon) tail += L;
    short * head = cPtr;

    while (tail != head){
        sum += (*coeffsPlie++) * ((*tail++)+(*head--));

                                            if(tail >= tampon+L) tail -= L;
                                            if(head < tampon) head += L;
    }

    sum += (*coeffsPlie) * (*tail);

    *y = sum >> 15;

    return cPtr;
}

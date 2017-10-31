/*
 * filtreFIR.c
 *
 *  Created on: Oct 31, 2017
 *      Author: dene2303
 *
 *  This file provides the implementation of the original FIR filter along side an optimized version
 */

short standardFIR(short *cPtr, short ech, const short coeffs[], short N, short tampon[], short L)
{
    int k;
    int out=0; // Doit �tre un int pour accepter le Q30
    short *p;

    /******************************************************************************
    Enregistrement du nouvel �chantillon dans le tampon
    ******************************************************************************/
    cPtr++;
    if (cPtr == tampon+L) // Si adresse de l'�ch. courant � la fin du tampon
        cPtr = tampon;
    *cPtr = ech;          // Enregistrement de l'�ch. courant dans le tampon

    /******************************************************************************
    Filtrage du tampon par convolution
    ******************************************************************************/
    p = cPtr;
    for (k=0; k<N; k++) {    // Pour tous les �chantillons du tampon
        // Convolution y[n] = sommation(h[k]x[n-k])
        out = out + coeffs[k] * (*p--);   // cette multiplication donne Q30

        if (p < tampon)   // Si l'adresse de l'�ch. courant sortie du tampon
            p = tampon+L-1;    // Remettre l'adresse � la fin du tampon
    }

    return out >> 15; // d�calage arithm�thique � droite pour passer de Q30 � Q15
}

short hp_optimizedFIR(short *cPtr, short ech, const short coeffsPlie[], short Nplie, short tampon[], short L)
{
    ++cPtr;                                 if (cPtr >= tampon+L) cPtr = tampon;
    *cPtr = ech;

    int sum = 0;

    short * tail = cPtr - 2*(Nplie-1);      if(tail < tampon) tail += L;
    short * head = cPtr;

    while (tail != head){
        sum += (*coeffsPlie++) * ((*tail++)+(*head--));

                                            if(tail >= tampon+L) tail -= L;
                                            if(head < tampon) tail += L;
    }

    sum += (*coeffsPlie) * (*tail);

    return sum << 15;
}

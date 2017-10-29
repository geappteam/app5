/* genCos.c */
/*
  Cr�ateur:    Bruno Gagnon, M. Sc.A
  Date:        7 juin 2009
  Revisions:   

  DESCRIPTION : 
     Permet de g�n�rer un signal sinuso�dal en utilisant la 
     fonction cosinus de la librairie standard <math.h>

  ENTR�E : 
     deltaAngle : valeur de 2*PI*f/Fs

  ENTR�E/SORTIE :
	 angle_Ptr : Pointeur sur l'angle courant de la fonction cos. 
	             Normalement, ce pointeur doit pointer sur une variable 
	             statique ou globale.

  RETOUR : 
	 Amplitude de l'�chantillon courrant pour la g�n�ration du signal.
	 
*/

#include <stdio.h>
#include <math.h>
#include "CONSTANTES.h" // Constantes partag�es
#include "genCos.h"
#include "float.h"


float sinTable[16] = {
    1.0,
    0.995184726672197,
    0.980785280403230,
    0.956940335732209,
    0.923879532511287,
    0.881921264348355,
    0.831469612302545,
    0.773010453362737,
    0.707106781186548,
    0.634393284163646,
    0.555570233019602,
    0.471396736825998,
    0.382683432365090,
    0.290284677254462,
    0.195090322016128,
    0.098017140329561
};

float cosTaylorDenominators[8] = { // 1/(2n)!
    1.0,    // 1/0!
    0.5,
    0.041666666666667,
    0.001388888888889,
    2.480158730158730e-05,
    2.755731922398589e-07,
    2.087675698786810e-09,
    1.147074559772973e-11,  // 1/(2*7)!
};

float computeTaylorCos(float teta, int nbTerms);

/***********************************************************
 Permet de garder l'angle entre 0 et 2pi
***********************************************************/
void fixAngle(float *a_Ptr) {

	if (*a_Ptr >= 2*PI)
		*a_Ptr = *a_Ptr-2*PI;

	return;
}


float genCos(float deltaAngle, float *angle_Ptr) {

	float out; // �chantillon de sortie

	*angle_Ptr = ( *angle_Ptr + deltaAngle ); // calcul de l'angle de l'�ch. actuel
	fixAngle(angle_Ptr);		// permet de garder l'angle entre 0 et 2pi

	// Alternatives cosinus
	out = cos(*angle_Ptr);          // from math.h
	//out = cosTable(*angle_Ptr);     // from a precalculated table
	//out = cosTaylor(*angle_Ptr);    // from Taylor series
	//out = cosDiff(*angle_Ptr);      // from difference equation
	//out = cosRotate(*angle_Ptr);    // from rotating vector algorithm

	return out;
}


float cosTable (float angle) {

    int angIndex = (int) (angle * 32.0 / (PI + FLT_EPSILON));

    if (angIndex >= 48)
        return sinTable[63 - angIndex]; // Same as 15-(angIndex-48)
    else if (angIndex >= 32)
        return -sinTable[angIndex - 32];
    else if (angIndex >= 16)
        return -sinTable[31 - angIndex];
    else
        return sinTable[angIndex];
}

float cosTaylor (float angle) {

    // On utilise les trois premiers termes
    if (angle >= (3.0f/2.0f)*PI)
        return computeTaylorCos((2*PI)-angle, 3);
    if (angle >= PI)
        return -computeTaylorCos(angle-PI, 3);
    if (angle >= PI/2.0f)
        return -computeTaylorCos(PI-angle, 3);
    return computeTaylorCos(angle, 3);
}

float computeTaylorCos(float teta, int nbTerms) {
    // sum (-1)^n * (angle^(2*n))/((2*n)!) , where n=0 to +infinity

    float sum = cosTaylorDenominators[0];
    float angleSquare = teta*teta;
    float numerator = 1.0;

    int k;
    for(k = 1; k < nbTerms; ++k) {
        numerator *= -angleSquare;
        sum += numerator * cosTaylorDenominators[k];
    }

    return sum;
}

float cosDiff (float angle) {
    return 0;
}

float cosRotate (float angle) {
    return 0;
}
/* genCos.c */
/*
  Créateur:    Bruno Gagnon, M. Sc.A
  Date:        7 juin 2009
  Revisions:   

  DESCRIPTION : 
     Permet de générer un signal sinusoïdal en utilisant differents algorithmes

  ENTRÉE : 
     deltaAngle : valeur de 2*PI*f/Fs

  ENTRÉE/SORTIE :
	 angle_Ptr : Pointeur sur l'angle courant de la fonction cos. 
	             Normalement, ce pointeur doit pointer sur une variable 
	             statique ou globale.

  RETOUR : 
	 Amplitude de l'échantillon courrant pour la génération du signal.
	 
*/

#include <stdio.h>
#include <math.h>
#include "CONSTANTES.h" // Constantes partagées
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

float diffEquationParams[6][3] = {
    // {a1, y(n-1), y(n-2)}
    {1.9958124859719508f, 0.9979062429859754f, 0.9916337395807692f}, 
    {1.9925407526362018f, 0.9962703763181009f, 0.9851093254580207f}, 
    {1.9867156608163248f, 0.9933578304081624f, 0.9735195584664229f}, 
    {1.9763503104849738f, 0.9881751552424869f, 0.9529802748770261f}, 
    {1.9625020151779449f, 0.9812510075889724f, 0.9257070797887472f}, 
    {1.9333498938997629f, 0.9666749469498814f, 0.8689209061211122f}
};

float deltaRell[6] = {
    0.9979062429859754f,
    0.9962703763181009f,
    0.9933578304081624f,
    0.9881751552424869f,
    0.9812510075889724f,
    0.9666749469498814f
};

float deltaImag[6] = {
    0.0646771227685294f,
    0.0862863678166468f,
    0.115066158216865f,
    0.153329261921810f,
    0.192734169533133f,
    0.256006927522370f
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

	float out; // échantillon de sortie

	*angle_Ptr = ( *angle_Ptr + deltaAngle ); // calcul de l'angle de l'éch. actuel
	fixAngle(angle_Ptr);		// permet de garder l'angle entre 0 et 2pi

	out = cos(*angle_Ptr);          // from math.h

	return out;
}


// Generates similar output using a table of precalculated values
float genCosTab(float deltaAngle, float *angle_Ptr) {

    *angle_Ptr = (*angle_Ptr + deltaAngle);
    fixAngle(angle_Ptr);

    return cosTable(*angle_Ptr);
}

// Using Taylor Series
float genCosTaylor(float deltaAngle, float *angle_Ptr) {

    *angle_Ptr = (*angle_Ptr + deltaAngle);
    fixAngle(angle_Ptr);

    return cosTaylor(*angle_Ptr);
}


// Using a meta stable differrence equation
float genCosDiff(int corde) {
    
    static int lastCorde = -1;
    static float a1;
    static float yBuffer[2];

    if (corde != lastCorde) {
        lastCorde = corde;
        a1 = diffEquationParams[corde][0];
        yBuffer[0] = diffEquationParams[corde][1];
        yBuffer[1] = diffEquationParams[corde][2];
    }

    float nextSample = a1 * yBuffer[0] - yBuffer[1];

    yBuffer[1] = yBuffer[0];
    yBuffer[0] = nextSample;

    return nextSample;
}


// Using the rotating vector
float genCosRotate(int corde, float *reel_Ptr, float *imag_Ptr) {

    float nReel = deltaRell[corde] * *reel_Ptr - deltaImag[corde] * *imag_Ptr;
    float nImag = deltaRell[corde] * *imag_Ptr + deltaImag[corde] * *reel_Ptr;

    *reel_Ptr = nReel;
    *imag_Ptr = nImag;

    return nReel;
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

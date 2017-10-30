/* genCos.h */
/*
  Cr�ateur:    Bruno Gagnon, M. Sc.A
  Date:        7 juin 2009
  Revisions:   

  DESCRIPTION : 
     Permet de g�n�rer un signal sinuso�dal en utilisant la 
     fonction cosinus de la librairie standard <math.h>
*/


#ifndef GENCOS_H_
#define GENCOS_H_

#define PI 3.14159265358979f


/*************************************************************
 Liste des prototypes de fonction
*************************************************************/

// DESCRIPTION : G�n�ration de l'amplitude de l'�ch. � l'aide de la fonction cos de 
// la librairie standard <math.h>
float genCos(float deltaAngle, float *anglePtr);
float genCosTab(float deltaAngle, float *angle_Ptr);
float genCosTaylor(float deltaAngle, float *angle_Ptr);
float genCosDiff(int corde);
float genCosDiff(int corde, float *reel_Ptr, float *imag_Ptr);

// DESCRIPTION : Permet de garder l'angle entre 0 et 2pi
void fixAngle(float *a_ptr);

float cosTable (float angle);
float cosTaylor (float angle);
float cosDiff (float angle);
float cosRotate (float angle);

#endif /* GENCOS_H_ */

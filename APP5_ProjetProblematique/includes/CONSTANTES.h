/* Ce fichier contient quelques constantes d'intérêts qui sont partagées 
   par plusieurs fonctions */

#ifndef CONSTANTES_H_
#define CONSTANTES_H_

#ifndef NB_CYCLES_PAR_SEC
#define NB_CYCLES_PAR_SEC 225000000		// Nombre de cycles par secondes
#endif

#ifndef NB_CORDES
#define NB_CORDES 6		// Nombre de cordes de guitare
#endif

#ifndef L_TAMPON
#define L_TAMPON 256  	// Longueur du tampon circulaire d'échantillons
#endif

#ifndef FS
#define FS 8000			// Fréquence d'échantillonnage
//#define FS 7417			// Fréquence d'échantillonnage

#ifndef MIN_SIG_MAG
#define MIN_SIG_MAG 0.0     // Minimal practical value of signal assumed
#endif

#ifndef MAX_SIG_MAG
#define MAX_SIG_MAG 5.0     // Maximal practical value of signal assumed
#endif

#endif

#endif /* CONSTANTES_H_ */

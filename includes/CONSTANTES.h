/* Ce fichier contient quelques constantes d'int�r�ts qui sont partag�es 
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
#define L_TAMPON 256  	// Longueur du tampon circulaire d'�chantillons
#endif

#ifndef FS
#define FS 8000			// Fr�quence d'�chantillonnage
//#define FS 7417			// Fr�quence d'�chantillonnage

#ifndef MIN_SIG_MAG
#define MIN_SIG_MAG 0.0     // Minimal practical value of signal assumed
#endif

#ifndef MAX_SIG_MAG
#define MAX_SIG_MAG 5.0     // Maximal practical value of signal assumed
#endif

#endif

#endif /* CONSTANTES_H_ */

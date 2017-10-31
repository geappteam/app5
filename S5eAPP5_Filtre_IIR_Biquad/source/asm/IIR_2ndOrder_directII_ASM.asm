;****************************************************************************************
; APPEL :
; short * direct1FIR_ASM(short *cPtr, short ech, const short h[], short *y);
;
; A4 : Adresse du pointeur sur l'échantillon précédent
; B4 : Valeur de l'échantillon courant
; A6 : Adresse du début du tableau de coefficients du filtre, h[]
; B6 : Adresse de l'échantillon de sortie
;
; Return : la nouvelle adresse de cPtr (A4)
;
; NB:
; 1) La longueur du filtre passe-haut, N = 63 (ordre = 62), est fixe (hardcoded)
;    et n'est donc pas passée comme paramètre à la fonction
; 2) Comme le mode d'adressage circulaire est employé pour le tampon, il n'est pas nécessaire
;    de spécifier l'adresse de début du tampon mais simplement l'adresse de l'échantillon
;    courant. En effet, quand le pointeur du tampon est incrémenté ou décrémenté, le
;    mode d'adressage circulaire force le pointeur à rester dans le tampon ("wrapping"). Il suffit simplement
;    de spécifier la bonne longueur avec l'AMR et de bien aligner le tampon lors de sa
;    déclaration dans le programme C avec "#pragma DATA_ALIGN"
;
;****************************************************************************************

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;; Les directives ;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	.def IIR_2ndOrder_directII_ASM

	.data




	.text


IIR_2ndOrder_directII_ASM
    .asmfunc

	;SATURATE FUNCTION 					;Obtain x

	LDW .D1 *+A6[3], A0 				;Load C[3]
||	LDW .D2 *+B4[1], B10				;Load w[1]

	NOP 4

	MPYID .M1 A0, A4, A3:A2				;Obtain a0*x(n)
||	LDW .D1 *+A6[1], A10 				;Load C[4]
||	LDW .D2 *+B4[1], B6					;Load w[2]

	NOP 4

	MV A10, B8							;Move C[4] into another register

	MPYID .M2 B8, B10, B9:B8			;Obtain a1*w(n-1)
||	LDW .D1 *+A6[1], A10 				;Load C[5]

	NOP 4

;	SHR A3:A2, 0x13, A12				;Obtain a0*x(n)>>13
;||	LDW .D1 *-A6[5], A0 				;Load C[0]

	NOP;

;	MV A10, B1 							;Move C[5] into another register
;	MPYID .M2 B1, B6, B13:B12			;Obtain a2*w(n-2)

	NOP;

;	SHR B9:B8, 0x13, B0					;Obtain a1*w(n-1)>>13
;||	LDW .D1 *+A6[1], A14 				;Load C[1]

;	SUB A12, B0, A1						;Obtain a0*x(n)-a1*w(n-1)

	NOP 3

;	LDW .D1 *+A6[1], A12 				;Load C[2]

	NOP 2

;	SHR B13:B12, 0x13, B14				;Obtain a2*w(n-2)>>13
;	SUB A1, B14, A2  					;Obtain a0*x(n)-a1*w(n-1)-a2*w(n-2)

	;SATURATE FUNCTION 					;Obtain w[0]

;	MPYID .M2 A0, A8, A3:A2				;Obtain b0*w(n)

	NOP 8

;	MV A14, B0 							;Move C[1] into another register

;	SHR A3:A2, 0x13, A10				;Obtain b0*w(n)>>13

;	MPYID .M2 B0, B10, B9:B8			;Obtain b1*w(n-1)

	NOP 8

;	MV B6, A14							;Move ...  into another register

;	MPYID .M2 A12, A14, A3:A2			;Obtain b2*w(n-2) ;

;	SHR B9:B8, 0x13, A11				;Obtain b1*w(n-1)>>13

;	ADD A10, A11, A0					;Obtain b0*w(n)+b1*w(n-1)

	NOP 7

;	SHR A3:A2, 0x13, A10				;Obtain b2*w(n-2)>>13

;	ADD A0, A10, A4						;Obtain and "store" y
;||	STW B10, *-B4[0]					;Store w[2]

;	STW A8, *-B4[1] 					;Store w[1]

    B B3 ; INDISPENSABLE ; B3 contient l'adresse de retour
    NOP 5

    .endasmfunc

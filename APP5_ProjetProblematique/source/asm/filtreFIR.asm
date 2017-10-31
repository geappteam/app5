;
; filtreFIR.asm
;
;	Fonction de filtre FIR replie

	.def 	_hp_asmFIR

	.data

	.text

; short* hp_asmFIR(short *cPtr, short ech, const short coeffsPlie[], short Nplie, short tampon[], short L, short* y);
_hp_asmFIR
	; Parameters
	; A4 cPtr
	; B4 ech
	; A6 coeffsPlie
	; B6 Nplie
	; A8 tampon
	; B8 L
	; A10 y
	.asmfunc

	; Context protection CSR & AMR
	MVC		CSR, B12
||	MVKL	31, A5
	MVC		AMR, B13
||	MVKH	31, A5

	; Setting up circular addressing for cPtr(A4), head(B5) and tail(A5)
	; Calculating buffer size
	LMBD 	1, B8, B5
	SUB 	A5, B5, B5
	SHL		B5, 16, B5
	; Asigning register A4,A5,B5
||	MVKL	0x405, A5
	OR		B5, A5, B5
	MVC 	B5, AMR

	; Incrementing the address of cPtr and storing ech
	STH		B4, *++A4

||	ZERO B9	; Preparing the sum register

	SUB		B6, 1, A5	; Nplie-1
	ADD		A5, A5, A5	; 2*(Nplie-1)
||	MV 		A4, B5		; head
	SUBAH	A4, A5, A5	; tail

	B		convolutionCheck
	NOP		5

convolutionLoop:
	; Load increment tail
	LDH		*A5++[1], B7
	; Load decrement head
||	LDH		*B5--[1], A7
	NOP		4

	; Sum both samples
	ADD 	A7, B7, A9
	; Load coefficient
|| 	LDH		*A6++, A11
	NOP		4

	; Multiplication
	MPYLH	A11, A9, A0
	MPYSU	A11, A9, A9
	SHL		A0, 0X10, A0
	ADD		A0, A9, A9

	; Sum
	ADD 	B9, A9, B9

convolutionCheck:
	CMPEQ	A5, B5, A1
	[!A1]B	convolutionLoop
	NOP 	5

	; Load middle sample
	LDH		*A5, B7
 	LDH		*A6, A11
 	NOP		4
	MPY		B7, A11, A9
	NOP		1
	; Sum
	ADD 	B9, A9, B9

	SHR		B9, 15, B9
	STH		B9, *A10

	; Restauration of context
	MVC 	B12, AMR
	MVC 	B13, CSR

	B 		B3
	NOP 	5
	.endasmfunc

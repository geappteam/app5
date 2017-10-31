;
; filtreFIR.asm
;
;	Fonction de filtre FIR replie

	.def _hp_asmFIR

	.data

	.text


_hp_asmFIR
	.asmfunc

	; Context protection CSR & AMR
	MVC	CSR, B5
	MVC	AMR, B6

	; Setting up circular addressing for cPtr(A4), head and tail
	MVKL 0x00040001,A7
	MVKH 0x00040001,A7
	MVC A7,AMR

	; Restauration of context
	MVC B6, AMR
	MVC B5, CSR

	B B3
	NOP 5
	.endasmfunc

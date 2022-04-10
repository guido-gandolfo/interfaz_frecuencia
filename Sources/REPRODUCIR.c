#include "REPRODUCIR.h"
#include "derivative.h"
unsigned short frecuencias[] = {100, 300, 500, 1000, 2000,
		5000, 10000, 12000};
static unsigned char reproduccion = 0; // nota = 1, barrido = 0
static unsigned short NC = 0;

void REPRODUCIR_frecuencia (unsigned char indice) {
	REPRODUCIR_sonido_on();
	NC = frecuencias[indice];
}

void REPRODUCIR_sonido_on () {
	TPM1C1SC = 0x54U;
}
void REPRODUCIR_sonido_off () {
	TPM1C1SC = 0;
}
void REPRODUCIR_TPMC0_Handler() {
	TPM1C0V += 4000;	
}
void REPRODUCIR_TPMC1_Handler() {
	TPM1C1V += NC;
}

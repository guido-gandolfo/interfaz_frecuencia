#include "INTERFAZ.h"
#include "SCI.h"
void INTERFAZ_bienvenida () {
	SCI_escribir_cadena_en_buffer("BIENVENIDO\r\n");
}
void INTERFAZ_tabla () {
	SCI_escribir_cadena_en_buffer("100Hz(100) 300Hz(300) 500Hz(500) 1KHz(1K) 2KHz(2K)\r\n");
	SCI_escribir_cadena_en_buffer("5KHz(5K) 10KHz(10K) 12KHz(12K)\r\n");
}
void INTERFAZ_menu () {
	SCI_escribir_cadena_en_buffer("'reset' - reset.\r\n");
	SCI_escribir_cadena_en_buffer("'on' - sonido on.\r\n");
	SCI_escribir_cadena_en_buffer("'off' - sonido off.\r\n");
}

void INTERFAZ_opciones_frecuencia() {
	SCI_escribir_cadena_en_buffer("ingrese el comando correspondiente a la frecuencia.\r\n");
}

void INTERFAZ_cmd_inv () {
	SCI_escribir_cadena_en_buffer("comando invalido.\r\n");
}

#include <hidef.h>
#include "derivative.h"
#include "SCI.h"
#include "INTERFAZ.h"
#include "REPRODUCIR.h"
char dato;
unsigned char FLAG_inicio = 1;
unsigned char FLAG_play = 0;
unsigned char FLAG_play_frecuencia = 0;

void MCU_init(void); /* Device initialization function declaration */

void main(void) {
	MCU_init();
	PTBDD_PTBDD2 = 0; // => STATE en 0 desconectado en 1 conectado
	SCI_inicializar_ble (); // Setea el nombre al módulo de bluetooth
	REPRODUCIR_sonido_off();
	for(;;) {
		SCI_update(); // Si ahy algo en el buffer lo escribe 
		if (PTBD_PTBD2) { //STATE = 1
			if (FLAG_inicio) {
				REPRODUCIR_sonido_off();
				INTERFAZ_bienvenida();
				INTERFAZ_tabla ();
				INTERFAZ_menu ();
				FLAG_inicio = 0;
			}
			else
			{
				if (SCI_get_comando(&dato)){
					switch(dato){
					case 'A':
						//REPRODUCIR_frecuencia(0);
						SCI_escribir_cadena_en_buffer("Se ingreso A .\r\n");
						break;
					case 'B':
						//REPRODUCIR_frecuencia(1);
						SCI_escribir_cadena_en_buffer("Se ingreso B .\r\n");
						break;
					case 'C':
						//REPRODUCIR_frecuencia(2);
						SCI_escribir_cadena_en_buffer("Se ingreso C .\r\n");
						break;
					case 'D':
						//REPRODUCIR_frecuencia(3);
						SCI_escribir_cadena_en_buffer("Se ingreso D .\r\n");
						break;
					case 'E':
						//REPRODUCIR_frecuencia(4);
						break;
					case 'F':
						//REPRODUCIR_frecuencia(4);
						break;
					case 'G':
						//REPRODUCIR_frecuencia(4);
						break;
					case 'H':
						//REPRODUCIR_frecuencia(4);
						break;
					case 'r':
						FLAG_inicio = 1;
						REPRODUCIR_sonido_off();
						break;
					case 'n':
						REPRODUCIR_sonido_on();
						break;
					case 'f':
						REPRODUCIR_sonido_off();
						break;
					default:
						INTERFAZ_cmd_inv();
						break;
					}
				}  
			} 
		}
	}
}

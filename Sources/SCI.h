#ifndef _SCI_H
#define _SCI_H 1
#define BUFFER_ESCRITURA 167
#define BUFFER_LECTURA 30

void SCI_inicializar_ble (void);
void SCI_update (void);
unsigned char SCI_escribir_cadena_en_buffer (char * cadena);
unsigned char SCI_leer_caracter(char * dato);
void SCI_RX_Handler (void);
void SCI_TX_Handler (void);
char SCI_get_comando(char * dato);
#endif

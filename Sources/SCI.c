#include "derivative.h"
#include "SCI.h"
volatile char RX_flag, RX_flag_respuesta = 0;
volatile char caracter;
static char cadena_recibir[BUFFER_LECTURA];
static char cadena_enviar[BUFFER_ESCRITURA];
static unsigned char TXindiceBuffer = 0;
static unsigned char TXindiceEnviar = 0;
static unsigned char RXindiceBuffer = 0;
static unsigned char RXindiceLectura = 0;

static char arrayCaracter[] = {'A','B','C','D','E','F','G','H','I','J','K','L'};
static char cien[] = {'1','0','0'};
static char trescientos[] = {'3','0','0'};
static char quinientos[] = {'5','0','0'};
static char mil[] = {'1','K'};
static char dosmil[] = {'2','K'};
static char cincomil[] = {'5','K'};
static char diezmil[] = {'1','0','K'};
static char docemil[] = {'1','2','K'};
static char on[] = {'O','N'};
static char off[] = {'O','F','F'};
static char reset[] = {'R','E','S','E','T'};

void SCI_inicializar_ble () {
	SCI_escribir_cadena_en_buffer("AT+NAMEG1\r\n");
	while (!RX_flag_respuesta) {
		SCI_update();
	}

}
unsigned char SCI_escribir_cadena_en_buffer (char * dato) {
	unsigned char i = 0;
	while(dato[i] != '\0') {
		if (TXindiceBuffer == BUFFER_ESCRITURA)
			return 0;
		cadena_enviar[TXindiceBuffer] = dato[i];
		TXindiceBuffer++; i++;
	}
	return 1;
}
void SCI_TX_Handler () {
	while (SCIS1_TDRE==0);
	if (TXindiceBuffer > TXindiceEnviar) {
		SCID = cadena_enviar[TXindiceEnviar];
		TXindiceEnviar++;
	} else {
		SCIC2_TIE = 0;
	}
}
void SCI_RX_Handler () {
	if (SCIS1_RDRF) {
		caracter = SCID;
		RX_flag = 1;
	}
}
void SCI_update() {
	if (TXindiceBuffer > TXindiceEnviar) {
		SCIC2_TIE = 1;
	} else {
		TXindiceBuffer = 0;
		TXindiceEnviar = 0;
	}
	if (RX_flag) {
		cadena_recibir[RXindiceBuffer] = caracter;
		if (caracter == '\n') {
			RX_flag_respuesta = 1;
		}
		RXindiceBuffer++;
		RX_flag = 0;
	}
}
unsigned char SCI_leer_caracter(char * dato) {
	unsigned char i=0;
	if (RXindiceBuffer > RXindiceLectura) {
		dato[i] = cadena_recibir[RXindiceLectura];
		RXindiceLectura++;
		i++;
		if (RXindiceBuffer == RXindiceLectura) {
			RXindiceBuffer = 0;
			RXindiceLectura = 0;
		}
		return 1;
	}
	return 0;
}
char SCI_get_comando(char * c)
{
	unsigned char i;
	char result;
	if (RXindiceBuffer < 1)
	{
		return 0;
	}
	for(i = 0; i < RXindiceBuffer; i++)
	{
		if (mil[i] == cadena_recibir[i])
		{
			result = 'D';
			if (i == RXindiceBuffer)
			{
				*c = result;
				return 1;
			}
		}
		else
		{
			result = 'X';
			break;
		}
	}
	for(i = 0; i < RXindiceBuffer; i++)
	{
		if (dosmil[i] == cadena_recibir[i])
		{
			result = 'E';
			if (i == RXindiceBuffer)
			{
				*c = result;
				return 1;
			}
		}
		else
		{
			result = 'X';
			break;
		}
	}
	for(i = 0; i < RXindiceBuffer; i++)
	{
		if (on[i] == cadena_recibir[i])
		{
			result = 'I';
			if (i == RXindiceBuffer)
			{
				*c = result;
				return 1;
			}
		}
		else
		{
			result = 'X';
			break;
		}
	}
	for(i = 0; i < RXindiceBuffer; i++)
	{
		if (cien[i] == cadena_recibir[i])
		{
			result = 'A';
			if (i == RXindiceBuffer)
			{
				*c = result;
				return 1;
			}
		}
		else
		{
			result = 'X';
			break;
		}
	}
	for(i = 0; i < RXindiceBuffer; i++)
	{
		if (trescientos[i] == cadena_recibir[i])
		{
			result = 'B';
			if (i == RXindiceBuffer)
			{
				*c = result;
				return 1;
			}
		}
		else
		{
			result = 'X';
			break;
		}
	}
	for(i = 0; i < RXindiceBuffer; i++)
	{
		if (quinientos[i] == cadena_recibir[i])
		{
			result = 'C';
			if (i == RXindiceBuffer)
			{
				*c = result;
				return 1;
			}
		}
		else
		{
			result = 'X';
			break;
		}
	}

	for(i = 0; i < RXindiceBuffer; i++)
	{
		if (cincomil[i] == cadena_recibir[i])
		{
			result = 'F';
			if (i == RXindiceBuffer)
			{
				*c = result;
				return 1;
			}
		}
		else
		{
			result = 'X';
			break;
		}
	}
	for(i = 0; i < RXindiceBuffer; i++)
	{
		if (diezmil[i] == cadena_recibir[i])
		{
			result = 'G';
			if (i == RXindiceBuffer)
			{
				*c = result;
				return 1;
			}
		}
		else
		{
			result = 'X';
			break;
		}
	}
	for(i = 0; i < RXindiceBuffer; i++)
	{
		if (docemil[i] == cadena_recibir[i])
		{
			result = 'H';
			if (i == RXindiceBuffer)
			{
				*c = result;
				return 1;
			}
		}
		else
		{
			result = 'X';
			break;
		}
	}
	for(i = 0; i < RXindiceBuffer; i++)
	{
		if (off[i] == cadena_recibir[i])
		{
			result = 'J';
			if (i == RXindiceBuffer)
			{
				*c = result;
				return 1;
			}
		}
		else
		{
			result = 'X';
			break;
		}
	}
	for(i = 0; i < RXindiceBuffer; i++)
	{
		if (reset[i] == cadena_recibir[i])
		{
			result = 'K';
			if (i == RXindiceBuffer)
			{
				*c = result;
				return 1;
			}
		}
		else
		{
			result = 'X';
			break;
		}
	}
	*c = result;
	return 1;
}

/************************************************************************************
     Fichero: encript.c

 	Generar la imagen encriptada

***********************************************************************************/

#include "pixmap.h"
#include <stdio.h>
#define SIZE 2

void encript_aux (unsigned char *v1, unsigned char *v2) {

///////////////////////////////////////////////////////////////////////////////$
// POR HACER:
// codigo para el encriptado de 2 pixeles de la imagen
///////////////////////////////////////////////////////////////////////////////$

	//Clave para encriptar los pixeles
	int key[SIZE][SIZE] = {
			{21, 35},
			{18, 79},
	};

	unsigned char *pixels[SIZE] = {v1, v2};
	int encryptedPixels[SIZE];

	int i, j, temp;
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			encryptedPixels[i] += (key[i][j] * (int)*pixels[j]);
		}
		encryptedPixels[i] %= 256;
	}

	int k;
	for (k = 0; k < SIZE; k++) {
		*pixels[k] = encryptedPixels[k];
	}

}


void generar_imagen_encriptada(imagen in_imagen, imagen *out_imagen) {

	generar_imagen(out_imagen,in_imagen.h,in_imagen.w,NEGRO);

	//////////////////////////////////////////////////////////////////////////////////////
	// Codigo para generar la imagen encriptada
	//////////////////////////////////////////////////////////////////////////////////////

	int i, j;
	unsigned char c1, c2;
	// Recorrer la imagen encriptando los pixeles de 2 en 2
	for(i = 0; i < in_imagen.h - 1; i++) {
		for(j = 0; j < in_imagen.w - 1; j += 2) {

		c1 = in_imagen.im[i][j];
		c2 = in_imagen.im[i][j+1];

		encript_aux(&c1, &c2);

		out_imagen->im[i][j] = c1;
		out_imagen->im[i][j+1] = c2;
		}
	}

}

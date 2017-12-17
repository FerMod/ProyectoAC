/************************************************************************************
     Fichero: transmit.c

       Contiene las funciones para preparar la transmision de la imagen
***********************************************************************************/

#include "pixmap.h"
#include "transmit_aux.h"


/* Prepara la transmision de la imagen                         */
/***********************************************************************************/

void preparar_transmision(imagen in_imagen) {

    //////////////////////////////////////////////////////////////////////////////////////
    // codigo para preparar la transmision de la imagen
    // a cada pixel hay que aplicarle la funcion transmit_aux
    //
    // tened en cuenta la cabecera de la funcion transmit_aux.h
    // extern void transmit_aux (unsigned char vp1, int i, int j, int h, int w);
    // pixel de la imagen, su posicion (i,j) y dimensiones de la imagen (h,w)
    //////////////////////////////////////////////////////////////////////////////////////

    int i, j;
    for(i = 0; i < in_imagen.h; i++) {
        for(j = 0; j < in_imagen.w; j++) {
            transmit_aux(in_imagen.im[i][j], i, j, in_imagen.h, in_imagen.w);
        }
    }

}

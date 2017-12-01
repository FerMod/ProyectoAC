/************************************************************************************
   Fichero: ecualizacion.c 

   Incluye las funciones de ecualizacion de la imagen
***********************************************************************************/

#include <math.h>
#include "pixmap.h"

/* Calcula el histograma de niveles de gris en la imagen                         */
/***********************************************************************************/

void histograma(imagen in_imagen, int *histo, int *vmin_ha)
{

//////////////////////////////////////////////////////////////////////////////////////
// POR HACER: 
// codigo para el calculo del histograma, histograma acumulado y minimo
// procesar la imagen in_imagen y calcular histo y vmin_ha
//////////////////////////////////////////////////////////////////////////////////////

}


/* Genera la imagen ecualizada utilizando el histograma ecualizado               */
/***********************************************************************************/

void generar_imagen_ecualizada(imagen in_imagen, imagen *out_imagen, int *histoa, int vmin_ha)
{

 generar_imagen(out_imagen,in_imagen.h,in_imagen.w,NEGRO);

//////////////////////////////////////////////////////////////////////////////////////
// POR HACER: 
// codigo para generar la imagen ecualizada
//////////////////////////////////////////////////////////////////////////////////////

}


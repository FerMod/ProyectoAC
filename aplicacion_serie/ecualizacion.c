/************************************************************************************
   Fichero: ecualizacion.c 

   Incluye las funciones de ecualizacion de la imagen
***********************************************************************************/

#include <stdio.h>
#include <math.h>
#include "pixmap.h"

const char *progress = "-\\|/";

typedef struct {
    int intensity;
    int cdf;
} Pixel;

/* Calcula el histograma de niveles de gris en la imagen                         */
/***********************************************************************************/

void histograma(imagen in_imagen, int *histo, int *vmin_ha) {

//////////////////////////////////////////////////////////////////////////////////////
// POR HACER:
// codigo para el calculo del histograma, histograma acumulado y minimo
// procesar la imagen in_imagen y calcular histo y vmin_ha
//////////////////////////////////////////////////////////////////////////////////////

    int totalPix = (in_imagen.w * in_imagen.h) - 1;

    Pixel minCdfPixel;
    minCdfPixel.intensity = 0;
    minCdfPixel.cdf = MAX_VAL; // Valor minimo de la funcion CDF
    
    int i, j;
    for(i = 0; i < in_imagen.h-1; i++) {
        for(j = 0; j < in_imagen.w-1; j++) {
            histo[in_imagen.im[i][j]]++;
        }
    }

    // int chisto[MAX_VAL];
    // chisto[0] = histo[0];
    printf ("\nHistograma:\n");
    for (i = 0; i < MAX_VAL; i++) {
        int cdfVal = histo[i];
        if(cdfVal< minCdfPixel.cdf) {
         minCdfPixel.intensity = in_imagen.im[i][j];
         minCdfPixel.cdf = cdfVal;
     }
     printf("%d\n", cdfVal);
        // chisto[i] = chisto[i-1] + histo[i];
 }

 *vmin_ha = minCdfPixel.cdf;
 printf ("vmin_ha -> %d\n", *vmin_ha);

}



/* Genera la imagen ecualizada utilizando el histograma ecualizado               */
/***********************************************************************************/

void generar_imagen_ecualizada(imagen in_imagen, imagen *out_imagen, int *histo, int vmin_ha) {
    //printf("\n\tProcesando [-]\n\n");
    int totalPix = (in_imagen.w * in_imagen.h) - 1;
    int maxIntensity = MAX_VAL-1;
    int i, j;
    printf ("\nvmin_ha -> %d\n", vmin_ha);
    printf ("Imagen de %d x %d pixeles.\n", in_imagen.h, in_imagen.w);
    *out_imagen = in_imagen;
    for(i = 0; i < in_imagen.h-1; i++) {
       // printf ("i -> %d\n", i);
        for(j = 0; j < in_imagen.w-1; j++) {
            //printf ("j -> %d\n", j);
            // printf ("%d\n", ((histo[in_imagen.im[i][j]] - vmin_ha) / totalPix) * maxIntensity);
            //printf ("%f\n", floor((float)(histo[in_imagen.im[i][j]] - vmin_ha / totalPix * maxIntensity)));
            (*out_imagen).im[i][j] = floor((float)(histo[in_imagen.im[i][j]] - vmin_ha / totalPix * maxIntensity));
            // if(i % totalPix == 0) {
            //    printf("%c%c%c]", 8, 8, progress[(i/totalPix) % 4]);
            //    fflush(stdout);
            // }
        }
    }

    generar_imagen(out_imagen,in_imagen.h,in_imagen.w,NEGRO);
    
//////////////////////////////////////////////////////////////////////////////////////
// POR HACER:
// codigo para generar la imagen ecualizada
//////////////////////////////////////////////////////////////////////////////////////

}


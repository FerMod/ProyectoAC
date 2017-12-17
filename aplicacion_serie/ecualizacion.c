/************************************************************************************
   Fichero: ecualizacion.c 

   Incluye las funciones de ecualizacion de la imagen
***********************************************************************************/

/*
1. calculate histogram

loop over i ROWS of input image
    loop over j COLS of input image
        k = input_image[i][j]
        hist[k] = hist[k] + 1
    end loop over j
    end loop over i


2. calculate the sum of hist

loop over i gray levels
    sum = sum + hist[i]
    sum_of_hist[i] = sum
end loop over i


3. transform input image to output image

area = area of image (ROWS x COLS)
Dm = number of gray levels in output image
loop over i ROWS
    loop over j COLS
        k = input_image[i][j]
        out_image[i][j] = (Dm/area) x sum_of_hist[k]
    end loop over j
end loop over i
*/

#include <stdio.h>
#include <math.h>
#include "pixmap.h"

typedef struct {
    int intensity;
    int cdf;
} Pixel;

/* Calcula el histograma de niveles de gris en la imagen                         */
/***********************************************************************************/

void histograma(imagen in_imagen, int *histo, int *vmin_ha) {

    //////////////////////////////////////////////////////////////////////////////////////
    // codigo para el calculo del histograma, histograma acumulado y minimo
    // procesar la imagen in_imagen y calcular histo y vmin_ha
    //////////////////////////////////////////////////////////////////////////////////////

    // Initialize all array values to 0
    // The compiler will fill the unwritten entries with zeros
    int pixelHisto[MAX_VAL] = {0};
    int i, j;
    for (i = 0; i < in_imagen.h; i++) {
        for (j = 0; j < in_imagen.w; j++) {
            pixelHisto[in_imagen.im[i][j]]++;
        }
    }

    Pixel minCdfPixel;
    minCdfPixel.intensity = 0;
    minCdfPixel.cdf = pixelHisto[0];

    for (i = 0; i < MAX_VAL-1; i++) {
        int cdfVal = pixelHisto[i];
        if(cdfVal < minCdfPixel.cdf && cdfVal > 0) {
            minCdfPixel.intensity = i;
            minCdfPixel.cdf = cdfVal;
        }
    }
    *vmin_ha = minCdfPixel.cdf;

    histo[0] = pixelHisto[0];
    for(i = 1; i < MAX_VAL; i++) {
        histo[i] = histo[i-1] + pixelHisto[i];
    }

}



/* Genera la imagen ecualizada utilizando el histograma ecualizado               */
/***********************************************************************************/

void generar_imagen_ecualizada(imagen in_imagen, imagen *out_imagen, int *histo, int vmin_ha) {

    generar_imagen(out_imagen, in_imagen.h, in_imagen.w, NEGRO);


    //////////////////////////////////////////////////////////////////////////////////////
    // codigo para generar la imagen ecualizada
    //////////////////////////////////////////////////////////////////////////////////////

    double factor = (MAX_VAL - 1) / (double)(in_imagen.w * in_imagen.h);
    
    int i, j;
    for(i = 0; i < in_imagen.h; i++) {
        for(j = 0; j < in_imagen.w; j++) {
            out_imagen->im[i][j] = round(factor * (double)(histo[in_imagen.im[i][j]] - vmin_ha));
        }
    }

}

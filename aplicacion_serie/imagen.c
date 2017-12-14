/************************************************************************************
   Fichero: imagen.c (SERIE)

   Se aplica a una imagen en formato PGM (P5: binario) el siguiente tratamiento
     -- ecualizacion del histograma
     -- encriptacion
     -- preparacion de la transmision

   Ficheros de entrada:   xx.pgm (imagen en formato pgm)
   Ficheros de salida:	  xx_ecu.pgm    imagen ecualizada
                          xx_cif.pgm    imagen encriptada
 
   Compilar el programa junto con ecualizacion.c, encript.c y transmit.c

***********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>

#include "pixmap.h" 
#include "ecualizacion.h"
#include "encript.h"
#include "transmit.h"


/*************************              MAIN                  **********************/
/***********************************************************************************/

int main(int argc, char **argv) {
  char name[100];
  int i;

  // Imagenes: original, ecualizada y encriptada
  imagen imagen_ori,imagen_ecu,imagen_cif; 

  // histogramas  
  int histo[MAX_VAL]; 
  int vmin_ha; 

  // calculo de tiempos
  struct timeval t0,t1;
  double tej1,tej2,tej3,tej4,tej;

  if (argc != 2) 
  {
    printf ("\nUSO: programa imagen\n");
    exit (0);
  }

  // Lectura de la imagen de entrada: solo imagenes graylevel en formato .pgm
  if (load_pixmap(argv[1], &imagen_ori) == 0) {
    printf ("\nError en lectura del fichero de entrada: %s\n\n",argv[1]);
    exit (0);
  }

  /* Proceso imagen: calcular el histograma ecualizado, generar nuevas imagenes (ecualizada y encriptada)      */
  /**********************************************************************************************************/
  printf("\n --> Procesando la imagen. Tamano: %d -- %d\n",imagen_ori.h,imagen_ori.w);
  

  gettimeofday(&t0, 0);
  for (i=0;i<MAX_VAL;i++) histo[i]=0;
  histograma(imagen_ori, histo, &vmin_ha);
  gettimeofday(&t1, 0);
  tej1 = (t1.tv_sec - t0.tv_sec) + (t1.tv_usec - t0.tv_usec) / 1e6;
  printf("\n     Calcular histograma: Tej. serie = %1.1f ms", tej1*1000);

  gettimeofday(&t0, 0);
  generar_imagen_ecualizada(imagen_ori, &imagen_ecu, histo, vmin_ha);
  gettimeofday(&t1, 0);
  tej2 = (t1.tv_sec - t0.tv_sec) + (t1.tv_usec - t0.tv_usec) / 1e6;
  printf("\n     Ecualizar la imagen: Tej. serie = %1.1f ms", tej2*1000);

  gettimeofday(&t0, 0);
  //generar_imagen_encriptada(imagen_ecu, &imagen_cif);
  gettimeofday(&t1, 0);
  tej3 = (t1.tv_sec - t0.tv_sec) + (t1.tv_usec - t0.tv_usec) / 1e6;
  printf("\n     Cifrar la imagen: Tej. serie = %1.1f ms\n", tej3*1000);

  gettimeofday(&t0, 0);
  //preparar_transmision(imagen_cif);
  gettimeofday(&t1, 0);
  tej4 = (t1.tv_sec - t0.tv_sec) + (t1.tv_usec - t0.tv_usec) / 1e6;
  printf("     Preparar la transmision: Tej. serie = %1.1f ms\n\n", tej4*1000);

  tej = tej1+tej2+tej3+tej4;
  printf("\n     TOTAL: Tej. serie = %1.1f ms\n\n", tej*1000);
 
  /* Escritura de las imagenes en el disco                                         */
  /*********************************************************************************/
  strcpy(name,argv[1]);
  name[strlen(name)-4]='\0';
  strcat(name,"_ecu.pgm");
  store_pixmap(name,imagen_ecu);
  
  strcpy(name,argv[1]);
  name[strlen(name)-4]='\0';
  strcat(name,"_cif.pgm");
  //store_pixmap(name,imagen_cif);

  // Liberar memoria de las imagenes 
  liberar_imagen(imagen_ori);
  liberar_imagen(imagen_ecu);
  //liberar_imagen(imagen_cif);

  printf("\nPulse ENTER para continuar...\n");
  getchar();

  return 0;

}

/* Fichero: pixmap.h */

#define NEGRO   0       
#define BLANCO  255
#define MAX_VAL 256     /* Rango de posibles valores de grises */


typedef struct {
  int w;                 /* Width */
  int h;                 /* Height */
  unsigned char *dat;    /* Image */
  unsigned char **im;
} imagen;


extern int load_pixmap(char *filename, imagen *iimage);
extern void store_pixmap(char *filename, imagen oimage);

extern void  generar_imagen(imagen *oimagen, int h, int w, unsigned char val);
extern void  liberar_imagen(imagen iimagen);



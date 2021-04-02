#ifndef _PGMIO_
#define _PGMIO_

unsigned char **allocate_image(int rows, int cols);

void free_image(unsigned char **image, int rows);

int read_pgm_image(char *infilename, unsigned char ***image, int *rows, int *cols);

int write_pgm_image(char *outfilename, unsigned char **image, int rows,
   int cols, char *comment, int maxval);

int write_gray_bmp(char *outfilename, unsigned char **image, short int rows, short int cols);
#endif
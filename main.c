#include <stdio.h>
#include <stdlib.h>
#include <string.h>		// Para usar strings

// SOIL é a biblioteca para leitura das imagens
#include "SOIL.h"

// Um pixel RGB
typedef struct {
    unsigned char r, g, b;
} RGB;

// Uma imagem em RGB
typedef struct {
    int width, height;
    RGB* img; //array de pixels
} Img;

// Protótipos
void load(char* name, Img* pic);

// Carrega uma imagem para a struct Img
void load(char* name, Img* pic)
{
    int chan;
    pic->img = (unsigned char*) SOIL_load_image(name, &pic->width, &pic->height, &chan, SOIL_LOAD_RGB);
    if(!pic->img)
    {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
        exit(1);
    }
    printf("Load: %d x %d x %d\n", pic->width, pic->height, chan);
}

void encrypt(char password[], char message2[], int argc, char** argv)
{




}

int main(int argc, char** argv)
{
    //encrypt("garrafa", "celular", argc, argv);


    free(pic.img);

}


/*

/*
    printf("Primeiros 10 pixels da imagem:\n");
    for(int i=0; i<10; i++) {
        printf("[%02X %02X %02X] ", pic.img[i].r, pic.img[i].g, pic.img[i].b);
    }
    printf("\n\n");
*/


    //EXEMPLO
    /*
    printf("\nEXEMPLO\n\n");
    for(int i=0; i<pic.width*pic.height; i++) {
        pic.img[i].r=0xff;
    }
    */
/*
    for(int i=0; i<pic.width*pic.height; i++) {
        printf("[%02X %02X %02X] ", pic.img[i].r, pic.img[i].g, pic.img[i].b);
    }
    printf("\n");

*/

    //pega letra em hexa
    //transforma em binario
    //le de traz para frente => get bit
    //codifica ao contrário => set bit

    //void cifra (char* senha, int* desloc, int* cifra)
    //CODIFICAÇÃO
   // *desloc = 0;
   // *salto = 0;
    //*cifra = 0;


    //1 + 1 + 3
    //a+(a++ + ++a)
    //a += a++ + ++a

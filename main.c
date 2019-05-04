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
    char message[300] = "aa";
    char mensagemCriptografada[300];

    printf("\n");
    printf("CRIPTOGRAFANDO MENSAGEM:");
    printf("\n");

    int count = 0;
    char caractereAtual;

    char bit1 = 0;
    char bit2 = 0;
    char bit3 = 0;
    char bit4 = 0;
    char bit5 = 0;
    char bit6 = 0;
    char bit7 = 0;
    char bit8 = 0;

    //Trocando bits
    for(int i = 0; i < strlen(message); i++) {
        caractereAtual = message[i];

        //pegando bit a bit do caracter...
        bit8 = (caractereAtual >> 7) & 0x01;
        bit7 = (caractereAtual >> 6) & 0x01;

        bit6 = (caractereAtual >> 5) & 0x01;
        bit5 = (caractereAtual >> 4) & 0x01;

        bit4 = (caractereAtual >> 3) & 0x01;
        bit3 = (caractereAtual >> 2) & 0x01;

        bit2 = (caractereAtual >> 1) & 0x01;
        bit1 = (caractereAtual >> 0) & 0x01;

        printf("CARACTERE ATUAL: %c\n", caractereAtual);
        printf("%d%d%d%d%d%d%d%d\n", bit8, bit7, bit6, bit5, bit4, bit3, bit2, bit1);

       mensagemCriptografada[i] = caractereAtual + 3;
    }
    printf("\nMENSAGEM ORIGINAL: ");
    printf("%s\n", message);
    printf("\nMENSAGEM CRIPTOGRAFADA: ");
    printf("%s\n", mensagemCriptografada);

    //MENSAGEM JÁ FOI CRIPTOGRAFADA
    //ESTENOGRAFANDO IMAGEM
    printf("\n");
    printf("Estaganografando imagem:");
    printf("\n");

    Img pic;
    if(argc < 1) {
        printf("loader [img]\n");
        exit(1);
    }
    load(argv[1], &pic);

    printf("\nPrimeiros 20 pixels da imagem antes da mudanca:\n");
    for(int i=0; i<20; i++) {
        printf("[%02X %02X %02X] ", pic.img[i].r +1, pic.img[i].g, pic.img[i].b);
    }
    printf("\n\n");

    int cont=0;
    for(int i=0; i<strlen(mensagemCriptografada); i++) {
        caractereAtual = mensagemCriptografada[i];

        //pegando bit a bit do caracter...
        bit8 = (caractereAtual >> 7) & 0x01;
        bit7 = (caractereAtual >> 6) & 0x01;

        bit6 = (caractereAtual >> 5) & 0x01;
        bit5 = (caractereAtual >> 4) & 0x01;

        bit4 = (caractereAtual >> 3) & 0x01;
        bit3 = (caractereAtual >> 2) & 0x01;

        bit2 = (caractereAtual >> 1) & 0x01;
        bit1 = (caractereAtual >> 0) & 0x01;
        //printf("%d%d%d%d%d%d%d%d\n", bit8, bit7, bit6, bit5, bit4, bit3, bit2, bit1);

        printf("CARACTERE ATUAL: %c\n", caractereAtual);

        //RASCUNHO
        //printf("\n\n<RASCUNHO>\n\n");
        for(int j=0; j<9;j++){
            switch(j){
                case 0:
                    pic.img[cont].r = bit8;
                    cont++;
                    break;
                case 1:
                    pic.img[cont].r = bit7;
                    cont++;
                    break;
                case 2:
                    pic.img[cont].r = bit6;
                    cont++;
                    break;
                case 3:
                    pic.img[cont].r = bit5;
                    cont++;
                    break;
                case 4:
                    pic.img[cont].r = bit4;
                    cont++;
                    break;
                case 5:
                    pic.img[cont].r = bit3;
                    cont++;
                    break;
                case 6:
                    pic.img[cont].r = bit2;
                    cont++;
                    break;
                case 7:
                    pic.img[cont].r = bit1;
                    cont++;
                    break;

                default:
                    break;
            }
        }
        //printf("\n\n</RASCUNHO>\n\n");


    }
    printf("\nPrimeiros 20 pixels da imagem depois da mudanca:\n");
    for(int i=0; i<20; i++) {
        printf("[%02X %02X %02X] ", pic.img[i].r, pic.img[i].g, pic.img[i].b);
    }
    printf("\n\n");

    SOIL_save_image("saida.bmp", SOIL_SAVE_TYPE_BMP, pic.width, pic.height, 3, pic.img);

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

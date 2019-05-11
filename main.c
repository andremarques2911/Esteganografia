#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Para usar strings
#include "SOIL.h" // SOIL é a biblioteca para leitura das imagens

// Um pixel RGB
typedef struct {
    unsigned char r, g, b;
} RGB;

// Uma imagem em RGB
typedef struct {
    int width, height;
    RGB* img; //array de pixels
} Img;

int cont = 0; //Responsavel pelo controle do index dos pixels da imagem
char bit1 = 0;
char bit2 = 0;
char bit3 = 0;
char bit4 = 0;
char bit5 = 0;
char bit6 = 0;
char bit7 = 0;
char bit8 = 0;

// Protótipos
void load(char* name, Img* pic);

// Carrega uma imagem para a struct Img
void load(char* name, Img* pic) {
    int chan;
    pic -> img = (unsigned char*) SOIL_load_image(name, &pic -> width, &pic -> height, &chan, SOIL_LOAD_RGB);
    if(!pic -> img) {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
        exit(1);
    }
    printf("Load: %d x %d x %d\n", pic->width, pic->height, chan);
}

void salta(int senha) {
    cont += senha;
}


void encrypt(int password, char message[], int argc, char** argv) {
    char mensagemCriptografada[348]; //Armazena a mensagem apos a cifra de Cesar
/*
    for(int i=0; i<strlen(mensagemCriptografada); i++){
        mensagemCriptografada[i] = ' ';
    }
*/
    printf("\n");
    printf("CRIPTOGRAFANDO MENSAGEM:");
    printf("\n");

    char caractereAtual; //Armazena o caractere atual da mensagem

    //Usando Cifra de Cesar. Somando 3 letras.
    for(int i = 0; i < strlen(message); i++) {
        caractereAtual = message[i];
        mensagemCriptografada[i] = caractereAtual + 3;
    }

    printf("\n\nTamanho Criptografada: %d \n\n", strlen(mensagemCriptografada) );
    printf("\nMENSAGEM ORIGINAL: ");
    printf("%s\n", message);
    printf("\nMENSAGEM CRIPTOGRAFADA: ");
    printf("%s\n", mensagemCriptografada);

    //ESTENOGRAFANDO IMAGEM
    printf("\n");
    printf("Estaganografando imagem:");
    printf("\n");

    //Carrega a imagem em pic
    Img pic;

    if(argc < 1) {
        printf("loader [img]\n");
        exit(1);
    }

    load(argv[1], &pic);
    printf("\nPixels da imagem antes da mudanca:\n");

    for(int i = 1; i <= 8*strlen(mensagemCriptografada); i++) {
        printf("[%02X %02X %02X] ", pic.img[i].r +1, pic.img[i].g, pic.img[i].b);
        if(i % 8 == 0) {
            printf("\n");
        }
    }
    printf("\n\n");

    for(int i = 0; i < strlen(mensagemCriptografada); i++) {
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

        printf("CARACTERE ATUAL: %c\n", caractereAtual);

        for(int j = 0; j < 8; j++) {
            switch(j) {
                case 0:
                    pic.img[cont].r = (pic.img[cont].r << 1) | bit8;
                    salta(password);
                    break;
                case 1:
                    pic.img[cont].r = (pic.img[cont].r << 1) | bit7;
                    salta(password);
                    break;
                case 2:
                    pic.img[cont].r = (pic.img[cont].r << 1) | bit6;
                    salta(password);
                    break;
                case 3:
                    pic.img[cont].r = (pic.img[cont].r << 1) | bit5;
                    salta(password);
                    break;
                case 4:
                    pic.img[cont].r = (pic.img[cont].r << 1) | bit4;
                    salta(password);
                    break;
                case 5:
                    pic.img[cont].r = (pic.img[cont].r << 1) | bit3;
                    salta(password);
                    break;
                case 6:
                    pic.img[cont].r = (pic.img[cont].r << 1) | bit2;
                    salta(password);
                    break;
                case 7:
                    pic.img[cont].r = (pic.img[cont].r << 1) | bit1;
                    salta(password);
                    break;

                default:
                    break;
            }
        }

    }
    printf("\nPixels da imagem depois da mudanca:\n");

    for(int i = 1; i <= 8*strlen(mensagemCriptografada); i++) {
        printf("[%02X %02X %02X] ", pic.img[i].r, pic.img[i].g, pic.img[i].b);
        if(i % 8 == 0) {
            printf("\n");
        }
    }

    printf("\n\n");

    printf("TESTE DESCRITOGRAFIA\n");

    printf("LETRA DA MENSAGEM EM BINARIO\n");
    bit8 = (message[0] >> 7) & 0x01;
    bit7 = (message[0] >> 6) & 0x01;
    bit6 = (message[0] >> 5) & 0x01;
    bit5 = (message[0] >> 4) & 0x01;
    bit4 = (message[0] >> 3) & 0x01;
    bit3 = (message[0] >> 2) & 0x01;
    bit2 = (message[0] >> 1) & 0x01;
    bit1 = (message[0] >> 0) & 0x01;
    printf("Bit8: %d \nBit7: %d \nBit6: %d \nBit5: %d \nBit4: %d \nBit3: %d \nBit2: %d \nBit1: %d\n\n\n", bit8, bit7, bit6, bit5, bit4, bit3, bit2, bit1);

    printf("LETRA CRIPTOGRAFADA EM BINARIO\n");
    bit8 = (mensagemCriptografada[0] >> 7) & 0x01;
    bit7 = (mensagemCriptografada[0] >> 6) & 0x01;
    bit6 = (mensagemCriptografada[0] >> 5) & 0x01;
    bit5 = (mensagemCriptografada[0] >> 4) & 0x01;
    bit4 = (mensagemCriptografada[0] >> 3) & 0x01;
    bit3 = (mensagemCriptografada[0] >> 2) & 0x01;
    bit2 = (mensagemCriptografada[0] >> 1) & 0x01;
    bit1 = (mensagemCriptografada[0] >> 0) & 0x01;
    printf("Bit8: %d \nBit7: %d \nBit6: %d \nBit5: %d \nBit4: %d \nBit3: %d \nBit2: %d \nBit1: %d\n\n\n", bit8, bit7, bit6, bit5, bit4, bit3, bit2, bit1);

    printf("BUSCANDO LETRA CRIPTOGRAFADA NA IMAGEM EM BINARIO\n");
    bit8 = (pic.img[0].r >> 0)  & 0x01;
    bit7 = (pic.img[1].r >> 0)  & 0x01;
    bit6 = (pic.img[2].r >> 0)  & 0x01;
    bit5 = (pic.img[3].r >> 0)  & 0x01;
    bit4 = (pic.img[4].r >> 0)  & 0x01;
    bit3 = (pic.img[5].r >> 0)  & 0x01;
    bit2 = (pic.img[6].r >> 0)  & 0x01;
    bit1 = (pic.img[7].r >> 0)  & 0x01;
    printf("Bit8: %d \nBit7: %d \nBit6: %d \nBit5: %d \nBit4: %d \nBit3: %d \nBit2: %d \nBit1: %d\n\n\n", bit8, bit7, bit6, bit5, bit4, bit3, bit2, bit1);

    // Limpando bits
    bit8 = 0;
    bit7 = 0;
    bit6 = 0;
    bit5 = 0;
    bit4 = 0;
    bit3 = 0;
    bit2 = 0;
    bit1 = 0;

    // Salvando imagem criptografada
    SOIL_save_image("saida.bmp", SOIL_SAVE_TYPE_BMP, pic.width, pic.height, 3, pic.img);

    free(pic.img);
}

void decrypt(int password, char** argv) {
    printf("\n\nDESCRIPTOGRAFANDO...\n\n");


    char* message = calloc(300, sizeof message);
    printf("\nPassword: %d\n\n", password);
    Img pic;

    load("saida.bmp", &pic);

    char caractereDescoberto[7];

    cont = 0;
    int contCarac = 0;
    for(int i = 0; i < 8; i++){
        //printf("\n\nCont: %d\n", cont);
        //printf("ContCaractere: %d\n\n", contCarac);
        contCarac = i;

        switch(contCarac) {
            case 0:
                bit8 = (pic.img[cont].r >> 0)  & 0x01;
                salta(password);
                break;
            case 1:
               bit7 = (pic.img[cont].r >> 0) & 0x01;
                salta(password);
                break;
            case 2:
                bit6 = (pic.img[cont].r >> 0) & 0x01;
                salta(password);
                break;
            case 3:
                bit5 = (pic.img[cont].r >> 0) & 0x01;
                salta(password);
                break;
            case 4:
                bit4 = (pic.img[cont].r >> 0) & 0x01;
                salta(password);
                break;
            case 5:
                bit3 = (pic.img[cont].r >> 0) & 0x01;
                salta(password);
                break;
            case 6:
                bit2 = (pic.img[cont].r >> 0) & 0x01;
                salta(password);
                break;
            case 7:
                bit1 = (pic.img[cont].r >> 0) & 0x01;
                salta(password);
                break;
            default:
                break;
        }
    }

    printf("\nMensagem descriptografada em binario: \n");

    printf("Bit8: %d \nBit7: %d \nBit6: %d \nBit5: %d \nBit4: %d \nBit3: %d \nBit2: %d \nBit1: %d\n\n\n", bit8, bit7, bit6, bit5, bit4, bit3, bit2, bit1);

    //bit8 + bit7 + bit6 + bit5, bit4 + bit3 + bit2 + bit1;
    //printf("\nVALOR M: %d\n\n", m);

    printf("\n\nMENSAGEM CRIPTOGRAFADA: %s\n\n", message);

    free(message);
}

int main(int argc, char** argv) {
    encrypt(1, "b", argc, argv);
    decrypt(1, argv);
}
/*

char x = 'x';
    char buffer[8];
    printf("################### TESTE ###################\n\n");
    printf("Valor x: %c\n", x);

    bit8 = (x >> 7) & 0x01;
    bit7 = (x >> 6) & 0x01;
    bit6 = (x >> 5) & 0x01;
    bit5 = (x >> 4) & 0x01;
    bit4 = (x >> 3) & 0x01;
    bit3 = (x >> 2) & 0x01;
    bit2 = (x >> 1) & 0x01;
    bit1 = (x >> 0) & 0x01;

    printf("Bit8: %d \nBit7: %d \nBit6: %d \nBit5: %d \nBit4: %d \nBit3: %d \nBit2: %d \nBit1: %d\n", bit8, bit7, bit6, bit5, bit4, bit3, bit2, bit1);

/*
    printf("\nPixel original: [ %02X %02X %02X ]\n\n ", pic.img[0].r, pic.img[0].g, pic.img[0].b);

    printf("Bit Novo: %d ", bit6);

    itoa(pic.img[0].r,buffer,2);
    printf("\nBuffer: %s\n ", buffer);

    pic.img[0].r = (pic.img[0].r << 1) | bit6;//Empurra os bits do pixel para direita e coloca o novo bit no final

    itoa(pic.img[0].r,buffer,2);
    printf("\nBuffer: %s\n ", buffer);

    printf("Pixel alterado: [ %02X %02X %02X ]\n\n", pic.img[0].r, pic.img[0].g, pic.img[0].b);
*/
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

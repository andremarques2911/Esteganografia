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

// Responsável pelo controle do index dos pixels da imagem
int cont = 0;
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
    //printf("Load: %d x %d x %d\n", pic->width, pic->height, chan);
}

// Algoritmo de salto entre pixels
void salta(char* password) {
    int salto = 0;
    for(int i=0; i<strlen(password); i++) {
        salto += password[i];
    }

    salto /= strlen(password);

    cont += salto;
}

void encrypt(int password, char message[], int argc, char** argv) {

    // Armazena a mensagem apos a cifra de Cesar
    char mensagemCriptografada[348];

//    for(int i=0; i<strlen(mensagemCriptografada); i++){
//        mensagemCriptografada[i] = ' ';
//    }

    printf("\n");
    printf("CRIPTOGRAFANDO:");
    printf("\n");

    // Armazena o caractere atual da mensagem
    char caractereAtual;

    // AUMENTANDO 3 LETRAS NO ALFABETO PARA CADA LETRA DA MENSAGEM (CRIPTOGRAFANDO COM CIFRA DE CESAR).
    for(int i = 0; i < strlen(message); i++) {
        caractereAtual = message[i];
        mensagemCriptografada[i] = caractereAtual + 3;
    }

//    printf("\n\nTamanho Criptografada: %d \n\n", strlen(mensagemCriptografada) );
    printf("\nMENSAGEM DESCRIPTOGRAFADA: ");
    printf("%s\n", message);
    printf("\nMENSAGEM CRIPTOGRAFADA: ");
    printf("%s\n", mensagemCriptografada);

    // ESTEGANOGRAFANDO IMAGEM
    printf("\n");
    printf("Estaganografando imagem...");
    printf("\n");

    // Carrega a imagem em pic
    Img pic;

    if(argc < 1) {
        printf("loader [img]\n");
        exit(1);
    }

    load(argv[1], &pic);
/*
    printf("\nPixels da imagem antes da mudanca:\n");
    for(int i = 1; i <= 8*strlen(mensagemCriptografada); i++) {
        printf("[%02X %02X %02X] ", pic.img[i].r +1, pic.img[i].g, pic.img[i].b);
        if(i % 8 == 0) {
            printf("\n");
        }
    }
    printf("\n");
*/
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

//        printf("CARACTERE ATUAL: %c\n", caractereAtual);

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
/*
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

    printf("LETRA DA MENSAGEM EM BINARIO APOS CRIPTOGRAFIA\n");
    bit8 = (mensagemCriptografada[0] >> 7) & 0x01;
    bit7 = (mensagemCriptografada[0] >> 6) & 0x01;
    bit6 = (mensagemCriptografada[0] >> 5) & 0x01;
    bit5 = (mensagemCriptografada[0] >> 4) & 0x01;
    bit4 = (mensagemCriptografada[0] >> 3) & 0x01;
    bit3 = (mensagemCriptografada[0] >> 2) & 0x01;
    bit2 = (mensagemCriptografada[0] >> 1) & 0x01;
    bit1 = (mensagemCriptografada[0] >> 0) & 0x01;
    printf("Bit8: %d \nBit7: %d \nBit6: %d \nBit5: %d \nBit4: %d \nBit3: %d \nBit2: %d \nBit1: %d\n\n\n", bit8, bit7, bit6, bit5, bit4, bit3, bit2, bit1);

    printf("LETRA CRIPTOGRAFADA EM BINARIO RECUPERADA DA IMAGEM SALVA\n");
    bit8 = (pic.img[0].r >> 0)  & 0x01;
    bit7 = (pic.img[1].r >> 0)  & 0x01;
    bit6 = (pic.img[2].r >> 0)  & 0x01;
    bit5 = (pic.img[3].r >> 0)  & 0x01;
    bit4 = (pic.img[4].r >> 0)  & 0x01;
    bit3 = (pic.img[5].r >> 0)  & 0x01;
    bit2 = (pic.img[6].r >> 0)  & 0x01;
    bit1 = (pic.img[7].r >> 0)  & 0x01;
    printf("Bit8: %d \nBit7: %d \nBit6: %d \nBit5: %d \nBit4: %d \nBit3: %d \nBit2: %d \nBit1: %d\n\n\n", bit8, bit7, bit6, bit5, bit4, bit3, bit2, bit1);
*/
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

void decrypt(int password, int passwordLength, char** argv) {
    printf("----------------------------------------------------------------------------------------------\n");
    printf("DESCRIPTOGRAFANDO:\n");

    char* message = calloc(300, sizeof message);
    char* messageCriptografada = calloc(300, sizeof messageCriptografada);

    Img pic;
    load("saida.bmp", &pic);

    // MONTA A LETRA ATRAVÉS DO BINARIO
    cont = 0;
    int contCarac = 0;
    for(int i = 0; i < passwordLength; i++) {
        bit8 = (pic.img[cont].r >> 0)  & 0x01;
        salta(password);
        bit7 = (pic.img[cont].r >> 0) & 0x01;
        salta(password);
        bit6 = (pic.img[cont].r >> 0) & 0x01;
        salta(password);
        bit5 = (pic.img[cont].r >> 0) & 0x01;
        salta(password);
        bit4 = (pic.img[cont].r >> 0) & 0x01;
        salta(password);
        bit3 = (pic.img[cont].r >> 0) & 0x01;
        salta(password);
        bit2 = (pic.img[cont].r >> 0) & 0x01;
        salta(password);
        bit1 = (pic.img[cont].r >> 0) & 0x01;
        salta(password);

        messageCriptografada[i] = (bit8 << 7) + (bit7 << 6) + (bit6 << 5) + (bit5 << 4) + (bit4 << 3) + (bit3 << 2) + (bit2 << 1) + (bit1 << 0);
    }

    // REDUZINDO 3 LETRAS NO ALFABETO PARA CADA LETRA DA MENSAGEM (DESCRIPTOGRAFANDO COM CIFRA DE CESAR)
    for(int i=0; i<strlen(messageCriptografada); i++){
        message[i] = messageCriptografada[i] - 3;
    }

    printf("\nMENSAGEM CRIPTOGRAFADA: %s\n", messageCriptografada);
    printf("\nMENSAGEM DESCRIPTOGRAFADA: %s\n", message);

    free(message);
    free(messageCriptografada);
    free(pic.img);
}

int main(int argc, char** argv) {

    char* password = calloc(50, sizeof password);
    char* message = calloc(300, sizeof message);

    printf("Senha:", password);
    gets(password);
    printf("Mensagem:", message);
    gets(message);

    printf("\nPassword: %s\n", password);
    printf("\nMessage: %s\n", message);

    encrypt(password, message, argc, argv);
    decrypt(password, strlen(message), argv);

}

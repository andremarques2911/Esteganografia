#include <stdio.h>
#include <stdlib.h>
#include <string.h> // PARA UTILIZAR STRINGS
#include "SOIL.h" // BIBLIOTECA PARA LEITURA DAS IMAGENS
#include <conio.h>// PARA OCULTAR A SENHA

// UM PIXEL RGB
typedef struct {
    unsigned char r, g, b;
} RGB;

// UMA IMAGEM EM RGB
typedef struct {
    int width, height;
    RGB* img; //  ARRAY DE PIXELS
} Img;

// RESPONSAVEL PELO CONTROLE DO INDEX DOS PIXEL DA IMAGEM
int cont = 0;

// ARMAZENAM OS BIT DOS CARACTERES
char bit1 = 0;
char bit2 = 0;
char bit3 = 0;
char bit4 = 0;
char bit5 = 0;
char bit6 = 0;
char bit7 = 0;
char bit8 = 0;

// PROTOTIPOS
void load(char* name, Img* pic);
void salta(char* password);
void encrypt(char* password, char message[], int argc, char** argv);
char* cifrar(char* message);
char* passwordInput();
char* messageInput();



// CARREGA UMA IMAGEM PARA A STRUCT IMG
void load(char* name, Img* pic) {
    int chan;
    pic -> img = (unsigned char*) SOIL_load_image(name, &pic -> width, &pic -> height, &chan, SOIL_LOAD_RGB);
    if(!pic -> img) {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
        exit(1);
    }
    //printf("Load: %d x %d x %d\n", pic->width, pic->height, chan);
}

// SALTO ENTRE OS PIXELS
void salta(char* password) {
    int salto = 0;
    for(int i=0; i<strlen(password); i++) {
        salto += password[i];
    }
    salto /= strlen(password);
    cont += salto;
}

char* cifrar(char* message){
    int tam = strlen(message);
    int cesar = tam/(tam/tam);
    char cifra[tam];
    for(int i=0; i<tam; i++){
        cifra[i] = message[i] + cesar;
    }
}

void encrypt(char* password, char message[], int argc, char** argv) {
    //ARMAZENA A MENSAGEM APOS A CIFRA DE CESAR
    char* mensagemCriptografada = calloc(300, sizeof mensagemCriptografada);

    // ARMAZENA O CARACTERE ATUAL DA MENSAGEM
    char caractereAtual;

    // AUMENTANDO 3 LETRAS NO ALFABETO PARA CADA LETRA DA MENSAGEM (CRIPTOGRAFANDO COM CIFRA DE CESAR).
    for(int i = 0; i < strlen(message); i++) {
        caractereAtual = message[i];
        mensagemCriptografada[i] = caractereAtual + 3;
    }

    //printf("MENSAGEM DESCRIPTOGRAFADA: ");
    //printf("%s\n", message);
    //printf("MENSAGEM CRIPTOGRAFADA: ");
    //printf("%s\n", mensagemCriptografada);

    // ESTEGANOGRAFANDO IMAGEM
    // CARREGA A IMAGEM EM PIC
    Img pic;
    if(argc < 1) {
        printf("loader [img]\n");
        exit(1);
    }
    load(argv[1], &pic);

    for(int i = 0; i < strlen(mensagemCriptografada); i++) {
        caractereAtual = mensagemCriptografada[i];

        // PEGANDO BIT A BIT DO CARACTERE
        bit8 = (caractereAtual >> 7) & 0x01;
        bit7 = (caractereAtual >> 6) & 0x01;
        bit6 = (caractereAtual >> 5) & 0x01;
        bit5 = (caractereAtual >> 4) & 0x01;
        bit4 = (caractereAtual >> 3) & 0x01;
        bit3 = (caractereAtual >> 2) & 0x01;
        bit2 = (caractereAtual >> 1) & 0x01;
        bit1 = (caractereAtual >> 0) & 0x01;

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
    // MARCANDO FINAL DA MENSAGEM
    cont++;
    pic.img[cont].r = 0x23;
    // LIMPANDO OS BITS
    bit8 = 0;bit7 = 0;bit6 = 0;bit5 = 0;bit4 = 0;bit3 = 0;bit2 = 0;bit1 = 0;

    // SALVANDO A IMAGEM CRIPTOGRAFADA
    SOIL_save_image("../decrypt/saida.bmp", SOIL_SAVE_TYPE_BMP, pic.width, pic.height, 3, pic.img);

    free(pic.img);
}

char* passwordInput() {
    char* password = calloc(50, sizeof password);
    printf("Senha:", password);
    //gets(password);
    int i;
    fflush(stdin);
    for (i=0;i<300;i++)
    {
        password[i] = getch();
        if(password[i] == 13){
            break;
        }
        putchar('*');
    }
    printf("\n");
    password[i]='\0';
    return password;
}

char* messageInput() {
    char* message = calloc(300, sizeof message);
    printf("Mensagem:", message);
    gets(message);
    return message;
}

int main(int argc, char** argv) {
    encrypt(passwordInput(), messageInput(), argc, argv);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h> // PARA UTILIZAR STRINGS
#include "SOIL.h" // BIBLIOTECA PARA LEITURA DAS IMAGENS
#include <conio.h>// PARA OCULTAR A SENHA

// STRUCT DE UM PIXEL RGB
typedef struct {
    unsigned char r, g, b;
} RGB;

// STRUCT DE UMA IMAGEM FORMADA COM PIXELS EM RGB
typedef struct {
    int width, height;
    RGB* img; //  ARRAY DE PIXELS
} Img;

// VARIÁVEL RESPONSAVEL PELO CONTROLE DO INDEX DOS PIXEL DA IMAGEM
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

// PROTÓTIPOS
void load(char* name, Img* pic);
void salta(char* password);
void decrypt(int password, char** argv);
char* passwordInput();
char* decifrar(char* message);

// CARREGA UMA IMAGEM PARA A STRUCT IMG
void load(char* name, Img* pic) {
    int chan;
    pic -> img = (unsigned char*) SOIL_load_image(name, &pic -> width, &pic -> height, &chan, SOIL_LOAD_RGB);
    if(!pic -> img) {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
        exit(1);
    }
}

// DEFINE O SALTO ENTRE OS PIXELS
void salta(char* password) {
    int salto = 0;
    for(int i = 0; i < strlen(password); i++) {
        salto += password[i];
    }
    salto /= strlen(password);
    cont += salto;
}

// UTILIZA CIFRA DE CESAR NOS CARACTERES DA MENSAGEM CRIPTOGRAFADA. PEGA O TAMANHO DA MENSAGEM, DIVIDE POR 2 E SUBTRAI 
// COM O VALOR DECIMAL DO CARACTERE
char* decifrar(char* message){
    int tam = strlen(message);
    int cesar = (tam/2);
    char* cifra = calloc(300, sizeof cifra);
    for(int i=0; i<tam; i++){
        cifra[i] = message[i] - cesar;
    }
    return cifra;
}

// RECUPERA A MENSAGEM CRIPTOGRAFADA DA IMAGEM E DESCRIPTOGRAFA A MESMA
void decrypt(int password, char** argv) {
    char* message = calloc(300, sizeof message);
    char* messageCriptografada = calloc(300, sizeof messageCriptografada);

    Img pic;
    load("saida.bmp", &pic);

    // MONTA A LETRA ATRAVÉS DO BINARIO
    cont = 0;
    int contCarac = 0;

    // UTILIZA O OPERADOR BITWISE RIGHT SHIFT EM CADA PIXEL RED QUE CONTRENHAM UMA PARTE DE UMA LETRA DA MENSAGEM CRIPTOGRAFADA PARA OBTER
    // O BIT MENOS SIGNIFICATIVO E ARMAZENA O MESMO NAS VARIAVEIS BIT1 - BIT8
    for(int i = 0; i < pic.height*pic.width; i++) {
        if(pic.img[cont+1].r == 0x23){break;}
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
    /*
    for(int i = 0; i < strlen(messageCriptografada); i++){
        message[i] = messageCriptografada[i] - strlen(password);
    }
    */
    message = decifrar(messageCriptografada);


    //printf("\nMENSAGEM CRIPTOGRAFADA: %s\n", messageCriptografada);
    printf("\nMENSAGEM: %s\n", message);
    free(message);
    free(messageCriptografada);
    free(pic.img);
}

char* passwordInput() {
    char* password = calloc(50, sizeof password);
    printf("Senha:", password);
    int i;
    fflush(stdin);
    for(i = 0; i < 300; i++)
    {
        password[i] = getch();
        if(password[i] == 13){
            break;
        }
        putchar('*');
    }
    printf("\n");
    password[i] = '\0';
    return password;
}

int main(int argc, char** argv) {
    decrypt(passwordInput(), argv);
}

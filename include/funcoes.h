// Este header contem as funcoes para o programa principal, separar por tipo posteriormente?
#include "raylib.h"
#include "estruturas.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

//----------------------------------------------------------------------------------
// Protótipos das funções
//----------------------------------------------------------------------------------
void inicializaPlayer(TIPO_PLAYER *player, int posx, int posy);
void inicializaInimigo(TIPO_INIMIGO inimigo[MAX_INIMIGOS]);
void sentidoAleatorioInimigo(TIPO_INIMIGO *inimigo);
void posicaoInimigo(TIPO_INIMIGO inimigo[MAX_INIMIGOS]);
int ehColisaoInimiga(TIPO_INIMIGO inimigo[MAX_INIMIGOS]);
int deveMover(COORDENADAS *entidade, char* matriz);
void controleJogador(TIPO_PLAYER *entidade, char* matriz);
int moveInimigo(TIPO_INIMIGO *inimigo, char* matriz);
void redefineDeslocamentoInimigo(TIPO_INIMIGO *inimigo);
void centerWindow(float windowWidth, float windowHeight);

//----------------------------------------------------------------------------------
// Definição das funções
//----------------------------------------------------------------------------------


// Funcao que inicializa player
void inicializaPlayer(TIPO_PLAYER *player, int posx, int posy)
{
    player->cor = GREEN;
    player->coordPlayer.x = posx;
    player->coordPlayer.y = posy;
    player->coordPlayer.dx = 0;
    player->coordPlayer.dx = 0;
}

// Funcao que inicializa inimigos
void inicializaInimigo(TIPO_INIMIGO* inimigo)
{

    double tempoAtual = GetTime(); // Tempo atual    
    
    posicaoInimigo(inimigo);          // Inicializa posicao aleatoria do inimigo
    sentidoAleatorioInimigo(inimigo); // Inicializa sentido aleatorio do inimigo
    inimigo->timer = 0;                 // Inicializa timer

    // Atualiza o tempo do último movimento
    inimigo->timer = tempoAtual;
}

// Funcao que define o sentido aleatorio do inimigo
void sentidoAleatorioInimigo(TIPO_INIMIGO *inimigo)
{
    // Gerar sentido aleatorio:

    //srand(time(NULL)); // seed atrelada ao tempo do computador, deixa mais devagar.

    // Ao subtrair -1 de um numero aleatorio entre 0 e 2, gera um numero entre -1 e 1
    // Variaveis contendo o sentido de deslocamento do inimigo.
    int numeroRandomDx = (rand() % 3) - 1; // Numero entre -1 e 1
    int numeroRandomDy = (rand() % 3) - 1; // Numero entre -1 e 1

    // Se o numeroRandom for 0, deve-se retirar outro numero aleatorio
    while (numeroRandomDx == 0 && numeroRandomDy == 0)
    {
        numeroRandomDx = (rand() % 3) - 1;
        numeroRandomDy = (rand() % 3) - 1;
    }

    // Define o deslocameto aleatorio do inimigo
    inimigo->coordInimigo.dx = numeroRandomDx;
    inimigo->coordInimigo.dy = numeroRandomDy;
}

// Funcao que define a posicao aleatoria do inimigo
void posicaoInimigo(TIPO_INIMIGO inimigo[MAX_INIMIGOS])
{

    // Define a posicao do inimigo
    inimigo->coordInimigo.x = (rand() % (LARGURA/LADO)) + 1;
    inimigo->coordInimigo.y = (rand() % (LARGURA/LADO)) + 1;
}

// Funcao que verifica se houve colisao entre inimigos
int ehColisaoInimiga(TIPO_INIMIGO inimigo[MAX_INIMIGOS])
{

    for (int i = 0; i < MAX_INIMIGOS; i++)
    {
        for (int j = i + 1; j < MAX_INIMIGOS; j++)
        {
            if (inimigo[i].coordInimigo.x == inimigo[j].coordInimigo.x && inimigo[i].coordInimigo.y == inimigo[j].coordInimigo.y)
            {
                printf("\n Eh coli entre i %d e j %d", i, j);
                return 1; // Retorna 1 indicando que houve colisao
            }
            else
                return 0; // Retorna 0 indicando que nao houve colisao
        }
    }
}

int coletaRecursos (COORDENADAS *entidade, char *matriz) {
    if (entidade->x == 'R' && entidade->y== 'R') {
        return 1;
    }
    return 0;
}

// Funcao que verifica se a entidade deve mover.
int deveMover(COORDENADAS *entidade, char* matriz){
    //Verifica se a movimentação é permitida
    if (entidade->x == (LARGURA/LADO -1) && entidade->dx == 1)
        return 0;
    if (entidade->x == 0 && entidade->dx == -1)
        return 0;
    if (entidade->y == (ALTURA/LADO -1) && entidade->dy == 1)
        return 0;
    if (entidade->y == 0 && entidade->dy == -1)
        return 0;

    if(*(matriz + (entidade->x+entidade->dx) + (entidade->y + entidade->dy)*(LARGURA/LADO)) == 'W')
        return 0;
    if(*(matriz + (entidade->x+entidade->dx) + (entidade->y + entidade->dy)*(LARGURA/LADO)) == 'R')
        coletaRecursos(entidade, matriz);
    
    //Realiza a movimentação
    matriz += entidade->x + entidade->y*(LARGURA/LADO);
    *matriz = ' ';

    entidade->x += entidade->dx;
    entidade->y += entidade->dy;

    matriz += entidade->dx + entidade->dy*(LARGURA/LADO);
    *matriz = 'J';

    return 1;
}

// Funcao que trata controle do jogador
void controleJogador(TIPO_PLAYER *entidade, char* matriz)
{
    entidade->cor;

    if (IsKeyPressed(KEY_RIGHT)) // Verifica tecla pressionada e a tecla segurada
    {
        entidade->coordPlayer.dx = 1;
        entidade->coordPlayer.dy = 0;
        deveMover(&entidade->coordPlayer, matriz);
    }

    if (IsKeyPressed(KEY_LEFT))
    {
        entidade->coordPlayer.dx = -1;
        entidade->coordPlayer.dy = 0;
        deveMover(&entidade->coordPlayer, matriz);
    }

    if (IsKeyPressed(KEY_UP))
    {
        entidade->coordPlayer.dx = 0;
        entidade->coordPlayer.dy = -1;
        deveMover(&entidade->coordPlayer, matriz);
    }

    if (IsKeyPressed(KEY_DOWN))
    {
        entidade->coordPlayer.dx = 0;
        entidade->coordPlayer.dy = 1;
        deveMover(&entidade->coordPlayer, matriz);
    }
}

// Funcao que move o inimigo
int moveInimigo(TIPO_INIMIGO *inimigo, char* matriz)
{

    // Tempo atual
    double tempoAtual = GetTime();

    // // Verifica se o inimigo nao deve mover na direcao aleatoria informada
    // if (!deveMover(inimigo->x, inimigo->y, inimigo->dx, inimigo->dy))
    // {
    //     return 0; // Retorna 0 indicando que o inimigo não se moveu
    // }

    // Se não, se timer for válido.

    if (tempoAtual - inimigo->timer >= INIMIGO_DELAY)
    {
        // Atualiza o tempo do último movimento
        inimigo->timer = tempoAtual;

        deveMover(&inimigo->coordInimigo, matriz);

        return 1; // Retorna 1 indicando que o timer foi zerado e inimigo moveu
    }

    return 0; // Retorna 0 indicando que o inimigo não se moveu
}

// Funcao que redefine o deslocamento do inimigo
void redefineDeslocamentoInimigo(TIPO_INIMIGO *inimigo)
{

    int dyInicial, dxInicial;

    dxInicial = inimigo->coordInimigo.dx;
    dyInicial = inimigo->coordInimigo.dy;

    // Randomiza o sentido enquanto os valores forem iguais ao inicial
    do
    {
        sentidoAleatorioInimigo(inimigo);

    } while (inimigo->coordInimigo.dx == dxInicial && inimigo->coordInimigo.dy == dyInicial);
}

// Funcao que centraliza a janela ao centro da tela
void centerWindow(float windowWidth, float windowHeight)
{
    int monitor = GetCurrentMonitor();             // Captura o monitor usado
    int monitorWidth = GetMonitorWidth(monitor);   //  Verifica a largura do monitor usado
    int monitorHeight = GetMonitorHeight(monitor); //  Verifica a altura do monitor usado

    //  Define a posição da janela (window) na tela
    SetWindowPosition((int)(monitorWidth / 2) - (int)(windowWidth / 2), (int)(monitorHeight / 2) - (int)(windowHeight / 2));
}

int salvaEstado(char nomeDoArquivo[30], GAMESTATUS gameStatus){
    int erro = 1;
    FILE *arq;

    if(!(arq = fopen(nomeDoArquivo, "w")))
        erro = 0;
        else if(!(fwrite(&gameStatus, sizeof(GAMESTATUS), 1, arq)))
                erro = 0;
            else fclose(arq);

    return erro;
}

int leEstado(char nomeDoArquivo[30], GAMESTATUS* gameStatus) {
    int erro = 1;
    FILE *arq;

    if (!(arq = fopen(nomeDoArquivo, "r"))) {
        perror("Erro ao abrir o arquivo para leitura");
        erro = 0;
        } else if (!(fread(gameStatus, sizeof(GAMESTATUS), 1, arq))) {
            perror("Erro ao ler do arquivo");
            erro = 0;}
                else fclose(arq);

    return erro;
}

void desenha(int coordX, int coordY, Color cor){


    DrawRectangle(coordX * LADO, coordY * LADO, LADO, LADO, cor); // Posição do quadrado player
   

}

int leMapa(char nomeDoArquivo[30], char* matriz) {
    int erro = 1;
    FILE *arq;
    char caractere;

    if (!(arq = fopen(nomeDoArquivo, "r"))) {
        perror("Erro ao abrir o arquivo para leitura");
        erro = 0;
    } else {
        while(!(feof(arq))){
            caractere = getc(arq);
            if (caractere != '\n' && caractere != '\0'){

                *matriz = caractere;
                matriz += sizeof(char); 
                
            }
        }
        fclose(arq);
    }

    return erro;
}

void desenhaMapa(char* matriz, TIPO_PLAYER* player, TIPO_INIMIGO* inimigo){

    for (int i=0; i<(ALTURA/20); i++)
        for(int j=0; j< LARGURA/20; j++){
            switch(*matriz){
                case 'J':                   //Player
                    desenha(j, i, GREEN);
                    inicializaPlayer(player, j, i); // Inicializar o jogador
                    break;

                case 'M':                   //Inimigo
                    desenha(j, i, RED);
                    inicializaInimigo(inimigo);
                    inimigo++;
                    break;
                
                case 'R':                   //Recurso
                    desenha(j, i, PINK);
                    break;

                case 'H':                   //Buraco/Portal
                    desenha(j, i, YELLOW);
                    break;

                case 'S':                   //Base
                    desenha(j, i, BLUE);
                    break;

                case 'W':                   //Parede
                    desenha(j, i, PURPLE);
                    break;
                
                case ' ':                   //Área de trânsito
                    desenha(j, i, WHITE);
                    break;

                case 'O':                   //Obstáculo
                    desenha(j, i, BLACK);
                    break;

            }
            matriz++;
        }
}
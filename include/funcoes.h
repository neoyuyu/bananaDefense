// Este header contem as funcoes para o programa principal, separar por tipo posteriormente?

#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
// Cria as constantes (macro definicoes) para uso no programa geral
#define LARGURA 800
#define ALTURA 800
#define M_TAMANHO 30
#define LADO 20
#define MAX_INIMIGOS 5
#define BACKGROUND_COLOR \
    (Color) { 60, 3, 32, 100 } // Light Gray

// Estruturas definicao:

// Estrutura StructPlayer representa o jogador do jogo.
typedef struct structPlayer
{

    int dx; // Deslocamento no sentido x
    int x;  // Coordenada x no mapa

    int dy; // Deslocamento no sentido y
    int y;  // Coordenada y no mapa

} TIPO_PLAYER;

// Estrutura StructInimigo representa os inimigos do jogo.
typedef struct structInimigo
{

    int dx; // Deslocamento no sentido x
    int x;  // Coordenada x no mapa

    int dy; // Deslocamento no sentido y
    int y;  // Coordenada y no mapa

} TIPO_INIMIGO;

// Esta funcao centraliza a janela ao centro da tela
void centerWindow(float windowWidth, float windowHeight)
{
    int monitor = GetCurrentMonitor();             // Captura o monitor usado
    int monitorWidth = GetMonitorWidth(monitor);   //  Verifica a largura do monitor usado
    int monitorHeight = GetMonitorHeight(monitor); //  Verifica a altura do monitor usado

    //  Define a posição da janela (window) na tela
    SetWindowPosition((int)(monitorWidth / 2) - (int)(windowWidth / 2), (int)(monitorHeight / 2) - (int)(windowHeight / 2));
}

// Funcao que verifica se a estrutura deve mover.
int deveMover(int x, int y, int dx, int dy)
{

    // Verifica eixo x, está fora dos limites (LARGURA X ALTURA)
    if ((dx == 1 && x + LADO > LARGURA - LADO) || (dx == -1 && x - LADO < 0))
        return 0;
    // Verifica eixo y, está fora dos limites (LARGURA X ALTURA)
    if ((dy == 1 && y + LADO > ALTURA - LADO) || (dy == -1 && y - LADO < 0))
        return 0;
    //	Retorna 1 caso esteja dentro dos limites.
    return 1;
}

// Funcao que move a estrutura player recebida.
void move(int dx, int dy, int *x, int *y)
{
    if (dx == 1) // Deslocamento direta
        *x += LADO;

    if (dx == -1) // Deslocamento esquerda
        *x -= LADO;

    if (dy == 1) // Deslocamento baixo
        *y += LADO;

    if (dy == -1) // Deslocamento cima
        *y -= LADO;
}
// Trata entrada do usuario e move o jogador
void controleJogador(int *px, int *py)
{

    if (IsKeyPressed(KEY_RIGHT) || IsKeyDown(KEY_RIGHT)) // Verifica tecla pressionada e a tecla segurada
    {

        if (deveMover(*px, *py, 1, 0))
            move(1, 0, px, py);
    }

    if (IsKeyPressed(KEY_LEFT) || IsKeyDown(KEY_LEFT))
    {
        if (deveMover(*px, *py, -1, 0))
            move(-1, 0, px, py);
    }

    if (IsKeyPressed(KEY_UP) || IsKeyDown(KEY_UP))
    {
        if (deveMover(*px, *py, 0, -1))
            move(0, -1, px, py);
    }

    if (IsKeyPressed(KEY_DOWN) || IsKeyDown(KEY_DOWN))
    {
        if (deveMover(*px, *py, 0, 1))
            move(0, 1, px, py);
    }
}

// Logica para fazer estrutura inimigo se movimentar com base em valores aleatorios.
int moveInimigo(TIPO_INIMIGO *inimigo)
{

    // Verifica se o inimigo nao deve mover na direcao aleatoria informada e retorna 0.
    if (!deveMover(inimigo->x, inimigo->y, inimigo->dx, inimigo->dy))
    {
        return 0;
    }
    // Se nao, desloca o inimigo.
    else
    {
        if (inimigo->dx == 1)
            inimigo->x += 20; // Deslocamento direta

        if (inimigo->dx == -1)
            inimigo->x -= 20; // Deslocamento esquerda

        if (inimigo->dy == 1)
            inimigo->y += 20; // Deslocamento baixo

        if (inimigo->dy == -1)
            inimigo->y -= 20; // Deslocamento cima

        return 1;
    }
}

// Inicializar a estrutura inimigo em posicao aleatoria
void posicaoAleatoriaInimigo(TIPO_INIMIGO *inimigo)
{
    srand(time(NULL)); // seed atrelada ao tempo do computador, deixa mais devagar.

    // Gerar um número aleatório no intervalo de 0 a 38
    int random = rand() % 39;

    // Calcular o múltiplo de 20 correspondente
    int randomMultiplo = (random * 20) + 20;

    inimigo->x, inimigo->y = randomMultiplo; // Define a posicao aleatoria do inimigo
}

// Inicializar a estrutura inimigo em sentido aleatorio
void sentidoAleatorioInimigo(TIPO_INIMIGO *inimigo)
{
    // Gerar sentido aleatorio:

    // srand(time(NULL)); // seed atrelada ao tempo do computador, deixa mais devagar.

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
    inimigo->dx = numeroRandomDx;
    inimigo->dy = numeroRandomDy;
}

// Mover inimigo em outra direcao
void redefineDeslocamentoInimigo(TIPO_INIMIGO *inimigo)
{
    // srand(time(NULL));

    int dyInicial, dxInicial;

    dxInicial = inimigo->dx;
    dyInicial = inimigo->dy;

    // Randomiza o sentido enquanto os valores forem iguais ao inicial
    do
    {
        sentidoAleatorioInimigo(inimigo);

    } while (inimigo->dx == dxInicial || inimigo->dy == dyInicial);

    // moveInimigo(inimigo);
}

// Verifica se ha colisao entre os inimigos
int ehColisaoInimiga(TIPO_INIMIGO *inimigo)
{
}

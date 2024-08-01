// Este header contem as funcoes para o programa principal, separar por tipo posteriormente?
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>
// Cria as constantes (macro definicoes) para uso no programa geral
#define LARGURA 600
#define ALTURA 600
#define M_TAMANHO 30
#define INIMIGO_DELAY 2 // Delay para movimentacao do inimigo em ms
#define LADO 20
#define MAX_INIMIGOS 10
#define BACKGROUND_COLOR \
    (Color) { 60, 3, 32, 100 } // Cor Vinho

// Estruturas definicao:

// Estrutura StructPlayer representa o jogador do jogo.
typedef struct
{

    int dx; // Deslocamento no sentido x
    int x;  // Coordenada x no mapa
    int dy; // Deslocamento no sentido y
    int y;  // Coordenada y no mapa

} TIPO_PLAYER;

// Estrutura StructInimigo representa os inimigos do jogo.
typedef struct
{

    int dx;       // Deslocamento no sentido x
    int x;        // Coordenada x no mapa
    int dy;       // Deslocamento no sentido y
    int y;        // Coordenada y no mapa
    double timer; // Timer para movimentacao

} TIPO_INIMIGO;

// Funcao que define o sentido aleatorio do inimigo
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

// Funcao que centraliza a janela ao centro da tela
void centerWindow(float windowWidth, float windowHeight)
{
    int monitor = GetCurrentMonitor();             // Captura o monitor usado
    int monitorWidth = GetMonitorWidth(monitor);   //  Verifica a largura do monitor usado
    int monitorHeight = GetMonitorHeight(monitor); //  Verifica a altura do monitor usado

    //  Define a posição da janela (window) na tela
    SetWindowPosition((int)(monitorWidth / 2) - (int)(windowWidth / 2), (int)(monitorHeight / 2) - (int)(windowHeight / 2));
}

// Funcao que verifica se houve colisao entre inimigos
int ehColisaoInimiga(TIPO_INIMIGO inimigo[MAX_INIMIGOS])
{

    for (int i = 0; i < MAX_INIMIGOS; i++)
    {
        for (int j = i + 1; j < MAX_INIMIGOS; j++)
        {
            if (inimigo[i].x == inimigo[j].x && inimigo[i].y == inimigo[j].y)
            {
                printf("\n Eh coli entre i %d e j %d", i, j);
                return 1; // Retorna 1 indicando que houve colisao
            }
            else
                return 0; // Retorna 0 indicando que nao houve colisao
        }
    }
}

// Funcao que define a posicao aleatoria do inimigo
void posicaoInimigo(TIPO_INIMIGO inimigo[MAX_INIMIGOS])
{

    // Define a posicao do inimigo
    inimigo->x = 300;
    inimigo->y = 300;
}

// Funcao que inicializa inimigos
void inicializaInimigo(TIPO_INIMIGO inimigo[MAX_INIMIGOS])
{

    double tempoAtual = GetTime(); // Tempo atual

    for (int i = 0; i < MAX_INIMIGOS; i++)
    {

        posicaoInimigo(&inimigo[i]);          // Inicializa posicao aleatoria do inimigo
        sentidoAleatorioInimigo(&inimigo[i]); // Inicializa sentido aleatorio do inimigo
        inimigo[i].timer = 0;                 // Inicializa timer

        // Atualiza o tempo do último movimento
        inimigo->timer = tempoAtual;
    }
}

// Funcao que inicializa player
void inicializaPlayer(TIPO_PLAYER *player)
{
    for (int i = 0; i < MAX_INIMIGOS; i++)
    {
        player->x = 300;
        player->y = 300;
        player->dx = 0;
        player->dy = 0;
    }
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
// Funcao que trata controle do jogador
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

// Funcao que move o inimigo
int moveInimigo(TIPO_INIMIGO *inimigo)
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

        if (inimigo->dx == 1)
            inimigo->x += LADO; // Deslocamento direta

        if (inimigo->dx == -1)
            inimigo->x -= LADO; // Deslocamento esquerda

        if (inimigo->dy == 1)
            inimigo->y += LADO; // Deslocamento baixo

        if (inimigo->dy == -1)
            inimigo->y -= LADO; // Deslocamento cima

        return 1; // Retorna 1 indicando que o timer foi zerado e inimigo moveu
    }

    return 0; // Retorna 0 indicando que o inimigo não se moveu
}

// Funcao que redefine o deslocamento do inimigo
void redefineDeslocamentoInimigo(TIPO_INIMIGO *inimigo)
{

    int dyInicial, dxInicial;

    dxInicial = inimigo->dx;
    dyInicial = inimigo->dy;

    // Randomiza o sentido enquanto os valores forem iguais ao inicial
    do
    {
        sentidoAleatorioInimigo(inimigo);

    } while (inimigo->dx == dxInicial && inimigo->dy == dyInicial);
}

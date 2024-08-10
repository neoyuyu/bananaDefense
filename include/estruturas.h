#include "raylib.h"

// Constantes (macro definicoes) para uso no programa geral
#define LARGURA 1200
#define ALTURA 600
#define M_TAMANHO 30
#define INIMIGO_DELAY 0.5 // Delay para movimentacao do inimigo em s
#define LADO 20
#define MAX_INIMIGOS 10
#define BACKGROUND_COLOR \
    (Color) { 60, 3, 32, 100 } // Cor Vinho

//----------------------------------------------------------------------------------
// Structures Definition
//----------------------------------------------------------------------------------

typedef struct
{

    int x, y;   // posições
    int dx, dy; // deslocamentos

} COORDENADAS;

// Estrutura StructPlayer representa o jogador do jogo.
typedef struct
{

    COORDENADAS coordPlayer;
    Color cor;
    char letra;

} TIPO_PLAYER;

// Estrutura StructInimigo representa os inimigos do jogo.
typedef struct
{

    COORDENADAS coordInimigo;
    int ultimoMovimentoX; // Ultima direcao de movimento
    int ultimoMovimentoY; // Ultima direcao de movimento
    double timer;         // Timer para movimentacao
    Color cor;
    char letra;

} TIPO_INIMIGO;

typedef struct
{

    COORDENADAS coordBase;
    Color cor;

} BASE;

typedef struct
{
    TIPO_PLAYER Player;
    TIPO_INIMIGO enemy[MAX_INIMIGOS];
    int pontuacao, vidas;
    char nivel;

} GAMESTATUS;

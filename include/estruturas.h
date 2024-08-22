#include "raylib.h"

// Constantes (macro definicoes) para uso no programa geral
#define LARGURA 1200
#define ALTURA 600
#define INIMIGO_DELAY 0.3 // Delay para movimentacao do inimigo em s
#define LADO 20
#define MAX_INIMIGOS 50
#define MAX_RECURSOS 50

//----------------------------------------------------------------------------------
// Definição de estruturas
//----------------------------------------------------------------------------------

typedef struct
{
    int x;  // posição x
    int y;  // posição y
    int dx; // deslocamento no eixo x
    int dy; // deslocamento no eixo y

} COORDENADAS;

// Estrutura StructPlayer representa o jogador do jogo.
typedef struct
{

    COORDENADAS coordPlayer; // Coordenadas do jogador
    Color cor;               // Cor do jogador
    char letra;              // Letra que o jogador representa no mapa
    int vidas;               // Vidas do jogador

} TIPO_PLAYER;

// Estrutura StructInimigo representa os inimigos do jogo.
typedef struct
{

    COORDENADAS coordInimigo; // Coordenadas do inimigo
    int ultimoMovimentoX;     // Ultima direcao de movimento
    int ultimoMovimentoY;     // Ultima direcao de movimento
    double timer;             // Timer para movimentacao com delay
    int vidas;                // Vida do inimigo
    Color cor;                // Cor do inimigo
    char letra;               // Letra que o inimigo representa no mapa

} TIPO_INIMIGO;

typedef struct
{

    COORDENADAS coordBase; // Coordenadas da base
    Color cor;             // Cor da base
    int vidas;             // Vidas da base

} BASE;

typedef struct
{
    TIPO_PLAYER Player;               // Informacoes do jogador
    TIPO_INIMIGO enemy[MAX_INIMIGOS]; // Informacoes dos inimigos
    int pontuacao;                    // Pontuacao do jogador no jogo
    int vidas;                        // Vidas do jogador
    char nivel;                       // Nivel do jogo

} GAMESTATUS;

// Estrutura enumerada GAMESCREEN representa as telas do jogo
typedef enum
{

    TITULO,
    MENU,
    GAMEPLAY,
    GAMEOVER,
    VITORIA
} GAMESCREEN;
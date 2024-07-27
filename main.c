#include "raylib.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "include/centerWindow.c"

#define LARGURA 800
#define ALTURA 800
#define M_TAMANHO 30
#define LADO 20
#define MAX_INIMIGOS 10
#define BACKGROUND_COLOR \
	(Color) { 60, 3, 32, 100 } // Light Gray

// Estruturas definicao:

// Estrutura StructPlayer representa o jogador do jogo.
typedef struct structPlayer
{

	int dx; // Deslocamento no sentido x
	int x;	// Coordenada x no mapa

	int dy; // Deslocamento no sentido y
	int y;	// Coordenada y no mapa

} TIPO_PLAYER;

// Estrutura StructInimigo representa os inimigos do jogo.
typedef struct structInimigo
{

	int dx; // Deslocamento no sentido x
	int x;	// Coordenada x no mapa

	int dy; // Deslocamento no sentido y
	int y;	// Coordenada y no mapa

} TIPO_INIMIGO;

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

// Logica para fazer estrutura inimigo se movimentar com base em valores aleatorios.
int moveInimigo(TIPO_INIMIGO *inimigo)
{

	// Verifica se o inimigo nao deve mover na direcao aleatoria informada e retorna 0.
	if (!deveMover(inimigo->x, inimigo->y, inimigo->dx, inimigo->dy))
		return 0;

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

// Redefinir o sentido do deslocamento inimigo.
void redefineDeslocamentoInimigo(TIPO_INIMIGO *inimigo)
{
}

// Inicializar a estrutura inimigo em posicao e sentido aleatorios.
void posicaoAleatoriaInimigo(TIPO_INIMIGO *inimigo)
{
	// Gerar sentido aleatorio:

	//  srand(time(NULL)); // seed atrelada ao tempo do computador, deixa mais devagar.

	// Ao subtrair -1 de um numero aleatorio entre 0 e 2, gera um numero entre -1 e 1
	int numeroRandom = (rand() % 3) - 1; // Numero entre -1 e 1

	// Variaveis contendo o sentido de deslocamento do inimigo.
	// int dx = numeroRandom;
	// int dy = numeroRandom;

	int posAleatoria = (rand() % 40) * LADO; // Variavel com a posicao aleatoria do inimigo

	inimigo->x, inimigo->y = posAleatoria;	 // Define a posicao aleatoria do inimigo
	inimigo->dx, inimigo->dy = numeroRandom; // Define o deslocameto aleatorio do inimigo
}

int main(void)
{

	// Inicializacoes variaveis e estruturas:

	TIPO_INIMIGO inimigo[MAX_INIMIGOS]; // Elemento da estrutura structInimigo

	TIPO_PLAYER player; // Elemento da estrutura structPlayer

	int posRandom = (rand() % 40) * LADO; // Posição aleatoria do quadrado multiplo de 20, 0 - 800.

	// Eixos de locomoção do quadrado, iniciar em posicao randomica quadrado 1.
	int posx = posRandom;
	int posy = posRandom;

	// Inicializacoes rayLib
	InitWindow(LARGURA, ALTURA, "O Jogo"); // Inicializa janela com certo tamanho e titulo.
	centerWindow(LARGURA, ALTURA);		   // Centraliza a janela do jogo ao centro da tela.
	SetTargetFPS(60);					   // Ajusta a execucao do jogo para 60 frames por segundo.

	// Laco principal do jogo
	while (!WindowShouldClose()) // Detectar o botao de fechar janela ou a tecla ESC
	{

		// Atualiza a representacao visual a partir do estado do jogo:

		// Trata entrada do usuario e atualiza estado do jogo.
		if (IsKeyPressed(KEY_RIGHT) || IsKeyDown(KEY_RIGHT)) // Verifica tecla pressionada e a tecla segurada
		{
			if (deveMover(posx, posy, 1, 0))
				move(1, 0, &posx, &posy);
		}

		if (IsKeyPressed(KEY_LEFT) || IsKeyDown(KEY_LEFT))
		{
			if (deveMover(posx, posy, -1, 0))
				move(-1, 0, &posx, &posy);
		}

		if (IsKeyPressed(KEY_UP) || IsKeyDown(KEY_UP))
		{
			if (deveMover(posx, posy, 0, -1))
				move(0, -1, &posx, &posy);
		}

		if (IsKeyPressed(KEY_DOWN) || IsKeyDown(KEY_DOWN))
		{
			if (deveMover(posx, posy, 0, 1))
				move(0, 1, &posx, &posy);
		}

		// Mostrar informacoes visuais para o usuario:

		BeginDrawing(); // Inicia o ambiente de desenho na tela

		ClearBackground(BACKGROUND_COLOR); // Limpa a tela e define cor de fundo

		// Inicializacao dos inimigos na tela
		for (int i = 0; i < MAX_INIMIGOS; i++)
		{

			posicaoAleatoriaInimigo(&inimigo[i]); // Inicializacao do inimigo em posicao e sentido aleatorios

			// Verifica se o sentido de movimento eh valido
			if (moveInimigo(&inimigo[i]))
				DrawRectangle(inimigo[i].x, inimigo[i].y, LADO, LADO, ORANGE); // Desenha quadrado inimigo
			// Se nao, redefine o deslocamento do inimigo para um sentido valido
			else
				redefineDeslocamentoInimigo(&inimigo[i]);
		}

		DrawRectangle(posx, posy, LADO, LADO, GREEN); // Posição do quadrado 1, player

		EndDrawing(); // Finaliza o ambiente de desenho na tela
	}

	CloseWindow(); // Fecha a janela e o contexto OpenGL

	return 0;
}

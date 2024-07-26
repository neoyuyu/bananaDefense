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

// Estruturas definicao

// Estrutura StructPlayer representa o jogador do jogo
typedef struct structPlayer
{

	int dx; // Deslocamento posicao x
	int x;	// Coordenada x no mapa

	int dy; // Deslocamento posicao y
	int y;	// Coordenada y no mapa
} TIPO_PLAYER;

// Estrutura StructInimigo representa os inimigos do jogo
typedef struct structInimigo
{

	int dx; // Deslocamento posicao x
	int x;	// Coordenada x no mapa

	int dy; // Deslocamento posicao y
	int y;	// Coordenada y no mapa

} TIPO_INIMIGO;

// Funcao que move a estrutura recebida
void move(int dx, int dy, int *x, int *y)
{
	if (dx == 1)
		*x += 20;

	if (dx == -1)
		*x -= 20;

	if (dy == 1)
		*y += 20;

	if (dy == -1)
		*y -= 20;
}

// Funcao que verifica se a estrutura deve mover
int deveMover(int x, int y, int dx, int dy)
{

	// Verifica eixo x, está fora dos limites (LARGURA X ALTURA)
	if ((dx == 1 && x + LADO > LARGURA - LADO) || (dx == -1 && x - LADO < 0))
		return 0;
	// Verifica eixo y, está fora dos limites (LARGURA X ALTURA)
	if ((dy == 1 && y + LADO > ALTURA - LADO) || (dy == -1 && y - LADO < 0))
		return 0;

	return 1;
}

// Logica para fazer estrutura inimigo se movimentar
int moveInimigo(TIPO_INIMIGO i)
{
	// srand(time(NULL)); // seed atrelada ao tempo do computador, deixa mais devagar

	// Gera um aleatorio entre 0 e 2
	int deslocaRandom = rand() % 3;

	// Mapeia o resultado desse número entre -1 e 1 quando subtrai 1
	int numeroRandom = deslocaRandom - 1;
	printf("%d", numeroRandom);

	// Variaveis de deslocamento do inimigo
	int desIniX = numeroRandom;
	int desIniY = numeroRandom;

	// Parar o inimigo caso ele bata na parede
	if (!deveMover(*x, *y, desIniX, desIniY))
	{
	}

	else
		move(desIniX, desIniY, x, y);
}

int main(void)
{

	// Inicializacoes variaveis e estruturas

	TIPO_INIMIGO inimigo[MAX_INIMIGOS]; // Inicializacao do vetor de inimigos

	TIPO_PLAYER player; // Inicialização da estrutura player

	// srand(time(NULL)); // seed atrelada ao tempo do computador

	int posRandom = (rand() % 40) * LADO; // Posição aleatoria do quadrado multiplo de 20, 0 - 800

	// Eixos de locomoção do quadrado, iniciar em posicao randomica quadrado 1
	int posx = posRandom;
	int posy = posRandom;

	int posRandom2;

	for (int i = 0; i < MAX_INIMIGOS; i++)
	{

		posRandom2 = (rand() % 40) * LADO; // Posição aleatoria do quadrado multiplo de 20, 0 - 800
		printf("\n %d", posRandom2);
		inimigo[i].x, inimigo[i].y = posRandom2;
	}

	// Inicializacoes rayLib
	InitWindow(LARGURA, ALTURA, "O Jogo"); // Inicializa janela, com certo tamanho e titulo
	centerWindow(LARGURA, ALTURA);		   // Centraliza a janela do jogo ao centro da tela
	SetTargetFPS(60);					   // Ajusta a execucao do jogo para 60 frames por segundo

	// Laco principal do jogo
	while (!WindowShouldClose()) // Detect window close button or ESC key
	{

		// Atualiza a representacao visual a partir do estado do jogo

		// Trata entrada do usuario e atualiza estado do jogo
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

		// deslocaInimigo(&posx, &posy);

		BeginDrawing(); // Inicia o ambiente de desenho na tela

		ClearBackground(BACKGROUND_COLOR); // Limpa a tela e define cor de fundo

		// Inicializacao dos inimigos e mostrar na tela sua posicao aleatoria
		for (int i = 0; i < MAX_INIMIGOS; i++)
		{

			DrawRectangle(inimigo[i].x, inimigo[i].y, LADO, LADO, ORANGE); // Quadrados inimigos
		}

		DrawRectangle(posx, posy, LADO, LADO, GREEN); // Posição do quadrado 1, player

		EndDrawing(); // Finaliza o ambiente de desenho na tela
	}

	CloseWindow(); // Fecha a janela e o contexto OpenGL

	return 0;
}

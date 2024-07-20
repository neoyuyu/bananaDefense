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
#define BACKGROUND_COLOR \
	(Color) { 60, 3, 32, 100 } // Light Gray

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

int deveMover(int x, int y, int dx, int dy)
{

	// int deslocaRandom = (rand() % 2) * -1 ; //Gera aleatorio entre -1 e 1

	if (dx == 1 && x + 20 > 800 - LADO)
		return 0;

	if (dx == -1 && x - 20 < 0)
		return 0;

	printf("\n y eh %d", y);
	if (dy == 1 && y + 20 > 800 - 20)
		return 0;

	if (dy == -1 && y - 20 <= 0)
		return 0;

	return 1;
}

int main(void)
{

	// bool ehDentroTela = true;

	srand(time(NULL)); // seed atrelada ao tempo do computador

	int posRandom = (rand() % 40) * 20; // Posição aleatoria do quadrado multiplo de 20, 0 - 800

	// Eixos de locomoção do quadrado, iniciar em posicao randomica quadrado 1
	int posx = posRandom;
	int posy = posRandom;

	// //Eixos de locomoção do quadrado, iniciar em posicao randomica quadrado 2
	// int posx2 = posRandom;
	// int posy2 = posRandom;

	// Ponteiros para deslocamento
	// int *pontX = posx;
	// int *pontY = posy;

	// Inicializacoes rayLib
	InitWindow(LARGURA, ALTURA, "O Jogo"); // Inicializa janela, com certo tamanho e titulo
	centerWindow(LARGURA, ALTURA);
	SetTargetFPS(60); // Ajusta a execucao do jogo para 60 frames por segundo

	// Laco principal do jogo
	while (!WindowShouldClose()) // Detect window close button or ESC key
	{

		// Atualiza a representacao visual a partir do estado do jogo

		// Trata entrada do usuario e atualiza estado do jogo
		if (IsKeyPressed(KEY_RIGHT) || IsKeyDown(KEY_RIGHT)) // Verifica tecla pressionada e a tecla segurada
		{
			if (deveMover(posx, posy, 1, 0) == 1)
			{
				move(1, 0, &posx, &posy);
			}
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

		BeginDrawing(); // Inicia o ambiente de desenho na tela

		ClearBackground(BACKGROUND_COLOR); // Limpa a tela e define cor de fundo

		DrawRectangle(posx, posy, LADO, LADO, GREEN); // Posição do quadrado 1

		// DrawRectangle(posx, posy, LADO, LADO, RED);	//Posição do quadrado 2

		EndDrawing(); // Finaliza o ambiente de desenho na tela
	}

	CloseWindow(); // Fecha a janela e o contexto OpenGL

	return 0;
}

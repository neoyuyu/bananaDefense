#include "raylib.h"
#include "../include/funcoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

// Definição de cores para uso em todo o programa
#define COLOR_WHITE \
	(Color) { 255, 255, 255, 255 }

int main(void)
{
	srand(time(NULL)); // Inicializa a semente dinamicamente

	// Leitura do arquivo de fases
	GAMESTATUS estadoDoJogo;
	estadoDoJogo.nivel = '0';
	char fase[30] = {};
	// Faz com que o jogo leia o arquivo da fase correspondente ao nivel
	strcpy(fase, "src/fases/mapa");		   // Copia o nome do arquivo para a variavel
	strncat(fase, &estadoDoJogo.nivel, 1); // Concatena o nome do arquivo com o nivel
	strcat(fase, ".txt");				   // Concatena o nome do arquivo com a extensao

	// Informações sobre o jogo
	char matriz[ALTURA / LADO][LARGURA / LADO] = {}; // Esta matriz representa o mapa do jogo
	int recursosColetados = 0;						 // Recursos coletados pelo jogador
	int qtdInimigos = 0;							 // Quantidade de inimigos lidos no mapa
	BASE base;										 // Base do jogador
	GAMESCREEN telaAtual = MENU;					 // Tela inicial do jogo
	int contadorFrames = 0;							 // Contador de frames

	// Inicializar o player pela primeira vez
	TIPO_PLAYER player;
	inicializaPlayer(&player); // Inicializa o player com valores base

	// Inicializar os inimigos pela primeira vez
	TIPO_INIMIGO inimigo[MAX_INIMIGOS] = {}; // Arranjo de inimigos da estrutura TIPO_INIMIGO
	for (int i = 0; i < MAX_INIMIGOS; i++)
	{
		inicializaInimigo(&inimigo[i]);
	}

	// Inicializacoes rayLib
	InitWindow(LARGURA, ALTURA, "Defense"); // Inicializa janela com certo tamanho e titulo
	centerWindow(LARGURA, ALTURA);			// Centraliza a janela do jogo ao centro da tela
	SetTargetFPS(60);						// Ajusta a taxa de atualizacao de quadros por segundo

	leMapa(fase, &matriz[0][0], &qtdInimigos); // Leitura do mapa

	// Laco principal do jogo
	while (!WindowShouldClose()) // Detectar o botao de fechar janela ou a tecla ESC
	{

		switch (telaAtual)
		{

		case TITULO:
		{
			// TODO: Draw TITLE screen here!
			DrawText("TITLE SCREEN", 20, 20, 40, DARKGREEN);
			DrawText("PRESS ENTER or TAP to JUMP to GAMEPLAY SCREEN", 120, 220, 20, DARKGREEN);
		}
		break;
		case GAMEPLAY:
		{
			// TODO: Draw GAMEPLAY screen here!
			DrawRectangle(0, 0, screenWidth, screenHeight, PURPLE);
			DrawText("GAMEPLAY SCREEN", 20, 20, 40, MAROON);
			DrawText("PRESS ENTER or TAP to JUMP to ENDING SCREEN", 130, 220, 20, MAROON);
		}
		break;
		case MENU:
		{
			// TODO: Draw ENDING screen here!
			DrawRectangle(0, 0, screenWidth, screenHeight, BLUE);
			DrawText("ENDING SCREEN", 20, 20, 40, DARKBLUE);
			DrawText("PRESS ENTER or TAP to RETURN to TITLE SCREEN", 120, 220, 20, DARKBLUE);
		}
		case GAMEOVER:
		{
			// TODO: Draw ENDING screen here!
			DrawText("SE LASCOU", 20, 20, 40, DARKBLUE);
			DrawText("PRESS ENTER or TAP to RETURN to TITLE SCREEN", 120, 220, 20, DARKBLUE);
		}
		break;
		default:
			break;
		}

		controleJogador(&player, &matriz[0][0]); // Verificacao dos controles do jogador

		// Mostrar informacoes visuais para o usuario:
		BeginDrawing(); // Inicia o ambiente de desenho na tela

		// ClearBackground(BACKGROUND_COLOR); // Limpa a tela e define cor de fundo

		desenhaMapa(&matriz[0][0], &player, &inimigo[0], &base); // Desenha mapa e inicializa inimigos

		// Move os inimigos
		for (int i = 0; i < qtdInimigos; i++)
		{
			moveInimigo(&inimigo[i], &matriz[0][0], &base);
		}

		recursosColetados += coletaRecursos(&player.coordPlayer, &matriz[0][0]);
		if (IsKeyPressed(KEY_G))
		{
			if (matriz[player.coordPlayer.y][player.coordPlayer.x] == ' ')
			{
				if (recursosColetados > 0)
				{
					matriz[player.coordPlayer.y][player.coordPlayer.x] = 'O';
					recursosColetados--;
				}
			}
		}
		DrawText(TextFormat("Recursos: %d", recursosColetados), 10, 10, 20, BLACK);

		EndDrawing(); // Finaliza o ambiente de desenho na tela
	}

	CloseWindow(); // Fecha a janela e o contexto OpenGL

	return 0;
}

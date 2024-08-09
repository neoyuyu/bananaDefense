#include "raylib.h"
#include "../include/funcoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

int main(void)
{
	srand(time(NULL)); //Inicializa a semente dinamicamente

	GAMESTATUS estadoDoJogo;
	estadoDoJogo.nivel = '0';
    char fase[30] = {};
    char matriz[ALTURA/LADO][LARGURA/LADO] = {};
	int recursosColetados = 0;


    strcpy(fase, "src/fases/mapa");
    strncat(fase, &estadoDoJogo.nivel, 1);
    strcat(fase, ".txt");

	// Inicializar o player
	TIPO_PLAYER player;		   // Elemento da estrutura structPlayer

	// Inicializar os inimigos
	TIPO_INIMIGO inimigo[MAX_INIMIGOS]; // Elemento da estrutura structInimigo

	BASE base;

	// Inicializacoes rayLib
	InitWindow(LARGURA, ALTURA, "O Jogo"); // Inicializa janela com certo tamanho e titulo
	centerWindow(LARGURA, ALTURA);		   // Centraliza a janela do jogo ao centro da tela
	SetTargetFPS(60);					   // Ajusta a taxa de atualizacao de quadros por segundo

	leMapa(fase, &matriz[0][0]);

	// Laco principal do jogo
	while (!WindowShouldClose()) // Detectar o botao de fechar janela ou a tecla ESC
	{

		controleJogador(&player, &matriz[0][0]); // Verificacao dos controles do jogador

		for(int i=0; i<2; i++){
			moveInimigo(&inimigo[i], &matriz[0][0], &base);
		}
		

		// Mostrar informacoes visuais para o usuario:
		BeginDrawing(); // Inicia o ambiente de desenho na tela

		//ClearBackground(BACKGROUND_COLOR); // Limpa a tela e define cor de fundo

		recursosColetados += coletaRecursos (&player.coordPlayer, matriz);
        if (IsKeyPressed(KEY_G)) {
            if (matriz[player.coordPlayer.y][player.coordPlayer.x] == ' ') {
                if (recursosColetados>0) {
                matriz[player.coordPlayer.y][player.coordPlayer.x] ='O';
                recursosColetados--;
            }
            }
        }
        DrawText(TextFormat("Recursos: %d", recursosColetados), 10, 10, 20, BLACK);
		desenhaMapa(&matriz[0][0], &player, &inimigo[0], &base);

		EndDrawing(); // Finaliza o ambiente de desenho na tela
	}

	CloseWindow(); // Fecha a janela e o contexto OpenGL

	return 0;
}

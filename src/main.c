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

    strcpy(fase, "src/fases/mapa");
    strncat(fase, &estadoDoJogo.nivel, 1);
    strcat(fase, ".txt");

	// Inicializar o player
	TIPO_PLAYER player;		   // Elemento da estrutura structPlayer

	// Inicializar os inimigos
	TIPO_INIMIGO inimigo[MAX_INIMIGOS]; // Elemento da estrutura structInimigo
	/*for (int i = 0; i < MAX_INIMIGOS; i++)
		{
			inicializaInimigo(&inimigo[i]);
		}
*/
	// Inicializacoes rayLib
	InitWindow(LARGURA, ALTURA, "O Jogo"); // Inicializa janela com certo tamanho e titulo
	centerWindow(LARGURA, ALTURA);		   // Centraliza a janela do jogo ao centro da tela
	SetTargetFPS(60);					   // Ajusta a taxa de atualizacao de quadros por segundo

	leMapa(fase, &matriz[0][0]);

	// Variável para controlar o tempo acumulado

	// Laco principal do jogo
	while (!WindowShouldClose()) // Detectar o botao de fechar janela ou a tecla ESC
	{

		controleJogador(&player, &matriz[0][0]); // Verificacao dos controles do jogador

		/*ehColisaoInimiga(inimigo); // Verifica o arranjo de inimigos para checar colisoes no inicio do jogo

		for (int i = 0; i < MAX_INIMIGOS; i++)
		{

			// Verifica se o inimigo pode se mover e desenha na tela
			if (!moveInimigo(&inimigo[i], &matriz[0][0]))
			{
				redefineDeslocamentoInimigo(&inimigo[i]);
				moveInimigo(&inimigo[i], &matriz[0][0]);
			}
		}*/

		// sentidoAleatorioInimigo(&inimigo[i]);	// Inicializa o sentido aleatorio do inimigo, não é necessário

		// Mostrar informacoes visuais para o usuario:
		BeginDrawing(); // Inicia o ambiente de desenho na tela

		ClearBackground(BACKGROUND_COLOR); // Limpa a tela e define cor de fundo

		desenhaMapa(&matriz[0][0], &player);

		/*DrawRectangle(player.coordPlayer.x * LADO, player.coordPlayer.y * LADO, LADO, LADO, player.cor); // Posição do quadrado player
		for (int i=0; i<MAX_INIMIGOS; i++){
			DrawRectangle(inimigo[i].coordInimigo.x * LADO, inimigo[i].coordInimigo.y * LADO, LADO, LADO, inimigo[i].cor); // Primeira posicao do inimigo desenhada
		}*/

		EndDrawing(); // Finaliza o ambiente de desenho na tela
	}

	CloseWindow(); // Fecha a janela e o contexto OpenGL

	return 0;
}

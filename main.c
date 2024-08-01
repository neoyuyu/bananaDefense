#include "raylib.h"
#include "include/funcoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

int main(void)
{
	srand(time(NULL)); //Inicializa a semente dinamicamente
	// Inicializar o player
	TIPO_PLAYER player;		   // Elemento da estrutura structPlayer
	inicializaPlayer(&player); // Inicializar o jogador

	// Inicializar os inimigos
	TIPO_INIMIGO inimigo[MAX_INIMIGOS] = {0}; // Elemento da estrutura structInimigo

	// Inicializacoes rayLib
	InitWindow(LARGURA, ALTURA, "O Jogo"); // Inicializa janela com certo tamanho e titulo
	centerWindow(LARGURA, ALTURA);		   // Centraliza a janela do jogo ao centro da tela
	SetTargetFPS(60);					   // Ajusta a taxa de atualizacao de quadros por segundo

	// Variável para controlar o tempo acumulado

	// Laco principal do jogo
	while (!WindowShouldClose()) // Detectar o botao de fechar janela ou a tecla ESC
	{

		// Atualiza a representacao visual a partir do estado do jogo:

		inicializaInimigo(inimigo);

		controleJogador(&player.coordPlayer.x, &player.coordPlayer.y); // Verificacao dos controles do jogador

		// ehColisaoInimiga(inimigo); // Verifica o arranjo de inimigos para checar colisoes no inicio do jogo

		for (int i = 0; i < MAX_INIMIGOS; i++)
		{

			// Verifica se o inimigo pode se mover e desenha na tela
			if (deveMover(inimigo[i].coordInimigo.x, inimigo[i].coordInimigo.y, inimigo[i].coordInimigo.dx, inimigo[i].coordInimigo.dy))
			{
				moveInimigo(&inimigo[i]);
				DrawRectangle(inimigo[i].coordInimigo.x, inimigo[i].coordInimigo.y, LADO, LADO, ORANGE); // Primeira posicao do inimigo desenhada
			}

			else
			{
				redefineDeslocamentoInimigo(&inimigo[i]);
				moveInimigo(&inimigo[i]);
			}
		}

		// sentidoAleatorioInimigo(&inimigo[i]);	// Inicializa o sentido aleatorio do inimigo, não é necessário

		// Mostrar informacoes visuais para o usuario:
		BeginDrawing(); // Inicia o ambiente de desenho na tela

		ClearBackground(BACKGROUND_COLOR); // Limpa a tela e define cor de fundo

		DrawRectangle(player.coordPlayer.x, player.coordPlayer.y, LADO, LADO, GREEN); // Posição do quadrado player

		EndDrawing(); // Finaliza o ambiente de desenho na tela
	}

	CloseWindow(); // Fecha a janela e o contexto OpenGL

	return 0;
}

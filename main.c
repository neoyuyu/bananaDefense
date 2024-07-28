#include "raylib.h"
#include "include/funcoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

int main(void)
{
	srand(time(NULL));
	// Inicializacoes variaveis e estruturas:

	TIPO_INIMIGO inimigo[MAX_INIMIGOS]; // Elemento da estrutura structInimigo

	TIPO_PLAYER player; // Elemento da estrutura structPlayer

	// Gerar um número aleatório no intervalo de 0 a 38
	int random = rand() % 39;

	// Calcular o múltiplo de 20 correspondente
	int randomMultiplo = (random * 20) + 20;

	// Eixos de locomoção do quadrado, iniciar em posicao randomica quadrado 1.
	int posx = randomMultiplo;
	int posy = randomMultiplo;

	// Inicializacoes rayLib
	InitWindow(LARGURA, ALTURA, "O Jogo"); // Inicializa janela com certo tamanho e titulo.
	centerWindow(LARGURA, ALTURA);		   // Centraliza a janela do jogo ao centro da tela.
	SetTargetFPS(60);					   // Ajusta a execucao do jogo para 60 frames por segundo.

	// Inicializar os inimigos
	for (int i = 0; i < MAX_INIMIGOS; i++)
	{

		posicaoAleatoriaInimigo(&inimigo[i]); // Inicializacao do inimigo em posicao aleatoria
		sentidoAleatorioInimigo(&inimigo[i]); // Inicalizacao do primeiro deslocamento do inimigo
	}
	// Laco principal do jogo
	while (!WindowShouldClose()) // Detectar o botao de fechar janela ou a tecla ESC
	{
		// Atualiza a representacao visual a partir do estado do jogo:

		controleJogador(&posx, &posy);

		// Mostrar informacoes visuais para o usuario:

		BeginDrawing(); // Inicia o ambiente de desenho na tela

		ClearBackground(BACKGROUND_COLOR); // Limpa a tela e define cor de fundo

		// Inicializacao dos inimigos na tela
		for (int i = 0; i < MAX_INIMIGOS; i++)
		{

			// ehColisaoInimiga(&inimigo);

			// Verificação para evitar que inimigos ocupem o mesmo espaço
			for (int i = 0; i < MAX_INIMIGOS; i++)
			{
				for (int j = (i + 1); j < MAX_INIMIGOS; j++)
				{
					if ((inimigo[i].x == inimigo[j].x) && (inimigo[i].y == inimigo[j].y))
					{
						redefineDeslocamentoInimigo(&inimigo[j]);
						// break;
					}
				}
			}

			//  Verifica se o sentido de movimento eh valido, dentro da tela
			if (moveInimigo(&inimigo[i]))
				DrawRectangle(inimigo[i].x, inimigo[i].y, LADO, LADO, ORANGE); // Desenha quadrado inimigo
			// Se nao, redefine o deslocamento do inimigo para um sentido valido
			else
			{
				redefineDeslocamentoInimigo(&inimigo[i]);
			}

			// Novo sentido aleatorio do inimigo
			// sentidoAleatorioInimigo(&inimigo[i]);
		}

		DrawRectangle(posx, posy, LADO, LADO, GREEN); // Posição do quadrado player

		EndDrawing(); // Finaliza o ambiente de desenho na tela
	}

	CloseWindow(); // Fecha a janela e o contexto OpenGL

	return 0;
}

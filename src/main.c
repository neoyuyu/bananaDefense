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
	estadoDoJogo.nivel = '1';
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
	GAMESCREEN telaAtual = TITULO;					 // Tela inicial do jogo
	int contadorFrames = 0;							 // Contador de frames

	int deveFechar = 0; // Variavel para fechar o jogo

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

	// Carregar textura do jogo
	Image imagemTitulo = LoadImage("src/resources/images/jungle.png"); // Loaded in CPU memory (RAM)
	Texture2D texturaTitulo = LoadTextureFromImage(imagemTitulo);	   // Image converted to texture, GPU memory (VRAM)
	UnloadImage(imagemTitulo);										   // Once image has been converted to texture and uploaded to VRAM, it can be unloaded from RAM

	leMapa(fase, &matriz[0][0], &qtdInimigos); // Leitura do mapa

	// Laco principal do jogo
	while (!deveFechar) // Detectar quando o jogador fecha a janela
	{

		controleJogador(&player, &matriz[0][0]); // Verificacao dos controles do jogador

		verificaTelaJogo(&telaAtual, &deveFechar); // Verifica a tela atual do jogo e muda conforme a tecla pressionada

		//----------------------------------------------------------------------------------
		// Mostrar informacoes visuais para o usuario:
		//----------------------------------------------------------------------------------
		BeginDrawing(); // Inicia o ambiente de desenho na tela

		ClearBackground(RAYWHITE); // Limpa a tela e define cor de fundo

		switch (telaAtual)
		{

		case GAMEPLAY:
		{

			desenhaMapa(&matriz[0][0], &player, &inimigo[0], &base); // Desenha mapa e inicializa inimigos

			// Move os inimigos
			for (int i = 0; i < qtdInimigos; i++)
			{
				moveInimigo(&inimigo[i], &matriz[0][0], &base);
			}


			if (IsKeyPressed(KEY_G))
			{
					if (player.recursos > 0)
					{
						matriz[player.coordPlayer.y][player.coordPlayer.x] = 'O';
						player.recursos--;
					}
			}
			DrawText(TextFormat("Recursos: %d", player.recursos), 10, 10, 20, BLACK);
		}
		break;

		case TITULO:
		{
			DrawTexture(texturaTitulo, LARGURA / 2 - texturaTitulo.width / 2, ALTURA / 2 - texturaTitulo.height / 2, WHITE);
			DrawText("N - Novo Jogo", LARGURA / 2 - 200, ALTURA / 2 - 80, 50, RAYWHITE);
			DrawText("C - Carregar Jogo", LARGURA / 2 - 200, ALTURA / 2 - 5, 50, RAYWHITE);
			DrawText("Q - Sair do Jogo", LARGURA / 2 - 200, ALTURA / 2 - -70, 50, RAYWHITE);
			DrawText("O - Mais", LARGURA / 2 - 200, ALTURA / 2 - -145, 50, RAYWHITE);
		}
		break;

		case MENU:
		{

			DrawTexture(texturaTitulo, LARGURA / 2 - texturaTitulo.width / 2, ALTURA / 2 - texturaTitulo.height / 2, WHITE);
			DrawText("MENU", 20, 20, 40, DARKBLUE);
			DrawText("C - Continuar", LARGURA / 2 - 200, ALTURA / 2 - 80, 50, RAYWHITE);
			DrawText("L - Carregar Jogo", LARGURA / 2 - 200, ALTURA / 2 - 5, 50, RAYWHITE);
			DrawText("S - Salvar Jogo", LARGURA / 2 - 200, ALTURA / 2 + 70, 50, RAYWHITE);
			DrawText("V - Voltar ao Menu", LARGURA / 2 - 200, ALTURA / 2 + 145, 50, RAYWHITE);
			DrawText("F - Sair", LARGURA / 2 - 200, ALTURA / 2 + 220, 50, RAYWHITE);
		}
		break;
		case GAMEOVER:
		{

			DrawRectangle(0, 0, LARGURA, ALTURA, BLACK); // Fundo da tela de game over
			DrawText("SE LASCOU", LARGURA / 2 - 270, ALTURA / 2 - 250, 100, RAYWHITE);
			DrawText("C - Carrega Jogo", LARGURA / 2 - 225, ALTURA / 2 - 100, 50, RED);
			DrawText("R - Reiniciar Jogo", LARGURA / 2 - 225, ALTURA / 2 - 150, 50, RED);
			DrawText("V - Voltar ao Menu", LARGURA / 2 - 225, ALTURA / 2 - 50, 50, RED);
		}
		break;
		case VITORIA:
		{

			DrawRectangle(0, 0, LARGURA, ALTURA, GREEN); // Fundo da tela de vitoria
			DrawText("VITORIA", LARGURA / 2 - 270, ALTURA / 2 - 150, 100, RAYWHITE);
			DrawText("Pressione enter para ir ao título", LARGURA / 2 - 400, ALTURA / 2 - 50, 50, RED);
		}

		default:
			break;
		}

		EndDrawing(); // Finaliza o ambiente de desenho na tela
	}

	// Descarregar texturas
	UnloadTexture(texturaTitulo); // Descarrega a textura da tela de titulo

	CloseWindow(); // Fecha a janela e o contexto OpenGL

	return 0;
}

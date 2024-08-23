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
	estadoDoJogo.gamescreen = TITULO; // Tela inicial do jogo

	char fase[30] = {}; // Nome do arquivo de fases

	// Informações sobre o jogo
	char matriz[ALTURA / LADO][LARGURA / LADO] = {}; // Esta matriz representa o mapa do jogo
	int recursosColetados = 0;						 // Recursos coletados pelo jogador
	int qtdInimigos = 0;							 // Quantidade de inimigos lidos no mapa, eh alterado conforme o jogador elimina os inimigos

	int deveFechar = 0; // Variavel para fechar o jogo

	TIPO_PLAYER player; // Estrutura do jogador

	BASE base; // Estrutura da base

	TIPO_INIMIGO inimigo[MAX_INIMIGOS] = {}; // Arranjo de inimigos da estrutura TIPO_INIMIGO

	inicializaNivel(&matriz[0][0], &fase[0], &estadoDoJogo, inimigo, &player, &base, &qtdInimigos); // Inicializa o nivel do jogo com valores padrao

	// Inicializacoes rayLib
	InitWindow(LARGURA, ALTURA, "Banana Defense"); // Inicializa janela com certo tamanho e titulo
	centerWindow(LARGURA, ALTURA);				   // Centraliza a janela do jogo ao centro da tela
	SetTargetFPS(60);							   // Ajusta a taxa de atualizacao de quadros por segundo

	// Carregamento da textura do jogo
	Image imagemTitulo = LoadImage("src/resources/images/jungle.png"); // Loaded in CPU memory (RAM)
	Texture2D texturaTitulo = LoadTextureFromImage(imagemTitulo);	   // Image converted to texture, GPU memory (VRAM)
	UnloadImage(imagemTitulo);										   // Once image has been converted to texture and uploaded to VRAM, it can be unloaded from RAM

	// Laco principal do jogo
	while (!deveFechar && !WindowShouldClose()) // Detectar quando o jogador fecha a janela
	{

		if (ehTelaVitoria(&qtdInimigos)) // Verifica a quantidade de inimigos para mudar a tela de vitoria
		{
			estadoDoJogo.gamescreen = VITORIA;
			qtdInimigos = 1; // Reseta a quantidade de inimigos
		}
		controleJogador(&player, &matriz[0][0]); // Verificacao dos controles do jogador

		verificaTelaJogo(&matriz[0][0], &estadoDoJogo.gamescreen, &deveFechar, &estadoDoJogo, fase, inimigo, &player, &base, &qtdInimigos); // Verifica a tela atual do jogo e muda conforme a tecla pressionada

		verificaVidas(&base, &player, &estadoDoJogo.gamescreen); // Verifica as vidas do jogador e da base

		//----------------------------------------------------------------------------------
		// Mostrar informacoes visuais para o usuario:
		//----------------------------------------------------------------------------------
		BeginDrawing(); // Inicia o ambiente de desenho na tela

		ClearBackground(RAYWHITE); // Limpa a tela e define cor de fundo

		switch (estadoDoJogo.gamescreen)
		{

		case GAMEPLAY: // Tela de jogo principal
		{

			desenhaMapa(&matriz[0][0], &player, &inimigo[0], &base); // Desenha mapa e inicializa inimigos

			// Move os inimigos
			for (int i = 0; i < MAX_INIMIGOS; i++)
			{
				if (inimigo[i].vidas > 0)												   // Verifica se o inimigo ainda esta vivo
					moveInimigo(&inimigo[i], &player, &matriz[0][0], &base, &qtdInimigos); // Move o inimigo no mapa
			}

			if (IsKeyPressed(KEY_G)) // Coleta recursos
			{
				if (player.recursos > 0) // Verifica se o jogador tem recursos
				{
					matriz[player.coordPlayer.y][player.coordPlayer.x] = 'O';
					player.recursos--;
				}
			}

			DrawText(TextFormat("Recursos: %d", player.recursos), 10, 3, 25, BLACK);   // Exibe a quantidade de recursos coletados
			DrawText(TextFormat("Vidas P: %d", player.vidas), 186, 3, 25, BLACK);	   // Exibe a quantidade de vidas do jogador
			DrawText(TextFormat("Vidas B: %d", base.vidas), 346, 3, 25, BLACK);		   // Exibe a quantidade de vidas da base
			DrawText(TextFormat("Inimigos: %d", qtdInimigos), 890, 3, 25, BLACK);	   // Exibe a quantidade de vidas da base
			DrawText(TextFormat("Nivel: %c", estadoDoJogo.nivel), 1050, 3, 25, BLACK); // Exibe a quantidade de vidas da base
		}
		break;

		case TITULO: // Tela de titulo do jogo, onde o jogador pode iniciar o jogo
		{
			DrawTexture(texturaTitulo, LARGURA / 2 - texturaTitulo.width / 2, ALTURA / 2 - texturaTitulo.height / 2, WHITE);
			DrawText("N - Novo Jogo", LARGURA / 2 - 200, ALTURA / 2 - 80, 50, RAYWHITE);
			DrawText("L - Carregar Jogo", LARGURA / 2 - 200, ALTURA / 2 - 5, 50, RAYWHITE);
			DrawText("Q - Sair do Jogo", LARGURA / 2 - 200, ALTURA / 2 - -70, 50, RAYWHITE);
			DrawText("O - Mais", LARGURA / 2 - 200, ALTURA / 2 - -145, 50, RAYWHITE);
		}
		break;

		case MENU: // Tela de menu ou pause, onde o jogador pode retornar ao titulo e outros
		{

			DrawTexture(texturaTitulo, LARGURA / 2 - texturaTitulo.width / 2, ALTURA / 2 - texturaTitulo.height / 2, WHITE);
			DrawText("MENU", 20, 20, 40, DARKBLUE);
			DrawText("C - Continuar", LARGURA / 2 - 200, ALTURA / 2 - 80, 50, RAYWHITE);
			DrawText("L - Carregar Jogo", LARGURA / 2 - 200, ALTURA / 2 - 5, 50, RAYWHITE);
			DrawText("S - Salvar Jogo", LARGURA / 2 - 200, ALTURA / 2 + 70, 50, RAYWHITE);
			DrawText("V - Voltar ao Menu", LARGURA / 2 - 200, ALTURA / 2 + 145, 50, RAYWHITE);
		}
		break;
		case GAMEOVER: // Tela de game over, onde o jogador pode retornar ao titulo e outros
		{

			DrawRectangle(0, 0, LARGURA, ALTURA, BLACK); // Fundo da tela de game over
			DrawText("SE LASCOU", LARGURA / 2 - 270, ALTURA / 2 - 250, 100, RAYWHITE);
			DrawText("L - Carrega Jogo", LARGURA / 2 - 225, ALTURA / 2 - 100, 50, RED);
			DrawText("R - Reiniciar Jogo", LARGURA / 2 - 225, ALTURA / 2 - 150, 50, RED);
			DrawText("V - Voltar ao Menu", LARGURA / 2 - 225, ALTURA / 2 - 50, 50, RED);
		}
		break;
		case VITORIA: // Tela de vitoria, onde o jogador pode retornar ao titulo e outros
		{

			DrawRectangle(0, 0, LARGURA, ALTURA, GREEN); // Fundo da tela de vitoria
			DrawText("VITORIA", LARGURA / 2 - 270, ALTURA / 2 - 150, 100, RAYWHITE);
			DrawText("N - Proximo Nivel", LARGURA / 2 - 225, ALTURA / 2 - 50, 50, RED);
			DrawText("R - Reiniciar Nível", LARGURA / 2 - 225, ALTURA / 2, 50, RED);
			DrawText("V - Voltar ao Menu", LARGURA / 2 - 225, ALTURA / 2 + 50, 50, RED);
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
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <float.h>
#include "../include/funcoes.h"

// Funcao que atribui os valores iniciais ao player
void inicializaPlayer(TIPO_PLAYER *player)
{
    player->vidas = 1;        // Inicializa a vida do player
    player->cor = GREEN;      // Atribui cor ao player
    player->letra = 'J';      // Letra que representa o player
    player->recursos = 0;     // Inicializa a quantidade de recursos coletados
    player->delayTempo = 0.2; // Delay para movimentacao do player
    player->timerDelay = 0;   // Inicializa o timer do player
}

// Funcao que atribui os valores inciciais ao inimigo
void inicializaInimigo(TIPO_INIMIGO *inimigo)
{
    inimigo->vidas = 1;   // Inicializa a vida do inimigo
    inimigo->cor = RED;   // Atribui cor ao inimigo
    inimigo->letra = 'M'; // Letra que representa o inimigo
    inimigo->timer = 0;   // Inicializa o timer do inimigo

    // Atribui os ultimos valores de movimento do inimigo
    inimigo->ultimoMovimentoX = 0;
    inimigo->ultimoMovimentoY = 0;
    inimigo->coordInimigo.dx = 0; // Inicializa o deslocamento x do inimigo
    inimigo->coordInimigo.dy = 0; // Inicializa o deslocamento y do inimigo
}

// Funcao que inicializa a base pela primeira vez
void inicializaBase(BASE *base)
{
    base->vidas = 3;  // Inicializa a vida da base
    base->cor = BLUE; // Atribui cor a base
}
// Funcao que verifica a quantidade de vidas da base e do player
void verificaVidas(BASE *base, TIPO_PLAYER *player, GAMESCREEN *tela)
{
    if (base->vidas == 0 || player->vidas == 0)
    {
        *tela = GAMEOVER;
    }
}

// Funcao que desenha o player na tela
void desenhaPlayer(TIPO_PLAYER *player, int posx, int posy)
{
    player->cor = GREEN; // Atribui cor ao player
    player->letra = 'J'; // Letra que representa o player

    // Coordenadas do player sao atribuidas
    player->coordPlayer.x = posx;
    player->coordPlayer.y = posy;

    DrawRectangle(player->coordPlayer.x * LADO, player->coordPlayer.y * LADO, LADO, LADO, player->cor); // Desenha player
}

// Funcao que desenha o inimigo na tela
void desenhaInimigo(TIPO_INIMIGO *inimigo, int posx, int posy)
{

    // Coordenadas do inimigo sao atribuidas
    inimigo->coordInimigo.x = posx;
    inimigo->coordInimigo.y = posy;
    DrawRectangle(inimigo->coordInimigo.x * LADO, inimigo->coordInimigo.y * LADO, LADO, LADO, inimigo->cor); // Desenha inimigo
}

void contaRecursos(TIPO_PLAYER *player)
{
    (player->recursos)++;
}

// Funcao que verifica se a entidade deve mover. Retorna 1 se deve mover, 0 se nao deve mover
int deveMoverPlayer(TIPO_PLAYER *entidade, char *matriz)
{
    int posInicialX = entidade->coordPlayer.x;
    int posInicialY = entidade->coordPlayer.y;
    double tempoAtual = GetTime(); // Captura o tempo atual

    double timerPlayer = entidade->timerDelay; // Captura o timer do inimigo

    // Se o tempo decorrido desde o ultimo movimento inimigo for maior ou igual ao delay
    if (tempoAtual - timerPlayer < entidade->delayTempo)
    {
        return 0;
    }
    else
    {
        entidade->timerDelay = tempoAtual; // Atualiza o timer do inimigo para o tempo atual

        // Verifica se a entidade está dentro dos limites da tela
        if (entidade->coordPlayer.x == (LARGURA / LADO - 1) && entidade->coordPlayer.dx == 1)
            return 0;
        if (entidade->coordPlayer.x == 0 && entidade->coordPlayer.dx == -1)
            return 0;
        if (entidade->coordPlayer.y == (ALTURA / LADO - 1) && entidade->coordPlayer.dy == 1)
            return 0;
        if (entidade->coordPlayer.y == 0 && entidade->coordPlayer.dy == -1)
            return 0;

        // Verifica se a entidade está parada
        if (entidade->coordPlayer.dx == 0 && entidade->coordPlayer.dy == 0)
            return 0;

        // Verifica se entidade está em movimento diagonal
        if (entidade->coordPlayer.dx != 0 && entidade->coordPlayer.dy != 0)
            return 0;

        // Verifica se a entidade colidiu com algum obstaculo
        if (*(matriz + (entidade->coordPlayer.x + entidade->coordPlayer.dx) + (entidade->coordPlayer.y + entidade->coordPlayer.dy) * (LARGURA / LADO)) == 'W')
        {
            return 0;
        }
        if (*(matriz + (entidade->coordPlayer.x + entidade->coordPlayer.dx) + (entidade->coordPlayer.y + entidade->coordPlayer.dy) * (LARGURA / LADO)) == 'M')
        {
            entidade->vidas--; // Jogador perde vida por tentar passar por inimigo
            return 0;
        }
        if (*(matriz + (entidade->coordPlayer.x + entidade->coordPlayer.dx) + (entidade->coordPlayer.y + entidade->coordPlayer.dy) * (LARGURA / LADO)) == 'S')
            return 0;

        if (*(matriz + (entidade->coordPlayer.x + entidade->coordPlayer.dx) + (entidade->coordPlayer.y + entidade->coordPlayer.dy) * (LARGURA / LADO)) == 'O')
            return 0;

        if (*(matriz + (entidade->coordPlayer.x + entidade->coordPlayer.dx) + (entidade->coordPlayer.y + entidade->coordPlayer.dy) * (LARGURA / LADO)) == 'R')
        {
            contaRecursos(entidade);
        }

        if (*(matriz + (entidade->coordPlayer.x + entidade->coordPlayer.dx) + (entidade->coordPlayer.y + entidade->coordPlayer.dy) * (LARGURA / LADO)) == 'H')
        {
            int vaix = entidade->coordPlayer.x;
            int vaiy = entidade->coordPlayer.y;
            int i;

            // Deslocamento no eixo Y
            if (entidade->coordPlayer.dy == 1 || entidade->coordPlayer.dy == -1)
            {
                if (entidade->coordPlayer.dy == -1)
                {
                    for (i = entidade->coordPlayer.y - 1; i >= 0; i--)
                    {
                        if (matriz[i * (LARGURA / LADO) + entidade->coordPlayer.x] == 'H')
                        {
                            vaiy = i;
                            matriz[i * (LARGURA / LADO) - entidade->coordPlayer.x] = ' ';
                        }
                    }
                }
                else if (entidade->coordPlayer.dy == 1)
                {
                    for (i = entidade->coordPlayer.y + 1; i < ALTURA / LADO; i++)
                    {
                        if (matriz[i * (LARGURA / LADO) + entidade->coordPlayer.x] == 'H')
                        {
                            vaiy = i;
                            matriz[i * (LARGURA / LADO) - entidade->coordPlayer.x] = ' ';
                        }
                    }
                }
            }

            // Deslocamento no eixo X
            if (entidade->coordPlayer.dx == 1 || entidade->coordPlayer.dx == -1)
            {
                if (entidade->coordPlayer.dx == 1)
                {
                    for (i = entidade->coordPlayer.x + 1; i < LARGURA / LADO; i++)
                    {
                        if (matriz[entidade->coordPlayer.y * (LARGURA / LADO) + i] == 'H')
                        {
                            vaix = i;
                            matriz[entidade->coordPlayer.y * (LARGURA / LADO) - i] = ' ';
                        }
                    }
                }
                else if (entidade->coordPlayer.dx == -1)
                {
                    for (i = entidade->coordPlayer.x - 1; i >= 0; i--)
                    {
                        if (matriz[entidade->coordPlayer.y * (LARGURA / LADO) + i] == 'H')
                        {
                            vaix = i;
                            matriz[entidade->coordPlayer.y * (LARGURA / LADO) - i] = ' ';
                        }
                    }
                }
            }

            *(matriz + posInicialY * (LARGURA / LADO) + posInicialX) = ' ';
            entidade->coordPlayer.y = vaiy;
            entidade->coordPlayer.x = vaix;
        }
        else
        {
            *(matriz + (entidade->coordPlayer.y + entidade->coordPlayer.dy) * (LARGURA / LADO) + (entidade->coordPlayer.x + entidade->coordPlayer.dx)) = 'J';
        }
    }
    return 1;
}
// Função para calcular a distância entre uma entidade e a base
float distanciaAteBase(COORDENADAS *entidade, BASE *base)
{
    int distanciaX = abs(entidade->x - base->coordBase.x);
    int distanciaY = abs(entidade->y - base->coordBase.y);
    return (float)hypot(distanciaX, distanciaY);
}

void processarInimigos(TIPO_INIMIGO *inimigos, int quantidadeInimigos, TIPO_PLAYER *player, char *matriz, BASE *base, int *qtdInimigo)
{
    int i = 0;

    while (i < quantidadeInimigos)
    {
        TIPO_INIMIGO *inimigoAtual = &inimigos[i];

        // Processa o inimigo
        moveInimigo(inimigoAtual, player, matriz, base, qtdInimigo);

        // Remove inimigo se colidir com um obstáculo
        if (inimigoAtual->vidas <= 0)
        {
            // Move todos os inimigos posteriores para preencher a lacuna
            for (int j = i; j < quantidadeInimigos - 1; j++)
            {
                inimigos[j] = inimigos[j + 1];
            }

            // Atualiza a quantidade de inimigos
            quantidadeInimigos--;
            *qtdInimigo = quantidadeInimigos;

            // Não incrementa i para verificar a nova posição do inimigo na posição atual
        }
        else
        {
            i++; // Só avança se o inimigo não foi removido
        }
    }
}

// Função que verifica se a entidade deve mover. Retorna 1 se deve mover, 0 se não deve mover
int deveMoverInimigo(TIPO_INIMIGO *inimigo, TIPO_PLAYER *player, char *matrizTemporaria, BASE *base, int *qtdInimigo)
{
    // Verifica se a entidade está dentro dos limites da tela
    if (inimigo->coordInimigo.x == (LARGURA / LADO - 1) && inimigo->coordInimigo.dx == 1)
        return 0;
    if (inimigo->coordInimigo.x == 0 && inimigo->coordInimigo.dx == -1)
        return 0;
    if (inimigo->coordInimigo.y == (ALTURA / LADO - 1) && inimigo->coordInimigo.dy == 1)
        return 0;
    if (inimigo->coordInimigo.y == 0 && inimigo->coordInimigo.dy == -1)
        return 0;

    // Verifica se a entidade está parada
    if (inimigo->coordInimigo.dx == 0 && inimigo->coordInimigo.dy == 0)
        return 0;

    // Verifica o tipo do próximo espaço
    char pos = *(matrizTemporaria + (inimigo->coordInimigo.x + inimigo->coordInimigo.dx) + (inimigo->coordInimigo.y + inimigo->coordInimigo.dy) * (LARGURA / LADO));

    if (pos == 'W' || pos == 'J' || pos == 'R' || pos == 'M' || pos == 'H')
        return 0;

    // Impede o movimento na direção oposta ao último movimento
    if ((inimigo->coordInimigo.dx == -inimigo->ultimoMovimentoX && inimigo->coordInimigo.dy == -inimigo->ultimoMovimentoY) ||
        (inimigo->ultimoMovimentoX == -1 && inimigo->coordInimigo.dy == 0 && inimigo->coordInimigo.dx == 1) ||
        (inimigo->ultimoMovimentoX == 1 && inimigo->coordInimigo.dy == 0 && inimigo->coordInimigo.dx == -1) ||
        (inimigo->ultimoMovimentoY == -1 && inimigo->coordInimigo.dx == 0 && inimigo->coordInimigo.dy == 1) ||
        (inimigo->ultimoMovimentoY == 1 && inimigo->coordInimigo.dx == 0 && inimigo->coordInimigo.dy == -1))
        return 0;

    // Verifica colisão com obstáculo
    if (pos == 'O')
    {
        // Remove o obstáculo e o inimigo
        *(matrizTemporaria + (inimigo->coordInimigo.x + inimigo->coordInimigo.dx) + (inimigo->coordInimigo.y + inimigo->coordInimigo.dy) * (LARGURA / LADO)) = ' ';
        matrizTemporaria += inimigo->coordInimigo.x + inimigo->coordInimigo.y * (LARGURA / LADO);
        *matrizTemporaria = ' ';
        *qtdInimigo -= 1; // Diminui a quantidade de inimigos
        inimigo->vidas--; // Remove vida do inimigo
        return 0;
    }

    if (pos == 'S')
    {
        matrizTemporaria += inimigo->coordInimigo.x + inimigo->coordInimigo.y * (LARGURA / LADO);
        *matrizTemporaria = ' ';
        *qtdInimigo -= 1; // Diminui a quantidade de inimigos
        inimigo->vidas--; // Remove vida do inimigo
        base->vidas--;    // Remove vida da base
        return 0;
    }

    // Verifica se a entidade colidiu com a base
    if (*(matrizTemporaria + (inimigo->coordInimigo.x + inimigo->coordInimigo.dx) + (inimigo->coordInimigo.y + inimigo->coordInimigo.dy) * (LARGURA / LADO)) == 'S')
    {
        *qtdInimigo = *qtdInimigo - 1;                                                            // Quantidade de inimigos diminui
        base->vidas--;                                                                            // Vida da base diminui
        inimigo->vidas--;                                                                         // Inimigo vidas diminui
        matrizTemporaria += inimigo->coordInimigo.x + inimigo->coordInimigo.y * (LARGURA / LADO); // Matriz recebe a posicao do inimigo
        *matrizTemporaria = ' ';                                                                  // Desenha espaco em branco na posicao do inimigo

        return 0; // Inimigo nao se move para não apagar base
    }

    // Verifica se a entidade colidiu com algum recurso
    if (*(matrizTemporaria + (inimigo->coordInimigo.x + inimigo->coordInimigo.dx) + (inimigo->coordInimigo.y + inimigo->coordInimigo.dy) * (LARGURA / LADO)) == 'R')
        return 0;

    // Verifica se a entidade colidiu com algum inimigo
    if (*(matrizTemporaria + (inimigo->coordInimigo.x + inimigo->coordInimigo.dx) + (inimigo->coordInimigo.y + inimigo->coordInimigo.dy) * (LARGURA / LADO)) == 'M')
        return 0;

    // Verifica se a entidade colidiu com jogador, inimigo perde vida?
    if (*(matrizTemporaria + (inimigo->coordInimigo.x + inimigo->coordInimigo.dx) + (inimigo->coordInimigo.y + inimigo->coordInimigo.dy) * (LARGURA / LADO)) == 'J')
        return 0;

    return 1;
}

// Função que move o inimigo
void moveInimigo(TIPO_INIMIGO *inimigo, TIPO_PLAYER *player, char *matrizTemporaria, BASE *base, int *qtdInimigo)
{
    double tempoAtual = GetTime();        // Captura o tempo atual
    double timerInimigo = inimigo->timer; // Captura o timer do inimigo

    // Se o tempo decorrido desde o último movimento inimigo for maior ou igual ao delay
    if (tempoAtual - timerInimigo >= INIMIGO_DELAY)
    {
        inimigo->timer = tempoAtual; // Atualiza o timer do inimigo para o tempo atual

        // Verifica se o inimigo deve mover
        if (deveMoverInimigo(inimigo, player, matrizTemporaria, base, qtdInimigo))
        {
            move(&inimigo->coordInimigo, matrizTemporaria, inimigo->letra);
            inimigo->ultimoMovimentoX = inimigo->coordInimigo.dx;
            inimigo->ultimoMovimentoY = inimigo->coordInimigo.dy;
        }
        else
        {
            redefineDeslocamentoInimigo(inimigo, player, matrizTemporaria, base, qtdInimigo);
        }
    }
}

// Função que redefine o deslocamento do inimigo
void redefineDeslocamentoInimigo(TIPO_INIMIGO *inimigo, TIPO_PLAYER *player, char *matrizTemporaria, BASE *base, int *qtdInimigo)
{
    int movimentos[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}}; // Movimentos possíveis: direita, cima, esquerda, baixo
    float melhorDistancia = FLT_MAX;
    int melhorMovimento[2] = {0, 0};

    // Verifica a distância para cada direção possível
    for (int i = 0; i < 4; ++i)
    {
        int dx = movimentos[i][0];
        int dy = movimentos[i][1];

        // Impede o movimento na direção oposta ao último movimento
        if (dx == -inimigo->ultimoMovimentoX && dy == -inimigo->ultimoMovimentoY)
        {
            continue;
        }

        COORDENADAS novaPos = inimigo->coordInimigo;
        novaPos.x += dx;
        novaPos.y += dy;

        // Verifica se o novo movimento é válido
        inimigo->coordInimigo.dx = dx;
        inimigo->coordInimigo.dy = dy;
        if (deveMoverInimigo(inimigo, player, matrizTemporaria, base, qtdInimigo))
        {
            float distanciaAtual = distanciaAteBase(&novaPos, base);
            if (distanciaAtual < melhorDistancia)
            {
                melhorDistancia = distanciaAtual;
                melhorMovimento[0] = dx;
                melhorMovimento[1] = dy;
            }
        }
    }

    // Atualiza o deslocamento do inimigo com a melhor direção
    inimigo->coordInimigo.dx = melhorMovimento[0];
    inimigo->coordInimigo.dy = melhorMovimento[1];
}

void move(COORDENADAS *entidade, char *matriz, char letra)
{
    //  Realiza a movimentação
    matriz += entidade->x + entidade->y * (LARGURA / LADO);
    if (*matriz != 'O' && *matriz != 'H' && *matriz != 'W')
        *matriz = ' ';

    entidade->x = entidade->x + entidade->dx;
    entidade->y += entidade->dy;

    matriz += entidade->dx + entidade->dy * (LARGURA / LADO);
    *matriz = letra;
}

// Funcao que trata controle do jogador
void controleJogador(TIPO_PLAYER *entidade, char *matriz)
{

    if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) // Verifica tecla pressionada
    {
        entidade->coordPlayer.dx = 1;
        entidade->coordPlayer.dy = 0;
        if (deveMoverPlayer(entidade, matriz))
            move(&entidade->coordPlayer, matriz, entidade->letra);
    }

    if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A))
    {
        entidade->coordPlayer.dx = -1;
        entidade->coordPlayer.dy = 0;
        if (deveMoverPlayer(entidade, matriz))
            move(&entidade->coordPlayer, matriz, entidade->letra);
    }

    if (IsKeyPressed(KEY_UP) || IsKeyDown(KEY_W))
    {
        entidade->coordPlayer.dx = 0;
        entidade->coordPlayer.dy = -1;
        if (deveMoverPlayer(entidade, matriz))
            move(&entidade->coordPlayer, matriz, entidade->letra);
    }

    if (IsKeyPressed(KEY_DOWN) || IsKeyDown(KEY_S))
    {
        entidade->coordPlayer.dx = 0;
        entidade->coordPlayer.dy = 1;
        if (deveMoverPlayer(entidade, matriz))
            move(&entidade->coordPlayer, matriz, entidade->letra);
    }
}

// Funcao que centraliza a janela ao centro da tela
void centerWindow(float windowWidth, float windowHeight)
{
    int monitor = GetCurrentMonitor();             // Captura o monitor usado
    int monitorWidth = GetMonitorWidth(monitor);   //  Verifica a largura do monitor usado
    int monitorHeight = GetMonitorHeight(monitor); //  Verifica a altura do monitor usado

    //  Define a posição da janela (window) na tela
    SetWindowPosition((int)(monitorWidth / 2) - (int)(windowWidth / 2), (int)(monitorHeight / 2) - (int)(windowHeight / 2));
}

// Funcao que le o mapa do arquivo e conta a quantidade de inimigos
int leMapa(char nomeDoArquivo[30], char *matriz, int *qtdInimigos)
{
    int erro = 1;
    FILE *arq;
    char caractere;

    if (!(arq = fopen(nomeDoArquivo, "r")))
    {
        perror("Erro ao abrir o arquivo para leitura");
        erro = 0;
    }
    else
    {
        while (!(feof(arq)))
        {
            caractere = getc(arq);
            if (caractere != '\n' && caractere != '\0')
            {

                *matriz = caractere;

                // Conta a quantidade de inimigos
                if (caractere == 'M')
                    *qtdInimigos = *qtdInimigos + 1;

                matriz += sizeof(char);
            }
        }
        fclose(arq);
    }

    return erro;
}

void passaNivel(char fase[], char *nivel)
{

    strcpy(fase, "../source/fases/mapa"); // Copia o nome do arquivo para a variavel
    strncat(fase, nivel, 1);              // Concatena o nome do arquivo com o nivel
    strcat(fase, ".txt");                 // Concatena o nome do arquivo com a extensao
}

void inicializaNivel(char *matriz, char fase[], GAMESTATUS *estadoDoJogo, TIPO_INIMIGO inimigos[], TIPO_PLAYER *player, BASE *base, int *qtdInimigos)
{

    for (int i = 0; i < MAX_INIMIGOS; i++)
    {
        inicializaInimigo(&inimigos[i]);
    }

    *qtdInimigos = 0; // Inicializa a quantidade de inimigos
    passaNivel(fase, &estadoDoJogo->nivel);
    leMapa(fase, matriz, qtdInimigos); // Leitura do mapa do jogo e contagem de inimigos
    inicializaPlayer(player);          // Funcao para inicializar o player com valores iniciais
    inicializaBase(base);
}
// Funcao que verifica se a quantidade de inimigos, retorna 1 se houver inimigos, 0 se nao houver
int ehTelaVitoria(int *qtdInimigo)
{
    if (*qtdInimigo == 0)
    {
        return 1;
    }
    else
        return 0;
}

// Funcao que verifica a tela atual do jogo e muda de acordo com a situacao
void verificaTelaJogo(char *matriz, GAMESCREEN *telaAtual, int *deveFechar, GAMESTATUS *estadoDoJogo, char fase[], TIPO_INIMIGO inimigos[], TIPO_PLAYER *player, BASE *base, int *qtdInimigos)
{
    // Modifica a tela atual de acordo com a situacao do jogo
    switch (*telaAtual)
    {

    case TITULO: // Tela titulo do jogo, onde o jogador pode iniciar o jogo
    {
        if (IsKeyPressed(KEY_N)) // Inicia um novo jogo
        {
            inicializaNivel(matriz, fase, estadoDoJogo, inimigos, player, base, qtdInimigos);
            *telaAtual = GAMEPLAY;
        }

        if (IsKeyPressed(KEY_L)) // Carrega o jogo
        {
            //  *telaAtual = GAMEPLAY;
        }
        if (IsKeyPressed(KEY_O)) // Tela de vitoria
        {
            *telaAtual = VITORIA;
        }
        if (IsKeyPressed(KEY_Q)) // Sai do jogo
        {
            *deveFechar = 1;
        }
    }
    break;

    case GAMEPLAY: // Tela de gameplay, onde o jogador pode jogar
    {
        if (IsKeyPressed(KEY_TAB)) // Abre o menu
        {
            *telaAtual = MENU;
        }
        if (IsKeyPressed(KEY_ESCAPE)) // Abre o menu
        {
            *telaAtual = MENU;
        }
    }
    break;

    case MENU: // Tela de menu ou pause, onde o jogador pode retornar ao titulo
    {
        if (IsKeyPressed(KEY_J)) /// Continua o jogo
        {
            *telaAtual = GAMEPLAY;
        }
        if (IsKeyPressed(KEY_C)) // Continua o jogo
        {
            *telaAtual = GAMEPLAY;
        }
        if (IsKeyPressed(KEY_S)) // Salva o jogo
        {
        }

        if (IsKeyPressed(KEY_V)) // Volta ao titulo
        {
            *telaAtual = TITULO;
        }
    }
    break;

    case GAMEOVER: // Tela de game over, onde o jogador pode retornar ao titulo
    {
        if (IsKeyPressed(KEY_L)) // Carrega o jogo
        {
            // *telaAtual = GAMEPLAY;
        }
        if (IsKeyPressed(KEY_R)) // Reinicia o jogo
        {
            inicializaNivel(matriz, fase, estadoDoJogo, inimigos, player, base, qtdInimigos);
            *telaAtual = GAMEPLAY;
        }

        if (IsKeyPressed(KEY_V)) // Volta ao titulo
        {
            inicializaNivel(matriz, fase, estadoDoJogo, inimigos, player, base, qtdInimigos);
            *telaAtual = TITULO;
        }
        if (IsKeyPressed(KEY_N)) // Volta ao titulo
        {
            *telaAtual = TITULO;
        }
    }
    break;

    case VITORIA: // Tela de vitoria, onde o jogador pode retornar ao titulo
    {
        if (IsKeyPressed(KEY_N)) // Carrega o proximo nivel
        {
            if (estadoDoJogo->nivel == '4')
            {
                estadoDoJogo->nivel = 1;
                inicializaNivel(matriz, fase, estadoDoJogo, inimigos, player, base, qtdInimigos);
                *telaAtual = GAMEPLAY;
            }
            else
            {

                estadoDoJogo->nivel = estadoDoJogo->nivel + 1;
                inicializaNivel(matriz, fase, estadoDoJogo, inimigos, player, base, qtdInimigos);
                *telaAtual = GAMEPLAY;
            }
        }
        if (IsKeyPressed(KEY_R)) // Reinicia o jogo
        {
            inicializaNivel(matriz, fase, estadoDoJogo, inimigos, player, base, qtdInimigos);
            *telaAtual = GAMEPLAY;
        }

        if (IsKeyPressed(KEY_V)) // Volta ao titulo
        {
            *telaAtual = TITULO;
        }
    }
    break;

    default:
        break;
    }
}

int salvaEstado(char nomeDoArquivo[30], GAMESTATUS gameStatus)
{
    int erro = 1;
    FILE *arq;

    if (!(arq = fopen(nomeDoArquivo, "w")))
        erro = 0;
    else if (!(fwrite(&gameStatus, sizeof(GAMESTATUS), 1, arq)))
        erro = 0;
    else
        fclose(arq);

    return erro;
}

int leEstado(char nomeDoArquivo[30], GAMESTATUS *gameStatus)
{
    int erro = 1;
    FILE *arq;

    if (!(arq = fopen(nomeDoArquivo, "r")))
    {
        perror("Erro ao abrir o arquivo para leitura");
        erro = 0;
    }
    else if (!(fread(gameStatus, sizeof(GAMESTATUS), 1, arq)))
    {
        perror("Erro ao ler do arquivo");
        erro = 0;
    }
    else
        fclose(arq);

    return erro;
}

// Funcao que desenha na tela
void desenha(int coordX, int coordY, Color cor)
{

    DrawRectangle(coordX * LADO, coordY * LADO, LADO, LADO, cor); // Desenha um retangulo
}

void desenhaMapa(char *matriz, TIPO_PLAYER *player, TIPO_INIMIGO *inimigo, BASE *base)
{

    for (int i = 0; i < (ALTURA / 20); i++)
        for (int j = 0; j < LARGURA / 20; j++)
        {
            switch (*matriz)
            {
            case 'J':                        // Player
                desenhaPlayer(player, j, i); // Desenha o player
                break;

            case 'M': // Inimigo
                desenhaInimigo(inimigo, j, i);
                inimigo++; // Quantidade de inimigos soma 1
                break;

            case 'R': // Recurso
                desenha(j, i, PINK);
                break;

            case 'H': // Buraco/Portal
                desenha(j, i, YELLOW);
                break;

            case 'S': // Base
                desenha(j, i, BLUE);
                base->coordBase.x = j;
                base->coordBase.y = i;
                break;

            case 'W': // Parede
                desenha(j, i, PURPLE);
                break;

            case ' ': // Área de trânsito
                desenha(j, i, WHITE);
                break;

            case 'O': // Obstáculo
                desenha(j, i, BLACK);
                break;
            }
            matriz++;
        }
}
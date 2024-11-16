
#ifndef FUNCOES_H // Verifica se a biblioteca funcoes.h ja foi definida
#define FUNCOES_H // Define a biblioteca funcoes.h
//----------------------------------------------------------------------------------
// Este header contem as funcoes para o programa principal, separar por tipo posteriormente?
#include "estruturas.h" // Inclui o header estruturas.h
//----------------------------------------------------------------------------------
// Protótipos das funções
//----------------------------------------------------------------------------------
void inicializaPlayer(TIPO_PLAYER *player);                              // Inicializa o player com valores base, como vida, cor, letra, recursos, delay e timer
void inicializaInimigo(TIPO_INIMIGO *inimigo);                           // Inicializa o inimigo com valores base, como vida, cor, letra, timer e coordenadas
void inicializaBase(BASE *base);                                         // Inicializa a base com valores base, como vida, cor e coordenadas
void verificaVidas(BASE *base, TIPO_PLAYER *player, GAMESCREEN *tela);   // Verifica a quantidade de vidas da base e do player
void desenhaPlayer(TIPO_PLAYER *player, int posx, int posy);             // Desenha o player na tela com posicao x e y
void desenhaInimigo(TIPO_INIMIGO inimigo[MAX_INIMIGOS], int dx, int dy); // Desenha o inimigo na tela com posicao x e y
void contaRecursos(TIPO_PLAYER *player);
void processarInimigos(TIPO_INIMIGO inimigo[MAX_INIMIGOS], int qtdInimigos, TIPO_PLAYER *player, char *matriz, BASE *base, int *qtdInimigo);
int deveMoverPlayer(TIPO_PLAYER *entidade, char *matriz);                                                                                                                                       // Verifica se o player deve mover, retorna 1 se deve mover, 0 se nao deve mover
int deveMoverInimigo(TIPO_INIMIGO *inimigo, TIPO_PLAYER *player, char *matriz, BASE *base, int *qtdInimigo);                                                                                    // Verifica se o inimigo deve mover, retorna 1 se deve mover, 0 se nao deve mover
void move(COORDENADAS *entidade, char *matriz, char letra);                                                                                                                                     // Move a entidade no mapa com a letra correspondente e coloca espaco em branco na posicao anterior
void controleJogador(TIPO_PLAYER *entidade, char *matriz);                                                                                                                                      // Controle do jogador, verifica teclas pressionadas e movimenta o jogador
void moveInimigo(TIPO_INIMIGO *inimigo, TIPO_PLAYER *player, char *matriz, BASE *base, int *qtdInimigo);                                                                                        // Move o inimigo no mapa
void redefineDeslocamentoInimigo(TIPO_INIMIGO *inimigo, TIPO_PLAYER *player, char *matriz, BASE *base, int *qtdInimigo);                                                                        // Redefine o deslocamento do inimigo
void centerWindow(float windowWidth, float windowHeight);                                                                                                                                       // Centraliza a janela do jogo ao centro da tela
void controleJogador(TIPO_PLAYER *entidade, char *matriz);                                                                                                                                      // Controle do jogador, verifica teclas pressionadas e movimenta o jogador
void verificaVidas(BASE *base, TIPO_PLAYER *player, GAMESCREEN *tela);                                                                                                                          // Verifica a quantidade de vidas da base e do player e muda a tela de acordo
void verificaTelaJogo(char *matriz, GAMESCREEN *telaAtual, int *deveFechar, GAMESTATUS *estadoDoJogo, char fase[], TIPO_INIMIGO inimigos[], TIPO_PLAYER *player, BASE *base, int *qtdInimigos); // Verifica a tela atual do jogo e muda conforme a tecla pressionada e a quantidade de inimigos
void desenhaMapa(char *matriz, TIPO_PLAYER *player, TIPO_INIMIGO inimigo[MAX_INIMIGOS], BASE *base);                                                                                            // Desenha o mapa do jogo com o player, inimigos e base
void inicializaNivel(char *matriz, char *fase, GAMESTATUS *estadoDoJogo, TIPO_INIMIGO inimigos[], TIPO_PLAYER *player, BASE *base, int *qtdInimigos);                                           // Inicializa o nivel do jogo com valores padrao e leitura do arquivo de fases
#endif                                                                                                                                                                                          // Desenha os inimigos na tela
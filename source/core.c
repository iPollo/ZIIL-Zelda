// ===========================================================================
//			
//		Pac-Telma (Desenvolvido em C, usando Raylib)
//		Por: Aline Lux (335722) e Henrique Selau de Oliveira (338301)
//		Universidade Federal do Rio Grande do Sul - UFRGS
//		Algoritmos e Programação - PROF. Marcelo Walter
//
// ===========================================================================

// ===========================================================================
// 		Imports e Includes Globas
// ===========================================================================

// Bibliotecas Nativas e Raylib
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "time.h"
#include "math.h"
#include "stdbool.h"
#include "raylib.h"
 
// ===========================================================================
// 		Variáveis Globais/Constantes
// ===========================================================================

// Globais constantes
const int SCREEN_WIDTH = 1200;  
const int SCREEN_HEIGHT = 800;
const int START_SCREEN_DIMENSION = 650;
const int TILE_SIZE = 50;
const int TILE_LINES = SCREEN_HEIGHT/TILE_SIZE;
const int TILE_ROWS = SCREEN_WIDTH/TILE_SIZE;
char MAP[16][24];
    
// Globais de gerenciamento do game loop
bool isGameRunning = false;
bool isGameOver = false;

// Declaração das Funções principais
int startGame();
void loadNewLevel(int playerCurrentLevel);
void gameLevelGameOver();

// ===========================================================================
// 		Dependencias do jogo (Módulos)
// ===========================================================================

#include "gameUtil/gameUtilMath.c"
#include "gameTextures/gameTexturesCore.c"
#include "gameAudio/gameAudioCore.c"
#include "gameEntity/gameEntityCore.c"
#include "gameLevels/gameLevel.c"
#include "gameMenu/gameMenu.c"

// ===========================================================================
// 		Core
// ===========================================================================

int main(void){
	
	// Inicializa a janela (Raylib)
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "ZIIL - Zelda");
	SetWindowPosition((GetMonitorWidth(GetCurrentMonitor())/2) - SCREEN_WIDTH/2, (GetMonitorHeight(GetCurrentMonitor())/2 - SCREEN_HEIGHT/2)+ 50);
	
	// Inicializa o dispositivo de áudio (Raylib)
	InitAudioDevice(); 

	// Define o FPS para 60 (Raylib)
	SetTargetFPS(60);

	// Inicializa cada arquivo e suas dependências (Módulos)
	gameAudioInit();
	gameTexturesInit();
	gameMenuInit();

	// Carrega as informações salvas do scoreboard
	gameLevelLoadScoreboard();

	// Game Loop principal
    while (!WindowShouldClose()) 
    {
    	// Raylib (Desenha e atualiza as variáveis do jogo)
        BeginDrawing();

        // Processa cada módulo e suas dependências
        gameMenuUpdate();
        gameTexturesUpdate();
        gameEntityUpdate();
        gameLevelUpdate();
        gameAudioUpdate();

        // Raylib (Finaliza a atualização do frame)
        EndDrawing();

    }

    // Finaliza o dispositivo de áudio (Raylib)
    CloseAudioDevice(); 
    
}

// Inicia o jogo
int startGame(){

	// Centraliza a janela
	SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	SetWindowPosition((GetMonitorWidth(GetCurrentMonitor())/2) - SCREEN_WIDTH/2, GetMonitorHeight(GetCurrentMonitor())/2 - SCREEN_HEIGHT/2);
	
	// Carrega o primeiro nível
	loadNewLevel(0);

	// Atualiza o status do jogo
	isGameRunning = true;
	isGameOver = false;

	// Toca as músicas respectivas (Pausa a música do menu e inicia a música de batalha do jogo)
	setMenuMusicPlaying(false);
	setGameMusicPlaying(true);
	return 1;
}
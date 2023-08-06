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

// Bibliotecas Nativas e Raylib Game Engine
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "time.h"
#include "math.h"
#include "stdbool.h"
#include "raylib.h"

// ===========================================================================
// 		Variáveis Globais
// ===========================================================================

// Janela Principal
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 800;
const int START_SCREEN_DIMENSION = 650;
const int TILE_SIZE = 50;
const int TILE_LINES = SCREEN_HEIGHT/TILE_SIZE;
const int TILE_ROWS = SCREEN_WIDTH/TILE_SIZE;
    
// Bool
bool isGameRunning = false;

// Declarações Core
int startGame();

// ===========================================================================
// 		Dependencias do jogo
// ===========================================================================

#include "tempMap.c"
#include "gameTextures/gameTexturesCore.c"
#include "gameData/gameDataCore.c"
#include "gameEntity/gameEntityCore.c"

// ===========================================================================
// 		Core
// ===========================================================================

int main(void){
	 
	// Inicializa a janela 
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "ZIIL - Zelda");
	SetWindowPosition((GetMonitorWidth(GetCurrentMonitor())/2) - SCREEN_WIDTH/2, (GetMonitorHeight(GetCurrentMonitor())/2 - SCREEN_HEIGHT/2)+ 50);
	//SetWindowState(FLAG_WINDOW_UNDECORATED);
	SetTargetFPS(60);

	// Inicializa cada arquivo e suas dependências
	gameTexturesInit();
	gameDataInit();
	gameEntityInit();

	// Carrega as informaçõeSSs salvas do jogosss
	gameDataLoad();

	// Inicia mostrando o menu inicialssss
   

	// Game Loop principal

    while (!WindowShouldClose()) 
    {

    	// Desenha e atualiza as variáveis do jogo
    	// Raylib Draw 
        BeginDrawing();

        // Processa cada arquivo e suas dependências
        gameTexturesUpdate();
        gameEntityUpdate();

        //Raylib end draw
        EndDrawing();

    }
    
}

int startGame(){
	
	SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	SetWindowPosition((GetMonitorWidth(GetCurrentMonitor())/2) - SCREEN_WIDTH/2, GetMonitorHeight(GetCurrentMonitor())/2 - SCREEN_HEIGHT/2);

	isGameRunning = true;

	return 1;
}
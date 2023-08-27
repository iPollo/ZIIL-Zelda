// ===========================================================================
//			
//		Pac-Telma (Desenvolvido em C, usando Raylib)
//		Por: Aline Lux (335722) e Henrique Selau de Oliveira (338301)
//		Universidade Federal do Rio Grande do Sul - UFRGS
//		Algoritmos e Programação - PROF. Marcelo Walter
//
// ===========================================================================

#define COLLOR_GOLDEN  CLITERAL(Color){ 255, 139, 49, 255 }

enum{
	OPTION_START,
	OPTION_LOAD,
	OPTION_SCOREBOARD,
	OPTION_SAIR,
};

enum{
	MENU_MAIN,
	MENU_SCOREBOARD,


};

int menuCurrentSelectedOption = OPTION_START;
int menuCurrentMenu = MENU_MAIN;


Vector2 selectedButton[4];

// ===========================================================================
// 		Imports e Includes Globas
// ===========================================================================

void gameMenuInit(){

	isGameRunning = false;
	selectedButton[0] = (Vector2){90, 439};
	selectedButton[1] = (Vector2){617, 439};
	selectedButton[2] = (Vector2){90, 558};
	selectedButton[3] = (Vector2){617, 558};
}


void gameMenuUpdate(){

	if(isGameRunning || menuCurrentMenu != MENU_MAIN) return;


	DrawTexture(gameTextures[TXT_MENU_BACKGROUND], 0, 0, WHITE);  
	DrawTexturePro(gameTextures[TXT_MENU_BUTTONS], (Rectangle){0,0,500,150}, (Rectangle){90, 439, 500,150}, (Vector2){0,0},0, WHITE);
	DrawTexturePro(gameTextures[TXT_MENU_BUTTONS], (Rectangle){0,150,500,150}, (Rectangle){617, 439, 500,150}, (Vector2){0,0},0, WHITE);
	DrawTexturePro(gameTextures[TXT_MENU_BUTTONS], (Rectangle){0,150*2,500,150}, (Rectangle){90, 558, 500,150}, (Vector2){0,0},0, WHITE);
	DrawTexturePro(gameTextures[TXT_MENU_BUTTONS], (Rectangle){0,150*3,500,150}, (Rectangle){617, 558, 500,150}, (Vector2){0,0},0, WHITE);
	DrawTexturePro(gameTextures[TXT_MENU_BUTTONS], (Rectangle){500,150*menuCurrentSelectedOption,500,150}, (Rectangle){selectedButton[menuCurrentSelectedOption].x, selectedButton[menuCurrentSelectedOption].y, 500,150}, (Vector2){0,0},0, WHITE);


	if(IsKeyPressed(KEY_RIGHT)){
		menuCurrentSelectedOption++;
		if(menuCurrentSelectedOption == 4) menuCurrentSelectedOption = 0;
	}

	if(IsKeyPressed(KEY_LEFT)){
		menuCurrentSelectedOption--;
		if(menuCurrentSelectedOption == -1){
			TraceLog(LOG_INFO, "cu");
			menuCurrentSelectedOption = 3;
		}
	}



}
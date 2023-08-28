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

	if(isGameRunning) return;


	if(IsKeyPressed(KEY_ENTER)){
		if((menuCurrentSelectedOption == OPTION_SCOREBOARD) && (menuCurrentMenu == MENU_MAIN)){
			menuCurrentMenu = MENU_SCOREBOARD;
		}
		else if(menuCurrentMenu == MENU_SCOREBOARD) menuCurrentMenu = MENU_MAIN;

	}


	if(menuCurrentMenu != MENU_MAIN){

		DrawTexture(gameTextures[TXT_MENU_SCOREBOARD], 0, 0, WHITE);  

		for(int i = 0; i < 5; i++){

			char name[16] = "Apollo";
			char date[16] = "NIVEL 1";
			char pts[16] = "1000 PTS";
			int dateSize, ptsSize;

			dateSize = MeasureText(date, 25);
			ptsSize = MeasureText(pts, 25);

			DrawText(TextFormat("%d.", i+1), 154, 378 + (64 * i), 25, WHITE);
			DrawText(name, 180, 378 + (64 * i), 25, WHITE);
			DrawText(date, 590 - dateSize/2, 378 + (64 * i), 25, WHITE);
			DrawText(pts, 1042 - ptsSize, 378 + (64 * i), 25, WHITE);

		}



		return;
	}

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
			menuCurrentSelectedOption = 3;
		}
	}
	if(IsKeyPressed(KEY_ENTER)){
		if(menuCurrentSelectedOption == OPTION_SAIR) CloseWindow();
		else if(menuCurrentSelectedOption == OPTION_START) startGame();
	}
}
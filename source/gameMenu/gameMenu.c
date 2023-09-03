// ===========================================================================
//			
//		Pac-Telma (Desenvolvido em C, usando Raylib)
//		Por: Aline Lux (335722) e Henrique Selau de Oliveira (338301)
//		Universidade Federal do Rio Grande do Sul - UFRGS
//		Algoritmos e Programação - PROF. Marcelo Walter
//
// ===========================================================================

// Cores utilizadas para debug
#define COLLOR_GOLDEN  CLITERAL(Color){ 255, 139, 49, 255 }

// ===========================================================================
// 		Variáveis
// ===========================================================================

// Enums para controlar as opções do menu (botões selecionados)
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

// Dados de controle do menu e dos botões 
int menuCurrentSelectedOption = OPTION_START;
int menuCurrentMenu = MENU_MAIN;

// Define a posição dos botões no menu principal
Vector2 selectedButton[4];

// ===========================================================================
// 		Imports e Includes Globas
// ===========================================================================

// Inicializa o módulo do menu principal
void gameMenuInit(){

	// Define o status do jogo como não rodando
	isGameRunning = false;

	// Começa a tocar a música do menu principal
	setMenuMusicPlaying(true);

	// Define a posição dos botões no menu principal
	selectedButton[0] = (Vector2){90, 439};
	selectedButton[1] = (Vector2){617, 439};
	selectedButton[2] = (Vector2){90, 558};
	selectedButton[3] = (Vector2){617, 558};
}

// Atualiza os dados e informações do módulo do menu
void gameMenuUpdate(){

	// Execut apenas se não estiver rodando o jogo
	if(isGameRunning || isGameOver) return;

	// Processa a tecla enter e atualiza o menu (abre o menu de scoreboard caso clique ou inicializa o jogo em sí)
	if(IsKeyPressed(KEY_ENTER)){
		if((menuCurrentSelectedOption == OPTION_SCOREBOARD) && (menuCurrentMenu == MENU_MAIN)){
			menuCurrentMenu = MENU_SCOREBOARD;
		}
		else if(menuCurrentMenu == MENU_SCOREBOARD) menuCurrentMenu = MENU_MAIN;

	}

	// Desenha o menu do scoreboard
	if(menuCurrentMenu != MENU_MAIN){

		// Desennha o asset do scorebaord
		DrawTexture(gameTextures[TXT_MENU_SCOREBOARD], 0, 0, WHITE);  

		// Inclui os dados do scoreboard na tela para os melhores 5
		for(int i = 0; i < 5; i++){

			char name[16] = "Apollo";
			TextCopy(name, topScore[i].playerName);

			char date[16] = "NIVEL 1";
			TextCopy(date, TextFormat("LEVEL %d", topScore[i].level));

			char pts[16] = "1000 PTS";
			TextCopy(pts, TextFormat("%d PTS", topScore[i].score));

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

	// Desenha os botões e o asset do menu principal
	DrawTexture(gameTextures[TXT_MENU_BACKGROUND], 0, 0, WHITE);  
	DrawTexturePro(gameTextures[TXT_MENU_BUTTONS], (Rectangle){0,0,500,150}, (Rectangle){90, 439, 500,150}, (Vector2){0,0},0, WHITE);
	DrawTexturePro(gameTextures[TXT_MENU_BUTTONS], (Rectangle){0,150,500,150}, (Rectangle){617, 439, 500,150}, (Vector2){0,0},0, WHITE);
	DrawTexturePro(gameTextures[TXT_MENU_BUTTONS], (Rectangle){0,150*2,500,150}, (Rectangle){90, 558, 500,150}, (Vector2){0,0},0, WHITE);
	DrawTexturePro(gameTextures[TXT_MENU_BUTTONS], (Rectangle){0,150*3,500,150}, (Rectangle){617, 558, 500,150}, (Vector2){0,0},0, WHITE);
	DrawTexturePro(gameTextures[TXT_MENU_BUTTONS], (Rectangle){500,150*menuCurrentSelectedOption,500,150}, (Rectangle){selectedButton[menuCurrentSelectedOption].x, selectedButton[menuCurrentSelectedOption].y, 500,150}, (Vector2){0,0},0, WHITE);

	// Atualiza o botão selecionado e toca o efeito sonoro caso clique na setas do teclado
	if(IsKeyPressed(KEY_RIGHT)){
		menuCurrentSelectedOption++;
		if(menuCurrentSelectedOption == 4) menuCurrentSelectedOption = 0;
		PlaySound(gameSound[SFX_MENU_BUTTON]);

	}

	// Atualiza o botão selecionado e toca o efeito sonoro caso clique na setas do teclado
	if(IsKeyPressed(KEY_LEFT)){
		menuCurrentSelectedOption--;
		if(menuCurrentSelectedOption == -1){
			menuCurrentSelectedOption = 3;
		}
		PlaySound(gameSound[SFX_MENU_BUTTON]);
	}

	// Verifica qual botão o jogador selecionou e clicou
	if(IsKeyPressed(KEY_ENTER)){
		if(menuCurrentSelectedOption == OPTION_SAIR) CloseWindow();
		else if(menuCurrentSelectedOption == OPTION_START) startGame();
		PlaySound(gameSound[SFX_MENU_BUTTON]);
	}
}
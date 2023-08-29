// ===========================================================================
//			
//		Pac-Telma (Desenvolvido em C, usando Raylib)
//		Por: Aline Lux (335722) e Henrique Selau de Oliveira (338301)
//		Universidade Federal do Rio Grande do Sul - UFRGS
//		Algoritmos e Programação - PROF. Marcelo Walter
//
// ===========================================================================

#define MAX_NAME 16
#define MAX_TOPSCORE 5

// ===========================================================================
// 		Imports e Includes Globas
// ===========================================================================

char gameOverInputBox[MAX_NAME];
int letterCount = 0;

typedef struct TOPSCORE{

    char playerName[16];
    int level;
    int score;

}TOPSCORE;

TOPSCORE topScore[MAX_TOPSCORE];

// ===========================================================================
// 		Funções
// ===========================================================================

void loadNewLevel(int playerCurrentLevel){

	int newLevel = playerCurrentLevel + 1;
	int rowCount = 0, lineCount = 0;

	const char *levelFileName = TextFormat("gameLevels/nivel%d.txt", newLevel);

    FILE *fp = fopen(levelFileName, "r");

    if (fp == NULL)
    {
        CloseWindow();
        return;
    }

    char ch;
    while ((ch = fgetc(fp)) != EOF){

    	if(rowCount > TILE_ROWS){
    		rowCount = 0;
    		lineCount++;
    	}

    	MAP[lineCount][rowCount] = ch;

    	rowCount++;
    }

    // close the file
    fclose(fp);

    gameEntityInit(playerCurrentLevel == 0);

}

void gameLevelLoadScoreboard(){

    FILE *arq = fopen("topfive.bin", "rb");

    if(arq == NULL){

        // Inicializa os dados
        for(int i = 0; i < MAX_TOPSCORE; i++){
            topScore[i] = (TOPSCORE){"Vazio", 0, 0};
        }

        FILE *newArq = fopen("topfive.bin", "wb");

        if(newArq == NULL){
            TraceLog(LOG_INFO, "========================================");
            TraceLog(LOG_INFO, " - Erro ao criar arquivo topfive.bin");
            TraceLog(LOG_INFO, "========================================");
            return;
        }

        fwrite(&topScore[0], sizeof(TOPSCORE), 5, newArq);
        fclose(newArq);

    }

}


void gameLevelSaveTopScore(){






}

void gameLevelGameOver(){
    //isGameRunning = false;
    isGameOver = true;

}

void gameLevelUpdate(){

    if(isGameOver){
        DrawTexture(gameTextures[TXT_MENU_GAMEOVER], 0, 0, WHITE);  


            DrawText("R E C O R D E  N Ã O  A T I N G I D O", 450, 296, 15, WHITE);
            DrawText("PONTOS:", 381, 371, 20, WHITE);
            DrawText("LEVEL:", 381, 431, 20, WHITE);

            DrawText("1923", 795 - MeasureText("1923", 20), 371, 20, WHITE);
            DrawText("2", 795 - MeasureText("2", 20), 431, 20, WHITE);
            //DrawTextEx(fonts[FONT_MECHA],"RECORDE NÃO ATINGIDO", (Vector2){500, 290}, 15, 2, WHITE); 

            char key = GetCharPressed();

            if ((key >= 32) && (key <= 125) && (letterCount < MAX_NAME))
            {
                gameOverInputBox[letterCount] = (char)key;
                gameOverInputBox[letterCount+1] = '\0'; // Add null terminator at the end of the string.
                letterCount++;
            }

            if (IsKeyPressed(KEY_BACKSPACE))
            {
                letterCount--;
                if (letterCount < 0) letterCount = 0;
                gameOverInputBox[letterCount] = '\0';
            }

            if(IsKeyPressed(KEY_ENTER)){
                isGameOver = false;
                isGameRunning = false;
            }

            DrawText(TextFormat("NOME [%d/16]: %s", letterCount, gameOverInputBox), 582 - MeasureText(TextFormat("NOME[%d/16]: %s", letterCount, gameOverInputBox), 20)/2, 543, 20, WHITE);

            DrawText("PRESSIONE [E N T E R] PARA CONTINUAR", 582 - MeasureText("PRESSIONE [E N T E R] PARA CONTINUAR", 10)/2, 615, 10, WHITE);
        

    }


}



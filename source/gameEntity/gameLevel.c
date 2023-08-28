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


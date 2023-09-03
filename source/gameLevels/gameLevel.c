// ===========================================================================
//			
//		Pac-Telma (Desenvolvido em C, usando Raylib)
//		Por: Aline Lux (335722) e Henrique Selau de Oliveira (338301)
//		Universidade Federal do Rio Grande do Sul - UFRGS
//		Algoritmos e Programação - PROF. Marcelo Walter
//
// ===========================================================================

// Defines utilitários para os níveis
#define MAX_NAME 16
#define MAX_TOPSCORE 5

// ===========================================================================
// 		Imports e Includes Globas
// ===========================================================================

// Dados do inputBox (caixa para digitar nome quando perder o jogo)
char gameOverInputBox[MAX_NAME];
int letterCount = 0;

// Estrutura de dados para o topScore (top 5 do scoreboard)
typedef struct TOPSCORE{

    char playerName[16];
    int level;
    int score;

}TOPSCORE;

// Incializa o topscore 
TOPSCORE topScore[MAX_TOPSCORE];

// ===========================================================================
// 		Funções
// ===========================================================================

// Carrega o novo level a partir do arquivo de texto
void loadNewLevel(int playerCurrentLevel){

    // Recebe o level atual do jogador e carrega o próximo arquivo
	int newLevel = playerCurrentLevel + 1;
	int rowCount = 0, lineCount = 0;

    // Carrega o arquivo de texto contendo os dados do level
	const char *levelFileName = TextFormat("gameLevels/nivel%d.txt", newLevel);
    FILE *fp = fopen(levelFileName, "r");

    // Caso atinja o nível máximo ou não encontre o arquivo (corrompido) o jogo finaliza
    if (fp == NULL)
    {
        CloseWindow();
        return;
    }

    // Caso atinja o nível máxima o jogo termina (game over automatico)
    if(newLevel == 7){
        gameLevelGameOver();
        return;
    }

    // Carrega caractere por caractere e insere na array do mapa
    char ch;
    while ((ch = fgetc(fp)) != EOF){

    	if(rowCount > TILE_ROWS){
    		rowCount = 0;
    		lineCount++;
    	}

    	MAP[lineCount][rowCount] = ch;

    	rowCount++;
    }

    // Fecha o arquivo
    fclose(fp);

    // Inicializa novamente as entidades e reseta os dados do jogador caso ele morra (game over), ou seja level = 0.
    gameEntityInit(playerCurrentLevel == 0);

    // Atualiza os dados do level do jogador
    player.level = newLevel;

    // Toca o efeito sonoro de level up caso o jogador passe de fase
    if(newLevel != 1) PlaySound(gameSound[SFX_LEVELUP]);
}

// Carrega do arquivo binario os dados do scoreboard
void gameLevelLoadScoreboard(){

    // Abre o arquivo
    FILE *arq = fopen("topfive.bin", "rb");

    // Caso não exista cria um com os Dados ("Vazio", 0, 0)
    if(arq == NULL){

        // Inicializa os dados
        for(int i = 0; i < MAX_TOPSCORE; i++){
            topScore[i] = (TOPSCORE){"Vazio", 0, 0};
        }

        // Abre e cria um novo arquivo
        FILE *newArq = fopen("topfive.bin", "wb");

        // Informa que deu erro na criação do arquivo
        if(newArq == NULL){
            TraceLog(LOG_INFO, "========================================");
            TraceLog(LOG_INFO, " - Erro ao criar arquivo topfive.bin");
            TraceLog(LOG_INFO, "========================================");
            return;
        }

        // Escreve os dados padrões no arquivo binário e fecha o arquivo
        fwrite(&topScore[0], sizeof(TOPSCORE), MAX_TOPSCORE, newArq);
        fclose(newArq);
        return;
    }

    // Caso o arquivo já exista lê os dados dele e coloca na estrutura TOPSCORE e fecha o arquivo
    fread(&topScore[0], sizeof(TOPSCORE), MAX_TOPSCORE, arq);
    fclose(arq);
}


// Salva os dados da array da estrutura topscore no arquivo binário
void gameLevelSaveTopScore(){

    // Abre e verifica o arquivo
    FILE *newArq = fopen("topfive.bin", "wb");

    if(newArq == NULL){
        TraceLog(LOG_INFO, "========================================");
        TraceLog(LOG_INFO, " - Erro ao salvar arquivo topfive.bin");
        TraceLog(LOG_INFO, "========================================");
        return;
    }

    // Salva no arquivo os dados da array
    fwrite(&topScore, sizeof(TOPSCORE), MAX_TOPSCORE, newArq);
    
    // Fecha o arquivo
    fclose(newArq);
}

// Atualiza os dados do topscore e insere o jogador na posição caso ele atinja um novo recorde
void gameLevelUpdateTopScore(int pos, char name[]){
    
    // Move os elementos da array um index para cima
    for(int i = MAX_TOPSCORE-1; i > pos; i--){
        topScore[i] = topScore[i-1];
    }

    // Insere o jogador na posição que bateu o recorde
    TextCopy(topScore[pos].playerName, name);
    topScore[pos].score = player.score;
    topScore[pos].level = player.level;
}

// Verifica se o jgoador atingiu um novo recorde e retorna a posição 
int gameLevelCheckPlayerScore(){

    for(int i = 0; i < MAX_TOPSCORE; i++){
        if(player.score >= topScore[i].score) return i;
    }
    
    return -1;
}

// Desenha a tela de game over
void gameLevelDrawGameOver(){

    // Asset da tela de game over
    DrawTexture(gameTextures[TXT_MENU_GAMEOVER], 0, 0, WHITE);  

    // Caso o jogador atinja um novo recorde mostra qual a posição que ele atingiu
    if(player.currentTopPos != -1){
        DrawText(TextFormat("R E C O R D E  A T I N G I D O [ TOP %d ]", player.currentTopPos+1), 450, 296, 15, WHITE);
    }

    // Caso contrário mostra que não atingiu um novo recorde
    else{
        DrawText("R E C O R D E  N Ã O  A T I N G I D O", 450, 296, 15, WHITE);
    }

    // Mostra a quantidade de pontos e o level
    DrawText("PONTOS:", 381, 371, 20, WHITE);
    DrawText("LEVEL:", 381, 431, 20, WHITE);
    DrawText(TextFormat("%d", player.score), 795 - MeasureText(TextFormat("%d", player.score), 20), 371, 20, WHITE);
    DrawText(TextFormat("%d", player.level), 795 - MeasureText(TextFormat("%d", player.level), 20), 431, 20, WHITE);

    // Atualiza os dados da inputbox, coletando o caractere e inserindo na string (nome do jogador que ele digite quando perde)
    char key = GetCharPressed();

    // Insere o caractere na array e define um novo final
    if ((key >= 32) && (key <= 125) && (letterCount < MAX_NAME))
    {
        gameOverInputBox[letterCount] = (char)key;
        gameOverInputBox[letterCount+1] = '\0'; // Add null terminator at the end of the string.
        letterCount++;
    }

    // Apaga um caractere da array e define um novo final
    if (IsKeyPressed(KEY_BACKSPACE))
    {
        letterCount--;
        if (letterCount < 0) letterCount = 0;
        gameOverInputBox[letterCount] = '\0';
    }

    // Processa os dados e o nome do jogador e volta ao menu principal, atualizando também o scoreboard caso necessário
    if(IsKeyPressed(KEY_ENTER)){
        
        // Atualiza o status do game
        isGameOver = false;
        isGameRunning = false;
        
        // Atualiza o scoreboard caso atinja um novo recorde
        if(player.currentTopPos != -1){
            gameLevelUpdateTopScore(player.currentTopPos, gameOverInputBox);
            gameLevelSaveTopScore();
        }

        // Bota a música do menu para tocar novamente
        setMenuMusicPlaying(true);

    }

    // Desenha o nome digitado e a tecla Enter apra continuar
    DrawText(TextFormat("NOME [%d/16]: %s", letterCount, gameOverInputBox), 582 - MeasureText(TextFormat("NOME[%d/16]: %s", letterCount, gameOverInputBox), 20)/2, 543, 20, WHITE);
    DrawText("PRESSIONE [E N T E R] PARA CONTINUAR", 582 - MeasureText("PRESSIONE [E N T E R] PARA CONTINUAR", 10)/2, 615, 10, WHITE);
}

// Função responsável por chamar a tela de gameover
void gameLevelGameOver(){

    // Define o status do jogo como over
    isGameOver = true;

    // Chama a função para verificar se o jogador atingiu um novo recorde
    player.currentTopPos = gameLevelCheckPlayerScore();

    // Reseta os dados da inputbox do nome
    letterCount = 0;
    gameOverInputBox[letterCount] = '\0';

    // Para de tocar a música de batalha do jogo
    setGameMusicPlaying(false);

    // Toca o efeito sonoro de fim de jogo
    PlaySound(gameSound[SFX_GAMEOVER]);

}

// Atualiza e desenha a tela de gameover
void gameLevelUpdate(){
    if(isGameOver){
        gameLevelDrawGameOver();
    }
}



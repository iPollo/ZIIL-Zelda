// ===========================================================================
//			
//		Pac-Telma (Desenvolvido em C, usando Raylib)
//		Por: Aline Lux (335722) e Henrique Selau de Oliveira (338301)
//		Universidade Federal do Rio Grande do Sul - UFRGS
//		Algoritmos e Programação - PROF. Marcelo Walter
//
// ===========================================================================

// OBS: As texturas do jogo são assets carregados globalmente para utiliza-los em todo os script
// São imagens/sprites/texturas etc.

// Define o número máximo de textras do jogo
#define MAX_GAME_TEXTURES 32

// ===========================================================================
// 		Variáveis
// ===========================================================================

// Enum responsável por controlar as texturas do jogo
enum{
	TXT_GROUND,
	TXT_ROCK,
	TXT_PLAYER_STATE,
	TXT_PLAYER_WALK,
    TXT_SLASH,
    TXT_ATTACK,
    TXT_MONSTER_STATE,
    TXT_MONSTER_WALK,
    TXT_HUD_LIFE,
    TXT_HUD_SCORE,
    TXT_HUD_LIFEBAR,
    TXT_HUD_SCOREBACK,
    TXT_MONSTER_FOLLOW_STATE,
    TXT_MONSTER_HIT_STATE,
    TXT_MONSTER_LIFE_SPRITESHEET,
    TXT_MONSTER_ATTACK,
    TXT_MENU_BACKGROUND,
    TXT_MENU_BUTTONS,
    TXT_MENU_SCOREBOARD,
    TXT_MENU_GAMEOVER,
};

// Inicializa as texturas do jogo usando um Texture2D (Struct do próprio Raylib)
Texture2D gameTextures[MAX_GAME_TEXTURES];

// ===========================================================================
// 		Funções
// ===========================================================================

// Inicializa as variaveis e arquivos de texturas 
void gameTexturesInit(){

	gameTextures[TXT_GROUND] = LoadTexture(TextFormat("%s/gameAssets/TXT_GROUND.png", GetWorkingDirectory()));
	gameTextures[TXT_ROCK] = LoadTexture(TextFormat("%s/gameAssets/TXT_ROCK.png", GetWorkingDirectory()));
	gameTextures[TXT_PLAYER_STATE] = LoadTexture(TextFormat("%s/gameAssets/PLAYER_STATE_SPRITESHEET.png", GetWorkingDirectory()));
	gameTextures[TXT_PLAYER_WALK] = LoadTexture(TextFormat("%s/gameAssets/PLAYER_WALK_SPRITESHEET.png", GetWorkingDirectory()));
	gameTextures[TXT_SLASH] = LoadTexture(TextFormat("%s/gameAssets/SLASH_SPRITESHEET.png", GetWorkingDirectory()));
	gameTextures[TXT_ATTACK] = LoadTexture(TextFormat("%s/gameAssets/PLAYER_ATTACK_SPRITESHEET.png", GetWorkingDirectory()));
	gameTextures[TXT_MONSTER_STATE] = LoadTexture(TextFormat("%s/gameAssets/MONSTER_STATE_SPRITESHEET.png", GetWorkingDirectory()));
	gameTextures[TXT_MONSTER_WALK] = LoadTexture(TextFormat("%s/gameAssets/MONSTER_WALK_SPRITESHEET.png", GetWorkingDirectory()));
	gameTextures[TXT_HUD_LIFE] = LoadTexture(TextFormat("%s/gameAssets/TXT_HUD_LIFE.png", GetWorkingDirectory()));
	gameTextures[TXT_HUD_SCORE] = LoadTexture(TextFormat("%s/gameAssets/TXT_HUD_SCORE.png", GetWorkingDirectory()));
	gameTextures[TXT_HUD_LIFEBAR] = LoadTexture(TextFormat("%s/gameAssets/TXT_HUD_LIFEBAR.png", GetWorkingDirectory()));
	gameTextures[TXT_HUD_SCOREBACK] = LoadTexture(TextFormat("%s/gameAssets/TXT_HUD_SCOREBACK.png", GetWorkingDirectory()));
	gameTextures[TXT_MONSTER_FOLLOW_STATE] = LoadTexture(TextFormat("%s/gameAssets/MONSTER_FOLLOW_STATE_SPRITESHEET.png", GetWorkingDirectory()));
	gameTextures[TXT_MONSTER_HIT_STATE] = LoadTexture(TextFormat("%s/gameAssets/MONSTER_HITSTATE_SPRITESHEET.png", GetWorkingDirectory()));
	gameTextures[TXT_MONSTER_LIFE_SPRITESHEET] = LoadTexture(TextFormat("%s/gameAssets/MONSTER_LIFE_SPRITESHEET.png", GetWorkingDirectory()));
	gameTextures[TXT_MONSTER_ATTACK] = LoadTexture(TextFormat("%s/gameAssets/MONSTER_ATTACK_SPRITESHEET.png", GetWorkingDirectory()));
	gameTextures[TXT_MENU_BACKGROUND] = LoadTexture(TextFormat("%s/gameAssets/MENU_BACKGROUND.png", GetWorkingDirectory()));
	gameTextures[TXT_MENU_BUTTONS] = LoadTexture(TextFormat("%s/gameAssets/MENU_BUTTON_SPRITESHEET.png", GetWorkingDirectory()));
	gameTextures[TXT_MENU_SCOREBOARD] = LoadTexture(TextFormat("%s/gameAssets/MENU_SCOREBOARD.png", GetWorkingDirectory()));
	gameTextures[TXT_MENU_GAMEOVER] = LoadTexture(TextFormat("%s/gameAssets/GAMEOVER_SCREEN.png", GetWorkingDirectory()));
}

// Desenha a textura completa do mapa, ou seja, o level atual do jogador
void drawMap(){

	// Desenha o plano de fundo de acordo com o caractere
	for(int i = 0; i < TILE_LINES; i++){
		for(int j = 0; j < TILE_ROWS; j++){
			if(MAP[i][j] == 'B' || MAP[i][j] == 'O' || MAP[i][j] == 'M' || MAP[i][j] == 'J'){
				DrawTexture(gameTextures[TXT_GROUND], j * TILE_SIZE, (i * TILE_SIZE), WHITE);
			}
			else if(MAP[i][j] == 'P'){
				DrawTexture(gameTextures[TXT_ROCK], j * TILE_SIZE, i * TILE_SIZE, WHITE);
			}
		}
	}
}

// Atualiza no main loop
void gameTexturesUpdate(){

	if(!isGameRunning) return;
	drawMap();
}

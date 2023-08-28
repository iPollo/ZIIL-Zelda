// ===========================================================================
//			
//		Pac-Telma (Desenvolvido em C, usando Raylib)
//		Por: Aline Lux (335722) e Henrique Selau de Oliveira (338301)
//		Universidade Federal do Rio Grande do Sul - UFRGS
//		Algoritmos e Programação - PROF. Marcelo Walter
//
// ===========================================================================

#define MAX_GAME_TEXTURES 32

// ===========================================================================
// 		Variáveis
// ===========================================================================

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
};

Texture2D gameTextures[MAX_GAME_TEXTURES];

// ===========================================================================
// 		Funções
// ===========================================================================

// Inicializa as variaveis e arquivos
void gameTexturesInit(){

	gameTextures[TXT_GROUND] = LoadTexture("C:/raylib/raylib/examples/ZIIL-Zelda/assets/TXT_GROUND.png");
	gameTextures[TXT_ROCK] = LoadTexture("C:/raylib/raylib/examples/ZIIL-Zelda/assets/TXT_ROCK.png");
	gameTextures[TXT_PLAYER_STATE] = LoadTexture("C:/raylib/raylib/examples/ZIIL-Zelda/assets/PLAYER_STATE_SPRITESHEET.png");
	gameTextures[TXT_PLAYER_WALK] = LoadTexture("C:/raylib/raylib/examples/ZIIL-Zelda/assets/PLAYER_WALK_SPRITESHEET.png");
	gameTextures[TXT_SLASH] = LoadTexture("C:/raylib/raylib/examples/ZIIL-Zelda/assets/SLASH_SPRITESHEET.png");
	gameTextures[TXT_ATTACK] = LoadTexture("C:/raylib/raylib/examples/ZIIL-Zelda/assets/PLAYER_ATTACK_SPRITESHEET.png");
	gameTextures[TXT_MONSTER_STATE] = LoadTexture("C:/raylib/raylib/examples/ZIIL-Zelda/assets/MONSTER_STATE_SPRITESHEET.png");
	gameTextures[TXT_MONSTER_WALK] = LoadTexture("C:/raylib/raylib/examples/ZIIL-Zelda/assets/MONSTER_WALK_SPRITESHEET.png");
	gameTextures[TXT_HUD_LIFE] = LoadTexture("C:/raylib/raylib/examples/ZIIL-Zelda/assets/TXT_HUD_LIFE.png");
	gameTextures[TXT_HUD_SCORE] = LoadTexture("C:/raylib/raylib/examples/ZIIL-Zelda/assets/TXT_HUD_SCORE.png");
	gameTextures[TXT_HUD_LIFEBAR] = LoadTexture("C:/raylib/raylib/examples/ZIIL-Zelda/assets/TXT_HUD_LIFEBAR.png");
	gameTextures[TXT_HUD_SCOREBACK] = LoadTexture("C:/raylib/raylib/examples/ZIIL-Zelda/assets/TXT_HUD_SCOREBACK.png");
	gameTextures[TXT_MONSTER_FOLLOW_STATE] = LoadTexture("C:/raylib/raylib/examples/ZIIL-Zelda/assets/MONSTER_FOLLOW_STATE_SPRITESHEET.png");
	gameTextures[TXT_MONSTER_HIT_STATE] = LoadTexture("C:/raylib/raylib/examples/ZIIL-Zelda/assets/MONSTER_HITSTATE_SPRITESHEET.png");
	gameTextures[TXT_MONSTER_LIFE_SPRITESHEET] = LoadTexture("C:/raylib/raylib/examples/ZIIL-Zelda/assets/MONSTER_LIFE_SPRITESHEET.png");
	gameTextures[TXT_MONSTER_ATTACK] = LoadTexture("C:/raylib/raylib/examples/ZIIL-Zelda/assets/MONSTER_ATTACK_SPRITESHEET.png");
	gameTextures[TXT_MENU_BACKGROUND] = LoadTexture("C:/raylib/raylib/examples/ZIIL-Zelda/assets/MENU_BACKGROUND.png");
	gameTextures[TXT_MENU_BUTTONS] = LoadTexture("C:/raylib/raylib/examples/ZIIL-Zelda/assets/MENU_BUTTON_SPRITESHEET.png");
	gameTextures[TXT_MENU_SCOREBOARD] = LoadTexture("C:/raylib/raylib/examples/ZIIL-Zelda/assets/MENU_SCOREBOARD.png");



}

// Desenha o mapa
void drawMap(){

	// Desenha o plano de fundo
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

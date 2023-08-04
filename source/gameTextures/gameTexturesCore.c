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
	TXT_PLAYER_WALK
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

}

// Desenha o mapa
void drawMap(){

	// Desenha o plano de fundo
	for(int i = 0; i < TILE_LINES; i++){
		for(int j = 0; j < TILE_ROWS; j++){
			if(MAP[i][j] == 'B'){
				DrawTexture(gameTextures[TXT_GROUND], j * TILE_SIZE, (i * TILE_SIZE), WHITE);
			}
			else if(MAP[i][j] == 'O'){
				DrawTexture(gameTextures[TXT_ROCK], j * TILE_SIZE, i * TILE_SIZE, WHITE);
			}
		}
	}
}

// Atualiza no main loop
void gameTexturesUpdate(){

	drawMap();

}

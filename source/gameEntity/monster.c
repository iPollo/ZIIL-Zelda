// ===========================================================================
//			
//		Pac-Telma (Desenvolvido em C, usando Raylib)
//		Por: Aline Lux (335722) e Henrique Selau de Oliveira (338301)
//		Universidade Federal do Rio Grande do Sul - UFRGS
//		Algoritmos e Programação - PROF. Marcelo Walter
//
// ===========================================================================

#define MAX_MONSTER 50

// ===========================================================================
// 		Variáveis
// ===========================================================================

const float MONSTER_MOVE_SPEED = 1.5f;

Entity monster[MAX_MONSTER];

int monsterCount = 0;

// ===========================================================================
// 		Funções
// ===========================================================================


void monsterInit(){


	for(int i = 0; i < TILE_LINES; i++){
		for(int j = 0; j < TILE_ROWS; j++){
			if(MAP[i][j] == 'M'){
				monster[monsterCount].xPos = j * TILE_SIZE;
				monster[monsterCount].yPos = i * TILE_SIZE;
				monster[monsterCount].moveDirection = DIR_NONE;
				monster[monsterCount].moveSpeed = MONSTER_MOVE_SPEED;
				monster[monsterCount].isAttacking = false;
				monster[monsterCount].canAttack = true;
				monster[monsterCount].isVisible = true;
				monsterCount++;
			}
		}
	}

}

void monsterDraw(){

	for(int i = 0; i < monsterCount; i++){

		if(monster[i].isVisible){
		
			Rectangle tempTex3 = {PLAYER_SPRITE_DIMENSION * 0, PLAYER_SPRITE_DIMENSION * 0, PLAYER_SPRITE_DIMENSION, PLAYER_SPRITE_DIMENSION};
			DrawTextureRec(gameTextures[TXT_MONSTER_WALK], tempTex3, (Vector2){monster[i].xPos - 5 , monster[i].yPos - 3}, WHITE); 

			Rectangle tempTex2 = {PLAYER_SPRITE_DIMENSION * 1, PLAYER_SPRITE_DIMENSION * 0, PLAYER_SPRITE_DIMENSION, PLAYER_SPRITE_DIMENSION};
			DrawTextureRec(gameTextures[TXT_MONSTER_STATE], tempTex2, (Vector2){monster[i].xPos - 5 , monster[i].yPos -5}, WHITE); 
		

		}

	}


}

void monsterUpdate(){

	monsterDraw();

}

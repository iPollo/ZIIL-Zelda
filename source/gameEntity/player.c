// ===========================================================================
//			
//		Pac-Telma (Desenvolvido em C, usando Raylib)
//		Por: Aline Lux (335722) e Henrique Selau de Oliveira (338301)
//		Universidade Federal do Rio Grande do Sul - UFRGS
//		Algoritmos e Programação - PROF. Marcelo Walter
//
// ===========================================================================


#define WALK_ANIM_FRAME_SPEED 5

// ===========================================================================
// 		Variáveis
// ===========================================================================

const float PLAYER_MOVE_SPEED = 1.5f;
const float PLAYER_NORMALIZED_MOVE_SPEED = 1.2f;
const int PLAYER_SPRITE_DIMENSION = 65;

int ANIMFRAME_walk = 0;

int walkAnimSpriteIndex = 0;

Entity player;

bool collisionDirections[4];

enum{
	COLLISION_DIR_UP,
	COLLISION_DIR_DOWN,
	COLLISION_DIR_LEFT,
	COLLISION_DIR_RIGHT,
};

// ===========================================================================
// 		Funções
// ===========================================================================

void playerInit(){

	player.xPos = 0;
	player.yPos = 0;
	player.moveDirection = DIR_NONE;
	player.moveSpeed = PLAYER_MOVE_SPEED;
	//player.colideBox = {65}
}

bool isPlayerMoving(){

	if(!IsKeyDown(KEY_W) && !IsKeyDown(KEY_S) && !IsKeyDown(KEY_D) && !IsKeyDown(KEY_A)) return false;
	return true;

}


void playerDraw(){

	// Anim do movimento dos pés
	ANIMFRAME_walk++;

	if(ANIMFRAME_walk >= WALK_ANIM_FRAME_SPEED){
		if(walkAnimSpriteIndex > 3) walkAnimSpriteIndex = 0; 
		walkAnimSpriteIndex++;
		ANIMFRAME_walk = 0;
	}

	int idleAnimSpriteIndex = 1;
	if(isPlayerMoving()) idleAnimSpriteIndex = 1;
	else { 
		idleAnimSpriteIndex = 0;
		walkAnimSpriteIndex = 0;
	}


	Rectangle tempTex2 = {PLAYER_SPRITE_DIMENSION * walkAnimSpriteIndex, PLAYER_SPRITE_DIMENSION * idleAnimSpriteIndex, PLAYER_SPRITE_DIMENSION, PLAYER_SPRITE_DIMENSION};
	DrawTextureRec(gameTextures[TXT_PLAYER_WALK], tempTex2, (Vector2){player.xPos - 5 , player.yPos -5}, WHITE); 

	Rectangle tempTexture = {PLAYER_SPRITE_DIMENSION * player.moveDirection, PLAYER_SPRITE_DIMENSION * 0, PLAYER_SPRITE_DIMENSION, PLAYER_SPRITE_DIMENSION};
	DrawTextureRec(gameTextures[TXT_PLAYER_STATE], tempTexture, (Vector2){player.xPos - 5, player.yPos - 5}, WHITE);


	// For Debug
	//DrawRectangle(player.xPos, player.yPos, 50, 50, RED);
	for(int i = 0; i <= obstacleAmount; i++){
		//DrawRectangleRec(mapObstacle[i], BLUE);
	}
}

void playerCheckCollisions(){

	// Verifica a colisão lateral com a tela
	if(IsKeyDown(KEY_W) && ((player.yPos - player.moveSpeed) < 0)){
		collisionDirections[COLLISION_DIR_UP] = true;
	} else collisionDirections[COLLISION_DIR_UP] = false;

	if(IsKeyDown(KEY_S) && ((player.yPos + player.moveSpeed + TILE_SIZE) > SCREEN_HEIGHT)){
		collisionDirections[COLLISION_DIR_DOWN] = true;
	} else collisionDirections[COLLISION_DIR_DOWN] = false;
	
	if(IsKeyDown(KEY_D) && ((player.xPos + player.moveSpeed + TILE_SIZE) > SCREEN_WIDTH)){
		collisionDirections[COLLISION_DIR_RIGHT] = true;
	} else collisionDirections[COLLISION_DIR_RIGHT] = false;

	if(IsKeyDown(KEY_A) && ((player.xPos - player.moveSpeed) < 0)){
		collisionDirections[COLLISION_DIR_LEFT] = true;
	} else collisionDirections[COLLISION_DIR_LEFT] = false;


	
	// Checa a colisão dos objetos
	for(int i = 0; i <= obstacleAmount; i++){

		if(IsKeyDown(KEY_W) && CheckCollisionRecs(mapObstacle[i], (Rectangle){player.xPos, player.yPos-player.moveSpeed, 50, 50})) collisionDirections[COLLISION_DIR_UP] = true;
	
		if(IsKeyDown(KEY_S) && CheckCollisionRecs(mapObstacle[i], (Rectangle){player.xPos, player.yPos+player.moveSpeed, 50, 50})) collisionDirections[COLLISION_DIR_DOWN] = true;

		if(IsKeyDown(KEY_D) && CheckCollisionRecs(mapObstacle[i], (Rectangle){player.xPos+player.moveSpeed, player.yPos, 50, 50})) collisionDirections[COLLISION_DIR_RIGHT] = true;

		if(IsKeyDown(KEY_A) && CheckCollisionRecs(mapObstacle[i], (Rectangle){player.xPos-player.moveSpeed, player.yPos, 50, 50})) collisionDirections[COLLISION_DIR_LEFT] = true;

	}
}


void playerUpdateMoveDirection(){


	if(IsKeyDown(KEY_W)) player.moveDirection = DIR_UP;
	else if(IsKeyDown(KEY_S)) player.moveDirection = DIR_DOWN;

	if(IsKeyDown(KEY_A)) player.moveDirection = DIR_LEFT;
	else if(IsKeyDown(KEY_D)) player.moveDirection = DIR_RIGHT;

}

bool playerProcessMovement(){

	// Normaliza o vetor da velocidade na diagonals
	if((IsKeyDown(KEY_W) && IsKeyDown(KEY_A)) ||
	(IsKeyDown(KEY_W) && IsKeyDown(KEY_D)) ||
	(IsKeyDown(KEY_S) && IsKeyDown(KEY_A)) ||
	(IsKeyDown(KEY_S) && IsKeyDown(KEY_D)))
		player.moveSpeed = PLAYER_NORMALIZED_MOVE_SPEED;
	player.moveSpeed = PLAYER_MOVE_SPEED;


	// Atualiza a direção
	playerUpdateMoveDirection();

	// Verifica as colisões
	playerCheckCollisions();

	// Processa a direção do movimento e colisão lateral
	if(IsKeyDown(KEY_W) && !collisionDirections[COLLISION_DIR_UP]){;
		player.yPos -= player.moveSpeed;
		player.moveDirection = DIR_UP;
	}
	else if(IsKeyDown(KEY_S) && !collisionDirections[COLLISION_DIR_DOWN]) {
		player.yPos += player.moveSpeed;
		player.moveDirection = DIR_DOWN;
	}
	
	if(IsKeyDown(KEY_D) && !collisionDirections[COLLISION_DIR_RIGHT]) {
		player.xPos += player.moveSpeed;
		player.moveDirection = DIR_RIGHT;
	}
	else if(IsKeyDown(KEY_A) && !collisionDirections[COLLISION_DIR_LEFT]) {
		player.xPos -= player.moveSpeed;
		player.moveDirection = DIR_LEFT;
	}
    
    return false;
}

void playerUpdate(){
	playerProcessMovement();
	playerDraw();
}

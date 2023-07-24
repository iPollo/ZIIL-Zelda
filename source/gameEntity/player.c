// ===========================================================================
//			
//		Pac-Telma (Desenvolvido em C, usando Raylib)
//		Por: Aline Lux (335722) e Henrique Selau de Oliveira (338301)
//		Universidade Federal do Rio Grande do Sul - UFRGS
//		Algoritmos e Programação - PROF. Marcelo Walter
//
// ===========================================================================


// ===========================================================================
// 		Variáveis
// ===========================================================================

const float PLAYER_MOVE_SPEED = 1.5f;
const float PLAYER_NORMALIZED_MOVE_SPEED = 1.2f;

Entity player;

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

void playerDraw(){
	DrawRectangle(player.xPos, player.yPos, 50, 50, RED);


	for(int i = 0; i <= rockCounter; i++){
		DrawRectangleRec(mapCollideBox[i], BLUE);
	}

}

void playerCheckCollisions(){

	// Verifica a colisão lateral com a tela
	if((player.moveDirection == DIR_UP) && ((player.yPos - player.moveSpeed) < 0)){
		player.yPos = 0;
	}
	else if((player.moveDirection == DIR_DOWN) && ((player.yPos + player.moveSpeed + TILE_SIZE) > SCREEN_HEIGHT)){
		player.yPos = SCREEN_HEIGHT - TILE_SIZE;
	}
	
	else if((player.moveDirection == DIR_RIGHT) && ((player.xPos + player.moveSpeed + TILE_SIZE) > SCREEN_WIDTH)){
		player.xPos = SCREEN_WIDTH - TILE_SIZE;
	}
	else if((player.moveDirection == DIR_LEFT) && ((player.xPos - player.moveSpeed) < 0)){
		player.xPos = 0;
	}

	// General cases (diagonal)
	if((player.yPos < 0)) player.yPos = 0;
	if(((player.yPos + player.moveSpeed + TILE_SIZE) > SCREEN_HEIGHT)) player.yPos = SCREEN_HEIGHT - TILE_SIZE;


	// Checa a colisão dos objetos
	for(int i = 0; i <= rockCounter; i++){

		if(player.moveDirection == DIR_UP){
			if(CheckCollisionRecs(mapCollideBox[i], (Rectangle){player.xPos, player.yPos-player.moveSpeed, 50, 50})){
				player.yPos = mapCollideBox[i].y + TILE_SIZE;
			}
		}

		if(player.moveDirection == DIR_DOWN){
			if(CheckCollisionRecs(mapCollideBox[i], (Rectangle){player.xPos, player.yPos+player.moveSpeed, 50, 50})){
				player.yPos = mapCollideBox[i].y - TILE_SIZE;
			}
		}
		if(player.moveDirection == DIR_RIGHT){
			if(CheckCollisionRecs(mapCollideBox[i], (Rectangle){player.xPos+player.moveSpeed, player.yPos, 50, 50})){
				player.xPos = mapCollideBox[i].x - TILE_SIZE;
			}
		}

		if(player.moveDirection == DIR_DOWN){
			if(CheckCollisionRecs(mapCollideBox[i], (Rectangle){player.xPos-player.moveSpeed, player.yPos, 50, 50})){
				player.xPos = mapCollideBox[i].x + TILE_SIZE;
			}
		}

	}

}

void playerProcessMovement(){

	// Normaliza o vetor da velocidade na diagonals
	if((IsKeyDown(KEY_W) && IsKeyDown(KEY_A)) ||
	(IsKeyDown(KEY_W) && IsKeyDown(KEY_D)) ||
	(IsKeyDown(KEY_S) && IsKeyDown(KEY_A)) ||
	(IsKeyDown(KEY_S) && IsKeyDown(KEY_D)))
		player.moveSpeed = PLAYER_NORMALIZED_MOVE_SPEED;
	else player.moveSpeed = PLAYER_MOVE_SPEED;

	// Verifica as colisões
	playerCheckCollisions();

	// Processa a direção do movimento e colisão lateral
	if(IsKeyDown(KEY_W)){;
		player.yPos -= player.moveSpeed;
		player.moveDirection = DIR_UP;
	}
	else if(IsKeyDown(KEY_S)) {
		player.yPos += player.moveSpeed;
		player.moveDirection = DIR_DOWN;
	}
	
	if(IsKeyDown(KEY_D)) {
		player.xPos += player.moveSpeed;
		player.moveDirection = DIR_RIGHT;
	}
	else if(IsKeyDown(KEY_A)) {
		player.xPos -= player.moveSpeed;
		player.moveDirection = DIR_LEFT;
	}


}


void playerUpdate(){
	playerProcessMovement();
	playerDraw();
}

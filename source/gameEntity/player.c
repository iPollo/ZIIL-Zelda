// ===========================================================================
//			
//		Pac-Telma (Desenvolvido em C, usando Raylib)
//		Por: Aline Lux (335722) e Henrique Selau de Oliveira (338301)
//		Universidade Federal do Rio Grande do Sul - UFRGS
//		Algoritmos e Programação - PROF. Marcelo Walter
//
// ===========================================================================

// Defines utilitários para o jogador
// Defines marcados com ANIM/FRAME são usados para controlar a animação dos sprites 
#define WALK_ANIM_FRAME_SPEED 5
#define PLAYER_ATTACK_COLDOWN 20
#define MAX_PLAYER_LIFES 3
#define ATTACK_ANIM_FRAME_SPEED 3

// Cores utilizadas para debug
#define COLLOR_TEXT  CLITERAL(Color){ 255, 234, 117, 255 }
#define COLLOR_HITBOX  CLITERAL(Color){ 255, 0, 0, 200 }

// ===========================================================================
// 		Variáveis
// ===========================================================================

// Constantes globais utilitárias do jogador
const float PLAYER_MOVE_SPEED = 1.5f;
const float PLAYER_NORMALIZED_MOVE_SPEED = 1.2f;
const int PLAYER_SPRITE_DIMENSION = 65;

// Variáveis globais de animação do jogador
int ANIMFRAME_walk = 0; 
int ANIMFRAME_attack = 0;
int walkAnimSpriteIndex = 0;
int attackAnimSpriteIndex = 0;
int playerColDownAttack = 0;

// Inicializa a variável do tipo Entidade que guarda a informação do jogador
Entity player;

// Direções possíveis para movimentação do jogador baseado nas colisões do mapa
bool collisionDirections[4];

// ===========================================================================
// 		Funções
// ===========================================================================

// Inicializa o jogador definindo os dados principais padrões
void playerInit(bool resetData){

	// Define a posição inicial do jogador (de acordo com o J definido no arquivo do nível)
	for(int i = 0; i < TILE_LINES; i++){
		for(int j = 0; j < TILE_ROWS; j++){
			if(MAP[i][j] == 'J'){
				player.xPos = j*TILE_SIZE;
				player.yPos = i*TILE_SIZE;
			}
		}
	}


	// Define os dados de movimento, velocidade e posição original do jogador
	player.moveDirection = DIR_NONE;
	player.moveSpeed = PLAYER_MOVE_SPEED;
	player.originalPosition.x = player.xPos;
	player.originalPosition.y = player.yPos;

	// Dados gerais do jogador, são resetados caso ele morra
	if(!resetData) return;
	player.isAttacking = false;
	player.canAttack = true;
	player.life = 3;
	player.score = 0;
	player.level = 1;
}

// Verifica se o jogadro está se movendo, retornando true caso verdadeiro
bool isPlayerMoving(){
	if(!IsKeyDown(KEY_W) && !IsKeyDown(KEY_S) && !IsKeyDown(KEY_D) && !IsKeyDown(KEY_A)) return false;
	return true;
}

// Desenha a HUD do jogador (Desing que mostra o nível, vida, level)
void playerDrawHud(){

	// Desenha o design da vida e do score
	DrawTexturePro(gameTextures[TXT_HUD_SCORE], (Rectangle){0,0,44,120}, (Rectangle){20, 80, 50, 136}, (Vector2){0,0},0, WHITE);
	DrawTexturePro(gameTextures[TXT_HUD_LIFE], (Rectangle){0,0,161,64}, (Rectangle){20, 20, 201, 80}, (Vector2){0,0},0, WHITE);
	DrawTexturePro(gameTextures[TXT_HUD_SCOREBACK], (Rectangle){0,0,25,20}, (Rectangle){70, 119, 45, 35}, (Vector2){0,0},0, WHITE);
	DrawTexturePro(gameTextures[TXT_HUD_SCOREBACK], (Rectangle){0,0,25,20}, (Rectangle){70, 172, 45, 35}, (Vector2){0,0},0, WHITE);
	
	// Desenha as barras de vida de acordo com a quantidade de vida do jogador
	for(int i = 0; i < MAX_PLAYER_LIFES; i++){
		if(i < player.life){
			DrawTexturePro(gameTextures[TXT_HUD_LIFEBAR], (Rectangle){0,0,161,64}, (Rectangle){20 + i*19, 21, 201, 80}, (Vector2){0,0},0, WHITE);
		}
	}

	// Mostra o texto do score e level
	DrawText(TextFormat("%d", player.score), 79, 130, 15, COLLOR_TEXT); 
	DrawText(TextFormat("%d", player.level), 79, 183, 15, COLLOR_TEXT); 
}

// Desenha o jogador na tela
void playerDraw(){

	// Animação do movimento dos pés
	ANIMFRAME_walk++;
	if(ANIMFRAME_walk >= WALK_ANIM_FRAME_SPEED){
		if(walkAnimSpriteIndex > 3) walkAnimSpriteIndex = 0; 
		walkAnimSpriteIndex++;
		ANIMFRAME_walk = 0;
	}

	// Atualiza os indexs de animação do jogador
	int idleAnimSpriteIndex = 1;
	if(isPlayerMoving()) idleAnimSpriteIndex = 1;
	else { 
		idleAnimSpriteIndex = 0;
		walkAnimSpriteIndex = 0;
	}

	// Desenha a animação dos pés do jgoador
	Rectangle tempTex2 = {PLAYER_SPRITE_DIMENSION * walkAnimSpriteIndex, PLAYER_SPRITE_DIMENSION * idleAnimSpriteIndex, PLAYER_SPRITE_DIMENSION, PLAYER_SPRITE_DIMENSION};
	DrawTextureRec(gameTextures[TXT_PLAYER_WALK], tempTex2, (Vector2){player.xPos - 5 , player.yPos -5}, WHITE); 		

	// Desenha o sprite do jogador
	if(!player.isAttacking){
		Rectangle tempTexture = {PLAYER_SPRITE_DIMENSION * player.moveDirection, PLAYER_SPRITE_DIMENSION * 0, PLAYER_SPRITE_DIMENSION, PLAYER_SPRITE_DIMENSION};
		DrawTextureRec(gameTextures[TXT_PLAYER_STATE], tempTexture, (Vector2){player.xPos - 5, player.yPos - 5}, WHITE);
	}
}

// Verifica as colisões nas direções de movimento do jogador
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

		if(IsKeyDown(KEY_W) && CheckCollisionRecs(mapObstacle[i], (Rectangle){player.xPos + 18, player.yPos + 20-player.moveSpeed, 15, 25})) collisionDirections[COLLISION_DIR_UP] = true;	
		if(IsKeyDown(KEY_S) && CheckCollisionRecs(mapObstacle[i], (Rectangle){player.xPos + 18, player.yPos + 20+player.moveSpeed, 15, 25})) collisionDirections[COLLISION_DIR_DOWN] = true;
		if(IsKeyDown(KEY_D) && CheckCollisionRecs(mapObstacle[i], (Rectangle){player.xPos + 18+player.moveSpeed,  player.yPos + 20, 15, 25})) collisionDirections[COLLISION_DIR_RIGHT] = true;
		if(IsKeyDown(KEY_A) && CheckCollisionRecs(mapObstacle[i], (Rectangle){player.xPos + 18-player.moveSpeed,  player.yPos + 20, 15, 25})) collisionDirections[COLLISION_DIR_LEFT] = true;

	}
}

// Atualiza os dados das variáveis do jogador (angulo e direção do movimento)
void playerUpdateMoveDirection(){

	// Direção do movimento
	if(IsKeyDown(KEY_W)) player.moveDirection = DIR_UP;
	else if(IsKeyDown(KEY_S)) player.moveDirection = DIR_DOWN;
	if(IsKeyDown(KEY_A)) player.moveDirection = DIR_LEFT;
	else if(IsKeyDown(KEY_D)) player.moveDirection = DIR_RIGHT;

	// Atualiza o hitbox da espada do jogador
	if(player.moveDirection == DIR_UP){
		player.attackHitBox = (Rectangle){player.xPos-7, player.yPos-50, 70, 80};
	}
	else if(player.moveDirection == DIR_DOWN){
		player.attackHitBox = (Rectangle){player.xPos-7, player.yPos+30, 70, 80};	
	}
	else if(player.moveDirection == DIR_LEFT){
		player.attackHitBox = (Rectangle){player.xPos-50, player.yPos-10, 80, 70};	
	}
	else if(player.moveDirection == DIR_RIGHT){
		player.attackHitBox = (Rectangle){player.xPos+25, player.yPos-10, 80, 70};
	}
}

// Processa e atualiza as informações do ataque do jogador com a espada
bool playerProcessAttack(){

	// Coldown para atacar novamente (tempo entre os ataques para não ficar spamando o ataque)
	if(!player.canAttack){
		playerColDownAttack++;
		if(playerColDownAttack >= PLAYER_ATTACK_COLDOWN){
			playerColDownAttack = 0;
			player.canAttack = true;
		}
		return false;
	}


	// Processa o ataque
	if(player.isAttacking){

		// Atualiza os dados para animação dos sprites do jogador
		ANIMFRAME_attack++;
		if(ANIMFRAME_attack >= ATTACK_ANIM_FRAME_SPEED){
			attackAnimSpriteIndex++;
			ANIMFRAME_attack = 0;
		}

		// Calcula os retangulos inicias para desenhar os sprites
		Rectangle tempRec = {(PLAYER_SPRITE_DIMENSION) * attackAnimSpriteIndex, PLAYER_SPRITE_DIMENSION * 1, PLAYER_SPRITE_DIMENSION, PLAYER_SPRITE_DIMENSION};
		Rectangle tempRec2 = {(PLAYER_SPRITE_DIMENSION) * attackAnimSpriteIndex, PLAYER_SPRITE_DIMENSION * player.moveDirection, PLAYER_SPRITE_DIMENSION, PLAYER_SPRITE_DIMENSION};

		// Atualiza o angulo de movimento do jogador e a direção
		int xPosOffset = 0;
		int yPosOffset = 0;
		int rotOffset = 0;

		if(player.moveDirection == DIR_UP){
			xPosOffset = 0;
			yPosOffset = PLAYER_SPRITE_DIMENSION/2 * - 1;
			rotOffset = 270;
		}
		if(player.moveDirection == DIR_DOWN){
			xPosOffset = 0;
			yPosOffset = PLAYER_SPRITE_DIMENSION/2;
			rotOffset = 90;
		}
		if(player.moveDirection == DIR_LEFT){
			xPosOffset = PLAYER_SPRITE_DIMENSION/2 * - 1;
			yPosOffset = 0;
			rotOffset = 180;
		}
		if(player.moveDirection == DIR_RIGHT){
			xPosOffset = PLAYER_SPRITE_DIMENSION/2;
			yPosOffset = 0;
			rotOffset = 0;
		}

		// Desenha os sprites do slash (ataque com a espada do jogador)
		Rectangle destRec = {(player.xPos + (PLAYER_SPRITE_DIMENSION/2) - 5) + xPosOffset, (player.yPos + (PLAYER_SPRITE_DIMENSION/2) - 5) + yPosOffset, PLAYER_SPRITE_DIMENSION, PLAYER_SPRITE_DIMENSION};
		DrawTextureRec(gameTextures[TXT_ATTACK], tempRec2, (Vector2){player.xPos -5 , player.yPos -5}, WHITE); 
		DrawTexturePro(gameTextures[TXT_SLASH], tempRec, destRec, (Vector2){(PLAYER_SPRITE_DIMENSION/2), (PLAYER_SPRITE_DIMENSION/2)}, rotOffset, WHITE);

		// Reseta as informações dos dados para animação do ataque
		if(attackAnimSpriteIndex == 2){
			player.isAttacking = false;
			player.canAttack = false;
			ANIMFRAME_attack = 0;
			attackAnimSpriteIndex = 0;
		}
	}

	// Processa o ataque com J do jogador
	else if(IsKeyPressed(KEY_J)){

		// Atualiza os dados
		player.isAttacking = true;

		// Toca o efeito senero
		PlaySound(gameSound[SFX_SWORD_SLASH]);
	}
    return false;
}

// Processa e atualiza as informações do movimento do jogador
bool playerProcessMovement(){

	// Normaliza o vetor da velocidade na diagonal
	if((IsKeyDown(KEY_W) && IsKeyDown(KEY_A)) ||
	(IsKeyDown(KEY_W) && IsKeyDown(KEY_D)) ||
	(IsKeyDown(KEY_S) && IsKeyDown(KEY_A)) ||
	(IsKeyDown(KEY_S) && IsKeyDown(KEY_D)))
	player.moveSpeed = PLAYER_NORMALIZED_MOVE_SPEED;
	player.moveSpeed = PLAYER_MOVE_SPEED;

	// Atualiza a direção do movimento
	playerUpdateMoveDirection();

	// Verifica as colisões da direção
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

// Reseta a data do jogador
void playerResetData(){
	player.moveDirection = DIR_NONE;
	player.moveSpeed = PLAYER_MOVE_SPEED;
	player.originalPosition.x = player.xPos;
	player.originalPosition.y = player.yPos;
	player.isAttacking = false;
	player.canAttack = true;
	player.life = 3;
	player.score = 0;
	player.level = 1;
}

// Atualiza as informações do jogador
void playerUpdate(){
	if(isGameOver) return;
	playerProcessMovement();
	playerProcessAttack();
	playerDraw();
	playerDrawHud();
}

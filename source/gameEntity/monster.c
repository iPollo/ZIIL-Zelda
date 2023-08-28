// ===========================================================================
//			
//		Pac-Telma (Desenvolvido em C, usando Raylib)
//		Por: Aline Lux (335722) e Henrique Selau de Oliveira (338301)
//		Universidade Federal do Rio Grande do Sul - UFRGS
//		Algoritmos e Programação - PROF. Marcelo Walter
//
// ===========================================================================

#define MAX_MONSTER 50
#define MAX_MONSTER_LIFE 3
#define MONSTER_WALK_ANIM_FRAME_SPEED 40
#define MONSTER_HIT_ANIM_FRAME_SPEED 10
#define MONSTER_ATTACK_ANIM_FRAME_SPEED 10
#define MONSTER_ATTACK_MIN_RANGE 50

// ===========================================================================
// 		Variáveis
// ===========================================================================

const float MONSTER_MOVE_SPEED = 1.5f;
const float MONSTER_HITBOX_DISTANCE = 80.0f;
const int MAX_MONSTER_MOVE_SPEED = 7;
const int MIN_MONSTER_MOVE_SPEED = 5;
const float MAX_MONSTER_FOLLOW_DISTANCE = 200.0;

const int MIN_MONSTER_FOLLOW_OFFSET = -50;
const int MAX_MONSTER_FOLLOW_OFFSET = 50;

int ANIMFRAME_monsterWalk = 0;
int ANIMFRAME_monsterHited = 0;
int monsterWalkSpriteIndex = 0;

Entity monster[MAX_MONSTER];

int monsterCollisionDirection[MAX_MONSTER][4];
int monsterCount = 0;

// ===========================================================================
// 		Funções
// ===========================================================================

void monsterInit(){

	monsterCount = 0;

	for(int i = 0; i < TILE_LINES; i++){
		for(int j = 0; j < TILE_ROWS; j++){
			if(MAP[i][j] == 'O'){
				monster[monsterCount].xPos = j * TILE_SIZE;
				monster[monsterCount].yPos = i * TILE_SIZE;
				monster[monsterCount].moveDirection = DIR_NONE;
				monster[monsterCount].moveSpeed = (GetRandomValue(MIN_MONSTER_MOVE_SPEED, MAX_MONSTER_MOVE_SPEED))/10.0;
				monster[monsterCount].isAttacking = false;
				monster[monsterCount].canAttack = true;
				monster[monsterCount].isVisible = true;
				monster[monsterCount].isFollowing = false;
				monster[monsterCount].life = MAX_MONSTER_LIFE;
				monster[monsterCount].hits = 0;
				monster[monsterCount].originalPosition.x = monster[monsterCount].xPos;
				monster[monsterCount].originalPosition.y = monster[monsterCount].yPos;
				monster[monsterCount].attackSpriteIndex = 0;
				monster[monsterCount].animframe_attack = 0;
				monster[monsterCount].unfollowMoveXPos = GetRandomValue(1, SCREEN_WIDTH);
				monster[monsterCount].unfollowMoveYPos = GetRandomValue(1, SCREEN_HEIGHT);
				monster[monsterCount].xFollowOffset = GetRandomValue(MIN_MONSTER_FOLLOW_OFFSET, MAX_MONSTER_FOLLOW_OFFSET);
				monster[monsterCount].yFollowOffset = GetRandomValue(MIN_MONSTER_FOLLOW_OFFSET, MAX_MONSTER_FOLLOW_OFFSET);
				
				monsterCollisionDirection[monsterCount][COLLISION_DIR_UP] = false;
				monsterCollisionDirection[monsterCount][COLLISION_DIR_DOWN] = false;
				monsterCollisionDirection[monsterCount][COLLISION_DIR_LEFT] = false;
				monsterCollisionDirection[monsterCount][COLLISION_DIR_RIGHT] = false;

				monsterCount++;
			}
		}
	}
}

void monsterDraw(int mid){

	if(monster[mid].isVisible){

			// Anim do movimento dos pés
		ANIMFRAME_monsterWalk++;

		if(ANIMFRAME_monsterWalk >= MONSTER_WALK_ANIM_FRAME_SPEED){
			if(monsterWalkSpriteIndex > 3) monsterWalkSpriteIndex = 0; 
			monsterWalkSpriteIndex++;
			ANIMFRAME_monsterWalk = 0;
		}


		// Desenha cada elemento

		Rectangle tempTex3 = {PLAYER_SPRITE_DIMENSION * monsterWalkSpriteIndex, PLAYER_SPRITE_DIMENSION * 1, PLAYER_SPRITE_DIMENSION, PLAYER_SPRITE_DIMENSION};
		DrawTextureRec(gameTextures[TXT_MONSTER_WALK], tempTex3, (Vector2){monster[mid].xPos - 5 , monster[mid].yPos - 3}, WHITE); 


		if(monster[mid].isBeingHited){
			monster[mid].animframe_hit++;

			if(monster[mid].animframe_hit++ > MONSTER_HIT_ANIM_FRAME_SPEED){
				monster[mid].animframe_hit = 0;
				monster[mid].isBeingHited = false;
			}

			Rectangle tt3 = {PLAYER_SPRITE_DIMENSION * monster[mid].moveDirection, PLAYER_SPRITE_DIMENSION * 0, PLAYER_SPRITE_DIMENSION, PLAYER_SPRITE_DIMENSION};
			DrawTextureRec(gameTextures[TXT_MONSTER_HIT_STATE], tt3, (Vector2){monster[mid].xPos - 5 , monster[mid].yPos -5}, WHITE); 
	

		}
		else{




			//DrawTexturePro(gameTextures[TXT_MONSTER_ATTACK], (Rectangle){256*monster[mid].attackSpriteIndex,0,256,256}, (Rectangle){monster[mid].xPos -200/2 + 18, monster[mid].yPos - 200/2 + 25, 200, 200}, (Vector2){0,0},0, WHITE);
			



			Rectangle tempTex2 = {PLAYER_SPRITE_DIMENSION * monster[mid].moveDirection, PLAYER_SPRITE_DIMENSION * 0, PLAYER_SPRITE_DIMENSION, PLAYER_SPRITE_DIMENSION};
			DrawTextureRec(gameTextures[TXT_MONSTER_STATE], tempTex2, (Vector2){monster[mid].xPos - 5 , monster[mid].yPos -5}, WHITE); 
	
			DrawTexturePro(gameTextures[TXT_MONSTER_LIFE_SPRITESHEET], (Rectangle){0,286 * (monster[mid].hits-3*-1),1051,286}, (Rectangle){monster[mid].xPos + 5, monster[mid].yPos - 10, 37, 10}, (Vector2){0,0},0, WHITE);
			
			if(monster[mid].isFollowing){
				
			
				Rectangle t3 = {PLAYER_SPRITE_DIMENSION * monster[mid].moveDirection, PLAYER_SPRITE_DIMENSION * 0, PLAYER_SPRITE_DIMENSION, PLAYER_SPRITE_DIMENSION};		
				DrawTextureRec(gameTextures[TXT_MONSTER_FOLLOW_STATE], t3, (Vector2){monster[mid].xPos - 5 , monster[mid].yPos -5}, WHITE); 
			}


		}


	}
}

void monsterCheckNewDirection(int mid){

	if(monster[mid].isFollowing) return;


	for(int i = 0; i < 4; i++){
		if(monsterCollisionDirection[mid][monster[mid].moveDirection]){
			monster[mid].unfollowMoveXPos = GetRandomValue(1, SCREEN_WIDTH);
			monster[mid].unfollowMoveYPos = GetRandomValue(1, SCREEN_HEIGHT);
		}
	}

}

void monsterUpdateMoveDirection(int mid){
    
    if(!monster[mid].isFollowing){
		monster[mid].angleMoveDirection = getAngleBetweenPoints(monster[mid].xPos+30, monster[mid].yPos+30, monster[mid].unfollowMoveXPos, monster[mid].unfollowMoveYPos);
   		//DrawLineV((Vector2){monster[4].xPos+30, monster[4].yPos+30}, (Vector2){monster[4].unfollowMoveXPos, monster[4].unfollowMoveYPos}, RED);
    }
	else{
		monster[mid].angleMoveDirection = getAngleBetweenPoints(monster[mid].xPos+30, monster[mid].yPos+30, player.xPos+30, player.yPos+30);
		//DrawLineV((Vector2){monster[4].xPos+30, monster[4].yPos+30}, (Vector2){player.xPos+30, player.yPos+30}, RED);
	}

	//DrawLineV((Vector2){monster[4].xPos, monster[4].yPos}, (Vector2){SCREEN_WIDTH/2, SCREEN_HEIGHT/2}, RED);
	//TraceLog(LOG_INFO, "ANGLE: %f", monster[4].angleMoveDirection);

	if((monster[mid].angleMoveDirection > 0 && monster[mid].angleMoveDirection < 45) || (monster[mid].angleMoveDirection > 315 && monster[mid].angleMoveDirection < 350)){
		monster[mid].moveDirection = DIR_RIGHT;
		//TraceLog(LOG_INFO, "RIGHT: %f", monster[mid].angleMoveDirection);
	}
	if((monster[mid].angleMoveDirection > 45 && monster[mid].angleMoveDirection < 135)){
		monster[mid].moveDirection = DIR_DOWN;
		//TraceLog(LOG_INFO, "DOWN: %f", monster[mid].angleMoveDirection);
	}
	if((monster[mid].angleMoveDirection > 135 && monster[mid].angleMoveDirection < 225)){
		monster[mid].moveDirection = DIR_LEFT;
		//TraceLog(LOG_INFO, "LEFT: %f", monster[mid].angleMoveDirection);
	}
	if((monster[mid].angleMoveDirection > 225 && monster[mid].angleMoveDirection < 315)){
		monster[mid].moveDirection = DIR_UP;
		//TraceLog(LOG_INFO, "UP: %f", monster[4].angleMoveDirection);
	}
}

bool monsterCheckCollisions(int mid){

	if(monster[mid].moveDirection == DIR_UP && ((monster[mid].yPos - monster[mid].moveSpeed) < 0)){
		monsterCollisionDirection[mid][COLLISION_DIR_UP] = true;
	} else monsterCollisionDirection[mid][COLLISION_DIR_UP] = false;

	if(monster[mid].moveDirection == DIR_DOWN && ((monster[mid].yPos + monster[mid].moveSpeed + TILE_SIZE) > SCREEN_HEIGHT)){
		monsterCollisionDirection[mid][COLLISION_DIR_DOWN] = true;
	} else monsterCollisionDirection[mid][COLLISION_DIR_DOWN] = false;
	
	if(monster[mid].moveDirection == DIR_RIGHT && ((monster[mid].xPos + monster[mid].moveSpeed + TILE_SIZE) > SCREEN_WIDTH)){
		monsterCollisionDirection[mid][COLLISION_DIR_RIGHT] = true;
	} else monsterCollisionDirection[mid][COLLISION_DIR_RIGHT] = false;

	if(monster[mid].moveDirection == DIR_LEFT && ((monster[mid].xPos - monster[mid].moveSpeed) < 0)){
		monsterCollisionDirection[mid][COLLISION_DIR_LEFT] = true;
	} else monsterCollisionDirection[mid][COLLISION_DIR_LEFT] = false;

	// Checa a colisão dos objetos
	for(int i = 0; i <= obstacleAmount; i++){

		if(monster[mid].moveDirection == DIR_UP && CheckCollisionRecs(mapObstacle[i], (Rectangle){monster[mid].xPos + 18, monster[mid].yPos + 20-monster[mid].moveSpeed, 15, 25})) monsterCollisionDirection[mid][COLLISION_DIR_UP] = true;
	
		if(monster[mid].moveDirection == DIR_DOWN && CheckCollisionRecs(mapObstacle[i], (Rectangle){monster[mid].xPos + 18, monster[mid].yPos + 20+monster[mid].moveSpeed, 15, 25})) monsterCollisionDirection[mid][COLLISION_DIR_DOWN] = true;

		if(monster[mid].moveDirection == DIR_RIGHT && CheckCollisionRecs(mapObstacle[i], (Rectangle){monster[mid].xPos + 18+monster[mid].moveSpeed,  monster[mid].yPos + 20, 15, 25})) monsterCollisionDirection[mid][COLLISION_DIR_RIGHT] = true;

		if(monster[mid].moveDirection == DIR_LEFT && CheckCollisionRecs(mapObstacle[i], (Rectangle){monster[mid].xPos + 18-monster[mid].moveSpeed,  monster[mid].yPos + 20, 15, 25})) monsterCollisionDirection[mid][COLLISION_DIR_LEFT] = true;

	}

	if(monster[mid].moveDirection == DIR_UP && monsterCollisionDirection[mid][COLLISION_DIR_UP]) return true;
	if(monster[mid].moveDirection == DIR_DOWN && monsterCollisionDirection[mid][COLLISION_DIR_DOWN]) return true;
	if(monster[mid].moveDirection == DIR_LEFT && monsterCollisionDirection[mid][COLLISION_DIR_LEFT]) return true;
	if(monster[mid].moveDirection == DIR_RIGHT && monsterCollisionDirection[mid][COLLISION_DIR_RIGHT]) return true;

	return false;
}

void monsterCheckIfPlayerHit(int mid){

	if(!monster[mid].isVisible) return;

	double distance = getDistanceBetweenPoints(player.xPos, player.yPos, monster[mid].xPos, monster[mid].yPos);

	bool isHitable = CheckCollisionRecs(player.attackHitBox, (Rectangle){monster[mid].xPos + 18, monster[mid].yPos + 20, 15, 25});

	if(IsKeyPressed(KEY_J) && (isHitable) && player.canAttack){
		monster[mid].isBeingHited = true;
		monster[mid].animframe_hit = 0;
		monster[mid].hits++;

		if(monster[mid].hits == MAX_MONSTER_LIFE){
			monster[mid].isVisible = false;
			player.score++;
		}

	
		double angulo = getAngleBetweenPoints(monster[mid].xPos+30, monster[mid].yPos+30, player.xPos+30+monster[mid].xFollowOffset, player.yPos+30+monster[mid].yFollowOffset);
		
		Vector2 newPos = getVectorByAngleDistance(angulo, (monster[mid].moveSpeed) * -2);
	

		//if(monsterCheckCollisions(mid)) return false;

		monster[mid].xPos += newPos.x;
		monster[mid].yPos += newPos.y;

	}
}

void monsterCheckIfHitPlayer(int mid){

	if(!monster[mid].isVisible) return;

	double distance = getDistanceBetweenPoints(player.xPos, player.yPos, monster[mid].xPos, monster[mid].yPos);

	if(distance < MONSTER_ATTACK_MIN_RANGE){
		player.life--;
		resetMapConfigs();
	}
}

bool monsterCheckIfAllDie(){
	for(int i = 0; i < monsterCount; i++){
		if(monster[i].isVisible) return false;
	}

	return true;
}

bool monsterMove(int mid){

	monsterCheckNewDirection(mid);

	if(getDistanceBetweenPoints(monster[mid].xPos+30, monster[mid].yPos+30, player.xPos+30+monster[mid].xFollowOffset, player.yPos+30+monster[mid].yFollowOffset) > MAX_MONSTER_FOLLOW_DISTANCE){
		
		monster[mid].isFollowing = false;

		if(getDistanceBetweenPoints(monster[mid].xPos+30, monster[mid].yPos+30, monster[mid].unfollowMoveXPos, monster[mid].unfollowMoveYPos) < 100){
			monster[mid].unfollowMoveXPos = GetRandomValue(1, SCREEN_WIDTH);
			monster[mid].unfollowMoveYPos = GetRandomValue(1, SCREEN_HEIGHT);
		}

		double angulo = getAngleBetweenPoints(monster[mid].xPos+30, monster[mid].yPos+30, monster[mid].unfollowMoveXPos, monster[mid].unfollowMoveYPos);
		
		Vector2 newPos = getVectorByAngleDistance(angulo, monster[mid].moveSpeed);

		if(monsterCheckCollisions(mid)) return false;

		monster[mid].xPos += newPos.x;
		monster[mid].yPos += newPos.y;

	}
	else{
		
		monster[mid].isFollowing = true;

		double angulo = getAngleBetweenPoints(monster[mid].xPos+30, monster[mid].yPos+30, player.xPos+30+monster[mid].xFollowOffset, player.yPos+30+monster[mid].yFollowOffset);
		
		Vector2 newPos = getVectorByAngleDistance(angulo, monster[mid].moveSpeed);
	
		if(monsterCheckCollisions(mid)) return false;

		monster[mid].xPos += newPos.x;
		monster[mid].yPos += newPos.y;

	}

	return true;
}

void monsterUpdate(){

	for(int i = 0; i < monsterCount; i++){
		monsterUpdateMoveDirection(i);
		monsterMove(i);
		monsterCheckIfPlayerHit(i);
		monsterCheckIfHitPlayer(i);
		monsterDraw(i);
	}

	if(monsterCheckIfAllDie()){
		loadNewLevel(player.level);
		player.level++;
	}
}

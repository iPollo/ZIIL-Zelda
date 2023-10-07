// ===========================================================================
//			
//		Pac-Telma (Desenvolvido em C, usando Raylib)
//		Por: Aline Lux (335722) e Henrique Selau de Oliveira (338301)
//		Universidade Federal do Rio Grande do Sul - UFRGS
//		Algoritmos e Programação - PROF. Marcelo Walter
//
// ===========================================================================

// Defines utilitários para os monstros
// Defines marcados com ANIM/FRAME são usados para controlar a animação dos sprites 
#define MAX_MONSTER 50
#define MAX_MONSTER_LIFE 3
#define MONSTER_WALK_ANIM_FRAME_SPEED 40
#define MONSTER_HIT_ANIM_FRAME_SPEED 10
#define MONSTER_ATTACK_ANIM_FRAME_SPEED 10
#define MONSTER_ATTACK_MIN_RANGE 50

// ===========================================================================
// 		Variáveis
// ===========================================================================

// Constantes globais utilitárias dos monstros
const float MONSTER_MOVE_SPEED = 1.5f;
const float MONSTER_HITBOX_DISTANCE = 80.0f;
const int MAX_MONSTER_MOVE_SPEED = 7;
const int MIN_MONSTER_MOVE_SPEED = 5;
const float MAX_MONSTER_FOLLOW_DISTANCE = 200.0;

// Distancia mínima e máxima para um monstro seguir e atacar um jogador
const int MIN_MONSTER_FOLLOW_OFFSET = -50;
const int MAX_MONSTER_FOLLOW_OFFSET = 50;

// Variáveis globais de animação geral (atualiza o frame de todosos monstros)
int ANIMFRAME_monsterWalk = 0;
int ANIMFRAME_monsterHited = 0;
int monsterWalkSpriteIndex = 0;

// Inicializa a variável do tipo Entidade que guarda a informação de todos os monstros e a quantidade
Entity monster[MAX_MONSTER];
int monsterCount = 0;

// Direções possíveis para movimentação dos monstros baseado nas colisões do mapa
int monsterCollisionDirection[MAX_MONSTER][4];

// ===========================================================================
// 		Funções
// ===========================================================================

// Inicializa os monstros definindo os dados principais padrões
void monsterInit(){

	// Zera o número de monstros para inicializar
	monsterCount = 0;

	for(int i = 0; i < TILE_LINES; i++){
		for(int j = 0; j < TILE_ROWS; j++){
			if(MAP[i][j] == 'O'){

				// Coloca o monstro em sua posição do mapa
				monster[monsterCount].xPos = j * TILE_SIZE;
				monster[monsterCount].yPos = i * TILE_SIZE;

				// Direção e velocidade de movimento (cada monstro possui uma pequena variação aleatória na velocidade)
				monster[monsterCount].moveDirection = DIR_NONE;
				monster[monsterCount].moveSpeed = (GetRandomValue(MIN_MONSTER_MOVE_SPEED, MAX_MONSTER_MOVE_SPEED))/10.0;

				// Dados gerais dos monstros
				monster[monsterCount].isAttacking = false;
				monster[monsterCount].canAttack = true;
				monster[monsterCount].isVisible = true;
				monster[monsterCount].isFollowing = false;
				monster[monsterCount].life = MAX_MONSTER_LIFE;
				monster[monsterCount].hits = 0;

				// Posição original de cada monstro, usada para resetar caso o jogador sofra dano
				monster[monsterCount].originalPosition.x = monster[monsterCount].xPos;
				monster[monsterCount].originalPosition.y = monster[monsterCount].yPos;

				// Dados para animação dos sprites
				monster[monsterCount].attackSpriteIndex = 0;
				monster[monsterCount].animframe_attack = 0;

				// Posição aleatória para qual o monstro vai quando não está seguindo o jogador
				monster[monsterCount].unfollowMoveXPos = GetRandomValue(1, SCREEN_WIDTH);
				monster[monsterCount].unfollowMoveYPos = GetRandomValue(1, SCREEN_HEIGHT);
				monster[monsterCount].xFollowOffset = GetRandomValue(MIN_MONSTER_FOLLOW_OFFSET, MAX_MONSTER_FOLLOW_OFFSET);
				monster[monsterCount].yFollowOffset = GetRandomValue(MIN_MONSTER_FOLLOW_OFFSET, MAX_MONSTER_FOLLOW_OFFSET);
				
				// Valores booleanos para a colisão em todas as direções
				monsterCollisionDirection[monsterCount][COLLISION_DIR_UP] = false;
				monsterCollisionDirection[monsterCount][COLLISION_DIR_DOWN] = false;
				monsterCollisionDirection[monsterCount][COLLISION_DIR_LEFT] = false;
				monsterCollisionDirection[monsterCount][COLLISION_DIR_RIGHT] = false;

				// Contagem geral de monstros
				monsterCount++;
			}
		}
	}
}

// Desenha os monstros na tela (mid = monsterid, ou seja, o id do monstro que está sendo desenhado)
void monsterDraw(int mid){

	// Desenha caso o monstro esteja visível
	if(monster[mid].isVisible){

		// Controla a anima~ção do movimento dos pés
		ANIMFRAME_monsterWalk++;
		if(ANIMFRAME_monsterWalk >= MONSTER_WALK_ANIM_FRAME_SPEED){
			if(monsterWalkSpriteIndex > 3) monsterWalkSpriteIndex = 0; 
			monsterWalkSpriteIndex++;
			ANIMFRAME_monsterWalk = 0;
		}

		// Desenha e anima os pés dos monstros
		Rectangle tempTex3 = {PLAYER_SPRITE_DIMENSION * monsterWalkSpriteIndex, PLAYER_SPRITE_DIMENSION * 1, PLAYER_SPRITE_DIMENSION, PLAYER_SPRITE_DIMENSION};
		DrawTextureRec(gameTextures[TXT_MONSTER_WALK], tempTex3, (Vector2){monster[mid].xPos - 5 , monster[mid].yPos - 3}, WHITE); 

		// Desenha e anima o monstro caso ele esteja sofrendo dano (sendo atacado pelo jogador)
		if(monster[mid].isBeingHited){
			monster[mid].animframe_hit++;

			if(monster[mid].animframe_hit++ > MONSTER_HIT_ANIM_FRAME_SPEED){
				monster[mid].animframe_hit = 0;
				monster[mid].isBeingHited = false;
			}

			// Sprite que deija ele um pouco mais vermelho (dano)
			Rectangle tt3 = {PLAYER_SPRITE_DIMENSION * monster[mid].moveDirection, PLAYER_SPRITE_DIMENSION * 0, PLAYER_SPRITE_DIMENSION, PLAYER_SPRITE_DIMENSION};
			DrawTextureRec(gameTextures[TXT_MONSTER_HIT_STATE], tt3, (Vector2){monster[mid].xPos - 5 , monster[mid].yPos -5}, WHITE); 
	

		}

		// Desenha e anima o monstro normal, sem estar sofrendo dano pelo jogador
		else{

			// Desenha o monstro normalmente
			Rectangle tempTex2 = {PLAYER_SPRITE_DIMENSION * monster[mid].moveDirection, PLAYER_SPRITE_DIMENSION * 0, PLAYER_SPRITE_DIMENSION, PLAYER_SPRITE_DIMENSION};
			DrawTextureRec(gameTextures[TXT_MONSTER_STATE], tempTex2, (Vector2){monster[mid].xPos - 5 , monster[mid].yPos -5}, WHITE); 
	
			// Desenha a vida dos monstros (acima da cabeça)
			DrawTexturePro(gameTextures[TXT_MONSTER_LIFE_SPRITESHEET], (Rectangle){0,286 * (monster[mid].hits-3*-1),1051,286}, (Rectangle){monster[mid].xPos + 5, monster[mid].yPos - 10, 37, 10}, (Vector2){0,0},0, WHITE);
			
			// Desenha os olhos vermelhos dos monstros caso estejam seguindo o jogador
			if(monster[mid].isFollowing){
				Rectangle t3 = {PLAYER_SPRITE_DIMENSION * monster[mid].moveDirection, PLAYER_SPRITE_DIMENSION * 0, PLAYER_SPRITE_DIMENSION, PLAYER_SPRITE_DIMENSION};		
				DrawTextureRec(gameTextures[TXT_MONSTER_FOLLOW_STATE], t3, (Vector2){monster[mid].xPos - 5 , monster[mid].yPos -5}, WHITE); 
			}


		}


	}
}

// Atualiza a direção de movimento do monstro caso bata em alguma parede (apenas se não estiver seguindo jogador)
void monsterCheckNewDirection(int mid){

	if(monster[mid].isFollowing) return;

	for(int i = 0; i < 4; i++){
		if(monsterCollisionDirection[mid][monster[mid].moveDirection]){

			// Caso colida em alguma parede o monstro anda em uma nova direção aleatoriamente
			monster[mid].unfollowMoveXPos = GetRandomValue(1, SCREEN_WIDTH);
			monster[mid].unfollowMoveYPos = GetRandomValue(1, SCREEN_HEIGHT);
		}
	}
}

// Atualiza os dados das variáveis do monstro (angulo e direção do movimento)
void monsterUpdateMoveDirection(int mid){
    
    // Caso o monstro esteja seguindo coleta o angulo entre ele e a posição a qual o monstro está andando
    if(!monster[mid].isFollowing){
		monster[mid].angleMoveDirection = getAngleBetweenPoints(monster[mid].xPos+30, monster[mid].yPos+30, monster[mid].unfollowMoveXPos, monster[mid].unfollowMoveYPos);
	}

	// Caso o monstro esteja seguindo coleta o angulo entre ele e o jogador
	else{
		monster[mid].angleMoveDirection = getAngleBetweenPoints(monster[mid].xPos+30, monster[mid].yPos+30, player.xPos+30, player.yPos+30);		
	}

	// Atualiza os dados da direçao do movimento (vertical/horizontal), ou seja, para cima, baixo, esquerda, direita
	if((monster[mid].angleMoveDirection > 0 && monster[mid].angleMoveDirection < 45) || (monster[mid].angleMoveDirection > 315 && monster[mid].angleMoveDirection < 350)){
		monster[mid].moveDirection = DIR_RIGHT;
	}
	if((monster[mid].angleMoveDirection > 45 && monster[mid].angleMoveDirection < 135)){
		monster[mid].moveDirection = DIR_DOWN;
	}
	if((monster[mid].angleMoveDirection > 135 && monster[mid].angleMoveDirection < 225)){
		monster[mid].moveDirection = DIR_LEFT;
	}
	if((monster[mid].angleMoveDirection > 225 && monster[mid].angleMoveDirection < 315)){
		monster[mid].moveDirection = DIR_UP;
	}
}

// Verifica se há uma parede na direção em que o monstro está andando, retorna true caso tenha.
bool monsterCheckCollisions(int mid){

	// Cehca a colisão das paredes extremas do mapa (bordas da janela)
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

	// Checa a colisão das paredes do mapa (definidas como P na array do nível)
	for(int i = 0; i <= obstacleAmount; i++){

		if(monster[mid].moveDirection == DIR_UP && CheckCollisionRecs(mapObstacle[i], (Rectangle){monster[mid].xPos + 18, monster[mid].yPos + 20-monster[mid].moveSpeed, 15, 25})) monsterCollisionDirection[mid][COLLISION_DIR_UP] = true;
		if(monster[mid].moveDirection == DIR_DOWN && CheckCollisionRecs(mapObstacle[i], (Rectangle){monster[mid].xPos + 18, monster[mid].yPos + 20+monster[mid].moveSpeed, 15, 25})) monsterCollisionDirection[mid][COLLISION_DIR_DOWN] = true;
		if(monster[mid].moveDirection == DIR_RIGHT && CheckCollisionRecs(mapObstacle[i], (Rectangle){monster[mid].xPos + 18+monster[mid].moveSpeed,  monster[mid].yPos + 20, 15, 25})) monsterCollisionDirection[mid][COLLISION_DIR_RIGHT] = true;
		if(monster[mid].moveDirection == DIR_LEFT && CheckCollisionRecs(mapObstacle[i], (Rectangle){monster[mid].xPos + 18-monster[mid].moveSpeed,  monster[mid].yPos + 20, 15, 25})) monsterCollisionDirection[mid][COLLISION_DIR_LEFT] = true;

	}

	// Retorna a informação caso tenha alguma colisão verificada na direção de movimento do monstro
	if(monster[mid].moveDirection == DIR_UP && monsterCollisionDirection[mid][COLLISION_DIR_UP]) return true;
	if(monster[mid].moveDirection == DIR_DOWN && monsterCollisionDirection[mid][COLLISION_DIR_DOWN]) return true;
	if(monster[mid].moveDirection == DIR_LEFT && monsterCollisionDirection[mid][COLLISION_DIR_LEFT]) return true;
	if(monster[mid].moveDirection == DIR_RIGHT && monsterCollisionDirection[mid][COLLISION_DIR_RIGHT]) return true;

	return false;
}

// Verifica se o jogador bateu no monstro
void monsterCheckIfPlayerHit(int mid){

	// Válido apenas para monstros que ainda estão vivos (ou seja, visiveis)
	if(!monster[mid].isVisible) return;
	
	// Verifica se o monstro está na HitBox do jogador (área quadrada a qual a espada tem efeito e o monstro sofre dano)
	bool isHitable = CheckCollisionRecs(player.attackHitBox, (Rectangle){monster[mid].xPos + 18, monster[mid].yPos + 20, 15, 25});

	// Verifica se o monstro sofrerá ou não o dano
	if(IsKeyPressed(KEY_J) && (isHitable) && player.canAttack){

		// Atualiza os dados do monstro
		monster[mid].isBeingHited = true;
		monster[mid].animframe_hit = 0;
		monster[mid].hits++;

		// Efeito sonoro de dano do monstro
		PlaySound(gameSound[SFX_MONSTER_DAMAGE]);

		// Caso o monstro morra (última vida dele), o jogador ganha um ponto e o monstro some
		if(monster[mid].hits == MAX_MONSTER_LIFE){
			monster[mid].isVisible = false;
			player.score++;
		}

		// Responsável por aplicar um Rag Doll nos monstros, ou seja, sofrer pela ação da espada do jogador
		// Basicamente o monstro é movido um pouco para trás, dando a impressão que o jogador bateu nele
		double angulo = getAngleBetweenPoints(monster[mid].xPos+30, monster[mid].yPos+30, player.xPos+30+monster[mid].xFollowOffset, player.yPos+30+monster[mid].yFollowOffset);
		Vector2 newPos = getVectorByAngleDistance(angulo, (monster[mid].moveSpeed) * -2);
		monster[mid].xPos += newPos.x;
		monster[mid].yPos += newPos.y;

	}
}

// Verifica se o monstro bateu no jogador
void monsterCheckIfHitPlayer(int mid){

	// Válido apenas para monstros que ainda estão vivos (ou seja, visiveis)
	if(!monster[mid].isVisible) return;

	// Calcula distancia do jogador até o monstro, se for pequena (próxima a aréa efetiva do monstro) o jogador sofre dano
	double distance = getDistanceBetweenPoints(player.xPos, player.yPos, monster[mid].xPos, monster[mid].yPos);
	if(distance < MONSTER_ATTACK_MIN_RANGE){
		
		// Remove vida do jogador
		player.life--;

		// Centraliza os elementos do mapa
		resetMapConfigs();

		// Efeito sonoro do jogador levando dano
		PlaySound(gameSound[SFX_MONSTER_HIT]);

		// Se o jogador perder todas as vidas, o jogoa acaba
		if(player.life <= 0) gameLevelGameOver();
	}
}

// Verifica se todos os monstros do nível morreram para carregar ó próximo
bool monsterCheckIfAllDie(){
	for(int i = 0; i < monsterCount; i++){
		if(monster[i].isVisible) return false;
	}

	return true;
}

// Responsável por mover (atualizando os dados X, Y dos monstros) os monstros pelo mapa
// Podendo ser para uma posição aleatória ou atrás do jogador (caso chegue perto)
bool monsterMove(int mid){

	// Verifica se posição para o movimento não tem paredes se tiver move em outra posição
	monsterCheckNewDirection(mid);

	// Se o jogador estiver muito longe, o monstro anda em uma direção aleatório
	if(getDistanceBetweenPoints(monster[mid].xPos+30, monster[mid].yPos+30, player.xPos+30+monster[mid].xFollowOffset, player.yPos+30+monster[mid].yFollowOffset) > MAX_MONSTER_FOLLOW_DISTANCE){
		
		// Dados do monstro
		monster[mid].isFollowing = false;

		// Gera novas direções aleatórias
		if(getDistanceBetweenPoints(monster[mid].xPos+30, monster[mid].yPos+30, monster[mid].unfollowMoveXPos, monster[mid].unfollowMoveYPos) < 100){
			monster[mid].unfollowMoveXPos = GetRandomValue(1, SCREEN_WIDTH);
			monster[mid].unfollowMoveYPos = GetRandomValue(1, SCREEN_HEIGHT);
		}

		// Calcula o vetor para mover o monstro em determinada direção
		double angulo = getAngleBetweenPoints(monster[mid].xPos+30, monster[mid].yPos+30, monster[mid].unfollowMoveXPos, monster[mid].unfollowMoveYPos);
		Vector2 newPos = getVectorByAngleDistance(angulo, monster[mid].moveSpeed);

		// Apenas move o monstro caso não tenha colisão na direção do movimento
		if(monsterCheckCollisions(mid)) return false;

		// Move o monstro pelo vetor calculado
		monster[mid].xPos += newPos.x;
		monster[mid].yPos += newPos.y;

	}

	// Caso o jogador esteja perta o monstro irá segui-lo
	else{
		
		// Dados do monstro
		monster[mid].isFollowing = true;

		// Calcula o vetor para mover o monstro na direção do jogador
		double angulo = getAngleBetweenPoints(monster[mid].xPos+30, monster[mid].yPos+30, player.xPos+30+monster[mid].xFollowOffset, player.yPos+30+monster[mid].yFollowOffset);
		Vector2 newPos = getVectorByAngleDistance(angulo, monster[mid].moveSpeed);
	
		// Apenas move o monstro caso não tenha colisão na direção do movimento
		if(monsterCheckCollisions(mid)) return false;

		// Move o monstro pelo vetor calculado
		monster[mid].xPos += newPos.x;
		monster[mid].yPos += newPos.y;

	}

	return true;
}

// Atualiza todas as informações gerais de cada monstro
void monsterUpdate(){

	for(int i = 0; i < monsterCount; i++){
		monsterUpdateMoveDirection(i);
		monsterMove(i);
		monsterCheckIfPlayerHit(i);
		monsterCheckIfHitPlayer(i);
		monsterDraw(i);
	}

	// Verifica se todos monstros já morreram para carregar um novo nível
	if(monsterCheckIfAllDie()){
		loadNewLevel(player.level);
	}
}

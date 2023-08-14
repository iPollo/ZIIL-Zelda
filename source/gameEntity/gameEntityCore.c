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

enum {
	DIR_UP,
	DIR_RIGHT,
	DIR_DOWN,
	DIR_LEFT,
	DIR_NONE,
};

enum{
	COLLISION_DIR_UP,
	COLLISION_DIR_RIGHT,
	COLLISION_DIR_DOWN,
	COLLISION_DIR_LEFT,
};

typedef struct Entity{
	float xPos;
	float yPos;
	float moveSpeed;
	int xFollowOffset;
	int yFollowOffset;
	int moveDirection;
	float angleMoveDirection;
	int unfollowMoveXPos;
	int unfollowMoveYPos;
	Rectangle colideBox;
	bool isAttacking;
	bool isFollowing;
	bool canAttack;
	bool isVisible;
	int life;
	int score;
	int level;


} Entity;


// ===========================================================================
// 		Dependencias
// ===========================================================================

#include "obstacle.c"
#include "player.c"
#include "monster.c"

// ===========================================================================
// 		Funções
// ===========================================================================

void gameEntityUpdate(){
	monsterUpdate();
	playerUpdate();
}

void gameEntityInit(){

	mapCollidersInit();
	playerInit();
	monsterInit();

}




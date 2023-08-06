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

typedef struct Entity{
	float xPos;
	float yPos;
	float moveSpeed;
	int moveDirection;
	Rectangle colideBox;
	bool isAttacking;
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




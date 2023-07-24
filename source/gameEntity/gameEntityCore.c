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
	DIR_NONE,
	DIR_UP,
	DIR_DOWN,
	DIR_LEFT,
	DIR_RIGHT,
};

typedef struct Entity{
	float xPos;
	float yPos;
	float moveSpeed;
	int moveDirection;
	Rectangle colideBox;


} Entity;


// ===========================================================================
// 		Dependencias
// ===========================================================================

#include "mapColliders.c"
#include "player.c"

// ===========================================================================
// 		Funções
// ===========================================================================

void gameEntityUpdate(){
	playerUpdate();
}

void gameEntityInit(){

	mapCollidersInit();
	playerInit();

}



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

// Declaração da função responsável por centralizar todos os elementos em suas posições (caso o jogador sofra dano)
void resetMapConfigs();

// Enums relacionados a direção da movimentação do jogador/monstros e suas colisões
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

// Estrutura global principral da Entidade (rege os dados do jogador/monstro)
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
	Rectangle attackHitBox;
	bool isAttacking;
	bool isBeingHited;
	int animframe_hit;
	int animframe_attack;
	int attackSpriteIndex;
	Vector2 originalPosition;
	bool isFollowing;
	bool canAttack;
	bool isVisible;
	int life;
	int hits;
	int score;
	int level;
	int currentTopPos;

} Entity;

// ===========================================================================
// 		Dependencias
// ===========================================================================

// Inclui os dados das estidades criadas a partir da estrutura principal
#include "obstacle.c"
#include "player.c"
#include "monster.c"

// ===========================================================================
// 		Funções
// ===========================================================================

// Atualiza as entidades caso o jogo esteja rodando
void gameEntityUpdate(){

	if(!isGameRunning || isGameOver) return;
	monsterUpdate();
	playerUpdate();
}

// Inicializa cada entidade
// resetData é para zerar as variáveis do jogador/mapa/monstros caso o jogador morra e volte ao menu, assim inicializando os módulos novamente
void gameEntityInit(bool resetData){
	playerInit(resetData);
	monsterInit();
	mapCollidersInit();
}

// Responsável por centralizar todos os elementos em suas posições originais (caso o jogador sofra dano)
void resetMapConfigs(){

	player.xPos = player.originalPosition.x;
	player.yPos = player.originalPosition.y;

	for(int i = 0; i < monsterCount; i++){
		monster[i].xPos = monster[i].originalPosition.x;
		monster[i].yPos = monster[i].originalPosition.y;
	}

}





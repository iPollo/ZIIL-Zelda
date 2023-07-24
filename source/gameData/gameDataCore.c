// ===========================================================================
//			
//		Pac-Telma (Desenvolvido em C, usando Raylib)
//		Por: Aline Lux (335722) e Henrique Selau de Oliveira (338301)
//		Universidade Federal do Rio Grande do Sul - UFRGS
//		Algoritmos e Programação - PROF. Marcelo Walter
//
// ===========================================================================

#define MAX_PLAYER_DATA 2

// ===========================================================================
// 		Variáveis
// ===========================================================================

// Player
enum{
	PLAYER_LEVEL,
};

int playerData[MAX_PLAYER_DATA];

// ===========================================================================
// 		Funções
// ===========================================================================

void gameDataInit(){
	playerData[PLAYER_LEVEL] = 1;
}

void gameDataLoad(){

}
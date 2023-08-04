// ===========================================================================
//			
//		Pac-Telma (Desenvolvido em C, usando Raylib)
//		Por: Aline Lux (335722) e Henrique Selau de Oliveira (338301)
//		Universidade Federal do Rio Grande do Sul - UFRGS
//		Algoritmos e Programação - PROF. Marcelo Walter
//
// ===========================================================================

#define MAX_MAP_OBSTACLE 50

// ===========================================================================
// 		Variáveis
// ===========================================================================

Rectangle mapObstacle[MAX_MAP_OBSTACLE];

int obstacleAmount = -1;

// ===========================================================================
// 		Inicializa as collides das rochas (arbustos)
// ===========================================================================

// Defini a caixa de colisão de cada objeto do mapa
void mapCollidersInit(){

	for(int i = 0; i < TILE_LINES; i++){
		for(int j = 0; j < TILE_ROWS; j++){
			if(MAP[i][j] == 'O'){
                obstacleAmount++;
                mapObstacle[obstacleAmount].x = j * TILE_SIZE;
                mapObstacle[obstacleAmount].y = i * TILE_SIZE;
                mapObstacle[obstacleAmount].width = TILE_SIZE;
                mapObstacle[obstacleAmount].height = TILE_SIZE;
			}
		}
	}

}



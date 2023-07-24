// ===========================================================================
//			
//		Pac-Telma (Desenvolvido em C, usando Raylib)
//		Por: Aline Lux (335722) e Henrique Selau de Oliveira (338301)
//		Universidade Federal do Rio Grande do Sul - UFRGS
//		Algoritmos e Programação - PROF. Marcelo Walter
//
// ===========================================================================

#define MAX_COLLIDE_ROCKS 50

// ===========================================================================
// 		Variáveis
// ===========================================================================

Rectangle mapCollideBox[MAX_COLLIDE_ROCKS];

int rockCounter = -1;

// ===========================================================================
// 		Inicializa as collides das rochas (arbustos)
// ===========================================================================

// Defini a caixa de colisão de cada objeto do mapa
void mapCollidersInit(){

	for(int i = 0; i < TILE_LINES; i++){
		for(int j = 0; j < TILE_ROWS; j++){
			if(MAP[i][j] == 'O'){
                rockCounter++;
                mapCollideBox[rockCounter].x = j * TILE_SIZE;
                mapCollideBox[rockCounter].y = i * TILE_SIZE;
                mapCollideBox[rockCounter].width = TILE_SIZE;
                mapCollideBox[rockCounter].height = TILE_SIZE;
			}
		}
	}

}



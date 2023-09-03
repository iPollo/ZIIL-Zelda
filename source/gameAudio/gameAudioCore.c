// ===========================================================================
//			
//		Pac-Telma (Desenvolvido em C, usando Raylib)
//		Por: Aline Lux (335722) e Henrique Selau de Oliveira (338301)
//		Universidade Federal do Rio Grande do Sul - UFRGS
//		Algoritmos e Programação - PROF. Marcelo Walter
//
// ===========================================================================

// Numero máximo de sons
#define MAX_SOUNDS 36

// ===========================================================================
// 		Variáveis
// ===========================================================================

// Declaração global da música do menu e de batalha do jogo
Music SFX_MENU;
Music SFX_GAME;

// Enum dos efeitos sonoros
enum{
	SFX_GAMEOVER,
	SFX_MENU_BUTTON,
	SFX_SWORD_SLASH,
	SFX_MONSTER_DAMAGE,
	SFX_MONSTER_HIT,
	SFX_LEVELUP,

};

// Declaração global dos efeitos sonoros
Sound gameSound[MAX_SOUNDS];

// OBS: Os efeitos sonoros são efeitos cujo o tempo de reprodução é curto, menos que cinco segundos
// Isso é uma recomendação do próprio Raylib, documentado na página da biblioteca.

// ===========================================================================
// 		Funções
// ===========================================================================

// Responsável por reproduzir/pausar a música do menu
void setMenuMusicPlaying(bool play){
	if(play){
		SFX_MENU = LoadMusicStream("C:/raylib/raylib/examples/ZIIL-Zelda/assets/sfx/SFXMUSIC_MENU.mp3"); 
		SFX_MENU.looping = true;
		PlayMusicStream(SFX_MENU);
	}
	else{
		StopMusicStream(SFX_MENU);
		UnloadMusicStream(SFX_MENU);
	}
}

// Responsável por reproduzir/pausar a música de batalha do jogo
void setGameMusicPlaying(bool play){
	if(play){
		SFX_GAME = LoadMusicStream("C:/raylib/raylib/examples/ZIIL-Zelda/assets/sfx/SFXMUSIC_GAME.mp3"); 
		SFX_GAME.looping = true;
		PlayMusicStream(SFX_GAME);
		SetMusicVolume(SFX_GAME, 0.2);    
	}
	else{
		StopMusicStream(SFX_GAME);
		UnloadMusicStream(SFX_GAME);
	}
}

// Inicializa os efeitos sonoros, carregando-os respectivamente na array
void gameAudioInit(){
	gameSound[SFX_MENU_BUTTON] = LoadSound("C:/raylib/raylib/examples/ZIIL-Zelda/assets/sfx/SFX_MENU_BUTTON.wav");
	gameSound[SFX_GAMEOVER] = LoadSound("C:/raylib/raylib/examples/ZIIL-Zelda/assets/sfx/SFX_GAMEOVER.mp3");
	gameSound[SFX_SWORD_SLASH] = LoadSound("C:/raylib/raylib/examples/ZIIL-Zelda/assets/sfx/SFX_SWORD_SLASH.mp3");
	gameSound[SFX_MONSTER_DAMAGE] = LoadSound("C:/raylib/raylib/examples/ZIIL-Zelda/assets/sfx/SFX_MONSTER_DAMAGE.mp3");
	gameSound[SFX_MONSTER_HIT] = LoadSound("C:/raylib/raylib/examples/ZIIL-Zelda/assets/sfx/SFX_MONSTER_HIT.mp3");
	gameSound[SFX_LEVELUP] = LoadSound("C:/raylib/raylib/examples/ZIIL-Zelda/assets/sfx/SFX_LEVELUP.mp3");
}

// Atualiza as músicas a cada frame (como demonstrado na documentação da biblioteca)
void gameAudioUpdate(){
	if(IsMusicStreamPlaying(SFX_MENU)) UpdateMusicStream(SFX_MENU);
	if(IsMusicStreamPlaying(SFX_GAME)) UpdateMusicStream(SFX_GAME);
}
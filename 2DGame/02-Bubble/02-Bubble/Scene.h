#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "fondo.h"
#include "Flecha.h"
#include "Bola.h"
#include "Bolsas.h"
#include "Base.h"
#include "Rueda.h"
#include "Arco.h"
#include "Bub.h"
#include "Techo.h"
#include "ConjuntoBolas.h"
#include "Tubo.h"
#include "SpriteTexto.h"
#include "Text.h"


// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{

public:
	Scene();
	~Scene();

	void init();
	void update(int deltaTime);
	void render();
	bool get_perdido();

private:
	void initShaders();

private:
	TileMap *map;
	Player *player;
	ShaderProgram texProgram;
	float currentTime,tiempo;
	glm::mat4 projection;
	Fondo *fondo;
	Flecha *flecha;
	Bola *bola, *auxBola;
	Bolsas * bolsa;
	Base *base;
	Rueda *rueda;
	Arco *arco;
	Bub *bub;
	Techo *techo;
	Tubo *tubo;
	int nivel_techo, limite, temblor;
	bool perdido,ganado; 
	int *bolas;
	ConjuntoBolas *matBolas;
	SpriteTexto *spriteTexto;
	Text replay;
	Text puntos;


};


#endif // _SCENE_INCLUDE


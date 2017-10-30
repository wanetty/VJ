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

private:
	void initShaders();

private:
	TileMap *map;
	Player *player;
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;
	Fondo *fondo;
	Flecha *flecha;
	Bola *bola;
	Bolsas * bolsa;
	Base *base;
	Rueda *rueda;
	Arco *arco;
	Bub *bub;
	int nivel_techo, limite;

};


#endif // _SCENE_INCLUDE


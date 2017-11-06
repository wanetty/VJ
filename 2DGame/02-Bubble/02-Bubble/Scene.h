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
#include "AudioEngine.h"



// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{

public:
	Scene();
	~Scene();

	void init(int nivel,int puntos);
	void update(int deltaTime);
	void render();
	bool get_perdido();
	bool get_completado();
	bool get_ganado() { return ganado; }
	bool get_creditos() { return creditos; }

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
	int nivel_techo, limite, temblor, empezado;
	bool perdido,ganado,lanzado,completado;
	int *bolas, channelprincipal;
	ConjuntoBolas *matBolas;
	SpriteTexto *spriteTexto,*round;
	Text replay;
	CAudioEngine aEngine;
	bool test,creditos;
	Text puntos,abandonar;
	int points,nivel,delay;
	Text lvl;
	


};


#endif // _SCENE_INCLUDE


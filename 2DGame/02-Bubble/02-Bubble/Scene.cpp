#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"
#include "Bolsas.h"



#define SCREEN_X 191
#define SCREEN_Y 50
#define bolsax 131
#define bolsay 412
#define basex 243
#define basey 412
#define ruedax 360
#define rueday 420
#define arcox 278
#define arcoy 377
#define bubx 251
#define buby 419
#define Pos_felcha_x 104
#define Pos_felcha_y 302


Scene::Scene()
{
	map = NULL;
	fondo = NULL;
	flecha = NULL;
	bolsa = NULL;
	base = NULL;
	techo = NULL;
}

Scene::~Scene()
{
	if(map != NULL)
		delete map;
	if (fondo != NULL)
		delete fondo;
	if (flecha != NULL)
		delete flecha;
}


void Scene::init()
{
	initShaders();
	map = TileMap::createTileMap("levels/mapa1.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	fondo = new Fondo();
	flecha = new Flecha();
	bola = new Bola();
	auxBola = new Bola();
	bolsa = new Bolsas();
	base = new Base();
	rueda = new Rueda();
	arco = new Arco();
	bub = new Bub();
	techo = new Techo();
	matBolas = new ConjuntoBolas();
	fondo->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram,"images/fondocuatro.png");
	fondo->setPosition(glm::vec2(0,0));
	flecha->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	flecha->setPosition(glm::vec2(Pos_felcha_x, Pos_felcha_y));
	flecha->setTileMap(map);
	bola->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, map,bub);
	bola->setPosition(glm::vec2(Pos_felcha_x+8, Pos_felcha_y+32));
	bola->setDireccion(flecha->getAngulo());
	auxBola->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, map, bub);
	auxBola->setPosition(glm::vec2(25, 389));
	matBolas->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, map, bub, glm::ivec2(8,11));
	bolsa->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	bolsa->setPosition(glm::vec2(bolsax, bolsay));
	bolsa->setTileMap(map);
	base->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	base->setPosition(glm::vec2(basex, basey));
	base->setTileMap(map);
	rueda->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	rueda->setPosition(glm::vec2(ruedax, rueday));
	rueda->setTileMap(map);
	arco->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	arco->setPosition(glm::vec2(arcox, arcoy));
	arco->setTileMap(map);
	bub->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	bub->setPosition(glm::vec2(bubx, buby));
	bub->setTileMap(map);
	techo->init(glm::ivec2(SCREEN_X, -270), texProgram, map);
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
	nivel_techo = 0;
	limite =8;
	temblor = 0;
	perdido = false;
	bola->reincio_bola(map->get_bola());
	bolas = new int[2];
	bolas[0] = map->get_bola();
	auxBola->set_color(bolas[0]);
	bolas[1] = map->get_bola();
	
}

void Scene::update(int deltaTime)
{
	bool lanzada_bola = bola->get_lanzada();
	bool reinicio_bola = bola->get_reinicio();
	if (map->get_perdido() == true) {
	
		map->set_grises();
		matBolas->update(deltaTime);
		map->update(glm::vec2(SCREEN_X + temblor, SCREEN_Y + nivel_techo * 32), texProgram);
		perdido = true;
	}
	else {
		if (bola->get_lanzadas() == limite) {
			++nivel_techo;
			limite += 8;
			bola->set_tilemapPos(glm::ivec2(SCREEN_X, SCREEN_Y + nivel_techo * 32));
			bola->setPosition(glm::vec2(Pos_felcha_x +8, (Pos_felcha_y + 32) - nivel_techo * 32));
			bola->set_pos_ini(glm::ivec2(0, -32));
			matBolas->set_tilemapPos(glm::ivec2(SCREEN_X, SCREEN_Y + nivel_techo * 32));
			int actualtura = techo->get_altura();
			techo->set_altura(++actualtura);
			map->set_limite(techo->get_altura());
			temblor = 0;
		}
		if (bola->get_lanzadas() == (limite - 2)) {
			if (temblor != 2) {
				temblor = 2;
			}
			else if (temblor != -2) {

				temblor = -2;
			}
		}
		if (bola->get_lanzadas() == (limite - 1)) {
			if (temblor != 3) {
				temblor = 3;
			}
			else if (temblor != -3) {

				temblor = -3;
			}
		}
		currentTime += deltaTime;
		flecha->update(deltaTime);
		bola->setDireccion(flecha->getAngulo());
		if (lanzada_bola) {
			if (reinicio_bola) {
				glm::vec2 lasputpos = bola->get_lastput_bola();
				int lastput_color = bola->get_lastput_color();
				matBolas->brilla(lasputpos, lastput_color);
				bola->reincio_bola(bolas[0]);
				auxBola->set_color(bolas[1]);
				bolas[0] = bolas[1];
				bolas[1] = map->get_bola();
			}
		}
		bola->update(deltaTime);
		auxBola->update_aux(deltaTime);
		map->update(glm::vec2(SCREEN_X + temblor, SCREEN_Y + nivel_techo * 32), texProgram);
		matBolas->update(deltaTime);
		//bolsa->update(deltaTime);
		rueda->update(deltaTime, flecha->getAngulo());
		bub->update(deltaTime);
		techo->update(deltaTime);
	}
}

void Scene::render()
{
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	fondo->render();
	//map->render();
	matBolas->render(map->get_mapa());
	techo->render();
	base->render();
	arco->render();
	flecha->render();
	bola->render();
	bolsa->render();
	auxBola->render();
	rueda->render();
	bub->render();
	
}

void Scene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if(!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if(!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if(!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}
bool Scene::get_perdido() {
	return perdido;
}


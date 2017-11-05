#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"
#include "string"

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
#define tubox 288
#define tuboy 404


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
	if (map != NULL)
		delete map;
	if (fondo != NULL)
		delete fondo;
	if (flecha != NULL)
		delete flecha;
	if (bola != NULL)
		delete bola;
	if (auxBola != NULL)
		delete auxBola;
	if (bolsa != NULL)
		delete bolsa;
	if (base != NULL)
		delete base;
	if (rueda != NULL)
		delete rueda;
	if (arco != NULL)
		delete arco;
	if (bub != NULL)
		delete bub;
	if (techo != NULL)
		delete techo;
	if (tubo != NULL)
		delete tubo;
	if (matBolas != NULL)
		delete matBolas;
	if (round != NULL)
		delete round;

}


void Scene::init(int nivel,int puntos)
{
	initShaders();
	this->nivel = nivel;
	tiempo = 0;
	points = puntos;
	string mapa = "levels/mapa";
	char c = nivel + '0';
	mapa += c;
	mapa += ".txt";
	map = TileMap::createTileMap(mapa, glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
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
	tubo = new Tubo();
	matBolas = new ConjuntoBolas();
	spriteTexto = new SpriteTexto();
	round = new SpriteTexto();
	string fon = "images/mapa";
	fon += c;
	fon += ".png";
	fondo->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram,fon);
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
	tubo->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	tubo->setPosition(glm::vec2(tubox, tuboy));
	tubo->setTileMap(map);
	string aux = "run";
	aux += c;
	aux += ".png";
	round->init(aux, texProgram, 226, 133, 190, 108);
	aEngine.Init();
	aEngine.LoadSound("audio/original.wav", false,true);
	aEngine.LoadSound("audio/BallBounce.wav", false, false);
	aEngine.LoadSound("audio/BubbleShot.wav", false, false);
	aEngine.LoadSound("audio/BallsElimination.wav", false, false);
	channelprincipal = aEngine.PlaySounds("audio/original.wav", Vector3{ 0, 0, 0 }, aEngine.VolumeTodB(0.2f));
	test = false;
	techo->init(glm::ivec2(SCREEN_X, -270), texProgram, map);
	if (!replay.init("fonts/OpenSans-Regular.ttf"))
		//if(!text.init("fonts/OpenSans-Bold.ttf"))
		//if(!text.init("fonts/DroidSerif.ttf"))
		cout << "Could not load font!!!" << endl;
	if (!this->puntos.init("fonts/OpenSans-Bold.ttf"))
		//if(!text.init("fonts/OpenSans-Regular.ttf"))
		//if(!text.init("fonts/DroidSerif.ttf"))
		cout << "Could not load font!!!" << endl;
	if (!this->lvl.init("fonts/OpenSans-Bold.ttf"))
		//if(!text.init("fonts/OpenSans-Regular.ttf"))
		//if(!text.init("fonts/DroidSerif.ttf"))
		cout << "Could not load font!!!" << endl;



	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
	nivel_techo = 0;
	limite =8;
	temblor = 0;
	perdido = false;
	ganado = false;
	lanzado = false;
	bola->reincio_bola(map->get_bola());
	bolas = new int[2];
	bolas[0] = map->get_bola();
	auxBola->set_color(bolas[0]);
	bolas[1] = map->get_bola();
	
	
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	if (currentTime > 5000) {
		tiempo += deltaTime;
		bool lanzada_bola = bola->get_lanzada();
		bool reinicio_bola = bola->get_reinicio();
		if (map->get_perdido() == true && !perdido) {

			map->set_grises();
			map->update(glm::vec2(SCREEN_X + temblor, SCREEN_Y + nivel_techo * 32), texProgram);
			matBolas->set_grises(map->get_mapa());
			matBolas->update(deltaTime);
			perdido = true;
			spriteTexto->init("lost.png", texProgram, 200, 160, 240, 108);
			tiempo = 0;

		}
		else if (!perdido && !ganado) {
			if (bola->get_lanzadas() == limite) {
				++nivel_techo;
				limite += 8;
				bola->set_tilemapPos(glm::ivec2(SCREEN_X, SCREEN_Y + nivel_techo * 32));
				bola->setPosition(glm::vec2(Pos_felcha_x + 8, (Pos_felcha_y + 32) - nivel_techo * 32));
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

			bool petado = map->get_petado();
			if (lanzada_bola) {
				if (!lanzado) {
					aEngine.PlaySounds("audio/BubbleShot.wav", Vector3{ 0, 0, 0 }, aEngine.VolumeTodB(.6f));
					lanzado = true;
				}
				if (petado) {
					aEngine.PlaySounds("audio/BallsElimination.wav", Vector3{ 0, 0, 0 }, aEngine.VolumeTodB(1.0f));
				}				
				
			if (reinicio_bola) {
				lanzado = false;
				if (!petado)aEngine.PlaySounds("audio/BallBounce.wav", Vector3{ 0, 0, 0 }, aEngine.VolumeTodB(.6f));
					glm::vec2 lasputpos = bola->get_lastput_bola();
					int lastput_color = bola->get_lastput_color();
					bola->reincio_bola(bolas[0]);
					auxBola->set_color(bolas[1]);
					matBolas->brilla(lasputpos, lastput_color);
					bolas[0] = bolas[1];
					bolas[1] = map->get_bola();

				}

			}
			
				

				flecha->update(deltaTime);
				bola->setDireccion(flecha->getAngulo());
				bola->update(deltaTime);
				matBolas->set_tilemapPos(glm::ivec2(SCREEN_X + temblor, SCREEN_Y + nivel_techo * 32));
				matBolas->set_caer(map->get_mapa());
				matBolas->update(deltaTime);
				auxBola->update_aux(deltaTime);
				map->update(glm::vec2(SCREEN_X + temblor, SCREEN_Y + nivel_techo * 32), texProgram);
				rueda->update(deltaTime, flecha->getAngulo());
				bub->update(deltaTime);
				techo->update(deltaTime);
			}


		if (perdido) {
			spriteTexto->update(deltaTime);
			if (!test) {
				aEngine.Shutdown();
				aEngine.Init();
				aEngine.LoadSound("audio/Game_Over.wav", false);
				aEngine.PlaySounds("audio/Game_Over.wav", Vector3{ 0, 0, 0 }, aEngine.VolumeTodB(0.5f));
				test = true;

			}
			if (Game::instance().getKey(13)) {
				this->~Scene();
				this->init(nivel, 0);
			}
		}

			else if (map->get_ganado() && !ganado) {
				ganado = true;
				aEngine.Shutdown();
				aEngine.Init();
				aEngine.LoadSound("audio/StageClear.wav", false);
				aEngine.PlaySounds("audio/StageClear.wav", Vector3{ 0, 0, 0 }, aEngine.VolumeTodB(0.5f));
				spriteTexto->init("win.png", texProgram, 226, 133, 190, 108);
			}


			
			if (ganado) {
				spriteTexto->update(deltaTime);
				if (Game::instance().getKey(13)) {
					this->~Scene();
					this->init(nivel + 1, points);
				}
			}

			points += map->get_bolas_petadas();
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
	tubo->render();
	if (currentTime < 5000) round->render();
	string aux = std::to_string(points * 10);
	string s = "SCORE: ";
	s += aux;
	if (!ganado && !perdido)puntos.render(s, glm::vec2(200, 35), 20, glm::vec4(1, 1, 1, 1));
	if (perdido) {
		spriteTexto->render();
		if (tiempo < 500) replay.render("Pulsa enter para reintentar!", glm::vec2(200, 315), 20, glm::vec4(0.9, 1, 0.0, 1));
		else if (tiempo > 1000) tiempo = 0;
	}

	if (ganado) {
		spriteTexto->render();
		puntos.render(s, glm::vec2(250, 285), 20, glm::vec4(1, 1, 1, 1));
	}
	lvl.render("Nivel: "+ std::to_string(nivel), glm::vec2(300, 480), 15, glm::vec4(1, 1, 1, 1));
	
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


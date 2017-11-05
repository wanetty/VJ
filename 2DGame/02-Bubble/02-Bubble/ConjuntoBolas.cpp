#include "ConjuntoBolas.h"



ConjuntoBolas::ConjuntoBolas()
{
}
void ConjuntoBolas::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, TileMap *tileMap, Bub *bub,glm::ivec2 MapSize) {
	SizeMapa = MapSize;
	matbolas = new Bola[MapSize.x*MapSize.y];
	tileMapDispl = tileMapPos;
	int desviacion = 0;
	int limite;
	mapa = tileMap->get_mapa();
	for (int j = 0; j < MapSize.y ; j++)
	{
		if (j % 2 != 0) {
			desviacion = 16;
			limite = MapSize.x - 1;
		}
		else {
			desviacion = 0;
			limite = MapSize.x;
		}
		for (int i = 0; i < limite;i++)
		{
			matbolas[j * MapSize.x + i].init(tileMapPos, shaderProgram, tileMap, bub);
			matbolas[j * MapSize.x + i].setPosition(glm::vec2(desviacion + i * 32,  j * 32));
			matbolas[j * MapSize.x + i].set_color(mapa[j * SizeMapa.x + i]);
		}
	}
	
}
void ConjuntoBolas::update(int deltaTime) {
	int limite;

	for (int j = 0; j < SizeMapa.y; j++)
	{
		if (j % 2 != 0) {
			
			limite = SizeMapa.x - 1;
		}
		else {
			
			limite = SizeMapa.x;
		}
		for (int i = 0; i < limite; i++)
		{
			
			/* if (mapa[j * SizeMapa.x + i] != 0) {
				matbolas[j * SizeMapa.x + i].set_color(mapa[j * SizeMapa.x + i]);
			}*/
			matbolas[j * SizeMapa.x + i].update_aux(deltaTime);
		}
	}
}
void ConjuntoBolas::render(int *map) {
	int limite;
	mapa = map;
	for (int j = 0; j < SizeMapa.y; j++)
	{
		if (j % 2 != 0) {

			limite = SizeMapa.x - 1;
		}
		else {

			limite = SizeMapa.x;
		}
		for (int i = 0; i < limite; i++)
		{
			if (mapa[j * SizeMapa.x + i] != 0 ) {
				matbolas[j * SizeMapa.x + i].render();
			}
		}
	}
}
void ConjuntoBolas::set_tilemapPos(const glm::ivec2 &tileMapPos) {
	tileMapDispl = tileMapPos;
	int limite,desviacion;
	
	for (int j = 0; j < SizeMapa.y; j++)
	{
		if (j % 2 != 0) {
			desviacion = 16;
			limite = SizeMapa.x - 1;
		}
		else {
			desviacion = 0;
			limite = SizeMapa.x;
		}
		for (int i = 0; i < limite; i++)
		{
				matbolas[j * SizeMapa.x + i].set_tilemapPos(tileMapDispl);
		}
	}
}
void ConjuntoBolas::set_grises(int *map) {
	int limite;
	mapa = map;
	for (int j = 0; j < SizeMapa.y; j++)
	{
		if (j % 2 != 0) {
			limite = SizeMapa.x - 1;
		}
		else {
			limite = SizeMapa.x;
		}
		for (int i = 0; i < limite; i++)
		{
			if (mapa[j * SizeMapa.x + i] != 0) matbolas[j * SizeMapa.x + i].set_color(9);

		}
	}
}
void ConjuntoBolas::set_caer(int *map) {
	int limite;
	mapa = map;
	bolas_cayendo.clear();
	for (int j = 0; j < SizeMapa.y; j++)
	{
		if (j % 2 != 0) {
			limite = SizeMapa.x - 1;
		}
		else {
			limite = SizeMapa.x;
		}
		for (int i = 0; i < limite; i++)
		{
			if (mapa[j * SizeMapa.x + i] == 11) {
				matbolas[j * SizeMapa.x + i].set_cayendo(true);
				bolas_cayendo.push_back({ i,j });
			}
		}
	}
}
bool ConjuntoBolas::get_cayendo() {
	list <glm::ivec2> bolas_caer = bolas_cayendo;
	while (!bolas_caer.empty()){
		if (!matbolas[bolas_caer.front().y * SizeMapa.x + bolas_caer.front().x].get_cayendo()) {
			bolas_cayendo.clear();
			return false;
		}
		bolas_caer.pop_front();
	}
	
	return true;
}
void ConjuntoBolas::brilla(glm::vec2 pos, int color) {
	glm::ivec2 posMap;
	posMap.y = (pos.y) / 32;
	(posMap.y % 2 == 0) ? posMap.x = (pos.x) / 32 : posMap.x = (pos.x - 16) / 32;
	matbolas[posMap.y * SizeMapa.x + posMap.x].set_color_brillo(color);
	posBrillo = posMap;
}
ConjuntoBolas::~ConjuntoBolas()
{
}

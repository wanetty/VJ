#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "TileMap.h"
#include "Game.h"
#include "Bola.h"


using namespace std;


TileMap *TileMap::createTileMap(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram &program)
{
	TileMap *map = new TileMap(levelFile, minCoords, program);
	
	return map;
}


TileMap::TileMap(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram &program)
{
	loadLevel(levelFile);
	prepareArrays(minCoords, program);
	posbolsa = -1;
	limit = 0;
	perder = false;
}

TileMap::~TileMap()
{
	if(map != NULL)
		delete map;
}



void TileMap::update(const glm::vec2 &minCoords, ShaderProgram &program) {
	if (Game::instance().getKey('n')) {
		map[1*mapSize.x + 1] = 2;
	}
	prepareArrays(minCoords, program);
}

void TileMap::render() const
{
	glEnable(GL_TEXTURE_2D);
	tilesheet.use();
	glBindVertexArray(vao);
	glEnableVertexAttribArray(posLocation);
	glEnableVertexAttribArray(texCoordLocation);
	glDrawArrays(GL_TRIANGLES, 0, 6 * mapSize.x * mapSize.y);
	glDisable(GL_TEXTURE_2D);
}

void TileMap::free()
{
	glDeleteBuffers(1, &vbo);
}

bool TileMap::loadLevel(const string &levelFile)
{
	ifstream fin;
	string line, tilesheetFile;
	stringstream sstream;
	char tile, color;
	
	fin.open(levelFile.c_str());
	if(!fin.is_open())
		return false;
	getline(fin, line);
	if(line.compare(0, 7, "TILEMAP") != 0)
		return false;
	getline(fin, line);
	sstream.str(line);
	sstream >> mapSize.x >> mapSize.y;
	getline(fin, line);
	sstream.str(line);
	sstream >> tileSize >> blockSize;
	getline(fin, line);
	sstream.str(line);
	sstream >> tilesheetFile;
	tilesheet.loadFromFile(tilesheetFile, TEXTURE_PIXEL_FORMAT_RGBA);
	tilesheet.setWrapS(GL_CLAMP_TO_EDGE);
	tilesheet.setWrapT(GL_CLAMP_TO_EDGE);
	tilesheet.setMinFilter(GL_NEAREST);
	tilesheet.setMagFilter(GL_NEAREST);
	getline(fin, line);
	sstream.str(line);
	sstream >> tilesheetSize.x >> tilesheetSize.y;
	tileTexSize = glm::vec2(1.f / tilesheetSize.x, 1.f / tilesheetSize.y);
	
	map = new int[mapSize.x * mapSize.y];
	for(int j=0; j<mapSize.y; j++)
	{
		for(int i=0; i<mapSize.x; i++)
		{
			fin.get(tile);
			if(tile == ' ')
				map[j*mapSize.x+i] = 0;
			else
				map[j*mapSize.x+i] = tile - int('0');
		}
		fin.get(tile);
#ifndef _WIN32
		fin.get(tile);
#endif
	}
	getline(fin, line);
	sstream.str(line);
	sstream >> sizebolsa;
	bolsa = new int[sizebolsa - int('0')];
	for (int i = 0; i < (sizebolsa-int('0')); ++i) {
		fin.get(color);
		if (color > '0' && color < '9')bolsa[i] = color - int('0');
	}
	fin.close();
	
	return true;
}

void TileMap::prepareArrays(const glm::vec2 &minCoords, ShaderProgram &program)
{
	int desviacion = 0;
	int limite = mapSize.x;
	int tile, nTiles = 0;
	glm::vec2 posTile, texCoordTile[2], halfTexel;
	vector<float> vertices;
	
	halfTexel = glm::vec2(0.5f / tilesheet.width(), 0.5f / tilesheet.height());
	for(int j=0; j<mapSize.y; j++)
	{
		if (j % 2 != 0) {
			desviacion = 16;
			limite = mapSize.x - 1;
		}
		else {
			desviacion = 0;
			limite = mapSize.x;
		}
		for(int i=0; i<limite; i++)
		{
			tile = map[j * mapSize.x + i];
			if(tile != 0 && tile != 11)
			{
				// Non-empty tile
 				nTiles++;
				posTile = glm::vec2(desviacion + minCoords.x + i * tileSize , minCoords.y + j * tileSize);
				texCoordTile[0] = glm::vec2(float((tile-1)%3) / tilesheetSize.x, float((tile-1)/3) / tilesheetSize.y);
				texCoordTile[1] = texCoordTile[0] + tileTexSize;
				//texCoordTile[0] += halfTexel;
				texCoordTile[1] -= halfTexel;
				// First triangle
				vertices.push_back(posTile.x); vertices.push_back(posTile.y);
				vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[0].y);
				vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y);
				vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[0].y);
				vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y + blockSize);
				vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[1].y);
				// Second triangle
				vertices.push_back(posTile.x); vertices.push_back(posTile.y);
				vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[0].y);
				vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y + blockSize);
				vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[1].y);
				vertices.push_back(posTile.x); vertices.push_back(posTile.y + blockSize);
				vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[1].y);
			}
		}
	}

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	if(nTiles != 0)	glBufferData(GL_ARRAY_BUFFER, 24 * nTiles * sizeof(float), &vertices[0], GL_STATIC_DRAW);
	posLocation = program.bindVertexAttribute("position", 2, 4*sizeof(float), 0);
	texCoordLocation = program.bindVertexAttribute("texCoord", 2, 4*sizeof(float), (void *)(2*sizeof(float)));
}
int TileMap::get_bola() {
	int i = 0;
	++posbolsa;
	while (!comprueba_bolsa() && i < this->get_sizebolsa()) {
		++i;
	}
	return bolsa[posbolsa];
}

void  TileMap::set_bola(glm::vec2 pos,const int color) {
	glm::ivec2 posMap;
	posMap.y = (pos.y) / tileSize;
	(posMap.y % 2 == 0) ? posMap.x = (pos.x) / tileSize : posMap.x = (pos.x - 16 ) / tileSize;
	 map[posMap.y * mapSize.x + posMap.x] = color;
	 if (posMap.y == 10 - limit) {
		 perder = true;
	 }
}
glm::vec2 TileMap::comprueba_izquierda(glm::vec2 pos) {
	glm::ivec2 posMap;
	glm::vec2 centro = { 16,16 };
	glm::vec2 izquierda = { -15,0 };
	pos += centro;
	glm::vec2 actual = pos;
	pos += izquierda;
	posMap.y = (pos.y) / tileSize;
	(posMap.y % 2 == 0) ? posMap.x = (pos.x) / tileSize : posMap.x = (pos.x - 16) / tileSize;
	if (posMap.y <= 9 && posMap.x >= 0 && ((posMap.y%2 == 0 && posMap.x <= 6) || (posMap.y % 2 == 0 && posMap.x <= 7))) {
		if (map[posMap.y * mapSize.x + posMap.x] != 0 && map[posMap.y * mapSize.x + posMap.x] != 11) {
			return actual;
		}
	}
	return { -1,-1 };
}
glm::vec2 TileMap::comprueba_derecha(glm::vec2 pos) {
	glm::ivec2 posMap;
	glm::vec2 centro = { 16,16 };
	glm::vec2 derecha = { 15,0 };
	pos += centro;
	glm::vec2 actual = pos;
	pos += derecha;
	posMap.y = (pos.y) / tileSize;
	(posMap.y % 2 == 0) ? posMap.x = (pos.x) / tileSize : posMap.x = (pos.x - 16) / tileSize;
	if (posMap.y <= 9 && posMap.x >= 0 && ((posMap.y % 2 != 0 && posMap.x <= 6) || (posMap.y % 2 == 0 && posMap.x <= 7))) {
		if (map[posMap.y * mapSize.x + posMap.x] != 0 && map[posMap.y * mapSize.x + posMap.x] != 11) {
			return actual;
		}
	}
	return { -1,-1 };
}
glm::vec2 TileMap::comprueba_arriba_derecha(glm::vec2 pos) {
	glm::ivec2 posMap, posActual;
	glm::vec2 centro = { 16,16 };
	glm::vec2 derecha_arriba = { 15,-15 };
	pos += centro;
	glm::vec2 actual = pos;
	posActual = { actual.x / tileSize, actual.x / tileSize };
	pos += derecha_arriba;
	posMap.y = (pos.y) / tileSize;
	(posMap.y % 2 == 0) ? posMap.x = (pos.x) / tileSize : posMap.x = (pos.x - 16) / tileSize;
	if ((posActual.y % 2 == 0 && posActual.x != 7) || posActual.y % 2 != 0) {
		if (posMap.y <= 9 && posMap.x >= 0 && ((posMap.y % 2 != 0 && posMap.x <= 6) || (posMap.y % 2 == 0 && posMap.x <= 7))){
			if (map[posMap.y * mapSize.x + posMap.x] != 0 && map[posMap.y * mapSize.x + posMap.x] != 11) {
				return actual;
			}
		}
	}
	return { -1,-1 };
	
}
glm::vec2 TileMap::comprueba_arriba_izquierda(glm::vec2 pos) {
	glm::ivec2 posMap, posActual;
	glm::vec2 centro = { 16,16 };
	glm::vec2 izquierda_arriba = { -15,-15 };
	pos += centro;
	glm::vec2 actual = pos;
	posActual = { actual.x / tileSize, actual.x / tileSize };
	pos += izquierda_arriba;
	posMap.y = (pos.y) / tileSize;
	(posMap.y % 2 == 0) ? posMap.x = (pos.x) / tileSize : posMap.x = (pos.x -16) / tileSize;
	if (posMap.y <= 9 && posMap.x >= 0 && ((posMap.y % 2 != 0 && posMap.x <= 6) || (posMap.y % 2 == 0 && posMap.x <= 7))){
		if (map[posMap.y * mapSize.x + posMap.x] != 0 && map[posMap.y * mapSize.x + posMap.x] != 11) {
			return actual;
		}
	}
	return { -1,-1 };
}

char TileMap::get_sizebolsa() {
	return sizebolsa  - int('0');
}
void TileMap::comprueba_bolas(glm::vec2 posi, int color) {
 	glm::ivec2 pos;
	pos.y = (posi.y) / tileSize;
	(pos.y % 2 == 0) ? pos.x = (posi.x) / tileSize : pos.x = (posi.x - 16) / tileSize;
	stack<glm::ivec2> stack;
	int *visitados = new int[mapSize.x * mapSize.y];
	int iguales = 0;
	stack.push(pos);
	visitados[pos.y *mapSize.x + pos.x] = 1;
	list<glm::ivec2> borrar;
	borrar.push_back(pos);
	iguales++;
	while (!stack.empty()) {
		
		glm::ivec2 actu = stack.top();
		stack.pop();
		glm::ivec2 arribader = { actu.x - ((actu.y + 1) % 2) + 1,actu.y - 1 };
		glm::ivec2 arribaiz = { actu.x - (actu.y + 1) % 2,actu.y - 1 };
		glm::ivec2 der = { actu.x + 1,actu.y };
		glm::ivec2 iz = { actu.x - 1,actu.y };
		glm::ivec2 abajoder = { actu.x - ((actu.y + 1) % 2) + 1,actu.y + 1 };
		glm::ivec2 abajoiz = { actu.x - (actu.y + 1) % 2,actu.y + 1 };
			if (pos_correcta(arribader) && visitados[arribader.y *mapSize.x + arribader.x] != 1) {
			if (map[arribader.y * mapSize.x + arribader.x] == color) {
				visitados[arribader.y *mapSize.x + arribader.x] = 1;
				stack.push(arribader);
				iguales++;
				borrar.push_back(arribader);
			}
		}
			if (pos_correcta(arribaiz) && visitados[arribaiz.y *mapSize.x + arribaiz.x] != 1) {
				if (map[arribaiz.y * mapSize.x + arribaiz.x] == color) {
					visitados[arribaiz.y *mapSize.x + arribaiz.x] = 1;
					stack.push(arribaiz);
					iguales++;
					borrar.push_back(arribaiz);
				}
			}
			if (pos_correcta(iz) && visitados[iz.y *mapSize.x + iz.x] != 1) {
				if (map[iz.y * mapSize.x + iz.x] == color) {
					visitados[iz.y *mapSize.x + iz.x] = 1;
					stack.push(iz);
					iguales++;
					borrar.push_back(iz);
				}
			}
			if (pos_correcta(der) && visitados[der.y *mapSize.x + der.x] != 1) {
				if (map[der.y * mapSize.x + der.x] == color) {
					visitados[der.y *mapSize.x + der.x] = 1;
					stack.push(der);
					iguales++;
					borrar.push_back(der);
				}
			}
			if (pos_correcta(abajoder) && visitados[abajoder.y *mapSize.x + abajoder.x] != 1) {
				if (map[abajoder.y * mapSize.x + abajoder.x] == color) {
					visitados[arribader.y *mapSize.x + arribader.x] = 1;
					stack.push(arribader);
					iguales++;
					borrar.push_back(abajoder);
				}
			}
			if (pos_correcta(abajoiz) && visitados[abajoiz.y *mapSize.x + abajoiz.x] != 1) {
				if (map[abajoiz.y * mapSize.x + abajoiz.x] == color) {
					visitados[abajoiz.y *mapSize.x + abajoiz.x] = 1;
					stack.push(abajoiz);
					iguales++;
					borrar.push_back(abajoiz);
				}
			}
	}
	if (iguales > 2) {
		this->borrar(borrar);
	}
}
bool TileMap::pos_correcta(glm::ivec2 pos) {
	if (pos.y % 2 == 0) {
		if (pos.x < 0 || pos.x > 7) return false;
	}
	else {
		if (pos.x < 0 || pos.x > 6) return false;
	}
	if (pos.y < 0 || pos.y > 9) return false;
	return true;
}
void TileMap::borrar(list<glm::ivec2> lista) {
	while (!lista.empty()) {
		glm::ivec2 actu = lista.front();
		map[actu.y *mapSize.x + actu.x] = 0;
		lista.pop_front();
	}
	int *visitados = new int[mapSize.x * mapSize.y];
	int limite ;
	for (int j = 0; j < mapSize.y; j++)
	{
		if (j % 2 != 0) {
			limite = mapSize.x - 1;
		}
		else {
			limite = mapSize.x;
		}
		for (int i = 0; i < limite ; i++)
		{
			int *visitados = new int[mapSize.x * mapSize.y];
			glm::ivec2 actual = {i,j};
			
			if (map[j *mapSize.x + i] != 0 && map[j *mapSize.x + i] != 11 && comprueba_bolas_flotantes(actual, visitados)) {
				map[j *mapSize.x + i] = 11;
			}
		}
	}
	
}
bool TileMap::comprueba_bolsa() {
	if (posbolsa >= this->get_sizebolsa())posbolsa = 0;
	int color = bolsa[posbolsa];
	bool encontrado = false;
	int limite;
	for (int j = 0; j < mapSize.y && !encontrado ; j++)
	{
		if (j % 2 != 0) {
			limite = mapSize.x - 1;
		}
		else {
			limite = mapSize.x;
		}
		for (int i = 0; i < limite && !encontrado; i++)
		{
			if (color == map[j * mapSize.x + i]) encontrado = true;
		}
	}
	if (!encontrado) {
		++posbolsa;
		return false;
	}
	return true;
}
bool TileMap::comprueba_bolas_flotantes(glm::ivec2 pos, int *visitados) {
	visitados[pos.y *mapSize.x + pos.x] = 1;
	glm::ivec2 actu = pos;
	if (pos.y == 0) return false;
	glm::ivec2 arribader = { actu.x - ((actu.y + 1) % 2) + 1,actu.y - 1 };
	glm::ivec2 arribaiz = { actu.x - (actu.y + 1) % 2,actu.y - 1 };
	glm::ivec2 der = { actu.x + 1,actu.y };
	glm::ivec2 iz = { actu.x - 1,actu.y };
	glm::ivec2 abajoder = { actu.x - ((actu.y + 1) % 2) + 1,actu.y + 1 };
	glm::ivec2 abajoiz = { actu.x - (actu.y + 1) % 2,actu.y + 1 };
	if (pos_correcta(arribader) && visitados[arribader.y *mapSize.x + arribader.x] != 1 && map[arribader.y *mapSize.x + arribader.x] != 0 && map[arribader.y *mapSize.x + arribader.x] != 11) {
		if (!comprueba_bolas_flotantes(arribader, visitados)) return false;
	}
	if (pos_correcta(arribaiz) && visitados[arribaiz.y *mapSize.x + arribaiz.x] != 1 && map[arribaiz.y *mapSize.x + arribaiz.x] != 0 && map[arribaiz.y *mapSize.x + arribaiz.x] != 11) {
		if (!comprueba_bolas_flotantes(arribader, visitados)) return false;

	}
	if (pos_correcta(iz) && visitados[iz.y *mapSize.x + iz.x] != 1 && map[iz.y *mapSize.x + iz.x] != 0 && map[iz.y *mapSize.x + iz.x] != 11) {

		if (!comprueba_bolas_flotantes(iz, visitados)) return false;

	}
	if (pos_correcta(der) && visitados[der.y *mapSize.x + der.x] != 1 && map[der.y *mapSize.x + der.x] != 0 && map[der.y *mapSize.x + der.x] != 11) {

		if (!comprueba_bolas_flotantes(der, visitados)) return false;

	}
	if (pos_correcta(abajoder) && visitados[abajoder.y *mapSize.x + abajoder.x] != 1 && map[abajoder.y *mapSize.x + abajoder.x] != 0 && map[abajoder.y *mapSize.x + abajoder.x] != 11) {
		if (!comprueba_bolas_flotantes(abajoder, visitados)) return false;
	}
	if (pos_correcta(abajoiz) && visitados[abajoiz.y *mapSize.x + abajoiz.x] != 1 && map[abajoiz.y *mapSize.x + abajoiz.x] != 0 && map[abajoiz.y *mapSize.x + abajoiz.x] != 11) {

		if (!comprueba_bolas_flotantes(abajoiz, visitados)) return false;

	}
		return true;

}

void TileMap::set_limite(int new_limit) {
	limit = new_limit;
}
bool TileMap::get_perdido() {
	return perder;
}
void TileMap::set_grises() {
	int limite;
	for (int j = 0; j < mapSize.y ; j++)
	{
		if (j % 2 != 0) {
			limite = mapSize.x - 1;
		}
		else {
			limite = mapSize.x;
		}
		for (int i = 0; i < limite; i++)
		{
			 if(map[j * mapSize.x + i] != 0 && map[j *mapSize.x + i] != 11)map[j * mapSize.x + i] = 9 ;
		}
	}
}
void TileMap::reset_pos(glm::vec2 pos) {
	glm::ivec2 posMap;
	glm::vec2 centro = { 16,16 };
	//pos += centro;
	posMap.y = (pos.y) / tileSize;
	(posMap.y % 2 == 0) ? posMap.x = (pos.x) / tileSize : posMap.x = (pos.x - 16) / tileSize;
	if (map[posMap.y *mapSize.x + posMap.x] == 11) {
		map[posMap.y *mapSize.x + posMap.x] = 0;
	}
}







// Collision tests for axis aligned bounding boxes.
// Method collisionMoveDown also corrects Y coordinate if the box is
// already intersecting a tile below.



































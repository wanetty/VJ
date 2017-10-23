#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "TileMap.h"
#include "Game.h"


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
			if(tile != 0)
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
	glBufferData(GL_ARRAY_BUFFER, 24 * nTiles * sizeof(float), &vertices[0], GL_STATIC_DRAW);
	posLocation = program.bindVertexAttribute("position", 2, 4*sizeof(float), 0);
	texCoordLocation = program.bindVertexAttribute("texCoord", 2, 4*sizeof(float), (void *)(2*sizeof(float)));
}
void TileMap::set_bola(const int x,const  int y,const  int color) {
	int auxx = (x) / tileSize;
	int auxy = (y) / tileSize;
	if (auxy % 2 != 0 && auxx == 7) {
		auxx = 6;
		map[auxy * mapSize.x + auxx] = color;
	}
	else map[auxy * mapSize.x + auxx] = color;
}
bool TileMap::comprueba_izquierda(const int x, const int y) {
	bool primero = false;
	int auxx = (x+32) / tileSize;
	int auxy = (y+32) / tileSize;
	if (auxy > 9) primero = true;
				auxx = (x) / tileSize;
				auxy = (y) / tileSize;
				 if (map[(auxy) * mapSize.x + (auxx +1)] != 0 && !primero) {
					return false; //izq
				}
	return true;
}
bool TileMap::comprueba_derecha(const int x, const int y) {
	int auxx = (x) / tileSize;
	int auxy = (y) / tileSize;
	bool primero = false;
	if (auxy > 9) primero = true;
	if (map[(auxy)* mapSize.x + (auxx - 1)] != 0 && !primero) {
		return false;//der
	}
	return true;
}

bool TileMap::comprueba_arrderecha(const int x, const int y) {
	bool primero = false;
	int auxx = (x) / tileSize;
	int auxy = (y) / tileSize;
	if (auxy > 9) primero = true;
	if (auxy % 2 == 0 && auxx == 7) return true;
	if (auxy % 2 != 0 && auxx == 7) auxx = 6;
	if (map[(auxy - 1)* mapSize.x + (auxx - ((auxy + 1) % 2) + 1)] != 0 && !primero) {
 			return false;//arribaderecha.
	}
	return true;
}
bool TileMap::comprueba_arrizquiera(const int x, const int y) {
	bool primero = false;
	int auxx = (x) / tileSize;
	int auxy = (y) / tileSize;
	if (auxy > 9) primero = true;
	if (auxy % 2 == 0 &&  auxx == 0) return true;
	if (map[(auxy - 1)* mapSize.x + (auxx - ((auxy + 1) % 2))] != 0 && !primero) {
		return false;//arriba izquerda
	}
	return true;
}
int TileMap::get_bola(const int pos) {
	return bolsa[pos];
}
char TileMap::get_sizebolsa() {
	return sizebolsa  - int('0');
}



// Collision tests for axis aligned bounding boxes.
// Method collisionMoveDown also corrects Y coordinate if the box is
// already intersecting a tile below.



































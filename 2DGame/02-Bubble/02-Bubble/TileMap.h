#ifndef _TILE_MAP_INCLUDE
#define _TILE_MAP_INCLUDE


#include <glm/glm.hpp>
#include "Texture.h"
#include "ShaderProgram.h"
#include <stack>
#include <list>


// Class Tilemap is capable of loading a tile map from a text file in a very
// simple format (see level01.txt for an example). With this information
// it builds a single VBO that contains all tiles. As a result the render
// method draws the whole map independently of what is visible.


class TileMap
{

public:
	// Tile maps can only be created inside an OpenGL context
	static TileMap *createTileMap(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram &program);

	TileMap(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram &program);
	~TileMap();

	void update(const glm::vec2 &minCoords, ShaderProgram &program);
	void render() const;
	void free();
	void set_bola(glm::vec2 pos,const  int color);
	int  get_bola();
	char get_sizebolsa();
	int getTileSize() const { return tileSize; }
	glm::vec2 comprueba_derecha(glm::vec2 pos);
	glm::vec2 comprueba_izquierda(glm::vec2 pos);
	glm::vec2 comprueba_arriba_derecha(glm::vec2 pos);
	glm::vec2 comprueba_arriba_izquierda(glm::vec2 pos);
	void  comprueba_bolas(glm::vec2 pos,int color);
	void set_limite(int new_limit);
	void set_grises();
	bool get_perdido();
	int* get_mapa() { return map; }
	void reset_pos(glm::vec2 pos);
	bool get_ganado();


private:
	bool loadLevel(const string &levelFile);
	void prepareArrays(const glm::vec2 &minCoords, ShaderProgram &program);
	bool pos_correcta(glm::ivec2 pos);
	void borrar(list<glm::ivec2> lista);
	bool comprueba_bolsa();
	bool comprueba_bolas_flotantes(glm::ivec2 posi, int *visitados);

private:
	GLuint vao;
	GLuint vbo;
	GLint posLocation, texCoordLocation;
	glm::ivec2 position, mapSize, tilesheetSize;
	int tileSize, blockSize; 
	char sizebolsa;
	Texture tilesheet;
	glm::vec2 tileTexSize;
	int *map;
	int *bolsa;
	int posbolsa, limit;
	bool perder,ganado;

};


#endif // _TILE_MAP_INCLUDE



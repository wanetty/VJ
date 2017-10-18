#ifndef MAPA_INCLUDE
#define MAPA_INCLUDE

#include <glm/glm.hpp>
#include "Texture.h"
#include "ShaderProgram.h"
class Mapa
{
public:
	Mapa(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram &program);
	~Mapa();

	void render() const;
	void free();

	int getTileSize() const { return tileSize; }
private:
	bool loadLevel(const string &levelFile);
	void prepareArrays(const glm::vec2 &minCoords, ShaderProgram &program);
private:
	GLuint vao;
	GLuint vbo;
	GLint posLocation, texCoordLocation;
	glm::ivec2 position, mapSize, tilesheetSize;
	int tileSize, blockSize;
	Texture tilesheet;
	glm::vec2 tileTexSize;
	int *map;
};
#endif // _TILE_MAP_INCLUDE

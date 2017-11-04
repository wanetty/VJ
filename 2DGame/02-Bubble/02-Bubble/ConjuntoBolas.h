
#ifndef _CONJUNTOBOLAS_INCLUDE
#define _CONJUNTOBOLAS_INCLUDE

#include <glm/glm.hpp>
#include "Texture.h"
#include "ShaderProgram.h"
#include "Bola.h"

class ConjuntoBolas
{
public:
	ConjuntoBolas();
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, TileMap *tileMap, Bub *bub,glm::ivec2 MapSize);
	void update(int deltaTime);
	void render(int *map) ;
	void set_tilemapPos(const glm::ivec2 &tileMapPos);
	void set_grises();
	void brilla(glm::vec2 pos, int color);
	~ConjuntoBolas();
private:
private:
	Bola *matbolas;
	glm::ivec2 SizeMapa, posBrillo;
	int *mapa;
	glm::ivec2 tileMapDispl;

};
#endif // _CONJUNTOBOLAS_INCLUDE



#ifndef _BOLSAS_INCLUDE
#define _BOLSAS_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
class Bolsas
{
public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);


private:
	glm::ivec2 tileMapDispl, posBolsas;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
};
#endif // _BOLSAS_INCLUDE

#ifndef _ARCO_INCLUDE
#define _ARCO_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
class Arco
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);


private:
	glm::ivec2 tileMapDispl, posArco;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
};
#endif // _ARCO_INCLUDE
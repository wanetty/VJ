#ifndef _BUB_INCLUDE
#define _BUB_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
class Bub
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);
	void Bub::setLanzada(bool lanzada);


private:
	glm::ivec2 tileMapDispl, posBub;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
	bool lanzada,vacio;
	int tiempo;
};
#endif // _BUB_INCLUDE
#ifndef _FONDO_INCLUDE
#define _FONDO_INCLUDE


#include "Sprite.h"






class Fondo
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, string image);
	
	void render();

	
	void setPosition(const glm::vec2 &pos);

private:
	
	glm::ivec2 tileMapDispl, posfondo;
	Texture spritesheet;
	Sprite *sprite;
	

};

#endif // _FONDO_INCLUDE


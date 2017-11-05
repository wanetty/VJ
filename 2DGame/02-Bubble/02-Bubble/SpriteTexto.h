#ifndef _SPRITETEXTO_INCLUDE
#define _SPRITETEXTO_INCLUDE


#include <vector>
#include <glm/glm.hpp>
#include "Texture.h"
#include "ShaderProgram.h"
#include "AnimKeyframes.h"
#include "Sprite.h"



class SpriteTexto
{

public:
	void init(string s, ShaderProgram &shaderProgram, int posx, int posy,int tamx,int tamy);
	void update(int deltaTime);
	void render();


	void setPosition(const glm::vec2 &pos);


private:
	glm::ivec2 tileMapDispl, posSpriteTexto;
	Texture spritesheet;
	Sprite *sprite;

};
#endif // _SPRITETEXTO_INCLUDE
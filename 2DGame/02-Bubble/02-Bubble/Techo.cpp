#include "Techo.h"



void Techo::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, TileMap *tileMap)
	{

		spritesheet.loadFromFile("images/techo.png", TEXTURE_PIXEL_FORMAT_RGBA);
		map = tileMap;
		altura = 0;
		shaderProgrambola = shaderProgram;
		tileMapDispl = tileMapPos;
		glm::vec2 tamano[2] = { glm::vec2(0, 320 - altura*32), glm::vec2(256, 320) };
		glm::vec2 tiletecho[2]; 
		glm::vec2 tileTexSize = glm::vec2(1.f / 11, 1.f / 11);
		tiletecho[0] = glm::vec2(0, 1- altura*0.0909090909);
		tiletecho[1] = glm::vec2(1, 1);
		sprite = Sprite_texture::createSpriteTexture(tamano, tiletecho, &spritesheet, &shaderProgrambola);
		sprite->setPosition(glm::vec2(float(tileMapDispl.x), float(tileMapDispl.y+altura*32)));
		
	}
void Techo::update(int deltaTime)
{
	glm::vec2 tamano[2] = { glm::vec2(0, 320 - altura * 32), glm::vec2(256, 320) };
	glm::vec2 tiletecho[2];
	glm::vec2 tileTexSize = glm::vec2(1.f / 11, 1.f / 11);
	tiletecho[0] = glm::vec2(0, 1 - altura*0.0909090909);
	tiletecho[1] = glm::vec2(1, 1);
	sprite = Sprite_texture::createSpriteTexture(tamano, tiletecho, &spritesheet, &shaderProgrambola);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x), float(tileMapDispl.y + altura * 32)));
}
void Techo::render()
{
	sprite->render();
}
int Techo::get_altura() {
	return altura;
}
void Techo::set_altura(int hight) {
	altura = hight;
}

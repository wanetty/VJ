#ifndef _CAMERA_INCLUDE
#define _CAMERA_INCLUDE
#include <glm/glm.hpp>
#include "ShaderProgram.h"

class Camera
{
public:
	Camera();
	~Camera();
	void init(glm::vec3 eye, glm::vec3 center, glm::vec3 up);
	void update(bool *keys);
	void look(ShaderProgram &texProgram);
private:
private:
	glm::vec3 eye, center, up;
	float rotx, roty, rotz;
};
#endif //_CAMERA_INCLUDE

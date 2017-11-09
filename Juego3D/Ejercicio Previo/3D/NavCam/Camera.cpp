#include "Camera.h"



Camera::Camera()
{
}
void Camera::init(glm::vec3 eye, glm::vec3 center, glm::vec3 up) {
	this->eye = eye;
	this->center = center;
	this->up = up;
}
void Camera::update(bool *keys) {
	
	if (keys['1']) {
		eye = {};
		center = {};
		up = {};
	}
	/*
	if(keys['d']){
		pos_x++;
	}else if(keys['a']{
		pos_x--;
	}
	if(keys['w']){
	pos_x += cos(rot_y)*step_length;
	pos_z += sin(rot_y)*step_length;
	}
	if("strafe_rigth")cos(rot_y-90);
	*/
}
void Camera::look(ShaderProgram &texProgram) {
	//Hay que pasar por parametro el shader y ahorramos nose que y mirar el shader en la escen.a
	/*rotate(-rotx, -1,0,0)*/
	/*rotate(-roty,0,1,0)*/
	/*rotate(-rotz,0,0,1)
	translate(-pos_x,-pos_z)*/

}

Camera::~Camera()
{
}

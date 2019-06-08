#include "Camera.h"




camera::camera()
{
}

camera::~camera()
{
}

void camera::initializeCamera()
{
	camPos = glm::vec3(0.0f, 0.0f, 3.0f);
	camLookDir = glm::vec3(0.0f, 0.0f, -1.0f);
	camUpDir = glm::vec3(0.0f, 1.0f, 0.0f);


}

void camera::calculate(GLfloat currentTime)
{
	
	//rotMat2 = glm::rotate(glm::mat4(), glm::radians(0.01f * currentTime), glm::vec3(0, 1, 0));
	//rotMat = glm::rotate(glm::mat4(), glm::radians(-30.0f), glm::vec3(1, 0, 0));

	newPos = /*rotMat **/ glm::vec4(0, 2, 3, 1) /** rotMat2*/;
	camPos = glm::vec3(newPos);
	camTar = glm::vec3(0.0f, 0.0f, 0.0f);
	view = glm::lookAt(camPos, camTar, camUpDir);

}

glm::mat4 camera::getView()
{
	return (view);
}

glm::mat4 camera::getProj()
{
	return (proj);
}

glm::mat4 camera::Model(glm::vec3 position, glm::vec3 scale, glm::mat4 rotationz)
{
	glm::vec3 backObjPosition = position;
	glm::mat4 backTranslationMatrix = glm::translate(glm::mat4(), backObjPosition);
	glm::vec3 objscaleBack = scale;
	glm::mat4 scaleMatrixBack = glm::scale(glm::mat4(), objscaleBack);
	glm::mat4 backModel = backTranslationMatrix * rotationz * scaleMatrixBack;
	return (backModel);
}

glm::mat4 camera::MVP(glm::vec3 postion, glm::vec3 scale, glm::mat4 rotationZ)
{
	glm::vec3 backObjPosition = postion;
	glm::mat4 backTranslationMatrix = glm::translate(glm::mat4(), backObjPosition);
	glm::vec3 objscaleBack = scale;
	glm::mat4 scaleMatrixBack = glm::scale(glm::mat4(), objscaleBack);
	glm::mat4 backModel = backTranslationMatrix * rotationZ * scaleMatrixBack;
	glm::mat4 backProj_calc = proj * getView() * backModel;
	return (backProj_calc);
}

glm::mat4 camera::SetProj(glm::mat4 project)
{
	proj = project;
	return glm::mat4();
}

camera* currentCamera = nullptr;


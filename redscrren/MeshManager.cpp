#include "MeshManager.h"

MeshManager::MeshManager()
{

}

MeshManager::~MeshManager()
{

}

GLfloat MeshManager::returnvert(int type)
{
	GLfloat verts[]{
		-0.5f, 0.0f, -0.5f,		0.0f, 1.0f, 0.0f,	0.0f, 1.0f,
	};

	if (type == 1)
	{
		GLfloat vertices[] //player
		{
			-0.5f, 0.0f, -0.5f,		0.0f, 1.0f, 0.0f,	0.0f, 1.0f,
			-0.5f, 0.0f, 0.5f,		0.0f, 1.0f, 0.0f,	0.0f, 0.0f,
			0.5f, 0.0f, 0.5f,		0.0f, 1.0f, 0.0f,	1.0f, 0.0f,
			0.5f, 0.0f, -0.5f,		0.0f, 1.0f, 0.0f,	1.0f, 1.0f,

			-0.5f, 0.0f, -0.5f,		0.0f, 1.0f, 0.0f,	1.0f, 1.0f,
			0.5f, 0.0f, -0.5f,		0.0f, 1.0f, 0.0f,	0.0f, 1.0f,

			0.5f, 0.0f, -0.5f,		0.0f, 1.0f, 0.0f,	1.0f, 1.0f,
			0.5f, 0.0f, 0.5f,		0.0f, 1.0f, 0.0f,	0.0f, 1.0f,

			0.5f, 0.0f, 0.5f,		0.0f, 1.0f, 0.0f,	1.0f, 1.0f,
			-0.5f, 0.0f, 0.5f,		0.0f, 1.0f, 0.0f,	0.0f, 1.0f,

			-0.5f, 0.0f, 0.5f,		0.0f, 1.0f, 0.0f,	1.0f, 1.0f,
			-0.5f, 0.0f, -0.5f,		0.0f, 1.0f, 0.0f,	0.0f, 1.0f,

			0.0f, 0.5f, 0.0f,		0.0f, 1.0f, 1.0f,	0.5f, 0.0f,
		};
		return *vertices;
	}
	else
	{

	}
	return *verts;
}

GLint MeshManager::returnindec(int type)
{
	return GLint();
}

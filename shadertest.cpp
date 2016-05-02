/*
 * shadertest.cpp
 *
 *  Created on: Mar 15, 2016
 *      Author: nevangelista
 */
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <glm/glm.hpp>

#include <iostream>

int main()
{
	GLenum err = glewInit();
	if( GLEW_OK != err )
	{
	    std::cerr
		<< "Error initializing GLEW: "
		<< glewGetErrorString(err)
		<< std::endl;
	}

	return 0;
}





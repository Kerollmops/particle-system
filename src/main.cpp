/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenault <crenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 11:41:05 by crenault          #+#    #+#             */
/*   Updated: 2016/02/14 15:35:12 by crenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Window.hpp"

// test cl.hpp
#include "cl.hpp"
#include <stdio.h>

#define GLFW_EXPOSE_NATIVE_COCOA
#define GLFW_EXPOSE_NATIVE_NSGL
#include "glfw3native.h"
#include <OpenGL/OpenGL.h>

#if defined (__APPLE__) || defined(MACOSX)
# define CL_GL_SHARING_EXT "cl_APPLE_gl_sharing"
#else
# define CL_GL_SHARING_EXT "cl_khr_gl_sharing"
#endif

// ///////////

/*// test eigen
#include <iostream>
#include "Eigen/Dense"
// //////////*/

int		main(int argc, char const **argv)
{
	Window		window("Particle System", 854, 480, GL_FALSE);

	(void)argc;
	(void)argv;

	glClearColor(0.175f, 0.175f, 0.175f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// test cl.hpp

	cl_int						ret;
	std::vector<cl::Platform>	platforms;

	ret = cl::Platform::get(&platforms);
	printf("Number of platforms: %ld\n", platforms.size());

	std::vector<cl::Device>		devices;

	ret = platforms.front().getDevices(CL_DEVICE_TYPE_GPU, &devices);
	printf("Number of devices GPU on first platform: %ld\n", devices.size());

	std::string					device_name;
	std::string					device_extensions;

	ret = devices.front().getInfo(CL_DEVICE_NAME, &device_name);
	printf("Device name: %s\n", device_name.c_str());

	ret = devices.front().getInfo(CL_DEVICE_EXTENSIONS, &device_extensions);
	if (device_extensions.find(CL_GL_SHARING_EXT) == std::string::npos)
	{
		dprintf(2, "This device doesn't support GL/CL sharing...\n");
		throw std::exception();
	}

	// Get current CGL Context and CGL Share group
	CGLContextObj kCGLContext = CGLGetCurrentContext();
	CGLShareGroupObj kCGLShareGroup = CGLGetShareGroup(kCGLContext);

	// Create CL context properties, add handle & share-group enum
	cl_context_properties properties[] = {
		CL_CONTEXT_PROPERTY_USE_CGL_SHAREGROUP_APPLE,
		(cl_context_properties)kCGLShareGroup,
		0
	};

	cl::Context		context = cl::Context::Context(devices, properties, NULL, NULL, &ret);

	if (ret != CL_SUCCESS)
	{
		dprintf(2, "Error while trying to create context...\n");
		throw std::exception();
	}

	/*
	glEnableVertexAttribArray(0);
	glVertexAttribIPointer(0, 2, GL_UNSIGNED_INT, 0, NULL);
	*/

	// create opengl buffer here
	// void glGenBuffers(GLsizei n​, GLuint * buffers​);
	// void glBindBuffer(GLenum target​, GLuint buffer​);
	// void glBufferData​(enum target, sizeiptr size, const void *data, enum usage)

	// cl::BufferGL::BufferGL(context, CL_MEM_READ_WRITE, /*GLuint bufobj*/0, &ret);

	if (ret != CL_SUCCESS)
	{
		dprintf(2, "Error while trying to create buffer from openGL...\n");
		throw std::exception();
	}

	// ///////////

	/*// test eigen
	Eigen::MatrixXd m(2,2);

	m(0,0) = 3;
	m(1,0) = 2.5;
	m(0,1) = -1;
	m(1,1) = m(1,0) + m(0,1);
	std::cout << m << std::endl;
	// //////////*/

	while (glfwWindowShouldClose(window.getPtr()) == GL_FALSE)
	{
		glfwPollEvents();
		if (GLFW_PRESS == glfwGetKey(window.getPtr(), GLFW_KEY_ESCAPE))
		{
			glfwSetWindowShouldClose(window.getPtr(), GL_TRUE);
		}
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//

		glfwSwapBuffers(window.getPtr());
	}
	return (0);
}

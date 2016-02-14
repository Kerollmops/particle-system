/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenault <crenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 11:41:05 by crenault          #+#    #+#             */
/*   Updated: 2016/02/14 22:16:57 by crenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Window.hpp"
#include "Particles.hpp"
#include "pers_proj.hpp"

#include "load_shaders.hpp"

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

int		main(int argc, char const **argv)
{
	Window		window("Particle System", 854, 480, GL_FALSE);
	Particles	particles(1000);

	#pragma message("put this in the particles object")
	GLuint			prog_particles;

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

	particles.bind_array();
	particles.bind_buffer();
	glEnableVertexAttribArray(0);
	glVertexAttribIPointer(0, 2, GL_UNSIGNED_INT, 0, NULL);

	cl::BufferGL::BufferGL(context, CL_MEM_READ_WRITE, particles.get_buffer_id(), &ret);

	if (ret != CL_SUCCESS)
	{
		dprintf(2, "Error while trying to create buffer from openGL...\n");
		throw std::exception();
	}

	//*

	t_mat4		proj_mat;
	t_mat4		trans_mat;
	t_mat4		rot_mat;
	t_mat4		scale_mat;
	t_mat4		model_mat;
	t_mat4		view_mat;

	// matrices
	float screen_ratio = (float)window.get_width() / (float)window.get_height();
	proj_mat = mat4_pers_proj_rh(60.f, screen_ratio, 0.1f, 1000.f);

	// trans_mat = mat4_trans(-0.5f * map_size.x, 0.f, -0.5f * map_size.y);
	trans_mat = mat4_ident();
	// rot_mat = mat4_rotate(0.0f, vec3(0.f, 1.f, 0.f));
	rot_mat = mat4_ident();

	float scale_ratio = 1.f; // 0.08f
	scale_mat = mat4_scale(scale_ratio, scale_ratio, scale_ratio);
	model_mat = mat4_mult(rot_mat, mat4_mult(scale_mat, trans_mat));
	t_vec3 cam_pos = vec3(0, 1, 6);
	view_mat = mat4_view_lookat(cam_pos, vec3(0, 0, 0), vec3(0, 1, 0));

	//*/

	prog_particles = program_from_shaders("src/shaders/particles.vert",
				"src/shaders/particles.frag");
	if (prog_particles == 0)
	{
		dprintf(2, "Error while trying to load shaders...\n");
		throw std::exception();
	}

	// loading matrices

	GLint		tmp_location;

	glUseProgram(prog_particles);

	tmp_location = glGetUniformLocation(prog_particles, "proj_mat");
	glUniformMatrix4fv(tmp_location, 1, GL_FALSE, proj_mat.m);
	tmp_location = glGetUniformLocation(prog_particles, "model_mat");
	glUniformMatrix4fv(tmp_location, 1, GL_FALSE, model_mat.m);
	tmp_location = glGetUniformLocation(prog_particles, "view_mat");
	glUniformMatrix4fv(tmp_location, 1, GL_FALSE, view_mat.m);

	while (glfwWindowShouldClose(window.get_ptr()) == GL_FALSE)
	{
		glfwPollEvents();
		if (GLFW_PRESS == glfwGetKey(window.get_ptr(), GLFW_KEY_ESCAPE))
		{
			glfwSetWindowShouldClose(window.get_ptr(), GL_TRUE);
		}
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		#pragma message("update FPS counter here !!!")

		// particles.bind_array();
		glDrawArrays(GL_POINTS, 0, particles.number_particles());

		glfwSwapBuffers(window.get_ptr());
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Particles.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenault <crenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/14 15:22:40 by crenault          #+#    #+#             */
/*   Updated: 2016/02/15 00:39:55 by crenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <exception>

#if defined (__APPLE__) || defined(MACOSX)
# define CL_GL_SHARING_EXT "cl_APPLE_gl_sharing"
#else
# define CL_GL_SHARING_EXT "cl_khr_gl_sharing"
#endif

#include "Particles.hpp"
#include "load_shaders.hpp"
#include "load_kernel.hpp"

Particles::Particles(size_t number)
	: _number_particles(number) {

	cl_int		err;

	glGenVertexArrays(1, &this->_vao);
	this->allocate_buffer(number);

	// init openCL things
	this->_init_cl_context();

	this->_init_particles_sphere_program = cl::Program::Program(
		program_from_kernel(this->_cl_context(), "src/kernels/init_particles_sphere.cl"));
	if (this->_init_particles_sphere_program() == 0)
	{
		dprintf(2, "Error while trying to load program...\n");
		throw std::exception();
	}
	this->_init_particles_sphere_kernel = cl::Kernel::Kernel(
		this->_init_particles_sphere_program, "init_particles_sphere", &err);
	if (err != CL_SUCCESS)
	{
		dprintf(2, "Error while trying to load kernel...\n");
		throw std::exception();
	}

	this->_positions_cl = clCreateFromGLBuffer(this->_cl_context(),
		CL_MEM_READ_WRITE, this->_positions_vbo, &err);
	if (err != CL_SUCCESS)
	{
		dprintf(2, "Cannot create buffer (status: %d) from opengl\n", err);
		throw std::exception();
	}

	// openGL
	this->_gl_program = program_from_shaders("src/shaders/particles.vert",
				"src/shaders/particles.frag");
	if (this->_gl_program == 0)
	{
		dprintf(2, "Error while trying to load shaders...\n");
		throw std::exception();
	}
}

// Particles::Particles(Particles const &src) {

// 	*this = src;
// }

Particles::~Particles(void) {

	glDeleteVertexArrays(1, &this->_vao);
	this->deallocate_buffer();
	glDeleteProgram(this->_gl_program);
}

// Particles		&Particles::operator=(Particles const &src) {

// 	static_cast<void>(src);
// 	return *this;
// }

void			Particles::_init_cl_context(void) {

	cl_int						ret;
	std::vector<cl::Platform>	platforms;

	ret = cl::Platform::get(&platforms);
	// printf("Number of platforms: %ld\n", platforms.size());

	std::vector<cl::Device>		devices;

	ret = platforms.front().getDevices(CL_DEVICE_TYPE_GPU, &devices);
	// printf("Number of devices GPU on first platform: %ld\n", devices.size());

	std::string					device_name;
	std::string					device_extensions;

	ret = devices.front().getInfo(CL_DEVICE_NAME, &device_name);
	// printf("Device name: %s\n", device_name.c_str());

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

	this->_cl_context = cl::Context::Context(devices, properties, NULL, NULL, &ret);
	if (ret != CL_SUCCESS)
	{
		dprintf(2, "Error while trying to create context...\n");
		throw std::exception();
	}

	this->bind_array();
	this->bind_buffer();
	glEnableVertexAttribArray(0);
	glVertexAttribIPointer(0, 2, GL_UNSIGNED_INT, 0, NULL);

	cl::BufferGL::BufferGL(this->_cl_context, CL_MEM_READ_WRITE, this->_positions_vbo, &ret);
	if (ret != CL_SUCCESS)
	{
		dprintf(2, "Error while trying to create buffer from openGL...\n");
		throw std::exception();
	}
}

size_t			Particles::number_particles(void) const {

	return (this->_number_particles);
}

void			Particles::allocate_buffer(size_t number) {

	size_t		buff_size;

	this->_number_particles = number;
	buff_size = this->_number_particles * sizeof(float) * 3;
	this->bind_array();
	glGenBuffers(1, &this->_positions_vbo);
	this->bind_buffer();
	glBufferData(GL_ARRAY_BUFFER, buff_size, NULL, GL_STATIC_DRAW);
}

void			Particles::deallocate_buffer(void) {

	glDeleteBuffers(1, &this->_positions_vbo);
}

void			Particles::bind_array(void) const {

	glBindVertexArray(this->_vao);
}

void			Particles::bind_buffer(void) const {

	glBindBuffer(GL_ARRAY_BUFFER, this->_positions_vbo);
}

GLuint			Particles::get_buffer_id(void) const {

	return (this->_positions_vbo);
}

GLint			Particles::get_uniform_location(const char *name) const {

	return (glGetUniformLocation(this->_gl_program, name));
}

void			Particles::init_particles(void) const {

	/*cl_int		ret;

	// acquire buffer
	ret = clEnqueueAcquireGLObjects(command_queue_cl, 1, &map_heights_buff_cl,
		0, NULL, NULL);
	if (ret != CL_SUCCESS)
	{
		dprintf(2, "clEnqueueAcquireGLObjects Status: %d\n", ret);
		throw std::exception();
	}

	//

	// release buffer
	ret = clEnqueueReleaseGLObjects(command_queue_cl, 1, &map_heights_buff_cl,
		0, NULL, NULL);
	if (ret != CL_SUCCESS)
	{
		dprintf(2, "clEnqueueReleaseGLObjects Status: %d\n", ret);
		throw std::exception();
	}*/
}

void			Particles::update_particles(void) const {

	//
}

void			Particles::use_gl_program(void) const {

	glUseProgram(this->_gl_program);
}

void			Particles::draw_arrays(void) const {

	glDrawArrays(GL_POINTS, 0, this->_number_particles);
}

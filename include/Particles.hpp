/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Particles.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenault <crenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/14 15:22:40 by crenault          #+#    #+#             */
/*   Updated: 2016/02/15 00:35:30 by crenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARTICULES_HPP
# define PARTICULES_HPP

# define GLFW_INCLUDE_GLCOREARB
# include "glfw3.h"

#define GLFW_EXPOSE_NATIVE_COCOA
#define GLFW_EXPOSE_NATIVE_NSGL
#include "glfw3native.h"
#include <OpenGL/OpenGL.h>

# include "cl.hpp"

# define ONE_MILLION	1000000

class Particles {

public:
	Particles(size_t number = ONE_MILLION);
	// Particles(Particles const &src);
	virtual ~Particles(void);
	Particles		&operator=(Particles const &src) = delete;

	size_t			number_particles(void) const; // not needed

	void			allocate_buffer(size_t number);
	void			deallocate_buffer(void);

	void			bind_array(void) const;
	void			bind_buffer(void) const;

	GLuint			get_buffer_id(void) const;
	GLint			get_uniform_location(const char *name) const;

	// openCL
	void			init_particles(void) const;
	void			update_particles(void) const;

	// openGL
	void			use_gl_program(void) const;
	void			draw_arrays(void) const;

private:
	size_t			_number_particles;

	cl::Context		_cl_context;

	GLuint			_vao;
	GLuint			_positions_vbo;

	cl_mem			_positions_cl;

	cl::Program		_init_particles_sphere_program;
	cl::Kernel		_init_particles_sphere_kernel;

	cl::Program		_update_particles_program;
	cl::Kernel		_update_particles_kernel;

	GLuint			_gl_program;

	void			_init_cl_context(void);
};

#endif

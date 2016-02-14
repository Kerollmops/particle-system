/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Particles.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenault <crenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/14 15:22:40 by crenault          #+#    #+#             */
/*   Updated: 2016/02/14 22:08:01 by crenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARTICULES_HPP
# define PARTICULES_HPP

# define GLFW_INCLUDE_GLCOREARB
# include "glfw3.h"

# define ONE_MILLION	1000000

class Particles {

public:
	Particles(size_t number = ONE_MILLION);
	// Particles(Particles const &src);
	virtual ~Particles(void);
	Particles		&operator=(Particles const &src) = delete;

	size_t			number_particles(void) const;

	void			allocate_buffer(size_t number);
	void			deallocate_buffer(void);

	void			bind_array(void) const;
	void			bind_buffer(void) const;

	GLuint			get_buffer_id(void) const;

private:
	size_t			_number_particles;

	GLuint			_vao;
	GLuint			_positions_vbo;

};

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Particles.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenault <crenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/14 15:22:40 by crenault          #+#    #+#             */
/*   Updated: 2016/02/14 19:41:50 by crenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Particles.hpp"

Particles::Particles(size_t number) {

	glGenVertexArrays(1, &this->_vao);
	this->allocate_buffer(number);
}

// Particles::Particles(Particles const &src) {

// 	*this = src;
// }

Particles::~Particles(void) {

	glDeleteVertexArrays(1, &this->_vao);
	this->deallocate_buffer();
}

// Particles		&Particles::operator=(Particles const &src) {

// 	static_cast<void>(src);
// 	return *this;
// }

void			Particles::allocate_buffer(size_t number) {

	this->bind_array();
	glGenBuffers(1, &this->_positions_vbo);
	this->bind_buffer();
	glBufferData(GL_ARRAY_BUFFER, number * sizeof(float) * 3, NULL, GL_STATIC_DRAW);
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
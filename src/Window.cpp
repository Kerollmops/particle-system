/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Window.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenault <crenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 13:05:03 by crenault          #+#    #+#             */
/*   Updated: 2016/02/13 13:26:04 by crenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Window.hpp"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <exception>

static void		glfw_error_callback(int error, const char *description)
{
	dprintf(2, "GLFW Error: code %i msg: %s\n", error, description);
}

static void		init_gl_context(void)
{
	glfwSetErrorCallback(glfw_error_callback);
	if (glfwInit() == 0)
	{
		dprintf(2, "ERROR: could not start GLFW3\n");
		throw std::exception();
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);
}

Window::Window(const char *title, int width, int height, int resizable)
	: _title(title), _width(width), _height(height), _resizable(resizable) {

	init_gl_context();
	glfwWindowHint(GLFW_RESIZABLE, resizable);
	this->_window_ptr = glfwCreateWindow(this->_width, this->_height, this->_title.c_str(), NULL, NULL);
	glfwGetWindowSize(this->_window_ptr, &this->_width, &this->_height);
	if (this->_window_ptr == NULL)
	{
		dprintf(2, "ERROR: could not open window with GLFW3\n");
		throw std::exception();
	}
	glfwMakeContextCurrent(this->_window_ptr);
	glfwGetFramebufferSize(this->_window_ptr, &this->_frame_width, &this->_frame_height);
	glViewport(0, 0, this->_frame_width, this->_frame_height);
}

Window::Window(Window const &src) {

	*this = src;
}

Window::~Window(void) {

	glfwMakeContextCurrent(NULL);
	glfwDestroyWindow(this->_window_ptr);
}

/*Window		&Window::operator=(Window const &src) {

	static_cast<void>(src);
	return *this;
}*/

GLFWwindow			*Window::getPtr(void)
{
	return (this->_window_ptr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Window.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenault <crenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 13:05:03 by crenault          #+#    #+#             */
/*   Updated: 2016/02/14 19:58:56 by crenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_HPP
# define WINDOW_HPP

# define GLFW_INCLUDE_GLCOREARB
# include "glfw3.h"
# include <string>

class Window {

public:
	Window(void) = delete;
	Window(const char *title, int width, int height, int resizable);
	// Window(Window const &src);
	virtual ~Window(void);
	Window		&operator=(Window const &src) = delete;

	GLFWwindow		*get_ptr(void);

	int				get_width(void) const;
	int				get_height(void) const;

private:
	std::string	_title;
	int			_width;
	int			_height;
	int			_resizable;

	int			_frame_width;
	int			_frame_height;

	GLFWwindow	*_window_ptr;
};

#endif

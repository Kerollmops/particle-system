/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Window.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenault <crenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 13:05:03 by crenault          #+#    #+#             */
/*   Updated: 2016/02/11 13:30:11 by crenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_HPP
# define WINDOW_HPP

# define GLFW_INCLUDE_GLCOREARB
# include "glfw3.h"

class Window {

public:
	Window(void) = delete;
	Window(const char *title, int width, int height, int resizable);
	Window(Window const &src);
	virtual ~Window(void);
	// Window		&operator=(Window const &src);

	GLFWwindow		*getWindowPtr(void);

private:
	char		*_title;
	int			_resizable;

	int			_width;
	int			_height;

	int			_frame_width;
	int			_frame_height;

	GLFWwindow	*_window_ptr;
};

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenault <crenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 11:41:05 by crenault          #+#    #+#             */
/*   Updated: 2016/02/11 13:31:01 by crenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Window.hpp"

int		main(int argc, char const **argv)
{
	Window		window("Particle-system", 854, 480, GL_FALSE);

	(void)argc;
	(void)argv;

	while (glfwWindowShouldClose(window.getWindowPtr()) == GL_FALSE)
	{
		glfwPollEvents();
		if (GLFW_PRESS == glfwGetKey(window.getWindowPtr(), GLFW_KEY_ESCAPE))
		{
			glfwSetWindowShouldClose(window.getWindowPtr(), GL_TRUE);
		}
	}

	return (0);
}

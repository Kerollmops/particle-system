/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenault <crenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 11:41:05 by crenault          #+#    #+#             */
/*   Updated: 2016/02/13 16:29:32 by crenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Window.hpp"

// test eigen
#include <iostream>
#include "Eigen/Dense"
// //////////

int		main(int argc, char const **argv)
{
	Window		window("Particle System", 854, 480, GL_FALSE);

	(void)argc;
	(void)argv;

	glClearColor(0.175f, 0.175f, 0.175f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// test eigen

	Eigen::MatrixXd m(2,2);

	m(0,0) = 3;
	m(1,0) = 2.5;
	m(0,1) = -1;
	m(1,1) = m(1,0) + m(0,1);
	std::cout << m << std::endl;
	// printf("%s\n", (static_cast<std::string>(m).c_str());

	// //////////

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

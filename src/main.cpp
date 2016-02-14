/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenault <crenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 11:41:05 by crenault          #+#    #+#             */
/*   Updated: 2016/02/15 00:23:20 by crenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Window.hpp"
#include "Particles.hpp"
#include "pers_proj.hpp"

// test cl.hpp
#include "cl.hpp"
#include <stdio.h>

int		main(int argc, char const **argv)
{
	Window		window("Particle System", 854, 480, GL_FALSE);
	Particles	particles(1000);

	#pragma message("put this in the particles object")

	(void)argc;
	(void)argv;

	glClearColor(0.175f, 0.175f, 0.175f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	//

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

	// loading matrices

	GLint		tmp_location;

	particles.use_gl_program();
	tmp_location = particles.get_uniform_location("proj_mat");
	glUniformMatrix4fv(tmp_location, 1, GL_FALSE, proj_mat.m);
	tmp_location = particles.get_uniform_location("model_mat");
	glUniformMatrix4fv(tmp_location, 1, GL_FALSE, model_mat.m);
	tmp_location = particles.get_uniform_location("view_mat");
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
		// create fps counter with particles turning around gravity points !!!

		// particles.bind_array();
		particles.draw_arrays();

		glfwSwapBuffers(window.get_ptr());
	}
	return (0);
}

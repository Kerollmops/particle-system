/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_shaders.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenault <crenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 19:46:18 by crenault          #+#    #+#             */
/*   Updated: 2016/02/14 22:01:02 by crenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOAD_SHADERS_HPP
# define LOAD_SHADERS_HPP

# define GLFW_INCLUDE_GLCOREARB
# include "glfw3.h"

GLuint		program_from_shaders(const char *vertex_file,
			const char *fragment_file);

#endif

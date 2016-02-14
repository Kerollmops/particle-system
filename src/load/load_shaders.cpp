/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_shaders.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenault <crenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/10 14:38:49 by crenault          #+#    #+#             */
/*   Updated: 2016/01/28 18:04:48 by crenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "load_shaders.hpp"
#include "get_file_content.hpp"

static GLuint	link_shaders(GLuint vertex_id, GLuint fragment_id)
{
	GLuint			program_id;

	program_id = glCreateProgram();
	glAttachShader(program_id, vertex_id);
	glAttachShader(program_id, fragment_id);
	glLinkProgram(program_id);
	glDetachShader(program_id, vertex_id);
	glDetachShader(program_id, fragment_id);
	return (program_id);
}

static int		check_link_result(GLuint program_id)
{
	GLint			success;
	int				bufflen;
	GLchar			*error_message;

	glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &bufflen);
	if (bufflen > 1)
	{
		error_message = (char*)malloc(sizeof(char) * (bufflen + 1));
		glGetShaderInfoLog(program_id, bufflen, NULL, error_message);
		dprintf(2, "Log found:\n%s", error_message);
		free(error_message);
	}
	glGetProgramiv(program_id, GL_LINK_STATUS, &success);
	if (success != GL_TRUE)
	{
		dprintf(2, "Failed to link program.\n");
		return (0);
	}
	return (1);
}

static int		compile_shader_check(GLuint shader_id, const char **content)
{
	GLint			success;
	int				bufflen;
	GLchar			*error_message;

	glShaderSource(shader_id, 1, content, NULL);
	glCompileShader(shader_id);
	glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &bufflen);
	if (bufflen > 1)
	{
		error_message = (char*)malloc(sizeof(char) * (bufflen + 1));
		glGetShaderInfoLog(shader_id, bufflen, 0, error_message);
		dprintf(2, "Log found:\n%s", error_message);
		free(error_message);
	}
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
	if (success != GL_TRUE)
	{
		dprintf(2, "Failed to compile shader.\n");
		return (0);
	}
	return (1);
}

GLuint			program_from_shaders(const char *vertex_file,
				const char *fragment_file)
{
	GLuint			vertex_id;
	GLuint			fragment_id;
	GLuint			prog_id;
	char			*vertex_c;
	char			*fragment_c;

	if ((vertex_c = get_file_content(vertex_file)) == NULL)
		return (0);
	if ((fragment_c = get_file_content(fragment_file)) == NULL)
	{
		free(vertex_c);
		return (0);
	}
	vertex_id = glCreateShader(GL_VERTEX_SHADER);
	fragment_id = glCreateShader(GL_FRAGMENT_SHADER);
	if (compile_shader_check(vertex_id, (const char **)&vertex_c) == 0
	|| compile_shader_check(fragment_id, (const char **)&fragment_c) == 0
	|| check_link_result(prog_id = link_shaders(vertex_id, fragment_id)) == 0)
	{
		free(vertex_c);
		free(fragment_c);
		return (0);
	}
	glDeleteShader(vertex_id);
	glDeleteShader(fragment_id);
	free(vertex_c);
	free(fragment_c);
	return (prog_id);
}

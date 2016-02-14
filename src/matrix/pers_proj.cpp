/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pers_proj.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenault <crenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/22 00:02:10 by crenault          #+#    #+#             */
/*   Updated: 2016/02/07 19:16:23 by crenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <math.h>
#include "pers_proj.hpp"

t_mat4			mat4_pers_proj_rh(float fov, float ar, float near, float far)
{
	t_mat4			mat;
	float			xymax;
	float			width;
	float			height;
	float			depth;

	xymax = near * tan(fov * M_PI / 360);
	width = xymax + xymax;
	height = xymax + xymax;
	depth = near - far;
	bzero(mat.m, sizeof(mat.m));
	mat.m[0] = (2.f * near / width) / ar;
	mat.m[5] = 2.f * near / height;
	mat.m[10] = far / depth;
	mat.m[11] = -1.f;
	mat.m[14] = (near * far) / depth;
	return (mat);
}

t_mat4			mat4_pers_proj_lh(float fov, float ar, float near, float far)
{
	t_mat4			mat;
	float			xymax;
	float			width;
	float			height;

	xymax = near * tan(fov * M_PI / 360);
	width = xymax + xymax;
	height = xymax + xymax;
	bzero(mat.m, sizeof(mat.m));
	mat.m[0] = (2.f * near / width) / ar;
	mat.m[5] = 2.f * near / height;
	mat.m[10] = far / (far - near);
	mat.m[11] = 1.f;
	mat.m[14] = (near * far) / (near - far);
	return (mat);
}

t_mat4			mat4_view_lookat(t_vec3 eye, t_vec3 targ, t_vec3 up)
{
	t_mat4		out;
	t_vec3		zaxis;
	t_vec3		xaxis;
	t_vec3		yaxis;

	zaxis = vec3_normal(vec3_sub(eye, targ));
	xaxis = vec3_normal(vec3_cross(up, zaxis));
	yaxis = vec3_cross(zaxis, xaxis);
	out = mat4_ident();
	out.m[0] = xaxis.x;
	out.m[1] = yaxis.x;
	out.m[2] = zaxis.x;
	out.m[4] = xaxis.y;
	out.m[5] = yaxis.y;
	out.m[6] = zaxis.y;
	out.m[8] = xaxis.z;
	out.m[9] = yaxis.z;
	out.m[10] = zaxis.z;
	out.m[12] = -vec3_dot(xaxis, eye);
	out.m[13] = -vec3_dot(yaxis, eye);
	out.m[14] = -vec3_dot(zaxis, eye);
	return (out);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pers_proj.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenault <crenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/14 19:46:11 by crenault          #+#    #+#             */
/*   Updated: 2016/02/14 19:58:16 by crenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.hpp"

Eigen::MatrixXd		get_pers_proj(float fov, float ar, float near, float far) {

	Eigen::MatrixXd		mat(4, 4);
	float				xymax;
	float				width;
	float				height;
	float				depth;

	xymax = near * tan(fov * M_PI / 360);
	width = xymax + xymax;
	height = xymax + xymax;
	depth = near - far;
	bzero(mat.data(), sizeof(*mat.data()) * 4 * 4);
	mat(0, 0) = (2.f * near / width) / ar;
	mat(1, 1) = 2.f * near / height;
	mat(2, 2) = far / depth;
	mat(2, 3) = -1.f;
	mat(3, 2) = (near * far) / depth;
	return (mat);
}

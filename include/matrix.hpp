/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenault <crenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/14 19:57:26 by crenault          #+#    #+#             */
/*   Updated: 2016/02/14 19:58:00 by crenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX
# define MATRIX

# include "Eigen/Dense"

Eigen::MatrixXd		get_pers_proj(float fov, float ar, float near, float far);

#endif

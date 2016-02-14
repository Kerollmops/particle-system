/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pers_proj.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenault <crenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/22 16:23:03 by crenault          #+#    #+#             */
/*   Updated: 2016/02/14 21:50:29 by crenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PERS_PROJ_H
# define PERS_PROJ_H

# include "mat4.h"

t_mat4			mat4_pers_proj_rh(float fov, float ar, float near, float far);
t_mat4			mat4_pers_proj_lh(float fov, float ar, float near, float far);

t_mat4			mat4_view_lookat(t_vec3 eye, t_vec3 targ, t_vec3 up);

#endif

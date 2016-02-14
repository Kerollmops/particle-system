/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_kernel.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenault <crenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 22:07:33 by crenault          #+#    #+#             */
/*   Updated: 2016/02/14 22:00:57 by crenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOAD_KERNEL_HPP
# define LOAD_KERNEL_HPP

# include <OpenCL/opencl.h>

cl_program		program_from_kernel(cl_context context,
				const char *kernel_file);

#endif

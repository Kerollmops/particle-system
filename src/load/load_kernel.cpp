/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_kernel.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenault <crenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 22:16:04 by crenault          #+#    #+#             */
/*   Updated: 2016/02/14 22:01:04 by crenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "load_kernel.hpp"
#include "get_file_content.hpp"

static void		build_info(cl_context context, cl_program program)
{
	cl_int			ret;
	cl_uint			i;
	cl_uint			num_devices;
	cl_device_id	devices[64];
	size_t			log_len;
	char			*log_mess;

	ret = clGetContextInfo(context, CL_CONTEXT_NUM_DEVICES, sizeof(cl_uint),
		(void*)&num_devices, NULL);
	if (ret != CL_SUCCESS)
		return ;

	ret = clGetContextInfo(context, CL_CONTEXT_DEVICES, sizeof(devices),
		(void*)devices, NULL);
	if (ret != CL_SUCCESS)
		return ;

	i = 0;
	while (i < num_devices)
	{
		clGetProgramBuildInfo(program, devices[i], CL_PROGRAM_BUILD_LOG, 0,
			NULL, &log_len);
		log_mess = (char *)malloc(log_len);
		clGetProgramBuildInfo(program, devices[i], CL_PROGRAM_BUILD_LOG,
			log_len, log_mess, NULL);
		dprintf(2, "%s\n", log_mess);
		free(log_mess);
		++i;
	}
}

cl_program		program_from_kernel(cl_context context, const char *kernel_file)
{
	char		*kernel_c;
	cl_int		ret;

	if ((kernel_c = get_file_content(kernel_file)) == NULL)
		return (0);

	cl_program program = clCreateProgramWithSource(context, 1,
		(const char **)&kernel_c, NULL, &ret);
	if (ret != CL_SUCCESS)
	{
		dprintf(2, "Failed to create program from \"%s\"\n", kernel_file);
		return (0);
	}

	free(kernel_c);

	ret = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
	if (ret != CL_SUCCESS)
	{
		dprintf(2, "Failed to compile (status: %d) \"%s\"\n", ret, kernel_file);
		build_info(context, program);
		return (0);
	}
	return (program);
}

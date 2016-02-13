/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OpenCL.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenault <crenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 13:05:18 by crenault          #+#    #+#             */
/*   Updated: 2016/02/13 15:58:49 by crenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "OpenCL.hpp"

OpenCL::OpenCL(void) {

	//
}

OpenCL::OpenCL(OpenCL const &src) {

	*this = src;
}

OpenCL::~OpenCL(void) {

	//
}

OpenCL		&OpenCL
	::operator=(OpenCL const &src) {

	static_cast<void>(src);
	return *this;
}


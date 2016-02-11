/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OpenCl.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenault <crenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 13:05:18 by crenault          #+#    #+#             */
/*   Updated: 2016/02/11 13:06:16 by crenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "OpenCl.hpp"

OpenCl::OpenCl(void) {

	//
}

OpenCl::OpenCl(OpenCl const &src) {

	*this = src;
}

OpenCl::~OpenCl(void) {

	//
}

OpenCl		&OpenCl::operator=(OpenCl const &src) {

	static_cast<void>(src);
	return *this;
}


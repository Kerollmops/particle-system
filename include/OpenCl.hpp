/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OpenCl.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenault <crenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 13:05:18 by crenault          #+#    #+#             */
/*   Updated: 2016/02/11 13:05:45 by crenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPENCL_HPP
# define OPENCL_HPP

class OpenCl {

public:
	OpenCl(void);
	OpenCl(OpenCl const &src);
	virtual ~OpenCl(void);
	OpenCl		&operator=(OpenCl const &src);

private:
	//

};

#endif

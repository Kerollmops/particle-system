/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OpenCL.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenault <crenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 13:05:18 by crenault          #+#    #+#             */
/*   Updated: 2016/02/13 15:58:43 by crenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPENCL_HPP
# define OPENCL_HPP

class OpenCL {

public:
	OpenCL(void);
	OpenCL(OpenCL const &src);
	virtual ~OpenCL(void);
	OpenCL		&operator=(OpenCL const &src);

private:
	//

};

#endif

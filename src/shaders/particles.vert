#version 400

layout(location = 0) in vec3 particles_pos;

uniform mat4		proj_mat; // projection matrix
uniform mat4		view_mat; // view matrix
uniform mat4		model_mat; // model matrix

void		main()
{
	gl_Position = proj_mat * view_mat * model_mat * vec4(particles_pos, 1.0);
}

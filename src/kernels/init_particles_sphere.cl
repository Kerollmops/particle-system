__kernel void    init_particles_sphere(__global uint *particles_pos)
{
    size_t      x;

    x = get_global_id(0);

    particles_pos[x] = 10.f;
}

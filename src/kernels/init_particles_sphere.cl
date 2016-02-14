__kernel void    init_particles_sphere(__global uint    *particles_pos,
                                                uint    particles_number)
{
    size_t      x;
    size_t      y;

    x = get_global_id(0);
    y = get_global_id(1);

    // do something here !!!
}

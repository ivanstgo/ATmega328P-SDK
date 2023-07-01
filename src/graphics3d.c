#include "graphics3d.h"
#include <math.h>

float perspective_matrix[4][4] = {0};
float rotationx_matrix[4][4] = {0};
float rotationy_matrix[4][4] = {0};
float rotationz_matrix[4][4] = {0};

/**
 * Configures the perspective matrix
 * @param angle angle of vision
 * @param z_far far z
 * @param z_near near z
 */
void set_perspective_matrix(float angle, float z_far, float z_near)
{
    float a = 64.0f / 128.0f;
    float fov = 1.0f / tanf(0.5f * angle * M_PI / 180.0f);
    perspective_matrix[0][0] = a * fov;
    perspective_matrix[1][1] = fov;
    perspective_matrix[2][2] = z_far / (z_far - z_near);
    perspective_matrix[2][3] = 1.0f;
    perspective_matrix[3][2] = -z_far * z_near / (z_far - z_near);
    perspective_matrix[3][3] = 0.0f;
}

/**
 * Sets the angle of rotation around x, y and z axis
 * @param alpha rotation around x
 * @param beta rotation around y
 * @param gamma rotation around z
 */
void set_rotation_matrix(float alpha, float beta, float gamma)
{
    rotationx_matrix[0][0] = 1.0f;
    rotationx_matrix[1][1] = cosf(alpha);
    rotationx_matrix[1][2] = -sinf(alpha);
    rotationx_matrix[2][1] = sinf(alpha);
    rotationx_matrix[2][2] = cosf(alpha);
    rotationx_matrix[3][3] = 1.0f;

    rotationy_matrix[0][0] = cosf(beta);
    rotationy_matrix[0][2] = sinf(beta);
    rotationy_matrix[1][1] = 1.0f;
    rotationy_matrix[2][0] = -sinf(beta);
    rotationy_matrix[2][2] = cosf(beta);
    rotationx_matrix[3][3] = 1.0f;

    rotationz_matrix[0][0] = cosf(gamma);
    rotationz_matrix[0][1] = sinf(gamma);
    rotationz_matrix[1][0] = -sinf(gamma);
    rotationz_matrix[1][1] = cosf(gamma);
    rotationz_matrix[2][2] = 1.0f;
    rotationz_matrix[3][3] = 1.0f;
}

/**
 * Computes the cross product between two vectors and normalize it
 * @param a first vector
 * @param b second vector
 * @param c output vector
 */
void cross_product(Point3 *a, Point3 *b, Point3 *output)
{
    output->x = a->y * b->z - a->z * b->y;
    output->y = a->x * b->z - a->z * b->x;
    output->z = a->x * b->y - a->y * b->x;
}

/**
 * Normalize a vector
 * @param a vector to normalize
 */
void normalize_vector3d(Point3 *a)
{
    float r = sqrtf(dot_product(a, a));
    if (r != 0)
    {
        a->x /= r;
        a->y /= r;
        a->z /= r;
    }
}

/**
 * Computes the dot product between two vectors
 * @param a first vector
 * @param b second vector
 * @return the scalar product of a and b
 */
float dot_product(Point3 *a, Point3 *b)
{
    return a->x * b->x + a->y * b->y + a->z * b->z;
}

/**
 * @param input input vector
 * @param output transformed vector
 * @param matrix 4x4 transformation matrix
 */
void transform_vector3d(Point3 *input, Point3 *output, float matrix[4][4])
{
    output->x = input->x * matrix[0][0] + input->y * matrix[1][0] + input->z * matrix[2][0] + matrix[3][0];
    output->y = input->x * matrix[0][1] + input->y * matrix[1][1] + input->z * matrix[2][1] + matrix[3][1];
    output->z = input->x * matrix[0][2] + input->y * matrix[1][2] + input->z * matrix[2][2] + matrix[3][2];
    float w = input->x * matrix[0][3] + input->y * matrix[1][3] + input->z * matrix[2][3] + matrix[3][3];
    if (w != 0.0f)
    {
        output->x /= w;
        output->y /= w;
        output->z /= w;
    }
}

/**
 * Projects a R3 vector into R2 space
 * @param input the 3d point
 * @param output the 2d point
 */
void project_point3d(Point3 *input, Point *output)
{
    Point3 translated;
    translated.x = input->x;
    translated.y = input->y;
    translated.z = input->z + 2.4f;
    Point3 projected;
    transform_vector3d(&translated, &projected, perspective_matrix);
    output->x = (int)((projected.x + 1.0f) * 64.0f);
    output->y = (int)((projected.y + 1.0f) * 32.0f);
}

/**
 * Apply rotation transformation to a 3d point
 * @param input input 3d point
 * @param output rotated 3d point
 */
void rotate_point3d(Point3 *input, Point3 *output)
{
    Point3 rotated_x;
    transform_vector3d(input, &rotated_x, rotationx_matrix);
    Point3 rotated_y;
    transform_vector3d(&rotated_x, &rotated_y, rotationy_matrix);
    transform_vector3d(&rotated_y, output, rotationz_matrix);
}

/**
 * Creates a cube
 * @param cube pointer to a cube struct
 */
void init_cube(Cube *cube)
{
    Point3 p0 = {0.0f, 0.0f, 0.0f};
    Point3 p1 = {0.0f, 1.0f, 0.0f};
    Point3 p2 = {1.0f, 1.0f, 0.0f};
    Point3 p3 = {1.0f, 0.0f, 0.0f};
    Point3 p4 = {0.0f, 0.0f, 1.0f};
    Point3 p5 = {0.0f, 1.0f, 1.0f};
    Point3 p6 = {1.0f, 1.0f, 1.0f};
    Point3 p7 = {1.0f, 0.0f, 1.0f};

    cube->points[0] = p0;
    cube->points[1] = p1;
    cube->points[2] = p2;
    cube->points[3] = p3;
    cube->points[4] = p4;
    cube->points[5] = p5;
    cube->points[6] = p6;
    cube->points[7] = p7;

    cube->triangles[0].v0 = &(cube->projected_points[0]);
    cube->triangles[0].v1 = &(cube->projected_points[1]);
    cube->triangles[0].v2 = &(cube->projected_points[2]);

    cube->triangles[1].v0 = &(cube->projected_points[0]);
    cube->triangles[1].v1 = &(cube->projected_points[2]);
    cube->triangles[1].v2 = &(cube->projected_points[3]);

    cube->triangles[2].v0 = &(cube->projected_points[3]);
    cube->triangles[2].v1 = &(cube->projected_points[2]);
    cube->triangles[2].v2 = &(cube->projected_points[6]);

    cube->triangles[3].v0 = &(cube->projected_points[3]);
    cube->triangles[3].v1 = &(cube->projected_points[6]);
    cube->triangles[3].v2 = &(cube->projected_points[7]);

    cube->triangles[4].v0 = &(cube->projected_points[7]);
    cube->triangles[4].v1 = &(cube->projected_points[6]);
    cube->triangles[4].v2 = &(cube->projected_points[5]);

    cube->triangles[5].v0 = &(cube->projected_points[7]);
    cube->triangles[5].v1 = &(cube->projected_points[5]);
    cube->triangles[5].v2 = &(cube->projected_points[4]);

    cube->triangles[6].v0 = &(cube->projected_points[4]);
    cube->triangles[6].v1 = &(cube->projected_points[5]);
    cube->triangles[6].v2 = &(cube->projected_points[1]);

    cube->triangles[7].v0 = &(cube->projected_points[4]);
    cube->triangles[7].v1 = &(cube->projected_points[1]);
    cube->triangles[7].v2 = &(cube->projected_points[0]);

    cube->triangles[8].v0 = &(cube->projected_points[1]);
    cube->triangles[8].v1 = &(cube->projected_points[5]);
    cube->triangles[8].v2 = &(cube->projected_points[6]);

    cube->triangles[9].v0 = &(cube->projected_points[1]);
    cube->triangles[9].v1 = &(cube->projected_points[6]);
    cube->triangles[9].v2 = &(cube->projected_points[2]);

    cube->triangles[10].v0 = &(cube->projected_points[7]);
    cube->triangles[10].v1 = &(cube->projected_points[4]);
    cube->triangles[10].v2 = &(cube->projected_points[0]);

    cube->triangles[11].v0 = &(cube->projected_points[7]);
    cube->triangles[11].v1 = &(cube->projected_points[0]);
    cube->triangles[11].v2 = &(cube->projected_points[5]);

    // cube->triangles3d[0].v0 = &(cube->rotated_points[0]);
    // cube->triangles3d[0].v1 = &(cube->rotated_points[1]);
    // cube->triangles3d[0].v2 = &(cube->rotated_points[2]);

    // cube->triangles3d[1].v0 = &(cube->rotated_points[0]);
    // cube->triangles3d[1].v1 = &(cube->rotated_points[2]);
    // cube->triangles3d[1].v2 = &(cube->rotated_points[3]);

    // cube->triangles3d[2].v0 = &(cube->rotated_points[3]);
    // cube->triangles3d[2].v1 = &(cube->rotated_points[2]);
    // cube->triangles3d[2].v2 = &(cube->rotated_points[6]);

    // cube->triangles3d[3].v0 = &(cube->rotated_points[3]);
    // cube->triangles3d[3].v1 = &(cube->rotated_points[6]);
    // cube->triangles3d[3].v2 = &(cube->rotated_points[7]);

    // cube->triangles3d[4].v0 = &(cube->rotated_points[7]);
    // cube->triangles3d[4].v1 = &(cube->rotated_points[6]);
    // cube->triangles3d[4].v2 = &(cube->rotated_points[5]);

    // cube->triangles3d[5].v0 = &(cube->rotated_points[7]);
    // cube->triangles3d[5].v1 = &(cube->rotated_points[5]);
    // cube->triangles3d[5].v2 = &(cube->rotated_points[4]);

    // cube->triangles3d[6].v0 = &(cube->rotated_points[4]);
    // cube->triangles3d[6].v1 = &(cube->rotated_points[5]);
    // cube->triangles3d[6].v2 = &(cube->rotated_points[1]);

    // cube->triangles3d[7].v0 = &(cube->rotated_points[4]);
    // cube->triangles3d[7].v1 = &(cube->rotated_points[1]);
    // cube->triangles3d[7].v2 = &(cube->rotated_points[0]);

    // cube->triangles3d[8].v0 = &(cube->rotated_points[1]);
    // cube->triangles3d[8].v1 = &(cube->rotated_points[5]);
    // cube->triangles3d[8].v2 = &(cube->rotated_points[6]);

    // cube->triangles3d[9].v0 = &(cube->rotated_points[1]);
    // cube->triangles3d[9].v1 = &(cube->rotated_points[6]);
    // cube->triangles3d[9].v2 = &(cube->rotated_points[2]);

    // cube->triangles3d[10].v0 = &(cube->rotated_points[7]);
    // cube->triangles3d[10].v1 = &(cube->rotated_points[4]);
    // cube->triangles3d[10].v2 = &(cube->rotated_points[0]);

    // cube->triangles3d[11].v0 = &(cube->rotated_points[7]);
    // cube->triangles3d[11].v1 = &(cube->rotated_points[0]);
    // cube->triangles3d[11].v2 = &(cube->rotated_points[5]);
}

/**
 * Rotates a cube
 * @param cube pointer to a cube
 */
void rotate_cube(Cube *cube)
{
    for (int i = 0; i < 8; i++)
        rotate_point3d(&(cube->points[i]), &(cube->rotated_points[i]));
}

/**
 * Applies perspective projection to a cube
 * @param cube point to a cube
 */
void project_cube(Cube *cube)
{
    for (int i = 0; i < 8; i++)
        project_point3d(&(cube->rotated_points[i]), &(cube->projected_points[i]));
}

/**
 * Compute the normal vector for each cube's face, this function should be
 * called after rotate the cube
 * @param cube a cube
 */
void compute_cube_normals(Cube *cube)
{
    for (int i = 0; i < 12; i++)
    {
        Point3 a;
        a.x = cube->triangles3d[i].v1->x - cube->triangles3d[i].v0->x;
        a.y = cube->triangles3d[i].v1->y - cube->triangles3d[i].v0->y;
        a.z = (cube->triangles3d[i].v1->z + 2.4f) - (cube->triangles3d[i].v0->x + 2.4f);
        Point3 b;
        b.x = cube->triangles3d[i].v2->x - cube->triangles3d[i].v0->x;
        b.y = cube->triangles3d[i].v2->y - cube->triangles3d[i].v0->y;
        b.z = (cube->triangles3d[i].v2->z + 2.4f) - (cube->triangles3d[i].v0->x + 2.4f);
        Point3 n;
        cross_product(&a, &b, &n);
        normalize_vector3d(&n);
        cube->normals[i] = n;
    }
}
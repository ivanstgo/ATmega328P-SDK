/**
 * @file graphics3d.h
 * @author Iván Santiago
 * @date 07-01-2023 17:54
 * @brief Library for drawing 3d graphic primitives on OLED display SSD1306
*/
#ifndef _GRAPHICS3D_H_
#define _GRAPHICS3D_H_
typedef struct point
{
    int x;
    int y;
} Point;

typedef struct point3
{
    float x;
    float y;
    float z;
} Point3;

typedef struct triangle
{
    Point *v0;
    Point *v1;
    Point *v2;
} Triangle;

typedef struct triangle3d
{
    Point3 *v0;
    Point3 *v1;
    Point3 *v2;
} Triangle3d;

typedef struct cube
{
    Point3 points[8];
    Point3 rotated_points[8];
    Point projected_points[8];
    Triangle triangles[12];
    Triangle3d triangles3d[12];
    Point3 normals[12];
} Cube;

/**
 * Configures the perspective matrix
 * @param angle angle of vision
 * @param z_far far z
 * @param z_near near z
 */
void set_perspective_matrix(float angle, float z_far, float z_near);
/**
 * @param input input vector
 * @param output transformed vector
 * @param matrix 4x4 transformation matrix
 */
void transform_vector3d(Point3 *input, Point3 *output, float matrix[4][4]);
/**
 * Sets the angle of rotation around x, y and z axis
 * @param alpha rotation around x
 * @param beta rotation around y
 * @param gamma rotation around z
 */
void set_rotation_matrix(float alpha, float beta, float gamma);
/**
 * Computes the cross product between two vectors and normalize it
 * @param a first vector
 * @param b second vector
 * @param c output vector
 */
void cross_product(Point3 *a, Point3 *b, Point3 *output);
/**
 * Computes the dot product between two vectors
 * @param a first vector
 * @param b second vector
 * @return the scalar product of a and b
 */
float dot_product(Point3 *a, Point3 *b);
/**
 * Projects a R3 vector into R2 space
 * @param input the 3d point
 * @param output the 2d point
 */
void project_point3d(Point3 *input, Point *output);
/**
 * Apply rotation transformation to a 3d point
 * @param input input 3d point
 * @param output rotated 3d point
 */
void rotate_point3d(Point3 *input, Point3 *output);
/**
 * Creates a cube
 * @param cube pointer to a cube struct
 */
void init_cube(Cube *cube);
/**
 * Rotates a cube
 * @param cube pointer to a cube
 */
void rotate_cube(Cube *cube);
/**
 * Applies perspective projection to a cube
 * @param cube point to a cube
 */
void project_cube(Cube *cube);
/**
 * Compute the normal vector for each cube's face, this function should be
 * called after rotate the cube
 * @param cube a cube
 */
void compute_cube_normals(Cube *cube);
/**
 * Normalize a vector
 * @param a vector to normalize
 */
void normalize_vector3d(Point3 *a);
#endif
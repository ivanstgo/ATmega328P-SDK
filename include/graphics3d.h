#ifndef GRAPHICS3D_H
#define GRAPHICS3D_H
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

void set_perspective_matrix(float angle, float z_far, float z_near);
void transform_vector3d(Point3 *input, Point3 *output, float matrix[4][4]);
void set_rotation_matrix(float alpha, float beta, float gamma);
void cross_product(Point3 *a, Point3 *b, Point3 *output);
float dot_product(Point3 *a, Point3 *b);
void project_point3d(Point3 *input, Point *output);
void rotate_point3d(Point3 *input, Point3 *output);
void init_cube(Cube *cube);
void rotate_cube(Cube *cube);
void project_cube(Cube *cube);
void compute_cube_normals(Cube *cube);
#endif
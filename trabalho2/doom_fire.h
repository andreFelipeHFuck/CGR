#include <GL/glut.h>
#include <math.h>
#include <unistd.h>

#define ESCAPE 27
#define NUM_PARTICLES 150000
#define GRAVITY 0.0003

struct color {
  float r, g, b;
}Color;

struct s_pf {
  float x, y,veloc_x, veloc_y;
  unsigned lifetime;
  int lifetime_Y1, lifetime_Y2, lifetime_R1, lifetime_R2;
  struct color color;
} particles[NUM_PARTICLES];

struct s_pf step_particles[NUM_PARTICLES];



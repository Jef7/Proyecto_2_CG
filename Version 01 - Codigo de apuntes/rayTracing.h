#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#define Hres 1024
#define Vres 1024

typedef struct {
  float Xmax;
  float Ymax;
  float Zmax;
  float Xmin;
  float Ymin;
  float Zmin;
} PANTALLA;

typedef struct {
  double r;
  double g;
  double b;
} COLOR;


typedef struct {
  double Xw;
  double Yw;
  double Zw;
} PUNTO3D;

typedef struct {
  double X;
  double Y;
  double Z;
} VECTOR;

typedef struct {
	
} INTERSECCION;
#define Hres 200
#define Vres 200

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
  long double Xw;
  long double Yw;
  long double Zw;
} PUNTO3D;

typedef struct {
  long double X;
  long double Y;
  long double Z;
} VECTOR;

typedef struct {
	struct OBJETO *objeto;
  long double tmin;
}INTERSECCION;


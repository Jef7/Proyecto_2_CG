struct OBJETO {
	char* tipo;
  	COLOR color;
  	void *p;
  	struct OBJETO *sig;
};

struct ESFERA{
  PUNTO3D centro;
  float radio;
};
struct OBJETO {
	char* tipo;
  	COLOR color;
  	void *p;
  	struct OBJETO *sig;
	// intersecciones 	// retorna intersecciones positiva mas pequena
	// normal		//retorna Vector normal	 
};

struct ESFERA{
  PUNTO3D centro;
  float radio;
};
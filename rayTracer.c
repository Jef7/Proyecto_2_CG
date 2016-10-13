#include "rayTracer.h"
#include "objetos.h"
#include <math.h>
#include <malloc.h>

COLOR **framebuffer;
COLOR color;
COLOR BACKGROUND;
PUNTO3D punto3D;
VECTOR vDir;
PANTALLA P;
VECTOR ojo;
struct OBJETO *objetos;

COLOR De_que_color();
INTERSECCION * First_Intersection();
long double ProductoPunto();


COLOR De_que_color(VECTOR ojo, VECTOR vDir){
	COLOR color;
	INTERSECCION * interseccion;

	interseccion = First_Intersection(ojo, vDir);
	if(!interseccion){
		color = BACKGROUND;
	}else{
		/*
		Q = interseccion -> objeto;
		N = normal unitaria a Q en punto (Xi,Yi,Zi);
		I = 0.0;
		for(k = 0; k < N_lights; k++){
			L = vector unitario hacia la luz;
			if(ProductoPunto(N,L) > 0.0){
				Fatt = factor de atenuación;
				I = I + (ProductoPunto(N,L) * Q.Kd * Fatt * Light[k].Ip);
			}
		}
		I = I + Ia * Q.Ka;
		I = min(1.0, I);
		color = I * Q.color;
		*/
	}
	
	return color;
}

INTERSECCION *First_Intersection(){
	INTERSECCION * interseccion;
	long double tmin;

	interseccion = NULL;
	/*
	tmin = masinfinito;
	para todo objeto en la escena
	{
		calcular intersección entre rayo y objeto;
		si hay intersecciones y la distancia al objeto < tmin
		{
			tmin = distancia a interseccion;
			interseccion = interseccion con objeto;
		}
	}
	*/
	return interseccion;
}

long double ProductoPunto(VECTOR a, VECTOR b){
	return a.X * b.X + a.Y * b.Y + a.Z * b.Z; 
}


int longitudObjetos(struct OBJETO *objetos){
	struct OBJETO *o;
	int n;
	n = 0;
	o = objetos;
	while(o != NULL){
		n++;
		o = o-> sig;
	}
	return n;
}


struct OBJETO *creanodo(void) {
  return (struct OBJETO *) malloc(sizeof(struct OBJETO));
}

struct OBJETO *insertafinal(struct OBJETO *lista, struct OBJETO *q) {
  	struct OBJETO *p;
  	q->sig = NULL;
  	if (lista == NULL){
    	return q;
  	}
  	/* la OBJETO argumento no es vacía. Situarse en el último */
	else{
	  	p = lista;
	  	//if(p->sig == NULL){printf("es nulo\n");}else{printf("no es nulo\n");}
	  	while (p->sig != NULL){
	    	p = p->sig;
	  	}
	  	p->sig = q;
	  	return lista;
	}
}

//método para iniciar objetos de prueba
void iniciarOjectosP(){
	struct OBJETO *ptr1, *ptr2, *ptr3;
	struct ESFERA *e1, *e2, *e3;

	e1 = (struct ESFERA*) malloc(sizeof(struct ESFERA));
	e2 = (struct ESFERA*) malloc(sizeof(struct ESFERA));
	e3 = (struct ESFERA*) malloc(sizeof(struct ESFERA));

  	ptr1 = creanodo();
  	ptr1->color.r = 1.0;
  	ptr1->color.g = 0.0;
  	ptr1->color.b = 0.0;
  	e1->centro.Xw = 4.0;
  	e1->centro.Yw = 0.0;
  	e1->centro.Zw = 4.0;
  	e1->radio = 6.0;
 		
  	ptr1->p = e1;

  	objetos = insertafinal(objetos, ptr1);
  	
  	ptr2 = creanodo();
  	ptr2->color.r = 0.0;
  	ptr2->color.g = 1.0;
  	ptr2->color.b = 0.0;
  	e2->centro.Xw = 4.0;
  	e2->centro.Yw = 0.0;
  	e2->centro.Zw = 4.0;
  	e2->radio = 10.0;
 		
  	ptr2->p = e2;

  	objetos = insertafinal(objetos, ptr2);

  	ptr3 = creanodo();
  	ptr3->color.r = 0.0;
  	ptr3->color.g = 0.0;
  	ptr3->color.b = 1.0;
  	e3->centro.Xw = 4.0;
  	e3->centro.Yw = 0.0;
  	e3->centro.Zw = 4.0;
  	e3->radio = 3.0;
 		
  	ptr3->p = e3;

  	objetos = insertafinal(objetos, ptr3);
  	
}

int main(int argc, char** argv)
{
	int i, j;
	long double Xw, Yw, Zw, L, Xd ,Yd ,Zd;
	objetos = NULL;

	//datos de prueba
	P.Xmax = 10.0;
	P.Ymax = 10.0;
	P.Zmax = 0.0;
	P.Xmin = 0.0;
	P.Ymin = 0.0;
	P.Zmin = 0.0;

	ojo.X = 0.0;
	ojo.Y = 0.0;
	ojo.Z = -50.0;

	BACKGROUND.r = 0.11412;
	BACKGROUND.g = 0.71322;
	BACKGROUND.b = 0.83514;

	framebuffer = (COLOR **)malloc(Hres * sizeof(COLOR*));
	for (i = 0; i < Hres; i++) 
	{
	 framebuffer[i] = (COLOR *)malloc(Vres * sizeof(COLOR));
	}

	for (i = 0; i < Hres; i++) 
	{
	 for (j = 0; j < Vres; j++) 
	    {
	    	framebuffer[i][j].r = 0;
	        framebuffer[i][j].g = 0;
	        framebuffer[i][j].b = 0;
	    }
	}

	iniciarOjectosP();

	for(i = 0; i < Hres; i++){
		for(j = 0; j < Vres; j++){
			Xw = ((i + 1/2)*(P.Xmax - P.Xmin) / Hres) + P.Xmin;
			Yw = ((j + 1/2)*(P.Ymax - P.Ymin) / Vres) + P.Ymin;
			Zw = 0.0;
			//printf("Xw = %Lf\n", Xw);
			//printf("Yw = %Lf\n", Yw);
			
			L = sqrt(pow((punto3D.Xw - ojo.X), 2)+pow((punto3D.Yw - ojo.Y), 2)+pow((punto3D.Zw - ojo.Z), 2));
			vDir.X = (punto3D.Xw - ojo.X) / L;
			vDir.Y = (punto3D.Yw - ojo.Y) / L;
			vDir.Z = (punto3D.Zw - ojo.Z) / L;


			color = De_que_color(ojo,vDir);

			framebuffer[i][j] = color;
		}
	}
	//SaveImage(framebuffer);


	//PRUEBA de que si se insertan bn los valores
	struct OBJETO *ptr, *ptr2, *ptr3;
	ptr = objetos->sig;
	ptr2 = ptr->sig;
	ptr3 = ptr2->sig;

	printf("radio 1 = %f\n", ((struct ESFERA *)objetos->p)->radio);
	printf("radio 2 = %f\n", ((struct ESFERA *)ptr->p)->radio);
	printf("radio 3 = %f\n", ((struct ESFERA *)ptr2->p)->radio);
	//SaveImage(framebuffer);

	

}
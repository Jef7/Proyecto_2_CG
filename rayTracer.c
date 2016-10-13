#include "rayTracer.h"
#include "objetos.h"
#include <math.h>
#include <malloc.h>

#ifndef min
	#define min( a, b ) ( ((a) < (b)) ? (a) : (b) )
#endif

COLOR **framebuffer;
COLOR color;
COLOR BACKGROUND;
PUNTO3D punto3D;
VECTOR vDir;
PANTALLA P;
VECTOR ojo;
struct OBJETO *objetos;

COLOR De_que_color();
INTERSECCION First_Intersection();
long double ProductoPunto();


COLOR De_que_color(VECTOR ojo, VECTOR vDir){
	COLOR color;
	INTERSECCION interseccion;

	interseccion = First_Intersection(ojo, vDir);
	if(!interseccion.objeto){
		//printf("soy nulo :v\n");
		color = BACKGROUND;
	}else{

  		//printf("t = %Lf\n", interseccion.tmin);
		color = interseccion.objeto->color;
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
	else{
	  	p = lista;
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
  	e1->radio = 3.0;
 		
  	ptr1->p = e1;

  	objetos = insertafinal(objetos, ptr1);
  	
  	ptr2 = creanodo();
  	ptr2->color.r = 0.0;
  	ptr2->color.g = 1.0;
  	ptr2->color.b = 0.0;
  	e2->centro.Xw = 3.0;
  	e2->centro.Yw = 19.0;
  	e2->centro.Zw = 1.5;
  	e2->radio = 10.0;
 		
  	ptr2->p = e2;

  	objetos = insertafinal(objetos, ptr2);

  	ptr3 = creanodo();
  	ptr3->color.r = 0.0;
  	ptr3->color.g = 0.0;
  	ptr3->color.b = 1.0;
  	e3->centro.Xw = 14.915;
  	e3->centro.Yw = 20.1662;
  	e3->centro.Zw = 4.0;
  	e3->radio = 3.0;
 		
  	ptr3->p = e3;

  	objetos = insertafinal(objetos, ptr3);
  	
}

long double calcularDiscriminante(float a, float b, float c){
	return (pow(b,2) - 4*c);
}

long double interseccionEsfera(struct ESFERA *e){
	long double b,c,dis,t,t1,t2;
	b = 2*(vDir.X * (ojo.X - e->centro.Xw) + vDir.Y * (ojo.Y - e->centro.Yw) + vDir.Z * (ojo.Z - e->centro.Zw));
	c = pow((ojo.X - e->centro.Xw), 2) + pow((ojo.Y - e->centro.Yw), 2) + pow((ojo.Z - e->centro.Zw), 2) - pow((e->radio), 2);
	//printf("b = %Lf\n", b);
	//printf("c = %Lf\n", c);

	dis = calcularDiscriminante(1,b,c);
	//printf("dis = %Lf\n", dis);

	if(dis < 0){
		t = -1;
		//printf("discriminante negativo PUTO!!\n");
	}else{
		t1 = (-b + sqrt(dis))/2;
		t2 = (-b - sqrt(dis))/2;
		if(t1<0 && t2>0)
			t = t2;
		else if(t1>0 && t2<0)
			t = t1;
		else if(t1<0 && t2<0)
			t = -1;
		else{
			t = min(t1, t2);
		}
	}
	return t;
}
/*
β = 2(X D (X E – X C ) + Y D (Y E – Y C ) + Z D (Z E – Z C ))
γ = (X E - X C ) 2 + (Y E - Y C ) 2 + (Z E - Z C ) 2 – R 2
*/


INTERSECCION First_Intersection(){
	struct OBJETO *p;
	//p = creanodo();
	INTERSECCION interseccion;
	long double tmin, t;
	int i;

	interseccion.objeto = NULL;
	tmin = 99999.0;
	p = objetos;
	i = 1;

  	while(i <= longitudObjetos(objetos)){
  		t = interseccionEsfera(p->p);
  		if(t < tmin && t > 0){
  			interseccion.objeto = p;
  			tmin = t;
  		}
		
  		p = p->sig;
  		i++;
  	}
  	interseccion.tmin = tmin;
	/*para todo objeto en la escena
	{
		calcular intersección entre rayo y objeto;
		si hay intersecciones y la distancia al objeto < tmin
		{
			tmin = distancia a interseccion;
			interseccion = interseccion con objeto;
		}
	}g
	*/
	return interseccion;
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
	//for(i = 400; i <500; i++){
	//	for(j =499; j <500; j++){
			punto3D.Xw = ((i + 1/2)*(P.Xmax - P.Xmin) / Hres) + P.Xmin;
			punto3D.Yw = ((j + 1/2)*(P.Ymax - P.Ymin) / Vres) + P.Ymin;
			punto3D.Zw = 0.0;
			//printf("Xw = %Lf\n", Xw);
			//printf("Yw = %Lf\n", Yw);
			
			L = sqrt(pow((punto3D.Xw - ojo.X), 2)+pow((punto3D.Yw - ojo.Y), 2)+pow((punto3D.Zw - ojo.Z), 2));
			vDir.X = (punto3D.Xw - ojo.X) / L;
			vDir.Y = (punto3D.Yw - ojo.Y) / L;
			vDir.Z = (punto3D.Zw - ojo.Z) / L;

			color = De_que_color(ojo,vDir);

			framebuffer[i][j] = color;
			//framebuffer[500][500] = color;
			/*
			printf("i = %d \n j = %d \n", i, j);
			printf("L = %Lf \n", L);
			printf("punto3D.Xw = %Lf\n punto3D.Yw = %Lf\n punto3D.Zw = %Lf\n ", punto3D.Xw, punto3D.Yw, punto3D.Zw);
			printf("vDir.X = %Lf\n vDir.Y = %Lf\n vDir.Z = %Lf\n ", vDir.X, vDir.Y, vDir.Z);
			printf("----------------------\n");*/
		}
	}

	for(i = 0; i < Hres; i++){
		for(j = 0; j < Vres; j++){
			printf("framebuffer[%d][%d].r = %f;\n", i,j,framebuffer[i][j].r);
			printf("framebuffer[%d][%d].g = %f;\n", i,j,framebuffer[i][j].g);
			printf("framebuffer[%d][%d].b = %f;\n", i,j,framebuffer[i][j].b);
		}
	}	
	//SaveImage(framebuffer);

	//PRUEBA PUTOOOOOOO!!! 
/*	ojo.X = -19.84155;
	ojo.Y = 6.5;
	ojo.Z = -3.23439;
	//Radio = 6 y centro = (4.0, 0.0, 4.0)
	vDir.X = 0.982602;
	vDir.Y = -0.147390;
	vDir.Z = 0.112999;
*/
	/*
	struct OBJETO *p;
	p = objetos;
  	while (p->sig != NULL){
  		printf("%f\n", interseccionEsfera(p->p));
    	p = p->sig;
  	}
  	printf("%f\n", interseccionEsfera(p->p));*/


	//PRUEBA de que si se insertan bn los valores
	/*struct OBJETO *ptr, *ptr2, *ptr3;
	ptr = objetos->sig;
	ptr2 = ptr->sig;
	ptr3 = ptr2->sig;

	printf("radio 1 = %f\n", ((struct ESFERA *)objetos->p)->radio);
	printf("radio 2 = %f\n", ((struct ESFERA *)ptr->p)->radio);
	printf("radio 3 = %f\n", ((struct ESFERA *)ptr2->p)->radio);*/
	//SaveImage(framebuffer);

	

}
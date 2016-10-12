#include <stdio.h>

void miPrint(){
	printf("hola mundo\n");
}

int main(int argc, char const *argv[])
{
	//print();

	/*puntero a función 
	1- tipo que retorne
		void

	2- entre parentesis * y nombre del puntero
		(*miFuncion)

	3- otro parentesis con los parametros de la función, 
	si no tiene, ponemos void
		(void);

	4- quedamos con 
		void(*miFuncion)(void)

	5- así definimos un puntero nulo, con paramentros nulos
	llamado "miFuncion"

	6- Podemos darle valores, que son funciones con el mismo
	tipo, en este caso puedo darle mi función "miPrint" que 
	también es voy 
		miFuncion = &miPrint;

	7- ahora puedo llamar al puntero con la lista de parametros
	que en este caso sería nula
		miFuncion();
	*/

	void(*miFuncion)(void);
	miFuncion = &miPrint;
	miFuncion();

	return 0;
}
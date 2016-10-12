///////////////////////////////////////////////////
//                                              //
//      Instalacion                             //
//                                              //
//////////////////////////////////////////////////
/*
 1. Actualizar la vara
  sudo apt-get update

 2. Biblioteca necesaria
  sudo apt-get install libltdl-dev

 2. Bajar version 6 de Image-Magick
 wget  http://www.imagemagick.org/download/ImageMagick-6.9.6-2.tar.gz

	Si no sirve ese link buscar la ultima vesion 6 en tar.gz en http://www.imagemagick.org/download/

 3.
 tar xvzf ImageMagick.tar.gz

 4.
 cd ImageMagick-7.0.3

 5.
 ./configure  --with-modules


 6.
 make

 7.
 sudo make install

 8. Configurar la vara, si esto no sirve
 sudo ldconfig /usr/local/lib

Referencias:
http://www.imagemagick.org/script/install-source.php#unix
http://www.imagemagick.org/download/

///////////////////////////////////////////////////
//                                              //
//      Uso	                             	//
//                                              //
//////////////////////////////////////////////////	

 Para compilar:

 gcc -o programa programa.c -lm `pkg-config --cflags --libs MagickCore`


 Referencia en el codigo:
 generate_image("imagen.jpg", framebuffer, Hres, Vres);




*/
///////////////////////////////////////////////


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <magick/MagickCore.h>


///////////////////////////////////////////////////
//                                              //
//      Api                                     //
//                                              //
//////////////////////////////////////////////////

//Wraper sipmlificado Genera la imagen <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Usar Esta!!!!
int generate_image(char* output_image_name, COLOR **framebuffer, int h_res, int v_res);
// Ejemplo:  generate_image("imagen.jpg", framebuffer, Hres, Vres);
// Donde: "imagen.jpg" es el nombre de la imagen a ser generada


// Generar imagen
//Recive: nombre de archivo con pixeles, nombre de imagen que se va a generar

int file_to_image( char* input_file_name,  char* output_image_name);

// Generar imagen y resize
//Recive: nombre de archivo con pixeles, nombre de imagen que se va a generar, size x, sieze y
int file_to_image_resize(char* input_file_name, char* output_image_name, int sieze_x, int sieze_y);

//Convierte el framebuffer a archivo para generar imagen
int framebuffer_to_file(char* file_name, COLOR **framebuffer, int h_res, int v_res);


///////////////////////////////////////////////////
//                                              //
//      Funciones                               //
//                                              //
//////////////////////////////////////////////////

int generate_image(char* output_image_name, COLOR **framebuffer, int h_res, int v_res)
{
  framebuffer_to_file("temp.txt", framebuffer, h_res, v_res);

  file_to_image( "temp.txt", output_image_name );

  remove("temp.txt");
}

int framebuffer_to_file(char* file_name, COLOR **framebuffer, int h_res, int v_res)
{
	FILE *fp;

  fp = fopen(file_name, "w+");
  //Header
  fprintf(fp, "# ImageMagick pixel enumeration: %d,%d,1,rgb\n", h_res, v_res); // # ImageMagick pixel enumeration: 2,2,1,rgb
	int i, j;
	for (i = 0; i < h_res; i++)
 	{
 		for (j = 0; j < v_res; j++)
 	  {
			fprintf(fp, "%d,%d: (%f,%f,%f)  \n", i, j, framebuffer[i][j].r,framebuffer[i][j].g, framebuffer[i][j].b ); //0,0: (1.0,0.0,0.0)
 	  }
	}
  fclose(fp);
}



int file_to_image( char* input_file_name,  char* output_image_name)
{
  return file_to_image_resize(input_file_name, output_image_name, 0, 0);
}



int file_to_image_resize(char* input_file_name, char* output_image_name, int sieze_x, int sieze_y)
{
  char* file_name_input = input_file_name;
  char* file_name_output = output_image_name;

  int resize_x = sieze_x;
  int resize_y = sieze_y;

  ExceptionInfo *exception;
  Image *image, *images, *resize_image, *image_output;
  ImageInfo *image_info;


  //if (argc != 3)
  // {
  //     (void) fprintf(stdout,"Usage: %s image thumbnail\n",argv[0]);
  //     exit(0);
  // }

  //Initialize the image info structure and read an image.
  MagickCoreGenesis(NULL,MagickTrue);
  exception=AcquireExceptionInfo();


  image_info=CloneImageInfo((ImageInfo *) NULL);

  (void) strcpy(image_info->filename,file_name_input);

  images=ReadImage(image_info,exception);
  if (exception->severity != UndefinedException)
    CatchException(exception);
  if (images == (Image *) NULL)
    exit(1);


  /*
    Convert the image to a thumbnail.
  */
  image_output = NewImageList();
  while ((image=RemoveFirstImageFromList(&images)) != (Image *) NULL)
  {
    if(resize_x>0 && resize_y>0 )
    {
      resize_image=ResizeImage(image, resize_x, resize_y,LanczosFilter,1.0,exception);
      if (resize_image == (Image *) NULL)
        MagickError(exception->severity,exception->reason,exception->description);
        image = resize_image;
    }
    (void) AppendImageToList(&image_output,image);
    //DestroyImage(image);
  }
  /*
    Write the image thumbnail.
  */

  (void) strcpy(image_output->filename,file_name_output);
  WriteImage(image_info,image_output);
  /*
    Destroy the image thumbnail and exit.
  */
  image_output=DestroyImageList(image_output);
  image_info=DestroyImageInfo(image_info);
  exception=DestroyExceptionInfo(exception);
  MagickCoreTerminus();
  return(0);
}

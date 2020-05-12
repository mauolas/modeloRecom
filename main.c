#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include<unistd.h>

float productoPunto(float vector1[4],float vector2[4]);
void imprimirVector(float vector1[][6]);
void motorUsu(float usuarios[][6],float peliculas[][6],float error,int usu,int peli);
float sigma(float prodPunto);
void imprimeMatrizes(float usuarios[][6],float peliculas[][6], int matriz[][15]);
void sugerAmigo(float usuarios[][6],int id,float recom[2]);
float productoPunto2(float vector1[][6],float vector2[][6],int id,int recorre);
void peliculaSimilar(float peliculas[][6],int id,float recom2[2]);
void sugerirPeliAUsuario(float peliculas[][6], float usuarios[][6], int id,float recom3[2]);

int main(int argc, char const *argv[])
{
  //Creacion de matrizes
  float usuarios[30][6];
  float peliculas[15][6];
  float recom[2]={0,0};
  float recom2[2]={0,0}, id;
  float recom3[2]={0,0};
  float resultado=0;
  float error=0;
  int cont=0, cont1=0, h, m, opcion;
  FILE *fp, *fpMat;
  fp= fopen("usu.txt", "rt");
  //1.-Fantasia 2.-Romance 3.-Terror 4.-Comedia 5.-Suspenso
  //Llenar solo ids de los usuarios hacia abajo.
  /*for (int i = 0; i < 30; i++)
  {
    usuarios[i][0]=i;
    if (i<15)
    {
      peliculas[i][0]=i;
    }
  }*/
  while(fscanf(fp, "%f,", &id)==1)
  {
    usuarios[cont][0]= id;
    if (cont<15)
    {
        peliculas[cont][0]= id;
    }
    cont+=1;
  }
  fclose(fp);
  for (h=0;h<30;h++)
  {
    for (m=1;m<6;m++)
    {
        usuarios[h][m]= 0;
        if(h<15)
        {
            peliculas[h][m]= 0;
        }
    }
  }

  //Llenar valores random de 0 a 1
  for (int i = 0; i < 30; i++)
  {
    for (int x = 1; x < 6; x++)
    {
      usuarios[i][x]=(rand() % 11)*0.1;
      if (i<15)
      {
        peliculas[i][x]=(rand() % 11)*0.1;
      }
    }
  }

  // Esta es la matriiiiizzzzzzzz
  fpMat= fopen("GranMat.txt","rt");
  int matriz[30][15];
  while(fscanf(fpMat, "%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,\n", &matriz[cont1][0],&matriz[cont1][1],&matriz[cont1][2],&matriz[cont1][3],&matriz[cont1][4],&matriz[cont1][5],&matriz[cont1][6],&matriz[cont1][7],&matriz[cont1][8],&matriz[cont1][9],&matriz[cont1][10],&matriz[cont1][11],&matriz[cont1][12],&matriz[cont1][13],&matriz[cont1][14])==15)
    {
        if(cont1<30)
        {
            cont1= cont1+1;
        }
    }
    fclose(fpMat);
  //for (int ii = 0; ii < 30; ii++) {
    //for (int xx = 0; xx < 15; xx++) {
      //matriz[ii][xx]=(rand() % 11);
    //}
  //}
  do
  {
    printf("\n\n\n\t\t\t*Menù*\n");
    printf("\t\t\t1. Entrenar.\n");
    printf("\t\t\t2. Sugerir amigo similar.\n");
    printf("\t\t\t3. Sugerir pelìcula similar.\n");
    printf("\t\t\t4. Sugerir pelìcula a un usuario.\n");
    printf("\t\t\t5. Imprimir matrices.\n");
    printf("\t\t\t6. Salir.\n");
    printf("\n\t\tIngresa la opción que deseas: ");
    scanf("%i", &opcion);
    getchar();

    switch(opcion)
    {
      case 1:
        system("clear");
        ////////////Funcion de motor de aprendizaje
        printf(" Usuario antes:\n");
        imprimirVector(usuarios);
        printf(" Pelicula antes:\n");
        imprimirVector(peliculas);
        printf("\n");

        for (int qwer= 0; qwer < 30; qwer++)
        {
          for (int zxcv = 0; zxcv < 15; zxcv++)
          {
            if (matriz[qwer][zxcv]!=0)
            {
              resultado=productoPunto2(usuarios,peliculas,qwer,zxcv);
              error=(matriz[qwer][zxcv]-resultado);
              motorUsu(usuarios,peliculas,error,qwer,zxcv);
            }
          }
        }

        printf(" Usuario Despues: \n");
        imprimirVector(usuarios);
        printf(" Pelicula despues: \n");
        imprimirVector(peliculas);
        printf("\n");
        printf("\n\nPresiona enter para continuar...");
        getchar();
        /////////////////////////////////////////////
        break;
      case 2:
        system("clear");
        ///////////////Sugerir amigo similar
        int op=0;
        printf("A que usuario le deseas sugerir un amigo? \n");
        scanf("%d", &op);
        sugerAmigo(usuarios,op,recom);
        printf("Al usuario %f con estos features: Fantasia:%f, Romance:%f, Terror:%f, Comedia:%f, Suspenso:%f \n",usuarios[op][0],usuarios[op][1],usuarios[op][2],usuarios[op][3],usuarios[op][4],usuarios[op][5]);
        printf("Se le recomeinda el usuario: ");
        int op2=recom[1];
        printf("Id:%f, Fantasia:%f, Romance:%f, Terror:%f, Comedia:%f, Suspenso:%f \n",usuarios[op2][0],usuarios[op2][1],usuarios[op2][2],usuarios[op2][3],usuarios[op2][4],usuarios[op2][5]);
        printf("Con un producto punto de :%f \n", recom[0]);
        printf("\n\nPresiona enter para continuar...");
        getchar();
        /////////////////////////////////////////////
        break;
      case 3:
        system("clear");
        ///////////Sugerir pelicula similar
        int op3=0;
        printf("A que pelicula le quieres encontrar una similar\n");
        scanf("%d", &op3);
        peliculaSimilar(usuarios,op3,recom2);
        printf("La pelicula %f con estos features: Fantasia:%f, Romance:%f, Terror:%f, Comedia:%f, Suspenso:%f \n",peliculas[op3][0],peliculas[op3][1],peliculas[op3][2],peliculas[op3][3],peliculas[op3][4],peliculas[op3][5]);
        printf("Se parece a: ");
        int op4=recom2[1];
        printf("Id:%f, Fantasia:%f, Romance:%f, Terror:%f, Comedia:%f, Suspenso:%f \n",peliculas[op4][0],peliculas[op4][1],peliculas[op4][2],peliculas[op4][3],peliculas[op4][4],peliculas[op4][5]);
        printf("Con un producto punto de :%f ", recom2[0]);
        printf("\n\nPresiona enter para continuar...");
        getchar();
        /////////////////////////////////////////////
        break;
      case 4:
        system("clear");
        int op9=0;
        printf("A que usuario le quieres recomendar una pelicula\n");
        scanf("%d", &op9);
        sugerirPeliAUsuario(peliculas,usuarios,op9,recom3);
        int op10=recom3[1];
        printf("Al usuario %f con estos features: Fantasia:%f, Romance:%f, Terror:%f, Comedia:%f, Suspenso:%f \n",usuarios[op9][0],usuarios[op9][1],usuarios[op9][2],usuarios[op9][3],usuarios[op9][4],usuarios[op9][5]);
        printf("Se le recomeinda la pelicula:  ");
        printf("Id:%f, Fantasia:%f, Romance:%f, Terror:%f, Comedia:%f, Suspenso:%f \n",peliculas[op10][0],peliculas[op10][1],peliculas[op10][2],peliculas[op10][3],peliculas[op10][4],peliculas[op10][5]);
        printf("Con un producto punto de :%f ", recom3[0]);
        printf("\n\nPresiona enter para continuar...");
        getchar();
        break;
      case 5:
        system("clear");
        imprimeMatrizes(usuarios,peliculas,matriz);
        printf("\n\nPresiona enter para continuar...");
        getchar();
        break;
      case 6:
        system("clear");
        printf("\n\n\n\t\t\tGracias por usar el programa.");
        printf("\n\t\t\tSaliendo del programa...\n");
        sleep(3);
        system("clear");
        break;
      default:
        printf("\n");
        system("clear");
        printf("\n\n\n\t\t\tIngresa una opciòn válida.\n");
        printf("\n\t\t\tPresiona enter para continuar...");
        getchar();
        break;
    }
  }while(opcion!=6);

  return 0;

}

float productoPunto(float vector1[4],float vector2[4])
{
  int resultado=0;

  for (int i=0;i < 5; i++)
  {
    resultado=resultado+(vector1[i]*vector2[i]);
  }

  return resultado;
}

float productoPunto2(float vector1[][6],float vector2[][6],int id,int recorre)
{
  float resultado=0;
  for (int i=1;i < 6; i++)
  {
    resultado=resultado+(vector1[id][i]*vector2[recorre][i]);
  }

  return resultado;
}


void motorUsu(float usuarios[][6],float peliculas[][6],float error,int usu,int peli)
{

  float resig = sigma(error);

  for (int i = 1; i < 6; i++)
  {
    usuarios[usu][i]=usuarios[usu][i]+(0.01*(1-resig)*resig*peliculas[peli][i]);
    peliculas[peli][i]=peliculas[peli][i]+(0.01*(1-resig)*resig*usuarios[usu][i]);
  }

}

void imprimirVector(float vector1[][6])
{
  for (int i=0; i<6; i++)
  {
    printf("%f,", vector1[4][i]);
  }
}

float sigma(float prodPunto)
{
  float resultado=(1/(1+exp(prodPunto*-1)));

  return resultado;

}

void imprimeMatrizes(float usuarios[][6],float peliculas[][6],int matriz[][15])
{
  //1.-Fantasia 2.-Romance 3.-Terror 4.-Comedia 5.-Suspenso
  printf("Usuarios\n");
  for (int i = 0; i < 30; i++)
  {
      printf("Id:%f, Fantasia:%f, Romance:%f, Terror:%f, Comedia:%f, Suspenso:%f \n",usuarios[i][0],usuarios[i][1],usuarios[i][2],usuarios[i][3],usuarios[i][4],usuarios[i][5] );
  }
  printf("Peliculas \n");
  for (int i = 0; i < 15; i++)
  {
      printf("Id:%f, Fantasia:%f, Romance:%f, Terror:%f, Comedia:%f, Suspenso:%f \n",peliculas[i][0],peliculas[i][1],peliculas[i][2],peliculas[i][3],peliculas[i][4],peliculas[i][5] );
  }
  printf("Matriz de calificaciones\n");
  for (int i = 0; i < 30; i++)
  {
    for (int x = 0; x < 15; x++) {
      printf("%d,", matriz[i][x]);
    }
    printf("\n");

  }

}

void sugerAmigo(float usuarios[][6],int id,float recom[2])
{
  int x=0;
  float res=0;
  float puntofinal=0;
  int idfinal=0;
  while (usuarios[x][0]!=id)
  {
    x++;
  }

  for (int i = 0; i < 30; i++)
  {
    if (i != x)
    {
      res=productoPunto2(usuarios,usuarios,x,i);
      if (res>=puntofinal)
      {
        puntofinal=res;
        idfinal=i;
      }
    }
  }
  recom[0]=puntofinal;
  recom[1]=idfinal;

}

void peliculaSimilar(float peliculas[][6],int id,float recom2[2])
{
  int x=0;
  float res=0;
  float puntofinal=0;
  int idfinal=0;
  while (peliculas[x][0]!=id)
  {
    x++;
  }

  for (int i = 0; i < 15; i++)
  {
    if (i != x)
    {
      res=productoPunto2(peliculas,peliculas,x,i);
      if (res>=puntofinal)
      {
        puntofinal=res;
        idfinal=i;
      }
    }

  }
  recom2[0]=puntofinal;
  recom2[1]=idfinal;
}

void sugerirPeliAUsuario(float peliculas[][6], float usuarios[][6], int id,float recom3[2]){


  float res=0;
  float puntofinal=0;
  int idfinal=0;
  printf("%d\n",id );
  for (int i = 0; i < 15; i++)
  {
      res=productoPunto2(usuarios,peliculas,id,i);
      if (res>=puntofinal)
      {
        puntofinal=res;
        idfinal=i;
      }
  }
  recom3[0]=puntofinal;
  recom3[1]=idfinal;

}

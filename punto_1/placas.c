#include <stdio.h>
#include <stdlib.h>

/* Se definen las constantes del problema */
#define L 5.0
#define l 2.0
#define d 1.0
#define h 0.02
#define V_o 100.0

int matrix(int fila, int columna, int n_dis);

int main(){

  /* Se inicializan las variables y arreglos que se van a usar en el problema */
  /* N es el numero de iteraciones del metodo de relajacion */
  int N = (int)(2*L*L/(h*h));
  /* n_dis representa el numero de filas y de columnas de la matriz de discretizacion */
  int n_dis = (int)((L/h)+1);
  /* V es el arreglo que representa al potencial */
  double *V = malloc((n_dis*n_dis)*sizeof(double));
  /* V_temp es un arreglo temporal para cambiar entre iteraciones */
  double *V_temp = malloc((n_dis*n_dis)*sizeof(double));
  /* verif es un arreglo que funciona como un arreglo de booleanos, con el fin de decidir cuales casillas se evaluan y cuales no */
  int *verif = malloc((n_dis*n_dis)*sizeof(int));

  /* Ciclos que llenan la matriz inicial */
  /* i es una variable auxiliar para los ciclos */
  int i;
  /* 'for' que llena los arreglos con ceros */
  for(i=0; i<(n_dis*n_dis); i++){
    V[i] = 0.0;
    V_temp[i] = 0.0;
    verif[i] = 0;
  }
  /* 'for' que inicializa con 1 los bordes de la matriz */
  for(i=0; i<n_dis; i++){
    verif[matrix(0, i, n_dis)] = 1;
    verif[matrix(n_dis-1, i, n_dis)] = 1;
    verif[matrix(i, 0, n_dis)] = 1;
    verif[matrix(i, n_dis-1, n_dis)] = 1;
  }
  /* 'for' que inicializa con V/2 las placas */
  for(i=(int)(L-l)/(2*h); i<=(int)(((L-l)/(2*h))+(l/h)); i++){
    V[matrix((int)((L-d)/(2.0*h)), i, n_dis)] = V_o/2.0;
    V[matrix((int)(((L-d)/(2.0*h))+(d/h)), i, n_dis)] = -V_o/2.0;
    V_temp[matrix((int)((L-d)/(2.0*h)), i, n_dis)] = V_o/2.0;
    V_temp[matrix((int)(((L-d)/(2.0*h))+(d/h)), i, n_dis)] = -V_o/2.0;
    verif[matrix((int)((L-d)/(2.0*h)), i, n_dis)] = 1;
    verif[matrix((int)(((L-d)/(2.0*h))+(d/h)), i, n_dis)] = 1;
  }

  /* Ciclos que calculan el potencial */
  /* j y k son variables auxiliares para los ciclos */
  int j, k;
  for(i=0; i<N; i++){
    for(j=0; j<n_dis; j++){
      for(k=0; k<n_dis; k++){
	if(verif[matrix(j, k, n_dis)]==0){
	  V_temp[matrix(j, k, n_dis)] = (V[matrix(j, k-1, n_dis)]+V[matrix(j, k+1, n_dis)]+V[matrix(j-1, k, n_dis)]+V[matrix(j+1, k, n_dis)])/4;
	}
      }
    }
    for(j=0; j<(n_dis*n_dis); j++){
      V[j] = V_temp[j];
    }
  }

  double dVx, dVy;
  for(i=0; i<n_dis; i++){
    for(j=0; j<n_dis; j++){
      if(i==0){
	dVy = -(V[matrix(i+1, j, n_dis)]-V[matrix(i, j, n_dis)])/h;
      }
      else if(i==(n_dis-1)){
	dVy = -(V[matrix(i, j, n_dis)]-V[matrix(i-1, j, n_dis)])/h;
      }
      else{
	dVy = -(V[matrix(i+1, j, n_dis)]-V[matrix(i-1, j, n_dis)])/(2*h);
      }
      if(j==0){
	dVx = -(V[matrix(i, j+1, n_dis)]-V[matrix(i, j, n_dis)])/h;
      }
      else if(j==(n_dis-1)){
	dVx = -(V[matrix(i, j, n_dis)]-V[matrix(i, j-1, n_dis)])/h;
      }
      else{
	dVx = -(V[matrix(i, j+1, n_dis)]-V[matrix(i, j-1, n_dis)])/(2*h);
      }
      printf("%f %f %f\n", V[matrix(i, j, n_dis)], dVx, dVy);
    }
  }

  return 0;

}

int matrix(int fila, int columna, int n_dis){
  return (n_dis*fila)+columna;
}

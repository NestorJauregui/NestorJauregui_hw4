#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define T 40.0
#define rho 10.0
#define L 100.0
#define n_points 100
#define n_times 200

int main(){

  double c = pow(T/rho, 0.5);
  double per = 400.0;
  double *x = malloc(n_points*sizeof(double));
  double *u_initial = malloc(n_points*sizeof(double));
  double *u_past = malloc(n_points*sizeof(double));
  double *u_present = malloc(n_points*sizeof(double));
  double *u_future = malloc(n_points*sizeof(double));
  double dx = L/((double)(n_points)-1.0);
  double dt = per/((double)(n_times)-1.0);
  double r = dt/(dx*c);
  int i, j;
  for(i=0; i<n_points; i++){
    x[i] = (double)(i)*L/((double)(n_points)-1.0);
    u_past[i] = 0.0;
    u_present[i] = 0.0;
    u_future[i] = 0.0;
    if(x[i]<=80.0){
      u_initial[i] = 1.25*x[i]/L;
    }
    else{
      u_initial[i] = 5.0-(5.0*x[i]/L);
    }
  }
  u_initial[0] = 0.0;
  u_initial[n_points-1] = 0.0;
  for(i=0; i<n_points; i++){
    printf("%f\n", u_initial[i]);
  }
  for(i=1; i<(n_points-1); i++){
    u_future[i] = u_initial[i] + ((r*r/2.0)*(u_initial[i+1] - 2.0*u_initial[i] + u_initial[i-1]));
  }
  for(i=0; i<n_points; i++){
    u_past[i] = u_initial[i];
    u_present[i] = u_future[i];
    printf("%f\n", u_present[i]);
  }
  for(j=2; j<n_times; j++){
    for(i=1; i<(n_points-1); i++){
      u_future[i] = (2.0*(1.0-(r*r)))*u_present[i] - u_past[i] + (r*r)*(u_present[i+1] + u_present[i-1]);
    }
    for(i=0; i<n_points; i++){
      u_past[i] = u_present[i];
      u_present[i] = u_future[i];
      printf("%f\n", u_present[i]);
    }
  }

  return 0;

}

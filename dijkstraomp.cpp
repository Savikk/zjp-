/*
 * Labirynt #Dijkstra
 * @author: Paweł Sawicki
 * g++ dijkstra_s.cpp -o dijkstra -fopenmp -lrt
 * (moga byc drobne bledy)
 * licznik: on
 * openmpi
 */

#include <omp.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX 999999
#define INF 9999
using namespace std;
double timeDiff(struct timespec *timeA_p, struct timespec *timeB_p)
{
  double diff = (((timeA_p->tv_sec * 1000000000) + timeA_p->tv_nsec) -
    ((timeB_p->tv_sec * 1000000000) + timeB_p->tv_nsec));
  return diff / 1000000000;
}
FILE *we;
FILE *wy;
struct timespec s_input, e_input, start, end, s_steps, e_steps;
struct Node {
  int nw;
  int waga; // waga ( W labiryncie kazda waga wynosi 1)
  struct Node * nast;
};
  int ilosc,nr;
  int i,j,x,y,z,v0,vk,u,n,m; // x,y,z - pomocnicze
  int k[MAX],p[MAX]; // k - koszt, p - pomocnicze do obliczania kosztow
  bool Q[MAX]; // Q - sasiedztwo
  struct Node *sv[MAX],*pw; // sv - jakie wierzcholek ma sasiedztwo

int main(int argc,char **argv){
if(argc < 3){
    printf("Użycie: a.out plik_wejsciowy.txt plik_wyjsciowy.txt");
    return -1;
  }
  clock_gettime(CLOCK_MONOTONIC, &start);
  we =fopen(argv[1],"r"); 
 
  for(i = 1; i <= MAX; i++)
  {
    k[i] = INF;
    p[i] = 0;
    Q[i] = false; // jest w Q(t) czy nie Q(f)
    sv[i] = NULL; // sasiedzi
  }
  n = 0;
 clock_gettime(CLOCK_MONOTONIC, &s_input); 
 fscanf(we,"%i %i %i",&v0,&vk,&m); //zczytywanie z pliku,
  for(i = 1; i <= m; i++)
  {
    fscanf(we,"%i %i %i",&x,&y,&z); //zczytywanie krawedzi z pliku
    if(x > n) n = x; // x - numer wierzcholka
    if(y > n) n = y; // y - numer wierzcholka do ktorego x jest podlaczony
    pw = new Node; // z - waga (w wiekszosci 1, ale kiedy jest sciana labiryntu to 100)
    pw->nast = sv[x];
    pw->nw = y;
    pw->waga = z;
    sv[x] = pw;
  }
  clock_gettime(CLOCK_MONOTONIC, &e_input);
  k[v0] = 0; // v0 to v0 koszt zerowy
  clock_gettime(CLOCK_MONOTONIC, &s_steps); //stars steps
	#pragma omp parallel
	{ int startv,endv,step,step2,	me = omp_get_thread_num();
	#pragma omp single
	{ nr = omp_get_num_threads(); ilosc = m/nr;
		printf("%d threads\n",nr);}
	startv = me * ilosc;
	endv = startv+ ilosc -1;
	
	for(step=startv;step<endv;step++){ 
    u = -1; 
    
    for(step2 = startv; step2 <= endv; step2++)
    if(!Q[step2] && ((u == -1) || (k[step2] < k[u]))) u = step2;
    Q[u] = true;
    pw = sv[u]; // uaktualnienie sasiadow wierzcholka
  #pragma omp barrier
}
  while(pw) {
      if(!Q[pw->nw] && (k[pw->nw] > k[u] + pw->waga)) // uaktualnia sasiedztwo wierzcholka
      { // przy przejsciu do nastepnego
        k[pw->nw] = k[u] + pw->waga;
        p[pw->nw] = u;
      }
      pw = pw->nast;
    }
  }
//	#pragma omp barrier	
//}
  long int s[MAX]; // wypisywanie kolejnych wierzcholkow drogi od v0 do vk
  int ii;  
  clock_gettime(CLOCK_MONOTONIC, &e_steps);
  wy = fopen(argv[2],"w");
  for(i=1;i<=n;i++){
	fprintf(wy,"%i :",i);
	ii=0;
	 j=i;
	while(j){
	s[ii++]=j;j=p[j];}
	while(ii){ fprintf(wy,"%i ",s[--ii]);}
	fprintf(wy,"~%i",k[i]);	
}
  fprintf(wy,"v0 do vk: %i> ",v0);
  i = 0; j = vk;
	
    while(j)
    {
      s[i++] = j; j = p[j];
    }
    while(i)
        fprintf(wy,"%ld ",s[--i]); // wypisywanie kolejnych wierzcholkow drogi od v0 do vk
        fprintf(wy,">%i ~%i",vk,k[vk]);
    
clock_gettime(CLOCK_MONOTONIC, &end);
printf("Time : %.16f\n", timeDiff(&end, &start));
printf("Read : %.16f\n", timeDiff(&e_input, &s_input));
printf("Steps: %.16f\n", timeDiff(&e_steps, &s_steps));

fclose(wy);
fclose(we);
return 0;
}


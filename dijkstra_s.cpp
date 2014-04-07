/*
 * Labirynt #Dijkstra
 * @author: Paweł Sawicki
 * g++ dijkstra_s.cpp -o dijkstra
 */
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100
#define INF 9999
using namespace std;
struct Node {
  int nw;
  int waga; // waga ( W labiryncie kazda waga wynosi 1)
  struct Node * nast;
};
int main(int argc,char **argv){
  FILE *we; 
  //Inicjalizacja zczytywania z pliku 
  //if(argv[1][1]==EOF){ 
  //cout << "Uzycie ./dijkstra -r albo -d"<< endl; 
  //}else{
switch(argv[1][1]){
        case 'r':
        we = fopen("dane.txt","r");
        break;
        case 'd':
        we = fopen("dane2.txt","r");
        break;
        default:
        cout << "Uzycie ./dijkstra -r(dane.txt) -d(dane2.txt)" << endl;
        break;}
  int i,j,x,y,z,v0,vk,u,n,m; // x,y,z - pomocnicze
  int k[MAX],p[MAX]; // k - koszt, p - pomocnicze do obliczania kosztow
  bool Q[MAX]; // Q - sasiedztwo
  struct Node *sv[MAX],*pw; // sv - jakie wierzcholek ma sasiedztwo
  for(i = 1; i <= MAX; i++)
  {
    k[i] = INF;
    p[i] = 0;
    Q[i] = false; // jest w Q(t) czy nie Q(f)
    sv[i] = NULL; // sasiedzi
  }
  n = 0;
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
  k[v0] = 0; // v0 to v0 koszt zerowy
  for(i = 1; i <= n; i++)
 { // Sprawdzenie czy droga do wierzcholka nie jest zbyt kosztowna
    u = -1; // (sciany labiryntu maja wieksza wage niz normalne drogi pomiedzy wierzcholkami)
    for(j = 1; j <= n; j++)
    if(!Q[j] && ((u == -1) || (k[j] < k[u]))) u = j;
    Q[u] = true;
    pw = sv[u]; // uaktualnienie sasiadow wierzcholka
    while(pw) {
      if(!Q[pw->nw] && (k[pw->nw] > k[u] + pw->waga)) // uaktualnia sasiedztwo wierzcholka
      { // przy przejsciu do nastepnego
        k[pw->nw] = k[u] + pw->waga;
        p[pw->nw] = u;
      }
      pw = pw->nast;
    }
  }
  int s[MAX]; // wypisywanie kolejnych wierzcholkow drogi od v0 do vk
  cout << v0 << " > ";
  i = 0; j = vk;
    while(j)
    {
      s[i++] = j; j = p[j];
    }
    while(i) cout << s[--i] << " ";
        cout << " > " << vk << " #" << k[vk] << endl;
 fclose(we);
 return 0;
}


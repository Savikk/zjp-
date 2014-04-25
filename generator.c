#include <stdio.h>
/* Generator ostateczny labiryntu dijkstry
 * Jedynie "nie stawia" scian :c
 *
 */

FILE *wy;
int main(int argc,char **argv){
	if(argc <4){
	printf("./generator ilosc_v vk ilescian plik_wyjsciowy.txt");
	return -1;
}	int waga =1;
	int licznik=0;
	int plus,minus,jed,jedn;
	int max_v = atoi(argv[1]);
	int hasz = atoi(argv[3]);
	wy = fopen(argv[4],"w");
	int i;
	fprintf(wy,"1\n");
	fprintf(wy,"%i\n",atoi(argv[2]));
	for(i=1;i<max_v+1;i++){
	licznik=licznik+4;
}
	fprintf(wy,"%i\n",licznik);	
	for(i=1;i<max_v+1;i++){
		plus=i+10;
	minus=i-10;
	jed=i+1;
	jedn=i-1;
if((i%10)!=0){fprintf(wy,"%i %i %i\n",i,jed,waga);}
if((i%10)!=0)){fprintf(wy,"%i %i %i\n",i,jedn,waga);}
if(plus<max_v){fprintf(wy,"%i %i %i\n",i,plus,waga);}
if(minus>0){fprintf(wy,"%i %i %i\n",i,minus,waga);}
}
fclose(wy);		
return 0;
}

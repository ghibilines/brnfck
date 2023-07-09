#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "functions1.h"
#define LEN 1000

int main(int argc,char **argv)
{
	FILE *f;
	int * memory;
	int loop=0;
	int i=0, j,k;
	int ip, *vp;///!!!
	int c, instr=0;
	
	memory = (int *) malloc(LEN*sizeof(int));
	if (memory==NULL)    {
                fputs("cant malloc\n",stderr);
                return 1;
        }
	for(i=0;i<LEN;i++)      {
                *(memory+i) = 0;
        }
	if (argc == 2)	{
		if ((f=fopen(argv[1],"r")) == NULL)	{
			fputs("cant open file\n",stderr);
			return 1;
		}
		for(i=0;(c = fgetc(f)) != EOF && i<LEN;i++) {
        		*(memory+i) = c;
		}
		fclose(f);
	}
	else if (argc==1)	i=0;
	else if (argc!=1 && argc!=2)    { 
		free(memory);
		return 1;
	}
	ip = i;
	vp = memory + i;
	instr=i;
	interpreterintroduction(); //intro msg
	printf("%d>\t",i); //print cursor
	while(ip<LEN && vp-memory<LEN && instr<LEN)	{//ctrl+D c=getchar()!=EOF
		c=getchar();
		if (c=='\n')	printf("%d>\t",instr);//print cursor
		else if (c=='R')	ip = runloop(memory,ip,vp,LEN);
		else if (c=='I')	scanf("%d",&ip);
		else if (c=='V')	{
			scanf("%d",&j);
			vp = memory + j;
		}
		else if (c=='H')	brnfck3help(); //help msg
		else if (c=='X')	{
			printf("\nI: exiting interpreter\n");
			break;
		}
		else if (c=='D')	{
			scanf("%d-%d",&j,&k);
			for(;j<=k;j++)	{
				printf("%d->%c%c%c%c%c%c%c%c%c%c",j,(char) *(memory+j*10+0),(char) *(memory+j*10+1),
						(char) *(memory+j*10+2),(char) *(memory+j*10+3),(char) *(memory+j*10+4),
						(char) *(memory+j*10+5),(char) *(memory+j*10+6),(char) *(memory+j*10+7),
						(char) *(memory+j*10+8),(char) *(memory+j*10+9)
						);
			}
		}
		else {
			*(memory+instr)=c;
			instr++;
		}
	
	}
	free(memory);
}

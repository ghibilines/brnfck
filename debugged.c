#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define LEN 100

int main(int argc,char **argv)
{
	FILE *f;
	unsigned int g;
	int * instructions;
	unsigned int instr;
	int loop=1;
	int i, j;
	short * mem;
	short * pointer;
	int c;
	instructions = (int *) malloc(LEN*sizeof(int));
        mem = (short *) malloc(LEN*sizeof(short));
	if (mem==NULL || instructions==NULL)    {
                fputs("cant malloc\n",stderr);
                return 1;
        }
	for(i=0;i<LEN;i++)      {
                *(mem+i) = 0;
        }
	if (argc == 2)	{
		if ((f=fopen(argv[1],"r")) == NULL)	{
			fputs("cant open file\n",stderr);
			return 1;
		}
		for(i=0;(c = fgetc(f)) != EOF && i<LEN;i++) {
        		*(instructions+i) = c;
		}
		fclose(f);
	}
	else if (argc==1)	{
		for(i=0;(c=getchar()) != '\n' && i<LEN;i++)	{
			*(instructions+i) = c;
			printf("read %c\n",c);
		}
	}
	else if (argc!=1 && argc!=2)	{ return 1;}
	pointer=mem;
	for(instr=0;instr<LEN;instr++)
	{
		c=*(instructions+instr);
		switch (c)	{
			if (isspace(c) ) return 1;
			case '>':	{
				pointer++;
				break;	}
			case '<':	{
				pointer--;
				break;	}
			case '+':	{
				(*pointer)++;
				break;	}
			case '-':	{
				(*pointer)--;
				break;	}
			case '.':	{
				printf("%d\n",*pointer);
				break;	}
			case ',':	{
				*(pointer) = getchar();
				break;	}
			case '[':	{
				g=instr;
				loop=0;
				if (*(pointer)==0)	{
					for(i=0,c='['; c!=']' && i<LEN;i++)	{ 
						c=*(instructions+instr+i);
						j=i;      	}
					instr+=j-1;	}
				break;	}
			case ']':	{
				if ((*pointer)!=0 && loop==0) { 
					instr=g-1;
					loop=1;	}	
				break;	}
			default: break;
		}
	
	}
	free(instructions);
	free(mem);
}

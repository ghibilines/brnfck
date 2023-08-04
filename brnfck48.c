#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "functions5.h"
#define LEN 1000

int main(int argc,char **argv)
{
	FILE *f;
	int * memory;
	int i=0, j,k,l;
	int ip, *vp;///!!!
	int c, instr=0,d;
	
	memory = (int *) malloc(LEN*sizeof(int));
	if (memory==NULL)    {
                fputs("cant malloc\n",stderr);
                return 1;
        }
	for(i=0;i<LEN;i++)      {
                *(memory+i) = 0;
        }
	if (argc == 2)	{
		if ((f = fopen(argv[1],"r"))==NULL)	{
			printf("\nE: cant open file\n");
			return 1;
		}
		long fsize;
		fseek(f,0,SEEK_END);
		fsize = ftell(f);
		fseek(f,0,SEEK_SET);
		if (fsize<LEN)	{
			fread(memory,fsize,1,f);
		}
		else	{
			printf("\nE: file too big to load into memory\n");
			return 1;
		}
		fclose(f);
		i=(int) fsize/4;
	}
	else if (argc==1)	i=0;
	else if (argc!=1 && argc!=2)    {
		printf("\nE: arguments invalid\n");	
		free(memory);
		return 1;
	}
	ip = i;
	vp = memory + i;
	instr=i;
	interpreterintroduction(); //intro msg
	printf("%d>\t",i); //print cursor
	while(ip<LEN && vp-memory<LEN && instr<LEN)	{
		c=getchar();
		if (c=='\n')	printf("%d>\t",instr);//print cursor
		else if (c=='R')	ip = runloop(memory,ip,vp,LEN);
		else if (c=='I')	{
			scanf("%d",&ip);
		}
		else if (c=='V')	{
			scanf("%d",&j);
			vp = memory + j;
		}
		else if (c=='E')	{
			scanf("%d",&instr);
		}
		else if (c=='H')	brnfck3help(); //help msg
		else if (c=='X')	{
			printf("\nI: exiting interpreter\n");
			break;
		}
		else if (c=='N')	{
			instr = 10* ((int) instr/10+1);
		}
		else if (c=='P')	{
			instr = 10* ((int) instr/10-1);
		}
		else if (c=='\\')	{//if backslash read num
			int temp;
			if(scanf("%d",&temp))	{
				*(memory+instr) = temp;
				instr++;
			}
			else	{
				printf("\nE: editor syntax: no number following backslash\n");
			}
		}	
		else if (c=='W')	{
			int len;
			scanf("%d",&len);
			len*=4;
			system("touch out.mem");
			f = fopen("out.mem","wb");
			if (f)	{
				fwrite(memory,len+1,1,f);
				printf("\nI: wrote mem to file out.mem\n");
			}
			else {
				printf("\nE: couldnt create file\n");
			}
			fclose(f);
		}
		else if (c=='D')	{
			scanf("%d-%d",&j,&k);
			for(;j<=k;j++)	{
				printf("\t%d->\t",j*10);
				for(l=0;l<10;l++)	{
					switch (d=*(memory+j*10+l))	{
						case 'j':	{
							printf(" j");
							break;
						}
						case 'v':	{
							printf(" v");
							break;
								}
						case 'p':	{
							printf(" p");
							break;
								}
						case 'o':	{
							printf(" o");
							break;
								}
						case 'r':	{
							printf(" r");
							break;
								}
						case '+':	{
							printf(" +");
							break;
								}
						case '-':	{
							printf(" -");
							break;
								}
						case '.':	{
							printf(" .");
							break;
								}
						case ',':	{
							printf(" ,");
							break;
								}
						case ']':	{
							printf(" ]");
							break;
								}
						case '[':	{
							printf(" [");
							break;
								}
						case '>':	{
							printf(" >");
							break;
								}
						case '<':	{
							printf(" <");
							break;
								}
						default:	{
							printf(" %d",d);
							break;
						}
					}
				}
				printf("\n");
			}
		}
		else {
			*(memory+instr)=c;
			instr++;
		}
	
	}
	free(memory);
}

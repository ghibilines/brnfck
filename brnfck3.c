#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define LEN 100

int main(int argc,char **argv)
{
	FILE *f;
	int * instructions;
	unsigned int instr=0;
	int loop=0;
	int i, j;
	short * mem;
	short * pointer;
	int c;
	char d;
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
			printf("read(%d) %c\n",i,c);
		}
	}
	else if (argc!=1 && argc!=2)	{ return 1;}
	pointer=mem;
	for(instr=0;0<=instr<LEN;instr++)
	{
		c=*(instructions+instr);
		switch (c)	{
			case 0:
				return 1; //doesnt exit
			case 'v':	{
				pointer=mem+(*pointer);
				break;
					}
			case 'j':	{
				instr=(*pointer)-1;
				break;
					}
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
			case 'o':	{
				printf("%c",(char) *pointer);
				break;
					}
			case '.':	{
				printf("%hd\n",*pointer);
				break;	}
			case ',':	{
				scanf("%hd",pointer);
				break;	}
			case '[':	{
				if (*(pointer)==0)	{
					loop = -1;
					for(i=0,c='['; loop!=0 && 0<=i+instr<LEN;i++)     {
						c=*(instructions+instr+i);
                                	        if (i>0 && c=='[')       {
							loop--;
                                	        }
						else if (c==']')	{
							loop++;
						}
						else if (c==0)	{
							printf("[syntaxerror");
							return 1;
						}
					}
					printf("jump from %d to %d\n",instr,instr+i-2+1);
					instr=instr+i-2;
				}
				break;	}
			case ']':	{
				if (*(pointer)!=0) {
					loop = -1;
                                        for(i=0,c=']'; loop!=0 && 0<=instr-i<LEN ;i++)     {
                                                c=*(instructions+instr-i);
                                                if (i>0 && c==']')       {
                                                        loop--;
                                                }
						else if (c=='[')        {
                                                        loop++;
                                                }
						else if (c==0)	{
							printf("]syntax error");
							return 1;
						}
                                        }
					printf("jump from %d to %d\n",instr,instr-i+1);
                                        instr=instr-i-2;	
				}
				break;	}
			default: break;
		}
	
	}
	free(instructions);
	free(mem);
}

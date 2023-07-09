#include <stdio.h>

int runloop(int * mem, int b, int* d, int len);
void brnfck3help();
void interpreterintroduction();

int runloop(int * mem, int b, int * d, int len) //only returns ip
{
	int loop=0,i=0;
	int c;
	int ip = b, *vp;
	vp=d;
	printf("running %d\n",ip);
        for(;c!='x' && 0<=vp-mem<len &&  0<=ip<len;ip++)   {
        	c = *(mem+ip); 
                //doesnt seem to matter, see test.c
		//compiler knows
		switch (c)      {
			case 0: 	{
				return ip;
			}
                	case 'v':       {
                        	vp = mem + *(vp);
                                break;
                        }
                        case 'j':       {
                        	ip = *(vp)-1;
                                break;
                        }
                        case '>':       {
                                vp++;
                                break;  }
                        case '<':       {
                                vp--;
                                break;  }
                        case '+':       {
                                (*(vp))++;
                                break;  }
                        case '-':       {
                                (*(vp))--;
                                break;  }
                        case '.':       {
                                printf("%d\n",*(vp));
                                break;  }
			case 'o':	{
				printf("%c", (char) *(vp) );
				break;
			}
                        case ',':       {
                                scanf("%d",vp);
                                break;  }
                        case '[':       {
                                if (*(vp)==0)    {
                        		loop = -1;
                                        for(i=0,c='['; loop!=0 && 0<=i+ip<len;i++)     {
                                        	c=*(mem+ip+i);
                                                if (i>0 && c=='[')       {
                                                	loop--;
                                                }
                                                else if (c==']')        {
                                                        loop++;
                                                }
                                                else if (c==0)  {
                                                	printf("[syntaxerror");
                                                        break;
                                                }
                       			}
                                        printf("jump from %d to %d\n",ip,ip+i-2+1);
                                        ip=ip+i-2;
				}
                                break;
			}
			case ']':       {
                        	if (*(vp)!=0) {
                                	loop = -1;
                                        for(i=0,c=']'; loop!=0 && 0<=ip-i<len ;i++)     {
                                        	c=*(mem+ip-i);
                                                if (i>0 && c==']')       {
                                                	loop--;
                                                }
                                                else if (c=='[')        {
                                                	loop++;
                                                }
                                                else if (c==0)  {
                                                	printf("]syntax error");
                                                        break;
                                                }
                                   	}
                                        printf("jump from %d to %d\n",ip,ip-i+1);
                                        ip=ip-i-2;
                            	}
                                break;
               		}
                        default: break; //do nothing
		}//end switch
	}//end run loop
	printf("-%d\n",ip);
	return ip;
}

void brnfck3help()	{
	printf("\nEDITOR HELP\n");
	printf("\n\n");
	printf("\nbrnfck3 is essentially the same as normal brainfuck with only a few differences\n");
	printf("you are given a block of memory with an instruction pointer (ip) and a stack pointer (vp)\n");
	printf("DIFFERENCES:\n");
	printf("\t'v' - sets your vp to the value of the memory it points at, allowing you to jump around memory with your vp\n");
	printf("\t'j' - sets your ip to the value of the memory the vp points at, allowing you to jump around memory with your ip\n");
	printf("\t'o' - prints value at vp as a character\n");
	printf("SIMILARITIES:\n");
	printf("\t'<' - decrements your vp\n");
	printf("\t'>' - increments vp\n");
	printf("\t'+' - increments value at vp\n");
	printf("\t'-' - decrements value at vp\n");
	printf("\t'.' - prints value at vp as a digit\n");
	printf("\t',' - reads digit from stdin to memory at vp\n");
	printf("\t'[' - if value at vp is 0, it jumps the ip to the matching ']'\n");
	printf("\t']' - if value at vp is NOT 0, it jumps the ip back to the matching '['\n\n");
}

void interpreterintroduction()
{
	printf("I: entering the interpreter\n\n");
        printf("STEP 1: write your brnfck3 code\n");
        printf("STEP 2: enter interpreter command 'I' to store your program entry point, AND where it should stop executing\n");
	printf("like this: 'digit,digit'  entry point, exit point\n");
	printf("without an exit point your program will not stop executing\n");
        printf("STEP 3: enter interpreter command 'V' to store your stack entry point\n");
        printf("!!!\tbrnfck3 code and stack share the same memory\t!!!\n");
        printf("!!!\tYOUR PROGRAM CAN OVERWRITE ITSELF\t!!!\n");
	printf("STEP 5: enter interpreter command 'R' to run your program\n");
        printf("your program will stop running when it encounters a 0 character in memory\n");
        printf("enter interpreter command 'H' for help with brnfck3 commands\n\n");
}

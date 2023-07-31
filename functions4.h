#include <stdio.h>

int runloop(int * mem, int b, int* d, int len);
void brnfck3help();
void interpreterintroduction();
int intchk(int c);

int runloop(int * mem, int b, int * d, int len) //only returns ip
{
	int loop=0,i=0;
	int c, temp;
	int ip = b, *vp, *ret, vpjump=0;
	vp=d;
	printf("\trunning %d\n",ip);
        for(;c!='x' && 0<=vp-mem<len &&  0<=ip<len;ip++)   {
        	c = *(mem+ip); 
                //doesnt seem to matter, see test.c
		//compiler knows
		switch (c)      {
			case 0: 	{
				return ip;
			}
                	case 'v':       {
				ret=vp;
                        	vp = mem + (*vp);
				vpjump=1;
                                break;
                        }
			case 'p':	{//follow with arg
				ip++;
				c = *(mem+ip);
				(*(vp)) = c;
				break;
			}
			case 'r':	{
				if (vpjump==1)	{
					vp = ret;
					vpjump=0;
					break;
				}
				else if (vpjump==0)	{
					printf("\nE: syntaxerror: no 'v' preceding 'r'\n");
					return ip;
				}
				break;
			}
			case '>':       {//follow with arg
				ip++;
				c=*(mem+ip);
				if(!intchk(c) && c!=0)	{
					vp=vp+c;
				}
				else	{
					ip--;
                                	vp++;
				}
                                break;  }
                        case '<':       {//follow with arg
				ip++;
				c=*(mem+ip);
				if (!intchk(c) && c!=0)	{
					vp=vp-c;
				}
				else	{
					ip--;
                                	vp--;
				}
                                break;  }
                        case '+':       {//use temp
				ip++;
				c=*(mem+ip);
				if (!intchk(c) && c!=0)	{
					(*(vp))=(*(vp))+c;
				}
				else	{
					ip--;
					(*(vp))++;
				}
                                break;  }
                        case '-':       {//use temp
				ip++;
				c=*(mem+ip);
				if (!intchk(c) && c!=0)	{
					(*(vp))=(*(vp))-c;
				}
				else	{
					ip--;
					(*(vp))--;
				}
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
                                        ip=ip-i-2;
                            	}
                                break;
               		}
                        default: break; //do nothing
		}//end switch
	}//end run loop
	return ip;
}

void brnfck3help()	{
	printf("\nEDITOR HELP:\n");
	printf("\t'X' - exit the interpreter\n\t'N' - go to next page (ten positions)\n\t'P' - previous page\n\t'E' - edit specific location\n\t'D' - dump pages between range\n\t'W' - writes positions 0 to arg to out.mem\n\t'\\' - if followed by a number inserts that number in memory\n");
	printf("\nbrnfck3 is essentially the same as normal brainfuck with only a few differences\n");
	printf("you are given a block of memory with an instruction pointer (ip) and a stack pointer (vp)\n");
	printf("DIFFERENCES:\n");
	printf("some select commands if followed by a number in programspace it repeats that command that number of times, these are marked with *\n");
	printf("\t'v' - sets your vp to the value of the memory it points at, allowing you to jump around memory with your vp\n");
	printf("\t'r' - returns from vp jump to original vp location\n");
	printf("\t'j' - sets your ip to the value of the memory the vp points at, allowing you to jump around memory with your ip\n");
	printf("\t'o' - prints value at vp as a character\n");
	printf("\t'p' -* puts a number at vp location, argument required\n ");
	printf("SIMILARITIES:\n");
	printf("\t'<' -* decrements your vp\n");
	printf("\t'>' -* increments vp\n");
	printf("\t'+' -* increments value at vp\n");
	printf("\t'-' -* decrements value at vp\n");
	printf("\t'.' - prints value at vp as a digit\n");
	printf("\t',' - reads digit from stdin to memory at vp\n");
	printf("\t'[' - if value at vp is 0, it jumps the ip to the matching ']'\n");
	printf("\t']' - if value at vp is NOT 0, it jumps the ip back to the matching '['\n\n");
}

void interpreterintroduction()
{
	printf("I: entering the interpreter\n\n");
        printf("STEP 1: write your brnfck3 code\n");
        printf("STEP 2: enter interpreter command 'I' to store your program entry point, the program stops executing when it encounters a 0\n");
        printf("STEP 3: enter interpreter command 'V' to store your stack entry point\n");
        printf("!!!\tbrnfck3 code and stack share the same memory\t!!!\n");
        printf("!!!\tYOUR PROGRAM CAN OVERWRITE ITSELF\t!!!\n");
	printf("STEP 4: enter interpreter command 'R' to run your program\n");
        printf("your program will stop running when it encounters a 0 character in memory\n");
        printf("enter interpreter command 'H' for help with brnfck3 commands\n\n");
}

int intchk(int c)	{
	if (c!='v' && c!='p' && c!='r' && c!='j' && c!='<' && c!='>' && c!='+' && c!='-' && c!='.' && c!='o' && c!=',' && c!='[' && c!=']')	{
		return 0;
	}
	else {
		return 1;
	}
}

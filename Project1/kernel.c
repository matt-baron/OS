/* ACADEMIC INTEGRITY PLEDGE                                              */
/*                                                                        */
/* - I have not used source code obtained from another student nor        */
/*   any other unauthorized source, either modified or unmodified.        */
/*                                                                        */
/* - All source code and documentation used in my program is either       */
/*   my original work or was derived by me from the source code           */
/*   published in the textbook for this course or presented in            */
/*   class.                                                               */
/*                                                                        */
/* - I have not discussed coding details about this project with          */
/*   anyone other than my instructor. I understand that I may discuss     */
/*   the concepts of this program with other students and that another    */
/*   student may help me debug my program so long as neither of us        */
/*   writes anything during the discussion or modifies any computer       */
/*   file during the discussion.                                          */
/*                                                                        */
/* - I have violated neither the spirit nor letter of these restrictions. */
/*                                                                        */
/*                                                                        */
/*                                                                        */
/* Signed:__Jacob Hamblen & Matt Baron_____ Date:___1/30/17_______        */
/*                                                                        */
/*                                                                        */
/* 3460:4/526 BlackDOS kernel, Version 1.03, Spring 2017.                 */

void handleInterrupt21(int, int, int, int);

void main()
{
   char line[80];
   int x;
   
   makeInterrupt21();
   /*clearScreen(0,0);*/
	interrupt(33,12,1,5,0);
   interrupt(33,0,"___.   .__                 __       .___           \r\n\0",0,0);
   interrupt(33,0,"\\_ |__ |  | _____    ____ |  | __ __| _/___  ______\r\n\0",0,0);
   interrupt(33,0," | __ \\|  | \\__  \\ _/ ___\\|  |/ // __ |/ _ \\/  ___/\r\n\0",0,0);
   interrupt(33,0," | \\_\\ \\  |__/ /\\ \\\\  \\___|    </ /_/ ( <_> )___ \\ \r\n\0",0,0);
   interrupt(33,0," |___  /____(____  /\\___  >__|_ \\____ |\\___/____  >\r\n\0",0,0);
   interrupt(33,0,"     \\/          \\/     \\/     \\/    \\/         \\/ \r\n\0",0,0);
   interrupt(33,0," V. 1.03, C. 2017. Based on a project by M. Black. \r\n\0",0,0);
   interrupt(33,0," Author(s): Jake Hamblen and Matt Baron.\r\n\r\n\0",0,0);
   
   interrupt(33,0,"Hola mondo.\r\n\0",0,0);
   interrupt(33,0,"Enter a line: \0",0,0);
   interrupt(33,1,line,0,0);
   interrupt(33,0,"\r\nYou typed: \0",0,0);
   interrupt(33,0,line,0,0);
   interrupt(33,0,"\r\n\0",0,0);
   x = 5; 
   interrupt(33,0,"Your number is \0",0,0);
   interrupt(33,13,x,0,0);
   interrupt(33,0,"\r\n\0",0,0);
	
   while(1);
}

void printString(char* c)
{
	int i = 0;
   while(*(c+i) != '\0') {
		interrupt(16,14*256+*(c+i),0,0,0);
		i++;
   }
	return;
}

void readString(char* c)
{
	int ending = 0; 
	int i = 0;
	char n;
	while(ending == 0) {
   	n = interrupt(22,0,0,0,0);
   	if(n == 0x8 && i != 0) {  /*Backspace Handler*/
			*(c+i) = ' ';
			i--;
		}
		else if(n == 0xD) { /*Enter Handler*/
			ending = 1;
			*(c+i) = 0x0;
			i++;
			printString(c);
		}
		else {	/*otherwise, write n to string array.*/
			*(c+i) = n;
			i++;
		}
	}
	return;
}

void clearScreen(int bx, int cx)
{
	int i;
	for(i = 0; i<24; i++) {
		printString('\0');
	}
	interrupt(16, 512, 0, 0, 0);
	if(bx > 0 && cx > 0) 
		interrupt(16, 1536, 4096 * (bx - 1) + 256 * (cx - 1), 0, 6223);
	
	return;
}

int mod(int a, int b)
{
   int x = a;
   while (x >= b) x = x - b;
   return x;
}

int div(int a, int b)
{
   int q = 0;
   while (q * b <= a) q++;
   return (q - 1);
}

void writeInt(int x)
{
   char number[6], *d;
   int q = x, r;
   if (x < 1)
   {
      d = number; *d = 0x30; d++; *d = 0x0; d--;
   }
   else
   {
      d = number + 5;
      *d = 0x0; d--;
      while (q > 0)
      {
         r = mod(q,10); q = div(q,10);
         *d = r + 48; d--;
      }
      d++;
   }
   printString(d);
}

void readInt(int* number)
{
	char* c;
   int i = 0;
	int len = 0;
	readString(c);
	while(*(c+len++) != '\0');
	len--;
	while(len > -1) {
		number += *(c+i++)^len--;
	}

   return;
}

void handleInterrupt21(int ax, int bx, int cx, int dx) {
	if(ax == 0)
		printString(bx);
	else if(ax == 1) 
		readString(bx);
	else if(ax == 12)
		clearScreen(bx, cx);
	else if(ax == 13) 
		writeInt(bx);
	else if(ax == 14)
		readInt(bx);
	else {
		printString("Error: Invalid interrupt command");
	}
}

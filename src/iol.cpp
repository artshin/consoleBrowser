/* Assignment Number 1 
Subject Code and Section OOP344 A
Team Name - C SUCKS
Student Name - Jesse Silver, Arthur Shinkevich, Chris Stephens 
Student Number - 044819092, 040114092, 052627090
Instructor Name - Danny Abesdris
Due Date - October 17 23:59:00
Date Submitted October 17 

Student Oath:
All assignments must include the following statement:

"This assignment represents my own work in accordance
with Seneca Academic Policy"

Signature(s): Jesse Silver - 044819092
Arthur Shinkevich - 040114092 
Chris Stephens - 052627090


All assignments must contain a statement(s)
of the nature of the problem being solved
(i.e. Purpose of the assignment). Assignments should
be well commented, and must be properly indented
according to the guidelines established in class
(i.e. a minimum of 3 spaces of indenting is
required for each new code block).


The functions displayflag,flag,displaymenu item, and menuItem were originally coded/commented by Arthur.

The functions edit, display, getch, were originally coded/commented by Jesse.

Several of the basic functions were taken from in class examples from Danny Abesdris.

The program was assembled, re-commented, tested as a whole, making several changes to various 
functions throughout the program by Chris

*/
#include "iol.h"

void iol_displayflag(const char* format, int row, int col, int status){

    char *temp;  /*allocating memory for a temp array that holds the format */

    temp = (char*) malloc(sizeof(format)) + strlen((format)+1);
    strcpy(temp,format);

    if(status == 0)            /* changing the checkmark */
        temp[1] = ' ';

    else if(status == 1)
        temp[1] = 'X';

    iol_display(temp,row,col,col);           /*displaying the result*/
    iol_movecur(row,col+1);                  /*and moving the cursor*/
}
int iol_flag(const char* format, int row, int col, int* status, int radio){

    int key;             /*creating variables to hold the value of key pressed*/
    bool exit = false;       /*and loop exit varaible*/

     if (*status != 1 || *status != 0)
        *status = 1;        /*changing the status if it is not 0 or 1*/

    while(!exit){           /*beginning of the loop*/
        iol_displayflag(format,row,col,*status);
        key = iol_getch();


      if(key == ' '){   /*if space pressed then status changes */
            if(radio == 1)  /*according to a radio value */
                *status = 1;
            else if(radio == 0){
                if(*status == 0)
                    *status = 1;
                else if(*status == 1)
                    *status = 0;
            }

           iol_displayflag(format,row,col,*status);
           exit = true; /*displays the flag and exits the function*/
        }


        else if(key == F1_KEY || key == F2_KEY || key == F3_KEY ||
          key == F4_KEY || key == F5_KEY || key == F6_KEY ||
          key == F7_KEY || key == F8_KEY || key == F9_KEY ||
          key == F10_KEY || key == F11_KEY || key == F12_KEY)
            exit = true;   /*if any function key pressed, the function
                            is terminated */

    }

    return key;
}
void iol_displayMenuItem(const char* format, const char* menuItem, int row,
			 int col, int len, int status){

    int itemlen,i;  /*creating variable to store strlen of menu item*/
    char *temp;  /*and a temp variable for a space or special character format*/

    temp = (char*) malloc(sizeof(menuItem)) + len;

    itemlen = strlen(menuItem);

    

    if (status == 0){
        
        for(i=0; temp; i++) /*a lot of display function, but I found no other way*/
            temp[i] = ' ';  /*to store everything in one array */

        iol_display(temp,row,col,len);
        iol_display(menuItem,row,col+1,len);
        if(itemlen < (len -2))
            iol_display(temp,row,col+len,len);
        iol_movecur(row,col+1);
    }
    else if (status != 0){
        strcpy(temp,format);

        iol_display(temp++,row,col,len); /*moves the position of a temp by one*/
        iol_display(menuItem,row,col+1,len);
        if(itemlen < (len -2))
            iol_display(temp,row,col+len,len);
        iol_movecur(row,col+1);
     }
}
int iol_menuItem(const char* format, const char* menuItem, int row,
		 int col, int len, int* status){

    int key;            /*creating variables to hold the value of key pressed*/
    bool exit = false;  /*and loop exit variable*/


    if(*status != 0 && *status != 1) /*changing the status if it is anything*/
        *status = 1;                 /*but 0 or 1*/

    iol_displayMenuItem(format,menuItem,row,col,len,*status);

    while(!exit){ /*beginning of a loop that captures the key pressed*/
        key = iol_getch();

        if(key == ' '){  /*changes the status then space pressed*/
            *status = 1;
            iol_displayMenuItem(format,menuItem,row,col,len,*status);
            exit = true;
        }

        if(key == F1_KEY || key == F2_KEY || key == F3_KEY ||
           key == F4_KEY || key == F5_KEY || key == F6_KEY ||
           key == F7_KEY || key == F8_KEY || key == F9_KEY ||
           key == F10_KEY || key == F11_KEY || key == F12_KEY ||
           key == TAB_KEY || key == ENTER_KEY || key == ESC_KEY ||
           key == DOWN_KEY || key == UP_KEY || key == LEFT_KEY ||
           key == RIGHT_KEY || key == HOME_KEY || key == BS_KEY ||
           key == INS_KEY || key == DEL_KEY || key == END_KEY ||
           key == PGDN_KEY || key == PGUP_KEY)
            exit = true; /*if any non-ascii key pressed
                           terminates the function */

    }

    return key;
}

/*main logic of the program defining actions for several of the keys*/

int iol_edit(string *str, int row, int col, int fieldlen, int maxdatalen,
	     int* insertmode, int* offset, int* curpos, int IsTextEditor,
	     int ReadOnly){

    /*declaring variables:
     *key = to catch a key pressed; 'i' and 'j' as loop and array counters
     *temp as a dynamic array to hold str value
     *iol_cur,iol_offset and iol_insmode as local placeholders of curpos
     *offset and insertmode
     *max_offset to count maximum offset possible.
     */
    int key=0,iol_cur=0,iol_offset=0,iol_insmode=1,i,j;
    string temp=*str,temp2,temp3;
    int max_offset = maxdatalen - fieldlen;

    /*1.allocating memory for a temporary array and checking if the allocation
     *was a success
     *2.Checking if pointers sent to a function are nulls and assigning values
     *to their local placeholders
     *3.Checking the values of placeholders*/

    /*1*/

		/*2*/
		insertmode != NULL ? iol_insmode = *insertmode : 0;
		offset != NULL ? iol_offset = *offset : 0;
		curpos != NULL ? iol_cur = *offset : 0;

		/*3*/
		if (iol_cur > fieldlen){
			iol_cur = fieldlen;
			*curpos = fieldlen;
		}
		if (iol_cur > str->size()){
			iol_cur = str->size();
			*curpos = iol_cur;
		}
		if (iol_cur < col)
			iol_cur = col;
	    
		if (iol_offset > str->size()){
			iol_offset = str->size();
			*offset = iol_offset;
		}

		iol_cur+=str->size();
		/*beginning of editing, first checking if ReadOnly == 0 or to any other
		 *value*/
		if (ReadOnly == 0){
			while(key!= ESC_KEY && key!= ENTER_KEY && key!= TAB_KEY && key!= UP_KEY &&
				  key!= DOWN_KEY && key!= PGUP_KEY && key!= PGDN_KEY &&
				  key!= F1_KEY && key!= F2_KEY && key!= F3_KEY &&
				  key!= F4_KEY && key!= F5_KEY && key!= F6_KEY &&
				  key!= F7_KEY && key!= F8_KEY && key!= F9_KEY &&
				  key!= F10_KEY && key!= F11_KEY && key!= F12_KEY && key != -1){
			   /*main editting loop*/
				for(i=0;temp3.size()<fieldlen&&temp[i+iol_offset];i++) {
					temp3+=temp[i+iol_offset];
				}
			   iol_display(temp3.c_str(),row,col,fieldlen);
			   temp3="";
			   iol_movecur(row,iol_cur);

			   key = iol_getch();
	           
	           
			   switch(key){
				   case LEFT_KEY:
						if(iol_cur != col)
							iol_cur--;
						if(iol_cur == col && iol_offset != 0)
							iol_offset--;
						break;
				   case RIGHT_KEY:
						if(iol_cur-col < fieldlen && iol_cur-col < temp.size())
							iol_cur++;
						if(iol_cur-col == fieldlen+1 && iol_offset <= max_offset)
							iol_offset++;
						break;
				   case HOME_KEY:
					   iol_cur = col;
					   iol_offset = 0;
					   break;
				   case END_KEY:
					   iol_cur = fieldlen+1;;
					   iol_offset = max_offset;
					   break;
				   case DEL_KEY:
					   if (iol_cur+iol_offset-col+1<temp.size())
						temp.erase(iol_cur+iol_offset-col+1,1);
					   break;
				   case BS_KEY:
					   if(iol_cur > col){
						   temp.erase(iol_cur+iol_offset-col-1,1);
							if(iol_cur != col)
								iol_cur--;
							if(iol_cur == col && iol_offset != 0){
								iol_offset--;
								iol_cur++;
							}
						}
					   break;
				   case INS_KEY:
					   iol_insmode==0 ? iol_insmode=1 : iol_insmode = 0;
					   break;
				   case TAB_KEY:
					   if(IsTextEditor!=0 &&
							   iol_cur+iol_offset-col<=maxdatalen &&
							   temp.size()<=maxdatalen){
						   for(i=0;i<IOL_TAB_SIZE;i++){
								for(j=maxdatalen;j>iol_cur+iol_offset-col;j--)
								   temp[j] = temp[j-1];
								temp[iol_cur+iol_offset-col+i] = ' ';
						   }
					   }
					   break;
				   case ESC_KEY:
					   if(IsTextEditor != 0){
						   *str=temp;
					   }
					   else{
						  temp=*str;
					   }
					   break;
				   case ENTER_KEY:
					   break;
				   default:
					   if(key > 31 && key < 127){
						   if(iol_insmode != 0 && iol_cur+iol_offset-col<=maxdatalen
								   && temp.size()<=maxdatalen-1 ){
								if (temp.size()) {
								   for(j=temp.size();j>iol_cur+iol_offset-col;j--)
									   temp[j] = temp[j-1];
								   temp+=temp[temp.size()-1];
								}
							   if ((iol_cur+iol_offset-col<temp.size())&&temp.size())
									temp[iol_cur+iol_offset-col] = key;
							   else
								   temp+=key;
							   if(iol_cur-col!=fieldlen)
								   iol_cur++;
							   else if(iol_cur-col==fieldlen && iol_offset != max_offset)
								   iol_offset++;
							}
						   else if (iol_insmode == 0 && iol_cur+iol_offset-col<=maxdatalen){
							   if ((iol_cur+iol_offset-col+1)<temp.size())
									temp[iol_cur+iol_offset-col] = key;
							   else
								   temp+=key;
							   if(iol_cur-col!=fieldlen)
					     		   iol_cur++;
							   else if(iol_cur-col==fieldlen && iol_offset != max_offset)
								   iol_offset++;
						   }
					   }
					   break;
	                   
				}/*end of switch*/
			}/*end of editting loop*/
			*str=temp;
		}/*end of ReadOnly == 0*/
		else{ /*if readonly == 1 */
			while ((key == LEFT_KEY || key == RIGHT_KEY || key == 0) && key != -1){
				iol_display(*str,row,col,fieldlen);
				iol_movecur(row,iol_cur);
				key = iol_getch();

				if(key == LEFT_KEY){
					if(iol_cur != col)
					   iol_cur--;
					if(iol_cur == col && iol_offset != 0)
					   iol_offset--;
				}
				else if(key == RIGHT_KEY){
					if(iol_cur < fieldlen)
					   iol_cur++;
					if(iol_cur == fieldlen && iol_offset <= max_offset)
					   iol_offset++;
				}


			}
		/*assigning pointers to changed values*/
		}
		if (offset)
			*offset = iol_offset;
		if (curpos)
			*curpos = iol_cur;
		if (insertmode)
			*insertmode = iol_insmode;
		/*deallocating dynamic array*/
		/*temp = '\0';*/
		return key;
}

void iol_display(string str, int row, int col, int len) {
	int i=0;
	string temp;
	if(len <= 0)
		len = str.size();
	for (i=0;i<str.size();i++) {
		temp+=str[i];
	}
	for (;i<len;i++)
		temp+=' ';
	iol_movecur(row,col);
	iol_prnstr(temp.c_str());
    
	if ((col+len) > (col+temp.size()) )
		len = str.size();
    iol_movecur(row,col+len);
}

void iol_prnstr(const char* s) {
    #if OS == UNIX
        addstr(s);
    #elif OS == WINDOWS
        cputs(s);
    #endif

}
void iol_putch(int c) {
  #if OS == WINDOWS
     putch(c);
  #elif OS == UNIX
     addch(c);
  #endif
}
void iol_init(void) {
	  #if OS == WINDOWS
     /* no startUP_KEY requirements for windows */
  #elif OS == UNIX
     initscr( );
     noecho( );
     cbreak( );
     keypad(stdscr, 1);
  #endif
}
void iol_end(void) {
	 #if OS == WINDOWS
     iol_clrscr( );
  #elif OS == UNIX
     refresh( );
     endwin( );
  #endif
}
int iol_rows(void) {
	 int rows;
  #if OS == WINDOWS
     HANDLE hStdout;
     struct _CONSOLE_SCREEN_BUFFER_INFO x;
     hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
     GetConsoleScreenBufferInfo(hStdout, &x);
     rows = x.dwSize.Y;
  #elif OS == UNIX
     rows = LINES;
  #endif
  return rows;
}
int iol_cols(void) {
  int cols;
  #if OS == WINDOWS
     HANDLE hStdout;
     struct _CONSOLE_SCREEN_BUFFER_INFO x;
     hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
     GetConsoleScreenBufferInfo(hStdout, &x);
     cols = x.dwSize.X;
  #elif OS == UNIX
    cols = COLS;
  #endif
  return cols;
}
void iol_clrscr(void) {
	  #if OS == WINDOWS
     /*system("cls");*/
     DWORD n;                         /* Number of characters written */
     DWORD size;                      /* number of visible characters */
     COORD coord = { 0 };             /* Top LEFT_KEY screen position     */
     CONSOLE_SCREEN_BUFFER_INFO csbi;

     /* Get a handle to the console */
     HANDLE h = GetStdHandle (STD_OUTPUT_HANDLE);
     GetConsoleScreenBufferInfo (h, &csbi);

     /* Find the number of characters to overwrite */
     size = csbi.dwSize.X * csbi.dwSize.Y;

     /* Overwrite the screen buffer with whitespace */
     FillConsoleOutputCharacter(h, TEXT(' '), size, coord, &n);
     GetConsoleScreenBufferInfo(h, &csbi);
     FillConsoleOutputAttribute(h, csbi.wAttributes, size, coord, &n);

     /* Reset the cursor to the top LEFT_KEY position */
     SetConsoleCursorPosition(h, coord);
  #elif OS == UNIX
     erase( );
  #endif
}
void iol_flush(void) {
	  #if OS == WINDOWS
     /* not required to UP_KEYdate the screen on windows */
  #elif OS == UNIX
     refresh( );
  #endif
}
int iol_getch(void) {
  int key;
  iol_flush();
  #if OS == WINDOWS
    key = getch( );
    /* On windows, getch( ) returns 0 for function keys, but
       0xE0 for all other non-ascii (extended) keys */
    key = (key == 0 || key == 0xE0) ? getch( ) + 1000 : key;
  #elif OS == UNIX
    key = getch( );
  #endif
  return key;
}

void iol_movecur(int row, int col) {
  #if OS == WINDOWS  /* windows specific routines for cursor control */
     HANDLE hStdout;
     struct _CONSOLE_SCREEN_BUFFER_INFO x;
     hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
     GetConsoleScreenBufferInfo(hStdout, &x);
     x.dwCursorPosition.X = col;
     x.dwCursorPosition.Y = row;
     SetConsoleCursorPosition(hStdout, x.dwCursorPosition);
  #elif OS == UNIX
     move(row, col);
  #endif
}


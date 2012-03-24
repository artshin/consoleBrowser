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

The functions edit, display, getch were originally coded/commented by Jesse.

Several of the basic functions were taken from in class examples from Danny Abesdris.

The program was assembled, re-commented, tested as a whole, making several changes to various 
functions throughout the program by Chris

*/

#define UNIX 1
#define WINDOWS 2
#ifdef OS
	#undef OS
#endif
#define OS WINDOWS /* choose which platform to compile for */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using namespace std;


#if OS == UNIX
  /* using Unix/Linux ncurses library only */
  #include <ncurses.h>
#elif OS == WINDOWS
  /* include windows specific libraries */
  #include <conio.h>
  #include <windows.h>
#endif

/* wrapper functions that will work for BOTH environments */
void iol_prnstr(const char* s);
void iol_display(string str, int row, int col, int len);
int iol_edit(string *str, int row, int col, int fieldlen, int maxdatalen,
	     int* insertmode, int* offset, int* curpos, int IsTextEditor,
	     int ReadOnly);
int iol_getch(void);
void iol_putch(int c);
void iol_init(void);
void iol_end(void);
int iol_rows(void);
int iol_cols(void);
void iol_clrscr(void);
void iol_flush(void);
int iol_getch(void);
void iol_movecur(int r, int c);
void iol_displayflag(const char* format, int row, int col, int status);
int iol_flag(const char* format, int row, int col, int* status, int radio);
void iol_displayMenuItem(const char* format, const char* menuItem, int row,
						 int col, int len, int status);
int iol_menuItem(const char* format, const char* menuItem, int row,
				 int col, int len, int* status);


#if OS == WINDOWS
   #define ESC_KEY 27
   #define ESCAPE_KEY 27
   #define UP_KEY 1072
   #define DOWN_KEY 1080
   #define LEFT_KEY 1075
   #define RIGHT_KEY 1077
   #define BS_KEY 8
   #define BACKSPACE_KEY 8
   #define DEL_KEY 1083
   #define DELETE_KEY 1083
   #define HOME_KEY 1071
   #define END_KEY 1079
   #define ENTER_KEY 13
   #define TAB_KEY 9
   #define INS_KEY 1082
   #define INSERT_KEY 1082
   #define PGUP_KEY 1073
   #define PGDN_KEY 1081
   #define F1_KEY 1059
   #define F2_KEY 1060
   #define F3_KEY 1061
   #define F4_KEY 1062
   #define F5_KEY 1063
   #define F6_KEY 1064
   #define F7_KEY 1065
   #define F8_KEY 1066
   #define F9_KEY 1067
   #define F10_KEY 1068
   #define F11_KEY 1133
   #define F12_KEY 1134
   #define CIO_TAB_SIZE 4
   #define IOL_TAB_SIZE 4
#elif OS == UNIX
   #define ESC_KEY 27
   #define UP_KEY 259
   #define DOWN_KEY 258
   #define LEFT_KEY 260
   #define RIGHT_KEY 261
   #define BS_KEY 263
   #define DEL_KEY 330
   #define HOME_KEY 362
   #define END_KEY 385
   #define ENTER_KEY 10
   #define TAB_KEY 9
   #define INS_KEY 331
   #define PGUP_KEY 339
   #define PGDN_KEY 338
   #define F1_KEY 261
   #define F2_KEY 266
   #define F3_KEY 267
   #define F4_KEY 268
   #define F5_KEY 269
   #define F6_KEY 270
   #define F7_KEY 271
   #define F8_KEY 272
   #define F9_KEY 273
   #define F10_KEY 274
   #define F11_KEY 275
   #define F12_KEY 276
   #define CIO_TAB_SIZE 4
#endif

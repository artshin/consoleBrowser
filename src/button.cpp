#include "button.h"
#include <string.h>

button::button(char *btname, char *cmd, char *errmsg, int row, int col, int errnum, int terminating, 
	Screen *scr, int(*task)(char *, int, Screen*)) :
    Field(btname, row, col, (scr && task) ? strlen(btname) : 0, strlen(btname))
{
	int i;
	scrr=scr;
	f_ReadOnly=0;
	b_name = btname;

	b_cmd = new char [strlen(cmd)+1];
	for (i = 0; cmd[i]!='\0';i++)
        b_cmd[i] = cmd[i];
	b_cmd[i]=0;

	b_errmsg = new char [strlen(errmsg)+1];
	for (i = 0; errmsg[i]!='\0'; i++)
        b_errmsg[i] = errmsg[i];
	b_errmsg[i]=0;
	
	b_row = row;
	b_col = col;
	b_errnum = errnum;
	b_term = terminating;
	b_id = rand() % 1000;
}

int button::edit()
{
	int key=0;
	iol_movecur(b_row,b_col+1);
	key=iol_getch();
	while (key==13) {
		if(b_name=="<BACK>")
			return -200;
		else if(b_name=="<FWD>")
			return -300;
		else if(b_name=="<HOME>")
			return -400;
		else if(b_name=="<QUIT>")
			return -500;
		else if(b_name=="<PARSE>")
			return -600;
		else if(b_name=="<GO>")
			return -700;
		key=iol_getch();
		b_edit=0;
	}
	return key;
}

char* button::data()
{
	return b_cmd;
}

int button::button_id()
{
	return b_id;
}

void button::add_screen(Screen *scr)
{
	scrr = scr;
	if(scrr && taskk )
	{
		b_edit=1;
	}


}

void button::add_task(int (*task)(char *, int, Screen*))
{
	taskk = task;
	if(scrr && taskk )
	{
		b_edit=1;
	}


}


button::~button()
{
	delete [] b_cmd;
	delete [] b_errmsg;
}


/*int main()
{
    /iol_init();
	char tmp[20];
	Screen scr;
	int key;

	button *ok;

	ok = new button("<ok>", "go back", "can't go back", 10, 20, 0, 1, &scr, 0);
	iol_clrscr();
	while (key!=13) {
		key=scr.edit();
	}
	//str,row,col,51,11
	return 0;
}*/
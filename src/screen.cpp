#include "screen.h"

Screen::Screen() {
	// Initialize all data members
	fieldnum=0;
	for (int i=0;i<80;i++) {
		field[i]=NULL;
		autodel[i]=false;
	}
}

Screen::~Screen() {
	// Destroy any autodeleted and/or dynamically allocated data
	for (int i=0;i<80;i++) {
		if (autodel[i])
			delete field[i];
	}
}

void Screen::del(Field *fptr) {
	for (int i=0;i<80;i++) {
		if (field[i]==fptr) {
			field[i]=NULL;
			delete fptr;
			fieldnum--;
		}
	}
}

int Screen::add(Field *fp, int autodelete=1) {
	for (int i=0;i<fieldnum+1;i++) {
		if (!field[i]) {
			if (fieldnum<79) {
				field[i]=fp;
				if (field[i]) {
					autodel[i]=autodelete;
					fieldnum++;
					return fieldnum+1;
				} else {
					return 0;
				}
				break;
			} else {
				cout << "Error: Cannot add more than 80 screens." << endl;
				return 0;
				break;
			}
		}
	}
	return 0;
}

void Screen::display(int fnum=0) {
	if (!fnum) {
		for(int i=0;i<fieldnum+1;i++) {
			if (field[i])
				field[i]->draw();
		}
	} else {
		if (field[fnum-1])
			field[fnum-1]->draw();
	}
}
		
int Screen::edit(int *fpnum=NULL, int clear=0) {
	int num=0, editnum=0, curfield=0, numeditable=0, numbers=0, curfield2=0;
	
	if (clear) {

	}
	display();
	if (fpnum&&*fpnum>0&&*fpnum<=80)
		num=*fpnum;

	int i=num;

	for (;i<80;i++) {
		if (!field[i])
			continue;
		if (field[i]->editable()) {
			curfield=i;
			editnum=field[i]->edit();
		}
		if (editnum==UP_KEY||editnum==LEFT_KEY||editnum=='`') {
			i--;
			while (!field[i]->editable()) {
				if (i>0)
					i--;
				else
					i=fieldnum-1;
			}
			i--;
		} else if (editnum==DOWN_KEY||editnum==TAB_KEY||editnum==RIGHT_KEY) {
			i++;
			while (!field[i]->editable()) {
				if (field[i]->editable())
					break;
				if (i<fieldnum-1)
					i++;
				else
					i=0;
			}
			if (i==fieldnum)
				i=0;
			i--;
		} else { 
			if (editnum)
				break;
		}
	}
	return editnum;
}

int Screen::locate(Field *fp) {
	for (int i=0;i<fieldnum+1;i++) {
		if (fp==field[i])
			return i;
	}

	return 0;
}
		
Field* Screen::fieldptr(int n) {
	if (field[n-1]) {
		if (n>0&&n<=80)
			return field[n-1];
	} else {
		return NULL;
	}

	return NULL;
}
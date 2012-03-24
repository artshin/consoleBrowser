#include <iostream>
#include "field.cpp"

using namespace std;

class Screen {
		Field *field[80];
		bool autodel[80];
		int fieldnum;
	public:
		Screen();
		~Screen();
		void del(Field*);
		int add(Field*, int);
		void display(int);
		int edit(int*,int);
		int locate(Field*);
		Field* fieldptr(int);
};
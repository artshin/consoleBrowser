#define Windows 1
#define Unix 2
#define OS Windows

#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex> 
#include "network.c"
#include "screen.cpp"
#include "button.cpp"
#include "textfield.cpp"

using namespace std;

class Browser {
		int sd;
		int cnt;
		string data;
		string info;
		string ip;
		string hostname;
		string dir;
		string filename;
		string ext;
		string parsed;
		string status;
		Screen *screen;
		Field *border;
		Field *title;
		Field *urltitle;
		Field *htmltitle;
		Field *statustitle;
		Field *urlbox;
		Field *urlbar;
		Field *statusbar;
		TextField *htmlbox;
		button *back;
		button *fwd;
		button *home;
		button *go;
		button *quit;
		button *parsing;
		vector<string> hhist;
		vector<string> dhist;
		string homehost;
		string homedir;
		int hloc;
		bool parsedata;
	public:
		Browser();
		Browser(const char*,const char*);
		Browser(string);
		~Browser();
		int surf();
		void init();
		void splitinput(string);
		bool fetch(const char *);
		void sethost(string);
		bool set_server(const char *);
		void details();
		void parse();
		void goback();
		void goforward();
		int gohome();
		int goweb();
		int redraw();
		void set_home_page(const char *home);
};

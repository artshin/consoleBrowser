class button:public Field
{
	string b_name;
	char *b_cmd, *b_errmsg;
	int b_row, b_col, b_errnum, b_term, b_id, b_edit;
	Screen *scrr;
	int (*taskk)(char *, int, Screen *);

public:
	button(char *btname, char *cmd, char *errmsg, int row, int col, int errnum, 
		int terminating, Screen *scr=NULL, int(*task)(char *, int, Screen*)=NULL);
	int edit();
	char* data();
	int button_id();
	void add_screen(Screen *scr);
	void add_task(int (*task)(char *, int, Screen*));
	virtual ~button();

};
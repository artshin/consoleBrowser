#include "iol.cpp"


class Field {
protected:
    string f_str;
    int f_col, f_row, f_fieldlen, f_maxdatalen,
    *f_insertmode, *f_offset, *f_curpos, f_IsTextEditor,
    f_ReadOnly;

public:
    Field(const char* str, int row, int col, int fieldlen, int maxdatalen,
	     int* insertmode=0, int* offset=0, int* curpos=0, int IsTextEditor=1,
	     int ReadOnly=1); // make default values
                            //rand( ) % 26 - return any value between 0 and 25
    virtual void draw( ) const;
    int draw(int row, int col, int l, int h,
	  char edge, char top_btm, char ls_rs) const;
    bool editable( ) const;
    virtual int edit( );
    string data( );
	void getdata(string data);
    virtual ~Field();
};


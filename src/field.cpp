#include "field.h"

Field::Field(const char* str, int row, int col, int fieldlen, int maxdatalen,
	     int* insertmode, int* offset, int* curpos, int IsTextEditor,
	     int ReadOnly){
	int i=0;
	f_str=str;
    f_row = row;
    f_col = col;
    f_fieldlen = fieldlen;
    f_maxdatalen = maxdatalen;
    f_insertmode = insertmode;
    f_offset = offset;
    f_curpos = curpos;
    f_IsTextEditor = IsTextEditor;
    f_ReadOnly = ReadOnly;

   // cout << "Entering field constructor" << endl;
    
}

void Field::draw() const{
    iol_display(f_str,f_row,f_col,f_fieldlen);
    
}

int Field::draw(int row, int col, int l, int h,
                char edge, char top_btm, char ls_rs) const{

    int row_end = l-1, arr_end = h-1,r,c;
    int middle = h/2;
    char** box;

	try {
		box = new char*[h];
		if (box) {
			for (int i=0; i < h; i++)
				box[i] = new char[l+1];
		} else {
			cerr << "Memory allocation for box(int Field::draw) failed" << endl;
			return 0;
		}
	}

	catch(bad_alloc) {
        cerr << "Memory allocation for box(int Field::draw) failed" << endl;
		return 0;
	}

    for(int i=0,j=0,k=0;i < h;j++){
		
        if ( (i == 0 || i == arr_end) &&
             (j == 0 || j == row_end) )
            box[i][j] = edge;

        else if ( (i == 0 || i == arr_end) && (j>0 && j<row_end) )
            box[i][j] = top_btm;

        else if ( (i!=0 && i!=arr_end) && (j==0 || j==row_end) )
            box[i][j] = ls_rs;

        else if (f_str[k] != '\0'){
			if (f_str[k]<0||f_str[k]>127)
				box[i][j]=' ';
			else
				box[i][j] = f_str[k];
            k++;
        }
        else
            box[i][j] = ' ';

        
        if (j==l-1){
			box[i][j+1]=0;
            i++;
            j=-1;
        }

    }

    for (int i = 0; i<h; i++,row++)
        iol_display(box[i],row,col,0);
	for (int i=0;i<h;i++) {
		delete [] box[i];
	}
    
    delete [] box;

    r = iol_rows(); c = iol_cols();

    return ( r-(row+h)>=0 && c-(col+l)>=0 ? 1:0 );
}

Field::~Field(){
}

bool Field::editable( ) const{
	if (!this)
		return 1;
	return f_ReadOnly?0:1;
}

int Field::edit( ){
    int a;
	if (f_ReadOnly == 0) {
		a = iol_edit(&f_str,f_row,f_col,f_fieldlen,f_maxdatalen,
                 f_insertmode,f_offset,f_curpos,f_IsTextEditor,f_ReadOnly);
	} else {
        a=0;
        draw();
    }
        

    return a;

}

string Field::data(){
    return f_str;
}

void Field::getdata(string data) {
	f_str=data;
}
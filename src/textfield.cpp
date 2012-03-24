#include "textfield.h"

TextField::TextField(const char *page, int row, int col, int width,
	  int height, char edge, char top_btm, char ls_rs) :
          Field(page,row,col,0,width){
	tf_edge = edge, tf_top_btm = top_btm, tf_ls_rs = ls_rs;
	tf_height = height;
	tf_width = width;
	offset = 0;
	f_ReadOnly=0;
	int spaces=0, d=1;

	border = new Field("",row-1,col-1,width+2,width+2);

	string temp;
	if (strlen(page)) {
		for(int i = 0,j = 0; page[j]; i++, d++){
			for (; temp.size()<tf_width&&page[j]; j++){
				if(page[j] != '\n' && page[j] != '\r' && page[j] != '\t') {
					if (page[j])
						temp += page[j];
				} else if (page[j] == '\t') {
					temp += "     ";
				} else if (page[j] == '\r') {
					continue;
				} else {
					j++;
					break;
				}
			}
			if(temp.size()>0) {
				if(temp[0] == ' ')
					temp.erase(0,1);
				if (temp.size()>0) {
					if (temp[temp.size()-1] != ' ' && temp.size()>=tf_width-2) { 
						int found=0,dif=0;
						found=temp.find_last_of(' ');
						dif=temp.size()-found;
						if (found!=string::npos&&dif>0) {
							temp.erase(found,dif);
							j-=dif;
						}
					}
				}
				for(int k=temp.size()-1;k<tf_width-1;k++)
					temp+=' ';
				f_str.push_back(temp);
			} else {
			}
			temp="";
			spaces=0;
					  
		}
		if (temp.size())
				f_str.push_back(temp);
	}
}

int TextField::edit() {
	int xPos = f_col+tf_width+2;
	int key = 0;
	int yPos;
	double perc;
	int rowsize=f_str.size();
	do {
		draw();
		offset ? perc=(tf_height)*(((double)offset/f_str.size())) : perc=0;
		(f_str.size()>0&&offset) ? yPos = f_row+perc : yPos=(f_row);
		iol_movecur(yPos,xPos);
	    key = iol_getch();
			switch(key){
			case LEFT_KEY:
				xPos--;
				break;
			case RIGHT_KEY:
				xPos++;
				break;
			case UP_KEY:
				if(offset>0)
					offset--;
				break;
			case DOWN_KEY:
				if(offset+tf_height<rowsize)
					offset++;
				break;
			case PGUP_KEY:
				if(offset>0)
					offset-=tf_height;
				if(offset<0)
					offset=0;
				break;
			case PGDN_KEY:
				if(offset<rowsize)
					offset+=tf_height;
				if(offset>rowsize-1)
					offset=rowsize-1;
				break;
			case HOME_KEY:
				if(offset>0)
					offset=0;
				break;
			case END_KEY:
				if(offset+tf_height<rowsize)
					offset=rowsize-tf_height;
				break;
			default:
				break;
			}
	} while(key == UP_KEY||key == DOWN_KEY||key==PGUP_KEY||key==PGDN_KEY||key==HOME_KEY||key==END_KEY);
	return key;
}


void TextField::draw() const{
	int yPos;
	double perc;
	offset ? perc=(tf_height)*(((double)offset/f_str.size())) : perc=0;
	(f_str.size()>0&&offset) ? yPos = f_row+perc : yPos=(f_row);
	for (int i=f_row;i<f_col+tf_height;i++)
		iol_display("|   |",i,f_col+tf_width,0);
	iol_display("+===+",f_row-1,f_col+tf_width,0);
	iol_display("+===+",f_col+tf_height,f_col+tf_width,0);
	iol_display("*===*",yPos-1,f_col+tf_width,0);
	iol_display("|(*)|",yPos,f_col+tf_width,0);
	iol_display("*===*",yPos+1,f_col+tf_width,0);
	if(f_str.size()) {
		for(int i = offset; i < tf_height+offset; i++) {
				if (i>f_str.size()-1)
					break;
				iol_display(f_str[i].c_str(),f_row+i-offset,f_col,0);
		}
	}
}
TextField::~TextField(){
	delete border;
}

void TextField::drawborder() {
	border->draw(f_row-1,f_col-1,tf_width+2,tf_height+2,tf_edge,tf_top_btm,tf_ls_rs);
}
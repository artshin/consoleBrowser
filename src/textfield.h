class TextField: public Field {
     char tf_edge, tf_top_btm, tf_ls_rs;
     int tf_height,tf_width;
	 vector<string> f_str;
	 int offset;
     //char **tf_line;
	 //string clearline;
	 //int numlinesx;
	 //int offset;
	 Field *border;
	 Field *scrollbar;
public:
    TextField(const char *page, int row, int col, int width,
		int height, char edge='+', char top_btm='-', char ls_rs='|');
    int edit( );
	void drawborder();
    /*bool editable( ) const;
    char* data( );*/
	void draw() const;
	//void clear();
     ~TextField();
};

/*
 * A TextField allows data to be displayed (but not altered) on several lines
bounded by a "box" containing a fixed number of rows and columns. A TextField
must have the following constructor and a virutal destructor.

TextField(char *page, int row, int col, int width,
	  int height, char edge='+', char top_btm='-', char ls_rs='|');
	  // note: default arguments
+ Used to create a TextField for displaying the contents of 'page' within
  the box bounded by 'edge', 'top_btm', and 'ls_rs'.
  The data within a TextField object may never be modified or altered in
  any way. Data is to be displayed on the screen a "line" amount at a time,
  where a "line" represents 'width' number of characters.
  After a "line" of data is displayed on the screen, additional characters are
  to be displayed starting on the next line. If a "word" cannot be displayed
  completely without breaking it up (because the right edge of the TextField
  has been reached, then it must be displayed in its entirety starting on the
  next line. A "word" is any sequence of non-blank (spaces, tabs or newlines)
  characters. If a "word" exceeds the entire width of a TextField, then only
  'width' number of characters will be displayed and the remaining characters
  displayed on the next line (breaking up the word in this case being
  unavoidable). If there is more data in the 'page' string than can fit within
  a TextField's area, then the remaining data will be "hidden" until the user
  chooses to uncover the data by "scrolling" through the TextField when
  the edit(...) function (see below) is called.

  Paremeters:
  'page' a null-terminated string representing the contents of the data to
   display on the screen within the TextField "box".
  'row' and 'col' represents the starting location (on the screen) of the
  TextField itself.
  'width' and 'height' represent the width and height of the box that will
  surround the contents of the data in 'page'.
  'width' is the maximum number of characters that can appear on any line.
  'height' is the maximum number of lines the box contains.
  'edge', 'top_btm', and 'ls_rs' are used to draw the bounding 'box' around
  the TextField (as in assignment #1)

A TextField has the following public (and possibly virtual) member functions:

int edit( );
+ Displays the TextField at the appropriate place on the screen
  (including the bounding box) and fills the box with the data in the
  null-terminated string 'page' according to the following guidelines:

Assume we have a variable:
char page[ ] =
"Once there lived a village of creatures along the bottom of a great crystal"
"river. The current of the river swept silently over them all - young and old,"
"rich and poor, good and evil, the current going its own way, knowing only"
"its own crystal self. Each creature in its own manner clung tightly to the"
"twigs and rocks of the river bottom, for clinging was their way of life, and"
"resisting the current what each had learned from birth."
"But one creature said at last, 'I am tired of clinging. Though I cannot see"
"it with my eyes, I trust that the current knows where it is going. I shall"
"let go, and let it take me where it will. Clinging I shall die of boredom'"
"The other creatures laughed and said, 'Fool! Let go and that current you"
"worship will throw you tumbled and smashed across the rocks, and you will"
"die quicker than boredom!' But the one heeded them not, and taking a breath"
"did let go, and at once was tumbled and smashed by the current across the rocks."
"Yet in time, as the creature refused to cling again, the current lifted him"
"free from the bottom, and he was bruised and hurt no more."
"And the creatures downstream, to whom he was a stranger cried, 'See a miracle!"
"A creature like ourselves, yet he flies! See the Messiah come to save us all!'"
"And the one carried in the current said, 'I am no more Messiah than you. The"
"river delights to lift us free, if only we dare let go. Our true work is this"
"voyage, this adventure.' But they cried the more, 'Saviour!' all the while"
"clinging to the rocks, and then when they looked again he was gone, and they"
"were left alone making legends of a Saviour. --Richard Bach--";

Then a TextField object created as:
TextField x(page, 5, 5, 50, 10);
x.edit( );

Would display 'x' below at coordinates 5,5 on the screen and would fill the
box with the following text:

 012345678901234567890123456789012345678901234567890123456789
0
1
2
3
4
5     +--------------------------------------------------+
6     |Once there lived a village of creatures along the |
7     |bottom of a great crystal river. The current of   |
8     |the river swept silently over them all - young and|
9     |old, rich and poor, good and evil, the current    |
10    |going its own way, knowing only its own crystal   |
11    |self. Each creature in its own manner clung       |
12    |tightly to the twigs and rocks of the river       |
13    |bottom, for clinging was their way of life, and   |
14    |resisting the current what each had learned from  |
15    |birth. But one creature said at last, 'I am tired |
16    +--------------------------------------------------+


The remaining data in 'page' would be "hidden" from the user's view.
To see the remaining data, the user would press the UP, DN, PGUP, or PGDN
keys. The cursor is initially to be placed in the top left corner of the
TextField and await keypresses:

  UP: Moves the cursor to the previous line in the TextField or does nothing
      if the cursor is already on the first line (scrolling when necessary).
  DN: Moves the cursor to the next line in the TextField or does nothing
      if the cursor is already on the last line (scrolling when necessary).
      Scrolling would only begin when the cursor is on the last line of the
      TextField and the DN key is pressed (assuming, of course, that there are
      additional lines of text to uncover).
PGUP: Displays the previous 'height' (number of rows) number of lines in the
      TextField or does nothing if there are no previous lines to display.
      If there are fewer than 'height' lines being hidden, then PGUP would
      uncover all lines and leave the cursor at line 1.
PGDN: As PGUP, but displays the next 'height' lines in the TextField.
HOME: Displays the first 'height' number of lines in the TextField.
END:  Displays the last 'height' number of lines in the TextField.

All other keys simply terminate editing returning their appropriate keycode.

For an example of what is required, please see <html> <textarea>
field below:
Once there lived a village of creatures along the bottom of a great crystal river. The current of the river swept silently over them all - young and old, rich and poor, good and evil, the current going its own way, knowing only its own crystal self. Each creature in its own manner clung tightly to the twigs and rocks of the river bottom, for clinging was their way of life, and resisting the current what each had learned from birth. But one creature said at last, 'I am tired of clinging. Though I cannot see it with my eyes, I trust that the current knows where it is going. I shall let go, and let it take me where it will. Clinging I shall die of boredom'. The other creatures laughed and said, 'Fool! Let go and that current you worship will throw you tumbled and smashed across the rocks, and you will die quicker than boredom!' But the one heeded them not, and taking a breath did let go, and at once was tumbled and smashed by the current across the rocks. Yet in time, as the creature refused to cling again, the current lifted him free from the bottom, and he was bruised and hurt no more. And the creatures downstream, to whom he was a stranger cried, 'See a miracle! A creature like ourselves, yet he flies! See the Messiah come to save us all!' And the one carried in the current said, 'I am no more Messiah than you. The river delights to lift us free, if only we dare let go. Our true work is this voyage, this adventure.' But they cried the more, 'Saviour!' all the while clinging to the rocks, and then when they looked again he was gone, and they were left alone making legends of a Saviour. --Richard Bach--


bool editable( ) const;
+ Always returns true since TextField's are considered to be 'editable'

char* data( );
+ Returns a pointer to the data stored in the TextField.
*/
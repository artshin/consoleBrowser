#include "browser.h"

Browser::Browser() {
	sd=0;
	cnt=0;
	data="";
	info="";
	status="";
	ip="0.0.0.0";
	hostname="localhost";
	dir="/";
	filename="index.html";
	ext=".html";
	parsed="";
	init();
}

Browser::Browser(const char *host_name, const char *html_page) {
	sd=0;
	cnt=0;
	data="";
	info="";
	status="";
	ip="0.0.0.0";
	hostname=host_name;
	dir=html_page;
	if (dir.find(".")!=std::string::npos) { // Separate the directory name and the hostname
		ext=dir;
		ext.erase(0,dir.find("."));
	} else {
		ext=".html";
	}
	filename=dir;
	if (filename.find("/")!=std::string::npos)
		filename.erase(0,1);
	do {
		if (dir.find("/")!=std::string::npos) { // Separate the directory name and the hostname
			filename.erase(0,filename.find("/")+1);
		} else {
			filename="index.html";
		}
	} while (filename.find("/")!=std::string::npos);
	if (filename=="")
		filename="index.html";
	parsed="";
	init();
	set_server(hostname.c_str());
}

Browser::Browser(string website) {
	sd=0;
	cnt=0;
	data="";
	info="";
	status="";
	ip="0.0.0.0";
	parsed="";
	init();
	splitinput(website);
	set_server(hostname.c_str());
}

void Browser::init() {
	parsedata=false;
	set_home_page("senecacollege.ca");
	hloc=-1;
	screen = new Screen;
	border = new Field("",2,6,72,500);
	title = new Field("SENECA OOP344 WEB BROWSER",3,8,25,25);
	urltitle = new Field("URL://",5,22,6,6);
	htmltitle = new Field("HTML",7,9,4,4);
	statustitle = new Field("STATUS",20,8,6,6);
	urlbox = new Field("",4,29,40,42);
	urlbar = new Field("",5,30,39,1024,0,0,0,0,0);
	statusbar = new Field("",20,16,40,40);
	htmlbox = new TextField("",9,9,60,10,'+','-','|');
	back = new button("<BACK>", "go back", "can't go back", 4, 8, 0, 1, screen, 0);
	fwd = new button("<FWD>", "go forward", "can't go forward", 4, 16, 0, 1, screen, 0);
	home = new button("<HOME>", "go home", "can't go home", 4, 23, 0, 1, screen, 0);
	go = new button("<GO>", "go", "can't go", 5, 72, 0, 1, screen, 0);
	quit = new button("<QUIT>", "quit", "can't quit", 21, 8, 0, 1, screen, 0);
	parsing = new button("<PARSE>", "parse", "can't parse", 5, 8, 0, 1, screen, 0);
	screen->add(title);
	screen->add(urltitle);
	screen->add(htmltitle);
	screen->add(statustitle);
	screen->add(statusbar);
	screen->add(back);
	screen->add(fwd);
	screen->add(home);
	screen->add(parsing);
	screen->add(urlbar);
	screen->add(go);
	screen->add(htmlbox,1);
	screen->add(quit);
}

Browser::~Browser() {
	delete screen;
	if (sd)
		net_stop(sd);
}

void Browser::splitinput(string website) {
	if (website.find("/")!=std::string::npos) { // Separate the directory name and the hostname
		dir=website;
		dir.erase(0,dir.find("/"));
		website.erase(website.find("/"),website.length()-website.find("/"));
	} else {
		dir="/";
	}

	filename=dir;
	if (filename.find("/")!=std::string::npos)
		filename.erase(0,1);
	do {
		if (dir.find("/")!=std::string::npos) { // Separate the directory name and the hostname
			filename.erase(0,filename.find("/")+1);
		} else {
			filename="index.html";
		}
	} while (filename.find("/")!=std::string::npos);
	if (filename=="")
		filename="index.html";
	hostname=website;
	if (dir.find(".")!=std::string::npos) { // Separate the directory name and the hostname
		ext=dir;
		ext.erase(0,dir.find("."));
	} else {
		ext=".html";
	}
}

bool Browser::set_server(const char *host_name) {
	hostname=host_name;
	status="Connecting...";
	if (sd)
		net_stop(sd);
	net_start();
	sd = net_socket();
	if (sd) {
		ip = get_ip(hostname.c_str());
		cnt = net_connect(sd);	
	}
	else
		return false;
	if (!cnt) {
		status="Error Connecting to Server";
		if (hostname!="localhost")
			cout << "Error: Could not connect to: " << ip << endl; // If it didn't connect properly, send us the type of error
		return false;
	}

	screen->display();
	return true;
}

bool Browser::fetch(const char *web_page) {
	int i=0, j=3;
	char buf;
	bool initinfo=0, warning=false, redirect=false, dofetch=true;
	stringstream datastream;
	string getstr;
	dir=web_page;
	// Make sure the "GET" string gives the server enough information to let us in
	if (dir.find(".")!=-1) {
		if ((dir.find(".html")!=-1)||(dir.find(".htm")!=-1)||(dir.find(".php")!=-1)||
		(dir.find(".pl")!=-1)||(dir.find(".asp")!=-1)||(dir.find(".c")!=-1)||
		(dir.find(".cpp")!=-1)||(dir.find(".cgi")!=-1)||(dir.find(".txt")!=-1)) {
			dofetch=true;
		} else {
			dofetch=false;
		}
	} else {
		dofetch=true;
	}
	do {
		getstr = "GET ";
		getstr += dir;
		getstr += " HTTP/1.1\r\n";
		getstr += "Host: ";
		if (!warning)
			getstr += ip;
		else
			getstr += hostname;
		getstr += "\r\n";
		getstr += "Connection: close\r\n";
		getstr += "User-Agent: Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US; rv:1.8.1.3) Gecko/20070309 Firefox/2.0.0.3\r\n";
		getstr += "Accept: text/xml,application/xml,application/xhtmlgetstr+=xml,text/html;q=0.9,text/plain;q=0.8,image/png,*/*;q=0.5\r\n";
		getstr += "Accept-Language: en-us;q=0.5,en;q=0.3\r\n";
		getstr += "Accept-Charset: ISO-8859-1,utf-8;q=0.7,*;q=0.7\r\n\r\n";
		net_send(getstr.c_str(),sd);
		do {
			if (initinfo==0) {
				if (datastream.str().find("<")!=std::string::npos) { // Correctly separate the info and html data
					initinfo=1;
					info=datastream.str();
					info.erase(info.length()-4,4);
					datastream.seekp(0);
					datastream << "<";
				}
			}
			buf=net_recieve(sd);
			datastream << buf;

		   if (buf)
			   i++;
		} while(buf!=-1);

		data=datastream.str(); 
		if (data[data.size()-1] == -1)
			data.erase(data.size()-1,1);
		system("@ECHO OFF\nmkdir cache");
		if (dir!="/") {
			std::string temp="cache/" + filename;
			ofstream ofs(temp.c_str());
			ofs << data;
		} else {
			ofstream ofs("cache/index.html");
			ofs << data;
		}
		
		if (data.find("</html>")!=std::string::npos)
			data.erase(data.find("</html>")+7,data.length()-data.find("</html>")); // Erase any junk after the end of the page

		if ((data.find("<")==std::string::npos && data.find(">")==std::string::npos)
			|| (info.find("200 OK")==std::string::npos)) { // Search for error message
			warning=true;
			status="Error retrieving information";
		} else {
			warning=false;
			status="Connected";
		}

		if ((info.find("301 Moved")!=std::string::npos)||
			(data.find("301 Moved")!=std::string::npos)) {
			int found,found2;
			string temp;
			found=info.find("Location: ")+17;
			found2=info.find("\n",found-1);
			for (int i=found;i<found2;i++)
				temp+=info[i];
			splitinput(temp);
			redirect=true;
		}

		if (j!=3)
			warning=false;
		if (warning) {
			// If there's a warning, let's reset and try again with the hostname instead of the IP Address
			datastream.seekp(0);
			datastream.clear();
			initinfo=0;
			info="";
			data="";
			j--;
			
			if (sd)
				net_stop(sd);
			net_start();
			sd = net_socket();
			if (sd)
				cnt=net_connect(sd);
			if (!cnt)
				warning=false;
		}
	} while (warning);
	if (!dofetch) {
		data="";
	}
	if (j!=3)
		return false;
	else
		return true;
}

void Browser::details() {
	cout << endl
		 << "Network Details: " << endl << "-----------------" << endl;
	cout << "Address: http://" << hostname;
	if (dir!="/")
		cout << dir;
	cout << endl << "IP: " << ip << endl << endl
		 << "Website Details: " << endl << "-----------------" << endl << info << endl << endl
		 << "Website Data: " << endl << "-----------------" << endl << data << endl << endl
		 << "Parsed Data: " << endl << "-----------------" << endl << parsed << endl;  
}

void Browser::sethost(string host) {
	hostname=host;
}

void Browser::parse() {
	tr1::cmatch res;
	string temp;
	bool nextword=false, nextline=false;
    int pos=0, pos2=0, i=0;
	parsed=data;
	/*tr1::regex rx("<script>(.*)</script>");
	std::string fmt("TESTING");*/
	//parsed = tr1::regex_replace(parsed,rx,fmt);*/
    /*tr1::regex rx2("[ ]+");
	std::string fmt2(" ");
	parsed = tr1::regex_replace(parsed,rx2,fmt2);*/
	pos = parsed.find("<head>");
	pos2 = parsed.find("</head>");
	if (pos!=-1&&pos2!=-1)
		parsed.erase(pos,pos2-pos+7);
	while(parsed.find("<script>")!=string::npos) {
		pos = parsed.find("<script>");
		pos2 = parsed.find("</script>");
		if (pos!=-1&&pos2!=-1)
			parsed.erase(pos,pos2-pos+9);
	}
    tr1::regex rx("<(.*)>");
	std::string fmt("\0");
	parsed = tr1::regex_replace(parsed,rx,fmt);
	while (i<parsed.size()) {
		for (;i<parsed.size();i++) {
			if (parsed[i]>32&&parsed[i]<127) {
				if (nextword) {
					temp+=' ';
					nextword=false;
				}
				if (nextline) {
					temp+='\n';
					nextline=false;
				}
				temp+=parsed[i];
			} else if (parsed[i]=='\n') {
				nextline=true;
			} else {
				nextword=true;
			}
		}
	}
	while (temp[0]==' ' || temp[0]=='\r' || temp[0]=='\t' || temp[0]=='\n')
		temp.erase(0,1);
	parsed=temp;
}

int Browser::surf() {
	int key=-1, temp=0, loc=0;
	iol_init();
	border->draw(2,6,72,21,'o','-','|');
	htmlbox->drawborder();
	statusbar->getdata(status.c_str());
	loc=screen->locate(urlbar);
	urlbox->draw(4,29,42,3,'+','-','|');
	//hloc++;
	//hhist.push_back(hostname);
	//dhist.push_back(dir);
	key=screen->edit(&loc);
	do {
		if (key==13||key==-700||key=='g') {
			hostname=urlbar->data();
			key=goweb();
			if (key<0)
				continue;
			hloc++;
			hhist.push_back(hostname);
			dhist.push_back(dir);
			loc=screen->locate(htmlbox);
		} else if (key==-200||key=='b') {
			goback();
			loc=screen->locate(back);
		} else if (key==-300||key=='f') {
			goforward();
			loc=screen->locate(fwd);
		} else if (key==-400||key=='h') {
			key=gohome();
			loc=screen->locate(htmlbox);
		} else if (key==-500||key=='q'||key==27) {
			break;
		} else if (key==-600||key=='p') {
			parsedata=!parsedata;
			redraw();
			loc=screen->locate(htmlbox);
		} else if (key=='r') {
			loc=screen->locate(urlbar);
		}
		key=screen->edit(&loc);
	} while (key!=-500&&key!='q'&&key!=27);
	iol_end();
	return 0;
}

int main() {
	iol_clrscr();
	Browser browser;
	browser.surf();
	return 0;
}

void Browser::goforward() {
	if (hloc<hhist.size()-1) {
		hloc++;
		hostname=hhist[hloc];
		dir=dhist[hloc];
		urlbar->getdata(hostname+dir);
		goweb();
	}
}

void Browser::goback() {
	if (hloc>0) {
		hloc--;
		hostname=hhist[hloc];
		dir=dhist[hloc];
		urlbar->getdata(hostname+dir);
		goweb();
	}
}

int Browser::gohome() {
	int key=0;
	hostname=homehost;
	dir=homedir;
	urlbar->getdata(hostname+dir);
	key=goweb();
	return key;
}

int Browser::goweb() {
	int key=0;
	set_server(hostname.c_str());
	splitinput(hostname);
	if (cnt) {
		fetch(dir.c_str());
		parse();
	}
	key=redraw();
	return key;
}

int Browser::redraw() {
	int key=0,loc=0;
	iol_clrscr();
	border->draw(2,6,72,21,'o','-','|');
	screen->del(htmlbox);
	if (!parsedata)
		htmlbox = new TextField(data.c_str(),9,9,60,10,'+','-','|');
	else
		htmlbox = new TextField(parsed.c_str(),9,9,60,10,'+','-','|');
	screen->add(htmlbox,1);
	statusbar->getdata(status.c_str());
	urlbox->draw(4,29,42,3,'+','-','|');
	htmlbox->drawborder();
	loc=screen->locate(htmlbox);
	return key;
}

void Browser::set_home_page(const char *home) {
	string temp=home;
	if (temp.find("/")!=std::string::npos) { // Separate the directory name and the hostname
		homedir=home;
		homedir.erase(0,homedir.find("/"));
		temp.erase(temp.find("/"),temp.length()-temp.find("/"));
	} else {
		homedir="/";
	}
	homehost=temp;
}
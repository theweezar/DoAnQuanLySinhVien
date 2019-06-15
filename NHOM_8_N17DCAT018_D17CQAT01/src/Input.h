void KeyPress_1(int &cur, int &from, int &to, int &page, int maxlen, bool &reload, bool &press, bool &move, bool &esc);
void KeyPress_2(int &cur, int &pre, int &from, int &to, int &page, int maxlen, bool &press, bool &move, bool &esc, bool &enter);
void InputString(int x, int y, int x_e, int y_e, int len, string &tmp, bool check_0_9, bool &esc);
void InputGender(int x, int y, int &gender, bool &esc);
void InputNumber(int x, int y, int x_e, int y_e, int &var, int maxlen, bool not_null, bool &esc);
void InputScore(int x, int y, float &diem);
void InputNienKhoa(int x, int y, string &nk, bool &esc);
void ReadString(fstream &f, string tmp, char label);
void RemoveSpace(string &tmp,bool athead);
void ToUpper(string &tmp);
void ConvertName(string &name);
bool file_exist(const char *link);
bool Yes();
void Pause();
bool check_max_length(string tmp, int length);

void KeyPress_1(int &cur, int &from, int &to, int &page, int maxlen, bool &reload, bool &press, bool &move, bool &esc){
	char c; // Lay ds mon hoc lam` vi du.
	c = getch();
	if (c == 0){
		c = getch();
		if (c == 59){ // F1: Them Mon Hoc
			cur = 1; press = true;
		}
		if (c == 60){ // F2: Dieu Chinh mon hoc
			cur = 2; press = true;
		}
		if (c == 61){ // F3: Xoa mon hoc
			cur = 3; press = true;
		}
		if (c == 62){ // F4: Tim mon hoc va` show ra
			cur = 4; press = true;
		}
		if (c == 63){ // F5:
			cur = 5; press = true;
		}
		if (c == 64){ // F6
			cur = 6; press = true;
		}
	}
	if (c == -32){
		c = getch();
		if (c == 75){ // left arrow - Lui
			if (from != 0){ // Neu from = 0 thi` ko can` phai~ chuyen~ trang
				move = true;
				to = from;
				page--;
			}
			if (from - 10 < 0){ // Neu dang o~ trang dau tien thi` ko can` phai~ thay doi~ thong so
				from = 0;
			}
			else from -= 10;
		}
		if (c == 77){ // right arrow - Tien
			if (to != maxlen){ // Neu to van~ con` co` the~ tien toi thi` tiep tuc 
				move = true;
				from = to;
				page++;
			} 
			// vd: from = 0, to = 10, in ra array tu 0->9, thi minh chi can gan from = to se` in ra bat dau o ptu~ 10
			if (to + 10 > maxlen){ // Neu to+10 > do dai ds thi` set to = max length cua~ ds
				to = maxlen;
			}
			else to += 10; // neu ko thi` to += 10
		}
	}
	if (c == 27) esc = true;
}

void KeyPress_2(int &cur, int &pre, int &from, int &to, int &page, int maxlen, bool &press, bool &move, bool &esc, bool &enter){
	char c; 
	c = getch();
	if (c == -32){
		c = getch();
		if (c == 75){ // left arrow - Lui
			if (from != 0){ // Neu from = 0 thi` ko can` phai~ chuyen~ trang
				move = true;
				to = from;
				page--;
			}
			if (from - 10 < 0){ // Neu dang o~ trang dau tien thi` ko can` phai~ thay doi~ thong so
				from = 0;
			}
			else from -= 10;
		}
		if (c == 77){ // right arrow - Tien
			if (to != maxlen){ // Neu to van~ con` co` the~ tien toi thi` tiep tuc 
				move = true;
				from = to;
				page++;
			} 
			// vd: from = 0, to = 10, in ra array tu 0->9, thi minh chi can gan from = to se` in ra bat dau o ptu~ 10
			if (to + 10 > maxlen){ // Neu to+10 > do dai ds thi` set to = max length cua~ ds
				to = maxlen;
			}
			else to += 10; // neu ko thi` to += 10
		}
		if (c == 72){ // up arrow
			pre = cur--; press = true;
		}
		if (c == 80){ // down arrow
			pre = cur++; press = true;
		}
	}
	if (c == 27) esc = true;
	if (c == 13) enter = true;
}

void InputString(int x, int y, int x_e, int y_e, int len, string &tmp, bool check_0_9, bool &esc){
	Cursor(true);
	char c; bool max = false, empty = false; 
	gotoxy(x,y);
	x = x - tmp.size(); 
	// Cai nay dung cho phan` edit, vi` khi edit string tmp co gia tri. vd: khi nhap 1 sv moi chang~ han. thi` tmp.size = 0
	// va` x gui~ vo la` 5 (Diem bat dau ghi cua~ con tro~), thi` khi b�o loi~ con tro~ se~ nhay~ lai. cho~ cu~ 5+len=5+40=45. 
	// Nhung neu cho tmp = "duc" thi` khi gui~ vao` x = 8 de~ cho con tro vi tri hien tai. sau chu~ "duc"
	// va` neu bao loi~ = 8 + 40 = 48 la` sai, vi` cho~ cu~ mac dinh la` 45. Nen ta phai~ cho 8 - tmp.size = 8-3 = 5
	string e1 = "KHONG DUOC BO TRONG";
	string e2 = "KHONG THE NHAP DUOC NUA";
	while(true){
		c = getch();
		if (c == 13){ // enter - bao loi khong duoc bo trong
			if (tmp.size() > 0) break;
			else{
				empty = true;
				drawText(x_e - e1.size()/2,y_e,e1,RED);
				gotoxy(x,y); // vi bo~ trong thi` chi~ can tro lai vi tri ban dau
			}
		}
		if (c == 8){ // backspace - x�a 
			if (tmp.size() != 0){
//				tmp.replace(tmp.size()-1,1,""); // Uncomment dong` nay` neu ban. chua~ them '-std=c++11'
				tmp.erase(tmp.size()-1,1);		// erase cung~ co the xoa string
//				tmp.pop_back(); 				// Neu bao loi~ dung` lenh tren
				printf("\b \b");
				// Khi dang o~ trang. th�i string maxlen th� khi x�a di k� tu cuoi c�ng, th� se~ x�a b�o loi~
				if (max){ // khi xoa di thi` xoa dong bao loi~
					clearRect(x_e - e2.size()/2,y_e,e2.size(),1); // xoa bao loi~
					gotoxy(x+tmp.size(),y); // tro ve cho~ bi xoa
					max = false;
				}
			}
		}
		if (c == 27){ // escape = back
			esc = true;
			clearRect(x_e - 20,y_e,40,1); // xoa bao loi~
			return;
		}
		if (c == -32 || c == 0){ // da~ fix dc BUG gay bat phim arrow
			c = getch(); continue;
			// trong if nay`, ta de~ them 1 dong` c = getch() la` vi` neu c == -32 or 0 thi` n� se~ tu. dong. getch them 1
			// lan nua~ khi lap lai. vong loop nay` va` cai c = getch() o~ dau` se~ bat nham` ph�m => gay loi~
		}
		if(!check_max_length(tmp,len)){ // Neu string n�y chua dat. toi gioi han. max th� se~ tiep tuc. push_back 
			if (c != 8 && c != 13 && c >= 32){ 
			// nut backspace && enter no cung~ pusb_back dc,v� nhung~ ki tu nho~ hon 32 
			// se~ lam` sai dieu kien bao loi va` in sai 
				if (!check_0_9){ // Neu ko kich hoat che do nhap string kieu number th� c� the nhap toan bo ki tu v�o
					if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c >= '0' && c <= '9'){ // 32 = SPACE
						// ko dc nhap ki tu dac biet nhu ; . ' " ? /
						tmp.push_back(c);
						printf("%c",c);	
					}
					if (c == 32 && tmp.size() > 0){
						tmp.push_back(c);
						printf("%c",c);
					}
				}
				//!check_0_9 && c >= '0' && c <= '9' || c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z'
				else{
					if (c >= '0' && c <= '9'){
						tmp.push_back(c);
						printf("%c",c);
					}
				}
				if (empty){ // vi` khi nhap 1 ki tu nao` do thi` no se~ tu dong xoa bao loi empty di
					empty = false;
					clearRect(x_e - e1.size()/2,y_e,e1.size(),1);
					if (tmp.size() != 0) gotoxy(x+1,y);
					else gotoxy(x,y); 
					// x+1 la` vi` khi tmp.size() = 0, thi` khi 1 char duoc push vao`, thi` tmp.size() = 1
					// dong nghia voi viec 1 ki tu duoc in ra, va` ki tu do duoc ghi o~ (x,y)
				} // lam nhu the nay` de~ no clearRect 1 lan thoi
			}
		}
		else { // Khi string da~ du~ do. d�i m� c�n nhap. them th� se~ kich hoat. b�o loi~ max = true
			max = true;
			drawText(x_e - e2.size()/2,y_e,e2,RED);
			gotoxy(x+len,y); // (10+1+17) la cai x co dinh, + len la vi tri max o cuoi string
		}
		
	}
	clearRect(x_e - 20,y_e,40,1); // xoa tat ca~ thong bao loi~
	Cursor(false);
}
void InputGender(int x, int y,int &gender, bool &esc){
	gotoxy(x,y); Cursor(true);
	char c; string tmp;
	if (gender == 1) tmp = "1"; // Dung` cho ham` edit sinh vien
	else if (gender == 0) tmp = "0";
	else tmp = "";
	while(true){
		c = getch();
		if (tmp.size() == 1){ // Khi string tmp c� do dai` == 1 thi` se~ ko dc push_back them nua~
			if (c == 8){
				if (tmp.size() != 0){
					tmp.replace(tmp.size()-1,1,"");
					printf("\b \b");
				}
			}
			if (c == 13) break;
		}
		else{
			if (c == '1' || c == '0'){
				tmp.push_back(c);
				printf("%c",c);
			}
		}
		if (c == 27){ // escape = back
			esc = true;
			return;
		}
	}
	if (tmp == "1") gender = 1;
	if (tmp == "0") gender = 0;
	Cursor(false);
}

void InputNumber(int x, int y, int x_e, int y_e, int &var, int maxlen, bool not_null, bool &esc){
	gotoxy(x,y); Cursor(true);
	int len = (var == 0 ? 0:1+floor(log10(var))); // do dai cai chuoi~ so moi vua` truyen` v�o
	x = x - len; // x = x - len l� v� d�ng cho nhung~ lan` gotoxy ve` cho~ cu~ khi da~ b�o loi~
	char c; // var = 0;
	bool empty = false, max = false;
	string e1 = "KHONG DUOC BO TRONG", e2 = "SO LUONG QUA LON";
	while(true){ // co the bi sai || chua xong, viet tiep di
		c = getch();
		if (c == 13){ // enter
			if (!not_null) break; // neu ko bat. che do kiem tra bo~ trong th� se~ break ngay ca~ khi
			// var da~ == 0 tu` khi truyen v�o r, v� da~ dinh nghia~ const struct m� c�c bien int = 0
			else {
				if (not_null && var != 0) break;
				else{
					empty = true;
					drawText(x_e - e1.size()/2,y_e,e1,RED);
					gotoxy(x,y);
				}
			}
		}
		if (c == 8 && len > 0) { // Backspace - x�a. Neu var != 0, vd var = 85 -> var = int(85/10) = 8, do d�i giam~
			var /= 10; len--;
			printf("\b \b");
			if (max){ // Neu len dang max th� khi giam~ di gia tri. th� se~ set max = false v� x�a b�o loi~
				max = false;
				clearRect(x_e - 20,y_e,40,1); // xoa bao loi~
				gotoxy(x+maxlen-1,y); // 5 chu so (qua gioi han), khi xoa di 1 chu so thi` con 4 nen x + 4 
			}
		}
		if (c == 27){ // escape = back
			esc = true;
			clearRect(x_e - 20,y_e,40,1); // xoa bao loi~
			return;
		}
		if (c >= '0' && c <= '9' && len < maxlen){ // Bam phim 8 v� var = 0 -> var = 0*10 + 8 = 8
			var = var * 10 + (int(c) - 48); len++; // Bam phim 5 v� var = 8 -> var = 8*10 + 5 = 85
			printf("%c",c);
			if (empty){ // Neu c� bat che do kiem tra bo~ trong th� khi enter m� var = 0 th� empty se~ dc set = true
						// N�n khi nhap 1 gi� tri. n�o v�o th� empty se~ dc set lai. = false
				empty = false;
				clearRect(x_e - 20,y_e,40,1); // xoa bao loi~
				gotoxy(x+1,y);// Dang de~ khi ma` them 1 chu so vao` thi` khi xoa bao loi~, phai~ tro~ ve` x + 1
			}
		}
		else if (len == maxlen){ // Neu hien tai do. dai` cua~ chuoi so dang == 5 thi` khi nhap tiep tuc se~ bao loi~
			max = true;
			drawText(x_e - e2.size()/2,y_e,e2,RED);
			gotoxy(x+maxlen,y); // ve lai vi tri max cua~ chuoi~ so
		}
	}
	clearRect(x_e - 20,y_e,40,1); // xoa bao loi~
	Cursor(false);
}

void InputScore(int x, int y, float &diem){ // ko dc an ESC, chi ENTER v� luu lai.
	gotoxy(x,y); Cursor(true);
	char c;
	bool dot = false; // dot l� dau " . " -> so thap phan = false
	string d;
	if (diem < 10){
		if (diem - floor(diem) == 0) d.push_back(char(48+diem)); // vd: truyen v�o diem = 0 -> d = "0"
		else{// vd: truyen v�o diem = 6.5; d = ""
			d.push_back(char(floor(diem)+48)); //floor(6.5) = 6 -> 48 + 6 = "6" ->  d = "6"
			d.push_back('.');					// d = "6."
			d.push_back(char((diem - floor(diem))*10 + 48)); // (6.5 - floor(6.5)) x 10 = 0.5 x 10 = 5 -> 48 + 5 = "5" -> d = "6.5"
		} 
	}
	else d = "10";
	while(true){
		c = getch();
		if (c >= '0' && c <= '9'){
			if (!dot){    // neu ko phai so thap phan
				if (d.size() == 0){
					d = ""; d.push_back(c); // d = "1" .... "9"
					printf("%c",c);
				}
				else if (d == "1" && c == '0'){ // TH: d = "1" th� chi~ c�n c� TH d = "10", neu ko c� c == '0' th� d co the = "14","18",...
					d = "10"; printf("%c",c);
				}
			}
			else{
				if (d.size() < 3){
					d.push_back(c);
					printf("%c",c);
				}
			}
		}
		if (c == 46 && !dot && d != "10"){ // neu dot == true th� ko push back, tranh gay loi~
			dot = true;
			d.push_back(c); // push back dau '.'
			printf("%c",c);
		}
		if (c == 8 && d.size() != 0){
			if (d[d.size()-1] == 46) dot = false;
			d.erase(d.size()-1,1);
			printf("\b \b");
		}
		if (c == 13){ // enter
			if (d.size() == 0) d = "0";
			break;
		}
	}
	
	if (!dot){ // d ko phai~ l� so thap. phan
		diem = (d != "10" ? float(d[0]) - 48:10);
		// neu d == "10" th� diem = 10, ko th� nhu InputNumber
	} 
	else{ // TH: dot = true
		if (d[0] == '.'){ // TH: string d = ".75" -> diem = 0.75 | d = ".5" -> diem = 0.5
			diem = 0;
			for(int i = 1; i < d.size(); i++){
				diem += (float(d[i]) - 48) / pow(10,i);
			}
		}
		else{
			diem = (d[d.size()-1] == 46 ? float(d[0]) - 48 : float(d[0])-48 + (float(d[d.size()-1])-48)/10); // 45 = ' . '
			// if d == "8." th� diem = 8
			// else d == "8.5" th� diem = 8 + 5/10 = 8.5
		}
	}
	Cursor(false);
}

void InputNienKhoa(int x, int y, string &nk, bool &esc){
	Cursor(true);
	time_t now = time(0);
	tm *tg = localtime(&now);
	int yf, yt, ynow, ylast; // year from - year to, nam bat dau: 2019, nam toi da: 2099 
	char c, cyf[4], cyt[4];
	yf = ynow = 1900 + tg->tm_year; 
	yt = yf + 1;
	ylast = 2099;
	gotoxy(x+12,y); printf("%c",18);
	while(true){
		drawNumber(x,y,yf,WHITE);
		drawText(x+4,y,"-",WHITE);
		drawNumber(x+5,y,yt,WHITE);
		c = getch();
		if (c == -32 || c == 0){
			c = getch();
			if (c == 72){ // Up
				if (yf < ylast){
					yf++; yt++;
				}
			}
			if (c == 80){ // Down
				if (yf > ynow){
					yf--; yt--;
				}
			}
		}
		if (c == 13){ // enter
			nk = "";
			itoa(yf,cyf,10);
			itoa(yt,cyt,10);
			for(int i=0;i<4;i++) nk.push_back(cyf[i]);
			nk.push_back('-');
			for(int i=0;i<4;i++) nk.push_back(cyt[i]);
			break;
		}
		if (c == 27){
			esc = true;
			break;
		}
	}
	Cursor(false);
	clearRect(x+12,y,1,1);
}

void ToUpper(string &tmp){
	for(int i=0;i<tmp.size();i++) tmp[i] = char(toupper(tmp[i]));
}

void ConvertName(string &name){
	
}

void ReadString(ifstream &f, string &tmp, char label){
	fflush(stdin);
	getline(f,tmp,label);
	for(int i=0;i<tmp.size();i++){ // isspace la` ham` bool kiem tra xem ki tu do co phai~ WHITESPACE hay ko
		if (isspace(tmp[i])) tmp.erase(0,1); // Do` toi khi cham. duoc 1 ki tu thay vi khoang trang
		else break;
	}
}

void RemoveSpace(string &tmp,bool athead){ // athead nghia~ la` chi~ xoa nhung~ thang space dau tien, con ko thi xoa het space
	if (athead){
		int slxoa = 0;
		for(int i=0;i<tmp.size();i++){
			if (!isspace(tmp[i])) break; 
			else slxoa++;
			// N�u char i ko phai~ l� khoang~ trang th� slxoa++, n�u nhu char i l� 1 k� tu. ngay lan` dau tien th� break
		}
		tmp.erase(0,slxoa); // x�a slxoa k� tu. bat dau tu` char[0] 
	}
	else{
		for(int i=0;i<tmp.size();i++){
			if (isspace(tmp[i])){
				tmp.erase(i,1);
				i=-1; // Tai. sao i ko = 0 m� l� -1. V� khi vong lap duoc lap. lai. thi` i++ => i = 0
			}
		}
	}
}

bool file_exist(const char *link){
	fstream f(link);
	if (!f) return false;
	else return true;
}

bool Yes(){
	char c;
	while(true){
		c = getch();
		if (c == 'y' || c == 'Y') return true;
		else if ( c == 'n' || c == 'N') return false;
	}
}

void Pause(){
	char c;
	c = getch();
	if (c == -32 || c == 0) c = getch();
}

bool check_max_length(string tmp, int length){
	if (tmp.size() == length) return true;
	else return false;
}

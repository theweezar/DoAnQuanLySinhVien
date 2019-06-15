#ifndef SINHVIEN_H
#define SINHVIEN_H
typedef struct{
	string mssv; // unique
	string ho_tdem;
	string ten;
	int gender;
	string sdt;
	string malop;
}SINHVIEN;

const SINHVIEN null_sv = {"","","",-1,"",""};

struct nodesv{
	SINHVIEN sv;
	nodesv *next;
};
typedef struct nodesv NODESV;

class dssv_tamthoi{ // Thay cho vector
	private:
		SINHVIEN *ds_tt;
		int max;
		int length;
	public:
		dssv_tamthoi(int length_in){
			ds_tt = new SINHVIEN[length_in];
			max = length_in;
			length = 0;
		}
		int getLength(){
			return length;
		}
		SINHVIEN *getList(){
			return ds_tt;
		}
		void Insert(SINHVIEN in){
			if (length < max){
				ds_tt[length++] = in; // them vào r, length ++
			}
			else{
				Message("DANH SACH SV TAM THOI DAY",RED);
			}
		}
		void Delete(string mssv){
			for(int i = 0; i < length; i++){
				if (ds_tt[i].mssv == mssv){
					for(int j = i + 1; j < length; j++){
						ds_tt[j-1] = ds_tt[j];
					}
					break;
				}
			}
		}
		void Edit(string mssv, SINHVIEN in){
			for(int i = 0; i < length; i++){
				if (ds_tt[i].mssv == mssv){
					ds_tt[i] = in; break;
				}
			}
		}
		string getHo(string ho_tdem){ // lay cái ho. ra
			string tmp = "";
			for(int i=0;i<ho_tdem.size();i++){
				if (ho_tdem[i] == ' ') break;
				else tmp.push_back(ho_tdem[i]);
			}
			return tmp;
		}
		void ResetList(){
			length = 0;
		}
		void Sort(){
			if (length > 1){
				SINHVIEN minsv;
				int min;
				for(int i=0 ; i < length-1 ; i++){
					min = i;
					minsv = ds_tt[min];
					for(int j = i ; j < length ; j++){
						if (strcmp(minsv.ten.c_str(),ds_tt[j].ten.c_str()) > 0){ // Sort theo ten truoc
							minsv = ds_tt[j];
							min = j;
						} // Neu trung` ten thì sort ho.
						else if (strcmp(minsv.ten.c_str(),ds_tt[j].ten.c_str()) == 0){
							if (strcmp(getHo(minsv.ho_tdem).c_str(), getHo(ds_tt[j].ho_tdem).c_str()) > 0){
								minsv = ds_tt[j];
								min = j;
							}
						}
					}
					swap(ds_tt[i],ds_tt[min]);
				}	
			}
		}
		void Freelist(){
			ds_tt = NULL;
		}
		void ShowListStudent(int x, int y, int from, int to){
			if (length != 0){
				int start_x = x, start_y = y;
				drawRect(start_x,start_y,86,2);
				draw_high_line(start_x+13,start_y,2);
				drawText(start_x+5,start_y+1,"MSSV",WHITE);
				draw_high_line(start_x+41,start_y,2);
				drawText(start_x+26,start_y+1,"HO",WHITE);
				draw_high_line(start_x+51,start_y,2);
				drawText(start_x+45,start_y+1,"TEN",WHITE);
				draw_high_line(start_x+58,start_y,2);
				drawText(start_x+54,start_y+1,"GT",WHITE);
				draw_high_line(start_x+73,start_y,2);
				drawText(start_x+64,start_y+1,"SDT",WHITE);
				drawText(start_x+77,start_y+1,"MA LOP",WHITE);
				for(int i=from ; i < to; i++){
					// DRAW ELEMENT FRAME // PUT ALL THIS IN LOOP TO DRAW
					drawRect(start_x,start_y+2*(i+1-from),86,2);
					draw_high_line(start_x+13,start_y+2*(i+1-from),2);
					draw_high_line(start_x+41,start_y+2*(i+1-from),2);
					draw_high_line(start_x+51,start_y+2*(i+1-from),2);
					draw_high_line(start_x+58,start_y+2*(i+1-from),2);
					draw_high_line(start_x+73,start_y+2*(i+1-from),2);
					gotoxy(start_x,start_y+2*(i+1-from)); // + i*2
					printf("%c",195);
					gotoxy(start_x+13,start_y+2*(i+1-from));
					printf("%c",197);
					gotoxy(start_x+41,start_y+2*(i+1-from));
					printf("%c",197);
					gotoxy(start_x+51,start_y+2*(i+1-from));
					printf("%c",197);
					gotoxy(start_x+58,start_y+2*(i+1-from));
					printf("%c",197);
					gotoxy(start_x+73,start_y+2*(i+1-from));
					printf("%c",197);
					gotoxy(start_x+86,start_y+2*(i+1-from));
					printf("%c",180);
					// DRAW ELEMENT DATA // PUT ALL THIS IN LOOP TO DRAW
					drawText(start_x+3 ,start_y+2*(i+1-from)+1,ds_tt[i].mssv,WHITE);
					drawText(start_x+16,start_y+2*(i+1-from)+1,ds_tt[i].ho_tdem,WHITE);
					drawText(start_x+44,start_y+2*(i+1-from)+1,ds_tt[i].ten,WHITE);
					if (ds_tt[i].gender == 1) drawText(start_x+53,start_y+2*(i+1-from)+1,"Nam",WHITE);
					else if (ds_tt[i].gender == 0) drawText(start_x+53,start_y+2*(i+1-from)+1,"Nu",WHITE);
					drawText(start_x+61,start_y+2*(i+1-from)+1,ds_tt[i].sdt,WHITE);
					drawText(start_x+76,start_y+2*(i+1-from)+1,ds_tt[i].malop,WHITE);
				}
			}
		}
};
//typedef struct dssv_tamthoi DSSV_TAMTHOI;
class SinhVien{ // ds lien ket don
	private:
		NODESV *first;
		NODESV *last;
		int length; // dung` de~ generate mssv hoac get so luong
		const char *link;
//		vector<SINHVIEN> showlist; // ds de~ in ra man` hinh`
	public:
		dssv_tamthoi *dstt;
		SinhVien(){
			first = last = NULL;
			length = 0;
			dstt = new dssv_tamthoi(100);
		}
		SinhVien(const char *linkIn){
			link = linkIn;
			first = last = NULL;
			length = 0;
			dstt = new dssv_tamthoi(100);
			if (!file_exist(link)){
				ofstream f(link); // Mo ra de~ tao. 1 file.txt neu no ko ton tai.
				f.close();
			}
			else LoadData();
		}
		void LoadData();
		void SaveData();
		void FrameInput(int x, int y);
		NODESV *GetListStudent();
		NODESV *getLast();
		int getLength();
		int getShowListLength();
		void SortByName();	  // Sort nay` la` sort vector<SINHVIEN> dung` de~ show ra màn hình
		void CreateNewStudent(int x, int y,string malop, bool &reload); // GUI_Nhap sinh vien moi
		void Insert(SINHVIEN sv);
		NODESV *Search(string mssv);
		bool CheckClassID_Exist(string malop); // dùng de~ kt xem ma~ lop có tòn tai. hay ko, neu có thì tiep tuc. ds sv
		bool CheckStudentExist(string mssv,string malop);
		void FilterStudentByClass(string malop); // Bo. loc. sv theo ma lop roi bo~ vao` 1 vector tam. thoi`
		void Find(string malop, string &t_mssv,bool findtodel, bool findtoedit, bool &reload);
		void EditStudent(string mssv,SINHVIEN sv_in);
		void DeleteStudent(string mssv);
		void Show_Student_List(int x, int y, int from, int to);
		void FreeThisList();
};

void SinhVien::LoadData(){
	ifstream f(link);
	SINHVIEN t_sv;
	string tmp = "";
	while(tmp != "NULL"){
		tmp = ""; // reset bien tmp này, cho khoi~ bi. loi~
		getline(f,tmp,'_'); fflush(stdin); 
		// dòng này là de~ xem trong file.txt có gì ko. Neu có thì tmp se~ là 1 mssv, nen khi vào if ta phai~ gán t_sv.mssv = tmp
		// neu ko có gì thì tmp se~ = "NULL" và out vòng lap.
		if (tmp != "NULL"){
			t_sv.mssv = tmp; // gán tmp vào mssv 
			getline(f,t_sv.ho_tdem,'_'); fflush(stdin);
			getline(f,t_sv.ten,'_'); fflush(stdin);
			getline(f,t_sv.sdt,'_'); fflush(stdin);
			getline(f,t_sv.malop,'_'); fflush(stdin);
			f >> t_sv.gender;
			Insert(t_sv);
			getline(f,tmp); fflush(stdin); // Xuong hang`
//			cout << t_sv.mssv << "\t" << t_sv.ho_tdem << "\t" << t_sv.ten << "\t" << t_sv.sdt << "\t" << t_sv.malop << "\t" << t_sv.gender << endl;
		}
	}
//	cout << length; getch();
	f.close();
}

void SinhVien::SaveData(){
	ofstream f(link);
	if (first != NULL){
		for(NODESV *p = first; p != NULL; p = p->next){
			f << p->sv.mssv << "_" << p->sv.ho_tdem << "_" << p->sv.ten << "_" << p->sv.sdt << "_" << p->sv.malop << "_" << p->sv.gender << endl;
		}
	}
	f << "NULL_";
	f.close();
}

void SinhVien::FrameInput(int x, int y){
	// FRAME
	drawRect(x,y,60,20);
	// DUONG THANG NAM NGANG
	draw_flat_line(x,4+y,60);
	draw_flat_line(x,8+y,60);
	draw_flat_line(x,12+y,60);
	draw_flat_line(x,16+y,60);
	// TITLE
	// length = 16, max string = 42
	drawText(x+1,y+2,   "MSSV           :",WHITE);
	drawText(x+1,4+y+2, "HO             :",WHITE);
	drawText(x+1,8+y+2, "TEN            :",WHITE);
	drawText(x+1,12+y+2,"GT (1:Nam|0:Nu):",WHITE);
	drawText(x+1,16+y+2,"SDT            :",WHITE);
}

NODESV *SinhVien::GetListStudent(){
	return first;
}

NODESV *SinhVien::getLast(){
	return last;
}

int SinhVien::getLength(){
	return length;
}

//int SinhVien::getShowListLength(){
//	return showlist.size();
//}

void SinhVien::SortByName(){ // Selection Sort - tìm thang nho nhat roi` swap nó len dau`
	// vector<SINHVIEN>
//	if (showlist.size() != 0){
//		SINHVIEN minsv;
//		int min;
//		for(int i=0;i<showlist.size()-1;i++){
//			min = i;
//			minsv = showlist[min];
//			for(int j=i;j<showlist.size();j++){
//				if (strcmp(minsv.ten.c_str(),showlist[j].ten.c_str()) > 0){
//					minsv = showlist[j];
//					min = j;
//				}
//			}
//			swap(showlist[i],showlist[min]);
//		}	
//	}
	dstt->Sort();
}

void SinhVien::CreateNewStudent(int x, int y, string malop, bool &reload){
	bool esc = false; char c;
	FrameInput(x,y);
	// NHAP THONG TIN
	Cursor(true); SINHVIEN tmp; // tao. 1 gia tri tmp SINHVIEN moi
	// ========================= WHILE KIEM TRA XEM SINH VIEN CO TON TAI HAY KO ================================ //
	while(true){
		InputString(x+1+17,y+2,2*GetConsoleWidth()/3+24,GetConsoleHeight()-4,40,tmp.mssv,false,esc);
		if (esc){
			clearRect(x,y,62,22); gotoxy(0,0); return;
		}
		RemoveSpace(tmp.mssv,false); ToUpper(tmp.mssv);
		if (Search(tmp.mssv) == NULL) break; // NULL là mssv chua có trong ds nen duyet tiep tuc.
		else{
			Message("MSSV DA TON TAI TRONG DS. AN PHIM DE TIEP TUC",RED);
			c = getch();
			if (c == -32 || c == 0) c = getch();  
			clearMessage();
			clearRect(x+1+17,y+2,39,1);
			tmp.mssv = ""; // reset de~ còn nhap. lai.
		}
	}
	// ========================================================================================================== //
	InputString(x+1+17,4+y+2,2*GetConsoleWidth()/3+24,GetConsoleHeight()-4,40,tmp.ho_tdem,false,esc);
	if (esc){
		clearRect(x,y,62,22); gotoxy(0,0); return;
	}
	RemoveSpace(tmp.ho_tdem,true); ToUpper(tmp.ho_tdem);
	InputString(x+1+17,8+y+2,2*GetConsoleWidth()/3+24,GetConsoleHeight()-4,40,tmp.ten,false,esc);
	if (esc){
		clearRect(x,y,62,22); gotoxy(0,0); return;
	}
	RemoveSpace(tmp.ten,false); ToUpper(tmp.ten);
	InputGender(x+1+17,12+y+2,tmp.gender,esc);
	if (esc){
		clearRect(x,y,62,22); gotoxy(0,0); return;
	}
	InputString(x+1+17,16+y+2,2*GetConsoleWidth()/3+24,GetConsoleHeight()-4,12,tmp.sdt,true,esc); 
	if (esc){
		clearRect(x,y,62,22); gotoxy(0,0); return;
	}
	RemoveSpace(tmp.sdt,false);
	tmp.malop = malop;
	Insert(tmp);
	dstt->Insert(tmp); // Filter ds tam thoi` chi~ 1 làn, moi khi insert 1 sv thì ds này cung~ dc insert
	reload = true;
	Cursor(false);
	clearRect(x,y,62,22);
}

void SinhVien::Insert(SINHVIEN sv){
	NODESV *tmp = new NODESV;
	if (first == NULL){
		tmp->sv = sv;
		tmp->next = first; // luc dau thi` first = NULL
		first = last = tmp;
	}
	else{
		tmp->sv = sv;
		tmp->next = last->next; // last->next luc nao` cung~ == NULL
		last->next = tmp;
		last = tmp;
	}
	length++;
}

NODESV *SinhVien::Search(string mssv){
	NODESV *tmp = first;
	while(tmp != NULL){
		if (tmp->sv.mssv == mssv){
			return tmp;
		}
		tmp = tmp->next;
	}
	return NULL;
}

bool SinhVien::CheckClassID_Exist(string malop){
	for(NODESV *p = first; p != NULL; p = p->next){
		if (p->sv.malop == malop) return true;
	}
	return false;
}

bool SinhVien::CheckStudentExist(string mssv,string malop){
	for(NODESV *p = first; p != NULL; p = p->next){
		if (p->sv.mssv == mssv && p->sv.malop == malop) return true;
	}
	return false;
}

void SinhVien::FilterStudentByClass(string malop){ // Bo. loc sv theo ma lop, showlist la vector chua struct SINHVIEN
//	showlist.clear();
//	for(NODESV *p = first; p != NULL; p = p->next){
//		if (p->sv.malop == malop) showlist.push_back(p->sv);
//	}
	// Loc xog thi` tiep tuc sort theo ten tang dan`
	dstt->ResetList();
	for(NODESV *p = first; p != NULL; p = p->next){
		if (p->sv.malop == malop) dstt->Insert(p->sv);
	}
}

void SinhVien::Find(string malop, string &t_mssv, bool findtodel, bool findtoedit, bool &reload){
	// Tham tri. dùng cho phan` edit de~ khi edit xog roi thay doi~, return thì tiép tuc. hàm thay doi~ trong ltc
	string t = "Tim kiem theo MSSV: "; bool found, esc = false;
	clearRect(26+GetConsoleWidth()/2+t.size(),4,21,1); // clear dòng chu~ nhap. thong tin
	NODESV *tmp;
	RemoveSpace(t_mssv,false);
	ToUpper(t_mssv);
	tmp = Search(t_mssv);
	if (tmp != NULL){
		found = true;
		int y = 8;
		clearRect(25+GetConsoleWidth()/2,y,43,18);
		drawText(38+GetConsoleWidth()/2,y+1,"KET QUA TIM KIEM",YELLOW);
		drawText(26+GetConsoleWidth()/2,y+4, "MSSV      : ",WHITE);
		drawText(26+GetConsoleWidth()/2,y+7, "HO TEN    : ",WHITE);
		drawText(26+GetConsoleWidth()/2,y+10,"GIOI TINH : ",WHITE);
		drawText(26+GetConsoleWidth()/2,y+13,"SDT       : ",WHITE);
		drawText(39+GetConsoleWidth()/2,y+4,tmp->sv.mssv,WHITE);
		drawText(39+GetConsoleWidth()/2,y+7,tmp->sv.ho_tdem,WHITE);
		drawText(tmp->sv.ho_tdem.size()+1+39+GetConsoleWidth()/2,y+7,tmp->sv.ten,WHITE);
		if (tmp->sv.gender == 1) drawText(39+GetConsoleWidth()/2,y+10,"Nam",WHITE);
		else if (tmp->sv.gender == 0)drawText(39+GetConsoleWidth()/2,y+10,"Nu",WHITE);
		drawText(39+GetConsoleWidth()/2,y+13,tmp->sv.sdt,WHITE);
	}
	else{
		clearRect(25+GetConsoleWidth()/2,8,43,18); // Xoa bang~ thong tin cu~
		drawText(35+GetConsoleWidth()/2,15,"KHONG TIM THAY SINH VIEN",YELLOW);
	}
	if (findtodel && found){
		Message("Ban co chac chan khong [Y/N]",GREEN);
		if (Yes()){
			DeleteStudent(t_mssv);
			dstt->Delete(t_mssv); // Xoa sv trong ds tam. thoi`
			clearRect(25+GetConsoleWidth()/2,8,42,17); // Xoa bang~ thong tin cu~
			reload = true;
		}
		clearMessage();
	}
	if (findtoedit && found){
		int x = 11, y = 5+GetConsoleHeight()/2;
		// Ghi ra thong cu~ cua~ sinh vien do
		FrameInput(x,y);
		drawText(x+1+17,y+2,tmp->sv.mssv,WHITE);
		drawText(x+1+17,4+y+2,tmp->sv.ho_tdem,WHITE);
		drawText(x+1+17,8+y+2,tmp->sv.ten,WHITE);
		drawNumber(x+1+17,12+y+2,tmp->sv.gender,WHITE);
		drawText(x+1+17,16+y+2,tmp->sv.sdt,WHITE);
		// Nhap thong tin moi cho sinh vien do
		SINHVIEN t_sv = tmp->sv;
		// Coi nhu thang t_sv la` thang` sv moi vua` tim duoc. Va t_sv can` có data cua~ tmp->sv de~ nó có the lam`
		// tham so vao` ham InputString
		while(true){
			InputString(x+1+17+t_sv.mssv.size(),y+2,2*GetConsoleWidth()/3+24,GetConsoleHeight()-4,40,t_sv.mssv,false,esc);
			if (esc){
				clearRect(x,y,62,22); gotoxy(0,0); return;
			}
			RemoveSpace(t_sv.mssv,false); ToUpper(t_sv.mssv);
			if (t_sv.mssv != t_mssv && CheckStudentExist(t_sv.mssv,malop)){
				Message("MSSV DA TON TAI. VUI LONG NHAP LAI",RED);
			}
			else{
				clearMessage(); break;
			}
		}
		InputString(x+1+17+t_sv.ho_tdem.size(),4+y+2,2*GetConsoleWidth()/3+24,GetConsoleHeight()-4,40,t_sv.ho_tdem,false,esc);
		if (esc){
			clearRect(x,y,62,22); gotoxy(0,0); return;
		}
		RemoveSpace(t_sv.ho_tdem,true); ToUpper(t_sv.ho_tdem);
		InputString(x+1+17+t_sv.ten.size(),8+y+2,2*GetConsoleWidth()/3+24,GetConsoleHeight()-4,40,t_sv.ten,false,esc);
		if (esc){
			clearRect(x,y,62,22); gotoxy(0,0); return;
		}
		RemoveSpace(t_sv.ten,false); ToUpper(t_sv.ten);
		InputGender(x+1+18,12+y+2,t_sv.gender,esc);
		if (esc){
			clearRect(x,y,62,22); gotoxy(0,0); return;
		}
		InputString(x+1+17+t_sv.sdt.size(),16+y+2,2*GetConsoleWidth()/3+24,GetConsoleHeight()-4,12,t_sv.sdt,true,esc); 
		if (esc){
			clearRect(x,y,62,22); gotoxy(0,0); return;
		}
		RemoveSpace(t_sv.sdt,false);
//		cout << t_sv.mssv << "\t" << t_sv.ho_tdem << "\t" << t_sv.ten << "\t" << t_sv.gender << "\t" << t_sv.sdt;
		Message("Ban co chac chan khong [Y/N]",GREEN);
		if (Yes()){
			EditStudent(t_mssv,t_sv);
			dstt->Edit(t_mssv,t_sv); // Chinh sua~ trong ds tam. thoi`
			t_mssv = t_sv.mssv; // khi edit thanh cong thì phai~ truyen` thang mssv new ra de~ thay doi~ trong ds ltc
			clearRect(25+GetConsoleWidth()/2,8,42,17); // Xoa bang~ thong tin cu~
			reload = true;
		}
		clearRect(x,y,62,22);
		clearMessage();
	}
}

void SinhVien::EditStudent(string mssv,SINHVIEN sv_in){ 
	NODESV *cur;
	cur = first;
	while(cur != NULL){
		if (cur->sv.mssv == mssv){
			cur->sv = sv_in;
			break;
		}
		cur = cur->next;
	}
}

void SinhVien::DeleteStudent(string mssv){
	NODESV *pre,*cur;
	cur = first;
	if (first->sv.mssv == mssv){ // Kiem tra de~ delete first
		first = first->next;
	}
	else if (last->sv.mssv == mssv){ // Kiem tra de~ delete last
		while(cur->next != NULL){
			pre = cur;
			cur = cur->next;
		}
		pre->next = NULL; // hoac là last->next vì last->next luon luon = NULL
		last = pre; // gán cho last = pre vì cur lúc này da~ coi nhu là bi. xóa r
	}
	else{
		while(cur != NULL){
			if (cur->sv.mssv == mssv){
				pre->next = cur->next; break; // vd: 4,5,6. xóa 5 thì gán 4->next = 5->next = 6 => 4,6
			}
			pre = cur;
			cur = cur->next;
		}
	}
//	//cur->sv.mssv == mssv && cur->sv.malop == malop
	length--;
	free(cur); // phai~ luôn luôn free thang` cur vì néu ko cái giá tri. trong thang cur luôn ton` tai. o~ dau do
}

void SinhVien::Show_Student_List(int x, int y, int from, int to){
	if (dstt->getLength() != 0){
		int start_x = x, start_y = y;
		drawRect(start_x,start_y,86,2);
		draw_high_line(start_x+13,start_y,2);
		drawText(start_x+5,start_y+1,"MSSV",WHITE);
		draw_high_line(start_x+41,start_y,2);
		drawText(start_x+26,start_y+1,"HO",WHITE);
		draw_high_line(start_x+51,start_y,2);
		drawText(start_x+45,start_y+1,"TEN",WHITE);
		draw_high_line(start_x+58,start_y,2);
		drawText(start_x+54,start_y+1,"GT",WHITE);
		draw_high_line(start_x+73,start_y,2);
		drawText(start_x+64,start_y+1,"SDT",WHITE);
		drawText(start_x+77,start_y+1,"MA LOP",WHITE);
		for(int i=from ; i < to; i++){
			// DRAW ELEMENT FRAME // PUT ALL THIS IN LOOP TO DRAW
			drawRect(start_x,start_y+2*(i+1-from),86,2);
			draw_high_line(start_x+13,start_y+2*(i+1-from),2);
			draw_high_line(start_x+41,start_y+2*(i+1-from),2);
			draw_high_line(start_x+51,start_y+2*(i+1-from),2);
			draw_high_line(start_x+58,start_y+2*(i+1-from),2);
			draw_high_line(start_x+73,start_y+2*(i+1-from),2);
			gotoxy(start_x,start_y+2*(i+1-from)); // + i*2
			printf("%c",195);
			gotoxy(start_x+13,start_y+2*(i+1-from));
			printf("%c",197);
			gotoxy(start_x+41,start_y+2*(i+1-from));
			printf("%c",197);
			gotoxy(start_x+51,start_y+2*(i+1-from));
			printf("%c",197);
			gotoxy(start_x+58,start_y+2*(i+1-from));
			printf("%c",197);
			gotoxy(start_x+73,start_y+2*(i+1-from));
			printf("%c",197);
			gotoxy(start_x+86,start_y+2*(i+1-from));
			printf("%c",180);
			// DRAW ELEMENT DATA // PUT ALL THIS IN LOOP TO DRAW
//			drawText(start_x+3 ,start_y+2*(i+1-from)+1,showlist[i].mssv,WHITE);
//			drawText(start_x+16,start_y+2*(i+1-from)+1,showlist[i].ho_tdem,WHITE);
//			drawText(start_x+44,start_y+2*(i+1-from)+1,showlist[i].ten,WHITE);
//			if (showlist[i].gender == 1) drawText(start_x+53,start_y+2*(i+1-from)+1,"Nam",WHITE);
//			else if (showlist[i].gender == 0) drawText(start_x+53,start_y+2*(i+1-from)+1,"Nu",WHITE);
//			drawText(start_x+61,start_y+2*(i+1-from)+1,showlist[i].sdt,WHITE);
//			drawText(start_x+76,start_y+2*(i+1-from)+1,showlist[i].malop,WHITE);
			drawText(start_x+3 ,start_y+2*(i+1-from)+1,dstt->getList()[i].mssv,WHITE);
			drawText(start_x+16,start_y+2*(i+1-from)+1,dstt->getList()[i].ho_tdem,WHITE);
			drawText(start_x+44,start_y+2*(i+1-from)+1,dstt->getList()[i].ten,WHITE);
			if (dstt->getList()[i].gender == 1) drawText(start_x+53,start_y+2*(i+1-from)+1,"Nam",WHITE);
			else if (dstt->getList()[i].gender == 0) drawText(start_x+53,start_y+2*(i+1-from)+1,"Nu",WHITE);
			drawText(start_x+61,start_y+2*(i+1-from)+1,dstt->getList()[i].sdt,WHITE);
			drawText(start_x+76,start_y+2*(i+1-from)+1,dstt->getList()[i].malop,WHITE);
		}
	}
}

void SinhVien::FreeThisList(){
	NODESV *pre, *cur = first;
	while(cur != NULL){
		pre = cur;
		cur = cur->next;
		delete pre;
	}
	// phai~ delete ca~ hai con tro~ này vì 2 con tro~ này van~ con` ton` tai. sau khi del tat ca~ ptu~
	first = last = NULL;
	dstt->Freelist();
	free(dstt);
}
#endif

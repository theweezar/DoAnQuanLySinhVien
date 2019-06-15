#ifndef LOPTINCHI_H
#define LOPTINCHI_H
#define MAXLIST 1000
typedef struct{ // malop, ma mon hoc, nien khoa, hoc ki, nhom, so sv max, con tro ds sinh tham gia lop
	int malop;   // unique - ma lop tin chi
	string MAMH; // unique
	string nienkhoa; // unique
	int hocki; // unique
	int nhom; // unique
	int sv_max;
	SvDangKy *ds; // ds sinh vien dang ky ltc, chua diem~ và mssv
}LTC, *pLTC;
const LTC null_ltc = {0,"","",0,0,0,NULL}; 

class Ds_Diem_Tamthoi{
	private:
		DIEM *dsdtt;
		int length;
	public:
		Ds_Diem_Tamthoi(int length_in){
			length = 0;
			dsdtt = new DIEM[length_in];
		}
		int getLength(){
			return length;
		}
		DIEM *getList(){
			return dsdtt;
		}
		void Insert(DIEM td){
			dsdtt[length++] = td;
		}
		void Edit(float diem, int vitri){
			dsdtt[vitri].diem = diem;
		}
		void ResetList(){
			length = 0;
		}
		void FreeList(){
			dsdtt = NULL;
		}
};

class LopTinChi{ // ds tuyen tinh
	private:
		pLTC *pltc; // Mang~ con tro~ 
		int length;    // do dai`
		const char *link; // duong dan~
	public:
		dssv_tamthoi *dssvtt; // ds sinh vien tam thoi
		Ds_Diem_Tamthoi *dsdtt;
		
		LopTinChi(const char *linkIn){ // Khoi tao. ltc voi toàn bo. sinh vien
			link = linkIn;
			dssvtt = new dssv_tamthoi(100);
			dsdtt = new Ds_Diem_Tamthoi(100);
			pltc = new pLTC[MAXLIST]; // Mang con tro~ ton` tai. 1k con tro~ và tro~ den LTC
			if (!file_exist(link)){
				ofstream f(link);// dung` ofstream la` vi` neu file ko ton` tai thi` no se~ tao. 1 file moi de~ ghi - write
				length = 0;      // neu file ko ton tai. thi` length = 0, va` ghi vao` do 0 de~ sau nay` doc. de~ dang`
				f << length;
			}
			else LoadData(); // DONE - Khi nao` hoan tat het han~ mo~ ra
		}
		void FrameInput(int x, int y);
		void LoadData(); // LoadData có thêm dssv de~ load tat ca~ thong tin cua~ sv vào 1 ltc
		void SaveData();
		pLTC getLTC(LTC tmp); // Con tro~ phan tu~
		pLTC *getList(); // Mang con tro~
		int getPosition(LTC tmp);
		bool CheckMAMH_Exist(string mamh);
		int getLength();
		void CreateNewClass(int x, int y,string n_mamh, bool &reload);
		void Insert(LTC tmp);
		void RegisterStudent(SINHVIEN sv_dk);
		void Find(LTC &tmp, bool findtodel,bool findtoedit,bool &reload, SinhVien *dssv);
		void EditClass(LTC n_ltc,LTC o_ltc); // n: new, o: old
		void ChangeMAMH(string old_mamh, string new_mamh);
		void DeleteClass(int pos);
		void Show_Student_InClass();
		void Delete_Student_InClass(string mssv, string malop);
		void Edit_Student_InClass(string mssv, string malop, SINHVIEN sv_in);
		void ShowClassList(int x, int y, int from, int to);
		void Score_Table(bool edit, int vitri, SinhVien *dssv);
		void Score_List(int x, int y, int from, int to);
		void FreeList();
};

void LopTinChi::FrameInput(int x, int y){
	// FRAME
	drawRect(x,y,60,20);
	// DUONG THANG NAM NGANG
	draw_flat_line(x,4+y,60);
	draw_flat_line(x,8+y,60);
	draw_flat_line(x,12+y,60);
	draw_flat_line(x,16+y,60);
	// TITLE
	// length = 17, max string = 42
	drawText(x+1,y+2,   "MA MON HOC      :",WHITE);
	drawText(x+1,4+y+2, "NIEN KHOA       :",WHITE);
	drawText(x+1,8+y+2, "HOC KY          :",WHITE);
	drawText(x+1,12+y+2,"NHOM            :",WHITE);
	drawText(x+1,16+y+2,"SO SV TOI DA    :",WHITE);
}

void LopTinChi::LoadData(){
	ifstream f(link);// Neu file ton` tai. thi` doc cai` length ra, de~ khi LoadData, ta se~ dung loop < length
	f >> length; //cout << length << endl;
	string tmp;
	for(int i=0;i<length;i++){
		pltc[i] = new LTC;
		f >> pltc[i]->malop >> pltc[i]->hocki >> pltc[i]->nhom >> pltc[i]->sv_max;
		getline(f,tmp); fflush(stdin);// Xuong Dong de~ doc tiep --- new line here
		getline(f,pltc[i]->nienkhoa,'_');
		getline(f,pltc[i]->MAMH,'_'); fflush(stdin); 
		pltc[i]->ds = new SvDangKy();
		getline(f,tmp,'_'); fflush(stdin); // Doc file và xac dinh xem tmp có == NULL hay == NOT NULL
		printf("\nMalop: %d - HocKi: %d - Nhom: %d - NK: %s - SvMax: %d\n",pltc[i]->malop,pltc[i]->hocki,pltc[i]->nhom,pltc[i]->nienkhoa.c_str(),pltc[i]->sv_max);
		cout << "MAMH: " << pltc[i]->MAMH << endl;
		if (tmp == "NOT NULL"){	       // Neu co sv dang ky roi thi` tiep tuc doc mssv vao` ltc[i].dssv
			while(true){
				DIEM td; // temp diem~
				f >> td.diem;
				if (td.diem != -1){
					getline(f,td.mssv,'_');
					RemoveSpace(td.mssv,true);
					cout << td.mssv << "-" << td.diem << " | ";
					pltc[i]->ds->Insert(td);
				}
				else{
//					getline(f,tmp); 
					break; 
				}
			}
			cout << endl;
		}
	}
//	getch();
	f.close();
}

void LopTinChi::SaveData(){
	ofstream f(link);
	f << length << endl; // Ghi so luong vao` truoc roi xuong dong
	for(int i = 0 ; i < length ; i++){
		f << pltc[i]->malop << " " << pltc[i]->hocki << " " << pltc[i]->nhom << " " << pltc[i]->sv_max << endl;
		f << pltc[i]->nienkhoa << "_" << pltc[i]->MAMH << "_";
		if (pltc[i]->ds->getLength() == 0) f << "NULL_" << endl; // neu ltc chua co sv dang ky thi` ghi vao` file la` NULL_
		else{
			f << "NOT NULL_";  // neu co roi thi` NOT NULL_ va` tiep tuc in cac mssv vao` file
			for(NODED *p = pltc[i]->ds->getList(); p != NULL; p = p->next){
				f << p->d.diem << " " << p->d.mssv << "_";
			}
			f << -1 << endl; // Cot moc danh dau het khi da~ ghi het sv vao` list
		}
	}
	f.close();
}

pLTC LopTinChi::getLTC(LTC tmp){
	for(int i=0;i<length;i++){
		if (pltc[i]->MAMH == tmp.MAMH && pltc[i]->nienkhoa == tmp.nienkhoa && pltc[i]->hocki == tmp.hocki && pltc[i]->nhom == tmp.nhom) return pltc[i];
	}
	return NULL;
}

int LopTinChi::getPosition(LTC tmp){
	for(int i=0;i<length;i++){
		if (pltc[i]->MAMH == tmp.MAMH && pltc[i]->nienkhoa == tmp.nienkhoa && pltc[i]->hocki == tmp.hocki && pltc[i]->nhom == tmp.nhom) return i;
	}
	return -1; // -1 dùng de~ báo loi~ néu LOPTINCHI ko ton` tai.
}

bool LopTinChi::CheckMAMH_Exist(string mamh){
	for(int i=0;i<length;i++){
		if (pltc[i]->MAMH == mamh) return true;
	}
	return false;
}

int LopTinChi::getLength(){
	return length;
}

void LopTinChi::CreateNewClass(int x, int y,string n_mamh, bool &reload){
	Cursor(true); // lam hien lien con tro de~ ghi ra man hinh`
	LTC tmp = null_ltc; 
	tmp.MAMH = n_mamh;
	bool esc = false;
	FrameInput(x,y);
	// INPUT STRING
	drawText(x+1+18,y+2,tmp.MAMH,WHITE);
//	tmp.nienkhoa = 1900+tg->tm_year; // nienkhoa se~ = cái nam hien. tai.
//	drawNumber(x+1+18,4+y+2,tmp.nienkhoa,WHITE);
	while(true){
		InputNienKhoa(x+1+18,4+y+2,tmp.nienkhoa,esc);
		if (esc){
			clearRect(x,y,62,21); gotoxy(0,0); return;
		}
		InputNumber(x+1+18,8+y+2,2*GetConsoleWidth()/3+24, GetConsoleHeight()-4,tmp.hocki,1,true,esc); 
		if (esc){
			clearRect(x,y,62,21); gotoxy(0,0); return;
		}
		InputNumber(x+1+18,12+y+2,2*GetConsoleWidth()/3+24, GetConsoleHeight()-4,tmp.nhom,1,true,esc);
		if (esc){
			clearRect(x,y,62,21); gotoxy(0,0); return;
		}
		InputNumber(x+1+18,16+y+2,2*GetConsoleWidth()/3+24, GetConsoleHeight()-4,tmp.sv_max,3,true,esc); 
		if (esc){
			clearRect(x,y,62,21); gotoxy(0,0); return;
		}
		if (getLTC(tmp) == NULL){
			tmp.ds = new SvDangKy();
			tmp.malop = pltc[length-1]->malop + 1; // Lay maloptc cua ltc cuoi cung + 1 cho ltc moi
			Insert(tmp); 
			reload = true;
			break;
		}
		else{
			Message("LOP TIN CHI DA TON TAI. VUI LONG NHAP LAI",RED); Pause(); clearMessage();
			tmp.hocki = tmp.nhom = tmp.sv_max = 0; 
			clearRect(x+1+18,8+y+2,5,1);
			clearRect(x+1+18,12+y+2,5,1);
			clearRect(x+1+18,16+y+2,5,1);
		}
	}
	clearRect(x,y,62,21);
}

void LopTinChi::Insert(LTC tmp){ 
	if (length < MAXLIST){
		pLTC p = new LTC;
		p->malop = tmp.malop;
		p->MAMH = tmp.MAMH;
		p->hocki = tmp.hocki;
		p->nhom = tmp.nhom;
		p->nienkhoa = tmp.nienkhoa;
		p->sv_max = tmp.sv_max;
		p->ds = tmp.ds;
		pltc[length++] = p;
	}
	else Message("DANH SACH LTC DA DAY",RED);
}

void LopTinChi::RegisterStudent(SINHVIEN sv_dk){ // sinh vien list
	system("cls"); // xoa man hinh
	bool esc = false, press = true, move = true , enter = false;
	int cur = 0, pre = -1, page = 1, from = 0, to = (length > 10 ? 10:length);
	// cur,pre,page,from,to giong nhu coi danh sach
	int max = (length%10 == 0 ? length/10:1+length/10);
	// max này là tính só trang toi da
	int x = 8, y = GetConsoleHeight()/2 - 11, choose; // x = GetConsoleWidth()/2 - 50
	drawText(x+87,y+1,"Check",GREEN); int t = 2;
	drawText(x+56,y-4,"BANG DANG KY LOP TIN CHI",CYAN);
	drawFillRect(x, y-2,137,1,CYAN);
	// BANG THONG TIN SINH VIEN
	drawRect(x+96,y,40,22);
	drawText(x+106,y+2,"THONG TIN SINH VIEN",YELLOW);
	drawText(x+98,y+5, "MSSV      : ",WHITE);
	drawText(x+98,y+8, "HO VA TEN : ",WHITE);
	drawText(x+98,y+11,"GIOI TINH : ",WHITE);
	drawText(x+98,y+14,"SDT       : ",WHITE);
	drawText(x+98,y+17,"MA LOP    : ",WHITE);
	drawText(x+110,y+5,sv_dk.mssv,WHITE);
	drawText(x+110,y+8,sv_dk.ho_tdem,WHITE);
	drawText(x+110+sv_dk.ho_tdem.size()+1,y+8,sv_dk.ten,WHITE);
	if (sv_dk.gender == 1) drawText(x+110,y+11,"Nam",WHITE);
	else drawText(x+110,y+11,"Nu",WHITE);
	drawText(x+110,y+14,sv_dk.sdt,WHITE);
	drawText(x+110,y+17,sv_dk.malop,WHITE);
	while(true){ // mh->length%10 == 0 ? mh->length/10:1+mh->length/10,
		// vd : from = 20, to = 27;
		if (page < max){  // if cho~ này dùng de~ tính toán vi trí cua dau '>>>>'
			if (cur < 0) cur = 9;// vd trang 1: 1-10, trang 2: 11-20, trang 3: 21-27
			if (cur > 9) cur = 0; 
		}
		else{ // TH: page == max -> dang o~ trang cuoi cùng, trang cuói cùng có the~ ko du~ 10 phàn tu~
			if (length % 10 == 0){ // Neu trang cuoi cùng là so hàng chuc.: 30,40,50,......
				if (cur < 0) cur = 9;
				if (cur > 9) cur = 0;	
			}
			else{ // else này là dành cho trang cuoi cùng - neu ko phai~ mà là: 27, 35, 59, ....
				if (cur < 0) cur = to - 10*(to/10) - 1; // vd lay 27 -> cur = 27 - 10 x int(27/10) - 1 = 6
				if (cur > to - 10*(to/10) - 1) cur = 0;
			}
		}
		if (move){
			move = false;
			press = true;
			cur = 0; pre = -1;
			clearRect(x-6,y+3,93,22);
			clearRect(x+87,y+3,5,22);
			ShowClassList(x,y,from,to);
			drawNumber(x+42,y+25,page,WHITE);
			drawText(x+46,y+25,"/",WHITE);
			drawNumber(x+50,y+25,max,WHITE);
			for(int i=from; i<to;i++){ // vòng lap. này dùng de~ tim sv vùa nhap. vào trong tat ca~ ltc
				if (pltc[i]->ds->Search(sv_dk.mssv) != NULL){ // Neu sv có trong ds thì ve~ to màu xanh
					drawFillRect(x+88,y+2*(i-from+1)+1,3,1,GREEN); // neu có thì to màu green
				}
				else if (pltc[i]->sv_max - pltc[i]->ds->getLength() == 0){ // neu ko có sv mà ltc het slot thì ve~ màu RED
					drawFillRect(x+88,y+2*(i-from+1)+1,3,1,RED);
				}
				else{ // neu ko có sv thi ve~ màu GRAY
					drawFillRect(x+88,y+2*(i-from+1)+1,3,1,GRAY);
				}
			}
		}
		if (press){
			press = false;
			if (pre != -1){
				drawText(x-5,y+3+pre*2,">>>>",BLACK);
			}
			drawText(x-5,y+3+cur*2,">>>>",GREEN);
		}
		KeyPress_2(cur,pre,from,to,page,length,press,move,esc,enter);
		if (enter){
			enter = false;
			choose = cur+(page-1)*10;
			// Cách 1 de~ check xem sv có trong ltc chua ? :if ltc[choose].dssv->Search(sv_dk.mssv,sv_dk.malop) == NULL
			if (pltc[choose]->ds->Search(sv_dk.mssv) == NULL && pltc[choose]->sv_max - pltc[choose]->ds->getLength() > 0){
				// Neu sv chua dang ky và ltc còn slot thì moi them vào
				DIEM td = {sv_dk.mssv,0};
				pltc[choose]->ds->Insert(td);
				// Khi insert thì phai~ tìm het tat ca~ thong tin cua~ sv trong main list sv ròi moi` insert
				drawFillRect(x+88,y+2*(cur+1)+1,3,1,GREEN);
				clearRect(x+77,y+2*(cur+1)+1,5,1);
				drawNumber(x+78,y+2*(cur+1)+1,pltc[choose]->sv_max - pltc[choose]->ds->getLength(),WHITE);
				// Ghi lai. só luong còn lai trong ltc
			}
//			else if (pltc[choose]->sv_max - [choose]->ds->getLength() == 0){
//				
//			}
			else{ // Néu sv da~ có trong ds cua ltc này thì xóa bo~
//				ltc[choose].dssv->DeleteStudent(sv_dk.mssv,sv_dk.malop);
//				drawFillRect(x+88,y+2*(cur+1)+1,3,1,GRAY);
//				clearRect(x+77,y+2*(cur+1)+1,5,1);
//				drawNumber(x+78,y+2*(cur+1)+1,ltc[choose].sv_max - ltc[choose].dssv->getLength(),WHITE);
				// Ghi lai. só luong còn lai trong ltc
			}
		}
		if (esc) return;
	}
}

void LopTinChi::Find(LTC &tmp, bool findtodel,bool findtoedit,bool &reload, SinhVien *dssv){
	bool found = false, esc = false; char c; int vt; // vt = vi. trí
	for(int i=0;i<length;i++){ 
		if (pltc[i]->MAMH == tmp.MAMH && pltc[i]->nienkhoa == tmp.nienkhoa && pltc[i]->hocki == tmp.hocki && pltc[i]->nhom == tmp.nhom){
			//tmp = ltc[i]; 
			vt = i;
			found = true;
			break;
		}
	}
	if (!found){ // Neu ko tìm thay se~ bao loi~
		drawText(34+GetConsoleWidth()/2,23,"KHONG TIM THAY LOP TIN CHI",YELLOW);
		drawText(34+GetConsoleWidth()/2,24,"AN PHIM BAT KY DE TIEP TUC",YELLOW);
		getch();
		clearRect(26+GetConsoleWidth()/2,22,40,5);
		return;
	}
	if (found && !findtodel && !findtoedit){ 
//		 if này khác vs mh->find và sv->find là vì de~ phan biet. xem chúc nang là tìm và show ds sinh vien vói delete và edit
		drawText(35+GetConsoleWidth()/2,22,"DA TIM THAY LOP TIN CHI",GREEN);
		drawButton(37+GetConsoleWidth()/2,24,CYAN,8,0,"SPACE","Xem DSSV");
		while(true){
			c = getch();
			if (c == 32){ // Space
				if (pltc[vt]->ds->getLength() == 0){ // Neu so luong sv == 0 thì ds rong~
					clearRect(26+GetConsoleWidth()/2,22,40,5);
					drawText(35+GetConsoleWidth()/2,23,"DANH SACH SINH VIEN RONG",YELLOW);
					drawText(38+GetConsoleWidth()/2,24,"AN ESC DE QUAY LAI",YELLOW);
				}
				else{
					dssvtt->ResetList(); // Reset lai. cái list tam. thòi vì, có the~ tra cuu rat nhieu ltc, mà moi~ lop là 1 ds rieng biet.
					for(NODED *pd = pltc[vt]->ds->getList(); pd != NULL; pd = pd->next){
						dssvtt->Insert(dssv->Search(pd->d.mssv)->sv);
					}
					dssvtt->Sort(); // tìm xog ròi Sort theo ten và ho.
					Show_Student_InClass();
					clearRect(4,32,88,15);
					clearRect(26+GetConsoleWidth()/2,22,40,5); // xóa dòng thong báo màu vàng
					return;
				}
			}
			if (c == 27){ // Esc
				clearRect(4,32,88,15);
				clearRect(26+GetConsoleWidth()/2,22,40,5); // xóa dòng thong báo màu vàng
				return;
			}
		}
	}
	
	if (found && findtodel){
		Message("Ban co chac chan khong [Y/N]",GREEN);
		if (Yes()){
			DeleteClass(vt);
			reload = true;
		}
		clearMessage();
	}
	if (found && findtoedit){
		// Khi tìm dc thì thang LOPTINCHI tmp se~ dc gán lai. cái moi tìm.
		LTC n_ltc;
		n_ltc.nienkhoa = pltc[vt]->nienkhoa;
		n_ltc.hocki = pltc[vt]->hocki;
		n_ltc.nhom = pltc[vt]->nhom;
		n_ltc.sv_max = pltc[vt]->sv_max;
		int x = 11, y = 5+GetConsoleHeight()/2;
		FrameInput(x,y);
		drawText(x+1+18,y+2,pltc[vt]->MAMH,WHITE);
		drawText(x+1+18,4+y+2,pltc[vt]->nienkhoa,WHITE);
		drawNumber(x+1+18,8+y+2,pltc[vt]->hocki,WHITE);
		drawNumber(x+1+18,12+y+2,pltc[vt]->nhom,WHITE);
		drawNumber(x+1+18,16+y+2,pltc[vt]->sv_max,WHITE); 
		InputNienKhoa(x+1+18,4+y+2,n_ltc.nienkhoa,esc);
		if (esc){
			clearRect(x,y,62,21); return;
		}
		InputNumber(x+1+18+1,8+y+2,2*GetConsoleWidth()/3+24, GetConsoleHeight()-4,n_ltc.hocki,1,true,esc); 
		if (esc){
			clearRect(x,y,62,21); return;
		}
		InputNumber(x+1+18+1,12+y+2,2*GetConsoleWidth()/3+24, GetConsoleHeight()-4,n_ltc.nhom,1,true,esc);
		if (esc){
			clearRect(x,y,62,21); return;
		}
		while(true){
			InputNumber(x+1+18+floor(log10(pltc[vt]->sv_max))+1,16+y+2,2*GetConsoleWidth()/3+24, GetConsoleHeight()-4,n_ltc.sv_max,3,true,esc);
			if (esc){
				clearRect(x,y,62,21); return;
			}
			if (n_ltc.sv_max - pltc[vt]->ds->getLength() < 0){
				Message("SO SV TOI DA KHONG DU. VUI LONG NHAP LAI", RED);
				Pause(); clearMessage();
				drawNumber(x+1+18,16+y+2,pltc[vt]->sv_max,WHITE);
				n_ltc.sv_max = pltc[vt]->sv_max;
			}
			else break;
		}
		Message("Ban co chac chan khong [Y/N]",GREEN);
		if (Yes()){
			EditClass(n_ltc,tmp);
			clearMessage();
			clearRect(x,y,62,21);
			reload = true;
			tmp = n_ltc;
		}
	}
}

void LopTinChi::ChangeMAMH(string old_mamh, string new_mamh){
	for(int i=0;i<length;i++){
		if (pltc[i]->MAMH == old_mamh) pltc[i]->MAMH = new_mamh;
	}
}

void LopTinChi::EditClass(LTC n_ltc,LTC o_ltc){
	for(int i=0;i<length;i++){ 
		if (pltc[i]->MAMH == o_ltc.MAMH && pltc[i]->nienkhoa == o_ltc.nienkhoa && pltc[i]->hocki == o_ltc.hocki && pltc[i]->nhom == o_ltc.nhom){
			pltc[i]->hocki = n_ltc.hocki;
			pltc[i]->nhom = n_ltc.nhom;
			pltc[i]->sv_max = n_ltc.sv_max;
			break;
		}
	}
}

void LopTinChi::DeleteClass(int pos){
	delete pltc[pos]->ds; 
	delete pltc[pos];
	for(int i=pos+1;i<length;i++){
		pltc[i-1] = pltc[i];
	}
	length--;
}

void LopTinChi::Show_Student_InClass(){ // 4,5+GetConsoleHeight()/2
	bool move = true, esc = false; char c; int x = 4, y = 5+GetConsoleHeight()/2;
	int from = 0, to = (dssvtt->getLength() < 7 ? dssvtt->getLength():7);
	Message("AN ESC DE QUAY LAI",GREEN);
	while(true){
		if (move){
			move = false;
			clearRect(x,y+2,87,16);
			dssvtt->ShowListStudent(x,y,from,to);
		}
		c = getch();
		if (c == -32){
			c = getch();
			if (c == 75){ // left arrow - Lui
				if (from != 0){ // Neu from = 0 thi` ko can` phai~ chuyen~ trang
					move = true;
					to = from;
				}
				if (from - 7 < 0){ // Neu dang o~ trang dau tien thi` ko can` phai~ thay doi~ thong so
					from = 0;
				}
				else from -= 7;
			}
			if (c == 77){ // right arrow - Tien
				if (to != dssvtt->getLength()){ // Neu to van~ con` co` the~ tien toi thi` tiep tuc 
					move = true;
					from = to;
				} 
				// vd: from = 0, to = 10, in ra array tu 0->9, thi minh chi can gan from = to se` in ra bat dau o ptu~ 10
				if (to + 7 > dssvtt->getLength()){ // Neu to+10 > do dai ds thi` set to = max length cua~ ds
					to = dssvtt->getLength();
				}
				else to += 7; // neu ko thi` to += 10
			}
		}
		if (c == 27){ // ESC
			clearRect(x,y-1,87,19);
			clearMessage();
			break;
		}
	}
}

void LopTinChi::Delete_Student_InClass(string mssv, string malop){
//	RemoveSpace(mssv,false); ToUpper(mssv);
//	for(int i=0;i<length;i++){
//		if (ltc[i].dssv->CheckStudentExist(mssv,malop)){
//			ltc[i].dssv->DeleteStudent(mssv,malop);
//		}
//	}
}

void LopTinChi::Edit_Student_InClass(string mssv, string malop, SINHVIEN sv_in){
//	RemoveSpace(mssv,false); ToUpper(mssv);
//	for(int i=0;i<length;i++){
//		ltc[i].dssv->EditStudent(mssv,malop,sv_in);
//	}
}

void LopTinChi::ShowClassList(int x, int y, int from, int to){
	if (length != 0){
		// TITLE FRAME
		drawRect(x,y,85,2);
		draw_high_line(x+6,y,2);
		draw_high_line(x+22,y,2);
		draw_high_line(x+36,y,2);
		draw_high_line(x+46,y,2);
		draw_high_line(x+56,y,2);
		draw_high_line(x+72,y,2);
		// TITLE NAME
		drawText(x+1,y+1,"MALOP",WHITE);
		drawText(x+13,y+1,"MAMH",WHITE);
		drawText(x+25,y+1,"NIEN KHOA",WHITE);
		drawText(x+39,y+1,"HOC KI",WHITE);
		drawText(x+49,y+1,"NHOM",WHITE);
		drawText(x+59,y+1,"SO SV TOI DA",WHITE);
		drawText(x+76,y+1,"CON LAI",WHITE);
		for(int i=from;i<to;i++){
			// ELEMENT FRAME
			drawRect(x,y+2*(i-from+1),85,2);
			draw_high_line(x+6,y+2*(i-from+1),2);
			draw_high_line(x+22,y+2*(i-from+1),2);
			draw_high_line(x+36,y+2*(i-from+1),2);
			draw_high_line(x+46,y+2*(i-from+1),2);
			draw_high_line(x+56,y+2*(i-from+1),2);
			draw_high_line(x+72,y+2*(i-from+1),2);
			gotoxy(x,y+2*(i-from+1)); printf("%c",195);
			gotoxy(x+6,y+2*(i-from+1)); printf("%c",197);
			gotoxy(x+22,y+2*(i-from+1)); printf("%c",197);
			gotoxy(x+36,y+2*(i-from+1)); printf("%c",197);
			gotoxy(x+46,y+2*(i-from+1)); printf("%c",197);
			gotoxy(x+56,y+2*(i-from+1)); printf("%c",197);
			gotoxy(x+72,y+2*(i-from+1)); printf("%c",197);
			gotoxy(x+85,y+2*(i-from+1)); printf("%c",180);
			// ELEMENT DATA
			drawNumber(x+2,y+2*(i-from+1)+1,pltc[i]->malop,WHITE);
			drawText(x+8,y+2*(i-from+1)+1,pltc[i]->MAMH,WHITE);
			drawText(x+25,y+2*(i-from+1)+1,pltc[i]->nienkhoa,WHITE);
			drawNumber(x+41,y+2*(i-from+1)+1,pltc[i]->hocki,WHITE);
			drawNumber(x+51,y+2*(i-from+1)+1,pltc[i]->nhom,WHITE);
			drawNumber(x+63,y+2*(i-from+1)+1,pltc[i]->sv_max,WHITE); 
			drawNumber(x+78,y+2*(i-from+1)+1,pltc[i]->sv_max - pltc[i]->ds->getLength(),WHITE);
		}
	}
}

void LopTinChi::Score_Table(bool edit, int vitri, SinhVien *dssv){
	// - Chi chinh sua trong vector showlist
//	// - Neu an ESC -> ctr se~ thong báo "Co dong ý hay ko", néu dong ý thì se~ save lai. vào trong dslk diem
//	// - Neu an ENTER thi` se~ xuat hien con tro~ ngay diem~ cho~ do de~ chinh sua 
	system("cls");
	dsdtt->ResetList(); // reset ds diem~ tam. thoi`
	dssvtt->ResetList(); // reset ds sv tam. thoi`
	for(NODED *p = pltc[vitri]->ds->getList(); p != NULL; p = p->next){
		dsdtt->Insert(p->d); // ds diem tam. thoi` them vào struct diem
		dssvtt->Insert(dssv->Search(p->d.mssv)->sv); // ds sv tam. thoi` them vào struct sinh vien = phuong thuc search
	}
	bool esc = false, press = true, move = true , enter = false;
	int cur = 0, pre = -1, page = 1, from = 0, to = (dsdtt->getLength() > 10 ? 10:dsdtt->getLength());
	int max = (dsdtt->getLength()%10 == 0 ? dsdtt->getLength()/10:1+dsdtt->getLength()/10);
	int x = GetConsoleWidth()/2 - 33, y = 15, choose;
	float diem;
//	// tat ca các bien nhu ben DANG KY LOPTINCHI 
	setColor(YELLOW);
	gotoxy(GetConsoleWidth()/2-10,10); cout << "BANG DIEM MON HOC " << pltc[vitri]->MAMH;
	gotoxy(GetConsoleWidth()/2-18,12); cout << "NIEN KHOA: " << pltc[vitri]->nienkhoa << " HOC KI: " << pltc[vitri]->hocki << " NHOM: " << pltc[vitri]->nhom;
	setColor(WHITE);
	while(true){
		if (page < max){  // if cho~ này dùng de~ tính toán vi trí cua dau '>>>>'
			if (cur < 0) cur = 9;
			if (cur > 9) cur = 0;
		}
		else{ // TH: page == max, trang cuói cùng có the~ ko du~ 10 phàn tu~
			if (dsdtt->getLength() % 10 == 0){ 
				// neu nhu so phan tu~ chia het cho 10 thì các trang deu == nhau ve` so phan tu~
				if (cur < 0) cur = 9;
				if (cur > 9) cur = 0;	
			}
			else{
				if (cur < 0) cur = to - 10*(to/10) - 1;
				if (cur > to - 10*(to/10) - 1) cur = 0;
			}
		}
		if (move){
			move = false;
			press = true;
			cur = 0; pre = -1;
			clearRect(x-5,y+3,78,20);
			Score_List(x,y,from,to);
		}
		if (press && edit){
			press = false;
			if (pre != -1){
				drawText(x-5,y+3+pre*2,">>>>",BLACK);
				drawText(x+68,y+3+pre*2,"<<<<",BLACK);
			}
			drawText(x-5,y+3+cur*2,">>>>",GREEN);
			drawText(x+68,y+3+cur*2,"<<<<",GREEN);
		}
		KeyPress_2(cur,pre,from,to,page,dsdtt->getLength(),press,move,esc,enter); // xu~ ly phím bam
		if (enter && edit){
			choose = cur+(page-1)*10;
			diem = dsdtt->getList()[choose].diem;
			// Day là phan` xu~ lý xem diem~ là so nguyen hay so thap phan, roi` dat con tro~ o~ dau de~ có the ghi ra
			if (diem == 10) InputScore(x+64,y+1+2*(cur+1),diem); // TH: diem = 10
			else if (diem - floor(diem) == 0){   // TH: diem là so nguyen diem = 1,2,3,4,...
				InputScore(x+63,y+1+2*(cur+1),diem);
			}
			else{	// TH: diem la so thap phan diem = 6.5; 8.9; 4.3
				InputScore(x+65,y+1+2*(cur+1),diem);
			}
//			gotoxy(1,1); cout << diem;
			dsdtt->Edit(diem,choose);
			pltc[vitri]->ds->Edit(dsdtt->getList()[choose].mssv,diem);
			enter = false;
		}
		if (esc && edit){ // neu nhu esc và mode edit = true thì nó se~ tìm trong dslk diem và thay doi~ theo cái showlist
			drawText(x + 20,y + 26,"Ban co chac chan khong [Y/N]",GREEN);
			if (Yes()) break;
			else esc = false;
			clearRect(x+18,y+26,32,1); // xoa dòng thong bao màu xanh
		}
		else if (esc && !edit) break; // TH if (esc && !edit)
	}
}

void LopTinChi::Score_List(int x, int y, int from, int to){
	drawRect(x,y,66,2);
	draw_high_line(x+8,y,2);
	draw_high_line(x+21,y,2);
	draw_high_line(x+50,y,2);
	draw_high_line(x+59,y,2);
	drawText(x+3,y+1,"STT",WHITE);
	drawText(x+13,y+1,"MSSV",WHITE);
	drawText(x+35,y+1,"HO",WHITE);
	drawText(x+54,y+1,"TEN",WHITE);
	drawText(x+61,y+1,"DIEM",WHITE);
	
	for(int i= from; i<to;i++){
		// FRAME ELEMENT
		drawRect(x,y+2*(i+1-from),66,2);
		draw_high_line(x+8,y+2*(i+1-from),2);
		draw_high_line(x+21,y+2*(i+1-from),2);
		draw_high_line(x+50,y+2*(i+1-from),2);
		draw_high_line(x+59,y+2*(i+1-from),2);
		
		gotoxy(x,y+2*(i+1-from)); printf("%c",195);
		gotoxy(x+8,y+2*(i+1-from)); printf("%c",197);
		gotoxy(x+21,y+2*(i+1-from)); printf("%c",197);
		gotoxy(x+50,y+2*(i+1-from)); printf("%c",197);
		gotoxy(x+59,y+2*(i+1-from)); printf("%c",197);
		gotoxy(x+66,y+2*(i+1-from)); printf("%c",180);
		
		drawNumber(x+4,y+1+2*(i+1-from),i+1,WHITE);
		drawText(x+11,y+1+2*(i+1-from),dsdtt->getList()[i].mssv,WHITE);
		drawText(x+24,y+1+2*(i+1-from),dssvtt->getList()[i].ho_tdem,WHITE);
		drawText(x+53,y+1+2*(i+1-from),dssvtt->getList()[i].ten,WHITE);
		gotoxy(x+62,y+1+2*(i+1-from)); cout << dsdtt->getList()[i].diem;
	}
}

void LopTinChi::FreeList(){
	for(int i=0;i<length;i++){
		free(pltc[i]);
	}
	free(pltc);
	dsdtt->FreeList();
	free(dsdtt);
	dssvtt->Freelist();
	free(dssvtt);
}
#endif

#ifndef DIEM_H
#define DIEM_H
typedef struct{
	string mssv;
	float diem;
}DIEM;

struct noded{
	DIEM d;
	noded *next;
};
typedef struct noded NODED;

class SvDangKy{
	private:
		NODED *first;
		NODED *last;
		int length;
		vector<DIEM> showlist;
	public:
		SvDangKy(){
			first = last = NULL;
			length = 0;
			
		}
		void Insert(DIEM d);
		int getLength();
		NODED *Search(string mssv);
		NODED *getList();
		void Sort();
		void Edit(string mssv, float diem);
//		void Mark_Table(bool edit, SinhVien *dssv); // bang~ cham diem~
//		void ShowListDiem(int x, int y, int from, int to, SinhVien *dssv);
};

void SvDangKy::Insert(DIEM d){ 
	NODED *tmp = new NODED;
	if (first == NULL){
		tmp->d = d;
		tmp->next = first; // Luc nay first dang == NULL
		first = last = tmp;
	}
	else{
		tmp->d = d;
		tmp->next = last->next;
		last->next = tmp;
		last = tmp;
	}
	length++;
}

int SvDangKy::getLength(){
	return length;
}

NODED *SvDangKy::Search(string mssv){
	if (first != NULL){
		for(NODED *p = first; p != NULL; p = p->next){
			if (p->d.mssv == mssv) return p;
		}
	}
	return NULL;
}

NODED *SvDangKy::getList(){
	return first;
}

void SvDangKy::Sort(){
	
}

void SvDangKy::Edit(string mssv, float diem){
	for(NODED *p = first; p != NULL; p = p->next){
		if (p->d.mssv == mssv){
			p->d.diem = diem;
			break;
		}
	}
}
//void Diem::Mark_Table(bool edit, SinhVien *dssv){ // truyen dssv vào de~ quet MSSV và lay cái ho và ten
//	// - Chi chinh sua trong vector showlist
//	// - Neu an ESC -> ctr se~ thong báo "Co dong ý hay ko", néu dong ý thì se~ save lai. vào trong dslk diem
//	// - Neu an ENTER thi` se~ xuat hien con tro~ ngay diem~ cho~ do de~ chinh sua 
//	system("cls");
//	bool esc = false, press = true, move = true , enter = false;
//	int cur = 0, pre = -1, page = 1, from = 0, to = (showlist.size() > 10 ? 10:showlist.size());
//	int max = (showlist.size()%10 == 0 ? showlist.size()/10:1+showlist.size()/10);
//	int x = GetConsoleWidth()/2 - 33, y = 15, choose;
//	// tat ca các bien nhu ben DANG KY LOPTINCHI 
//	if (showlist.size() == 0){ 
//		// báo loi~
//		getch();
//		return;
//	}
//	else{
//		setColor(YELLOW);
//		gotoxy(GetConsoleWidth()/2-10,10); cout << "BANG DIEM MON HOC " << showlist[0].MAMH;
//		gotoxy(GetConsoleWidth()/2-15,12); cout << "NIEN KHOA: " << showlist[0].nienkhoa << " HOC KI: " << showlist[0].hocki << " NHOM: " << showlist[0].nhom;
//		setColor(WHITE);
//	}
//	while(true){
//		if (page < max){  // if cho~ này dùng de~ tính toán vi trí cua dau '>>>>'
//			if (cur < 0) cur = 9;
//			if (cur > 9) cur = 0;
//		}
//		else{ // TH: page == max, trang cuói cùng có the~ ko du~ 10 phàn tu~
//			if (showlist.size() % 10 == 0){ // neu nhu so phan tu~ chia het cho 10 thì các trang deu == nhau ve` so phan tu~
//				if (cur < 0) cur = 9;
//				if (cur > 9) cur = 0;	
//			}
//			else{
//				if (cur < 0) cur = to - 10*(to/10) - 1;
//				if (cur > to - 10*(to/10) - 1) cur = 0;
//			}
//		}
//		if (move){
//			move = false;
//			press = true;
//			cur = 0; pre = -1;
//			clearRect(x-5,y+3,78,20);
//			ShowListDiem(x,y,from,to,dssv);
//		}
//		if (press && edit){
//			press = false;
//			if (pre != -1){
//				drawText(x-5,y+3+pre*2,">>>>",BLACK);
//				drawText(x+68,y+3+pre*2,"<<<<",BLACK);
//			}
//			drawText(x-5,y+3+cur*2,">>>>",GREEN);
//			drawText(x+68,y+3+cur*2,"<<<<",GREEN);
//		}
//		KeyPress_2(cur,pre,from,to,page,showlist.size(),press,move,esc,enter); // xu~ ly phím bam
//		if (enter && edit){
//			choose = cur+(page-1)*10;
//			// Day là phan` xu~ lý xem diem~ là so nguyen hay so thap phan, roi` dat con tro~ o~ dau de~ có the ghi ra
//			if (showlist[choose].diem == 10) InputScore(x+64,y+1+2*(cur+1),showlist[choose].diem,esc); // TH: diem = 10
//			else if (showlist[choose].diem - floor(showlist[choose].diem) == 0){   // TH: diem là so nguyen diem = 1,2,3,4,...
//				InputScore(x+63,y+1+2*(cur+1),showlist[choose].diem,esc);
//			}
//			else{	// TH: diem la so thap phan diem = 6.5; 8.9; 4.3
//				InputScore(x+65,y+1+2*(cur+1),showlist[choose].diem,esc);
//			}
////			gotoxy(1,1); cout << showlist[choose].diem;
//			enter = false;
//		}
//		if (esc && edit){ // neu nhu esc và mode edit = true thì nó se~ tìm trong dslk diem và thay doi~ theo cái showlist
//			drawText(x + 20,y + 26,"Ban co chac chan khong [Y/N]",GREEN);
//			if (Yes()){
//				for(int i=0;i<showlist.size();i++){
//					EditDiem(showlist[i]); // Truyen showlist tam. thoi` vào de~ chinh~ sua~ vào dslk chính
//				}
//				break;
//			}
//			else esc = false;
//			clearRect(x+18,y+26,32,1);
//		}
//		else if (esc && !edit) break; // TH if (esc && !edit)
//	}
//}

//void Diem::ShowListDiem(int x, int y, int from, int to, SinhVien *dssv){
//	if (showlist.size() > 0){
//		// FRAME TITLE 
//		drawRect(x,y,66,2);
//		draw_high_line(x+8,y,2);
//		draw_high_line(x+21,y,2);
//		draw_high_line(x+50,y,2);
//		draw_high_line(x+59,y,2);
//		drawText(x+3,y+1,"STT",WHITE);
//		drawText(x+13,y+1,"MSSV",WHITE);
//		drawText(x+35,y+1,"HO",WHITE);
//		drawText(x+54,y+1,"TEN",WHITE);
//		drawText(x+61,y+1,"DIEM",WHITE);
//		
//		for(int i= from; i<to;i++){
//			// FRAME ELEMENT
//			drawRect(x,y+2*(i+1-from),66,2);
//			draw_high_line(x+8,y+2*(i+1-from),2);
//			draw_high_line(x+21,y+2*(i+1-from),2);
//			draw_high_line(x+50,y+2*(i+1-from),2);
//			draw_high_line(x+59,y+2*(i+1-from),2);
//			
//			gotoxy(x,y+2*(i+1-from)); printf("%c",195);
//			gotoxy(x+8,y+2*(i+1-from)); printf("%c",197);
//			gotoxy(x+21,y+2*(i+1-from)); printf("%c",197);
//			gotoxy(x+50,y+2*(i+1-from)); printf("%c",197);
//			gotoxy(x+59,y+2*(i+1-from)); printf("%c",197);
//			gotoxy(x+66,y+2*(i+1-from)); printf("%c",180);
//			
//			drawNumber(x+4,y+1+2*(i+1-from),i+1,WHITE);
//			drawText(x+11,y+1+2*(i+1-from),showlist[i].mssv,WHITE);
//			drawText(x+24,y+1+2*(i+1-from),dssv->SearchAll(showlist[i].mssv)->sv.ho_tdem,WHITE);
//			drawText(x+53,y+1+2*(i+1-from),dssv->SearchAll(showlist[i].mssv)->sv.ten,WHITE);
//			gotoxy(x+62,y+1+2*(i+1-from)); cout << showlist[i].diem;
//		}
//	}
//}



#endif

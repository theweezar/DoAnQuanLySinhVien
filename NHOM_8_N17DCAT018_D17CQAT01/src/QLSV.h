#ifndef QLSV_H
#define QLSV_H

class QLSV{ // main program
	private:
		MonHoc *mh;
		SinhVien *sv;
		LopTinChi *ltc;
	public:
		QLSV(){
			resizeConsole(); // Lan` nay` khong can` setFullscreen nua~ vi` ham` da~ dc update hay hon
//			setFullscreen(); // Bo~ them cai set fullscreen nay` vao` vong lap trong menu o~ duoi
//			disableMinimize();
			mh = new MonHoc("..\\db\\monhoc.txt"); // Khoi tao ds cây mon hoc
			sv = new SinhVien("..\\db\\sinhvien.txt"); // Khoi tao dslk don cho sinh vien
			ltc = new LopTinChi("..\\db\\loptinchi.txt"); // Khoi tao. dstt cho loptinchi và truyen` du~ lieu. sv vào
		}
		void test(){
			system("cls");
			string nk = ""; //char s[10];
//			int p = 2019; itoa(p,s,10);
//			cout << s[0];
//			InputNienKhoa(5,5,nk); drawText(10,10,nk,WHITE);
		}
		// ============================= GUI MENU =============================== //
		void GUI_KeyMenu(int &pre, int &cur, bool &arrow_press, bool &esc, bool &enter);
		void GUI_Frame();
		void GUI_Menu();
		void GUI_MonHocMenu();
		void GUI_LopTinChiMenu();
		void GUI_SinhVienMenu();
		void GUI_DiemMenu();
		// ============================ GUI PRINT LIST ============================= //
		void GUI_Title_BangTongKet(int x, int y);
		void GUI_Element_BangTongKet(int x, int y);
		// ============================ PROCESS LOGIC ============================== //
		void clearInputLTC(int x, int y);
		void Frame_InputLTC(int x, int y);
		void InputLTC(int x, int y, int x_e, int y_e, LTC &tmp, bool &esc);
};

void QLSV::GUI_KeyMenu(int &pre, int &cur, bool &arrow_press, bool &esc, bool &enter){
	char c;
	if (kbhit()){
		c = getch();
		if (c == -32 || c == 0){ // nhung~ TH dac biet
	        c = getch();
	        if(c == 72){ // UP
				pre = cur--;
				arrow_press = true;
	        }
	        if(c == 80){ // DOWN
	        	pre = cur++;
	            arrow_press = true;
	        }
	    }
	    if (c == 27) esc = true;
	    if (c == 13) enter = true;
	}
}

void QLSV::GUI_Menu(){ // h = 15
	system("cls");
	const string menu_item[4] = {"DANH SACH MON HOC","DANH SACH LOP TIN CHI","DANH SACH SINH VIEN","DANH SACH DIEM"};
	int start_x = GetConsoleWidth()/2 - 25, start_y = GetConsoleHeight()/2 - 10 ;
	drawTitle_3(2,2);
	drawTitle_1(start_x+12,start_y - 4);
	char c; 
	// ======================== CHI TIET VE CO DINH ======================== //
	Cursor(false); // Lam con tro~ trong man hinh bien mat
	// ===================================================================== //
	int pre = -1, cur = 1;
	bool arrow_press = true, esc = false, enter = false;
	// LIET KE CAC TEN CHUC NANG CUA MENU, SAU DO VAO VONG WHILE MOI VE~ KHUNG (CHON / KO CHON)
	for(int i=1;i<=4;i++) drawText(start_x+25-menu_item[i-1].size()/2-1,start_y+i*6+1,menu_item[i-1],WHITE);
	while(true){
		if (cur > 4) cur = 1;
		if (cur < 1) cur = 4;
		if (arrow_press){
			if (pre > 0){
				frame_not_choose_item(start_x-1,start_y+pre*6-1,menu_item[pre-1],WHITE);
			}
			frame_choose_item(start_x-1,start_y+cur*6-1,menu_item[cur-1],YELLOW);
			arrow_press = false;
			gotoxy(0,0);
//			Sleep(200);
		}
		GUI_KeyMenu(pre,cur,arrow_press,esc,enter);
        if (esc){
        	mh->SaveData();
        	sv->SaveData();
        	ltc->SaveData();
        	mh->FreeThisTree();
        	sv->FreeThisList();
        	ltc->FreeList();
        	return;
		}
		if (enter){ 
			enter = false;// thieu dong nay` thi se~ bi loi~ ket phim enter, vi` khi thoat switch case ra thi` enter van = true
			arrow_press = true;
			// FIX THE ESC BUTTON
			switch(cur){ // 30 la` cai width cua~ rect nho~
				case 1:
					GUI_MonHocMenu();
					break;
				case 2:
					GUI_LopTinChiMenu();
					break;
				case 3:
					GUI_SinhVienMenu(); 
					break;
				case 4:
					GUI_DiemMenu();
					break;
				default: // de~ cho co truong hop thoi, ko can cung duoc
					break;
			}
			system("cls");
			// Ghi Lai Tat ca~
			drawTitle_3(5,2);
			drawTitle_1(start_x+12,start_y - 4);
			for(int i=1;i<=4;i++) drawText(start_x+25-menu_item[i-1].size()/2-1,start_y+i*6+1,menu_item[i-1],WHITE);
			// Tat con tro~
			Cursor(false);
		}
	}
}

void QLSV::GUI_Frame(){
	system("cls");
	// ====================== Draw line ========================= //
	draw_high_line(20+GetConsoleWidth()/2,0,GetConsoleHeight()-1);
	draw_flat_line(0,2+GetConsoleHeight()/2,20+GetConsoleWidth()/2-1);
	draw_flat_line(20+GetConsoleWidth()/2+1,2+GetConsoleHeight()/2,GetConsoleWidth()-(20+GetConsoleWidth()/2)-2);
	draw_flat_line(20+GetConsoleWidth()/2+1,49,GetConsoleWidth()-(20+GetConsoleWidth()/2)-2);
//	draw_high_line(47+GetConsoleWidth()/2+1,2+GetConsoleHeight()/2,19);
	// ======================= Left Button ============================ //
	drawButton(24+GetConsoleWidth()/2+2,2+GetConsoleHeight()/2+1,GREEN,5,0,"F1","Insert");
	drawButton(24+GetConsoleWidth()/2+2,2+GetConsoleHeight()/2+6,RED,5,0,"F2","Delete");
	drawButton(24+GetConsoleWidth()/2+2,2+GetConsoleHeight()/2+11,CYAN,5,0,"F3","Edit");
	drawButton(24+GetConsoleWidth()/2+2,2+GetConsoleHeight()/2+16,YELLOW,5,0,"F4","Search");
	// ======================= Right Button =========================== //
	drawButton(53+GetConsoleWidth()/2+2,2+GetConsoleHeight()/2+1,GREEN,6,0,"ENTER","Choose");
	drawButton(53+GetConsoleWidth()/2+2,2+GetConsoleHeight()/2+6,RED,6,0,"ESC","Back");
//	drawButton(49+GetConsoleWidth()/2+2,2+GetConsoleHeight()/2+11,CYAN,6,0,"<","Previous Page");
//	drawButton(49+GetConsoleWidth()/2+2,2+GetConsoleHeight()/2+16,YELLOW,6,0,">","Next Page");
	// ======================== DRAW So trang ============================ //
}

void QLSV::GUI_MonHocMenu(){
	GUI_Frame();
	bool reload = true, press = false, move = false, esc = false;
	// reload dung` de~ reload lai list khi them, xoa, dieu chinh mon hoc
	// press dung` de~ bat phim f1,f2,f3,f4
	// move dung` de~ chuyen~ sang trang khac trong list moi~ trang show (0 -> 10) ptu~
	int from = 0, to = 10, cur = 0, page = 1;
	string t = "Tim kiem theo MAMH: ", t_mamh = "", o_mamh = ""; // t_mamh: mamh input tam. thoi`, o_mamh: mamh cu~ 
//	drawNumber(40,27,page,WHITE);
	drawText(43,27,"/",WHITE);
	// FRAME SEARCH MON HOC
	drawRect(24+GetConsoleWidth()/2,2,45,4);
	drawText(26+GetConsoleWidth()/2,4,"Tim kiem theo MAMH: ",WHITE);
	drawRect(24+GetConsoleWidth()/2,7,45,19); // Cai khung duoi chu~ tim kiem theo MAMH
	while(true){
		if (reload){
			page = 1; from = 0; to = (mh->getLength() > 10 ? 10:mh->getLength()); 
			// if len > 10 => to = 10 else to = len ( len luc nay` se~ <= 10 )
			drawNumber(40,27,page,WHITE);
			drawNumber(46,27,(mh->getLength()%10 == 0 ? mh->getLength()/10:1+mh->getLength()/10),YELLOW);
			// vd: len = 20 => so trang chi~ co the la` 2 (len/10 = 2)
			// neu nhu len = 23 => so trang se~ co la` 3 (len/10 + 1 = 2+1 = 3)
			reload = false;
			mh->Sort(); // LNR - sort ds tam. thoi`
			clearRect(11,4,72,22); // Xoa het cac ptu~ de~ in ra trang tiep theo
			mh->ShowSubjectList(11,2,0,10);
		}
		if (move){
			move = false;
			clearRect(11,4,72,22); // Xoa het cac ptu~ de~ in ra trang tiep theo
			mh->ShowSubjectList(11,2,from,to);
			drawNumber(40,27,page,WHITE);
		}
		KeyPress_1(cur,from,to,page,mh->getLength(),reload,press,move,esc);
		if (esc) return;
		if (press){
			press = false;
			switch(cur){
				case 1: // Them mon hoc
					mh->CreateNewSubject(11,5+GetConsoleHeight()/2,reload);
					break;
				case 2: // Xoa mon hoc
					// Neu trong ltc có lop dang hoc mon nay` thi` ko dc xoa, phai~ xoa ltc truoc roi moi xoa mon hoc
					Cursor(true);
					InputString(26+GetConsoleWidth()/2+t.size(),4,2*GetConsoleWidth()/3+24,GetConsoleHeight()-4,10,t_mamh,false,esc); // 19 cho dep.
					if (esc){
						esc = false;
						clearRect(26+GetConsoleWidth()/2+t.size(),4,21,1);
						break;
					}
					else {
						RemoveSpace(t_mamh,false); ToUpper(t_mamh);
						if (ltc->CheckMAMH_Exist(t_mamh)){
							Message("KHONG XOA DUOC MON HOC VI DA MO LOP TIN CHI",RED);
							Pause(); clearMessage();
							clearRect(26+GetConsoleWidth()/2+t.size(),4,21,1); // ClearInput
						}
						else mh->Find(t_mamh,true,false,reload); // da~ có ToUpper trong hàm Find
					}
					break;
				case 3: // Chinh sua mon hoc
					// Khi chinh sua~ thanh cong thi` phai~ sua~ ma mon hoc trong ltc
					Cursor(true);
					InputString(26+GetConsoleWidth()/2+t.size(),4,2*GetConsoleWidth()/3+24,GetConsoleHeight()-4,10,t_mamh,false,esc); // 19 cho dep.
					if (esc){
						esc = false;
						clearRect(26+GetConsoleWidth()/2+t.size(),4,21,1);
						break;
					} 
					else{
						RemoveSpace(t_mamh,false);
						ToUpper(t_mamh);
						o_mamh = t_mamh;
						mh->Find(t_mamh,false,true,reload); // da~ có ToUpper trong hàm Find
					}
					if (reload){ // neu nhu edit thành cong thi` se~ vào ds ltc và ds diem~ de~ thay doi~ MAMH trong 2 ds dó
						ltc->ChangeMAMH(o_mamh,t_mamh); // Find(t_mamh,...) là tham bien nen khi thay doi~ trong do ra ngoai cung thay doi
					}
					break;
				case 4: // Tim mon hoc
					Cursor(true);
					InputString(26+GetConsoleWidth()/2+t.size(),4,2*GetConsoleWidth()/3+24,GetConsoleHeight()-4,10,t_mamh,false,esc); // 19 cho dep.
					if (esc){
						esc = false;
						clearRect(26+GetConsoleWidth()/2+t.size(),4,21,1);
						break;
					}
					else mh->Find(t_mamh,false,false,reload); // da~ có ToUpper trong hàm Find
					break;
				default:
					break;
			}
			Cursor(false);
			t_mamh = o_mamh = ""; // reset t_mamh và o_mamh
		}
	}
}
void QLSV::GUI_LopTinChiMenu(){
	// node mon hoc tam. thoi` de~ tim kiem xem mon hoc co ton ta.i hay ko
	LTC t_ltc, o_ltc; t_ltc = o_ltc = null_ltc; // Khoi tao. 1 bien struct LTC rong~
	bool reload = true, press = false, move = false, esc = false, enter = false;
	int from, to, cur1, page, pre = -1, cur2 = 1;
	string edit[2] = {"CHINH SUA THONG TIN LOP TIN CHI","SINH VIEN DANG KY LOP TIN CHI"};
	string n_mamh=""; //Bien string này dùng de~ kiem tra xem mon hoc nhap vao` co ton tai. hay ko, neu co thi` duyet tiep
	GUI_Frame();
	drawRect(24+GetConsoleWidth()/2,2,45,25);
	draw_flat_line(24+GetConsoleWidth()/2,20,45);
	// =================== FORM tim kiem lop tin chi ====================== //
	Frame_InputLTC(26+GetConsoleWidth()/2,4);
	// ==================================================================== //
	drawText(46,27,"/",WHITE);
	while(true){
		if (reload){
			page = 1; from = 0; to = (ltc->getLength() > 10 ? 10:ltc->getLength());
			// if len > 10 => to = 10 else to = len ( len luc nay` se~ <= 10 )
			reload = false;
			drawNumber(43,27,page,WHITE);
			drawNumber(49,27,(ltc->getLength()%10 == 10 ? ltc->getLength()/10:1+ltc->getLength()/10),YELLOW);
//			// Coi giai thich o phan` GUI_MonHocMenu()
			clearRect(4,5,87,22);
			ltc->ShowClassList(4,2,from,to);
		}
		if (move){
			move = false;
			clearRect(4,5,87,22); // Xoa het cac ptu~ de~ in ra trang tiep theo
			ltc->ShowClassList(4,2,from,to);
			drawNumber(43,27,page,WHITE);
		}
		KeyPress_1(cur1,from,to,page,ltc->getLength(),reload,press,move,esc);
		if (esc) return;
		if (press){
			switch(cur1){
				case 1: // Mo lop tin chi
					Cursor(true);
					drawRect(11,5+GetConsoleHeight()/2,60,4);
					drawText(12,7+GetConsoleHeight()/2,"NHAP MA MON HOC : ",WHITE);
					InputString(12+18,7+GetConsoleHeight()/2,2*GetConsoleWidth()/3+24,GetConsoleHeight()-4,10,n_mamh,false,esc);
					if (esc){
						esc = false;
						clearRect(11,5+GetConsoleHeight()/2,62,20);
					}
					else{
						RemoveSpace(n_mamh,false); ToUpper(n_mamh); 
						clearRect(11,5+GetConsoleHeight()/2,62,20); // xóa o nhap ma mon hoc
						if (mh->CheckExist(n_mamh)){ // Kiem tra mon hoc có ton` tai. hay ko
							ltc->CreateNewClass(11,5+GetConsoleHeight()/2,n_mamh,reload);
						}
						else{ // Neu ko thì báo loi~
							Message("KHONG CO MON HOC. BAM PHIM BAT KY DE TIEP TUC",RED); Cursor(false);
							getch();
							clearMessage();
						}
					}
					n_mamh = ""; // reset
					break;
				case 2: // Xoa lop tin chi - 
					clearRect(26+GetConsoleWidth()/2,22,40,5); // xóa dòng thong báo màu vàng
					InputLTC(26+GetConsoleWidth()/2,4,2*GetConsoleWidth()/3+24,GetConsoleHeight()-4,t_ltc,esc);
					if (esc) break;
					else ltc->Find(t_ltc,true,false,reload,sv);
					clearInputLTC(26+GetConsoleWidth()/2,4);
					break;
				case 3: // Chinh sua lop tin chi gom (chinh sua thong tin - dang ky sinh vien)
					clearRect(26+GetConsoleWidth()/2,22,40,5); // xóa dòng tb màu vàng
					for(int i=1;i<=2;i++) frame_not_choose_item(4+GetConsoleWidth()/8,30+i*7,edit[i-1],WHITE);
					while(true){
						if (cur2 > 2) cur2 = 1;
						if (cur2 < 1) cur2 = 2;
						if (press){
							press = false;
							if (pre > 0) frame_not_choose_item(4+GetConsoleWidth()/8,30+pre*7,edit[pre-1],WHITE);
							frame_choose_item(4+GetConsoleWidth()/8,30+cur2*7,edit[cur2-1],BLUE);
//							Sleep(200);
						}
						GUI_KeyMenu(pre,cur2,press,esc,enter);
						if (esc){
							esc = false;
							clearRect(11,5+GetConsoleHeight()/2,65,20); // Xóa menu con 2 item
							break;
						}
						if (enter){
							clearRect(4,35,80,15);
							enter = false;
							switch(cur2){
								case 1: // Chinh sua thong tin lop tin chi
									InputLTC(26+GetConsoleWidth()/2,4,2*GetConsoleWidth()/3+24,GetConsoleHeight()-4,t_ltc,esc); // Input de~ tìm ltc
									if (esc) break;
									else ltc->Find(t_ltc,false,true,reload,sv);
									break;
								case 2: // sinh vien dang ky lop tin chi
									SINHVIEN t_sv = null_sv;
									// ========= FRAME - Nhap mssv voi ma lop ========= //
									drawRect(GetConsoleWidth()/8,5+GetConsoleHeight()/2,59,10);
									drawText(25+GetConsoleWidth()/8,7+GetConsoleHeight()/2,"NHAP MSSV",CYAN);
									drawText(3+GetConsoleWidth()/8,11+GetConsoleHeight()/2,"MSSV   : ",WHITE);
									InputString(12+GetConsoleWidth()/8,11+GetConsoleHeight()/2,2*GetConsoleWidth()/3+24,GetConsoleHeight()-4,20,t_sv.mssv,false,esc);
									if (esc){
										clearRect(GetConsoleWidth()/8,5+GetConsoleHeight()/2,62,18);
										// xóa cái bang~ nhap. thong tin sv trong phàn dang ky ltc
										break;
									}
									RemoveSpace(t_sv.mssv,false); ToUpper(t_sv.mssv);
									if (sv->Search(t_sv.mssv) != NULL){ // kt xem sv có ton` tai hay ko
										clearRect(GetConsoleWidth()/8,5+GetConsoleHeight()/2,62,18); // xóa cái bang~ nhap. thong tin sv trong phàn dk ltc
										t_sv = sv->Search(t_sv.mssv)->sv; // gán t_sv = sv tìm dc trong main list
										ltc->RegisterStudent(t_sv);
									}
									else{
										Message("SINH VIEN KHONG TON TAI. BAM PHIM BAT KY",RED);
										clearRect(GetConsoleWidth()/8,5+GetConsoleHeight()/2,62,18); 
										getch(); clearMessage();
									}
									break;
							}
							pre = -1, cur2 = 1; // reset cho cái menu nho~ trong edit
							reload = true; // reload lai. de~ ve~ ra lai. cái ds
							GUI_Frame();
							// ve~ lai toàn bo. khung frame
							drawRect(24+GetConsoleWidth()/2,2,45,25);
							draw_flat_line(24+GetConsoleWidth()/2,20,45);
							// =================== FORM tim kiem lop tin chi ====================== //
							Frame_InputLTC(26+GetConsoleWidth()/2,4);
							// ==================================================================== //
							drawText(46,27,"/",WHITE);
							break;
						}
					}
					break;
				case 4: // Tim lop tin chi - và in ra ds sv trong lop tin chi dó
					clearRect(26+GetConsoleWidth()/2,22,40,5); // xóa dòng thong báo màu vàng
					InputLTC(26+GetConsoleWidth()/2,4,2*GetConsoleWidth()/3+24,GetConsoleHeight()-4,t_ltc,esc);
					if (esc) break;
					else{
						ltc->Find(t_ltc,false,false,reload,sv);
						clearInputLTC(26+GetConsoleWidth()/2,4);
					}
					break;
				default:
					break;
			}
			Cursor(false);
			t_ltc = o_ltc = null_ltc; // reset bién struct LOPTINCHI tmp
			press = esc = false; 
			// reset 2 bien này vì 2 bién này dc dùng chung khá nhieu`, néu ko reset thì ko ra khoi~ if (press) nó se~ lap. tuc out ra
			// hoac lai. tiep tuc. thuc. hien. chuc nang truoc dó 1 làn nua~
		}
	}
}
void QLSV::GUI_SinhVienMenu(){
	// Nhap ma lop truoc
	Cursor(true);
	GUI_Frame();
	bool reload = true, press = false, move = false, esc = false;
	int from, to, page, cur;
	string t_malop;
	// ========================= Phan` giao dien de~ nhap MA LOP =================================== //
	drawRect((20+GetConsoleWidth()/2)/2-19,10,37,4);
	drawText((20+GetConsoleWidth()/2)/2-17,12,"NHAP MA LOP: ",YELLOW);
	while(true){
		// Nhap vao` ma~ lop => scan list de~ lay so sv co cung malop vao` 1 vector
		// Tiep tuc sort vector do de~ sap xep ten sv tang dan`
		InputString((20+GetConsoleWidth()/2)/2-17+13,12,2*GetConsoleWidth()/3+24,GetConsoleHeight()-4,15,t_malop,false,esc);
		//RemoveSpace(t_malop,false); ToUpper(t_malop);
		if (esc) return;
		RemoveSpace(t_malop,false); ToUpper(t_malop);
		if (sv->CheckClassID_Exist(t_malop)) break;
		else { // neu malop khong ton` tai. thì hoi~ có nen tao. lop moi hay ko?
			Message("LOP KHONG TON TAI. CO TAO MOI[Y/N]",GREEN);
			if (Yes()){
				break;
			}
			else{
				t_malop = ""; // 1 dang. unset
				clearRect((20+GetConsoleWidth()/2)/2-17+13,12,19,1); // clear cái dòng input
			}
			clearMessage();
		}
	} 
	clearMessage();
	// ========================== Phan` giao dien in ra danh sach voi ma lop  =========================== //
	Cursor(false); string t = "Tim kiem theo MSSV: ", t_mssv = "";
	drawText(46,27,"/",WHITE);
	drawRect(24+GetConsoleWidth()/2,2,45,4);
	drawText(26+GetConsoleWidth()/2,4,t,WHITE);
	drawRect(24+GetConsoleWidth()/2,7,45,19); // Cai khung duoi chu~ tim kiem theo MAMH
	sv->FilterStudentByClass(t_malop); // Loc. lai. vector tam. thoi` dùng de~ show ra, neu nhu add, del, edit
	while(true){
		if (reload){
			sv->SortByName(); // Sort lai. theo ten a-z
			page = 1; from = 0; to = (sv->dstt->getLength() > 10 ? 10:sv->dstt->getLength()); //(sv->getShowListLength() > 10 ? 10:sv->getShowListLength());
			reload = false;
			drawNumber(43,27,page,WHITE);
			drawNumber(49,27, (sv->dstt->getLength()%10 == 0 ? sv->dstt->getLength()/10:1+sv->dstt->getLength()/10) ,YELLOW);
//			drawNumber(49,27, (sv->getShowListLength()%10 == 0 ? sv->getShowListLength()/10:1+sv->getShowListLength()/10) ,YELLOW);
			clearRect(3,4,87,21);
//			sv->Show_Student_List(3,2,from,to);
			sv->dstt->ShowListStudent(3,2,from,to);
		}
		if (move){
			move = false;
			clearRect(3,4,87,21);
//			sv->Show_Student_List(3,2,from,to);
			sv->dstt->ShowListStudent(3,2,from,to);
			drawNumber(43,27,page,WHITE);
		}
//		KeyPress_1(cur,from,to,page,sv->getShowListLength(),reload,press,move,esc);
		KeyPress_1(cur,from,to,page,sv->dstt->getLength(),reload,press,move,esc);
		if (esc) return;
		if (press){
			press = false;
			string old_mssv=""; // dùng cho phan` edit sinh vien
			switch(cur){
				case 1: // Them 1 sinh vien moi
					sv->CreateNewStudent(11,5+GetConsoleHeight()/2,t_malop,reload);
					break;
				case 2: // xoa 1 sinh vien, khi xoa thanh cong phai~ tim` trong ltc 
					Cursor(true);
					InputString(26+GetConsoleWidth()/2+t.size(),4,2*GetConsoleWidth()/3+24,GetConsoleHeight()-4,20,t_mssv,false,esc);
					if (esc){
						esc = false;
						clearRect(26+GetConsoleWidth()/2+t.size(),4,21,1);
						break;
					}
					else sv->Find(t_malop,t_mssv,true,false,reload); // da~ dùng ToUpper trong hàm Find ròi
					if (reload){ // Khi xóa thành cong thì reload se~ = true
						ltc->Delete_Student_InClass(t_mssv,t_malop);
					}
					break;
				case 3: //chinh sua 1 sinh vien, khi chinh sua thanh cong thi` phai~ chinh~ luon ca~ mssv trong ltc va diem
					Cursor(true); 
					InputString(26+GetConsoleWidth()/2+t.size(),4,2*GetConsoleWidth()/3+24,GetConsoleHeight()-4,20,t_mssv,false,esc);
					if (esc){
						esc = false;
						clearRect(26+GetConsoleWidth()/2+t.size(),4,21,1);
						break;
					}
					else{
						old_mssv = t_mssv; RemoveSpace(old_mssv,false); ToUpper(old_mssv);
						sv->Find(t_malop,t_mssv,false,true,reload); // da~ dùng ToUpper trong hàm Find ròi
						// Sau khi edit thành cong thì t_mssv là tham tri. nen se~ thay doi~ khi quay lai. day
					}
					if (reload){
						// Khi thay doi~ thành cong sinh vien thì reload = true. Lúc này ta phai~ thay doi~ thong tin
						// cua~ sinh vien trong tat ca lop tin chi neu sv do có ton` tai. trong dó
						// Và thay doi~ luôn mssv trong ds diem~
						ltc->Edit_Student_InClass(old_mssv,t_malop,sv->Search(t_mssv)->sv); // sv-> là thang moi vua` edit
						// Tìm thông tin sv voi mssv cu~ (old_mssv) va` thay doi~ nó = sv->Search(t_mssv,t_malop)->sv
					}
					break; 
				case 4: // Tim thong tin 1 sinh vien
					Cursor(true);
					InputString(26+GetConsoleWidth()/2+t.size(),4,2*GetConsoleWidth()/3+24,GetConsoleHeight()-4,20,t_mssv,false,esc);
					if (esc){
						esc = false;
						clearRect(26+GetConsoleWidth()/2+t.size(),4,21,1);
						break;
					}
					sv->Find(t_malop,t_mssv,false,false,reload); // da~ dùng ToUpper trong hàm Find ròi
					break;
				default:
					break;
			}
			Cursor(false);
			t_mssv = "";
		}
	}
	
}

void QLSV::GUI_DiemMenu(){
	string item[4] = {"NHAP DIEM","IN DIEM THEO LOP TIN CHI","IN DIEM KHOA HOC THEO LOP","IN BANG DIEM TONG KET"};
	string malop;
	int start_x = GetConsoleWidth()/2 - 25, start_y = GetConsoleHeight()/2 - 10, nk = 0;
	clearRect(start_x - 5, start_y + 5, 60, 25);
	bool press = true, enter = false, esc = false;
	int pre = -1, cur = 1; 
	for(int i=1;i<=2;i++) drawText(start_x+25-item[i-1].size()/2-1,start_y+i*6+1,item[i-1],WHITE);
//	LOPTINCHI t_ltc; // vì de~ nhap. diem~ hoac in diem thì deu` phai~ nhap. 4 yeu to trong struct LOPTINCHI
	while(true){
		if (cur > 2) cur = 1;
		if (cur < 1) cur = 2;
		if(press){
			press = false;
			if (pre > 0){
				frame_not_choose_item(start_x-1,start_y+pre*6-1,item[pre-1],WHITE);
			}
			frame_choose_item(start_x-1,start_y+cur*6-1,item[cur-1],YELLOW);
		}
		GUI_KeyMenu(pre,cur,press,esc,enter);
		if (enter){
			LTC t_ltc = null_ltc; // reset struct LOPTINCHI tam. thoi`
			system("cls");
			string e = "LOP TIN CHI KHONG TON TAI HOAC CHUA CO SV DANG KY. AN PHIM BAT KY DE TIEP TUC";
			char c; // dùng de pause
//			VeDauCongChiaDoi();
			switch(cur){
				case 1: // Nhap diem
					while(true){
						bool err = false;
						drawRect(GetConsoleWidth()/2-22,GetConsoleHeight()/2-13,44,20); // ve khung hinh chu nhat
						Frame_InputLTC(GetConsoleWidth()/2-20,GetConsoleHeight()/2-10); // Ve may dòng input
						InputLTC(GetConsoleWidth()/2-20,GetConsoleHeight()/2-10,GetConsoleWidth()/2,15+GetConsoleHeight()/2,t_ltc,esc);
//						// Input string cho 4 dòng trong do
						if (esc) break;
						int vt = ltc->getPosition(t_ltc);
						if (vt != -1){
							ltc->Score_Table(true,vt,sv);
							break;
						}
						else err = true;
						if (err){ // Báo loi~ và reset du~ lieu tam. thoi`
							drawText(GetConsoleWidth()/2 - e.size()/2,GetConsoleHeight()/2+15,e,RED);
							Pause();
							clearRect(GetConsoleWidth()/2 - e.size()/2,GetConsoleHeight()/2+15,e.size(),1);
							clearInputLTC(GetConsoleWidth()/2-20,GetConsoleHeight()/2-10);
							t_ltc = null_ltc; // reset
						}
					}
					break;
				case 2: // In ds diem theo lop tin chi - chua giai quyet xog - phat hien bug
					while(true){
						bool err = false;
						drawRect(GetConsoleWidth()/2-22,GetConsoleHeight()/2-13,44,20); // ve khung hinh chu nhat
						Frame_InputLTC(GetConsoleWidth()/2-20,GetConsoleHeight()/2-10); // Ve may dòng input
						InputLTC(GetConsoleWidth()/2-20,GetConsoleHeight()/2-10,GetConsoleWidth()/2,15+GetConsoleHeight()/2,t_ltc,esc);
//						// Input string cho 4 dòng trong do
						if (esc) break;
						int vt = ltc->getPosition(t_ltc);
						if (vt != -1){
							ltc->Score_Table(false,vt,sv);
							break;
						}
						else err = true;
						if (err){ // Báo loi~ và reset du~ lieu tam. thoi`
							drawText(GetConsoleWidth()/2 - e.size()/2,GetConsoleHeight()/2+15,e,RED);
							Pause();
							clearRect(GetConsoleWidth()/2 - e.size()/2,GetConsoleHeight()/2+15,e.size(),1);
							clearInputLTC(GetConsoleWidth()/2-20,GetConsoleHeight()/2-10);
							t_ltc = null_ltc; // reset
						}
					}
					break;
				case 3: // In ds diem theo lop vd d17attt
//					malop = "";
//					drawRect(GetConsoleWidth()/2-22,GetConsoleHeight()/2-10,44,7);
//					drawText(GetConsoleWidth()/2-20,GetConsoleHeight()/2-8,"NHAP MA LOP: ",WHITE);
//					drawText(GetConsoleWidth()/2-20,GetConsoleHeight()/2-5,"NIEN KHOA  : ",WHITE);
//					InputString(GetConsoleWidth()/2-7,GetConsoleHeight()/2-8,GetConsoleWidth()/2,GetConsoleHeight()/2,20,malop,false,esc);
//					if (esc) break;
//					RemoveSpace(malop,false); ToUpper(malop);
//					InputNumber(GetConsoleWidth()/2-7,GetConsoleHeight()/2-5,GetConsoleWidth()/2,GetConsoleHeight()/2,nk,4,true,esc);
//					if (esc) break;
//					// so tin chi max = 18
//					// lay tat ca sv trong 1 lop. vd: d17attt
//					// dò tung` sv voi dssv trong ltc neu có thì dò tiep trong ds diem cong. dòn tu` tu` roi lát chia
//					// cho 18
//					// neu sv co trong dssv cua ltc mà ko có trong dssv diem~ thì. Insert vào roi` cong don` tiep
//					getch();
					break;
				case 4:
					break;
			}
			enter = esc = false;
			system("cls");
			for(int i=1;i<=2;i++) drawText(start_x+25-item[i-1].size()/2-1,start_y+i*6+1,item[i-1],WHITE);
			press = true;
			Cursor(false);
			drawTitle_3(2,2);
			drawTitle_1(GetConsoleWidth()/2 - 13,GetConsoleHeight()/2 - 14);
		}
		if (esc) return;
	}
}

void QLSV::GUI_Title_BangTongKet(int x, int y){
	
}
void QLSV::GUI_Element_BangTongKet(int x, int y){
	
}

void QLSV::clearInputLTC(int x, int y){
	clearRect(x+13,y+3,10,1); // 4 dòng này de~ xóa 4 dòng cho~ nhap. thong tin
	clearRect(x+13,y+6,10,1);
	clearRect(x+13,y+9,10,1);
	clearRect(x+13,y+12,10,1);
}
void QLSV::Frame_InputLTC(int x, int y){
	drawText(x+7,y,"FORM NHAP THONG TIN TIM KIEM",CYAN); // x + 7
	drawText(x,y+3, "Ma mon hoc : ",WHITE);
	drawText(x,y+6,"Nien khoa  : ",WHITE);
	drawText(x,y+9,"Hoc ki     : ",WHITE);
	drawText(x,y+12,"Nhom       : ",WHITE);
}
void QLSV::InputLTC(int x, int y, int x_e, int y_e, LTC &tmp, bool &esc){ // int x + 13
	Cursor(true);
	clearInputLTC(26+GetConsoleWidth()/2,4);
	InputString(x+13,y+3,x_e,y_e,10,tmp.MAMH,false,esc);
	if (esc){
		clearInputLTC(26+GetConsoleWidth()/2,4);
		return;
	}
	RemoveSpace(tmp.MAMH,false);ToUpper(tmp.MAMH);
	InputNienKhoa(x+13,y+6,tmp.nienkhoa,esc);
	if (esc){
		clearInputLTC(26+GetConsoleWidth()/2,4);
		return;
	}
	InputNumber(x+13,y+9,x_e,y_e,tmp.hocki,1,true,esc);
	if (esc){
		clearInputLTC(26+GetConsoleWidth()/2,4);
		return;
	}
	InputNumber(x+13,y+12,x_e,y_e,tmp.nhom,1,true,esc);
	if (esc){
		clearInputLTC(26+GetConsoleWidth()/2,4);
		return;
	}
	Cursor(false);
}
#endif

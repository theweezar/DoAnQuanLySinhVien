#ifndef MONHOC_H
#define MONHOC_H
typedef struct{ 
	string tenmh; // ten mon hoc
	int stclt; // tin chi ly thuyet
	int stcth; // tin chi thuc hanh
}MONHOC;
const MONHOC null_mh = {"",0,0}; 
struct nodemh{
	string MAMH; // unique - key - max length = 10
	MONHOC mh;
	nodemh *right;
	nodemh *left;
};
typedef struct nodemh NODEMH;

class dsmh_tamthoi{
	private:
		MONHOC *mhtt;
		string *mamh_tt;
		int length;
	public:
		dsmh_tamthoi(int length_in){
			mhtt = new MONHOC[length_in];
			mamh_tt = new string[length_in];
			length = 0;
		}
		MONHOC *getList_struct(){
			return mhtt;
		}
		string *getList_mamh(){
			return mamh_tt;
		}
		int getLength(){
			return length;
		}
		void Insert(string mamh, MONHOC mh){
			mamh_tt[length] = mamh;
			mhtt[length] = mh;
			length++;
		}
		void FreeList(){
			mhtt = NULL; mamh_tt = NULL;
		}
		void ResetList(){
			length = 0;
		}
};

class MonHoc{ // ds cay nhi phan
	private:
		NODEMH *root;
		int length;
		const char *link;
//		vector<string> listmamh; // Dung de~ in ra danh sach
//		vector<MONHOC> listmh; // Dung de~ in ra danh sach
	public:
		dsmh_tamthoi *dsmhtt; // danh sach mon hoc tam. thoi` - dùng de~ in ra màn hình
		MonHoc(const char *linkIn){
			link = linkIn;
			root = NULL;
			length = 0; // khoi tao
			dsmhtt = new dsmh_tamthoi(100);
			if (!file_exist(link)){ // neu file ko ton` tai. thì tao. 1 file moi và ghi chu~ NULL_ vào
				ofstream f(link);
				f << "NULL_";
				f.close();
			}
			else LoadData();
		}
		void LoadData();
		void SaveData();
		NODEMH *getTree();
		int getLength();
		void FrameInput(int x, int y);
		void NLR(NODEMH *nmh, ofstream &f); // Duyet cay de~ ghi vao` file - Preorder
		void CreateNewSubject(int x, int y, bool &reload);
		void Insert(NODEMH *&nmh,string MAMH_in, MONHOC mh);
		NODEMH *GetNodeBySearch(string mamh);
		bool CheckExist(string mamh);
		void Find(string &t_mamh, bool findtodel, bool findtoedit, bool &reload); // GUI Find and Delete
		void EditSubject(string old_mamh, string new_mamh, MONHOC new_mh);
		void DeleteRightOrLeftNULL(NODEMH *&nmh, string mamh); // Case 1, 2: left or right NULL
		void DeleteBothNotNULL(NODEMH *&min, NODEMH *rp); // case 3: left and right both not NULL, rp = replace
		void ShowSubjectList(int x, int y, int from, int to);
//		void ShowSubjectElement(int x, int y);
		void Sort();
		void LNR(NODEMH *nmh); // Duyet cay de~ in ra ds theo ten mon hoc tang dan - Inorder
		void FreeThisTree();
		void LRN(NODEMH *nmh); // Delete nguyen cai cay bang cach duyet LRN - Posorder
};
void MonHoc::LoadData(){
	ifstream f(link);
	string t_mamh = "", line; // line for get down new line
	MONHOC t_mh;
	while(t_mamh != "NULL"){ // dieu kien de~ dung` lai.
		getline(f,t_mamh,'_');
		if (t_mamh != "NULL"){ // Dieu kien de~ khoi~ phai~ insert thang` NULL cuoi cùng
			getline(f,t_mh.tenmh,'_');
			f >> t_mh.stclt >> t_mh.stcth;
			getline(f,line); // xuong hàng
			Insert(root,t_mamh,t_mh);
			length += 1;
		}
		fflush(stdin);
	}
	f.close();
}

void MonHoc::SaveData(){
	ofstream f(link);
	NLR(root,f); // goi ham` de quy duyet cay
	f << "NULL_"; // Ghi moc danh dau het.
	f.close();
}

NODEMH *MonHoc::getTree(){
	return root;
}

int MonHoc::getLength(){
	return length;
}

void MonHoc::FrameInput(int x, int y){
	// FRAME
	drawRect(x,y,60,16);
	// DUONG THANG NAM NGANG
	draw_flat_line(x,4+y,60);
	draw_flat_line(x,8+y,60);
	draw_flat_line(x,12+y,60);
	// TITLE // length = 16, max string = 42
	drawText(x+1,y+2,  "MA MON HOC     :",WHITE);
	drawText(x+1,4+y+2,"TEN MON HOC    :",WHITE);
	drawText(x+1,8+y+2,"STC LY THUYET  :",WHITE);
	drawText(x+1,12+y+2,"STC THUC HANH  :",WHITE);
}

void MonHoc::NLR(NODEMH *nmh, ofstream &f){
	if (nmh != NULL){
		f << nmh->MAMH << "_" << nmh->mh.tenmh << "_" << nmh->mh.stclt << " " << nmh->mh.stcth << endl;
		NLR(nmh->left,f);
		NLR(nmh->right,f);
	}
}

void MonHoc::CreateNewSubject(int x, int y, bool &reload){
	Cursor(true);
	MONHOC tmp = null_mh; // gán cho tenmh = "", và 2 bien int = 0
	string mamh; char c;
	bool esc = false;
	FrameInput(x,y);
	// NHAP THONG TIN
	// ====================================== KIEM TRA LOI~ TON` TAI. MAMH ==================================== //
	while(true){
		InputString(x+1+17,y+2,2*GetConsoleWidth()/3+24,GetConsoleHeight()-4,10,mamh,false,esc);
		if (esc){
			clearRect(x,y,62,20); gotoxy(0,0); return;
		}
		RemoveSpace(mamh,false); ToUpper(mamh);
		if (GetNodeBySearch(mamh) == NULL) break;
		else{
			Message("TRUNG MA MON HOC. AN PHIM BAT KY",RED);
			c = getch();
			if (c == -32 || c == 0) c = getch();
			clearMessage();
			clearRect(x+1+17,y+2,mamh.size(),1); // xóa input mamh, dúng voi size cua~ nó
			mamh = ""; // reset mamh
		}
	}
	// ========================================================================================================== //
	InputString(x+1+17,4+y+2,2*GetConsoleWidth()/3+24,GetConsoleHeight()-4,40,tmp.tenmh,false,esc);
	if (esc){
		clearRect(x,y,62,20); gotoxy(0,0); return;
	}
	RemoveSpace(tmp.tenmh,true); ToUpper(tmp.tenmh);
	InputNumber(x+1+17,8+y+2,2*GetConsoleWidth()/3+24, GetConsoleHeight()-4,tmp.stclt,1,true,esc);
	if (esc){
		clearRect(x,y,62,20); gotoxy(0,0); return;
	}
	InputNumber(x+1+17,12+y+2,2*GetConsoleWidth()/3+24, GetConsoleHeight()-4,tmp.stcth,1,false,esc);
	if (esc){
		clearRect(x,y,62,20); gotoxy(0,0); return;
	}
	// ==================== Kiem Tra Xem struct vua` nhap. da~ co trong ds chua ==================== //
	Insert(root,mamh,tmp);
	length += 1;
	reload = true; // Dung de~ load lai ds show ra
	clearRect(x,y,62,20);
}

void MonHoc::Insert(NODEMH *&nmh,string MAMH_in, MONHOC mh){
	if (nmh == NULL){ // Insert First
		nmh = new NODEMH;
		nmh->MAMH = MAMH_in;
		nmh->mh = mh;
		nmh->left = NULL;
		nmh->right = NULL;
	}
	else{ // .c_str la` doi~ 1 string thanh` 1 const char *. Ap dung methods nay` de~ su dung strcmp()
		if (strcmp(MAMH_in.c_str(),nmh->MAMH.c_str()) < 0) Insert(nmh->left,MAMH_in,mh); // neu nho hon thi` qua trai
		else if (strcmp(MAMH_in.c_str(),nmh->MAMH.c_str()) > 0) Insert(nmh->right,MAMH_in,mh); // neu lon hon thi qua phai
	}
}

NODEMH *MonHoc::GetNodeBySearch(string mamh){
	NODEMH *tmp = root;
	while(tmp != NULL && strcmp(mamh.c_str(),tmp->MAMH.c_str()) != 0){ // neu da tim dc tuc là manh == MANH r` thì out loop
		if (strcmp(mamh.c_str(),tmp->MAMH.c_str()) < 0) tmp = tmp->left;
		else if (strcmp(mamh.c_str(),tmp->MAMH.c_str()) > 0) tmp = tmp->right;
	}
	return tmp; // Ko can return NULL vi` khi het vong lap ma` chua tim duoc tmp thi` tmp luc nay` da~ = NULL
}

bool MonHoc::CheckExist(string mamh){
	return (GetNodeBySearch(mamh) != NULL ? true:false);
}

void MonHoc::Find(string &t_mamh, bool findtodel, bool findtoedit, bool &reload){
	Cursor(true); NODEMH *tmp; // de~ lam` bien cuc. bo.
	string t = "Tim kiem theo MAMH: "; bool esc = false, found;
	int x = 11, y = 5+GetConsoleHeight()/2;
	clearRect(26+GetConsoleWidth()/2+t.size(),4,21,1); // clear dòng chu~ khi nhap. vào ma~ mon hoc.
	RemoveSpace(t_mamh,false);
	ToUpper(t_mamh);
//	drawRect(24+GetConsoleWidth()/2,7,45,19);
	tmp = GetNodeBySearch(t_mamh);
	if (tmp != NULL){
		found = true;
		int y = 8;
		clearRect(25+GetConsoleWidth()/2,y,43,18);
		drawText(38+GetConsoleWidth()/2,y+1,"KET QUA TIM KIEM",YELLOW);
		drawText(26+GetConsoleWidth()/2,y+4, "Ma mon hoc : ",WHITE);
		drawText(26+GetConsoleWidth()/2,y+7, "Ten mon hoc: ",WHITE);
		drawText(26+GetConsoleWidth()/2,y+10,"STCLT      : ",WHITE);
		drawText(26+GetConsoleWidth()/2,y+13,"STCTH      : ",WHITE);
		drawText(39+GetConsoleWidth()/2,y+4,tmp->MAMH,WHITE);
		drawText(39+GetConsoleWidth()/2,y+7,tmp->mh.tenmh,WHITE);
		drawNumber(39+GetConsoleWidth()/2,y+10,tmp->mh.stclt,WHITE);
		drawNumber(39+GetConsoleWidth()/2,y+13,tmp->mh.stcth,WHITE);
	}
	else{
		clearRect(25+GetConsoleWidth()/2,8,43,18);
		drawText(35+GetConsoleWidth()/2,15,"KHONG TIM THAY MON HOC",YELLOW); found = false;
	}
	if (findtodel && found){
		Message("Ban co chac chan khong [Y/N]",GREEN);
		if (Yes()){
			DeleteRightOrLeftNULL(root,t_mamh);
			clearRect(25+GetConsoleWidth()/2,8,42,17);
			reload = true;
		}
		clearMessage();
	}
	if (findtoedit && found){
		FrameInput(x,y);
		MONHOC n_mh = tmp->mh; // new mon hoc
		string n_mamh = t_mamh;// new mamh
		// Ghi ra thong tin cu~ cua~ mon hoc
		drawText(x+1+17,y+2,n_mamh,WHITE);
		drawText(x+1+17,4+y+2,n_mh.tenmh,WHITE);
		drawNumber(x+1+17,8+y+2,n_mh.stclt,WHITE);
		drawNumber(x+1+17,12+y+2,n_mh.stcth,WHITE);
		// Nhap thong tin moi cho mon hoc
		while(true){ // Kiem tra trùng
			InputString(x+1+17+n_mamh.size(),y+2,2*GetConsoleWidth()/3+24,GetConsoleHeight()-4,10,n_mamh,false,esc);
			if (esc){
				clearRect(x,y,62,20); gotoxy(0,0); return;
			}
			RemoveSpace(n_mamh,false); ToUpper(n_mamh);
			if (n_mamh != t_mamh && CheckExist(n_mamh)){ // vd: edit "KTS" neu nhu enter bo~ qua thì van~ nhan. "KTS"
				// neu nhu edit lai. mà trùng vs 1 trong mamh trong ds se~ báo loi~
				Message("MA MON HOC DA TON TAI. VUI LONG NHAP LAI",RED);
			}
			else{
				clearMessage(); break; 
			}
		}
		InputString(x+1+17+n_mh.tenmh.size(),4+y+2,2*GetConsoleWidth()/3+24,GetConsoleHeight()-4,40,n_mh.tenmh,false,esc);
		if (esc){
			clearRect(x,y,62,20); gotoxy(0,0); return;
		}
		RemoveSpace(n_mh.tenmh,true);
		InputNumber(x+1+17+ (n_mh.stclt == 0 ? 1:floor(log10(n_mh.stclt))+1),8+y+2,2*GetConsoleWidth()/3+24, GetConsoleHeight()-4,n_mh.stclt,1,true,esc);
		if (esc){
			clearRect(x,y,62,20); gotoxy(0,0); return;
		}
		InputNumber(x+1+17+ (n_mh.stcth == 0 ? 1:floor(log10(n_mh.stcth))+1),12+y+2,2*GetConsoleWidth()/3+24, GetConsoleHeight()-4,n_mh.stcth,1,false,esc);
		if (esc){
			clearRect(x,y,62,20); gotoxy(0,0); return;
		}
		// GIAI THICH CHO INPUT NUMBER O DAY
		// Neu nhu stclt hay stcth mà == 0 thì len = 1 cho nen x + 1 + 17 + 1, còn neu` ko thì ta phai~ tìm do. dài cua~ so
		// dó roi` + vào x + 1 + 17
//		gotoxy(0,50);
//		cout <<n_mamh<<"\t"<<n_mh.tenmh<<"\t"<<n_mh.stclt<<"\t"<<n_mh.stcth;
		// Edit Process Here
		Message("Ban co chac chan khong [Y/N]",GREEN);
		if (Yes()){
			EditSubject(t_mamh,n_mamh,n_mh);
			clearRect(25+GetConsoleWidth()/2,8,42,17); // Xoa bang~ thong tin cu~
			reload = true;
			t_mamh = n_mamh;
		}
		clearRect(x,y,62,20);
		clearMessage();
	}
}

void MonHoc::EditSubject(string old_mamh, string new_mamh, MONHOC new_mh){
	// Buoc 1: Xoa NODEMH cu~
	DeleteRightOrLeftNULL(root,old_mamh);
	// Buoc 2: Insert NODEMH moi
	Insert(root,new_mamh,new_mh);
}

void MonHoc::DeleteRightOrLeftNULL(NODEMH *&nmh, string mamh){
	if (nmh != NULL){
		if (strcmp(mamh.c_str(),nmh->MAMH.c_str()) < 0) DeleteRightOrLeftNULL(nmh->left,mamh);
		else if(strcmp(mamh.c_str(),nmh->MAMH.c_str()) > 0) DeleteRightOrLeftNULL(nmh->right,mamh);
		else { // truong hop == . Da tìm ra muc. tieu can` xóa
			NODEMH *tmp = nmh; // Dùng con tro tmp tro vào vi. trí o nho can` xóa
			if (tmp->left == NULL){ // Neu mà ben trái null thì lay node con ben phai~ gán vào muc. tieu
				nmh = tmp->right;
			}
			else if (tmp->right == NULL){
				nmh = tmp->left;
			}
			else { // TH 2 cai deu khong phai~ NULL. Tuc la ca~ node trai phai~ deu co 1 gia tri nhat dinh
				DeleteBothNotNULL(tmp->right,nmh); 
				// Duyet qua ben node phai~ va` de~ tim ra node co gia tri nho~ nhat ben do
				// Tính tu` node muc. tieu thì duyet qua ben phai~ tìm node có gtnn thì node có gtnn van~ lon hon node ben
				// trái cua muc tieu. roi` gán node muc tieu = node gtnn, xóa o nho cua node có gtnn di
			}
			free(tmp); // xóa cái node do, 
			length--; // giam~ length
		}
	}
}

void MonHoc::DeleteBothNotNULL(NODEMH *&min, NODEMH *rp){ // delete case 3 - rp = replace
	// Duyet qua toan` bo node ben trái de~ tim node co gia tri nho~ nhat, GTNN la` node co` ->left == NULL
	if (min->left != NULL) DeleteBothNotNULL(min->left,rp); // Neu co nhanh ben trai thi` node hien tai. ko phai NN
	else{
		rp->MAMH = min->MAMH;
		rp->mh = min->mh;
		rp = min;
		min = rp->right; // Hien. tai. left cua~ node nay` == NULL nen gan cho right
	}
}

void MonHoc::ShowSubjectList(int x, int y, int from, int to){
	int start_x = x, start_y = y;
	if (root != NULL){
		// DRAW TITLE FRAME
		drawRect(start_x,start_y,70,2);
		draw_high_line(start_x+11,start_y,2);
		drawText(start_x+4,start_y+1,"MAMH",WHITE);
		draw_high_line(start_x+54,start_y,2);
		drawText(start_x+28,start_y+1,"TEN MON HOC",WHITE);
		draw_high_line(start_x+62,start_y,2);
		drawText(start_x+56,start_y+1,"STCLT",WHITE);
		drawText(start_x+64,start_y+1,"STCTH",WHITE);
		for(int i=from;i<to;i++){
			// DRAW ELEMENT FRAME // PUT ALL THIS IN LOOP TO DRAW
			drawRect(start_x,start_y+(i+1-from)*2,70,2);
			draw_high_line(start_x+11,start_y+(i+1-from)*2,2);
			draw_high_line(start_x+54,start_y+(i+1-from)*2,2);
			draw_high_line(start_x+62,start_y+(i+1-from)*2,2);
			gotoxy(start_x,start_y+(i+1-from)*2);
			printf("%c",195);
			gotoxy(start_x+11,start_y+(i+1-from)*2);
			printf("%c",197);
			gotoxy(start_x+54,start_y+(i+1-from)*2);
			printf("%c",197);
			gotoxy(start_x+62,start_y+(i+1-from)*2);
			printf("%c",197);
			gotoxy(start_x+70,start_y+(i+1-from)*2);
			printf("%c",180);
			// DRAW ELEMENT DATA // PUT ALL THIS IN LOOP TO DRAW
			drawText(start_x+2,start_y+1+(i+1-from)*2,dsmhtt->getList_mamh()[i],WHITE);
			drawText(start_x+13,start_y+1+(i+1-from)*2,dsmhtt->getList_struct()[i].tenmh,WHITE);
			drawNumber(start_x+58,start_y+1+(i+1-from)*2,dsmhtt->getList_struct()[i].stclt,WHITE);
			drawNumber(start_x+66,start_y+1+(i+1-from)*2,dsmhtt->getList_struct()[i].stcth,WHITE);
		}
	}
}

void MonHoc::Sort(){
//	listmamh.clear(); // 2 dong` clear nay` dung` de` xoa het ptu~ trong ds tam. thoi` de~ khi thoat 
//	listmh.clear();   // ham` se~ reload sort LNR lai.
	dsmhtt->ResetList();
	LNR(root);
}

void MonHoc::LNR(NODEMH *nmh){
	if (nmh != NULL){
		LNR(nmh->left);
//		listmamh.push_back(nmh->MAMH);
//		listmh.push_back(nmh->mh);
		dsmhtt->Insert(nmh->MAMH,nmh->mh);
		LNR(nmh->right);
	}
}

void MonHoc::FreeThisTree(){
	LRN(root);
	root = NULL;
	dsmhtt->FreeList();
	free(dsmhtt);
}

void MonHoc::LRN(NODEMH *nmh){ // Duyet LRN de~ xoa toan bo cay
	if (nmh != NULL){
		LRN(nmh->left);
		LRN(nmh->right);
		free(nmh);
	}
}
#endif

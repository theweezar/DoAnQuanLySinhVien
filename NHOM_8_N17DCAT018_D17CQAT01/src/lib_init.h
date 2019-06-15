using namespace std;
#define _WIN32_WINNT 0x0500 // Dùng cho win 32 bit
#include<iostream>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string>
#include<string.h>
#include<math.h>
#include<fstream>
#include<ctime>
#include<windows.h>
#include<vector>
#include"graphs.h" // Graphics
// Making menu
//: cap nhat ds mon hoc, cap nhat ds lop tin chi, cap nhat ds sinh vien, cap nhat ds diem
//: in ds mon hoc, in ds lop tin chi, in ds sinh vien, in ds diem
//: them mon hoc, chinh sua mon hoc, xoa mon hoc
//: them ltc, chinh sua ltc, xoa ltc
//: them sinh vien, chinh sua sinh vien, xoa sinh vien
//: chinh sua diem
//const string mh_item[4] = {"IN DS MON HOC","THEM MON HOC","CHINH SUA MON HOC","XOA MON HOC"};
//const string ltc_item[4] = {"IN DS LOP TIN CHI","THEM LOP TIN CHI","CHINH SUA LOP TIN CHI","XOA LOP TIN CHI"};
//const string sv_item[4] = {"IN DS SINH VIEN","THEM SINH VIEN","CHINH SUA SINH VIEN","XOA SINH VIEN"};
//const string diem_item[2] = {"IN DS DIEM","CHINH SUA DIEM"};
//const int menu_x = 2, menu_y = 1, menu_height = 15;
//cout << 1900+tg->tm_year;
#include"Input.h"  // Check Input_string_number_file
#include"MonHoc.h" // ds cay nhi phan
#include"SinhVien.h" // ds lien ket don
#include"SvDangKy.h" // ds lien ket don
#include"LopTinChi.h" // ds tuyen tinh
#include"QLSV.h" // Main app
		





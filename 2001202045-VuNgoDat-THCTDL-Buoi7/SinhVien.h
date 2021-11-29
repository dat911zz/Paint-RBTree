#ifndef _MY_SINH_VIEN_H_
#define _MY_SINH_VIEN_H_
#include<iostream>
using namespace std;
//Struct
struct SinhVien
{
	char mssv[11];
	char hoTen[11];
	int namSinh;
	float diemTB;
};

//Prototype
void nhapSinhVien(SinhVien& x);
void xuatSinhVien(SinhVien x);
bool operator > (SinhVien a, SinhVien b);
bool operator < (SinhVien a, SinhVien b);
bool operator == (SinhVien a, SinhVien b);
bool operator != (SinhVien a, SinhVien b);

//Function
void nhapSinhVien(SinhVien& x)
{
	cout << "Nhxp MSSV: ";
	cin >> x.mssv;
	cout << "Nhap Ho ten: ";
	gets_s(x.hoTen);
	cout << "Nhap nam sinh: ";
	cin >> x.namSinh;
	cout << "Nhap diem trung binh: ";
	cin >> x.diemTB;
}
void xuatSinhVien(SinhVien x)
{
	printf("%-12s%-20s%5d%5.2f\n", x.mssv, x.hoTen, x.namSinh, x.diemTB);
}
bool operator > (SinhVien a, SinhVien b)
{
	return strcmp(a.mssv, b.mssv) == 1;
}
bool operator < (SinhVien a, SinhVien b)
{
	return strcmp(a.mssv, b.mssv) == -1;
}
bool operator == (SinhVien a, SinhVien b)
{
	return strcmp(a.mssv, b.mssv) == 0;
}
bool operator != (SinhVien a, SinhVien b)
{
	return strcmp(a.mssv, b.mssv) != 0;
}


#endif // !_MY_SINH_VIEN
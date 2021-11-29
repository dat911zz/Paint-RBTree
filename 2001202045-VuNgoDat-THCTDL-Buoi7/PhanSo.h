#ifndef _MY_PHAN_SO_H_
#define _MY_PHAN_SO_H_
#include<iostream>
using namespace std;
//Struct
struct PhanSo
{
	int tu, mau;
};

//Prototype
void nhapPhanSo(PhanSo& x);
void xuatPhanSo(PhanSo x);
void toiGianPS(PhanSo& x);
bool operator > (PhanSo a, PhanSo b);
bool operator < (PhanSo a, PhanSo b);
bool operator == (PhanSo a, PhanSo b);
bool operator != (PhanSo a, PhanSo b);

//Function
void nhapPhanSo(PhanSo& x)
{
	cout << "\nNhap tu so:";
	cin >> x.tu;
	cout << "\nNhap mau so:";
	cin >> x.mau;
}
void xuatPhanSo(PhanSo x)
{
	printf("%-4d%-4s\t", x.tu,x.mau);
}
int GCD(int a, int b)
{
	while (a != b)
	{
		a > b ? a -= b : b -= a;
	}
	return a;
}
void toiGianPS(PhanSo& x)
{
	int gcd = GCD(x.tu, x.mau);
	if (x.mau != 0)
	{
		x.tu /= gcd;
		x.mau /= gcd;
	}
}
bool operator > (PhanSo a, PhanSo b)
{
	return (1.0 * a.tu / a.mau) > (1.0 * b.tu / b.mau);
}
bool operator < (PhanSo a, PhanSo b)
{
	return (1.0 * a.tu / a.mau) < (1.0 * b.tu / b.mau);
}
bool operator == (PhanSo a, PhanSo b)
{
<<<<<<< HEAD
	return a.tu == b.tu && a.mau == b.mau;
=======
	return (1.0 * a.tu / a.mau) == (1.0 * b.tu / b.mau);
>>>>>>> 32abf2bdaba626d0b904490dc4ee5e86d9e81c90
}
bool operator != (PhanSo a, PhanSo b)
{
	return (1.0 * a.tu / a.mau) != (1.0 * b.tu / b.mau);
}


#endif // !_MY_PHAN_SO_H_
//#include<iostream>
//using namespace std;
//void main()
//{
//	char str[100];
//	bool check = true;
//	cout << "Nhap :";
//	cin >> str;
//
//	//1234 -> SO NGUYEN
//	//0123 -> K PHAI LA SO NGUYEN
//	//9ADF -> K PHAI LA SO NGUYEN
//
//	//Kiem tra phan tu dau tien co phai la so 1->9 hay khong
//	//if (str[0] >= '1' && str[0] <= '9')
//	//{
//	//	for (int i = 1; i < strlen(str); i++)//Duyet tu dau den cuoi mang
//	//	{
//	//		if (str[i] >= '0' && str[i] <= '9')//1a3a4
//	//		{
//	//			check = true;
//	//		}
//	//		else
//	//		{
//	//			check = false;
//	//			break;//thoat vong lap
//	//		}
//	//	}
//	//}
//
//	//Kiem tra phan tu dau tien co phai la so 1->9 hay khong
//	if (str[0] <= '1' || str[0] >= '9')
//	{
//		check = false;
//	}
//	else
//	{
//		for (int i = 1; i < strlen(str); i++)//Duyet tu dau den cuoi mang
//		{
//			if (str[i] <= '0' || str[i] >= '9')//1a3a4
//			{
//				check = false;
//				break;
//			}
//		}
//	}
//	printf("KQ: %s", check == true ? "So nguyen" : "Khong la so nguyen");
//}
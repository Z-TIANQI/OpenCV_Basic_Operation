#include<iostream>
#include<string>
using namespace std;

const int n = 2;

struct ProductsInfo
{
	char Num[10], Name[10];
	double Price, Income;
	int Volume;
};

void Sort_Income(ProductsInfo p[]);
void Sort_Name(ProductsInfo p[]);
void Seek_Num(ProductsInfo p[]);
void Seek_Name(ProductsInfo p[]); 
void Show(ProductsInfo p[]);

void main()
{
	ProductsInfo p[n];
	cout << "\n���Դ����� " << n << " ����Ʒ�Ĵ��롢���ơ����ۡ����۶\n";//��һ��������ʾ�������н���������
	for (int i = 0; i < n; i++)
	{
		cin >> p[i].Num >> p[i].Name >> p[i].Price >> p[i].Volume;
		p[i].Income = p[i].Price*p[i].Volume;
	}

	Sort_Income(p);
	Sort_Name(p);
	cout << "��������Ʒ����";
	Seek_Num(p);
	cout << "��������Ʒ����";
	Seek_Name(p);

	system("pause");
}

void Sort_Income(ProductsInfo p[])
{
	ProductsInfo t;
	for (int i = 0; i < n - 1; i++)
		for (int j = 0; j < n - i - 1; j++)
			if (p[j].Income > p[j + 1].Income)
			{
				t = p[j];
				p[j] = p[j + 1];
				p[j + 1] = t;
			}
	cout << "\n\n�����ǰ������۶�����\n\n";
	Show(p);
}

void Sort_Name(ProductsInfo p[])
{
	ProductsInfo t;
	for (int i = 0; i < n - 1; i++)
		for (int j = 0; j < n - i - 1; j++)
			if (strcmp(p[j].Name, p[j + 1].Name)>0)
			{
				t = p[j];
				p[j] = p[j + 1];
				p[j + 1] = t;
			}
	cout << "\n\n�����ǰ�����Ʒ��������\n\n";
	Show(p);
}

void Seek_Num(ProductsInfo p[])
{
	char a[10];
	cin>>a;
	for (int i = 0; i < n; i++)
	{
		if (strcmp(a,p[i].Num)==0)
			cout << "��Ʒ���룺" << p[i].Num << "\n(target)��Ʒ���ƣ�" << p[i].Name
			<< "\n\t��Ʒ���ۣ�" << p[i].Price << "\n\t������  ��" << p[i].Volume
			<< "\n\t���۶�  ��" << p[i].Income << endl;
	}
}

void Seek_Name(ProductsInfo p[])
{
	char a[10];
	cin>>a;
	for (int i = 0; i < n; i++)
	{
		if (strcmp(p[i].Name,a) == 0)
			cout << "��Ʒ���룺" << p[i].Num << "\n(target)��Ʒ���ƣ�" << p[i].Name
			<< "\n\t��Ʒ���ۣ�" << p[i].Price << "\n\t������  ��" << p[i].Volume
			<< "\n\t���۶�  ��" << p[i].Income << endl;
	}
}

void Show(ProductsInfo p[])
{
	for (int i = 0; i < n; i++)
		cout << "��Ʒ���룺" << p[i].Num << "\n(target)��Ʒ���ƣ�" << p[i].Name
		<< "\n\t��Ʒ���ۣ�" << p[i].Price << "\n\t������  ��" << p[i].Volume
		<< "\n\t���۶�  ��" << p[i].Income << endl;
}

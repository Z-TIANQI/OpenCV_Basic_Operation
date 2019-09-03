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
	cout << "\n请以次输入 " << n << " 个商品的代码、名称、单价、销售额：\n";//做一个输入提示，在运行界面更好理解
	for (int i = 0; i < n; i++)
	{
		cin >> p[i].Num >> p[i].Name >> p[i].Price >> p[i].Volume;
		p[i].Income = p[i].Price*p[i].Volume;
	}

	Sort_Income(p);
	Sort_Name(p);
	cout << "请输入商品代码";
	Seek_Num(p);
	cout << "请输入商品名称";
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
	cout << "\n\n下面是按照销售额排序\n\n";
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
	cout << "\n\n下面是按照商品名称排序\n\n";
	Show(p);
}

void Seek_Num(ProductsInfo p[])
{
	char a[10];
	cin>>a;
	for (int i = 0; i < n; i++)
	{
		if (strcmp(a,p[i].Num)==0)
			cout << "商品代码：" << p[i].Num << "\n(target)商品名称：" << p[i].Name
			<< "\n\t商品单价：" << p[i].Price << "\n\t销售量  ：" << p[i].Volume
			<< "\n\t销售额  ：" << p[i].Income << endl;
	}
}

void Seek_Name(ProductsInfo p[])
{
	char a[10];
	cin>>a;
	for (int i = 0; i < n; i++)
	{
		if (strcmp(p[i].Name,a) == 0)
			cout << "商品代码：" << p[i].Num << "\n(target)商品名称：" << p[i].Name
			<< "\n\t商品单价：" << p[i].Price << "\n\t销售量  ：" << p[i].Volume
			<< "\n\t销售额  ：" << p[i].Income << endl;
	}
}

void Show(ProductsInfo p[])
{
	for (int i = 0; i < n; i++)
		cout << "商品代码：" << p[i].Num << "\n(target)商品名称：" << p[i].Name
		<< "\n\t商品单价：" << p[i].Price << "\n\t销售量  ：" << p[i].Volume
		<< "\n\t销售额  ：" << p[i].Income << endl;
}

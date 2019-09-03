#include<iostream>
using namespace std;
void main()
{
	int a[]= { 1,2,3,4,5 };
	int *p = a;
	*(p + 3) *= 3;
	cout << *p << endl << p[3] << endl;
	system("pause");
}
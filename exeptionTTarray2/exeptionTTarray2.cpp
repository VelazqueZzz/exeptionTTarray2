#include <iostream>
#include <fstream>
using namespace std;


class TTest
{
public:
	TTest(char*);
	int Sum(void);
	~TTest() { if (is_init) delete[]m; }
private:
	int* m;
	int n;
	bool is_init, is_empty;
};

TTest::TTest(char *fname) : is_init(true), is_empty(false)
{
	ifstream f(fname);
	if (!f)
	{
		is_init = false;
		throw 104;
	}
	f >> n;
	if (n < 1)
	{
		is_init = false;
		f.close();
		throw 109;
	}
	m = new int[n];
	if (!m)
	{
		is_init = false;
		f.close();
		throw 114;
	}
	for (int i = 0; i < n; i++)
	{
		if (f.eof())
		{
			is_empty = true;
			f.close();
			throw 119;

		}
		f >> m[i];
	}
	f.close();
}
int TTest::Sum(void)
{
	if (!is_init || is_empty) throw 201;
	int s = 0;
	for (int i = 0; i < n; i++) s += m[i];
	return s;
}
int main(int argc, char** argv)
{
	TTest *test = NULL;
	try
	{
		test = new TTest("data.txt");
		cout << "Summa = " << test->Sum() << endl;
	}
	catch (int &ex)
	{
		switch (ex)
		{
		case 104: cout << "exeption#" << ex << ".cannot open file!" << endl;
			break;
		case 109: cout << "exeption#" << ex << ".wrong array size" << endl;
			break;
		case 114: cout << "exeption#" << ex << ".memory failure" << endl;
			break;
		case 119: cout << "exeption#" << ex << ".not enought data in file!" << endl;
			break;
		case 201: cout << "exeption#" << ex << ".cannotcount sum data!" << endl;
			break;
		default: cout << "exeption#" << ex << ".unknow exeption" << endl;

		}
	}
	if (test) delete test;
	cout << "end of main" << endl;
	return 0;
}
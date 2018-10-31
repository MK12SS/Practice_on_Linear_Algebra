#include"Matrix.h"

using namespace std;

int main()
{
	int n, m;
	cin >> n >> m;
	Matrix test(n, m);
	cin >> test;
	cout << test.diagonalize() << endl;
	cout << test;
}
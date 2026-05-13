#include<iostream>
using namespace std;
int main() {
	int status;
	cin >> status;
	for (int j = status;j > 0;j = (j - 1) & status) {
		cout << j<<endl;
	}
}
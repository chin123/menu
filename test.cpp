#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace std;

class a {
public:
	void ex(int a, int x, char b) { // 1. Print Something
		cout << "Hello" << a << endl;
	};
	void bye(int x) { // 2. Print Goodbye
		cout << "Goodbye" << x << endl;
	};
};

int main() {
	int op;
	do {
		system("clear");
		cout << "Menu\n";
		cout << "1. Print Something\n";
		cout << "2. Print Goodbye\n";
		cout << "3. Exit\n";
		cout << "Choose an option: ";
		cin >> op;
		a obj;
		int a,x;
		char b;
		switch (op) {
			case 1:
				cout << "Enter the value of a: ";
				cin >> a;
				cout << "Enter the value of x: ";
				cin >> x;
				cout << "Enter the value of b: ";
				cin >> b;
				obj.ex(a, x, b);
				break;
			case 2:
				cout << "Enter the value of x: ";
				cin >> x;
				obj.bye(x);
				break;
			case 3:
				cout << "Goodbye.\n";
				break;
			default:
				cout << "Invalid option.\n";
				break;
		}
		getchar();
		getchar();
	} while (op != 3);
	return 0;
}

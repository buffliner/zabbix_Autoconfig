#include <iostream>
#include <string>

using namespace std;

int version;
string answer;

int main () {
	cout << "Select OS: \n1.Debian 2.Ubuntu 3.Windows" << endl;
	cin >> version;
	switch (version) {
		case 1:
			system("sudo apt update");
			break;
		case 2:
			system("sudo apt update");
			break;
		case 3:
			system("sudo apt update");
		default:
			cout << "Exit code 1: OS is not selected" << endl;
			break;
	}
	return 0;
}

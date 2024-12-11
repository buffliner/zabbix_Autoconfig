#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "utils.h"

using namespace std;

string agreement;

int main() {
	map<string, string> osPackages = {
		{"Ubuntu", "https://www.zabbix.com/download?os=ubuntu"},
		{"CentOS", "https://www.zabbix.com/download?os=centos"},
		{"Debian", "https://www.zabbix.com/download?os=debian"},
		{"Windows", "https://www.zabbix.com/download?os=windows"},
		{"Red Hat", "https://www.zabbix.com/download?os=rhel"}
	};

	map<string, string> arches= {
		{"x86_64", "64-bit"},
		{"i386", "32-bit"},
		{"arm", "ARM"}
	};

	string detectedOS = detectOS();
	string detectedArch = detectArch();

	if (osPackages.find(detectedOS) == osPackages.end() || arches.find(detectedArch) == arches.end()) {
		cerr << "Ошибка код 1. ОС или архитектура не поддерживаются." << endl;
		return 1;
	}

	string downloadURL = osPackages[detectedOS] + "&arch=" + detectedArch;

	cout << "Ваша ОС - " << detectedOS << endl;
	cout << "Ваша архитектура - " << detectedArch << endl;
	cout << "Для вашей ОС есть версия Zabbix. Начать установку? (y/n)";
	cin >> agreement;
}

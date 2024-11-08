#include "utils.h"
#include <iostream>
#include <iomanip>   // Для setw

using namespace std;

passwdData getUserData() {
    passwdData userData;

    // Получаем UID текущего пользователя
    uid_t uid = getuid();

    // Получаем информацию о пользователе
    struct passwd *pw = getpwuid(uid);
    if (pw) {
        // Заполняем структуру passwdData
        userData.pw_name = pw->pw_name;
        userData.pw_passwd = pw->pw_passwd;
        userData.pw_uid = pw->pw_uid;
        userData.pw_gid = pw->pw_gid;
        userData.pw_dir = pw->pw_dir;
    } else {
        cerr << "Error: Could not retrieve user data." << endl;
    }

    return userData;
}

void writeLog(ofstream &logFile, const string &message) {
    logFile << message << endl;
}

void printOSTable() {
    cout << "+-----------------------+" << endl;
    cout << "|       Select OS:      |" << endl;
    cout << "+-----------------------+" << endl;
    cout << "| 1 | Debian            |" << endl;
    cout << "+-----------------------+" << endl;
    cout << "| 2 | Ubuntu            |" << endl;
    cout << "+-----------------------+" << endl;
    cout << "| 3 | Windows           |" << endl;
    cout << "+-----------------------+" << endl;
}

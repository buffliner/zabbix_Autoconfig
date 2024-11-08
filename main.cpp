#include <iostream>
#include <cstring>  // Для strcpy
#include <string>

using namespace std;

int version;
string answer;

struct passwd {
    char *pw_name;      // Username
    char *pw_passwd;    // Password
    uid_t pw_uid;       // User ID
    gid_t pw_gid;       // Group ID
    char *pw_dir;       // Home directory
};

int main() {
    // Создаем указатель на структуру passwd и выделяем для нее память
    passwd *ptr = new passwd;
    
    // Инициализируем поля структуры
    ptr->pw_name = new char[50];
    ptr->pw_passwd = new char[50];
    ptr->pw_dir = new char[100];
    
    // Заполняем значения полей
    strcpy(ptr->pw_name, "username");
    strcpy(ptr->pw_passwd, "password");
    ptr->pw_uid = 1000;
    ptr->pw_gid = 1000;
    strcpy(ptr->pw_dir, "/home/username");

    // Выводим информацию о пользователе
    cout << "User Information:" << endl;
    cout << "Username: " << ptr->pw_name << endl;
    cout << "Password: " << ptr->pw_passwd << endl;
    cout << "UID: " << ptr->pw_uid << endl;
    cout << "GID: " << ptr->pw_gid << endl;
    cout << "Home Directory: " << ptr->pw_dir << endl;

    // Выбор ОС и выполнение команды
    cout << "\nSelect OS: \n1. Debian\n2. Ubuntu\n3. Windows" << endl;
    cin >> version;
    switch (version) {
        case 1:
            cout << "Updating Debian packages..." << endl;
            system("sudo apt update");
            break;
        case 2:
            cout << "Updating Ubuntu packages..." << endl;
            system("sudo apt update");
            break;
        case 3:
            cout << "Windows does not support 'apt update' command." << endl;
            break;
        default:
            cout << "Exit code 1: OS is not selected" << endl;
            break;
    }
    
    // Освобождаем выделенную память
    delete[] ptr->pw_name;
    delete[] ptr->pw_passwd;
    delete[] ptr->pw_dir;
    delete ptr;

    return 0;
}

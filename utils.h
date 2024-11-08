#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <fstream>
#include <pwd.h>
#include <unistd.h>

using namespace std;

struct passwdData {
    string pw_name;     // Username
    string pw_passwd;   // Password (может быть пустым или зашифрованным в зависимости от системы)
    uid_t pw_uid;            // User ID
    gid_t pw_gid;            // Group ID
    string pw_dir;      // Home directory
};

// Функция для получения информации о текущем пользователе
passwdData getUserData();

// Функция для записи лога
void writeLog(std::ofstream &logFile, const std::string &message);

// Функция для красивого вывода таблицы выбора ОС
void printOSTable();

#endif // UTILS_H

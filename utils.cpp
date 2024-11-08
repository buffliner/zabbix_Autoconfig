#include "utils.h"
#include <iostream>
#include <iomanip>   // Для setw
#include <cstdlib>

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

void install_and_configure_agent_debian() {
    // Загрузка пакета zabbix-release
    if (system("wget https://repo.zabbix.com/zabbix/7.0/debian/pool/main/z/zabbix-release/zabbix-release_latest+debian12_all.deb") != 0) {
        cerr << "Ошибка при загрузке пакета Zabbix" << endl;
        exit(1);
    }

    // Установка загруженного пакета
    if (system("sudo dpkg -i zabbix-release_latest+debian12_all.deb") != 0) {
        cerr << "Ошибка при установке пакета zabbix-release" << endl;
        exit(1);
    }

    // Обновление списка пакетов
    if (system("sudo apt update") != 0) {
        cerr << "Ошибка при обновлении списка пакетов" << endl;
        exit(1);
    }

    // Установка Zabbix Agent
    if (system("sudo apt install -y zabbix-agent") != 0) {
        cerr << "Ошибка при установке Zabbix Agent" << endl;
        exit(1);
    }

    // Перезапуск службы Zabbix Agent
    if (system("sudo systemctl restart zabbix-agent") != 0) {
        cerr << "Ошибка при перезапуске службы Zabbix Agent" << endl;
        exit(1);
    }

    // Включение автозапуска Zabbix Agent при старте системы
    if (system("sudo systemctl enable zabbix-agent") != 0) {
        cerr << "Ошибка при включении автозапуска Zabbix Agent" << endl;
        exit(1);
    }

    cout << "Zabbix Agent успешно установлен и настроен." << endl;
}

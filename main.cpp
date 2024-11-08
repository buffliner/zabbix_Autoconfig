#include <iostream>
#include <fstream>
#include <limits>
#include "utils.h"

using namespace std;

int main() {
    // Открываем файл для записи логов
    ofstream logFile("logs.txt");
    if (!logFile.is_open()) {
        cerr << "Error: Could not open log file." << endl;
        return 1;
    }

    // Получаем данные пользователя из системы
    passwdData user = getUserData();

    // Выводим и записываем информацию о пользователе в лог
    cout << "User Information:" << endl;
    cout << "Username: " << user.pw_name << endl;
    cout << "Password: " << user.pw_passwd << endl;
    cout << "UID: " << user.pw_uid << endl;
    cout << "GID: " << user.pw_gid << endl;
    cout << "Home Directory: " << user.pw_dir << endl;

    writeLog(logFile, "User Information:");
    writeLog(logFile, "Username: " + user.pw_name);
    writeLog(logFile, "Password: " + user.pw_passwd);
    writeLog(logFile, "UID: " + to_string(user.pw_uid));
    writeLog(logFile, "GID: " + to_string(user.pw_gid));
    writeLog(logFile, "Home Directory: " + user.pw_dir);

    // Выбор ОС и выполнение команды
    int version;
    bool validInput = false;

    while (!validInput) {
        // Выводим таблицу для выбора ОС
        printOSTable();

        // Получение ввода от пользователя
        cout << "Enter your choice: ";
        cin >> version;

        // Проверка на успешность ввода
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number (1-3)." << endl;
            continue;
        }

        switch (version) {
            case 1: {
                string debianVersion;
                cout << "Select Debian version (stable, testing, unstable): ";
                cin >> debianVersion;
                cout << "Updating Debian " << debianVersion << " packages..." << endl;
                writeLog(logFile, "OS selected: Debian " + debianVersion);
                system("sudo apt update");
                validInput = true;
		install_and_configure_agent_debian();
                break;
            }
            case 2: {
                string ubuntuVersion;
                cout << "Enter Ubuntu version (e.g., 20.04, 22.04): ";
                cin >> ubuntuVersion;
                cout << "Updating Ubuntu " << ubuntuVersion << " packages..." << endl;
                writeLog(logFile, "OS selected: Ubuntu " + ubuntuVersion);
                system("sudo apt update");
                validInput = true;
                break;
            }
            case 3:
                cout << "Windows does not support 'apt update' command." << endl;
                writeLog(logFile, "OS selected: Windows (no update command)");
                validInput = true;
                break;
            default:
                cout << "Invalid choice. Please select a valid OS option (1-3)." << endl;
                writeLog(logFile, "Invalid OS selection");
                break;
        }
    }

    // Закрываем файл логов после записи
    logFile.close();

    // Спрашиваем у пользователя, хочет ли он просмотреть и сохранить логи
    char choice;
    cout << "\nWould you like to view the logs? (y/n): ";
    cin >> choice;

    if (choice == 'y' || choice == 'Y') {
        ifstream logFileRead("logs.txt");
        if (logFileRead.is_open()) {
            cout << "\nLogs:\n";
            string line;
            while (getline(logFileRead, line)) {
                cout << line << endl;
            }
            logFileRead.close();
        } else {
            cerr << "Error: Could not open log file for reading." << endl;
        }
    }

    cout << "\nWould you like to save the logs permanently? (y/n): ";
    cin >> choice;

    if (choice == 'n' || choice == 'N') {
        if (remove("logs.txt") == 0) {
            cout << "Log file deleted successfully." << endl;
        } else {
            cerr << "Error: Could not delete log file." << endl;
        }
    } else {
        cout << "Logs saved in 'logs.txt'." << endl;
    }

    return 0;
}

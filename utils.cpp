#include "utils.h"
#include <cstdlib>
#include <string>
#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

string detectOS() {
#ifdef _WIN32
	return "Windows";
#elif __linux__
	if (system("grep -q 'Ubuntu' /etc/os-release > /dev/null 2>&1") == 0) {
		return "Ubuntu";
	} else if (system("grep -q 'CentOS' /etc/os-elease > /dev/null 2>&1") == 0) {
		return "CentOS";
	} else if (system("grep -q 'Debian' /etc/os-release > /dev/null 2>&1") == 0) {
		return "Debian";
	} else if (system("grep -q 'Red Hat' /etc/os-release > /dev/null 2>&1") == 0) {
		return "Red Hat";
	} else {
		return "Unknown linux";
	}

#elif __APPLE__
	return "MacOS";
#else
	return "Unknown";
#endif
}

string detectArch() {
#ifdef _WIN32
	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);
	if (sysInfo.wProcessorArchitecture ==  PROCESSOR_ARCHITECTURE_AMD64) {
		return "x86_64";
	} else if (sysInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_INTEL) {
		return "i386";
	} else {
		return "Unknown";
	}

#elif __linux__ || __APPLE__
	if (system("uname -m | grep -q 'x86_64' > /dev/null 2>&1") == 0) {
		return "x86_64";
	} else if (system("uname -m | grep -q 'i386' > /dev/null 2>&1") == 0) {
		return "i386";
	} else if (system("uname -m | grep -q 'arm' > /dev/null 2>&1") == 0) {
		return "arm";
	} else {
		return "Unknown";
	}
#else
	return "Unknown";
#endif
}

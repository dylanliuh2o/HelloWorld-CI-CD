#include <iostream>
#include <string>
#include <ctime>
#include <vector>

#if defined(_WIN32)
    #include <windows.h>
    #include <sysinfoapi.h>
#else
    #include <sys/utsname.h>
    #include <fstream>
#endif

void print_banner() {
    std::cout << "========================================" << std::endl;
    std::cout << "   CI/CD CROSS-PLATFORM SYSTEM INFO     " << std::endl;
    std::cout << "========================================" << std::endl;
}

std::string get_os_name() {
#if defined(_WIN32)
    return "Windows";
#elif defined(__apple__) || defined(__MACH__)
    return "macOS";
#elif defined(__linux__)
    // 尝试读取发行版信息
    std::ifstream file("/etc/os-release");
    std::string line;
    while (std::getline(file, line)) {
        if (line.find("PRETTY_NAME=") == 0) {
            return line.substr(13, line.length() - 14);
        }
    }
    return "Linux";
#else
    return "Unknown OS";
#endif
}

void print_system_specs() {
    time_t now = time(0);
    std::cout << "Current Time: " << ctime(&now);
    std::cout << "OS Name:      " << get_os_name() << std::endl;

#if defined(_WIN32)
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    std::cout << "Architecture: ";
    if (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64) std::cout << "x64";
    else if (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_ARM64) std::cout << "ARM64";
    else std::cout << "x86";
    std::cout << "\nProcessor Count: " << si.dwNumberOfProcessors << std::endl;
#else
    struct utsname buffer;
    if (uname(&buffer) == 0) {
        std::cout << "Kernel:       " << buffer.release << std::endl;
        std::cout << "Architecture: " << buffer.machine << std::endl;
    }
#endif
}

int main() {
    print_banner();
    print_system_specs();
    std::cout << "========================================" << std::endl;
    return 0;
}
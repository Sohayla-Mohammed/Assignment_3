// File: A3_SheetPb05_20220225.cpp
// Author: Omar Saeed Othman
// Section: S(1)
// ID: 20220225

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <windows.h>
#include <psapi.h>
#include <tlhelp32.h>
#include <iomanip>
using namespace std;
class Process {
private:
    string name;
    DWORD pid;
    int memoryUsage;
public:
    Process(const string& name, DWORD pid, int memoryUsage): name(name), pid(pid), memoryUsage(memoryUsage) {}


    string getName() const {
        return name;
    }

    DWORD getPID() const {
        return pid;
    }

    int getMemoryUsage() const {
        return memoryUsage;
    }


};

class ProcessList {
private:
    vector<Process> processes;
public:
    void fill() {
        HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if (hProcessSnap == INVALID_HANDLE_VALUE) {
            cerr << "Failed to create process snapshot." << endl;
            return;
        }

        PROCESSENTRY32 pe32;
        pe32.dwSize = sizeof(PROCESSENTRY32);

        if (!Process32First(hProcessSnap, &pe32)) {
            cerr << "Failed to get the first process." << endl;
            CloseHandle(hProcessSnap);
            return;
        }

        processes.clear();

        do {
            int memoryUsage = 0;
            HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pe32.th32ProcessID);
            if (hProcess != NULL) {

                PROCESS_MEMORY_COUNTERS pmc;
                if (GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc))) {
                    memoryUsage = pmc.WorkingSetSize;
                }
                CloseHandle(hProcess);
            }

            Process newProcess(pe32.szExeFile, pe32.th32ProcessID, memoryUsage);
            processes.push_back(newProcess);
        } while (Process32Next(hProcessSnap, &pe32));

        CloseHandle(hProcessSnap);
    }

    void sortBy(int sortBy) {
        if (sortBy == 1) {
            sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
                return a.getName() < b.getName();
            });
        }
        else if (sortBy == 2) {
            sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
                return a.getPID() < b.getPID();
            });
        }
        else if (sortBy == 3) {
            sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
                return a.getMemoryUsage() > b.getMemoryUsage();
            });
        }
    }

    void display() const {
        cout << "--------------------------------------------------------------------" << endl;
        cout << "| Process Name                | PID      | Memory Usage (KB)    |" << endl;
        cout << "--------------------------------------------------------------------" << endl;

        for (const auto& process : processes) {
            cout << "| " << left << std::setw(28) << process.getName() << " | "
                      << setw(8) << process.getPID() << " | "
                      << setw(20) << process.getMemoryUsage()/1024<<" KB" << " |" << endl;
        }

        cout << "--------------------------------------------------------------------" <<endl;
    }


};

int main() {
    ProcessList processList;
    processList.fill();

    int sortBy;
    while (true) {
        cout<<"Menu :\n";
        cout<<"Welcome To Task Manger Please Enter :\n";
        cout<<"1.Sort By Name\n";
        cout<<"2.Sort By PID\n";
        cout<<"3.Sort By Memory Usage \n";
        cout<<"0.EXIT\n";

        cin >> sortBy;

        if (sortBy == 0) {
            return 0;
        }

        processList.sortBy(sortBy);
        processList.display();
    }

    return 0;
}

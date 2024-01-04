#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <windows.h>
#include <psapi.h>
#include <tlhelp32.h>
#include <iomanip>
#include <fstream>

using namespace std;

class Process {
private:
    string name;
    string session_name;
    int pid;
    int session_num;
    int memoryUsage;

public:
    Process(const string& name, string session_name, int pid, int memoryUsage, int session_num) :
            name(name), session_name(session_name), session_num(session_num), pid(pid), memoryUsage(memoryUsage) {}

    string getName() const {
        return name;
    }

    string getSessionName() const {
        return session_name;
    }

    int getSessionNum() const {
        return session_num;
    }

    int getPID() const {
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
        system("tasklist>input.txt");

        ifstream inputFile("input.txt");
        string line;

        // Skip the first two lines as they contain headers
        getline(inputFile, line);
        getline(inputFile, line);
        getline(inputFile, line);

        string word = "";
        int flag = 0;
        string name1;
        string s_name;
        int pid1;
        int s_num;
        int mem;

        while (getline(inputFile, line)) {
            name1.clear(); // Clear the name1 variable

            int flag;
            for (int i = 0; i < line.size(); ++i) {
                if (line[i] == ' ' && line[i + 1] == ' ') {
                    flag = i;
                    break;
                } else {
                    word += line[i];
                }
            }

            name1 = word;
            word.clear();

            for (int i = flag; i < line.size(); ++i) {
                if (line[i] >= 'a' && line[i] <= 'z' || line[i] >= 'A' && line[i] <= 'Z') {
                    flag = i;
                    break;
                } else if (line[i] >= '0' && line[i] <= '9') {
                    word += line[i];
                }
            }
            pid1 = stoi(word);
            word.clear();

            for (int i = flag; i < line.size(); ++i) {
                if (line[i] == ' ' && line[i + 1] == ' ') {
                    flag = i;
                    break;
                } else {
                    word += line[i];
                }
            }
            s_name = word;
            word.clear();

            for (int i = flag; i < line.size(); ++i) {
                if (!word.empty() && line[i] == ' ') {
                    flag = i;
                    break;
                } else if (line[i] >= '0' && line[i] <= '9') {
                    word += line[i];
                }
            }
            s_num = stoi(word);
            word.clear();

            for (int i = flag; i < line.size(); ++i) {
                if (line[i] >= '0' && line[i] <= '9') {
                    word += line[i];
                } else if (line[i] == 'K') {
                    break;
                }
            }
            mem = stoi(word);
            word.clear();

            Process newProcess(name1, s_name, pid1, mem, s_num);
            processes.push_back(newProcess);
        }

        inputFile.close();
    }

    void sortBy(int sortBy) {
        if (sortBy == 1) {
            sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
                return a.getName() < b.getName();
            });
        } else if (sortBy == 2) {
            sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
                return a.getPID() < b.getPID();
            });
        } else if (sortBy == 3) {
            sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
                return a.getMemoryUsage() > b.getMemoryUsage();
            });
        }
    }

    void display() const {
        cout << "====================================================================================================" << endl;

        cout<<"| Process Name                 | PID      |Session Name     |Session_#       | Memory Usage (KB)    |" << endl;
        cout << "====================================================================================================" << endl;

        for (const auto& process : processes) {
            cout << "| " << left << setw(28) << process.getName() << " | "
                 << setw(8) << process.getPID() << " | "
                 << setw(15) << process.getSessionName() << " | "
                 << setw(14) << process.getSessionNum() << " | "
                 << setw(20) << process.getMemoryUsage() << " KB" << " |" << endl;
        }

        cout << "========================================================================================================" << endl;
    }
};

int main() {
    ProcessList processList;
    processList.fill();

    int sortBy;
    while (true) {
        cout << "Menu :\n";
        cout << "Welcome To Task Manager, Please Enter:\n";
        cout << "1. Sort By Name\n";
        cout << "2. Sort By PID\n";
        cout << "3. Sort By Memory Usage\n";
        cout << "0. EXIT\n";

        cin >> sortBy;

        if (sortBy == 0) {
            return 0;
        }

        processList.sortBy(sortBy);
        processList.display();
    }

    return 0;
}

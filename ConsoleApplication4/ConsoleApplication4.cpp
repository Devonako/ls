#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"
#define ANSI_COLOR_UNDERLINE "\x1b[4m"
#define ANSI_COLOR_BOLD "\x1b[1m"
#define ANSI_COLOR_ITALIC "\x1b[3m"
bool ListDirectoryContents(const wchar_t* sDir)
{
    WIN32_FIND_DATA fdFile;
    HANDLE hFind = 0;

    wchar_t sPath[2048];

    //Specify a file mask. *.* = We want everything! 
    wsprintfW(sPath, L"%s\\*.*", sDir);

    if ((hFind = FindFirstFileW(sPath, &fdFile)) == ((HANDLE)(LONG_PTR)-1))
    {
        wprintf(L"Path not found: [%s]\n", sDir);
        return false;
    }

    do
    {
        //Find first file will always return "."
        //    and ".." as the first two directories. 
        if (wcscmp(fdFile.cFileName, L".") != 0
            && wcscmp(fdFile.cFileName, L"..") != 0)
        {
            //Build up our file path using the passed in 
            //  [sDir] and the file/foldername we just found: 
            wsprintfW(sPath, L"%s\\%s", sDir, fdFile.cFileName);
        
            //Is the entity a File or Folder? 
            if (fdFile.dwFileAttributes & 0x00000010)
            {

                wprintf("\x1b[34m" L"%s  ", sPath);
                printf("\x1b[0m");
                //wprintf(L"Directory: %s\n", sPath);
                //ListDirectoryContents(sPath); //Recursion, I love it! 
            }
            else {
                wprintf("\x1b[31m" L"%s  ", sPath);
                printf("\x1b[0m");
            }
        }
    } while (FindNextFileW(hFind, &fdFile)); //Find the next file. 

    FindClose(hFind); //Always, Always, clean things up! 

    return true;
}

int main() {
    TCHAR tszBuffer[260];
    DWORD dwRet;

    dwRet = GetCurrentDirectoryW(260, tszBuffer);
    ListDirectoryContents(tszBuffer);
}
#include <string>
#include <atlimage.h>
using namespace std;

CImage image;
WIN32_FIND_DATA ffd; 
HANDLE file; 
HRESULT readIm;
LPSECURITY_ATTRIBUTES crDir;
char buf[15];

int main(int argc, char *argv[])
{ 
 string fpath = "";
 for(int i = 0; i < strlen(argv[1]); i++) 
  if(argv[1][i] == '\\') fpath += "\\\\"; else fpath += argv[1][i];
 if(!fpath.size()) return 0;
 if(fpath[fpath.size()-1] != '\\') fpath += "\\\\";
 wstring path(fpath.begin(), fpath.end());
 
 file = FindFirstFile((path + L"*.*").c_str(), &ffd); 
 do {
  if (!(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
   image.Destroy();
   readIm = image.Load((path + ffd.cFileName).c_str());
   if(readIm == S_OK) {
    sprintf(buf, "%dx%d", image.GetWidth(), image.GetHeight());
    string R = buf; 
    wstring Rdir(R.begin(),R.end()); 
    CreateDirectory((path + Rdir).c_str(), crDir);
    MoveFile((path + ffd.cFileName).c_str(), ((path + Rdir) + L"\\\\" + ffd.cFileName).c_str());
   } else {
    CreateDirectory((path + L"!File With Fail Data").c_str(), crDir);
    MoveFile((path + ffd.cFileName).c_str(), (path + L"!File With Fail Data\\\\" + ffd.cFileName).c_str());
   }
  }
 } while (FindNextFile(file, &ffd) != 0);
}

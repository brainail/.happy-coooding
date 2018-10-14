#include <string>
#include <atlimage.h>
using namespace std;

CImage image;
WIN32_FIND_DATA ffd; 
HANDLE file; 
HRESULT readIm;
LPSECURITY_ATTRIBUTES crDir;
char buf[15];

int main() { 
 file = FindFirstFile(L"*.*", &ffd); 
 do {
  if (!(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
   image.Destroy();
   readIm = image.Load(ffd.cFileName);
   if(readIm == S_OK) {
    sprintf(buf, "%dx%d", image.GetWidth(), image.GetHeight());
    wstring Rdir(buf, buf+strlen(buf));
    CreateDirectory(Rdir.c_str(), crDir);
    MoveFile(ffd.cFileName, (Rdir + L"\\\\" + ffd.cFileName).c_str());
   } else {
    CreateDirectory(L"!Unknown", crDir);
    MoveFile(ffd.cFileName, (wstring(L"!Unknown\\\\") + ffd.cFileName).c_str());
   }
  }
 } while (FindNextFile(file, &ffd) != 0);
}

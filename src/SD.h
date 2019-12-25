#ifndef _SD_h_
#define _SD_h_
#include <stdio.h>

class SDClass
{
  private:
    char *mountPoint = "/sd";
    char *realpath(char *path);
  public:
    bool begin(int miso = 2, int mosi = 15, int sck = 14, int cs = 13);
    bool end();
    bool exists(char* path);
    bool mkdir(char* path);
    FILE*open(char* path, char* mode);
    bool rename(char* path, char* newPath);
    bool remove(char* path);
    bool rmdir(char* path);
};

extern SDClass SD;

#endif

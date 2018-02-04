#include <iostream>
#include <fstream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
extern "C"{
    #include "rax-master/rax.h"
}
#include "tinydir.h"
#include "BluePyroLibraries/IO/IO.h"

using namespace std;

rax *rt = raxNew();

void addToTree(unsigned char *_str, int _length){
    void *counter = new int(0);
    if(raxInsert(rt,_str,_length,counter,NULL)){
        counter = raxFind(rt,_str,_length);
        counter++;
    }
}
void addFileToTree(const char *fileName){
    string line;
    unsigned char line2[500];
    ifstream myfile (fileName);
    if(myfile.is_open()){
        while ( getline (myfile,line) ){
            unsigned char *str = (unsigned char *)line.c_str();
            addToTree(str,line.length());
        }
        myfile.close();
    }else{
        cout << "Error: Can't read file!" << endl;
    }
}
#define LOOP_ALL_FILES_OF_EXTENSION(_dir, _ext) \
{ \
    tinydir_dir dir; \
    if(!_dir.length()){ \
        tinydir_open(&dir, "."); \
    }else{ \
        tinydir_open(&dir, _dir.c_str()); \
    } \
    while (dir.has_next){ \
        tinydir_file file; \
        tinydir_readfile(&dir, &file); \

#define LOOP_ALL_FILES_OF_EXTENSION_END() \
        tinydir_next(&dir); \
    } \
    tinydir_close(&dir); \
}

int main(int argc, char** argv){

    rt = raxNew();
    addFileToTree("twilight0_patterns.txt");
    //raxShow(rt);
    return 0;
}

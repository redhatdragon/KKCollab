#include <iostream>
#include <fstream>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "tinydir.h"
extern "C"{
    #include "rax-master/rax.h"
    //#include "BluePyroLibraries/IO/IO.h"
}

using namespace std;

rax *rt = raxNew();
int highest = 0;
int totalCount = 0;

void addToTree(unsigned char *_str, int _length){
    void *counter = new int(0);
    if(raxInsert(rt,_str,_length,counter,NULL)){
        counter = raxFind(rt,_str,_length);
        counter = (int *)counter+1;
        if(highest < (int)counter){
            highest = (int)counter;
        }
        return;
    }
    totalCount++;
}
void addFileToTree(const char *fileName){
    string line;
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
void addFileToTreeRepeat(const char *fileName, int _count){
    string line;
    fstream myfile (fileName);
    string total[50000];
    int lineCount = 0;
    if(myfile.is_open()){
        while ( getline (myfile,line) ){
            total[lineCount] = line;
            lineCount++;
        }
        myfile.close();
    }else{
        cout << "Error: Can't read file!" << endl;
    }
    for(int i = 0; i < _count; i++){
        //cout << i << endl;
        rt = raxNew();
        for(int j = 0; j < lineCount; j++){
            addToTree((unsigned char *)total[j].c_str(),total[j].length());
        }
        raxFree(rt);
    }
}
void addBinFileRepeat(const char *fileName, int _count){
    const int line_count = 120;
    FILE *file;
    file=fopen(fileName,"wb");
    unsigned char buffer[40*line_count];
    if(file){
        fwrite(&buffer, 1, 40*line_count, file);
        for(int i = 0; i < _count; i++){
            //cout << i << endl;
            rt = raxNew();
            for(int j = 0; j < line_count; j++){
                addToTree(&buffer[j*40],40);
            }
            //raxShow(rt);
            raxFree(rt);
        }
        //cout << highest << endl;
        cout << totalCount << endl;
        return;
    }
    printf("Error: can't open file!");
}
#define LOOP_ALL_FILES(_dir) \
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

#define LOOP_ALL_FILES_END() \
        tinydir_next(&dir); \
    } \
    tinydir_close(&dir); \
}

int main(int argc, char** argv){

    rt = raxNew();
    //addFileToTreeRepeat("twilight0_patterns.txt", 63750);
    addBinFileRepeat("twilight0.eth", 63750);
    //raxShow(rt);

    /*LOOP_ALL_FILES(string("."))
    if(file.extension == string("txt")){
        //cout << file.name << endl;
    }
    LOOP_ALL_FILES_END()*/
    return 0;
}

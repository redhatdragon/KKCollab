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
int highestDepth;
int totalNodeCount;

void addToTree(unsigned char *_str, int _length){
    void *counter = new int(0);
    if(!raxInsert(rt,_str,_length,counter,NULL)){
        counter = raxFind(rt,_str,_length);
        counter = (int *)counter+1;
        if(highestDepth < (int)counter){
            highestDepth = (int)counter;
        }
        return;
    }
    totalNodeCount++;
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
    highestDepth = 0;
    totalNodeCount = 0;

    rt = raxNew();
    //addFileToTreeRepeat("twilight0_patterns.txt", 63750);
    //addFileToTree("twilight0_patterns.txt");
    addBinFileRepeat("twilight0.eth", 1);
    cout << totalNodeCount << endl;
    cout << highestDepth << endl;
    //raxShow(rt);

    /*LOOP_ALL_FILES(string("."))
    if(file.extension == string("txt")){
        //cout << file.name << endl;
    }
    LOOP_ALL_FILES_END()*/
    return 0;
}

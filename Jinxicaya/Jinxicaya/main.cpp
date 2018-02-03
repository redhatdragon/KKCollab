#include <iostream>
#include <fstream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
extern "C"{
    #include "rax-master/rax.h"
}

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

int main(int argc, char** argv){

    rt = raxNew();
    addFileToTree("twilight0_patterns.txt");
    raxShow(rt);
    return 0;
}

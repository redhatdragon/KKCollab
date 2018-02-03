#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
extern "C"{
    #include "rax-master/rax.h"
}

int main(int argc, char** argv){
    void *y = new char(5);

    rax *rt = raxNew();
    raxInsert(rt,(unsigned char*)"122>122>122>122>122",5,y,NULL);
    raxInsert(rt,(unsigned char*)"142>141>141>141>141",5,0,NULL);
    raxInsert(rt,(unsigned char*)"141>141>141>141>129",5,0,NULL);
    raxInsert(rt,(unsigned char*)"100>133>141>141>141",5,0,NULL);
    raxInsert(rt,(unsigned char*)"133>141>141>141>141",5,0,NULL);
    raxShow(rt);

    return 0;
}

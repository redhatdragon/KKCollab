#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
extern "C"{
    #include "rax-master/rax.h"
}

int main(int argc, char** argv){
    rax *rt = raxNew();
    raxInsert(rt,(unsigned char*)"mykey",5,0,NULL);

    return 0;
}

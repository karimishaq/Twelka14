#include "main_game.h"

SDL_Surface *buat_lapisan(int panjang, int tinggi){
SDL_Surface *lapisan;
    Uint32 rm, gm, bm, am;
    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
        rm = 0xff000000;
        gm = 0x00ff0000;
        bm = 0x0000ff00;
        am = 0x000000ff;
    #else
        rm = 0x000000ff;
        gm = 0x0000ff00;
        bm = 0x00ff0000;
        am = 0xff000000;
    #endif
    lapisan=SDL_CreateRGBSurface(SDL_SWSURFACE, panjang, tinggi, 32, rm, gm, bm, am);
    return lapisan;
}

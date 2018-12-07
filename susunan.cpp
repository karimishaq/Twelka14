#include "main.h"

char** isi_susunan(int xmax, int ymax, int tertutup){
int x, y, ujungx, ujungy;
char** a;
    ujungx=xmax-1;
    ujungy=ymax-1;
    a=(char**)malloc(sizeof(char*)*ymax);
    y=0;
    while(y<ymax){
        a[y]=(char*)malloc(sizeof(char)*xmax);
        y++;
    }

    y=0;
    while(y<ymax){
        x=0;
        while(x<xmax){
            a[y][x]=0;
            x++;
        }
        y++;
    }

    y=0;
    while(y<ymax){
        a[y][0]=5;
        a[y][ujungx]=5;
        y++;
    }

    x=1;
    while(x<ujungx){
        a[ujungy][x]=5;
        a[ujungy][x]=5;
        x++;
    }
    if(tertutup!=0){
        x=0;
        while(x<ujungx){
            a[0][x]=5;
            a[0][x]=5;
            x++;
        }
    }
    return a;
}

int kosongkan_susunan(char** susunan, int ymax){
int y=0;
    while(y<ymax){
        free(susunan[y]);
        y++;
    }
    free(susunan);
    return 0;
}

int gambar_susunan(SDL_Surface *latar, SDL_Surface **box, char **a, int xmax, int ymax){
int x, y, jenis;
SDL_Rect dstrect;
    y=0;
    while(y<ymax){
        x=0;
        while(x<xmax){
            dstrect.x = x*32;
            dstrect.y = y*32;
            jenis=a[y][x];
            if((jenis!=0)&&(jenis<9)){
                SDL_BlitSurface(box[jenis], 0, latar, &dstrect);
            }
            x++;
        }
        y++;
    }
    return 0;
}

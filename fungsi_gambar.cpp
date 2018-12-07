#include "main.h"

int gambar_layar(struct Windowku *mwindow, SDL_Surface *latar){
struct tombolku *tombol;
struct tabku *ctab;
struct Menuku *mmenu, *menu_aktif;
SDL_Surface *tgambar;
TTF_Font *huruf;
SDL_Color hitam={0, 0, 0};
dataku *dataku, *dtbatas;
int i, n, x, y, jtampil;
int panjang=0;
    ctab=mwindow->ctab;
    if(ctab!=0){
        i=0;
        n=ctab->jtombol;
        while(i<n){
            tombol=&ctab->tombol[i];
            tgambar=tombol->cgambar;
            if(tgambar!=0){
                tampilkan_gambar(latar, tgambar, tombol->x, tombol->y, 0, 0, tgambar->w, tgambar->h);
            }
            i++;
        }
    }

    ctab=mwindow->ctab;
    if(ctab!=0){
        i=0;
        n=ctab->jtombol;
        while(i<n){
            tombol=&ctab->tombol[i];
            tgambar=tombol->cgambar;
            if(tgambar!=0){
                tampilkan_gambar(latar, tgambar, tombol->x, tombol->y, 0, 0, tgambar->w, tgambar->h);
            }
            i++;
        }
    }

    //status window
    if(mwindow->status==MENU_DITAMPILKAN){
        if(mwindow->menu_aktif!=0){
            mmenu=mwindow->menu_pertama;
            if(mmenu!=0){
                menu_aktif=mwindow->menu_aktif->pilihan;
                while(mmenu!=menu_aktif){
                    tgambar=mmenu->gambar_menu;
                    tampilkan_gambar(latar, tgambar, mmenu->x, mmenu->y, 0, 0, tgambar->w, tgambar->h);
                    mmenu=mmenu->pilihan;
                }
                mmenu=mwindow->menu_aktif;
                if(mmenu!=0){
                    if(mmenu->pilihan!=0){
                        mmenu=mmenu->pilihan;
                        if(mmenu->batas->berikutnya!=mmenu->batas){
                            tgambar=mmenu->gambar_menu;
                            tampilkan_gambar(latar, tgambar, mmenu->x, mmenu->y, 0, 0, tgambar->w, tgambar->h);
                        }
                    }
                }
            }
        }
    }else if(mwindow->status==PILIHAN_DITAMPILKAN){
        huruf=mwindow->huruf;
        tombol=ctab->tombol_aktif;
        dtbatas=&tombol->batas_pertama;
        x=tombol->x;
        y=tombol->y+24;
        panjang=tombol->cx-x;
        jtampil=tombol->jtampil;
        gambar_kotak(latar, x, y, panjang, (20*jtampil)+4, 0, 0, 0);
        gambar_kotak(latar, x+2, y+2, panjang-4, (20*jtampil), 255, 255, 255);
        if((dtbatas==dtbatas->berikutnya)||(tombol->atas_aktif==0)){
            return 0;
        }
        i=0;
        x+=4;
        y+=2;
        dataku=tombol->atas_aktif;
        while((dataku!=dtbatas)&&(i<jtampil)){
            if(dataku==tombol->pilihan){
                gambar_kotak(latar, x-2, y, panjang-4, 20, 0, 255, 0);
            }
            gambar_tulisan(latar, huruf, dataku->teks[0].isi, hitam, x, y);
            tombol->bawah=dataku;
            dataku=dataku->berikutnya;
            y+=20;
            i++;
        }
    }
    return 0;
}

int gambar_tulisan(SDL_Surface *latar, TTF_Font *huruf, char *s, SDL_Color warna, int x, int y){
SDL_Surface *tulisan;
SDL_Rect rct;
    if(s!=0){
        if(s[0]!=0){
            tulisan=TTF_RenderText_Blended(huruf, s, warna);
            if(tulisan!=0){
                rct.x=x;
                rct.y=y;
                rct.w=tulisan->w;
                rct.h=tulisan->h;
                SDL_BlitSurface(tulisan, 0, latar, &rct);
                SDL_FreeSurface(tulisan);
            }
        }
    }
    return 0;
}

int tampilkan_gambar(SDL_Surface *latar, SDL_Surface *gambar, int x1, int y1, int x2, int y2, int w, int h){
SDL_Rect rct, rcd;
    if(gambar!=0){
        rcd.x=x2;
        rcd.y=y2;
        rcd.w=w;
        rcd.h=h;
        rct.x=x1;
        rct.y=y1;
        rct.w=w;
        rct.h=h;
        SDL_BlitSurface(gambar, &rcd, latar, &rct);
    }
    return 0;
}

SDL_Surface *tambah_gambar(const char *nama_file){
SDL_Surface *gbr;
    gbr=IMG_Load(nama_file);
    return gbr;
}

SDL_Surface *buat_lapisan(int panjang, int tinggi){
SDL_Surface *lapisan=0;
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

int gambar_kotak(SDL_Surface *layar, int x, int y, int panjang, int tinggi, int r, int g, int b){
SDL_Rect rct;
    rct.x=x;
    rct.y=y;
    rct.w=panjang;
    rct.h=tinggi;
    SDL_FillRect(layar, &rct, SDL_MapRGB(layar->format, r, g, b));
    return 0;
}

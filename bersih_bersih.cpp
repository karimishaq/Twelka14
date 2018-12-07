#include "main.h"
#include <stdio.h>

int bersihkan_menu(struct Menuku* cmenu){
struct Menuku *batas, *data;
    if(cmenu!=0){
        batas=cmenu->batas;
        data=batas->berikutnya;
        while(data!=batas){
            bersihkan_menu(data);
            data=data->berikutnya;
        }
        if(cmenu->gambar_menu!=0){
            free(cmenu->gambar_menu);
        }
        free(cmenu->nama);
        free(cmenu);
    }
    return 0;
}

int bersihkan_tab(struct tabku *ctab){
struct tombolku *tombol;
int i, n;
    if(ctab!=0){
        i=0;
        n=ctab->jtombol;
        while(i<n){
            tombol=&ctab->tombol[i];
            if(tombol->gdilepas!=0){
                SDL_FreeSurface(tombol->gdilepas);
            }
            if(tombol->gditekan!=0){
                SDL_FreeSurface(tombol->gditekan);
            }
            if(tombol->gdilewati!=0){
                SDL_FreeSurface(tombol->gdilewati);
            }

            if(tombol->jenis==TB_DAFTARKU || tombol->jenis==TB_PILIHAN){
                bersihkan_data_daftar(tombol);
            }
            i++;
        }
        ctab->jenis=0;
        ctab->jtombol=0;
        ctab->tombol_aktif=0;
    }
    return 0;
}

int bersihkan_data_daftar(struct tombolku *tombol){
struct dataku *data, *batas, *berikutnya;
    batas=&tombol->batas_pertama;
    data=batas->asli_berikutnya;
    while(data!=batas){
        berikutnya=data->asli_berikutnya;
        free(data);
        data=berikutnya;
    }
    return 0;
}

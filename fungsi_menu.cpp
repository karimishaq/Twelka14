#include "main.h"
#include <dirent.h>

char sdir[]="data/";

int tampilkan_menu(struct Windowku *mwindow, struct Menuku *cmenu, int x, int y){
    cmenu->x = x;
    cmenu->y = y;
    cmenu->pilihan = 0;
    mwindow->menu_pertama = cmenu;
    mwindow->menu_aktif = cmenu;
    mwindow->status=MENU_DITAMPILKAN;
    return 0;
}

int gambar_menu(TTF_Font *huruf, struct Menuku *mmenu){
struct Menuku *cmenu, *batas;
SDL_Color warna= {0, 0, 0};
int y, panjang;
    if(mmenu==0)return 0;
    //atur tinggi kotak menu
    mmenu->h=4;
    mmenu->w=0;
    batas=mmenu->batas;
    cmenu=batas->berikutnya;
    while(cmenu!=batas){
        TTF_SizeText(huruf, cmenu->nama, &panjang, &y);
        if(panjang>mmenu->w){
            mmenu->w=panjang;
        }
        mmenu->h+=20;
        cmenu=cmenu->berikutnya;
    }
    mmenu->w+=16;
    //
    mmenu->gambar_menu=buat_lapisan(mmenu->w, mmenu->h);
    gambar_kotak(mmenu->gambar_menu, 0, 0, mmenu->w, mmenu->h, 255, 255, 0);
    y=0;
    batas=mmenu->batas;
    cmenu=batas->berikutnya;
    while(cmenu!=batas){
        if(cmenu==mmenu->pilihan){
            gambar_kotak(mmenu->gambar_menu, 2, y+2, mmenu->w-4, 18, 0, 255, 0);
        }
        gambar_tulisan(mmenu->gambar_menu, huruf, cmenu->nama, warna, 4, y);
        y+=20;
        cmenu=cmenu->berikutnya;
    }
    return 0;
}

struct Menuku *buat_menu(struct Menuku* ortu, char *nama, int id, TTF_Font *huruf){
struct Menuku *tmenu, *batas;
    tmenu=(struct Menuku*) malloc(sizeof(struct Menuku));
    tmenu->x=0;
    tmenu->y=0;
    tmenu->w=0;
    tmenu->h=0;
    tmenu->pilihan=0;
    tmenu->gambar_menu=0;
    tmenu->id=id;
    //tambahkan kata
    if(nama!=0){
        tmenu->nama=(char*)malloc(sizeof(char)*(str_panjang(nama)+1));
        str_salin(tmenu->nama, nama);
    }else{
        tmenu->nama=(char*)malloc(sizeof(char));
        tmenu->nama[0]=0;
    }
    tmenu->ortu=ortu;
    //
    tmenu->batas=(struct Menuku*)malloc(sizeof(struct Menuku));
    tmenu->batas->sebelumnya=tmenu->batas;
    tmenu->batas->berikutnya=tmenu->batas;
    if(ortu!=0){
        ortu->id=0;
        batas=ortu->batas;
        batas->sebelumnya->berikutnya=tmenu;
        tmenu->sebelumnya=batas->sebelumnya;
        tmenu->berikutnya=batas;
        batas->sebelumnya=tmenu;
        gambar_menu(huruf, ortu);
    }
    return tmenu;
}

int aksi_klik_menu(struct Windowku *mwindow, int id){
struct tombolku *tombol=0;
struct tabku *ctab;
struct dataku *data;
char stmp[256];
int i, n;
    ctab=mwindow->ctab;
    switch(id){
        case IDM_BARU:
            if(mwindow->ctab!=&mwindow->tab[0]){
                mwindow->ltab=mwindow->ctab;
                bersihkan_tab(mwindow->ltab);
                mwindow->ctab=&mwindow->tab[0];
            }
            break;
        case IDURUT_ALFABET:
            tombol=dapatkan_tombol(mwindow->ctab, ID_DAFTAR);
            urutkan_data(tombol, IDURUT_ALFABET, IDKOLOM_KATA);
            break;
        case IDURUT_PANJANG:
            tombol=dapatkan_tombol(mwindow->ctab, ID_DAFTAR);
            urutkan_data(tombol, IDURUT_PANJANG, IDKOLOM_KATA);
            break;
        case IDURUT_NILAI:
            tombol=dapatkan_tombol(mwindow->ctab, ID_DAFTAR);
            urutkan_data(tombol, IDURUT_NILAI, IDKOLOM_KATA);
            break;
        case IDURUT_BALIK:
            tombol=dapatkan_tombol(mwindow->ctab, ID_DAFTAR);
            urutkan_data(tombol, IDURUT_BALIK, IDKOLOM_KATA);
            break;

        case ID_HOOK_WORDS:
            tombol=dapatkan_tombol(mwindow->ctab, ID_DAFTAR);
            if(tombol!=0){
                hook_words(tombol);
            }
            break;
        case ID_BACK_HOOK:
            tombol=dapatkan_tombol(mwindow->ctab, ID_DAFTAR);
            if(tombol!=0){
                back_hook_words(tombol);
            }
            break;
        case ID_FRONT_HOOK:
            tombol=dapatkan_tombol(mwindow->ctab, ID_DAFTAR);
            if(tombol!=0){
                front_hook_words(tombol);
            }
            break;
        case ID_PALINDROM:
            tombol=dapatkan_tombol(mwindow->ctab, ID_DAFTAR);
            if(tombol!=0){
                cari_palindrom(tombol, IDKOLOM_KATA);
            }
            break;
        case ID_HURUF_UNIK:
            tombol=dapatkan_tombol(mwindow->ctab, ID_DAFTAR);
            if(tombol!=0){
                cari_kata_unik(tombol, IDKOLOM_KATA);
            }
            break;
        case IDM_SEMUA_KATA:
            tombol=dapatkan_tombol(mwindow->ctab, ID_DAFTAR);
            urutkan_data(tombol, IDM_SEMUA_KATA, IDKOLOM_KATA);
            break;
        case IDM_KELUAR:
            mwindow->selesai=1;
            break;
        case IDM_SALIN_DATA:
            tombol=dapatkan_tombol(mwindow->ctab, ID_DAFTAR);
            data=tombol->pilihan;
            stmp[0]=0;
            i=0;
            n=tombol->jkolom;
            while(i<n){
                strcat(stmp, data->teks[i].isi);
                i++;
                if(i<n)strcat(stmp, (char*)":");
            }
            SDL_SetClipboardText(stmp);
            break;
        case IDM_POTONG:
            tombol=ctab->tombol_aktif;
            if(tombol!=0){
                if(tombol->jenis==TB_TULISAN){
                    SDL_SetClipboardText(tombol->tulisan);
                    tombol->tulisan[0]=0;
                }
            }
            break;
        case IDM_SALIN:
            tombol=ctab->tombol_aktif;
            if(tombol!=0){
                if(tombol->jenis==TB_TULISAN){
                    SDL_SetClipboardText(tombol->tulisan);
                }
            }
            break;
        case IDM_TEMPEL:
            tombol=ctab->tombol_aktif;
            if(tombol!=0){
                if(tombol->jenis==TB_TULISAN){
                    strcpy(tombol->tulisan, SDL_GetClipboardText());
                    hurufbesar(tombol->tulisan);
                    n=strlen(tombol->tulisan);
                    for(i=0;i<n;i++){
                        if(tombol->tulisan[i]<'A' || tombol->tulisan[i]>'Z'){
                            tombol->tulisan[i]='?';
                        }
                    }
                }
            }
            break;
        case IDM_HAPUS:
            tombol=ctab->tombol_aktif;
            if(tombol!=0){
                if(tombol->jenis==TB_TULISAN){
                    tombol->tulisan[0]=0;
                }
            }
            break;
        default:
            break;
    }
    perbaharui_tombol(mwindow, mwindow->ctab, 0);
    return 0;
}

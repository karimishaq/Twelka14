#include "main.h"
#include <dirent.h>

char sberkas[]="Berkas";
char sdirs[]="data/";
char sxletter[]="Extra Letters";
char sdialog[]="Open File";
char sbuka[]="Open";
char sketerangan[]="Buka File : ";
//menu daftar
char sm_sort[]="Sort";
char sm_alfabet[]="Alfabet";
char sm_length[]="length";
char sm_point[]="Point";
char sm_reverse[]="Reverse";

struct tabku *buat_dialog(struct Windowku *mwindow){
struct tabku *ctab=0;
struct tombolku *daftar;
    ctab=&mwindow->tab[0];
    ctab->jtombol=0;
    ctab->tombol_aktif=0;
    mwindow->tombol_dilewati=0;
    mwindow->ctab=ctab;
    mwindow->ltab=ctab;
    //xxx
    buat_tombol(mwindow, TB_TOMBOL_TEKAN, 0, (char*)"tombol_menu.png", 4, 4, 0, 0, ID_TAB0, 1);
    buat_tombol(mwindow, TB_TOMBOL_TEKAN, (char*)"Tab 1", (char*)"tombol_tekan.png", 30, 4, 0, 0, ID_TAB1, 0);
    buat_tombol(mwindow, TB_TOMBOL_TEKAN, (char*)"Tab 2", (char*)"tombol_tekan.png", 186, 4, 0, 0, ID_TAB2, 0);
    buat_tombol(mwindow, TB_TOMBOL_TEKAN, (char*)"Tab 3", (char*)"tombol_tekan.png", 342, 4, 0, 0, ID_TAB3, 0);
    //
    buat_tombol(mwindow, TB_NAMA, sketerangan, 0, 4, 34, 20, 40, ID_KETERANGAN, 0);
    daftar=buat_tombol(mwindow, TB_DAFTARKU, 0, 0, 4, 58, 632, 390, ID_DAFTAR_BERKAS, 1);
    buat_tombol(mwindow, TB_TOMBOL_TEKAN, (char*)sbuka, (char*)"tombol_tekan.png", 4, 452, 0, 0, ID_BUKA_BERKAS, 0);
    isi_daftar_berkas(daftar);
    perbaharui_tombol(mwindow, mwindow->ctab, 1);
    return ctab;
}

SDL_Surface *mulai_program(struct Windowku *mwindow){
struct Menuku *tmenu;
TTF_Font *huruf;
    mwindow->tab[0].jtombol=0;
    mwindow->tab[0].id=0;
    mwindow->tab[1].jtombol=0;
    mwindow->tab[1].id=1;
    mwindow->tab[2].jtombol=0;
    mwindow->tab[2].id=2;
    mwindow->tab[3].jtombol=0;
    mwindow->tab[3].id=3;
    mwindow->gambar.panah=tambah_gambar("panah.png");

    //inisialisasi window utama
    huruf=TTF_OpenFont("FreeSans.ttf", 14);
    mwindow->huruf=huruf;
    mwindow->tombol_dilewati=0;
    mwindow->tombol_ditekan=0;
    mwindow->ctab=0;
    mwindow->warna.r=0;
    mwindow->warna.g=0;
    mwindow->warna.b=0;
    mwindow->status=STATUS_AWAL;
    mwindow->proses=0;
    mwindow->selesai=0;

    //buat menu daftar kata
    mwindow->menu_dtkata=buat_menu(0, (char *)"Daftar", 0, huruf);
    tmenu=buat_menu(mwindow->menu_dtkata, (char *)"New List", IDM_BARU, huruf);
    tmenu=buat_menu(mwindow->menu_dtkata, (char *)"Copy", IDM_SALIN_DATA, huruf);
    tmenu=buat_menu(mwindow->menu_dtkata, sm_sort, 0, huruf);
        buat_menu(tmenu, sm_alfabet, IDURUT_ALFABET, huruf);
        buat_menu(tmenu, sm_length, IDURUT_PANJANG, huruf);
        buat_menu(tmenu, sm_point, IDURUT_NILAI, huruf);
        buat_menu(tmenu, sm_reverse, IDURUT_BALIK, huruf);
    tmenu=buat_menu(mwindow->menu_dtkata, (char *)"Show Only : ", 0, huruf);
        buat_menu(tmenu, (char *)"Palindrom", ID_PALINDROM, huruf);
        buat_menu(tmenu, (char *)"Unique letters", ID_HURUF_UNIK, huruf);
        buat_menu(tmenu, (char *)"Hook Words", ID_HOOK_WORDS, huruf);
        buat_menu(tmenu, (char *)"Front Hook Words", ID_FRONT_HOOK, huruf);
        buat_menu(tmenu, (char *)"Back Hook Words", ID_BACK_HOOK, huruf);
    tmenu=buat_menu(mwindow->menu_dtkata, (char *)"Show All Words", IDM_SEMUA_KATA, huruf);
    //
    mwindow->menu_teks=buat_menu(0, (char *)"Teks", 0, huruf);
    tmenu=buat_menu(mwindow->menu_teks, (char *)"Cut", IDM_POTONG, huruf);
    tmenu=buat_menu(mwindow->menu_teks, (char *)"Copy", IDM_SALIN, huruf);
    tmenu=buat_menu(mwindow->menu_teks, (char *)"Paste", IDM_TEMPEL, huruf);
    tmenu=buat_menu(mwindow->menu_teks, (char *)"Delete", IDM_HAPUS, huruf);
    //
    mwindow->menu_aktif=0;
    //
    mwindow->waktu=0;
    mwindow->cwindow = SDL_CreateWindow( "Twelka", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN );
    mwindow->layar= SDL_GetWindowSurface(mwindow->cwindow);
    return mwindow->layar;
}

int isi_daftar_berkas(struct tombolku *tombol){
struct dataku *data, *batas_kolom;
dirent *dp;
DIR *tdir;
int posisi=0;
    batas_kolom=&tombol->batas_pertama;
    if((tdir=opendir(sdirs))){
        while((dp=readdir(tdir))){
            if(dp->d_name[0]!='.'){
                posisi++;
                data=tambah_data_daftar(tombol);
                data->teks[0].x_wcard=posisi;
                data->teks[0].panjang=ganti_isi_data(data, 0, dp->d_name);
            }
        }
        closedir(tdir);
    }
    tombol->atas_aktif=batas_kolom->berikutnya;
    tombol->pilihan=batas_kolom->berikutnya;
    tombol->pos=1;
    return 0;
}

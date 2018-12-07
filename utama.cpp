#include "main.h"

char snilai[]="Point : ";
char sposisi[]="Position : ";
char sjkata[]="All Words : ";

struct Windowku window_utama;
SDL_Surface *screen;

int main ( int argc, char** argv){
int i=0;
int x=0;
struct tombolku *tombol;
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return (1);
    }

    if(TTF_Init()==-1){
        printf("TTF_Init: %s\n", TTF_GetError());
        exit(2);
    }

    if(IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG)==-1){
        printf("SDL_Init: %s\n", TTF_GetError());
        exit(2);
    }

    screen=mulai_program(&window_utama);
    buat_dialog(&window_utama);
    window_utama.ctab=&window_utama.tab[0];
    window_utama.ltab=&window_utama.tab[1];

    if ( !screen ){
        printf("Tidak bisa menampilkan layar: %s\n", SDL_GetError());
        return 1;
    }

    while (window_utama.selesai==0){
        SDL_Event e;
        while(SDL_PollEvent(&e)){
            loop_utama(&e, &window_utama);
        }

        if(window_utama.ctab==0)break;
        x=SDL_GetTicks();
        tombol=window_utama.ctab->tombol_aktif;
        if(tombol!=0){
            if(tombol->jenis==TB_TULISAN){
                if(x-window_utama.waktu>=500){
                    if(window_utama.ctab!=0){
                        if(tombol->status==0){
                            tombol->status=1;
                        }else{
                            tombol->status=0;
                        }
                        tombol->perbaharui=1;
                        perbaharui_tombol(&window_utama, window_utama.ctab, 0);
                        window_utama.waktu=x;
                    }
                }
            }else if(tombol->jenis==TB_DAFTARKU){
                if(x-window_utama.waktu>=200){
                    if(window_utama.ctab!=0){
                    struct tombolku *tombol=window_utama.ctab->tombol_aktif;
                        if(tombol->status==DAFTAR_TURUN){
                            pindah_data(tombol, SDLK_DOWN);
                        }else if(tombol->status==DAFTAR_NAIK){
                            pindah_data(tombol, SDLK_UP);
                        }else if(tombol->status==DAFTAR_TURUN_HALAMAN){
                            pindah_data(tombol, SDLK_PAGEDOWN);
                            daftar_susun(&window_utama, tombol);
                        }else if(tombol->status==DAFTAR_NAIK_HALAMAN){
                            pindah_data(tombol, SDLK_PAGEUP);
                            daftar_susun(&window_utama, tombol);
                        }
                        tombol->perbaharui=1;
                        twelka_atur_status(&window_utama);
                        perbaharui_tombol(&window_utama, window_utama.ctab, 0);
                        window_utama.waktu=x;
                    }
                }
            }
        }
        //
        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 255, 255, 255));
        gambar_layar(&window_utama, screen);
        SDL_UpdateWindowSurface(window_utama.cwindow);
    }

    for(i=0;i<4;i++){
        bersihkan_tab(&window_utama.tab[i]);
    }
    bersihkan_menu(window_utama.menu_dtkata);
    bersihkan_menu(window_utama.menu_teks);
    SDL_DestroyWindow(window_utama.cwindow);
    SDL_Quit();
    return 0;
}

int loop_utama(SDL_Event *e, struct Windowku *mwindow){
struct tabku *xtab;
struct tombolku *tombol;
    xtab=mwindow->ctab;
    switch (e->type){
        case SDL_KEYDOWN:{
            xtab=mwindow->ctab;
            tombol=xtab->tombol_aktif;
            if(tombol!=0){
                switch(tombol->jenis){
                    case TB_TULISAN:{
                        int tkey;
                        tkey=e->key.keysym.sym;
                        if((tkey>='a')&&(tkey<='z')){
                            ubah_tulisan(tombol, tkey, e->key.keysym.mod);
                            susun_tulisan(mwindow, tombol);
                        }else if((tkey==SDLK_SLASH) || (tkey==SDLK_8)){
                            if((e->key.keysym.mod==1)||(e->key.keysym.mod==2)){
                                ubah_tulisan(tombol, tkey, e->key.keysym.mod);
                                susun_tulisan(mwindow, tombol);
                            }
                        }else if(tkey=='?' || tkey=='[' || tkey==']' || tkey=='*' || tkey ==SDLK_BACKSPACE){
                            ubah_tulisan(tombol, tkey, e->key.keysym.mod);
                            susun_tulisan(mwindow, tombol);
                        }else if(tkey==SDLK_RETURN){
                            cari_kata(mwindow, ID_CARI_SEMUA);
                            perbaharui_tombol(mwindow, mwindow->ctab, 1);
                        }
                        break;
                    }
                    case TB_PILIHAN:{
                        if(e->key.keysym.sym==SDLK_RETURN){
                            mwindow->status=0;
                        }else{
                            pindah_data(tombol, e->key.keysym.sym);
                            mwindow->waktu=SDL_GetTicks();
                        }
                        //susun_pilihan(mwindow, tombol, xtab);
                        break;
                    }
                    case TB_DAFTARKU:{
                        pindah_data(tombol, e->key.keysym.sym);
                        daftar_susun(mwindow, tombol);
                        mwindow->waktu=SDL_GetTicks();
                        twelka_atur_status(mwindow);
                        break;
                    }
                    default:
                        break;
                }
            }
        }
        break;
        case SDL_KEYUP:{
            xtab=mwindow->ctab;
            tombol=xtab->tombol_aktif;
            if(tombol!=0){
                switch(tombol->jenis){
                    case TB_TULISAN:
                        if(tombol->id==ID_KATA_KAMUS){
                        struct dataku *data, *batas;
                        int perbandingan, i;
                        char s[256];
                            str_salin(s, tombol->tulisan);
                            tombol=dapatkan_tombol(mwindow->ctab, ID_DAFTAR);
                            if(tombol!=0){
                                batas=&tombol->batas_pertama;
                                hurufbesar(s);
                                if(batas!=0){
                                    i=1;
                                    data=batas->berikutnya;
                                    while(data!=batas){
                                        perbandingan=str_bandingkan(s, data->teks[tombol->kolom_utama].isi);
                                        if(perbandingan>0){
                                            tombol->atas_aktif=data;
                                            tombol->pilihan=data;
                                            tombol->pos=i;
                                            break;
                                        }
                                        data=data->berikutnya;
                                        i++;
                                    }
                                }
                            }
                        }
                        break;
                }
            }
        }
        break;
        case SDL_MOUSEWHEEL:
            xtab=mwindow->ctab;
            if(xtab->tombol_aktif!=0){
                tombol=xtab->tombol_aktif;
                if((tombol->jenis==TB_DAFTARKU)||(tombol->jenis==TB_PILIHAN)){
                    if(e->wheel.y>0){
                        pindah_data(tombol, SDLK_UP);
                    }else if(e->wheel.y<0){
                        pindah_data(tombol, SDLK_DOWN);
                    }
                }
                if(tombol->jenis==TB_DAFTARKU){
                    daftar_susun(mwindow, tombol);
                    twelka_atur_status(mwindow);
                }else if(tombol->jenis==TB_PILIHAN){
                    susun_pilihan(mwindow, tombol);
                }
            }
            break;
        case SDL_MOUSEMOTION:
            if(xtab==0)xtab=mwindow->ctab;
            mouse_bergerak(mwindow, xtab, e->motion.x, e->motion.y);
            break;
        case SDL_MOUSEBUTTONDOWN:
            if(xtab==0)xtab=mwindow->ctab;
            mouse_ditekan(mwindow, xtab, e->button.x, e->button.y, e->button.button);
            break;
        case SDL_MOUSEBUTTONUP:
            if(xtab==0)xtab=mwindow->ctab;
            mouse_dilepas(mwindow, xtab, e->button.x, e->button.y, e->button.button);
            break;
        case SDL_QUIT:
            if(mwindow->proses==0){
                mwindow->selesai=1;
            }
            break;
        default:
            break;
    }
    return 0;
}

int twelka_atur_status(struct Windowku *mwindow){
struct tombolku *tstatus, *tdaftar;
struct tabku *ctab;
char sstatus[40], tsnilai[20];
int nilai;
    ctab=mwindow->ctab;
    if(ctab!=0){
        tdaftar=dapatkan_tombol(ctab, ID_DAFTAR);
        tstatus=dapatkan_tombol(ctab, ID_STATUS);
        if(tdaftar!=0 && tstatus!=0){
            //posisi
            str_salin(sstatus, sposisi);
            snprintf(tsnilai, 10, "%d", tdaftar->pos);
            strcat(sstatus, tsnilai);
            ganti_isi_data(&tstatus->batas_pertama, 0, sstatus);
            //jdata
            str_salin(sstatus, sjkata);
            snprintf(tsnilai, 10, "%d", tdaftar->jdata);
            strcat(sstatus, tsnilai);
            ganti_isi_data(&tstatus->batas_pertama, 1, sstatus);
            //nilai
            if(ctab->jenis==1){
                str_salin(sstatus, snilai);
                if(tdaftar->pilihan!=&tdaftar->batas_pertama){
                    nilai=dapatkan_nilai(tdaftar->pilihan->teks[1].isi);
                }else{
                    nilai=0;
                }
                snprintf(tsnilai, 10, "%d", nilai);
                strcat(sstatus, tsnilai);
                ganti_isi_data(&tstatus->batas_pertama, 2, sstatus);
            }
            //
            susun_status(mwindow, tstatus);
        }
    }
    return 0;
}

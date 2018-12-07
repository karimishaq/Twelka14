#include "main.h"

int mouse_dilepas(struct Windowku *mwindow, struct tabku *xtab, int x, int y, int klik){
struct tombolku *tombol;
int i=0;
int k;
    if((xtab!=0) && (mwindow->status!=MENU_DITAMPILKAN) && (mwindow->status!=DAFTAR_SCROLLBAR)){
        mwindow->tombol_ditekan=0;
        tombol=tombol_yang_dilewati(xtab, x, y);
        if(tombol==0){
            xtab=mwindow->ctab;
            tombol=tombol_yang_dilewati(xtab, x, y);
        }
        if(klik==SDL_BUTTON_LEFT){
            if(tombol==xtab->tombol_aktif && tombol!=0){
                tombol->perbaharui=1;
                perbaharui_tombol(mwindow, mwindow->ctab, 0);
                switch(tombol->jenis){
                    case TB_DAFTARKU:
                        if(x<(tombol->cx-LEBAR_SCROLLBAR)){
                            if((y>tombol->y+tombol->spesial)&&(tombol->y+(tombol->jtampil*TINGGI_BARIS_DAFTAR)>y)){
                            struct dataku *data, *batas;
                                data=tombol->pilihan;
                                batas=&tombol->batas_pertama;
                                while(data!=tombol->atas_aktif){
                                    if(data==batas){
                                        break;
                                    }
                                    data=data->sebelumnya;
                                    tombol->pos--;
                                }
                                y-=(tombol->y+tombol->spesial);
                                k=y/TINGGI_BARIS_DAFTAR;
                                while((i<k)&&(data!=batas)){
                                    data=data->berikutnya;
                                    i++;
                                }
                                if(data!=batas){
                                    tombol->pilihan=data;
                                }
                                tombol->pos+=i;
                            }
                        }
                        tombol->status=0;
                        daftar_susun(mwindow, tombol);
                        break;
                    case TB_TOMBOL_TEKAN:
                        if(mwindow->status==STATUS_AWAL){
                            aksi_klik_tombol(mwindow, tombol, x, y);
                            susun_tombol_tekan(mwindow, tombol, xtab);
                        }
                        break;
                    default:
                        break;
                }
            }
        }else if(klik==SDL_BUTTON_RIGHT){
            tombol=tombol_yang_dilewati(xtab, x, y);
            if(tombol!=0){
                if(tombol->jenis==TB_TULISAN){
                    xtab->tombol_aktif=tombol;
                    tampilkan_menu(mwindow, mwindow->menu_teks, tombol->x, tombol->cy);
                }else{
                    switch(tombol->id){
                        case ID_DAFTAR:
                            break;
                        default:
                            break;
                    }
                }
            }
        }
    }else{
        mwindow->menu_aktif=0;
        mwindow->status=0;
    }
    return 0;
}

int mouse_ditekan(struct Windowku *mwindow, struct tabku *xtab, int x, int y, int klik){
struct tombolku *tombol=0;
int i;
    if(xtab!=0){
        if(klik==SDL_BUTTON_LEFT){
            if(mwindow->status==STATUS_AWAL){
                tombol=tombol_yang_dilewati(xtab, x, y);
                if(tombol!=0){
                    tombol->perbaharui=1;
                    mwindow->tombol_ditekan=1;
                    if(tombol!=xtab->tombol_aktif){
                        xtab->tombol_aktif=tombol;
                    }
                }else{
                    xtab=mwindow->ctab;
                    tombol=tombol_yang_dilewati(xtab, x, y);
                    if(tombol!=0){
                        tombol->perbaharui=1;
                        mwindow->tombol_ditekan=1;
                        if(tombol!=xtab->tombol_aktif){
                            xtab->tombol_aktif=tombol;
                        }
                    }
                }
            }else if(mwindow->status==PILIHAN_DITAMPILKAN){
                mwindow->status=STATUS_AWAL;
            }
            switch(mwindow->status){
                case MENU_DITAMPILKAN:{
                    struct Menuku *mmenu;
                    int w, h;
                        mmenu=mwindow->menu_aktif;
                        if(mmenu!=0){
                            w=mmenu->x+mmenu->w;
                            h=mmenu->y+mmenu->h;
                            if((x>=mmenu->x && x<w)&&(y>=mmenu->y && y<h)){
                                if(mmenu->pilihan!=0){
                                    aksi_klik_menu(mwindow, mmenu->pilihan->id);
                                }
                            }
                        }
                    }
                    perbaharui_tombol(mwindow, mwindow->ctab, salah);
                    break;
                default:
                    if(tombol!=0){
                        switch(tombol->jenis){
                            case TB_TOMBOL_TEKAN:
                                break;
                            case TB_PILIHAN:
                                if(mwindow->status!=PILIHAN_DITAMPILKAN){
                                    mwindow->status=PILIHAN_DITAMPILKAN;
                                }
                                break;
                            case TB_DAFTARKU:
                                if(x>=(tombol->cx-LEBAR_SCROLLBAR)){
                                    if(y-tombol->y<20){
                                        tombol->status=DAFTAR_NAIK;
                                    }else if(tombol->cy-y<20){
                                        tombol->status=DAFTAR_TURUN;
                                    }else{
                                        i=y-tombol->y-20;
                                        if(i+20 < tombol->yscrollbar){
                                            tombol->status=DAFTAR_NAIK_HALAMAN;
                                        }else if(i+20 >= (tombol->yscrollbar+tombol->hscrollbar)){
                                            tombol->status=DAFTAR_TURUN_HALAMAN;
                                        }else{
                                            tombol->status=DAFTAR_SCROLLBAR;
                                        }
                                    }
                                }
                                break;
                            default:
                                break;
                        }
                    }
            }
        }
        perbaharui_tombol(mwindow, mwindow->ctab, 0);
    }
    return 0;
}

int mouse_bergerak(struct Windowku *mwindow, struct tabku *xtab, int x, int y){
struct tombolku *tombol;
    if(xtab!=0){
        switch(mwindow->status){
            case MENU_DITAMPILKAN:
                if(mwindow->menu_aktif!=0){
                int w, h;
                struct Menuku *mmenu, *cmenu, *batas;
                    mmenu=mwindow->menu_aktif;
                    if(mmenu->pilihan!=0){
                        mmenu=mmenu->pilihan;
                    }
                    while(mmenu!=0){
                        w=mmenu->x+mmenu->w;
                        h=mmenu->y+mmenu->h;
                        if((x>=mmenu->x)&&(x<w)){
                            if((y>=mmenu->y)&&(y<h)){
                                mwindow->menu_aktif=mmenu;
                                break;
                            }
                        }
                        mmenu=mmenu->ortu;
                    }
                    if(mmenu!=0){
                    int py;
                        mmenu->pilihan=0;
                        batas=mmenu->batas;
                        cmenu=batas->berikutnya;
                        py=mmenu->y+2;
                        while(cmenu!=batas){
                            if((y>=py)&&(y<=py+20)){
                                mmenu->pilihan=cmenu;
                                if(cmenu->batas->berikutnya!=cmenu->batas){
                                    cmenu->pilihan=0;
                                    cmenu->x=mmenu->x+mmenu->w;
                                    cmenu->y=py;
                                    gambar_menu(mwindow->huruf, cmenu);
                                }
                                break;
                            }
                            py+=20;
                            cmenu=cmenu->berikutnya;
                        }
                    }
                    gambar_menu(mwindow->huruf, mmenu);
                }
                break;
            case PILIHAN_DITAMPILKAN:
                tombol=xtab->tombol_aktif;
                if(tombol!=0){
                    if((x>=tombol->x)&&(x<tombol->cx)&&(y>tombol->cy)){
                    struct dataku *data, *batas;
                    int i=0;
                    int n=0;
                        data=tombol->atas_aktif;
                        batas=&tombol->batas_pertama;
                        n=(y-tombol->cy)/20;
                        if(n<tombol->jtampil){
                            while(i<n){
                                if(data==batas){
                                    break;
                                }
                                i++;
                                data=data->berikutnya;
                            }
                            if(data!=batas){
                                tombol->pilihan=data;
                            }
                        }
                    }
                }
                perbaharui_tombol(mwindow, mwindow->ctab, salah);
                break;
            case DAFTAR_SCROLLBAR:
                break;
            default:
                tombol=mwindow->tombol_dilewati;
                if(tombol!=0){
                    if(tombol->jenis==TB_DAFTARKU){
                        tombol->status=0;
                        tombol->perbaharui=1;
                    }else if(tombol->jenis!=TB_NAMA){
                        tombol->perbaharui=1;
                    }
                }

                tombol=tombol_yang_dilewati(xtab, x, y);
                if(tombol==0){
                    xtab=mwindow->ctab;
                    tombol=tombol_yang_dilewati(xtab, x, y);
                }
                if(tombol!=0){
                    if(tombol->jenis==TB_DAFTARKU){
                        if(x>=(tombol->cx-LEBAR_SCROLLBAR)){
                            if(y-tombol->y<20){
                                tombol->status=DAFTAR_KEDIP_NAIK;
                            }else if(tombol->cy-y<20){
                                tombol->status=DAFTAR_KEDIP_TURUN;
                            }
                        }
                        tombol->perbaharui=1;
                    }else if(tombol->jenis!=TB_NAMA){
                        tombol->perbaharui=1;
                    }
                }
                mwindow->tombol_dilewati=tombol;
                perbaharui_tombol(mwindow, mwindow->ctab, salah);
                break;
        }
    }
    return 0;
}

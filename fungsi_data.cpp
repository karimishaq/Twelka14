#include "main.h"

struct dataku *pindah_posisi(struct tombolku *tombol, int pos){
struct dataku *data, *batas;
int i;
    batas=&tombol->batas_pertama;
    data=batas->berikutnya;
    i=1;
    while(data!=batas){
        if(i==pos)break;
        data=data->berikutnya;
        i++;
    }
    if(data==batas){
        data=batas->sebelumnya;
        pos=tombol->jdata;
    }
    tombol->atas_aktif=data;
    tombol->pilihan=data;
    tombol->pos=pos;
    return data;
}

int ganti_isi_data(struct dataku* data, int pkolom, char* isi){
int panjang=0;
    panjang=strlen(isi);
    str_salin(data->teks[pkolom].isi, isi);
    return panjang;
}

int pindah_data(struct tombolku *tombol, int scode){
struct dataku *tdata, *batas;
int i;
    batas=&tombol->batas_pertama;
    if(batas==batas->berikutnya){
        return 0;
    }
    switch(scode){
        case SDLK_UP:
            if(tombol->pilihan->sebelumnya!=batas){
                if(tombol->pilihan==tombol->atas_aktif){
                    tombol->atas_aktif=tombol->atas_aktif->sebelumnya;
                }
                tombol->pilihan=tombol->pilihan->sebelumnya;
                tombol->pos--;
            }
            break;
        case SDLK_DOWN:
            tdata=tombol->pilihan->berikutnya;
            if(tdata!=batas){
                i=0;
                tombol->pilihan=tdata;
                //simpan data atas ke tdata
                tdata=tombol->atas_aktif;
                while((tdata!=tombol->pilihan)&&(tdata!=batas)){
                    i++;
                    tdata=tdata->berikutnya;
                }
                //jika data pilihan melewati data terbawah
                if(i>=tombol->jtampil){
                    //simpan data pilihan ke tdata & ganti data atas dengan data pilihan
                    tdata=tombol->pilihan;
                    tombol->atas_aktif=tdata;
                    //naikkan pilihan supaya pilihan asli tampil sebagai data terbawah
                    naikkan_halaman(tombol, batas, tombol->jtampil-1);
                    //kembalikan pilihan ke posisi semula;
                    tombol->pilihan=tdata;
                }
                tombol->pos++;
            }
            break;
        case SDLK_PAGEUP:
            if(tombol->pilihan->sebelumnya!=batas){
                if(tombol->pos>tombol->jtampil)pindah_posisi(tombol, tombol->pos-tombol->jtampil+1);
                else pindah_posisi(tombol, 1);
            }
            break;
        case SDLK_PAGEDOWN:
            if(tombol->pilihan->berikutnya!=batas){
                pindah_posisi(tombol, tombol->pos+tombol->jtampil-1);
                i=tombol->jtampil-1;
                tdata=tombol->pilihan;
                while(i>0){
                    tdata=tdata->sebelumnya;
                    if(tdata==batas){
                        tdata=tdata->berikutnya;
                        break;
                    };
                    i--;
                }
                tombol->atas_aktif=tdata;
            }
            break;
        case SDLK_END:
            if(tombol->pilihan!=batas->sebelumnya){
                tombol->atas_aktif=batas->sebelumnya;
                tombol->pilihan=tombol->atas_aktif;
                naikkan_halaman(tombol, batas, tombol->jtampil-1);
                tombol->bawah=tombol->atas_aktif;
                turunkan_halaman(tombol, batas, tombol->jtampil-1);
                tombol->pos=tombol->jdata;
            }
            break;
        case SDLK_HOME:
            if(tombol->pilihan!=batas->berikutnya){
                tombol->atas_aktif=batas->berikutnya;
                tombol->pilihan=tombol->atas_aktif;
                tombol->pos=1;
            }
            break;
        default:
            break;
    }
    return 0;
}

int naikkan_halaman(tombolku *tombol, struct dataku *batas, int langkah){
struct dataku *data;
int i=0;
    data=tombol->atas_aktif;
    while((data!=batas)&&(i<langkah)){
        data=data->sebelumnya;
        i++;
    }
    if(data==batas){
        data=batas->berikutnya;
        i--;
    }
    tombol->atas_aktif=data;
    tombol->pilihan=data;
    return i;
}

int turunkan_halaman(tombolku *tombol, struct dataku *batas, int langkah){
dataku *data;
int i=0;
    data=tombol->bawah;
    while((data!=batas)&&(i<langkah)){
        data=data->berikutnya;
        i++;
    }
    if(data==batas){
        data=batas->sebelumnya;
        i--;
    }
    tombol->atas_aktif=tombol->bawah;
    tombol->pilihan=data;
    return i;
}

int kembalikan_susunan_awal(struct tombolku *tombol, struct dataku *batas){
struct dataku *data, *sebelumnya;
int jdata=0;
    data=batas->asli_berikutnya;
    sebelumnya=batas;
    while(data!=batas){
        data->sebelumnya=sebelumnya;
        data->berikutnya=data->asli_berikutnya;
        sebelumnya=data;
        data=data->asli_berikutnya;
        jdata++;
    }
    batas->berikutnya=batas->asli_berikutnya;
    batas->sebelumnya=sebelumnya;
    tombol->pos=1;
    tombol->jdata=jdata;
    return 0;
}

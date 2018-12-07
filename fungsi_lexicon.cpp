#include "main.h"

int cari_palindrom(struct tombolku *tombol, int id_kolom){
struct dataku *data, *sebelumnya, *berikutnya, *batas_daftar;
int i, jdata, tengah, panjang, palindrom;
char *kata;
    jdata=0;
    batas_daftar=&tombol->batas_pertama;
    sebelumnya=batas_daftar;
    data=batas_daftar->berikutnya;
    while(data!=batas_daftar){
        berikutnya=data->berikutnya;
        i=0;
        palindrom=1;
        kata=data->teks[1].isi;
        panjang=data->teks[1].panjang;
        tengah=panjang/2;
        panjang--;
        while(i<tengah){
            if(kata[i]!=kata[panjang-i]){
                palindrom=0;
                break;
            }
            i++;
        }
        if(palindrom==1){
            sebelumnya->berikutnya=data;
            data->sebelumnya=sebelumnya;
            data->berikutnya=batas_daftar;
            batas_daftar->sebelumnya=data;
            sebelumnya=data;
            jdata++;
        }
        data=berikutnya;
    }
    sebelumnya->berikutnya=data;
    data->sebelumnya=sebelumnya;
    tombol->pos=1;
    tombol->jdata=jdata;
    tombol->atas_aktif=tombol->batas_pertama.berikutnya;
    tombol->pilihan=tombol->atas_aktif;
    return 0;
}

int cari_kata_unik(struct tombolku *tombol, int id_kolom){
struct dataku *data, *sebelumnya, *berikutnya, *batas_daftar;
int i, jdata, unik;
char kata[100], cdiubah;
    jdata=0;
    batas_daftar=&tombol->batas_pertama;
    sebelumnya=batas_daftar;
    data=batas_daftar->berikutnya;
    while(data!=batas_daftar){
        berikutnya=data->berikutnya;
        str_salin(kata, data->teks[1].isi);
        urut_huruf(kata);
        i=0;
        unik=1;
        cdiubah=0;
        while(kata[i]!=0){
            if(kata[i]!=cdiubah){
                cdiubah=kata[i];
            }else{
                unik=0;
                break;
            }
            i++;
        }
        if(unik==1){
            sebelumnya->berikutnya=data;
            data->sebelumnya=sebelumnya;
            data->berikutnya=batas_daftar;
            batas_daftar->sebelumnya=data;
            sebelumnya=data;
            jdata++;
        }
        data=berikutnya;
    }
    sebelumnya->berikutnya=data;
    data->sebelumnya=sebelumnya;
    tombol->pos=1;
    tombol->jdata=jdata;
    tombol->atas_aktif=tombol->batas_pertama.berikutnya;
    tombol->pilihan=tombol->atas_aktif;
    return 0;
}

int front_hook_words(struct tombolku *tombol){
struct dataku *tdata, *batas_daftar, *berikutnya, *sebelumnya;
int jdata=0;
    batas_daftar=&tombol->batas_pertama;
    tdata=batas_daftar->berikutnya;
    sebelumnya=batas_daftar;
    while(tdata!=batas_daftar){
        berikutnya=tdata->berikutnya;

        if(tdata->fhook!=0){
            sebelumnya->berikutnya=tdata;
            tdata->sebelumnya=sebelumnya;
            tdata->berikutnya=batas_daftar;
            batas_daftar->sebelumnya=tdata;
            sebelumnya=tdata;
            jdata++;
        }else{
            tdata->berikutnya=0;
        }
        tdata=berikutnya;
    }
    sebelumnya->berikutnya=tdata;
    tdata->sebelumnya=sebelumnya;
    tombol->pos=1;
    tombol->jdata=jdata;
    tombol->atas_aktif=tombol->batas_pertama.berikutnya;
    tombol->pilihan=tombol->atas_aktif;
    return 0;
}

int back_hook_words(struct tombolku * tombol){
struct dataku *data, *batas_daftar, *berikutnya, *sebelumnya;
int jdata=0;
    batas_daftar=&tombol->batas_pertama;
    data=batas_daftar->berikutnya;
    sebelumnya=batas_daftar;
    while(data!=batas_daftar){
        berikutnya=data->berikutnya;

        if(data->bhook!=0){
            sebelumnya->berikutnya=data;
            data->sebelumnya=sebelumnya;
            data->berikutnya=batas_daftar;
            batas_daftar->sebelumnya=data;
            sebelumnya=data;
            jdata++;
        }else{
            data->berikutnya=0;
        }
        data=berikutnya;
    }
    sebelumnya->berikutnya=data;
    data->sebelumnya=sebelumnya;
    tombol->pos=1;
    tombol->jdata=jdata;
    tombol->atas_aktif=tombol->batas_pertama.berikutnya;
    tombol->pilihan=tombol->atas_aktif;
    return 0;
}

int hook_words(struct tombolku *tombol){
struct dataku *data, *batas_daftar, *berikutnya, *sebelumnya;
int jdata=0;
    batas_daftar=&tombol->batas_pertama;
    data=batas_daftar->berikutnya;
    sebelumnya=batas_daftar;
    while(data!=batas_daftar){
        berikutnya=data->berikutnya;
        if(data->bhook!=0 || data->fhook!=0){
            sebelumnya->berikutnya=data;
            data->sebelumnya=sebelumnya;
            data->berikutnya=batas_daftar;
            batas_daftar->sebelumnya=data;
            sebelumnya=data;
            jdata++;
        }else{
            data->berikutnya=0;
        }
        data=berikutnya;
    }
    sebelumnya->berikutnya=data;
    data->sebelumnya=sebelumnya;
    tombol->pos=1;
    tombol->jdata=jdata;
    tombol->atas_aktif=tombol->batas_pertama.berikutnya;
    tombol->pilihan=tombol->atas_aktif;
    return 0;
}

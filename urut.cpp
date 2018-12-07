#include "main.h"

#define jkarakter 31


int urutkan_data(struct tombolku *daftar, int id_pengurutan, int id_kolom){
struct dataku *batas;
    if(daftar!=0){
        batas=&daftar->batas_pertama;
        //simpan sementara jumlah data ke batas->x_wcard
        switch(id_pengurutan){
            case IDURUT_ALFABET:
                batas->teks[id_kolom].x_wcard=daftar->jdata;
                urutkan_alfabet(batas, 0, id_kolom);
                break;
            case IDURUT_PANJANG:
                urutkan_panjang(batas, 1, 0, id_kolom);
                break;
            case IDURUT_NILAI:
                urutkan_nilai(batas, 1, 0, id_kolom);
                break;
            case IDURUT_MUNDUR_ALFABET:
                batas->teks[id_kolom].x_wcard=daftar->jdata;
                urutkan_mundur_alfabet(batas, 1, id_kolom);
                break;
            case IDURUT_MUNDUR_PANJANG:
                urutkan_panjang(batas, 1, 1, id_kolom);
                break;
            case IDURUT_BALIK:
                balikkan_susunan(batas);
                break;
            case IDM_SEMUA_KATA:
                kembalikan_susunan_awal(daftar, batas);
                break;
            default:
                break;
        }
        //set_batas_pertama
        daftar->pos=1;
        daftar->atas_aktif=batas->berikutnya;
        daftar->pilihan=daftar->atas_aktif;
    }
    return 0;
}

int urutkan_mundur_alfabet(struct dataku *batas, int posisi, int indeks){
struct dataku *data, *dt_berikutnya;
struct dataku tdata[jkarakter];
int data_diubah=0;
int i=0;
    //Pengurutan ini hanya untuk Huruf Alfabet
    if(batas->berikutnya->berikutnya!=batas){
        do{
            i=0;
            data_diubah=0;
            while(i<jkarakter){
                tdata[i].berikutnya=&tdata[i];
                tdata[i].sebelumnya=&tdata[i];
                tdata[i].teks[indeks].x_wcard=0;
                i++;
            }
            //kelompokkan berdasarkan huruf
            data=batas->berikutnya;
            while(data!=batas){
                dt_berikutnya=data->berikutnya;
                if(posisi<=data->teks[indeks].panjang){
                    i=data->teks[indeks].isi[data->teks[indeks].panjang-posisi];
                }else{
                    i=0;
                }
                //Abaikan semua selain huruf dan letakkan di belakang
                if((i>='A')&&(i<='Z')){
                    i=i-'A'+2;//'A' adalah karakter ascii ke 65;
                }else if((i>='a')&&(i<='z')){
                    i=i-'a'+2;//'A' adalah karakter ascii ke 97;
                }else if(i!=0){
                    if(i=='_'){
                        i=28;
                    }else if(i==' '){
                        i=29;
                    }else{
                        i=1;
                    }
                }
                //tdata[i] sebelumnya adalah data terakhir
                data->berikutnya=&tdata[i];
                data->sebelumnya=tdata[i].sebelumnya;
                tdata[i].sebelumnya->berikutnya=data;
                tdata[i].sebelumnya=data;
                tdata[i].teks[indeks].x_wcard++;
                data_diubah=i;
                data=dt_berikutnya;
            }
            if(tdata[data_diubah].teks[indeks].x_wcard==batas->teks[indeks].x_wcard){
                tdata[data_diubah].sebelumnya->berikutnya=batas;
                tdata[data_diubah].berikutnya->sebelumnya=batas;
            }else{
                break;
            }
            posisi++;
        }while(data_diubah!=0);
        //kosongkan daftar
        batas->berikutnya=batas;
        batas->sebelumnya=batas;
        //jika sudah di ujung kata jangan melakukan rekursi
        if(tdata[0].berikutnya!=&tdata[0]){
            tdata[0].sebelumnya->berikutnya=batas;
            tdata[0].berikutnya->sebelumnya=batas->sebelumnya;
            batas->sebelumnya->berikutnya=tdata[0].berikutnya;
            batas->sebelumnya=tdata[0].sebelumnya;
        }
        //lakukan rekursi untuk kata-kata yang belum mencapai ujung
        i=1;
        while(i<jkarakter){
            if(tdata[i].berikutnya!=&tdata[i]){
                urutkan_mundur_alfabet(&tdata[i], posisi, indeks);
                //tdata[i] sebelumnya adalah data terakhir
                tdata[i].sebelumnya->berikutnya=batas;
                tdata[i].berikutnya->sebelumnya=batas->sebelumnya;
                batas->sebelumnya->berikutnya=tdata[i].berikutnya;
                batas->sebelumnya=tdata[i].sebelumnya;
            }
            i++;
        }
    }
    return 0;
}

int urutkan_alfabet(struct dataku *batas, int posisi, int indeks){
struct dataku *data, *dt_berikutnya;
struct dataku tdata[jkarakter];
int data_diubah=0;
int i=0;
    //Pengurutan ini hanya untuk Huruf Alfabet
    if(batas->berikutnya->berikutnya!=batas){
        do{
            i=0;
            data_diubah=0;
            while(i<jkarakter){
                tdata[i].berikutnya=&tdata[i];
                tdata[i].sebelumnya=&tdata[i];
                tdata[i].teks[indeks].x_wcard=0;
                i++;
            }
            //kelompokkan berdasarkan huruf
            data=batas->berikutnya;
            while(data!=batas){
                dt_berikutnya=data->berikutnya;
                i=data->teks[indeks].isi[posisi];
                //Abaikan semua selain huruf dan letakkan di belakang
                if((i>='A')&&(i<='Z')){
                    i=i-'A'+2;//'A' adalah karakter ascii ke 65;
                }else if((i>='a')&&(i<='z')){
                    i=i-'a'+2;//'A' adalah karakter ascii ke 97;
                }else if(i!=0){
                    if(i=='_'){
                        i=28;
                    }else if(i==' '){
                        i=29;
                    }else{
                        i=1;
                    }
                }
                //tdata[i] sebelumnya adalah data terakhir
                data->berikutnya=&tdata[i];
                data->sebelumnya=tdata[i].sebelumnya;
                tdata[i].sebelumnya->berikutnya=data;
                tdata[i].sebelumnya=data;
                tdata[i].teks[indeks].x_wcard++;
                data_diubah=i;
                data=dt_berikutnya;
            }
            if(tdata[data_diubah].teks[indeks].x_wcard==batas->teks[indeks].x_wcard){
                tdata[data_diubah].sebelumnya->berikutnya=batas;
                tdata[data_diubah].berikutnya->sebelumnya=batas;
            }else{
                break;
            }
            posisi++;
        }while(data_diubah!=0);
        //kosongkan daftar
        batas->berikutnya=batas;
        batas->sebelumnya=batas;
        //jika sudah di ujung kata jangan melakukan rekursi
        if(tdata[0].berikutnya!=&tdata[0]){
            tdata[0].sebelumnya->berikutnya=batas;
            tdata[0].berikutnya->sebelumnya=batas->sebelumnya;
            batas->sebelumnya->berikutnya=tdata[0].berikutnya;
            batas->sebelumnya=tdata[0].sebelumnya;
        }
        //lakukan rekursi untuk kata-kata yang belum mencapai ujung
        i=1;
        while(i<jkarakter){
            if(tdata[i].berikutnya!=&tdata[i]){
                urutkan_alfabet(&tdata[i], posisi, indeks);
                //tdata[i].sebelumnya adalah data terakhir
                //tdata[i].berikutnya adalah data pertama
                tdata[i].sebelumnya->berikutnya=batas;
                tdata[i].berikutnya->sebelumnya=batas->sebelumnya;
                batas->sebelumnya->berikutnya=tdata[i].berikutnya;
                batas->sebelumnya=tdata[i].sebelumnya;
            }
            i++;
        }
    }
    return 0;
}

int balikkan_susunan(struct dataku *batas){
struct dataku *data, *sebelumnya, *berikutnya;
    sebelumnya=batas;
    data=batas->berikutnya;
    batas->sebelumnya=data;
    while(data!=batas){
        berikutnya=data->berikutnya;
        data->sebelumnya=berikutnya;
        data->berikutnya=sebelumnya;
        sebelumnya=data;
        data=berikutnya;
    }
    batas->berikutnya=sebelumnya;
    return 0;
}

int urutkan_panjang(struct dataku *batas, char lanjut, char terbalik, int indeks){
struct dataku *data, *dt_berikutnya;
struct dataku tdata[100];
int i=0;
    //Pengurutan ini hanya untuk panjang
    if(batas->berikutnya->berikutnya!=batas){
        while(i<100){
            tdata[i].berikutnya=&tdata[i];
            tdata[i].sebelumnya=&tdata[i];
            tdata[i].teks[indeks].x_wcard=0;
            i++;
        }
        //kelompokkan berdasarkan huruf
        data=batas->berikutnya;
        while(data!=batas){
            dt_berikutnya=data->berikutnya;
            i=data->teks[indeks].panjang;
            //tdata[i] sebelumnya adalah data terakhir
            data->berikutnya=&tdata[i];
            data->sebelumnya=tdata[i].sebelumnya;
            tdata[i].sebelumnya->berikutnya=data;
            tdata[i].sebelumnya=data;
            tdata[i].teks[indeks].x_wcard++;
            data=dt_berikutnya;
        }
        //kosongkan daftar
        batas->berikutnya=batas;
        batas->sebelumnya=batas;
        //lakukan rekursi untuk kata-kata yang belum mencapai ujung
        i=0;
        while(i<100){
            if(tdata[i].berikutnya!=&tdata[i]){
                if(lanjut!=0){
                    if(terbalik==0){
                        urutkan_alfabet(&tdata[i], 0, indeks);
                    }else{
                        urutkan_mundur_alfabet(&tdata[i], 1, indeks);
                    }
                }
                //tdata[i] sebelumnya adalah data terakhir
                tdata[i].sebelumnya->berikutnya=batas;
                tdata[i].berikutnya->sebelumnya=batas->sebelumnya;
                batas->sebelumnya->berikutnya=tdata[i].berikutnya;
                batas->sebelumnya=tdata[i].sebelumnya;
            }
            i++;
        }
    }
    return 0;
}

int urutkan_nilai(struct dataku *batas, char lanjut, char terbalik, int indeks){
struct dataku *data, *dt_berikutnya;
struct dataku tdata[100];
int i=0;
    //Pengurutan ini hanya untuk panjang
    if(batas->berikutnya->berikutnya!=batas){
        while(i<100){
            tdata[i].berikutnya=&tdata[i];
            tdata[i].sebelumnya=&tdata[i];
            tdata[i].teks[indeks].x_wcard=0;
            i++;
        }
        //kelompokkan berdasarkan huruf
        data=batas->berikutnya;
        while(data!=batas){
            dt_berikutnya=data->berikutnya;
            i=dapatkan_nilai(data->teks[indeks].isi);
            //tdata[i] sebelumnya adalah data terakhir
            data->berikutnya=&tdata[i];
            data->sebelumnya=tdata[i].sebelumnya;
            tdata[i].sebelumnya->berikutnya=data;
            tdata[i].sebelumnya=data;
            tdata[i].teks[indeks].x_wcard++;
            data=dt_berikutnya;
        }
        //kosongkan daftar
        batas->berikutnya=batas;
        batas->sebelumnya=batas;
        //lakukan rekursi untuk kata-kata yang belum mencapai ujung
        i=0;
        while(i<100){
            if(tdata[i].berikutnya!=&tdata[i]){
                if(lanjut!=0){
                    if(terbalik==0){
                        urutkan_alfabet(&tdata[i], 0, indeks);
                    }else{
                        urutkan_mundur_alfabet(&tdata[i], 1, indeks);
                    }
                }
                //tdata[i] sebelumnya adalah data terakhir
                tdata[i].sebelumnya->berikutnya=batas;
                tdata[i].berikutnya->sebelumnya=batas->sebelumnya;
                batas->sebelumnya->berikutnya=tdata[i].berikutnya;
                batas->sebelumnya=tdata[i].sebelumnya;
            }
            i++;
        }
    }
    return 0;
}

int urut_huruf(char *s){
int x=0;
int i, x2, pj;
char churuf;
    pj=str_panjang(s);
    x=pj-1;
    while(x>0){
        i=x;
        x2=x;
        churuf=0;
        while(i>=0){
            if(s[i]>churuf){
                x=x2;
                churuf=s[i];
            }
            if(s[i]==churuf){
                s[i]=s[x];
                s[x]=churuf;
                x--;
            }
            i--;
        }
    }
    return 0;
}

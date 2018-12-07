#include "main.h"

const int tabel_nilai[26]={1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int bukadaftarkata(struct tombolku *daftar, char *namafile){
FILE *f=0;
char s[100];
struct dataku *data, *batas;
int i, n, x;
    batas=&daftar->batas_pertama;
    f=fopen(namafile, "r");
    n=300000;
    i=0;
    if(f){
        while(i<n){
            if(feof(f))break;
            s[0]=0;
            if(fgets(s, 100, f)){
                if(s[0]!=0){
                    hurufbesar(s);
                    x=str_panjang(s)-1;
                    if(s[x]==10 || s[x]==13){
                        s[x]=0;
                    }else{
                        x++;
                        i=n;
                    }
                    data=tambah_data_daftar(daftar);
                    data->teks[1].panjang=ganti_isi_data(data, 1, s);
                }else{
                    break;
                }
            }
            i++;
        }
    }
    batas=&daftar->batas_pertama;
    data=batas->berikutnya;
    daftar->atas_aktif=data;
    daftar->pilihan=data;
    daftar->pos=1;
    fclose(f);
    isi_hook_letter(daftar);
    return 0;
}

int isi_hook_letter(struct tombolku *daftar){
struct dataku *data1, *data2, *batas;
char *kata1, *kata2;
char hook_letter[50];
int i, j, panjang, x;
    urutkan_data(daftar, IDURUT_MUNDUR_PANJANG, 1);
    batas=&daftar->batas_pertama;

    data1=batas->berikutnya;
    data2=data1->berikutnya;
    while((data1!=batas) && (data2!=batas)){
        x=0;
        hook_letter[0]=0;
        kata1=data1->teks[1].isi;
        panjang=data1->teks[1].panjang+1;
        while(data2!=batas){
            if(data2->teks[1].panjang==panjang){
                kata2=data2->teks[1].isi;
                i=data1->teks[1].panjang-1;
                j=data2->teks[1].panjang-1;
                while(i>0){
                    if(kata1[i]==kata2[j]){
                        i--;
                        j--;
                    }else{
                        break;
                    }
                }
                if(kata1[i]==kata2[j]){
                    data2->fhook=1;
                    hook_letter[x]=kata2[0];
                    x++;
                }else if(kata2[j]>kata1[i]){
                    break;
                }
            }else if(data2->teks[1].panjang>panjang){
                break;
            }
            data2=data2->berikutnya;
        }
        hook_letter[x]=0;
        ganti_isi_data(data1, 0, hook_letter);
        //
        data1=data1->berikutnya;
    }

    urutkan_data(daftar, IDURUT_PANJANG, 1);
    batas=&daftar->batas_pertama;

    data1=batas->berikutnya;
    data2=data1->berikutnya;
    while(data1!=batas){
        x=0;
        hook_letter[0]=0;
        kata1=data1->teks[1].isi;
        panjang=data1->teks[1].panjang+1;
        while(data2!=batas){
            if(data2->teks[1].panjang==panjang){
                i=0;
                kata2=data2->teks[1].isi;
                while(kata1[i]==kata2[i]){
                    i++;
                }
                if(kata1[i]==0){
                    data2->bhook=1;
                    hook_letter[x]=kata2[i];
                    x++;
                }else if(kata2[i]>kata1[i]){
                    break;
                }
            }else if(data2->teks[1].panjang>panjang){
                break;
            }
            data2=data2->berikutnya;
        }
        hook_letter[x]=0;
        ganti_isi_data(data1, 2, hook_letter);
        //
        data1=data1->berikutnya;
    }

    return 0;
}

int dapatkan_nilai(char *kata){
int churuf;
int nilai=0;
int i;
    if(kata!=0){
    int panjang;
        i=0;
        panjang=str_panjang(kata);
        while(i<panjang){
            churuf=kata[i];
            if(churuf>='A' && churuf<='Z'){
                churuf-='A';
            }else if(churuf>='z' && churuf<='z'){
                churuf-='a';
            }
            nilai+=tabel_nilai[churuf];
            i++;
        }
    }else{
        nilai=0;
    }
    return nilai;
}

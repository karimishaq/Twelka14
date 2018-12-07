#include "main.h"

int bandingkan_huruf(char c, char *ckata){
int sama=1;
int i=0;
    while(ckata[i]!=0){
        if(ckata[i]!=c){
            sama=0;
        }else{
            sama=1;
            break;
        }
        i++;
    }
    return sama;
}

int bandingkan_anagram(struct dataku *batas_cari, char churuf){
int sama=0;
struct dataku *tanagram;
    tanagram=batas_cari->berikutnya;
    while(tanagram!=batas_cari){
        if(tanagram->teks[1].panjang==0){
            sama=bandingkan_huruf(churuf, tanagram->teks[1].isi);
            if(sama!=0){
                tanagram->teks[1].panjang=1;
                break;
            }
        }
        tanagram=tanagram->berikutnya;
    }
    return sama;
}

int cari_includes_letters(struct dataku *batas_daftar, struct dataku *batas_cari, int tmin, int tmax, int jenis){
struct dataku *sebelumnya, *berikutnya, *tdata, *cdata;
char *tkata;
int i, tambahan;
int sama=0;
int jdata=0;
    sebelumnya=batas_daftar;
    if(jenis==ID_CARI_DALAM_HASIL){
        tdata=batas_daftar->berikutnya;
    }else{
        tdata=batas_daftar->asli_berikutnya;
    }
    batas_daftar->sebelumnya=batas_daftar;
    batas_daftar->berikutnya=batas_daftar;
    while(tdata!=batas_daftar){
        if(jenis==ID_CARI_DALAM_HASIL){
            berikutnya=tdata->berikutnya;
        }else{
            berikutnya=tdata->asli_berikutnya;
        }

        if((jenis==ID_CARI_DAN_GABUNGKAN)&&(tdata->sebelumnya!=0)){
            sama=1;
        }else{
            i=0;
            tambahan=0;
            tkata=tdata->teks[1].isi;
            batas_cari->teks[1].x_wcard=0;
            batas_cari->teks[1].panjang=1;
            while(tkata[i]!=0){
                sama=0;
                cdata=batas_cari->berikutnya;
                while(cdata!=batas_cari){
                    if(cdata->teks[1].isi[0]!=0){
                        if(bandingkan_huruf(tkata[i], cdata->teks[1].isi)!=0){
                            sama=1;
                            break;
                        }
                    }
                    cdata=cdata->berikutnya;
                }
                if(sama==0){
                    if(tambahan<tmax){
                        tambahan++;
                        sama=1;
                    }else{
                        break;
                    }
                }
                i++;
            }
            if(tambahan<tmin){
                sama=0;
            }
        }

        if(sama==1){
            sebelumnya->berikutnya=tdata;
            tdata->sebelumnya=sebelumnya;
            tdata->berikutnya=batas_daftar;
            batas_daftar->sebelumnya=tdata;
            sebelumnya=tdata;
            jdata++;
        }else{
            tdata->sebelumnya=0;
        }

        tdata=berikutnya;
    }
    sebelumnya->berikutnya=tdata;
    tdata->sebelumnya=sebelumnya;
    return jdata;
}

int cari_subpola(struct dataku *batas_daftar, struct dataku *batas_cari, int tmin, int tmax, int jenis){
struct dataku *sebelumnya, *berikutnya, *tdata, *cdata;
char *tkata;
int i, sama, jsama, tambahan;
int jdata=0;
    sebelumnya=batas_daftar;
    if(jenis==ID_CARI_DALAM_HASIL){
        tdata=batas_daftar->berikutnya;
    }else{
        tdata=batas_daftar->asli_berikutnya;
    }
    batas_daftar->sebelumnya=batas_daftar;
    batas_daftar->berikutnya=batas_daftar;
    while(tdata!=batas_daftar){
        if(jenis==ID_CARI_DALAM_HASIL){
            berikutnya=tdata->berikutnya;
        }else{
            berikutnya=tdata->asli_berikutnya;
        }

        if((jenis==ID_CARI_DAN_GABUNGKAN)&&(tdata->sebelumnya!=0)){
            sama=1;
        }else{
            i=0;
            tambahan=0;
            sama=1;
            jsama=0;
            tkata=tdata->teks[1].isi;
            cdata=batas_cari->berikutnya;
            while((cdata!=batas_cari)&&(tkata[i]!=0)){
                sama=bandingkan_huruf(tkata[i], cdata->teks[1].isi);
                cdata=cdata->berikutnya;
                if(sama!=0){
                    jsama++;
                    i++;
                }
            }

            if((tkata[i]!=0)|| (jsama==0) ||(tambahan<tmin)){
                sama=0;
            }
        }

        if(sama==1){
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
    return jdata;
}

int cari_subanagram(struct dataku *batas_daftar, struct dataku *batas_cari, int tmin, int tmax, int jenis){
struct dataku *sebelumnya, *berikutnya, *tdata, *cdata;
char *tkata;
int i, sama, jsama, tambahan;
int jdata=0;
    sebelumnya=batas_daftar;
    if(jenis==ID_CARI_DALAM_HASIL){
        tdata=batas_daftar->berikutnya;
    }else{
        tdata=batas_daftar->asli_berikutnya;
    }
    batas_daftar->sebelumnya=batas_daftar;
    batas_daftar->berikutnya=batas_daftar;
    while(tdata!=batas_daftar){
        if(jenis==ID_CARI_DALAM_HASIL){
            berikutnya=tdata->berikutnya;
        }else{
            berikutnya=tdata->asli_berikutnya;
        }
        if((jenis==ID_CARI_DAN_GABUNGKAN)&&(tdata->sebelumnya!=0)){
            sama=1;
        }else{
            cdata=batas_cari->berikutnya;
            while(cdata!=batas_cari){
                if(cdata->teks[1].x_wcard==0){
                    cdata->teks[1].panjang=0;
                }else{
                    cdata->teks[1].panjang=1;
                }
                cdata=cdata->berikutnya;
            }
            i=0;
            tambahan=0;
            sama=1;
            jsama=0;
            tkata=tdata->teks[1].isi;
            batas_cari->teks[1].x_wcard=0;
            batas_cari->teks[1].panjang=1;
            cdata=batas_cari->berikutnya;
            while(tkata[i]!=0){
                sama=0;
                if(cdata!=batas_cari){
                    sama=bandingkan_anagram(batas_cari, tkata[i]);
                }

                if(sama!=0){
                    jsama++;
                    cdata=cdata->berikutnya;
                }else{
                    if(tambahan<tmax){
                        sama=1;
                        tambahan++;
                    }else{
                        break;
                    }
                }
                i++;
            }

            if(tambahan<tmin || jsama==0){
                sama=0;
            }
        }

        if(sama==1){
            sebelumnya->berikutnya=tdata;
            tdata->sebelumnya=sebelumnya;
            tdata->berikutnya=batas_daftar;
            batas_daftar->sebelumnya=tdata;
            sebelumnya=tdata;
            jdata++;
        }else{
            tdata->sebelumnya=0;
        }

        tdata=berikutnya;
    }
    sebelumnya->berikutnya=tdata;
    tdata->sebelumnya=sebelumnya;
    return jdata;
}

int cari_pola(struct dataku *batas_daftar, struct dataku *batas_cari, int tmin, int tmax, int jenis){
struct dataku *sebelumnya, *berikutnya, *tdata, *cdata, *wcard;
char *tkata;
int i, j, sama, tambahan;
int jdata=0;
    sebelumnya=batas_daftar;
    if(jenis==ID_CARI_DALAM_HASIL){
        tdata=batas_daftar->berikutnya;
    }else{
        tdata=batas_daftar->asli_berikutnya;
    }
    batas_daftar->sebelumnya=batas_daftar;
    batas_daftar->berikutnya=batas_daftar;
    while(tdata!=batas_daftar){
        if(jenis==ID_CARI_DALAM_HASIL){
            berikutnya=tdata->berikutnya;
        }else{
            berikutnya=tdata->asli_berikutnya;
        }
        if((jenis==ID_CARI_DAN_GABUNGKAN)&&(tdata->sebelumnya!=0)){
            sama=1;
        }else{
            sama=0;
            if(tdata->teks[1].panjang>=(batas_cari->teks[1].panjang+tmin)){
                i=0;
                tambahan=0;
                wcard=0;
                tkata=tdata->teks[1].isi;
                batas_cari->teks[1].x_wcard=0;
                batas_cari->teks[1].panjang=1;
                cdata=batas_cari->berikutnya;
                while(tkata[i]!=0){
                    if(cdata->teks[1].x_wcard==0){
                        if(wcard!=0){
                            j=i;
                            sama=1;
                            cdata=wcard;
                            while((tkata[j]!=0)&&(cdata!=batas_cari)){
                                if((bandingkan_huruf(tkata[j], cdata->teks[1].isi)==0)||(cdata->teks[1].x_wcard!=0)){
                                    break;
                                }
                                cdata=cdata->berikutnya;
                                j++;
                            }

                            if(tkata[j]==0){
                                i=j;
                                break;
                            }else if(cdata->teks[1].x_wcard==0){
                                i++;
                            }else{
                                i=j;
                            }
                        }else{
                            sama=0;
                            if(cdata!=batas_cari){
                                sama=bandingkan_huruf(tkata[i], cdata->teks[1].isi);
                            }

                            if(sama!=0){
                                cdata=cdata->berikutnya;
                            }else{
                                if(tambahan<tmax){
                                    sama=1;
                                    tambahan++;
                                }else{
                                    break;
                                }
                            }
                            i++;
                        }
                    }else{
                        cdata=cdata->berikutnya;
                        wcard=cdata;
                        if(cdata==batas_cari){
                            sama=1;
                            break;
                        }else{
                            sama=0;
                        }
                    }
                }

                while(cdata!=batas_cari){
                    if(cdata->teks[1].x_wcard==0){
                        break;
                    }else{
                        sama=1;
                    }
                    cdata=cdata->berikutnya;
                }

                if((cdata!=batas_cari)||(tambahan<tmin)){
                    sama=0;
                }
            }
        }

        if(sama==1){
            sebelumnya->berikutnya=tdata;
            tdata->sebelumnya=sebelumnya;
            tdata->berikutnya=batas_daftar;
            batas_daftar->sebelumnya=tdata;
            sebelumnya=tdata;
            jdata++;
        }else{
            tdata->sebelumnya=0;
        }

        tdata=berikutnya;
    }
    sebelumnya->berikutnya=tdata;
    tdata->sebelumnya=sebelumnya;
    return jdata;
}

int cari_perbedaan(struct dataku *batas_daftar, struct dataku *batas_cari, int tmin, int tmax, int jenis){
struct dataku *sebelumnya, *berikutnya, *tdata, *cdata, *wcard;
char *tkata;
int i, j, sama, beda;
int jdata=0;
    sebelumnya=batas_daftar;
    if(jenis==ID_CARI_DALAM_HASIL){
        tdata=batas_daftar->berikutnya;
    }else{
        tdata=batas_daftar->asli_berikutnya;
    }
    batas_daftar->sebelumnya=batas_daftar;
    batas_daftar->berikutnya=batas_daftar;
    while(tdata!=batas_daftar){
        if(jenis==ID_CARI_DALAM_HASIL){
            berikutnya=tdata->berikutnya;
        }else{
            berikutnya=tdata->asli_berikutnya;
        }
        if((jenis==ID_CARI_DAN_GABUNGKAN)&&(tdata->sebelumnya!=0)){
            sama=1;
        }else{
            sama=0;
            if(tdata->teks[1].panjang>=(batas_cari->teks[1].panjang+tmin)){
                i=0;
                beda=0;
                wcard=0;
                tkata=tdata->teks[1].isi;
                batas_cari->teks[1].x_wcard=0;
                cdata=batas_cari->berikutnya;
                while(tkata[i]!=0){
                    if(cdata->teks[1].x_wcard==0){
                        if(wcard!=0){
                            j=i;
                            sama=1;
                            cdata=wcard;
                            while((tkata[j]!=0)&&(cdata!=batas_cari)){
                                if((bandingkan_huruf(tkata[j], cdata->teks[1].isi)==0)||(cdata->teks[1].x_wcard!=0)){
                                    break;
                                }
                                cdata=cdata->berikutnya;
                                j++;
                            }

                            if(tkata[j]==0){
                                i=j;
                                break;
                            }else if(cdata->teks[1].x_wcard==0){
                                i++;
                            }else{
                                i=j;
                            }
                        }else{
                            if(cdata!=batas_cari){
                                sama=bandingkan_huruf(tkata[i], cdata->teks[1].isi);
                            }else{
                                sama=0;
                            }
                            if(sama!=0){
                                cdata=cdata->berikutnya;
                            }else{
                                if(beda<tmax){
                                    if(cdata!=batas_cari){
                                        cdata=cdata->berikutnya;
                                    }
                                    beda++;
                                    sama=1;
                                }else{
                                    break;
                                }
                            }
                            i++;
                        }
                    }else{
                        cdata=cdata->berikutnya;
                        wcard=cdata;
                        if(cdata==batas_cari){
                            sama=1;
                            break;
                        }else{
                            sama=0;
                        }
                    }
                }

                while(cdata!=batas_cari){
                    if(cdata->teks[1].x_wcard==0){
                        break;
                    }else{
                        sama=1;
                    }
                    cdata=cdata->berikutnya;
                }

                if((cdata!=batas_cari)||(beda<tmin)){
                    sama=0;
                }
            }
        }
        if(sama==1){
            sebelumnya->berikutnya=tdata;
            tdata->sebelumnya=sebelumnya;
            tdata->berikutnya=batas_daftar;
            batas_daftar->sebelumnya=tdata;
            sebelumnya=tdata;
            jdata++;
        }else{
            tdata->sebelumnya=0;
        }

        tdata=berikutnya;
    }
    sebelumnya->berikutnya=tdata;
    tdata->sebelumnya=sebelumnya;
    return jdata;
}

int cari_anagram(struct dataku *batas_daftar, struct dataku *batas_cari, int tmin, int tmax, int jenis){
struct dataku *sebelumnya, *berikutnya, *tdata, *cdata;
char *tkata;
int i, tambahan;
int sama=0;
int jdata=0;
    sebelumnya=batas_daftar;
    if(jenis==ID_CARI_DALAM_HASIL){
        tdata=batas_daftar->berikutnya;
    }else{
        tdata=batas_daftar->asli_berikutnya;
    }
    batas_daftar->sebelumnya=batas_daftar;
    batas_daftar->berikutnya=batas_daftar;
    while(tdata!=batas_daftar){
        if(jenis==ID_CARI_DALAM_HASIL){
            berikutnya=tdata->berikutnya;
        }else{
            berikutnya=tdata->asli_berikutnya;
        }

        if((jenis==ID_CARI_DAN_GABUNGKAN)&&(tdata->sebelumnya!=0)){
            sama=1;
        }else{
            sama=0;
            if(tdata->teks[1].panjang>=(batas_cari->teks[1].panjang+tmin)){
                cdata=batas_cari->berikutnya;
                while(cdata!=batas_cari){
                    if(cdata->teks[1].x_wcard==0){
                        cdata->teks[1].panjang=0;
                    }else{
                        cdata->teks[1].panjang=1;
                    }
                    cdata=cdata->berikutnya;
                }
                i=0;
                tambahan=0;
                tkata=tdata->teks[1].isi;
                batas_cari->teks[1].x_wcard=0;
                batas_cari->teks[1].panjang=1;
                cdata=batas_cari->berikutnya;
                while(tkata[i]!=0){
                    sama=0;
                    if(cdata!=batas_cari){
                        sama=bandingkan_anagram(batas_cari, tkata[i]);
                    }

                    if(sama!=0){
                        cdata=cdata->berikutnya;
                    }else{
                        if(tambahan<tmax){
                            sama=1;
                            tambahan++;
                        }else{
                            break;
                        }
                    }
                    i++;
                }

                if((cdata!=batas_cari)||(tambahan<tmin)){
                    sama=0;
                }
            }
        }

        if(sama==1){
            sebelumnya->berikutnya=tdata;
            tdata->sebelumnya=sebelumnya;
            tdata->berikutnya=batas_daftar;
            batas_daftar->sebelumnya=tdata;
            sebelumnya=tdata;
            jdata++;
        }else{
            tdata->sebelumnya=0;
        }

        tdata=berikutnya;
    }
    sebelumnya->berikutnya=tdata;
    tdata->sebelumnya=sebelumnya;
    return jdata;
}

int cari_kata(struct Windowku *mwindow, int jenis){
struct tabku *xtab;
struct tombolku *tombol;
struct dataku xdata[256];
struct dataku *batas_kata, *batas_aktif, *data, *tdata;
char *ckata, tcari[256];
int i, j, n;
int jcari=0;
    //Set data pencarian
    for(i=0;i<255;i++){
        xdata[i].berikutnya=&xdata[i+1];
        xdata[i].asli_berikutnya=&xdata[i+1];
    }

    for(i=1;i<256;i++){
        xdata[i].sebelumnya=&xdata[i-1];
        xdata[i].teks[1].isi[0]=0;
        xdata[i].teks[1].panjang=0;
        xdata[i].teks[1].x_wcard=0;
        xdata[i].fhook=0;
        xdata[i].bhook=0;
    }

    batas_kata=&xdata[0];
    batas_kata->sebelumnya=&xdata[255];
    xdata[255].berikutnya=batas_kata;
    data=batas_kata;

    //Susun data pencarian
    mwindow->status=STATUS_MENUNGGU;
    xtab=mwindow->ctab;
    tombol=dapatkan_tombol(xtab, ID_KATA_KATA);
    jcari=dapatkan_posisi_pilihan(dapatkan_tombol(xtab, ID_JENIS_PENCARIAN));
    ckata=tombol->tulisan;

    i=0;
    n=0;
    if(jcari==IDCARI_POLA){
        while(ckata[i]!=0){
            data=data->berikutnya;
            data->teks[1].x_wcard=0;
            if(ckata[i]=='['){
                i++;
                j=0;
                while(ckata[i]!=']'){
                    if(ckata[i]==0){
                        i--;
                        break;
                    }
                    tcari[j]=ckata[i];
                    i++;
                    j++;
                }
                tcari[j]=0;
                n++;
                i++;
            }else if(ckata[i]=='?'){
                tcari[0]=0;
                n++;
                i++;
            }else if(ckata[i]=='*'){
                data->teks[1].x_wcard=1;
                tcari[0]=0;
                while(ckata[i]=='*'){
                    i++;
                }
            }else{
                tcari[0]=ckata[i];
                tcari[1]=0;
                n++;
                i++;
            }
            //strupr(tcari);
            data->teks[1].panjang=ganti_isi_data(data, 1, tcari);
        }
    }else{
        while(ckata[i]!=0){
            data=data->berikutnya;
            data->teks[1].x_wcard=0;
            if(ckata[i]=='?'){
                tcari[0]=0;
                n++;
                i++;
            }else if(ckata[i]=='['){
                i++;
                j=0;
                while(ckata[i]!=']'){
                    if(ckata[i]==0){
                        i--;
                        break;
                    }
                    tcari[j]=ckata[i];
                    i++;
                    j++;
                }
                tcari[j]=0;
                n++;
                i++;
            }else{
                tcari[0]=ckata[i];
                tcari[1]=0;
                n++;
                i++;
            }
            printf("%s\n", tcari);
            hurufbesar(tcari);
            data->teks[1].panjang=ganti_isi_data(data, 1, tcari);
        }
    }
    data->berikutnya=batas_kata;
    batas_kata->sebelumnya=data;
    //

    batas_kata->teks[1].panjang=n;
    //:D
    tdata=batas_kata->sebelumnya;
    //kumpulkan "?"
    data=batas_kata->berikutnya;
    while(data!=batas_kata && tdata!=batas_kata && data!=tdata){
        if(data->teks[1].isi[0]==0){
            if(data->teks[1].x_wcard==0){
                //tukar huruf/kata
                strcpy(ckata, data->teks[1].isi);
                strcpy(data->teks[1].isi, tdata->teks[1].isi);
                strcpy(tdata->teks[1].isi, ckata);
                //
                data=data->berikutnya;
            }
            if(data==tdata){
                break;
            }
            tdata=tdata->sebelumnya;
        }else{
            data=data->berikutnya;
        }
    }

    //lewati "?" dan "*"
    while(tdata!=batas_kata && tdata->teks[1].isi[0]==0){
        tdata=tdata->sebelumnya;
    }

    //kumpulkan "[....]"
    data=batas_kata->berikutnya;
    while(data!=batas_kata && tdata!=batas_kata && data!=tdata){
        if(data->teks[1].isi[0]==0){
            if(data->teks[1].x_wcard!=0){
                tdata=tdata->sebelumnya;
            }
        }else if(data->teks[1].isi[1]!=0){
            //tukar huruf/kata
            strcpy(ckata, data->teks[1].isi);
            strcpy(data->teks[1].isi, tdata->teks[1].isi);
            strcpy(tdata->teks[1].isi, ckata);
            //
            tdata=tdata->sebelumnya;
            if(data==tdata){
                break;
            }
            data=data->berikutnya;
        }else{
            data=data->berikutnya;
        }
    }

    //mulai pencarian
    i=dapatkan_posisi_pilihan(dapatkan_tombol(xtab, ID_MIN));
    j=dapatkan_posisi_pilihan(dapatkan_tombol(xtab, ID_MAX));
    tombol=dapatkan_tombol(xtab, ID_DAFTAR);
    batas_aktif=&tombol->batas_pertama;
    switch(jcari){
        case IDCARI_ANAGRAM:
            tombol->jdata=cari_anagram(batas_aktif, batas_kata, i, j, jenis);
            break;
        case IDCARI_POLA:
            tombol->jdata=cari_pola(batas_aktif, batas_kata, i, j, jenis);
            break;
        case IDCARI_PERBEDAAN:
            tombol->jdata=cari_perbedaan(batas_aktif, batas_kata, i, j, jenis);
            break;
        case IDCARI_SUBANAGRAM:
            tombol->jdata=cari_subanagram(batas_aktif, batas_kata, i, j, jenis);
            break;
        case IDCARI_HURUF_PEMBENTUK:
            tombol->jdata=cari_includes_letters(batas_aktif, batas_kata, i, j, jenis);
            break;
        case IDCARI_SUBPOLA:
            tombol->jdata=cari_subpola(batas_aktif, batas_kata, i, j, jenis);
            break;
        case IDCARI_AMBIL_AWALAN:
            printf("awalan");
            break;
        case IDCARI_AMBIL_AKHIRAN:
            printf("akhiran");
            break;
        default:
            break;
    }
    tombol->pos=1;
    tombol->perbaharui=1;
    tombol->pilihan=tombol->batas_pertama.berikutnya;
    tombol->atas_aktif=tombol->pilihan;
    daftar_susun(mwindow, tombol);
    perbaharui_tombol(mwindow, mwindow->ctab, 1);

    mwindow->status=STATUS_AWAL;
    return 0;
}

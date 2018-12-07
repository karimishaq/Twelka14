#include "main.h"

char xsdir[]="data/";
char sxletters[]="Extra letters";
char sbhook[]=">>";
char sfhook[]="<<";
char swords[]="Words";
char search_all[]="Search all";
char search_in_result[]="Search in result";
char search_and_insert[]="Search and insert";
char sfjpencarian[]="Jenis_pencarian.ini";
char sfile_ttekan[]="tombol_tekan.png";
char sfile_cari_semua[]="cari_semua.png";

int bukakamus(struct tombolku *daftar, char *namafile, int jkolom){
FILE *f=0;
char s[201];
stringku kata[5];
struct dataku *data, *batas;
int i, n, x;
    batas=&daftar->batas_pertama;
    f=fopen(namafile, "r");
    if(f){
        s[0]=0;
        kata[0][0]=0;
        kata[1][0]=0;
        kata[2][0]=0;
        kata[3][0]=0;
        if(fgets(s, 100, f)){
            x=str_panjang(s)-1;
            if(s[x]==10 || s[x]==13){
                s[x]=0;
            }else{
                x++;
                i=n;
            }
            pisahkan(s, kata[0], kata[1], kata[2], kata[3], ':');
            ganti_isi_data(batas, 0, kata[0]);
            ganti_isi_data(batas, 1, kata[1]);
            if(kata[2][0]!=0)ganti_isi_data(batas, 2, kata[2]);
            if(kata[3][0]!=0)ganti_isi_data(batas, 3, kata[3]);
            n=30000;
            i=0;
            while(i<n){
                if(feof(f))break;
                s[0]=0;
                if(fgets(s, 101, f)){
                    if(s[0]!=0){
                        hurufbesar(s);
                        x=str_panjang(s)-1;
                        if(s[x]==10 || s[x]==13){
                            s[x]=0;
                        }else{
                            x++;
                            i=n;
                        }
                        kata[0][0]=0;
                        kata[1][0]=0;
                        pisahkan(s, kata[0], kata[1], kata[2], kata[3], ':');
                        data=tambah_data_daftar(daftar);
                        data->teks[0].panjang=ganti_isi_data(data, 0, kata[0]);
                        data->teks[1].panjang=ganti_isi_data(data, 1, kata[1]);
                        if(kata[2][0]!=0)ganti_isi_data(data, 2, kata[2]);
                        if(kata[3][0]!=0)ganti_isi_data(data, 3, kata[3]);
                    }else{
                        break;
                    }
                }
                i++;
            }

            //urutkan_kolom 1
            urutkan_data(daftar, IDURUT_ALFABET, 0);
            //atur posisi pilihan

            batas=&daftar->batas_pertama;
            data=batas->berikutnya;
            pindah_posisi(daftar, 1);
        }
        fclose(f);
    }
    return 0;
}

struct tabku *tab_baru(struct Windowku *mwindow, char *folder, char *file){
struct tabku *ctab=0;
struct tombolku *tombol, *daftar;
struct dataku *batas;
int jkolom=0;
int x, y, w, h;
int berhasil=0;
char s[201], namafile[256];
stringku kata[4];
FILE *f=NULL;
TTF_Font *huruf;
    strcpy(namafile, folder);
    strcat(namafile, file);
    ctab=mwindow->ltab;
    if(ctab==0)return 0;
    kata[0][0]=0;
    kata[1][0]=0;
    kata[2][0]=0;
    kata[3][0]=0;
    f=fopen(namafile, "r");
    if(f){
        if(fgets(s, 100, f))
            jkolom=pisahkan(s, kata[0], kata[1], kata[2], kata[3], ':');
        fclose(f);
    }
    if(jkolom>=2){
        mwindow->ctab=ctab;
        ctab->jenis=2;
        //mulai buat tombol
        //tomboltab
        buat_tombol(mwindow, TB_TOMBOL_TEKAN, 0, (char*)"tombol_menu.png", 4, 4, 0, 0, ID_TAB0, 1);
        buat_tombol(mwindow, TB_TOMBOL_TEKAN, (char*)"Tab 1", sfile_ttekan, 30, 4, 0, 0, ID_TAB1, 0);
        buat_tombol(mwindow, TB_TOMBOL_TEKAN, (char*)"Tab 2", sfile_ttekan, 186, 4, 0, 0, ID_TAB2, 0);
        buat_tombol(mwindow, TB_TOMBOL_TEKAN, (char*)"Tab 3", sfile_ttekan, 342, 4, 0, 0, ID_TAB3, 0);
        buat_tombol(mwindow, TB_NAMA, file, sfile_ttekan, 498, 4, 0, 0, 0, 0);
        //
        buat_tombol(mwindow, TB_TULISAN, 0, 0, 30, 34, 606, 24, ID_KATA_KAMUS, 128);
        buat_tombol(mwindow, TB_TOMBOL_TEKAN, 0, (char*)"tukar_kolom.png", 4, 34, 0, 0, ID_TUKAR_KOLOM, 1);
        //buat daftar kata
        daftar=buat_tombol(mwindow, TB_DAFTARKU, 0, 0, 4, 62, 632, 390, ID_DAFTAR, jkolom);
        //nama kolom daftar
        bukakamus(daftar, namafile, jkolom);

        //buat tombol status
        buat_tombol(mwindow, TB_STATUS, 0, 0, 0, 456, 640, 24, ID_STATUS, 4);
        twelka_atur_status(mwindow);
        perbaharui_tombol(mwindow, mwindow->ctab, 1);
    }else{
        jkolom=3;
        mwindow->ctab=ctab;
        ctab->jenis=1;
        huruf=mwindow->huruf;

        //mulai buat tombol

        //tomboltab
        buat_tombol(mwindow, TB_TOMBOL_TEKAN, 0, (char*)"tombol_menu.png", 4, 4, 0, 0, ID_TAB0, 1);
        buat_tombol(mwindow, TB_TOMBOL_TEKAN, (char*)"Tab 1", sfile_ttekan, 30, 4, 0, 0, ID_TAB1, 0);
        buat_tombol(mwindow, TB_TOMBOL_TEKAN, (char*)"Tab 2", sfile_ttekan, 186, 4, 0, 0, ID_TAB2, 0);
        buat_tombol(mwindow, TB_TOMBOL_TEKAN, (char*)"Tab 3", sfile_ttekan, 342, 4, 0, 0, ID_TAB3, 0);
        buat_tombol(mwindow, TB_NAMA, file, sfile_ttekan, 498, 4, 0, 0, 0, 0);
        //buat daftar kata
        daftar=buat_tombol(mwindow, TB_DAFTARKU, 0, 0, 4, 90, 632, 362, ID_DAFTAR, 3);
        batas=&daftar->batas_pertama;
        ganti_isi_data(batas, 0, sfhook);
        ganti_isi_data(batas, 1, swords);
        ganti_isi_data(batas, 2, sbhook);
        bukadaftarkata(daftar, namafile);

        //buka file
        //berhasil=dtkata_buka(mwindow, (char*)namafile, daftar);
        berhasil=1;
        if(berhasil==0){
            mwindow->ctab=ctab;
        }else{
            //buat tombol lain
            buat_tombol(mwindow, TB_TULISAN, 0, 0, 4, 34, 286, 24, ID_KATA_KATA, 128);
            buat_tombol(mwindow, TB_TOMBOL_TEKAN, 0, sfile_cari_semua, 294, 34, 0, 0, ID_CARI_SEMUA, 1);
            //buat tombol nama
            TTF_SizeText(huruf, sxletters, &w, &h);
            x=77-(w/2);
            y=(24-h)/2;
            buat_tombol(mwindow, TB_NAMA, sxletters, 0, x+402, y+34, 154, 24, ID_TAMBAHAN_HURUF, 0);
            //buat tombol_pilihan

            tombol=buat_tombol(mwindow, TB_PILIHAN, 0, 0, 322, 34, 78, 0, ID_MIN, 5);
            tambah_pilihan_angka(tombol, 0, 10);
            tombol=buat_tombol(mwindow, TB_PILIHAN, 0, 0, 558, 34, 78, 0, ID_MAX, 5);
            tambah_pilihan_angka(tombol, 0, 10);
            tombol=buat_tombol(mwindow, TB_PILIHAN, 0, 0, 4, 62, 314, 0, ID_JENIS_PENCARIAN, 5);
            tambah_pilihan_berkas(tombol, sfjpencarian);
            //buat tombol_biasa
            buat_tombol(mwindow, TB_TOMBOL_TEKAN, search_in_result, sfile_ttekan, 322, 62, 0, 0, ID_CARI_DALAM_HASIL, 0);
            buat_tombol(mwindow, TB_TOMBOL_TEKAN, search_and_insert, sfile_ttekan, 481, 62, 0, 0, ID_CARI_DAN_GABUNGKAN, 0);

            //buat tombol status
            tombol=buat_tombol(mwindow, TB_STATUS, 0, 0, 0, 456, 640, 24, ID_STATUS, 4);
            twelka_atur_status(mwindow);

            perbaharui_tombol(mwindow, mwindow->ctab, 1);
        }
    }
    return ctab;
}

int aksi_klik_tombol(struct Windowku *mwindow, struct tombolku* ctombol, int x, int y){
struct tombolku *tombol;
    switch(ctombol->id){
        case ID_CARI_SEMUA:
            cari_kata(mwindow, ID_CARI_SEMUA);
            break;
        case ID_CARI_DALAM_HASIL:
            cari_kata(mwindow, ID_CARI_DALAM_HASIL);
            break;
        case ID_CARI_DAN_GABUNGKAN:
            cari_kata(mwindow, ID_CARI_DAN_GABUNGKAN);
            break;
        case ID_BUKA_BERKAS:{
        struct tabku *ctab;
        char namafile[256];
            mwindow->proses=1;
            tombol=dapatkan_tombol(mwindow->ctab, ID_DAFTAR_BERKAS);
            str_salin(namafile, tombol->pilihan->teks[0].isi);
            //hapus tab dialog
            if(tombol!=0){
                //tab baru
                ctab=tab_baru(mwindow, xsdir, namafile);
                if(ctab!=0){
                    mwindow->ctab=ctab;
                    tombol->perbaharui=1;
                }
            }
            if(dapatkan_tombol(mwindow->ctab, ID_STATUS)!=0){
                twelka_atur_status(mwindow);
            }
            mwindow->proses=0;
            break;
        }
        case ID_TUKAR_KOLOM:
            mwindow->proses=1;
            tombol=dapatkan_tombol(mwindow->ctab, ID_DAFTAR);
            if(tombol->kolom_utama<tombol->jkolom)tombol->kolom_utama++;
            if(tombol->kolom_utama>=tombol->jkolom)tombol->kolom_utama=0;
            urutkan_data(tombol, IDURUT_ALFABET, tombol->kolom_utama);
            mwindow->proses=0;
            break;
        case ID_TAB0:
            if(mwindow->ctab!=&mwindow->tab[0]){
                tampilkan_menu(mwindow, mwindow->menu_dtkata, 4, 29);
            }
            break;
        case ID_TAB1:
            if(mwindow->tab[1].jtombol==0){
                mwindow->ltab=&mwindow->tab[1];
                mwindow->ctab=&mwindow->tab[0];
            }else{
                mwindow->ctab=&mwindow->tab[1];
            }
            break;
        case ID_TAB2:
            if(mwindow->tab[2].jtombol==0){
                mwindow->ltab=&mwindow->tab[2];
                mwindow->ctab=&mwindow->tab[0];
            }else{
                mwindow->ctab=&mwindow->tab[2];
            }
            break;
        case ID_TAB3:
            if(mwindow->tab[3].jtombol==0){
                mwindow->ltab=&mwindow->tab[3];
                mwindow->ctab=&mwindow->tab[0];
            }else{
                mwindow->ctab=&mwindow->tab[3];
            }
            break;
        default:
            break;
    }
    perbaharui_tombol(mwindow, mwindow->ctab, benar);
    return 0;
}

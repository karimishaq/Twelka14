#include "main.h"

struct tombolku *buat_tombol(struct Windowku *mwindow, int jenis, char *nama, char *sgambar, int x, int y, int w, int h, int id, int jumlah){
struct tabku *xtab;
struct tombolku *tombol=0;
struct dataku *batas_data, *data;
SDL_Color hitam={0,0,0};
SDL_Surface *gtulisan, *pbawah, *tgambar;
SDL_Rect rct, rcd;
int i=0;
int xpos=0;
int panjang=0;
int tinggi;
    xtab=mwindow->ctab;
    tombol=&xtab->tombol[xtab->jtombol];
    xtab->jtombol++;
    //
    tombol->id=id;
    tombol->jenis=jenis;
    tombol->jkolom=jumlah;
    tombol->x=x;
    tombol->y=y;
    tombol->cx=x+w;
    tombol->cy=y+h;
    tombol->jtampil=0;
    tombol->jdata=0;
    tombol->pos=0;
    tombol->spesial=jumlah;
    tombol->yscrollbar=0;
    tombol->hscrollbar=0;
    tombol->kolom_utama=0;
    tombol->status=0;
    tombol->gdilepas=0;
    tombol->gdilewati=0;
    tombol->gditekan=0;
    tombol->cgambar=0;

    tombol->atas_aktif=0;
    tombol->pilihan=0;
    tombol->bawah=0;

    switch(jenis){
        case TB_TOMBOL_TEKAN:
            tgambar=IMG_Load(sgambar);

            tombol->cx=x+tgambar->w;
            tombol->cy=y+24;

            rct.x=0;
            rct.y=0;
            rct.w=tgambar->w;
            rct.h=tgambar->h/3;
            tombol->gdilepas=buat_lapisan(rct.w, rct.h);
            tombol->gdilewati=buat_lapisan(rct.w, rct.h);
            tombol->gditekan=buat_lapisan(rct.w, rct.h);
            //
            SDL_BlitSurface(tgambar, &rct, tombol->gdilepas, 0);
            rct.y+=rct.h;
            SDL_BlitSurface(tgambar, &rct, tombol->gdilewati, 0);
            rct.y+=rct.h;
            SDL_BlitSurface(tgambar, &rct, tombol->gditekan, 0);
            if(nama!=0){
                gtulisan=TTF_RenderText_Blended(mwindow->huruf, nama, hitam);
                if(gtulisan!=0){
                    rct.x=(tombol->gdilepas->w-gtulisan->w)/2;
                    rct.y=(tombol->gdilepas->h-gtulisan->h)/2;
                    //tombol dilepas
                    SDL_BlitSurface(gtulisan, 0, tombol->gdilepas, &rct);
                    //Tombol ditekan
                    SDL_BlitSurface(gtulisan, 0, tombol->gditekan, &rct);
                    //Tombol dilewati
                    SDL_BlitSurface(gtulisan, 0, tombol->gdilewati, &rct);
                }
                SDL_FreeSurface(gtulisan);
            }
            SDL_FreeSurface(tgambar);
            SDL_SetColorKey(tombol->gdilepas, SDL_TRUE, SDL_MapRGB(tombol->gdilepas->format, 0, 254, 254));
            SDL_SetColorKey(tombol->gdilewati, SDL_TRUE, SDL_MapRGB(tombol->gdilewati->format, 0, 254, 254));
            SDL_SetColorKey(tombol->gditekan, SDL_TRUE, SDL_MapRGB(tombol->gditekan->format, 0, 254, 254));
            break;
        case TB_TULISAN:
            tombol->gdilepas=buat_lapisan(w, h);
            if(jumlah==0){
                jumlah=28;
            }
            tombol->jdata=jumlah;
            tombol->tulisan[0]=0;
            break;
        case TB_NAMA:
            gtulisan=TTF_RenderText_Blended(mwindow->huruf, nama, hitam);
            if(gtulisan!=0){
                if(tombol->cgambar!=0){
                    SDL_FreeSurface(tombol->cgambar);
                }
                tombol->gdilepas=gtulisan;
            }
            break;
        case TB_DAFTARKU:
            if(jumlah>1)tombol->spesial=TINGGI_KEPALA_DAFTAR;
            else tombol->spesial=0;
            //atur batas untuk data dalam daftar
            batas_data=&tombol->batas_pertama;
            batas_data->sebelumnya=batas_data;
            batas_data->berikutnya=batas_data;
            batas_data->asli_berikutnya=batas_data;
            panjang=((tombol->cx-tombol->x)-LEBAR_SCROLLBAR-2)/jumlah;
            i=0;
            while(i<jumlah){
                batas_data->teks[i].isi[0]=0;
                batas_data->teks[i].panjang=panjang-2;
                i++;
            }
            //
            tombol->atas_aktif=batas_data;
            tombol->pilihan=batas_data;
            //buat lapisan
            tombol->gdilepas=buat_lapisan(w, h);
            break;
        case TB_STATUS:
            //
            tombol->jkolom=4;
            tombol->jdata=4;
            tombol->gdilepas=buat_lapisan(w, h);

            i=0;
            xpos=2;
            panjang=((tombol->cx-tombol->x)-2)/jumlah;
            data=&tombol->batas_pertama;
            while(i<jumlah){
                data->teks[i].isi[0]=0;
                data->teks[i].x_wcard=xpos;
                data->teks[i].panjang=panjang-2;
                xpos+=panjang;
                i++;
            }
            break;
        case TB_PILIHAN:
            pbawah=mwindow->gambar.panah;
            tinggi=(pbawah->h/3)+4;
            tombol->jkolom=1;
            tombol->cx=x+w;
            tombol->cy=y+tinggi;
            if(jumlah==0){
                tombol->jtampil=5;
            }
            tombol->jtampil=jumlah;
            tombol->pos=0;

            //atur batas untuk data dalam daftar
            batas_data=&tombol->batas_pertama;
            batas_data->sebelumnya=batas_data;
            batas_data->berikutnya=batas_data;
            batas_data->asli_berikutnya=batas_data;
            batas_data->teks[0].isi[0]=0;
            batas_data->teks[0].panjang=0;
            //
            tombol->atas_aktif=batas_data;
            tombol->pilihan=batas_data;
            //buat lapisan
            //set variabel
            rcd.x=w-tinggi+2;
            rcd.y=2;
            rcd.w=tinggi;
            rcd.h=tinggi;
            rct.x=0;
            rct.w=tinggi-4;
            rct.h=tinggi-4;
            //tombol pilihan dilepas
            rct.y=0;
            tombol->gdilepas=buat_lapisan(w, tinggi);
            gambar_kotak(tombol->gdilepas, 0, 0, w, tinggi, 0, 0, 0);
            gambar_kotak(tombol->gdilepas, 1, 1, w-2, tinggi-2, 255, 255, 255);
            SDL_BlitSurface(pbawah, &rct, tombol->gdilepas, &rcd);
            //tombol pilihan dilewati
            rct.y+=rct.h;
            tombol->gdilewati=buat_lapisan(w, tinggi);
            gambar_kotak(tombol->gdilewati, 0, 0, w, tinggi, 0, 0, 0);
            gambar_kotak(tombol->gdilewati, 1, 1, w-2, tinggi-2, 255, 255, 255);
            SDL_BlitSurface(pbawah, &rct, tombol->gdilewati, &rcd);
            //tombol pilihan ditekan
            rct.y+=rct.h;
            tombol->gditekan=buat_lapisan(w, tinggi);
            gambar_kotak(tombol->gditekan, 0, 0, w, tinggi, 0, 0, 0);
            gambar_kotak(tombol->gditekan, 1, 1, w-2, tinggi-2, 255, 255, 255);
            SDL_BlitSurface(pbawah, &rct, tombol->gditekan, &rcd);
            //
            tombol->cgambar=buat_lapisan(w, tinggi);
            break;
        default:
            break;
    }

    if(tombol->jenis!=TB_PILIHAN)tombol->cgambar=tombol->gdilepas;
    if(tombol->cgambar!=0 && tombol->jenis==TB_TULISAN){
        susun_tulisan(mwindow, tombol);
    }
    tombol->perbaharui=1;
    return tombol;
}

int susun_scroll_bar(struct Windowku *mwindow, struct tombolku *tombol, SDL_Surface *latar, int posx){
SDL_Surface *tgambar;
int tpanah;
int pjbatang, pjtotal, ypos;
int jsisa, jtampil, pjsisa, posisi;

    posisi=tombol->pos;
    jtampil=tombol->jtampil;
    tgambar=mwindow->gambar.panah;
    tpanah=tgambar->w/2;
    pjtotal=tombol->cy-tombol->y-tpanah-tpanah;

    if(tombol->jdata > jtampil)jsisa=tombol->jdata-jtampil;
    else{
        jsisa=1;
        if(tombol->jdata==0){
            jtampil=1;
            posisi=1;
        }
    }

    pjbatang=pjtotal/jsisa;
    if(pjbatang<20)pjbatang=20;

    pjsisa=pjtotal-pjbatang;
    if(pjsisa==0)pjsisa=1;
    if(posisi>jtampil)ypos=tpanah+((posisi-jtampil)*pjsisa/jsisa);
    else ypos=tpanah;
    gambar_kotak(latar, posx, tpanah, LEBAR_SCROLLBAR, pjtotal, 250, 0, 250);
    gambar_kotak(latar, posx+2, ypos, 16, pjbatang, 250, 255, 250);
    if(tombol->status==DAFTAR_NAIK)tampilkan_gambar(latar, tgambar, posx, 0, tpanah, tpanah+tpanah, tpanah, tpanah);
    else if(tombol->status==DAFTAR_KEDIP_NAIK)tampilkan_gambar(latar, tgambar, posx, 0, tpanah, tpanah, tpanah, tpanah);
    else tampilkan_gambar(latar, tgambar, posx, 0, tpanah, 0, tpanah, tpanah);
    if(tombol->status==DAFTAR_TURUN)tampilkan_gambar(latar, tgambar, posx, pjtotal+tpanah, 0, tpanah+tpanah, tpanah, tpanah);
    else if(tombol->status==DAFTAR_KEDIP_TURUN)tampilkan_gambar(latar, tgambar, posx, pjtotal+tpanah, 0, tpanah, tpanah, tpanah);
    else tampilkan_gambar(latar, tgambar, posx, pjtotal+tpanah, 0, 0, tpanah, tpanah);
    tombol->yscrollbar=ypos;
    tombol->hscrollbar=pjbatang;
    return 0;
}

int susun_judul_daftar(struct Windowku *mwindow, struct tombolku *daftar){
int i, x, y, jkolom;
struct dataku *data;
SDL_Surface *latar;
SDL_Color hitam={0,0,0};
TTF_Font *huruf;
    latar=daftar->cgambar;
    huruf=mwindow->huruf;
    gambar_kotak(latar, 0, 0, daftar->cx-daftar->x, TINGGI_KEPALA_DAFTAR, 255, 128, 0);
    i=0;
    jkolom=daftar->jkolom;
    data=&daftar->batas_pertama;
    x=2;
    y=2;
    while(i<jkolom){
        gambar_kotak(latar, x, y, data->teks[i].panjang, TINGGI_KEPALA_DAFTAR-2, 255, 255, 255);
        if(data->teks[i].isi[0]!=0){
            if(i==0 && jkolom>1){
                gambar_tulisan(latar, huruf, data->teks[daftar->kolom_utama].isi, hitam, x, y);
            }else if(i==daftar->kolom_utama){
                gambar_tulisan(latar, huruf, data->teks[0].isi, hitam, x, y);
            }else gambar_tulisan(latar, huruf, data->teks[i].isi, hitam, x, y);//??
        }
        x+=data->teks[i].panjang+2;
        i++;
    }
    return 0;
}

struct dataku *tambah_data_daftar(struct tombolku *daftar){
struct dataku *data=0;
struct dataku *batas;
char *data_isi;
int i, n;
    i=0;
    n=daftar->jkolom;
    data=(dataku*) malloc(sizeof(struct dataku));
    batas=&daftar->batas_pertama;
    //atur data_asli
    data->asli_berikutnya=batas;
    batas->sebelumnya->asli_berikutnya=data;
    //
    data->berikutnya=batas;
    data->sebelumnya=batas->sebelumnya;
    batas->sebelumnya->berikutnya=data;
    batas->sebelumnya=data;
    while(i<n){
        data_isi=data->teks[i].isi;
        data_isi[0]=0;
        data->teks[i].panjang=0;
        i++;
    }
    daftar->jdata++;
    return data;
}

int daftar_posisi_bawah(struct tombolku *tdaftar, struct dataku *batas){
int pos;
struct dataku *data, *bawah;
    pos=tdaftar->pos;
    data=tdaftar->pilihan;
    bawah=tdaftar->bawah;
    if(bawah!=0){
        while(data!=batas && data!=bawah){
            pos++;
            data=data->berikutnya;
        }
    }
    return pos;
}

int daftar_posisi_atas(struct tombolku *tdaftar, struct dataku *batas){
int pos;
struct dataku *data, *atas;
    pos=tdaftar->pos;
    data=tdaftar->pilihan;
    atas=tdaftar->atas_aktif;
    if(atas!=0){
        while(data!=batas && data!=atas){
            pos--;
            data=data->sebelumnya;
        }
    }
    return pos;
}

int daftar_susun(struct Windowku *mwindow, tombolku *tombol){
SDL_Surface *latar;
TTF_Font *huruf;
SDL_Color hitam={0,0,0};
struct tabku *xtab;
struct dataku *data, *data2, *pilihan;
struct dataku *batas, *batas2;
int x, y, panjang, tinggi, kepala;
int i, jkolom;
int jtampil=0;
    xtab=mwindow->ctab;
    pilihan=tombol->pilihan;
    huruf=mwindow->huruf;
    latar=tombol->cgambar;
    jkolom=tombol->jkolom;
    kepala=0;
    panjang=tombol->cx-tombol->x;
    tinggi=tombol->cy-tombol->y;
    if((tombol->status!=DAFTAR_KEDIP_NAIK)&&(tombol->status!=DAFTAR_KEDIP_TURUN)){
        if(tombol->spesial!=0)susun_judul_daftar(mwindow, tombol);
        if(tombol->spesial!=0){
            kepala=TINGGI_KEPALA_DAFTAR;
            tinggi-=TINGGI_KEPALA_DAFTAR;
        }
        gambar_kotak(latar, 0, kepala, panjang, tinggi, 255, 128, 0);
        i=0;
        x=2;
        y=2;
        batas=&tombol->batas_pertama;
        while(i<jkolom){
            gambar_kotak(latar, x, y+kepala, batas->teks[i].panjang, tinggi-4, 255, 255, 255);
            x+=batas->teks[i].panjang+2;
            i++;
        }

        tinggi=tombol->cy-tombol->y-TINGGI_BARIS_DAFTAR;
        jkolom=tombol->jkolom;
        //
        y=2;
        if(tombol->spesial!=0)y+=TINGGI_KEPALA_DAFTAR;
        jtampil=0;
        data=tombol->atas_aktif;
        batas=&tombol->batas_pertama;
        while((y<tinggi)&&(data!=batas)){
            if(data==pilihan){
                i=0;
                x=2;
                batas2=batas;
                while(i<jkolom){
                    if(tombol==xtab->tombol_aktif){
                        gambar_kotak(latar, x, y, batas2->teks[i].panjang, TINGGI_BARIS_DAFTAR, 0, 255, 0);
                    }else{
                        gambar_kotak(latar, x, y, batas2->teks[i].panjang, TINGGI_BARIS_DAFTAR, 0, 255, 255);
                    }
                    x+=batas2->teks[i].panjang+2;
                    i++;
                }
            }
            i=0;
            x=4;
            data2=data;
            batas2=&tombol->batas_pertama;
            jkolom=tombol->jkolom;
            while(i<jkolom){
                if(data2->teks[i].isi[0]!=0){
                    if(i==0 && jkolom>1){
                        gambar_tulisan(latar, huruf, data2->teks[tombol->kolom_utama].isi, hitam, x, y-2);
                    }else if(i==tombol->kolom_utama){
                        gambar_tulisan(latar, huruf, data2->teks[0].isi, hitam, x, y-2);
                    }else gambar_tulisan(latar, huruf, data2->teks[i].isi, hitam, x, y-2);
                }
                x+=batas2->teks[i].panjang+2;
                i++;
            }
            tombol->bawah=data;
            data=data->berikutnya;
            y+=TINGGI_BARIS_DAFTAR;
            jtampil++;
        }
        if(jtampil>=tombol->jtampil){
            tombol->jtampil=jtampil;
        }
    }
    susun_scroll_bar(mwindow, tombol, tombol->cgambar, panjang-LEBAR_SCROLLBAR);
    return 0;
}

int dapatkan_posisi_pilihan(struct tombolku *tombol){
int pos=0;
struct dataku *data, *batas, *pilihan;
    pilihan=tombol->pilihan;
    batas=&tombol->batas_pertama;
    data=batas->berikutnya;
    while(data!=batas){
        if(data==pilihan){
            break;
        }
        data=data->berikutnya;
        pos++;
    }
    return pos;
}

int tambah_pilihan_berkas(tombolku *tombol, char* nama_file){
int i, x;
int n=0;
char s[101];
FILE *f1;
struct dataku *data;
    if(tombol!=0){
        if(tombol->jenis==TB_PILIHAN){
            f1=fopen(nama_file, "r");
            if(f1){
                if(fgets(s, 101, f1)){
                    if(str_panjang(s)>5){
                        if(s[0]=='p' && s[1]=='i' && s[2]=='l' && s[3]==':'){
                            n=atoi(s+4);
                            if(n>10000)n=10000;
                            i=0;
                            while(i<n){
                                if(fgets(s, 101, f1)){
                                    x=str_panjang(s)-1;
                                    if(s[x]==10 || s[x]==13){
                                        s[x]=0;
                                    }else{
                                        x++;
                                        i=n;
                                    }
                                    tambah_pilihan(tombol, s);
                                }
                                i++;
                            }
                        }
                    }
                    data=tombol->batas_pertama.berikutnya;
                    tombol->atas_aktif=data;
                    tombol->pilihan=data;
                }
                fclose(f1);
            }
        }
    }
    return 0;
}

int tambah_pilihan_angka(tombolku *tombol, int awal, int akhir){
int i;
char s[20];
dataku *data;
    if(tombol!=0){
        if(tombol->jenis==TB_PILIHAN){
            i=awal;
            while(i<=akhir){
                snprintf(s, 10, "%d", i);
                tambah_pilihan(tombol, s);
                i++;
            }
        }
    }
    data=tombol->batas_pertama.berikutnya;
    tombol->atas_aktif=data;
    tombol->pilihan=data;
    return 0;
}

int susun_pilihan(struct Windowku *mwindow, struct tombolku *tombol){
int w, h;
struct tabku *xtab;
SDL_Surface *latar, *tgambar;
SDL_Color hitam={0,0,0};
TTF_Font *huruf;
    xtab=mwindow->ctab;
    latar=tombol->cgambar;
    huruf=mwindow->huruf;
    tgambar=tombol->gdilepas;
    if((mwindow->status!=MENU_DITAMPILKAN)&& ( tombol==mwindow->tombol_dilewati)){
        if((tombol==xtab->tombol_aktif)&&(mwindow->tombol_ditekan!=0)){
            tgambar=tombol->gditekan;
        }else{
            if(mwindow->status==PILIHAN_DITAMPILKAN){
                if(tombol==mwindow->ctab->tombol_aktif){
                    tgambar=tombol->gdilewati;
                }
            }else{
                tgambar=tombol->gdilewati;
            }
        }
    }
    if(tgambar!=0 && latar!=0){
        tampilkan_gambar(latar, tgambar, 0, 0, 0, 0, tgambar->w, tgambar->h);
    }
    if(&tombol->batas_pertama!=tombol->batas_pertama.berikutnya){
        if(tombol->pilihan!=0){
            TTF_SizeText(huruf, tombol->pilihan->teks[0].isi, &w, &h);
            gambar_tulisan(latar, huruf, tombol->pilihan->teks[0].isi, hitam, 4, 12-(h/2));
        }
    }
    return 0;
}

struct dataku *tambah_pilihan(tombolku *tpilihan, char *isi){
struct dataku *data=0;
struct dataku *batas, *sebelumnya;
    batas=&tpilihan->batas_pertama;
    data=(dataku*) malloc(sizeof(struct dataku));
    sebelumnya=batas->sebelumnya;
    //atur data_asli
    data->asli_berikutnya=batas;
    sebelumnya->asli_berikutnya=data;
    //sambungkan data dengan batas data dan data sebelumnya
    sebelumnya->berikutnya=data;
    data->sebelumnya=sebelumnya;
    data->berikutnya=batas;
    batas->sebelumnya=data;
    //atur pilihan
    ganti_isi_data(data, 0, isi);
    data=tpilihan->batas_pertama.berikutnya;
    tpilihan->atas_aktif=data;
    tpilihan->pilihan=data;
    tpilihan->jkolom=1;
    tpilihan->jdata++;
    return data;
}

int susun_status(struct Windowku *mwindow, struct tombolku *tombol){
int i, jkolom;
struct dataku *data;
SDL_Surface *latar;
SDL_Color hitam={0,0,0};
TTF_Font *huruf;
    latar=tombol->cgambar;
    huruf=mwindow->huruf;
    gambar_kotak(latar, 0, 0, tombol->cx-tombol->x, tombol->cy-tombol->y, 255, 128, 0);
    i=0;
    jkolom=tombol->jkolom;
    data=&tombol->batas_pertama;
    while(i<jkolom){
        gambar_kotak(latar, data->teks[i].x_wcard, 2, data->teks[i].panjang, tombol->cy-tombol->y-4, 255, 255, 128);
        gambar_tulisan(latar, huruf, data->teks[i].isi, hitam, data->teks[i].x_wcard+2, 0);
        i++;
    }
    return 0;
}

int susun_tombol_tekan(struct Windowku *mwindow, tombolku *tombol, struct tabku *xtab){
    if(tombol!=mwindow->tombol_dilewati){
        tombol->cgambar=tombol->gdilepas;
    }else{
        if((tombol==xtab->tombol_aktif)&&(mwindow->tombol_ditekan!=0)){
            tombol->cgambar=tombol->gditekan;
        }else{
            tombol->cgambar=tombol->gdilewati;
        }
    }
    return 0;
}

int susun_tulisan(struct Windowku *mwindow, struct tombolku *tombol){
SDL_Surface *latar;
TTF_Font *huruf;
SDL_Color hitam={0, 0, 0};
int y, w, h, panjang;
char *s;
struct tabku *xtab;
    xtab=mwindow->ctab;
    latar=tombol->cgambar;
    huruf=mwindow->huruf;
    panjang=tombol->cx-tombol->x;
    gambar_kotak(latar, 0, 0, panjang, tombol->cy-tombol->y, 0, 0, 0);
    gambar_kotak(latar, 2, 2, panjang-4, tombol->cy-tombol->y-4, 255, 255, 255);
    panjang-=12;
    s=tombol->tulisan;
    TTF_SizeText(huruf, s, &w, &h);
    while(w>panjang){
        s++;
        TTF_SizeText(huruf, s, &w, &h);
    }
    y=((tombol->cy-tombol->y)/2)-(h/2);
    gambar_tulisan(latar, huruf, s, hitam, 4, y);
    if((xtab->tombol_aktif==tombol)&&(tombol->status!=0)){
        y+=2;
        gambar_kotak(latar, w+5, y, 2, y+h-8, 0, 0, 0);
    }
    return 0;
}

int ubah_tulisan(struct tombolku *tombol, int scode, int mod){
    if((tombol->tulisan==0)||(scode==SDLK_LSHIFT)||(scode==SDLK_RSHIFT)
       ||(scode==SDLK_LCTRL)||(scode==SDLK_RCTRL)
       ||(scode==SDLK_LALT)||(scode==SDLK_RALT)
       ||(scode==SDLK_CAPSLOCK)||(scode==SDLK_NUMLOCKCLEAR)){
        return 0;
    }
    if((mod==1)||(mod==2)){
        if((scode>='a')&&(scode<='z')){
            scode-=32;
        }else{
            switch(scode){
                case SDLK_0:
                    scode=')';
                    break;
                case SDLK_1:
                    scode='!';
                    break;
                case SDLK_2:
                    scode='@';
                    break;
                case SDLK_3:
                    scode='#';
                    break;
                case SDLK_4:
                    scode='$';
                    break;
                case SDLK_5:
                    scode='%';
                    break;
                case SDLK_6:
                    scode='^';
                    break;
                case SDLK_7:
                    scode='&';
                    break;
                case SDLK_8:
                    scode='*';
                    break;
                case SDLK_9:
                    scode='(';
                    break;
                case SDLK_SLASH:
                    scode='?';
                    break;
                case SDLK_MINUS:
                    scode='_';
                    break;
                case SDLK_EQUALS:
                    scode='+';
                    break;
                case SDLK_BACKSLASH:
                    scode='|';
                    break;
                default:
                    break;
            }
        }
    }
    switch(scode){
    int k;
        case SDLK_BACKSPACE:
            k=str_panjang(tombol->tulisan)-1;
            if(k>=0){
                tombol->tulisan[k]=0;
            }
            break;
        case SDLK_RETURN:
            break;
        default:
            k=str_panjang(tombol->tulisan);
            if(k<tombol->jdata){
                tombol->tulisan[k]=scode;
                k++;
                tombol->tulisan[k]=0;
            }
            break;
    }
    return 0;
}

int perbaharui_tombol(struct Windowku *mwindow, struct tabku* ctab, char semua){
struct tombolku *tombol;
int i, n;
    if(ctab!=0){
        i=0;
        n=ctab->jtombol;
        while(i<n){
            tombol=&ctab->tombol[i];
            if(semua!=0){
                tombol->perbaharui=semua;
            }
            if(tombol->perbaharui!=0){
                switch(tombol->jenis){
                    case TB_TOMBOL_TEKAN:
                        susun_tombol_tekan(mwindow, tombol, ctab);
                        break;
                    case TB_TULISAN:
                        susun_tulisan(mwindow, tombol);
                        break;
                    case TB_DAFTARKU:
                        daftar_susun(mwindow, tombol);
                        break;
                    case TB_STATUS:
                        susun_status(mwindow, tombol);
                        break;
                    case TB_PILIHAN:
                        susun_pilihan(mwindow, tombol);
                    default:
                        break;
                }
                tombol->perbaharui=0;
            }else{
                tombol->perbaharui=1;
            }
            i++;
        }
        if(ctab!=mwindow->ctab)perbaharui_tombol(mwindow, mwindow->ctab, semua);
    }
    return 0;
}

struct tombolku *dapatkan_tombol(struct tabku *ctab, int id){
struct tombolku *tombol=0;
int i, n;
    if(ctab!=0){
        i=0;
        n=ctab->jtombol;
        while(i<n){
            tombol=&ctab->tombol[i];
            if(tombol->id==id){
                break;
            }
            i++;
        }
    }
    if(i>=n)tombol=0;
    return tombol;
}

struct tombolku *tombol_yang_dilewati(tabku *ctab, int x, int y){
tombolku *tombol=0;
int i, n;
    i=0;
    n=ctab->jtombol;
    while(i<n){
        tombol=&ctab->tombol[i];
        if((x>=tombol->x)&&(y>=tombol->y)){
            if((x<tombol->cx)&&(y<tombol->cy)){
                break;
            }
        }
        i++;
    }
    if(i>=n)tombol=0;
    return tombol;
}

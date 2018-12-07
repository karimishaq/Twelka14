#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
//boolean
#define salah 0
#define benar 1

//pilihan pencarian
#define IDCARI_ANAGRAM 0
#define IDCARI_POLA 1
#define IDCARI_PERBEDAAN 2
#define IDCARI_SUBANAGRAM 3
#define IDCARI_HURUF_PEMBENTUK 4
#define IDCARI_SUBPOLA 5
#define IDCARI_AMBIL_AWALAN 6
#define IDCARI_AMBIL_AKHIRAN 7

//IDMENU
#define IDM_KELUAR 1
//
#define IDURUT_ALFABET 11
#define IDURUT_PANJANG 12
#define IDURUT_NILAI 13
#define IDURUT_MUNDUR_ALFABET 14
#define IDURUT_MUNDUR_PANJANG 15
#define IDURUT_BALIK 16
#define ID_PALINDROM 17
#define ID_HURUF_UNIK 18
#define ID_HOOK_WORDS 19
#define ID_FRONT_HOOK 20
#define ID_BACK_HOOK 21
#define IDM_SEMUA_KATA 22
#define IDM_SALIN_DATA 23
#define IDM_BARU 24
#define IDM_SIMPAN 25
#define IDM_POTONG 26
#define IDM_SALIN 27
#define IDM_TEMPEL 28
#define IDM_HAPUS 29
//

//Pengurutan
#define IDURUT_ALFABET 11
#define IDURUT_PANJANG 12
#define IDURUT_NILAI 13
#define IDURUT_MUNDUR_ALFABET 14
#define IDURUT_MUNDUR_PANJANG 15
#define IDURUT_BALIK 16

//tinggi bagian tombol daftar
#define TINGGI_BARIS_DAFTAR 18
#define LEBAR_SCROLLBAR 20
#define TINGGI_KEPALA_DAFTAR 24
//IDMENU
#define IDM_KELUAR 1
//status window
#define STATUS_AWAL 0
#define STATUS_MENUNGGU 101
#define MENU_DITAMPILKAN 102
#define PILIHAN_DITAMPILKAN 103

//nomor kolom
#define IDKOLOM_FHOOK 0
#define IDKOLOM_KATA 1
#define IDKOLOM_BHOOK 2

//jenis tombol
#define TB_TOMBOL_TEKAN 1
#define TB_TULISAN 2
#define TB_DAFTARKU 3
#define TB_NAMA 4
#define TB_STATUS 5
#define TB_PILIHAN 6

//nomor tombol
#define ID_KATA_KATA 1
#define ID_DAFTAR 2
#define ID_CARI_SEMUA 3
#define ID_CARI_DALAM_HASIL 4
#define ID_CARI_DAN_GABUNGKAN 5
#define ID_BUKA_BERKAS 6
#define ID_DAFTAR_BERKAS 7
#define ID_STATUS 8
#define ID_TAMBAHAN_HURUF 9
#define ID_JENIS_PENCARIAN 10
#define ID_MIN 11
#define ID_MAX 12
#define ID_TUKAR_KOLOM 13
#define ID_KATA_KAMUS 14
#define ID_KETERANGAN 15
#define ID_TAB0 20
#define ID_TAB1 21
#define ID_TAB2 22
#define ID_TAB3 23

//status daftar
#define DAFTAR_TURUN 1
#define DAFTAR_NAIK 2
#define DAFTAR_TURUN_HALAMAN 3
#define DAFTAR_NAIK_HALAMAN 4
#define DAFTAR_KEDIP_TURUN 5
#define DAFTAR_KEDIP_NAIK 6
#define DAFTAR_SCROLLBAR 7

//type
typedef char stringku[51];

//deklarasi struct

struct Menuku{
    int id;
    int x, y, w, h;
    char *nama;
    SDL_Surface *gambar_menu;
    struct Menuku *batas;
    struct Menuku *pilihan;
    struct Menuku *ortu;
    struct Menuku *sebelumnya;
    struct Menuku *berikutnya;
};

struct teksku{
    stringku isi;
    int x_wcard;
    int panjang;
};

struct dataku{
    int fhook;
    int bhook;
    struct teksku teks[5];
    struct tabku *ctab;
    struct dataku *asli_berikutnya;
    struct dataku *berikutnya;
    struct dataku *sebelumnya;
};

struct tombolku{
    int x, y, cx, cy;
    int id;
    int pos;
    int jdata;
    int jenis;
    int jkolom;
    int status;
    int jtampil;
    int spesial;
    int yscrollbar;
    int hscrollbar;
    int kolom_utama;
    char perbaharui;
    char tulisan[256];
    SDL_Surface *gdilepas;
    SDL_Surface *gditekan;
    SDL_Surface *gdilewati;
    SDL_Surface *cgambar;
    struct dataku batas_pertama;
    struct dataku *bawah;
    struct dataku *pilihan;
    struct dataku *atas_aktif;
};

struct tabku{
    struct tombolku *tombol_aktif;
    struct tombolku tombol[20];
    int id;
    int jenis;
    int jtombol;
};

struct gambarku{
    SDL_Surface *panah;
};

struct Windowku{
    int waktu;
    int status;
    int proses;
    int selesai;
    int tombol_ditekan;
    struct tombolku *tombol_dilewati;
    struct gambarku gambar;
    struct Menuku *menu_pertama;
    struct Menuku *menu_aktif;
    struct Menuku *menu_dtkata;
    struct Menuku *menu_teks;
    SDL_Window *cwindow;
    SDL_Surface *layar;
    SDL_Color warna;
    TTF_Font *huruf;
    struct tabku *ctab;
    struct tabku *ltab;
    struct tabku tab[5];
    struct Windowku *berikutnya;
};

//utama.cpp
int loop_utama(SDL_Event *e, struct Windowku *mwindow);
int twelka_atur_status(struct Windowku *mwindow);

//bersih_bersih.cpp
int bersihkan_menu(struct Menuku* cmenu);
int bersihkan_tab(struct tabku *ctab);
int bersihkan_data_daftar(struct tombolku *tombol);

//fungsi_gambar.cpp
SDL_Surface *tambah_gambar(const char *nama_file);
SDL_Surface *buat_lapisan(int panjang, int tinggi);
int gambar_layar(struct Windowku *mwindow, SDL_Surface *latar);
int gambar_tulisan(SDL_Surface *latar, TTF_Font *huruf, char *s, SDL_Color warna, int x, int y);
int gambar_kotak(SDL_Surface *layar, int x, int y, int panjang, int tinggi, int r, int g, int b);
int tampilkan_gambar(SDL_Surface *latar, SDL_Surface *gambar, int x1, int y1, int x2, int y2, int w, int h);

//fungsi_tombol.cpp
struct tombolku *tombol_yang_dilewati(tabku *xtab, int x, int y);
struct tombolku *dapatkan_tombol(struct tabku *ctab, int id);
int perbaharui_tombol(struct Windowku *mwindow, struct tabku *xtab, char semua);

//fungsi_data.cpp
int naikkan_halaman(tombolku *tombol, struct dataku *batas, int langkah);
int turunkan_halaman(tombolku *tombol, struct dataku *batas, int langkah);
int ganti_isi_data(struct dataku* data, int pkolom, char* kata);
struct dataku *buat_batas_data(int panjang, int n);
int pindah_data(struct tombolku *tombol, int scode);
int bersihkan_berkas(struct Windowku *mwindow);
int bersihkan_daftar_berkas(struct tombolku *tombol);
struct dataku *pindah_posisi(struct tombolku *tombol, int pos);

//fungsi_dasar.cpp
struct tabku *buat_dialog(struct Windowku* mwindow);
int isi_daftar_berkas(struct tombolku *tombol);
SDL_Surface *mulai_program(struct Windowku *mwindow);

//fungsi_pengurutan.cpp
int balikkan_susunan(struct dataku *batas);
int kembalikan_susunan_awal(struct tombolku *tombol, struct dataku *batas);
int urutkan_alfabet(struct dataku *batas, int posisi, int indeks);
int urutkan_mundur_alfabet(struct dataku *batas, int posisi, int indeks);
int urutkan_panjang(struct dataku *batas, char lanjut, char terbalik, int indeks);
int urutkan_nilai(struct dataku *batas, char lanjut, char terbalik, int indeks);
int urutkan_data(struct tombolku *tdaftar, int id_pengurutan, int id_kolom);
int urut_huruf(char *s);

//fungsi_pencarian_kata.cpp
int cari_kata(struct Windowku *mwindow, int jenis);

//kamus.cpp
int bukakamus(struct tombolku *daftar, char *namafile, int jkolom);
struct tabku *tab_baru(struct Windowku *mwindow, char *folder, char *namafile);
int aksi_klik_tombol(struct Windowku *mwindow, struct tombolku* ctombol, int x, int y);

//event_mouse.cpp
int mouse_dilepas(struct Windowku *mwindow, struct tabku *xtab, int x, int y, int klik);
int mouse_ditekan(struct Windowku *mwindow, struct tabku *xtab, int x, int y, int klik);
int mouse_bergerak(struct Windowku *mwindow, struct tabku *xtab, int x, int y);

//stringku.cpp
int str_panjang(char s[]);
int str_salin(char s1[], char s2[]);
int str_bandingkan(char s1[], char s2[]);
int pisahkan(char *s, char *kata1, char *kata2, char *kata3, char *kata4, char c);
char* hurufbesar(char* s);

//fungsi_menu.cpp
struct Menuku *buat_menu(struct Menuku* ortu, char *nama, int id, TTF_Font *huruf);
int tampilkan_menu(struct Windowku *mwindow, struct Menuku *cmenu, int x, int y);
int aksi_klik_menu(struct Windowku *mwindow, int id);
int gambar_menu(TTF_Font *huruf, struct Menuku *mmenu);

//Daftar kata
int bukadaftarkata(struct tombolku *daftar, char *namafile);
int isi_hook_letter(struct tombolku *daftar);
int dapatkan_nilai(char *kata);

//fungsi_lexicon.cpp
int urut_huruf(char *s);
int hook_words(struct tombolku *tombol);
int back_hook_words(struct tombolku * tombol);
int front_hook_words(struct tombolku * tombol);
int cari_kata_unik(struct tombolku *tombol, int id_kolom);
int cari_palindrom(struct tombolku *tombol, int id_kolom);

//tombol.cpp
struct tombolku *buat_tombol(struct Windowku *mwindow, int jenis, char *nama, char *sgambar, int x, int y, int w, int h, int id, int jkolom);
int susun_tulisan(struct Windowku *mwindow, struct tombolku *tombol);
int ubah_tulisan(struct tombolku *tombol, int scode, int mod);
int susun_tombol_tekan(struct Windowku *mwindow, tombolku *tombol, struct tabku *xtab);
struct dataku *tambah_data_daftar(struct tombolku *daftar);
int daftar_posisi_atas(struct tombolku *tdaftar, struct dataku *batas);
int daftar_posisi_bawah(struct tombolku *tdaftar, struct dataku *batas);
int daftar_susun(struct Windowku *mwindow, tombolku *tombol);
int susun_judul_daftar(struct Windowku *mwindow, struct tombolku *daftar);
int susun_status(struct Windowku *mwindow, struct tombolku *tombol);
int dapatkan_posisi_pilihan(struct tombolku *tombol);
struct dataku *tambah_pilihan(tombolku *tombol, char *isi);
int tambah_pilihan_angka(tombolku *tombol, int awal, int akhir);
int tambah_pilihan_berkas(tombolku *tombol, char* nama_file);
int susun_pilihan(struct Windowku *mwindow, struct tombolku *tombol);

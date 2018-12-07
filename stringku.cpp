#include "main.h"

int pisahkan(char *s, char *kata1, char *kata2, char *kata3, char *kata4, char c){
int i=0;
int j=0;
int jkolom=0;
    if(s[0]!=0)jkolom++;
    while(s[i]!=0 && s[i]!=':'){
        kata1[i]=s[i];
        i++;
    }
    kata1[i]=0;

    if(s[i]!=0){
        j=0;
        if(s[i]!=0)i++;
        while(s[i]!=0 && s[i]!=':'){
            kata2[j]=s[i];
            i++;
            j++;
        }
        kata2[j]=0;
        jkolom++;
    }

    if(s[i]!=0){
        j=0;
        if(s[i]!=0)i++;
        while(s[i]!=0 && s[i]!=':'){
            kata3[j]=s[i];
            i++;
            j++;
        }
        kata3[j]=0;
        jkolom++;
    }
    if(s[i]!=0){
        j=0;
        if(s[i]!=0)i++;
        while(s[i]!=0 && s[i]!=':'){
            kata4[j]=s[i];
            i++;
            j++;
        }
        kata4[j]=0;
        jkolom++;
    }
    return jkolom;
}

int str_salin(char s1[], char s2[]){
int i=0;
    if(s1!=0 && s2!=0){
        i=0;
        while(s2[i]!=0){
            s1[i]=s2[i];
            i++;
        }
    }
    s1[i]=0;
    return 0;
}

int str_panjang(char s[]){
int i=0;
    if(s!=0){
        while(s[i]!=0){
            i++;
        }
    }
    return i;
}

int str_bandingkan(char s1[], char s2[]){
int i=0;
int hasil=-1;
    if(s1!=0 && s2!=0){
        i=0;
        while(s1[i]==s2[i] && s1[i]!=0){
            i++;
        }
        if(s1[i]==0){
            hasil=1;
        }else hasil=0;
    }
    return hasil;
}

char* hurufbesar(char* s){
    unsigned int i=0;
    char selisih='a'-'A';

    for (i=0;i<strlen(s);i++) {
        if(s[i]>='a' && s[i]<='z')s[i] = s[i]-selisih;
    }

    return s;
}

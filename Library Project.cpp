#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_KISI_SAYISI 50
#define MAX_KITAP_SAYISI 50

typedef enum{
	ogrenci=0,calisan=1
}kisiYetkiSeviyeleri;

typedef struct{
	char *kisiAdi;
	char *kisiSoyadi;
	int kutuphaneID;
	int sifre;
	kisiYetkiSeviyeleri kisiYetkisi;
}kisiBilgileri;

typedef struct{
	char *kitapAdi;
	char *kitapYazarAdi;
	char *kitapYazarSoyadi;
	char *yayinEvi;
	int sayfaSayisi;
	int kitapDurumu;
}kitapBilgileri;

int kisiSorgula(kisiBilgileri*uyeListesi,int ID){
	int i;
	for(i=0;i<MAX_KISI_SAYISI;i++){
		if(uyeListesi[i].kutuphaneID==ID){
			return ID;//bu ID daha once kullanildi
		}
	}
	return -1;
}

int kayitOl(kisiBilgileri*uyeListesi){
	int i,kayitYapilacakIndex,ID,sifre;
	char kisiAdi[20],kisiSoyadi[20],ch;
	for(i=0;i<MAX_KISI_SAYISI;i++){
		if(uyeListesi[i].kutuphaneID==0){
			kayitYapilacakIndex=i;
			break;
		}
	}
	
	ID=rand()%100000+1;
	if(kisiSorgula(uyeListesi,ID!=-1)){
		printf("Bu ID degeri daha once kullanilmistir..Kayit yapilamiyor..\n");
		exit(1);
	}
	
	printf("ID numaraniz %d olarak belirlenmistir.",ID);
	uyeListesi[kayitYapilacakIndex].kutuphaneID=ID;
	
	printf("Lutfen sirasiyla ad-soyad bilginizi giriniz:");
	scanf("%s%s",&kisiAdi,&kisiSoyadi);
	
	uyeListesi[kayitYapilacakIndex].kisiAdi=(char*)malloc(sizeof(char)*(strlen(kisiAdi)+1));
	uyeListesi[kayitYapilacakIndex].kisiSoyadi=(char*)malloc(sizeof(char)*(strlen(kisiSoyadi)+1));
	strcpy(uyeListesi[kayitYapilacakIndex].kisiAdi,kisiAdi);
	strcpy(uyeListesi[kayitYapilacakIndex].kisiSoyadi,kisiSoyadi);
	
	printf("Lutfen ogrenciyseniz '0'calisansaniz 'C'giriniz:");
	fflush(stdin);
	ch=getchar();
	if(ch=='0'){
		uyeListesi[kayitYapilacakIndex].kisiYetkisi=ogrenci;
	}
	else{
		uyeListesi[kayitYapilacakIndex].kisiYetkisi=calisan;
	}
	printf("Lutfen sifrenizi giriniz:");
	scanf("%d",&uyeListesi[kayitYapilacakIndex].sifre);
	
	return uyeListesi[kayitYapilacakIndex].kisiYetkisi;
}

int main(void){
	kitapBilgileri *kitaplik;
	kisiBilgileri *uyeListesi;
	kisiYetkiSeviyeleri uyeYetkisi;
	int girisDurumu;
	char ch;
	
	kitaplik=(kitapBilgileri*)calloc(MAX_KITAP_SAYISI,sizeof(kitapBilgileri));
	uyeListesi=(kisiBilgileri*)calloc(MAX_KISI_SAYISI,sizeof(kisiBilgileri));
	
	//uyeleriAktar(uyeListesi);
	//kitaplariAktar(kitaplik);
	
	//KAYIT OL,G�R�S YAP;
	printf("\t\tMerhaba,Kutuphane Sistemimize Hosgeldiniz\n");
	printf("1.Sisteme Kayit Olmak �stiyorsaniz 'K'Tuslayiniz:\n 2.Sisteme Giris Yapmak �stiyorsaniz 'G'Tuslayiniz:");
	fflsuh(stdin);
	ch=getchar();
	if(ch=='K'||ch=='k'){
		girisDurumu=kayitOl(uyeListesi);//ogrenci mi,yoksa calisan mi.
	}
	else if(ch=='G'||ch=='g'){
		girisDurumu=girisYap(uyeListesi);//ogrenci mi yoksa calisan mi.
		if(girisDurumu==-1){
			printf("Sifrenizi yanlis girdiniz..Giris yapilamiyor.\n");
			exit(1);
		}
		else if(girisDurumu==2){
			printf("Boyle bir ID degeri sistemde kayitli degil..Giris yapilamiyor.\n");
			exit(1);
		}
	}
	else{
		printf("Yanlis bir tuslama yaptiniz..Sistemden cikiliyor.\n");
		exit(1);
	}
	
	if(girisDurumu==1){
		uyeYetkisi=calisan;
	}
	else{
		uyeYetkisi=ogrenci;
	}
	
	if(uyeYetkisi==ogrenci){
		do{
			printf("1. Tum kitaplari goruntulemek icin 'G'tuslayiniz:\n2.Kitap aramak icin 'A'tuslayiniz:\n3.Cikis yapmak icin 'Q'tuslayiniz:");
			fflush(stdin);
			ch=getchar();
			switch(ch){
				case 'G':
				case 'g':
					kitaplariGoruntule(kitaplik);
					break;
				case 'A':
				case 'a':
					kitapAra(kitaplik);
				case 'Q':
				case 'q':	
					kitaplariYedekle(kitaplik);
					uyeleriYedekle(uyeListesi);
					printf("Cikis yapiliyor..");
					break;
				default:
					printf("Hatali tuslama yapildi..");
					break;
			}
		}while(ch!='Q');
	}
	else{
		do{
			printf("1.Kitap eklemek istiyorsaniz 'E'tuslayiniz:\n2.Tum uyeleri goruntulemek istiyorsaniz 'U'tuslayiniz:\n3.Cikis yapmak istiyorsaniz'Q'tuslayiniz:");
			fflush(stdin);
			ch=getchar();
				switch(ch){
				case 'G':
				case 'g':
					kitaplariGoruntule(kitaplik);
					break;
				case 'A':
				case 'a':
					kitapAra(kitaplik);
				case 'Q':
				case 'q':	
					kitaplariYedekle(kitaplik);
					uyeleriYedekle(uyeListesi);
					printf("Cikis yapiliyor..");
					break;
				default:
					printf("Hatali tuslama yapildi..");
					break;
			}
		}while(ch!='Q');
	}
	
	
	return 0;
}

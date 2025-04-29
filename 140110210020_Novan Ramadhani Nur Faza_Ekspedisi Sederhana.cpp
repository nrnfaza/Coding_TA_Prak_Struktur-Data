#include <iostream>
#include <iomanip>
#include <conio.h>
#include <string.h>
#define MAX 100

using namespace std;

struct admlog
{
    char r[MAX];
    string e;
};

struct Barang
{
    char namaPengirim[MAX],noPengirim[MAX];
    char namaPenerima[MAX],noPenerima[MAX];
    char alamat[MAX],jenis[MAX];
    int berat,volume;
    float jarak,ongkir;
    string bayar;
    long resi;
    Barang* nextBarang;
};

struct Kurir
{
    char infoKurir[MAX];
    Barang* firstBarang;
    Kurir* nextKurir;
};

struct Wilayah
{
    char infoWilayah[MAX];
    Kurir* firstKurir;
    Wilayah* next;
};

typedef Barang* PointerBarang;
typedef Kurir* PointerKurir;
typedef Wilayah* PointerWilayah;
typedef PointerWilayah ListWilayah;
ListWilayah ListWilayahA;
admlog al;

char key[MAX],keyKurir[MAX],keyWilayah[MAX];;
int n, found;
long keys;

void loading();

void menu();

void adlog();
void admin();

void CreateListWilayah();
void CreateElementWilayah(PointerWilayah& pbaru);
void CreateElementKurir(PointerKurir& pbaru);
void CreateElementBarang(PointerBarang& pbaru);
void InsertFirstWilayah(PointerWilayah pbaru);
void InsertFirstKurir(PointerKurir pbaru);
void InsertFirstBarang(PointerBarang pbaru);
void HitungOngkir(PointerBarang& pbaru);
void MetodeBayar(PointerBarang& pbaru,char jawab);
void noncod();
void InfoResi();
void traversal();

void kurir();
void displayBarang();
void antarBarang();

void pelanggan();

main()
{
    system("color 1B");
    loading();
    CreateListWilayah();
    system("color 3E");
    menu();
}

void delay(unsigned int time)
{
    clock_t goal = time + clock();
    while (goal > clock());
}

void loading()
{
    system("cls");
    for(int i=1;i<=50;i++)
    {
        system("cls");
        cout<<"\n\n\n\n\t\t\t\t   Loading "<<'\n'<<'\t'<<'\t';
        for(int j=1;j<=i;j++)
        cout<<"|";
        cout<<"\n\n\t "<<2*i<<"%";
        if( i > 1 && i < 20)
        cout<<"\n\n\tCreating Temporary files";
        else if( i > 20 && i<40)
        cout<<"\n\n\tAccessing Main Memory";
        else if(i >40 && i<48)
        cout<<"\n\n\tAccessing Cache";
        else
        cout<<"\n\n\tComplete to render No Fun Express. Press Enter to Continue ";
        delay(150 - i*3);
    }
    getch();
}

void menu()
{
    system("cls");
    do
    {
        cout<<"+============================+\n"
            <<"|       No Fun Express       |\n"
            <<"+============================+\n"
            <<"\n"
            <<"+==============================+\n"
            <<"| 1. Menu Admin                |\n"
            <<"| 2. Menu Kurir                |\n"
            <<"| 3. Menu Pelanggan            |\n"
            <<"| 4. Keluar                    |\n"
            <<"+==============================+\n"
            <<"\n Pilih Menu 1/2/3/4 : ";cin>>n;
        switch(n)
        {
        case 1:
            system("cls");
            adlog();
            break;
        case 2:
            system("cls");
            kurir();
            break;
        case 3:
            system("cls");
            pelanggan();
            break;
        case 4:
            system("cls");
            cout<<"\nTerima Kasih Sudah Menggunakan Jasa Kami"<<endl;
            break;
        default:
            cout<<"\nPILIHAN YANG ANDA MASUKAN TIDAK TERSEDIA"<<endl;
            getch();
            system("cls");
            break;

        }
    }
    while(n!=4);
    exit(0);
}

void adlog()
{
    system("cls");
    cout<<"+=============================+\n"
        <<"|          Login Admin        |\n"
        <<"+=============================+\n"
        <<"\n"
        <<"Input Username: ";cin>>al.r;
    cout<<"Input Password: ";cin>>al.e;
    if(al.e==strrev(al.r))
    {
        cout<<"Login Berhasil." <<endl;
        system("pause");
        system("cls");
        admin();
    }
    else
    {
        cout<<"Password yang Anda masukan salah. Silahkan ulang kembali."<<endl;
        getch();
        adlog();
    }
}

void admin()
{
    PointerWilayah pWilayah;
    PointerKurir pKurir;
    PointerBarang pBarang;


    do
    {
        system("cls");
        cout << "+===================+\n"
             << "|       ADMIN       |\n"
             << "+===================+\n"
             << "\n"
             << "+==============================+\n"
             << "| 1. Pendaftaran Wilayah       |\n"
             << "| 2. Pendaftaran Kurir         |\n"
             << "| 3. Pendaftaran Barang        |\n"
             << "| 4. Tampilkan Semua Paket     |\n"
             << "| 5. Cari Informasi Resi       |\n"
             << "| 6. Kembali ke Menu Utama     |\n"
             << "+==============================+\n"
             << "Masukan Pilihan 1/2/3/... : ";cin>>n;
        switch(n)
        {
        case 1:
            CreateElementWilayah(pWilayah);
            InsertFirstWilayah(pWilayah);
            cout<<"\nWilayah berhasil ditambahkan"<<endl;
            break;
        case 2:
            CreateElementKurir(pKurir);
            InsertFirstKurir(pKurir);
            break;
        case 3:
            CreateElementBarang(pBarang);
            InsertFirstBarang(pBarang);
            break;
        case 4:
            cout << "\nList Barang" << endl;
            traversal();
            break;
        case 5:
            InfoResi();
            break;
        case 6:
            cout << "\nAnda Kembali Ke Menu Utama" << endl;
            getch();
            menu();
            break;
        default:
            cout << "\nPilihan Tidak Tersedia" << endl;
            break;

        }getch();
    }
    while(n!=6);
}

void CreateListWilayah()
{
    ListWilayahA = NULL;
}

void CreateElementWilayah(PointerWilayah& pbaru)
{
    pbaru = new Wilayah;
    cout << "Masukan Wilayah : "; cin >> pbaru->infoWilayah;
    pbaru->next = NULL;
    pbaru->firstKurir = NULL;
}

void CreateElementKurir(PointerKurir& pbaru)
{
    pbaru = new Kurir;
    cout << "Masukan Kurir untuk Wilayah: "; cin >> key;
    cout << "Masukan Nama Kurir : "; cin >> pbaru->infoKurir;
    pbaru->nextKurir = NULL;
    pbaru->firstBarang=NULL;

}

void CreateElementBarang(PointerBarang& pbaru)
{
    pbaru = new Barang;
    char jawab;
    cout<<"---------------------Informasi Pengirim-------------------------"<<endl;
    cout<<"Nama Pengirim              : "; cin.ignore();cin.getline(pbaru->namaPengirim,sizeof(pbaru->namaPenerima));
    cout<<"Nomor Handphone Pengirim   : "; cin>>pbaru->noPengirim;
    cout<<"\n--------------------Informasi Penerima-------------------------"<<endl;
    cout<<"Nama Penerima              : "; cin.ignore(); cin.getline(pbaru->namaPenerima,sizeof(pbaru->namaPenerima));
    cout<<"Nomor Handphone Penerima   : "; cin>>pbaru->noPenerima;
    cout<<"Alamat Penerima Paket      : "; cin.ignore();cin.getline(pbaru->alamat,sizeof (pbaru->alamat));
    cout<<"\n---------------------Informasi Paket---------------------------"<<endl;
    cout<<"Jenis Barang               : "; cin>>pbaru->jenis;
    cout<<"Berat Barang (Kg)          : "; cin>>pbaru->berat;
    cout<<"Besar Barang (0/1/2)       : "; cin>>pbaru->volume;
    cout<<"Jarak        (Km)          : "; cin>>pbaru->jarak;
    srand(time(0));
    pbaru->resi =  rand();
    cout<<"No Resi                    : "<<pbaru->resi;
    HitungOngkir(pbaru);
    cout<<"\n---------------------Informasi Pembayaran----------------------"<<endl;
    cout<<"Ongkos Kirim                 : "<<pbaru->ongkir<<endl;
    cout<<"Apakah pembayaran COD? [Y/N] : "; cin>>jawab;
    cout<<"Nama Kurir                   : ";cin>>keyKurir;
    cout<<"Nama Wilayah                 : ";cin>>keyWilayah;
    cout<<endl;
    MetodeBayar(pbaru,jawab);
    pbaru->nextBarang=NULL;
}

void InsertFirstWilayah(PointerWilayah pbaru)
{
    if (ListWilayahA == NULL)
        ListWilayahA = pbaru;
    else
    {
        pbaru -> next = ListWilayahA;
        ListWilayahA = pbaru;
    }
}

void InsertFirstKurir(PointerKurir pbaru)
{
    PointerWilayah pWilayah = ListWilayahA;
    int found = 0;

    while(pWilayah!=NULL && found==0)
    {
        if(strcmp(pWilayah -> infoWilayah, key) == 0)
            found = 1;
        else
            pWilayah = pWilayah -> next;
    }
    if(found)
    {
        cout << "\nDitemukan" << endl;
        if(pWilayah->firstKurir == NULL)
        {
            pWilayah -> firstKurir = pbaru;
        }
        else
        {
            pbaru -> nextKurir = pWilayah -> firstKurir;
            pWilayah -> firstKurir = pbaru;
        }
        cout << "Berhasil ditambah" << endl;
    }
    else
    {
        cout << "\nWilayah tidak ditemukan" << endl;
        cout << "Tidak berhasil ditambah" << endl;
    }
}

void InsertFirstBarang(PointerBarang pbaru)
{
    PointerWilayah pWilayah;
    int ketemuWilayah;
    pWilayah=ListWilayahA;
    ketemuWilayah=0;
    while (pWilayah !=NULL && ketemuWilayah==0)
    {
        if ((strcmp(pWilayah->infoWilayah,keyWilayah))==0)
            ketemuWilayah=1;
        else
            pWilayah=pWilayah->next;
    }
    if(ketemuWilayah)
    {
        PointerKurir pKurir;
        int ketemuKurir;
        pKurir=pWilayah->firstKurir;
        ketemuKurir=0;
        while (pKurir !=NULL && ketemuKurir==0)
        {
            if ((strcmp(pKurir->infoKurir,keyKurir))==0)
                ketemuKurir=1;
            else
                pKurir=pKurir->nextKurir;
        }
        if(ketemuKurir)
        {
            if(pKurir->firstBarang==NULL)
            {
                pKurir->firstBarang=pbaru;
            }
            else
            {
                pbaru->nextBarang=pKurir->firstBarang;
                pKurir->firstBarang=pbaru;
            }
            cout<<"Data berhasil ditambahkan."<<endl;
        }
        else
            cout<<"Tidak ditemukan."<<endl;
    }
    else
    cout<<"Tidak ditemukan."<<endl;
}

void HitungOngkir(PointerBarang& pbaru)
{
    pbaru->ongkir=(pbaru->berat*3000)+(pbaru->volume*1000)+(pbaru->jarak*100);
}

void MetodeBayar(PointerBarang& pbaru,char jawab)
{
    if(jawab=='Y' || jawab=='y')
    {
        pbaru->bayar="COD";
    }
    else if(jawab=='N' || jawab=='n')
    {
        pbaru->bayar="Non COD";
        pbaru->ongkir=0;
        if(pbaru->bayar=="Non COD")
        {
            system("cls");
            cout<<"+=====================+\n"
                <<"    Cara Pembayaran    \n"
                <<"+=====================+\n"
                <<"  1. Tunai\n"
                <<"  2. Non Tunai\n"
                <<"+=====================+\n"
                <<"Masukan cara pembayaran : ";cin>>n;
            if(n==2)
            {
                system("cls");
                cout<<"+=====================+\n"
                    <<"    Cara Pembayaran    \n"
                    <<"+=====================+\n"
                    <<"  1. Debit\n"
                    <<"  2. E-Wallet\n"
                    <<"+=====================+\n"
                    <<"Masukan cara pembayaran : ";cin>>n;
            }
        }
    }
    else
    {
        cout<<"Pilihan Tidak Tersedia silahkan Masukan kembali pilihan\n"
            <<"Apakah pembayaran COD? [Y/N] : "; cin>>jawab;
        MetodeBayar(pbaru, jawab);
    }
}

void InfoResi()
{
    PointerWilayah pbantuWilayah = ListWilayahA;
    PointerKurir pbantuKurir;
    PointerBarang pcari;
    cout<<"\nMasukkan resi : "; cin>>keys;
    found=0;
    while(pbantuWilayah!=NULL && found==0)
    {
        pbantuKurir=pbantuWilayah->firstKurir;
        while(pbantuKurir!=NULL)
        {
            pcari=pbantuKurir->firstBarang;
            while(pcari!=NULL && found==0)
            {
                if(pcari->resi==keys)
                {
                    found=1;
                }
                else
                {
                    pcari=pcari->nextBarang;
                }
            }
            pbantuKurir=pbantuKurir->nextKurir;
        }
        pbantuWilayah=pbantuWilayah->next;
    }
    if(found==1)
    {
        system("cls");
        cout<<"\nBarang ditemukan."<<endl;
        cout<<"\n---------------------Informasi Pengirim-------------------------"<<endl;
        cout<<"Nama Pengirim              : "; cout<<pcari->namaPengirim<<endl;
        cout<<"Nomor Handphone Pengirim   : "; cout<<pcari->noPengirim<<endl;
        cout<<"\n---------------------Informasi Penerima-------------------------"<<endl;
        cout<<"Nama Penerima              : "; cout<<pcari->namaPenerima<<endl;
        cout<<"Nomor Handphone Penerima   : "; cout<<pcari->noPenerima<<endl;
        cout<<"Alamat Pengiriman Paket    : "; cout<<pcari->alamat<<endl;
        cout<<"\n-----------------------Informasi Paket--------------------------"<<endl;
        cout<<"Jenis Barang               : "; cout<<pcari->jenis<<endl;
        cout<<"Berat Barang (Kg)          : "; cout<<pcari->berat<<endl;
        cout<<"Besar Barang (0/1/2)       : "; cout<<pcari->volume<<endl;
        cout<<"Jarak        (Km)          : "; cout<<pcari->jarak<<endl;
        cout<<"\n---------------------Informasi Pembayaran-----------------------"<<endl;
        cout<<"Ongkos Kirim               : "; cout<<pcari->ongkir<<endl;
        cout<<"Pembayaran                 : "; cout<<pcari->bayar<<endl;
    }
    else{cout<<"Barang tidak ditemukan."<<endl;}
}

void traversal()
{
    PointerWilayah pbantuWilayah = ListWilayahA;
    PointerKurir pbantuKurir;
    PointerBarang pbantuBarang;

    cout<<"--------------------------------------"<<endl;
    cout<<"WILAYAH        KURIR          RESI    "<<endl;
    cout<<"--------------------------------------"<<endl;
    while(pbantuWilayah!=NULL)
    {
        cout<<setiosflags(ios::left)<<setw(15)<<pbantuWilayah->infoWilayah;
        pbantuKurir=pbantuWilayah->firstKurir;
        while(pbantuKurir!=NULL)
        {
            cout<<setiosflags(ios::left)<<setw(15)<<pbantuKurir->infoKurir;
            pbantuBarang=pbantuKurir->firstBarang;
            while(pbantuBarang!=NULL)
            {
                cout<<setiosflags(ios::left)<<setw(10)<<pbantuBarang->resi;
                cout<<endl<<setiosflags(ios::left)<<setw(30)<<" ";
                pbantuBarang=pbantuBarang->nextBarang;
            }
            cout<<endl<<setiosflags(ios::left)<<setw(15)<<" ";
            pbantuKurir=pbantuKurir->nextKurir;
        }
        cout<<endl;
        pbantuWilayah=pbantuWilayah->next;
    }
}

void menkur()
{
    system("cls");
    cout << "+======================================+\n"
         << "               MENU KURIR               \n"
         << "+======================================+\n\n"
         << "  1. Daftar Barang\n"
         << "  2. Daftar Barang yang sudah diantar\n"
         << "  3. Keluar\n\n"
         << "Masukkan Pilihan: "; cin >> n;

    switch(n){
    case 1:
        displayBarang();
        getch();
        break;
    case 2:
        antarBarang();
        getch();
        break;
    case 3:
        menu();
        break;
    default:
        cout << "Pilihan tidak tersedia" << endl;}
}

void kurir()
{
    PointerWilayah pbantuWilayah = ListWilayahA;
    PointerKurir pbantuKurir;
    PointerBarang pbantuBarang;
    system("cls");
    cout << "Masukkan Nama Kurir    : "; cin >> key;
    found=0;
    while(pbantuWilayah!=NULL && found==0)
    {
        pbantuKurir=pbantuWilayah->firstKurir;
        while(pbantuKurir!=NULL && found==0)
        {
            if(strcmp(pbantuKurir->infoKurir, key) == 0){found=1;}
            else{pbantuKurir=pbantuKurir->nextKurir;}
        }
        pbantuWilayah=pbantuWilayah->next;
    }
    if(found==1)
    {
        menkur();
    }
    else
    {
        cout<<"Nama Kurir "<<key<<" tidak ditemukan"<<endl;
    }
    getch();
    menu();
}

void displayBarang()
{
    PointerWilayah pbantuWilayah = ListWilayahA;
    PointerKurir pbantuKurir;
    PointerBarang pbantuBarang;
    found=0;
    system("cls");
    while(pbantuWilayah!=NULL && found==0)
    {
        pbantuKurir=pbantuWilayah->firstKurir;
        while(pbantuKurir!=NULL && found==0)
        {
            if(strcmp(pbantuKurir->infoKurir, key) == 0){found=1;}
            else{pbantuKurir=pbantuKurir->nextKurir;}
        }
        pbantuWilayah=pbantuWilayah->next;
    }
    if(found==1)
    {
        if(pbantuKurir->firstBarang==NULL){
            cout<<"\nTidak ada barang yang harus diantar."<<endl;
        }
        else{
            pbantuBarang=pbantuKurir->firstBarang;
            cout << "Nama Penerima     No. HP         Alamat                                  Jenis Barang       Jenis Pembayaran      Harga         Nomor Resi  " << endl;
            cout << "============================================================================================================================================\n" << endl;
            do
            {
            cout << setiosflags(ios::left) << setw(18) << pbantuBarang->namaPenerima;
            cout << setiosflags(ios::left) << setw(15) << pbantuBarang->noPenerima;
            cout << setiosflags(ios::left) << setw(40) << pbantuBarang->alamat;
            cout << setiosflags(ios::left) << setw(19) << pbantuBarang->jenis;
            cout << setiosflags(ios::left) << setw(22) << pbantuBarang->bayar;
            cout << setiosflags(ios::left) << setw(14) << pbantuBarang->ongkir;
            cout << setiosflags(ios::left) << setw(12) << pbantuBarang->resi<<endl;
            pbantuBarang=pbantuBarang->nextBarang;
            }
            while(pbantuBarang!=NULL);
        }
    }
    getch();
    menkur();
}

void antarBarang()
{
    PointerWilayah pbantuWilayah = ListWilayahA;
    PointerKurir pbantuKurir, bantuKurir;
    PointerBarang pbantuBarang, pCari, bantuBarang, pHapus;
    system("cls");
    cout << "\nMasukkan nomor resi barang: "; cin>>keys;
    found=0;
    while(pbantuWilayah!=NULL && found==0)
    {
        pbantuKurir=pbantuWilayah->firstKurir;
        while(pbantuKurir!=NULL && found==0)
        {
            pbantuBarang=pbantuKurir->firstBarang;
            while(pbantuBarang!=NULL && found==0)
            {
                if(pbantuBarang->resi==keys)
                {
                    bantuKurir = pbantuKurir;
                    found=1;
                }
                else
                {
                    bantuBarang = pbantuBarang;
                    pbantuBarang=pbantuBarang->nextBarang;
                }
            }
            pbantuKurir=pbantuKurir->nextKurir;
        }
        pbantuWilayah=pbantuWilayah->next;
    }
    if(found==1)
    {
        pCari = pbantuBarang;
        cout<<"\n---------------------Informasi Pengirim-------------------------"<<endl;
        cout<<"Nama Pengirim              : "; cout<<pCari->namaPengirim<<endl;
        cout<<"Nomor Handphone Pengirim   : "; cout<<pCari->noPengirim<<endl;
        cout<<"\n---------------------Informasi Penerima-------------------------"<<endl;
        cout<<"Nama Penerima              : "; cout<<pCari->namaPenerima<<endl;
        cout<<"Nomor Handphone Penerima   : "; cout<<pCari->noPenerima<<endl;
        cout<<"Alamat Pengiriman Paket    : "; cout<<pCari->alamat<<endl;
        cout<<"\n-----------------------Informasi Paket--------------------------"<<endl;
        cout<<"Jenis Barang               : "; cout<<pCari->jenis<<endl;
        cout<<"Berat Barang (Kg)          : "; cout<<pCari->berat<<endl;
        cout<<"Besar Barang (0/1/2)       : "; cout<<pCari->volume<<endl;
        cout<<"Jarak        (Km)          : "; cout<<pCari->jarak<<endl;
        cout<<"\n---------------------Informasi Pembayaran-----------------------"<<endl;
        cout<<"Ongkos Kirim               : "; cout<<pCari->ongkir<<endl;
        cout<<"Pembayaran                 : "; cout<<pCari->bayar<<endl;
        cout<<"\nBarang dengan Nomor Resi "<<pCari->resi<<" sudah di antar"<<endl;
        if(pCari==bantuKurir->firstBarang)
        {
            if(pCari->nextBarang==NULL)
            {
                bantuKurir->firstBarang=NULL;
                delete pCari;
            }
            else
            {
                bantuKurir->firstBarang=bantuKurir->firstBarang->nextBarang;
                delete pCari;
            }
        }
        else if(pCari->nextBarang==NULL)
        {
            bantuBarang->nextBarang=NULL;
            delete pCari;
        }
        else
        {
            bantuBarang->nextBarang=pCari->nextBarang;
            delete pCari;
        }
    }
    else{cout << "Barang tidak ditemukan" << endl;}
    getch();
    menkur();
}

void pelanggan()
{
    PointerBarang pBarang;
    do
    {
        system("cls");
        cout << "+==========================================+\n"
             << "               MENU PELANGGAN               \n"
             << "+==========================================+\n\n"
             << "  1. Check Barang\n"
             << "  2. Pendaftaran Barang Online (kurir mengambil kerumah)\n"
             << "  3. Keluar\n\n"
             << "Masukkan Pilihan: "; cin >> n;
        switch(n)
        {
        case 1:
            InfoResi();
            break;
        case 2:
            CreateElementBarang(pBarang);
            InsertFirstBarang(pBarang);
            break;
        case 3:
            menu();
            break;
        default:
            cout << "Pilihan tidak tersedia" << endl;
        }getch();
    }
    while(n!=3);
}

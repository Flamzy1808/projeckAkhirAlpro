#include <iostream>
#include <iomanip>
using namespace std;

struct Produk{
    string nama;
    int id;
    int harga;
    int stok;
    Produk* next;
};

struct Riwayat {
    string nama;
    int terjual;
    int totalHarga;
    Riwayat* next;
};

Produk* head = NULL;
Riwayat* headRiwayat = NULL;

void lihatProduk();
void ascending(int opsi);
void descending(int opsi);
void swapData(Produk* a, Produk* b);
void tambahProduk();
void updateStok();
void hapusProduk();
void cariProduk();
void beliProduk();
void lihatRiwayat();
void hapusSemuaProdukList(); 

void admin(){
    int pilihAdmin;
    string username, password;
    cout << "Masukkan Username: "; cin >> username;
    cout << "Masukkan Password: "; cin >> password;
    if(username == "admin" && password == "admin123"){
        do{
            cout << "Dashboard Admin Toko Kelontong" << endl <<
            "1. Lihat Stok barang" << endl <<
            "2. Cari Produk" << endl <<
            "3. Tambah Barang" << endl <<
            "4. Update Stok" << endl <<
            "5. Hapus Produk" << endl <<
            "6. Kembali ke menu utama" << endl <<
            "Pilih menu: "; cin >> pilihAdmin;
            switch(pilihAdmin) {
                case 1 : { lihatProduk(); break; }
                case 2 : { cariProduk(); break; }
                case 3 : { tambahProduk(); break; }
                case 4 : { updateStok(); break; }
                case 5 : { hapusProduk(); break; }
                case 6 : { return; }
                default : {
                    cout << "Nomor menu tidak valid! silahkan input ulang.." << endl;
                    break;
                }
            }
        }while(pilihAdmin != 6);
    }else{
        cout << endl << "Username atau password salah!" << endl;
        return;
    }
}

void user(){
    int pilihUser;
    do{
        cout << "Dashboard User Toko Kelontong" << endl;
        cout << "1. Lihat Semua Produk" << endl;
        cout << "2. Cari Produk" << endl;
        cout << "3. Beli Produk" << endl;
        cout << "4. Lihat Riwayat Belanja" << endl;
        cout << "5. Keluar" << endl; 
        cout << "Pilih menu: "; cin >> pilihUser;
        switch(pilihUser) {
            case 1 : { lihatProduk(); break; }
            case 2 : { cariProduk(); break; }
            case 3 : { beliProduk(); break; }
            case 4 : { lihatRiwayat(); break; }
            case 5 : {
                cout << "terimakasih sudah menggunakan sistem toko kelontong" << endl;
                break;
            }
            default : {
                cout << "Pilihan tidak valid" << endl;
                break;
            }
        }
    }while(pilihUser != 5);
}

int main(){
    int pilihMenu;
    do{
        cout << "Selamat Datang! Silahkan pilih menu.." << endl;
        cout << "1. Admin" << endl;
        cout << "2. User" << endl;
        cout << "3. Keluar" << endl;
        cout << "Pilih menu: "; cin >> pilihMenu;
        if(pilihMenu == 1){
            admin();
        }else if(pilihMenu == 2){
            user();
        }else if(pilihMenu == 3){
            cout << "Selamat Tinggal..." << endl;
            return 0;
        }else{
            cout << "Pilihan tidak valid!" << endl;
        }
    }while(pilihMenu != 3);
} 

void hapusSemuaProdukList() {
    while(head != NULL) {
        Produk* temp = head;
        head = head->next;
        delete temp;
    }
}

void swapData(Produk* a, Produk* b) {
    string tempNama = a->nama;
    int tempHarga = a->harga;
    int tempStok = a->stok;
    
    a->nama = b->nama; a->harga = b->harga; a->stok = b->stok;
    b->nama = tempNama; b->harga = tempHarga; b->stok = tempStok;
}


void tambahProduk(){
    FILE *ProjectAkhir = fopen("data_produk.txt", "a");
    if (!ProjectAkhir){
        cout << "Gagal membuka file!" << endl;
        return;
    }
    Produk produk;
    cout << "MENU TAMBAH PRODUK" << endl;
    cout << "Nama produk      : "; cin >> produk.nama;
    cout << "Stok             : "; cin >> produk.stok;
    cout << "Harga per pieces : "; cin >> produk.harga;
    
    fprintf(ProjectAkhir, "%s %d %d\n", produk.nama.c_str(), produk.stok, produk.harga);
    fclose(ProjectAkhir);
    cout << endl << "Produk berhasil ditambahkan!" << endl << endl;
}

void lihatProduk(){
    int pilih, pilihUrut;

    cout << "=== LIHAT PRODUK ===" << endl;
    cout << "1. Berdasarkan Nama" << endl;
    cout << "2. Berdasarkan Harga" << endl;
    cout << "3. Berdasarkan Stok" << endl;
    cout << "Pilih : "; cin >> pilih;

    cout << endl;
    cout << "1. Ascending" << endl;
    cout << "2. Descending" << endl;
    cout << "Pilih : "; cin >> pilihUrut;

    if(pilihUrut == 1){
        ascending(pilih);
    }else if(pilihUrut == 2){
        descending(pilih);
    }else{
        cout << "Pilihan tidak tersedia!" << endl;
    }
}

void ascending(int opsi){
    hapusSemuaProdukList(); 
    char tempNama[100];
    int tempStok, tempHarga;

    FILE *ProjectAkhir = fopen("data_produk.txt", "r");
    if (!ProjectAkhir){
        cout << "Gagal membuka file!" << endl;
        return;
    }

    while(fscanf(ProjectAkhir, "%s %d %d", tempNama, &tempStok, &tempHarga) != EOF){
        Produk* baru = new Produk{tempNama, 0, tempHarga, tempStok, NULL};
        if(head == NULL) head = baru;
        else {
            Produk* temp = head;
            while(temp->next != NULL) temp = temp->next;
            temp->next = baru;
        }
    }
    fclose(ProjectAkhir);

    if(head != NULL) {
        bool ditukar;
        Produk* ptr1;
        Produk* lptr = NULL;
        do {
            ditukar = false;
            ptr1 = head;
            while(ptr1->next != lptr) {
                bool tukar = false;
                if(opsi == 1 && ptr1->nama > ptr1->next->nama) tukar = true;
                else if(opsi == 2 && ptr1->harga > ptr1->next->harga) tukar = true;
                else if(opsi == 3 && ptr1->stok > ptr1->next->stok) tukar = true;

                if(tukar) {
                    swapData(ptr1, ptr1->next);
                    ditukar = true;
                }
                ptr1 = ptr1->next;
            }
            lptr = ptr1;
        } while(ditukar);
    }

    cout << endl;
    cout << left << setw(15) << "Nama"
         << setw(10) << "Stok"
         << setw(10) << "Harga" << endl;
         
    Produk* tempPrint = head;
    while(tempPrint != NULL){
        cout << left << setw(15) << tempPrint->nama
             << setw(10) << tempPrint->stok
             << setw(10) << tempPrint->harga << endl;
        tempPrint = tempPrint->next;
    }
}

void descending(int opsi){
    hapusSemuaProdukList();
    char tempNama[100];
    int tempStok, tempHarga;

    FILE *ProjectAkhir = fopen("data_produk.txt", "r");
    if (!ProjectAkhir){
        cout << "Gagal membuka file!" << endl;
        return;
    }

    while(fscanf(ProjectAkhir, "%s %d %d", tempNama, &tempStok, &tempHarga) != EOF){
        Produk* baru = new Produk{tempNama, 0, tempHarga, tempStok, NULL};
        if(head == NULL) head = baru;
        else {
            Produk* temp = head;
            while(temp->next != NULL) temp = temp->next;
            temp->next = baru;
        }
    }
    fclose(ProjectAkhir);
    
    if(head != NULL) {
        bool ditukar;
        Produk* ptr1;
        Produk* lptr = NULL;
        do {
            ditukar = false;
            ptr1 = head;
            while(ptr1->next != lptr) {
                bool tukar = false;
                if(opsi == 1 && ptr1->nama < ptr1->next->nama) tukar = true;
                else if(opsi == 2 && ptr1->harga < ptr1->next->harga) tukar = true;
                else if(opsi == 3 && ptr1->stok < ptr1->next->stok) tukar = true;

                if(tukar) {
                    swapData(ptr1, ptr1->next);
                    ditukar = true;
                }
                ptr1 = ptr1->next;
            }
            lptr = ptr1;
        } while(ditukar);
    }

    cout << endl;
    cout << left << setw(15) << "Nama"
         << setw(10) << "Stok"
         << setw(10) << "Harga" << endl;
         
    Produk* tempPrint = head;
    while(tempPrint != NULL){
        cout << left << setw(15) << tempPrint->nama
             << setw(10) << tempPrint->stok
             << setw(10) << tempPrint->harga << endl;
        tempPrint = tempPrint->next;
    }
}

void updateStok(){
    hapusSemuaProdukList();
    string namaCari;
    bool ditemukan = false;
    char tempNama[100];
    int tempStok, tempHarga;

    FILE *ProjectAkhir = fopen("data_produk.txt", "r");
    if(!ProjectAkhir){
        cout << "Gagal membuka file!" << endl;
        return;
    }

    cout << "Masukkan nama produk yang ingin diupdate: "; cin >> namaCari;
    
    while(fscanf(ProjectAkhir, "%s %d %d", tempNama, &tempStok, &tempHarga) != EOF){
        string strNama = tempNama;
        if(namaCari == strNama){
            ditemukan = true;
            cout << "Stok lama : " << tempStok << endl;
            cout << "Masukkan stok baru: "; cin >> tempStok;
        }
        Produk* baru = new Produk{strNama, 0, tempHarga, tempStok, NULL};
        if(head == NULL) head = baru;
        else {
            Produk* tempLL = head;
            while(tempLL->next != NULL) tempLL = tempLL->next;
            tempLL->next = baru;
        }
    }
    fclose(ProjectAkhir);

    FILE *FileTemp = fopen("temp.txt", "w");
    Produk* tempTulis = head;
    while(tempTulis != NULL){
        fprintf(FileTemp, "%s %d %d\n", tempTulis->nama.c_str(), tempTulis->stok, tempTulis->harga);
        tempTulis = tempTulis->next;
    }
    fclose(FileTemp);

    if(ditemukan){
        remove("data_produk.txt");
        rename("temp.txt", "data_produk.txt");
        cout << "Stok produk berhasil diupdate!" << endl;
    }else{
        remove("temp.txt");
        cout << "Produk tidak ditemukan!" << endl;
    }
}

void hapusProduk(){
    hapusSemuaProdukList();
    string namaHapus;
    bool ditemukan = false;
    char tempNama[100];
    int tempStok, tempHarga;

    FILE *ProjectAkhir = fopen("data_produk.txt", "r");
    if(!ProjectAkhir){
        cout << "Gagal membuka file!" << endl;
        return;
    }
    
    cout << "Masukkan nama produk yang ingin dihapus: "; cin >> namaHapus;
    
    while(fscanf(ProjectAkhir, "%s %d %d", tempNama, &tempStok, &tempHarga) != EOF){
        string strNama = tempNama;
        if(strNama != namaHapus){
            Produk* baru = new Produk{strNama, 0, tempHarga, tempStok, NULL};
            if(head == NULL) head = baru;
            else {
                Produk* tempLL = head;
                while(tempLL->next != NULL) tempLL = tempLL->next;
                tempLL->next = baru;
            }
        }else{
            ditemukan = true;
        }
    }
    fclose(ProjectAkhir);
    
    FILE *FileTemp = fopen("temp.txt", "w");
    Produk* tempTulis = head;
    while(tempTulis != NULL){
        fprintf(FileTemp, "%s %d %d\n", tempTulis->nama.c_str(), tempTulis->stok, tempTulis->harga);
        tempTulis = tempTulis->next;
    }
    fclose(FileTemp);

    if(ditemukan){
        remove("data_produk.txt");
        rename("temp.txt", "data_produk.txt");
        cout << "Produk '" << namaHapus << "' berhasil dihapus!" << endl;
    }else{
        remove("temp.txt");
        cout << "Produk dengan nama tersebut tidak ditemukan." << endl;
    }
}

void cariProduk(){
    hapusSemuaProdukList();
    string cariProduk;
    bool cekCari = false;
    char tempNama[100];
    int tempStok, tempHarga;

    FILE *ProjectAkhir = fopen("data_produk.txt", "r");
    if (!ProjectAkhir){
        cout << "Gagal membuka file!" << endl;
        return;
    }
    cout << "Masukkan nama produk yang akan dicari: "; cin >> cariProduk;
    
    // tarik file ke LL
    while(fscanf(ProjectAkhir, "%s %d %d", tempNama, &tempStok, &tempHarga) != EOF){
        Produk* baru = new Produk{tempNama, 0, tempHarga, tempStok, NULL};
        if(head == NULL) head = baru;
        else {
            Produk* tempLL = head;
            while(tempLL->next != NULL) tempLL = tempLL->next;
            tempLL->next = baru;
        }
    }
    fclose(ProjectAkhir);

    // cari dari LL
    Produk* tempCari = head;
    while(tempCari != NULL){
        if(tempCari->nama == cariProduk){
            cout << endl <<
            "Nama  : " << tempCari->nama << endl <<
            "Harga : " << tempCari->harga << endl <<
            "Stok  : " << tempCari->stok << endl;
            cekCari = true;
        }
        tempCari = tempCari->next;
    }
    
    if(cekCari == false){
        cout << endl << "Produk dengan nama tersebut tidak ditemukan" << endl;
    }
}

void beliProduk(){
    hapusSemuaProdukList();
    string namaProduk;
    cout << "Masukkan nama produk: ";
    cin >> namaProduk;

    char tempNama[100];
    int tempStok, tempHarga;
    FILE* fileProduk = fopen("data_produk.txt", "r");
    if (!fileProduk) {
        cout << "Belum ada data produk!\n";
        return;
    }
    
    while(fscanf(fileProduk, "%s %d %d", tempNama, &tempStok, &tempHarga) != EOF){
        Produk* baru = new Produk{tempNama, 0, tempHarga, tempStok, NULL};
        if(head == NULL) head = baru;
        else {
            Produk* t = head;
            while(t->next != NULL) t = t->next;
            t->next = baru;
        }
    }
    fclose(fileProduk);

    Produk* ptrBeli = head;
    while(ptrBeli != NULL){
        if(ptrBeli->nama == namaProduk) break;
        ptrBeli = ptrBeli->next;
    }

    if (ptrBeli == NULL) {
        cout << "Produk tidak ditemukan!\n";
        return;
    }

    int jumlahBeli;
    cout << "Masukkan jumlah beli: ";
    cin >> jumlahBeli;

    if (jumlahBeli > ptrBeli->stok) {
        cout << "Stok tidak cukup! Stok tersedia: " << ptrBeli->stok << endl;
        return;
    }

    ptrBeli->stok -= jumlahBeli;
    int total = jumlahBeli * ptrBeli->harga;

    string namaPembeli;
    cout << "Masukkan nama pembeli: ";
    cin >> namaPembeli;

    // invoice
    cout << "=== INVOICE ===" << endl;
    cout << "Nama Pembeli : " << namaPembeli << endl;
    cout << "Produk       : " << ptrBeli->nama << endl;
    cout << "Jumlah       : " << jumlahBeli << endl;
    cout << "Total Harga  : Rp " << total << endl;

    // Update stok ke file (tulis ulang dari Linked List)
    FILE* fileTemp = fopen("temp.txt", "w");
    Produk* tWrite = head;
    while(tWrite != NULL){
        fprintf(fileTemp, "%s %d %d\n", tWrite->nama.c_str(), tWrite->stok, tWrite->harga);
        tWrite = tWrite->next;
    }
    fclose(fileTemp);
    remove("data_produk.txt");
    rename("temp.txt", "data_produk.txt");

    // nyimpen riwayat produk 
    FILE* fileRiwayat = fopen("riwayat.txt", "a");
    fprintf(fileRiwayat, "%s %d %d\n", ptrBeli->nama.c_str(), jumlahBeli, total);
    fclose(fileRiwayat);

    // nyimpen data pelanggan 
    FILE* filePelanggan = fopen("data_pelanggan.txt", "a");
    fprintf(filePelanggan, "%s %d\n", namaPembeli.c_str(), total);
    fclose(filePelanggan);

    // tambah ke linked list Riwayat 
    Riwayat* baruRiw = new Riwayat{namaPembeli, jumlahBeli, total, NULL};
    if (!headRiwayat) headRiwayat = baruRiw;
    else {
        Riwayat* tempRiw = headRiwayat;
        while (tempRiw->next) tempRiw = tempRiw->next;
        tempRiw->next = baruRiw;
    }

    cout << "Pembelian berhasil!" << endl;
}

void lihatRiwayat(){
    FILE *FileRiwayat = fopen("riwayat.txt", "r");
    if(!FileRiwayat){
        cout << "Belum ada riwayat transaksi atau gagal membuka file!" << endl;
        return;
    }

    char namaBarang[50];
    int terjual, totalHarga;

    cout << "=== RIWAYAT TRANSAKSI ===" << endl;
    cout << left << setw(20) << "Nama Produk" 
         << setw(15) << "Jumlah Beli" 
         << setw(15) << "Total Harga" << endl;
         
    while(fscanf(FileRiwayat, "%s %d %d", namaBarang, &terjual, &totalHarga) != EOF){
        cout << left << setw(20) << namaBarang 
             << setw(15) << terjual 
             << setw(15) << totalHarga << endl;
    }
    fclose(FileRiwayat);
    cout << endl;
}

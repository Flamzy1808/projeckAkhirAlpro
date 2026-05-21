#include <iostream>
#include <iomanip>
using namespace std;

struct Produk{
    char nama[50];
    int id;
    int harga;
    int stok;
};

void lihatProduk();
void ascending(int opsi);
void descending(int opsi);
void tambahProduk();
void updateStok();
void hapusProduk();
void cariProduk();

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
                case 1 : {
                    lihatProduk();
                    break;
                }
                case 2 : {
                    cariProduk();
                    break;
                }
                case 3 : {
                    tambahProduk();
                    break;
                }
                case 4 : {
                    updateStok();
                    break;
                }
                case 5 : {
                    hapusProduk();
                    break;
                }
                case 6 : {
                    return;
                }
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

void tambahProduk(){
    FILE *ProjectAkhir = fopen("data_produk.txt", "a");
    if (!ProjectAkhir){
        cout << "Gagal membuka file!" << endl;
        system("pause");
        return;
    }
    Produk produk;
    cout << "MENU TAMBAH PRODUK" << endl;
    cout << "Nama produk      : "; cin >> produk.nama;
    cout << "Stok             : "; cin >> produk.stok;
    cout << "Harga per pieces : "; cin >> produk.harga;
    fprintf(ProjectAkhir, "%s %d %d\n", produk.nama, produk.stok, produk.harga);
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
    Produk produk[100], temp;
    int jumlah = 0;

    FILE *ProjectAkhir = fopen("data_produk.txt", "r");
    if (!ProjectAkhir){
        cout << "Gagal membuka file!" << endl;
        system("pause");
        return;
    }

    while(fscanf(ProjectAkhir, "%s %d %d", produk[jumlah].nama, &produk[jumlah].stok, &produk[jumlah].harga) != EOF){
        jumlah++;
    }
    if(opsi == 1){
            for(int k=0;k<jumlah-1;k++){
                for(int l=0;l<jumlah-1-k;l++){
                    int m=0;
                    while(produk[l].nama[m] != '\0' && produk[l+1].nama[m] != '\0'){
                        if(produk[l].nama[m] > produk[l+1].nama[m]){
                            temp = produk[l];
                            produk[l] = produk[l+1];
                            produk[l+1] = temp;
                            break;
                        }
                        else if(produk[l].nama[m] < produk[l+1].nama[m]){
                            break;
                        }
                        m++;
                    }
                }
            }
        }
    for(int i = 0; i < jumlah-1; i++){
        for(int j = i+1; j < jumlah; j++){
            bool tukar = false;
            if(opsi == 2){
                if(produk[i].harga > produk[j].harga){
                    tukar = true;
                }
            }
            else if(opsi == 3){
                if(produk[i].stok > produk[j].stok){
                    tukar = true;
                }
            }

            if(tukar){
                temp = produk[i];
                produk[i] = produk[j];
                produk[j] = temp;
            }
        }
    }
    cout << endl;
    cout << left << setw(15) << "Nama"
         << setw(10) << "Stok"
         << setw(10) << "Harga" << endl;
    for(int i = 0; i < jumlah; i++){
        cout << left << setw(15) << produk[i].nama
             << setw(10) << produk[i].stok
             << setw(10) << produk[i].harga << endl;
    }
    fclose(ProjectAkhir);
}

void descending(int opsi){
    Produk produk[100], temp;
    int jumlah = 0;
    FILE *ProjectAkhir = fopen("data_produk.txt", "r");
    if (!ProjectAkhir){
        cout << "Gagal membuka file!" << endl;
        system("pause");
        return;
    }

    while(fscanf(ProjectAkhir, "%s %d %d", produk[jumlah].nama, &produk[jumlah].stok, &produk[jumlah].harga) != EOF){
        jumlah++;
    }

    fclose(ProjectAkhir);
    if(opsi == 1){
            for(int k=0;k<jumlah-1;k++){
                for(int l=0;l<jumlah-1-k;l++){
                    int m=0;
                        while(produk[l].nama[m] != '\0' && produk[l+1].nama[m] != '\0'){
                        if(produk[l].nama[m] < produk[l+1].nama[m]){
                            temp = produk[l];
                            produk[l] = produk[l+1];
                            produk[l+1] = temp;
                            break;
                        }
                        else if(produk[l].nama[m] > produk[l+1].nama[m]){
                            break;
                        }
                        m++;
                    }
                }
            }
        }
    for(int i = 0; i < jumlah-1; i++){
        for(int j = i+1; j < jumlah; j++){
            bool tukar = false;
            if(opsi == 2){
                if(produk[i].harga < produk[j].harga){
                    tukar = true;
                }
            }
            else if(opsi == 3){
                if(produk[i].stok < produk[j].stok){
                    tukar = true;
                }
            }
            if(tukar){
                temp = produk[i];
                produk[i] = produk[j];
                produk[j] = temp;
            }
        }
    }
    cout << endl;
    cout << left << setw(15) << "Nama"
         << setw(10) << "Stok"
         << setw(10) << "Harga" << endl;
    for(int i = 0; i < jumlah; i++){
        cout << left << setw(15) << produk[i].nama
             << setw(10) << produk[i].stok
             << setw(10) << produk[i].harga << endl;
    }
}

void updateStok(){
    string namaCari;
    bool ditemukan = false;
    Produk produk;
    FILE *ProjectAkhir = fopen("data_produk.txt", "r");
    FILE *FileTemp = fopen("temp.txt", "w");
    if(!ProjectAkhir){
        cout << "Gagal membuka file!" << endl;
        system("pause");
        return;
    }

    cout << "Masukkan nama produk yang ingin diupdate: "; cin >> namaCari;
    while(fscanf(ProjectAkhir, "%s %d %d", produk.nama, &produk.stok, &produk.harga) != EOF){
        if(namaCari == produk.nama){
            ditemukan = true;
            cout << "Stok lama : " << produk.stok << endl;
            cout << "Masukkan stok baru: "; cin >> produk.stok;
        }
        fprintf(FileTemp, "%s %d %d\n", produk.nama, produk.stok, produk.harga);
    }
    fclose(ProjectAkhir);
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
    string namaHapus;
    bool ditemukan = false;
    Produk produk;

    FILE *ProjectAkhir = fopen("data_produk.txt", "r");
    FILE *FileTemp = fopen("temp.txt", "w");
    if(!ProjectAkhir){
        cout << "Gagal membuka file!" << endl;
        system("pause");
        return;
    }
    cout << "Masukkan nama produk yang ingin dihapus: "; cin >> namaHapus;
    while(fscanf(ProjectAkhir, "%s %d %d", produk.nama, &produk.stok, &produk.harga) != EOF){
        if(produk.nama != namaHapus){
            fprintf(FileTemp, "%s %d %d\n", produk.nama, produk.stok, produk.harga);
        }else{
            ditemukan = true;
        }
    }
    fclose(ProjectAkhir);
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
    string cariProduk;
    int jumlah = 0;
    bool cekCari = false;

    FILE *ProjectAkhir = fopen("data_produk.txt", "r");
    if (!ProjectAkhir){
        cout << "Gagal membuka file!" << endl;
        system("pause");
        return;
    }
    cout << "Masukkan nama produk yang akan dicari: "; cin >> cariProduk;
    Produk produk[100];
    while(fscanf(ProjectAkhir, "%s %d %d", produk[jumlah].nama, &produk[jumlah].stok, &produk[jumlah].harga) != EOF){
        jumlah++;
    }
    for(int i= 0; i < jumlah; i++){
        if(cariProduk == produk[i].nama){
            cout << endl <<
            "Nama  : " << produk[i].nama << endl <<
            "Harga : " << produk[i].harga << endl <<
            "Stok  : " << produk[i].stok << endl;
            cekCari = true;
        }
    }
    if(cekCari == false){
            cout << endl << "Produk dengan nama tersebut tidak ditemukan" << endl;
        }
    fclose(ProjectAkhir);
}

void beliProduk(){
    int pilih = -1;
    int jumlahProduk = 0;
    string namaPilih;
    int jumlahBeli;
    Produk produk[100];

    FILE *ProjectAkhir = fopen("data_produk.txt", "r");
    if (!ProjectAkhir){
        cout << "Belum ada data produk!" << endl;
        return;
    }
    while(fscanf(ProjectAkhir, "%s %d %d", produk[jumlahProduk].nama, &produk[jumlahProduk].stok, &produk[jumlahProduk].harga) != EOF){
        jumlahProduk++;
    }
    fclose(ProjectAkhir);

    cout << "Masukkan nama produk yang ingin dibeli: "; cin >> namaPilih;

    for(int i = 0; i < jumlahProduk; i++){
        if(produk[i].nama == namaPilih){
            pilih = i;
            break;
        }
    }

    if(pilih == -1){
        cout << "Produk tidak ditemukan!" << endl;
        return;
    }

    cout << "Masukkan jumlah beli: "; cin >> jumlahBeli;

    if(jumlahBeli > produk[pilih].stok){
        cout << "Stok tidak cukup! Stok tersedia: " << produk[pilih].stok << endl;  
        return;
    }

    produk[pilih].stok -= jumlahBeli;
    int total = jumlahBeli * produk[pilih].harga;
    cout << "Total Harga: Rp " << total << endl;

    FILE *ProjectAkhirTemp = fopen("temp.txt", "w");
    for(int i = 0; i < jumlahProduk; i++){
        fprintf(ProjectAkhirTemp, "%s %d %d\n", produk[i].nama, produk[i].stok, produk[i].harga);
    }
    fclose(ProjectAkhirTemp);
    
    remove("data_produk.txt");
    rename("temp.txt", "data_produk.txt");

    FILE *FileRiwayat = fopen("riwayat.txt", "a");
    if(FileRiwayat){
        fprintf(FileRiwayat, "%s %d %d\n", produk[pilih].nama, jumlahBeli, total);
        fclose(FileRiwayat);
    }

    cout << "Pembelian berhasil! Stok telah diperbarui." << endl;
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


#include <iostream>
#include <iomanip>
using namespace std;

struct Produk{
    char nama[50];
    int id;
    int harga;
    int stok;
};

struct Node {
    Produk data;
    Node* next;
};

struct Transaksi {
    string namaPembeli;
    string namaProduk;
    int jumlah;
    int total;
};

struct NodeTransaksi {
    Transaksi data;
    NodeTransaksi* next;
};

Node* bacaDariFile() {
    Node* head = nullptr;
    Node* tail = nullptr;

    FILE* f = fopen("data_produk.txt", "r");
    if (!f) {
        cout << "Gagal membuka file data_produk.txt!" << endl;
        return nullptr;
    }

    Produk tmp;
    while (fscanf(f, "%s %d %d", tmp.nama, &tmp.stok, &tmp.harga) != EOF) {
        Node* nodeBaru = new Node();
        nodeBaru->data = tmp;
        nodeBaru->next = nullptr;
        if (!head) {
            head = tail = nodeBaru;
        } else {
            tail->next = nodeBaru;
            tail = nodeBaru;
        }
    }
    fclose(f);
    return head;
}

void tulisKeFile(Node* head) {
    FILE* f = fopen("data_produk.txt", "w");
    if (!f) {
        cout << "Gagal menulis ke file!" << endl;
        return;
    }
    Node* current = head;
    while (current != nullptr) {
        fprintf(f, "%s %d %d\n", current->data.nama, current->data.stok, current->data.harga);
        current = current->next;
    }
    fclose(f);
}

void bebaskanMemoriProduk(Node* head) {
    while (head != nullptr) {
        Node* hapus = head;
        head = head->next;
        delete hapus;
    }
}

NodeTransaksi* headTransaksi = nullptr;

void tambahTransaksi(string namaPembeli, string namaProduk, int jumlah, int total) {
    NodeTransaksi* baru = new NodeTransaksi();
    baru->data = {namaPembeli, namaProduk, jumlah, total};
    baru->next = nullptr;

    if (!headTransaksi) {
        headTransaksi = baru;
    } else {
        NodeTransaksi* temp = headTransaksi;
        while (temp->next != nullptr) temp = temp->next;
        temp->next = baru;
    }

    FILE* f = fopen("data_transaksi.txt", "a");
    if (f) {
        fprintf(f, "%s %s %d %d\n", namaPembeli.c_str(), namaProduk.c_str(), jumlah, total);
        fclose(f);
    }
}

void muatTransaksiDariFile() {
    while (headTransaksi != nullptr) {
        NodeTransaksi* hapus = headTransaksi;
        headTransaksi = headTransaksi->next;
        delete hapus;
    }

    FILE* f = fopen("data_transaksi.txt", "r");
    if (!f) return; 

    char namaPembeli[50], namaProduk[50];
    int jumlah, total;
    while (fscanf(f, "%s %s %d %d", namaPembeli, namaProduk, &jumlah, &total) != EOF) {
        NodeTransaksi* baru = new NodeTransaksi();
        baru->data = {string(namaPembeli), string(namaProduk), jumlah, total};
        baru->next = nullptr;

        if (!headTransaksi) {
            headTransaksi = baru;
        } else {
            NodeTransaksi* temp = headTransaksi;
            while (temp->next != nullptr) temp = temp->next;
            temp->next = baru;
        }
    }
    fclose(f);
}

void lihatTransaksi() {
    muatTransaksiDariFile();

    if (!headTransaksi) {
        cout << "Belum ada transaksi." << endl;
        return;
    }

    cout << "\n=== DAFTAR TRANSAKSI PEMBELI ===" << endl;
    cout << left << setw(15) << "Pembeli"
         << setw(15) << "Produk"
         << setw(10) << "Jumlah"
         << setw(12) << "Total" << endl;
    cout << string(52, '-') << endl;

    NodeTransaksi* temp = headTransaksi;
    while (temp != nullptr) {
        cout << left << setw(15) << temp->data.namaPembeli
             << setw(15) << temp->data.namaProduk
             << setw(10) << temp->data.jumlah
             << "Rp. " << temp->data.total << endl;
        temp = temp->next;
    }
    cout << endl;
}

void lihatProduk();
void ascending(int opsi);
void descending(int opsi);
void tambahProduk();
void updateStok();
void hapusProduk();
void cariProduk();
void beliProduk();

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
            "6. Lihat Riwayat Pembeli" << endl <<
            "7. Kembali ke menu utama" << endl <<
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
                    lihatTransaksi();
                    break;
                }
                case 7 : {
                    return;
                }
                default : {
                    cout << "Nomor menu tidak valid! silahkan input ulang.." << endl;
                    break;
                }
            }
        }while(pilihAdmin != 7);
    }else{
        cout << endl << "Username atau password salah!" << endl;
        return;
    }
}


void user(){
    int pilihUser;
    cout << "Dashboard User Toko Kelontong" << endl;
    cout << "1. Lihat Semua Produk" << endl;
    cout << "2. Cari Produk" << endl;
    cout << "3. Beli Produk" << endl;
    cout << "4. Keluar" << endl;
    cout << "Pilih menu: "; cin >> pilihUser;
    switch(pilihUser) {
        case 1 : {
            lihatProduk();
            break;
        }
        case 2 : {
            cariProduk();
            break;
        }
        case 3 : {
            beliProduk();
            break;
        }
        case 4 : {
            cout << "terimakasih sudah menggunakan sistem toko kelontong" << endl;
        }
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

void beliProduk() {
    Node* head = bacaDariFile();
    if (!head) {
        cout << "Tidak ada produk tersedia!" << endl;
        return;
    }

    cout << "\n=== DAFTAR PRODUK TERSEDIA ===" << endl;
    lihatProduk();

    string namaPilih;
    cout << "\nMasukkan nama produk yang ingin dibeli: "; cin >> namaPilih;

    Node* target = nullptr;
    Node* cur = head;
    while (cur != nullptr) {
        if (namaPilih == string(cur->data.nama)) {
            target = cur;
            break;
        }
        cur = cur->next;
    }

    if (!target) {
        cout << "Produk tidak ditemukan!" << endl;
        bebaskanMemoriProduk(head);
        return;
    }

    cout << "\nProduk ditemukan!" << endl;
    cout << "Nama  : " << target->data.nama << endl;
    cout << "Harga : Rp. " << target->data.harga << endl;
    cout << "Stok  : " << target->data.stok << endl;

    int jumlahBeli;
    cout << "\nMasukkan jumlah beli: "; cin >> jumlahBeli;

    if (jumlahBeli <= 0) {
        cout << "Jumlah tidak valid!" << endl;
        bebaskanMemoriProduk(head);
        return;
    }
    if (jumlahBeli > target->data.stok) {
        cout << "Stok tidak cukup! Stok tersedia: " << target->data.stok << endl;
        bebaskanMemoriProduk(head);
        return;
    }

    int total = jumlahBeli * target->data.harga;
    cout << "Total Harga  : Rp. " << total << endl;

    string namaPembeli;
    cout << "Masukkan nama Anda: "; cin >> namaPembeli;

    target->data.stok -= jumlahBeli;

    cout << "\n======================================" << endl;
    cout << "           INVOICE PEMBELIAN          " << endl;
    cout << "======================================" << endl;
    cout << left << setw(15) << "Nama Pembeli" << ": " << namaPembeli << endl;
    cout << left << setw(15) << "Produk"       << ": " << target->data.nama << endl;
    cout << left << setw(15) << "Harga Satuan" << ": Rp. " << target->data.harga << endl;
    cout << left << setw(15) << "Jumlah"       << ": " << jumlahBeli << endl;
    cout << "--------------------------------------" << endl;
    cout << left << setw(15) << "TOTAL"        << ": Rp. " << total << endl;
    cout << "======================================" << endl;
    cout << "     Terimakasih sudah berbelanja!    " << endl;
    cout << "======================================" << endl;

    tulisKeFile(head);

    FILE* fp = fopen("data_pelanggan.txt", "a");
    if (fp) {
        fprintf(fp, "%s %d\n", namaPembeli.c_str(), total);
        fclose(fp);
    }

    tambahTransaksi(namaPembeli, string(target->data.nama), jumlahBeli, total);

    cout << "\nPembelian berhasil!" << endl;
    bebaskanMemoriProduk(head);
}
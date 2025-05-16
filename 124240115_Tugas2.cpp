#include <iostream>
#include <string>
using namespace std;

struct antrian
{
    string nama, jenis_roti;
    int total_harga;
    antrian *next;
};
antrian *depan, *belakang;

struct history{
    string nama, jenis_roti;
    int total_harga;
    history *next;
};
history *head = NULL;
bool antrianKosong(){
    return depan==NULL;
    
}
void buatAntrian(){
    depan = belakang = NULL;
}

void tambahAntrian(string nama, string jenis_roti, int total_harga){
    antrian* antrianBaru = new antrian;
    antrianBaru->nama = nama;
    antrianBaru->jenis_roti = jenis_roti;
    antrianBaru->total_harga = total_harga;
    antrianBaru->next = NULL;
    if(antrianKosong()){
        depan = belakang = antrianBaru;
    } else {
        belakang->next = antrianBaru;
        belakang = antrianBaru;
    }
    cout << "antrian berhasil ditambah\n";
}

void simpanHistory(string nama, string jenis_roti, int total_harga){
    history* historyBaru = new history;
    historyBaru->nama = nama;
    historyBaru->jenis_roti = jenis_roti;
    historyBaru->total_harga = total_harga;
    historyBaru->next = NULL;
    if(head == NULL){
        head = historyBaru;
    } else {
        history *temp = head;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = historyBaru;
    }
}
void layaniAntrian(){
    if (antrianKosong())
    {
        cout << "Belum ada antrian" << endl;
    } else {
        antrian *hapus = depan;
        simpanHistory(hapus->nama, hapus->jenis_roti, hapus->total_harga);
        cout << "\nMelayani pelanggan: " << hapus->nama << endl;
        depan = depan->next;
        delete hapus;

        if(depan == NULL) belakang = NULL;
    }
}
void tampilkanAntrian(){
    if (antrianKosong())
    {
        cout << "antrian masih kosong\n";
        return;
    }
    antrian *bantu = depan;
    cout << "\nDaftar Antrian:\n";
    cout << "------------------------------\n";
    while (bantu != NULL) {
        cout << "Nama        : " << bantu->nama << endl;
        cout << "Jenis Roti  : " << bantu->jenis_roti << endl;
        cout << "Total Harga : " << bantu->total_harga << endl;
        cout << "------------------------------\n";
        bantu = bantu->next;
    }
}

void tampilkanHistory(){
    if (head == NULL){
        cout << "Riwayat masih kosong" << endl;
        cout << "------------------------------\n";
        return;
    }
    history *bantu = head;
    cout << "\nRiwayat Pelayanan:\n";
    cout << "------------------------------\n";
    while (bantu != NULL) {
        cout << "Nama        : " << bantu->nama << endl;
        cout << "Jenis Roti  : " << bantu->jenis_roti << endl;
        cout << "Total Harga : " << bantu->total_harga << endl;
        cout << "------------------------------\n";
        bantu = bantu->next;
    }
}
int main(){
    buatAntrian();
    int menu, total_harga;
    string nama, jenis_roti;
    do{
        system("cls");
        cout << "=============================\n";
        cout << "||          Menu           ||\n";
        cout << "-----------------------------\n";
        cout << "||1. Tambah Pesanan        ||" << endl;
        cout << "||2. Tampilkan Antrian     ||\n";
        cout << "||3. Layani Pesanan        ||\n";
        cout << "||4. Lihat History Pesanan ||" << endl;
        cout << "||0. exit                  ||\n";
        cout << "=============================\n";
        cout << "pilih menu: "; cin >> menu;
        cin.ignore();
        switch (menu)
        {
        case 1:
            cout << "Masukkan Nama Pemesan: "; getline(cin, nama);
            cout << "Jenis Roti: "; getline(cin, jenis_roti);
            cout << "Total harga: "; cin>>total_harga;
            cin.ignore();
            tambahAntrian(nama, jenis_roti, total_harga);
            break;
        case 2:
            tampilkanAntrian();
            break;
        case 3:
            layaniAntrian();
            break;
        case 4:
            tampilkanHistory();
            break;
        case 0:
            cout << "Thank you!" << endl;
            break;
        default:
            cout << "pilihan tidak tersedia\n";
            break;
        }
        if (menu != 0) {
        cout << "\nTekan ENTER untuk kembali ke menu...";
        cin.get();
    }
    } while(menu != 0);
}
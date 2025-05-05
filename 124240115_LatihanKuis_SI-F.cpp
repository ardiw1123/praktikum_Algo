#include <iostream>
#include <cctype>
#include <algorithm>
#include <string>
#include <cstring>
#include <stdio.h>
using namespace std;

int jumlah_data = 0;
const int max_data = 100;
struct mahasiswa
{
    string nim, nama, jurusan, th_masuk;
    float ipk = 0.0;
};
mahasiswa* data[max_data];

void bacaData(){
    FILE *file = fopen("mahasiswa.dat", "r");
    if (file == NULL)
    {
        cout << "File tidak dapat dibuka.\n";
        jumlah_data = 0;
        return;
    }
    jumlah_data = 0;
    char nim[20], nama[100], jurusan[50], th_masuk[10], buffer[100];
    float ipk;
    while (fgets(nim, sizeof(nim), file) && fgets(nama, sizeof(nama), file) && fgets(jurusan, sizeof(jurusan), file) && fgets(th_masuk, sizeof(th_masuk), file) && fgets(buffer, sizeof(buffer), file))
    {
        sscanf(buffer, "%f", &ipk);

        nim[strcspn(nim, "\n")] = '\0';
        nama[strcspn(nama, "\n")] = '\0';
        jurusan[strcspn(jurusan, "\n")] = '\0';
        th_masuk[strcspn(th_masuk, "\n")] = '\0';
        data[jumlah_data] = new mahasiswa;
        data[jumlah_data]->nim = nim;
        data[jumlah_data]->nama = nama;
        data[jumlah_data]->jurusan = jurusan; 
        data[jumlah_data]->th_masuk = th_masuk;
        data[jumlah_data]->ipk = ipk;
        jumlah_data++;
        if (jumlah_data >= max_data)
        {
            break;
        }  
    }
    fclose(file);
}

void inputDataFile(){
    FILE *file;
    file = fopen("mahasiswa.dat", "w");
    if (!file)
    {
        cout << "File tidak dapat dibuka.\n";
        return;
    }
    for (int i = 0; i < jumlah_data; i++)
    {
        fprintf(file, "%s\n%s\n%s\n%s\n%.2f\n", 
            data[i]->nim.c_str(), 
            data[i]->nama.c_str(), 
            data[i]->jurusan.c_str(), 
            data[i]->th_masuk.c_str(), 
            data[i]->ipk);
    }
    fclose(file);
}

void inputData(){
    if (jumlah_data >= max_data)
    {
        cout << "File telah mencapai kapasitas maksimal" << endl;
        return;
    }
    int input;
    FILE *file;
    file = fopen("mahasiswa.dat", "a");
    if (!file)
    {
        cout << "Error while open file.\n";
        return;
    }
    cout << "Jumlah input mahasiswa: "; cin >> input;
    for (int i = 0; i < input; i++)
    {
        data[jumlah_data] = new mahasiswa;
        cout << "NIM: "; cin >> data[jumlah_data]->nim;
        cin.ignore();
        cout << "Nama: "; getline(cin,data[jumlah_data]->nama);
        cout << "Jurusan: "; getline(cin,data[jumlah_data]->jurusan);
        cout << "Tahun Masuk: "; getline(cin,data[jumlah_data]->th_masuk);
        fprintf(file, "%s\n%s\n%s\n%s\n%.2f\n", 
            data[jumlah_data]->nim.c_str(), 
            data[jumlah_data]->nama.c_str(), 
            data[jumlah_data]->jurusan.c_str(), 
            data[jumlah_data]->th_masuk.c_str(), 
            data[jumlah_data]->ipk);
        jumlah_data++;
    }
    fclose(file);
}
void updateData(){
    if (jumlah_data == 0)
    {
       cout << "Belum ada data, silahkan input dahulu" << endl;
       return;
    }
    string cariNIM;
    cout << "NIM yang ingin update IPK: "; cin >> cariNIM;
    bool found = false;
    for (int i = 0; i < jumlah_data; i++)
    {
        if(cariNIM == data[i]->nim) {
            cout << "Masukkan IPK baru: "; cin >> data[i]->ipk;
            found = true;
    }
}
    if(!found){
        cout << "Data tidak ditemukan" << endl;
        return;
    }
    inputDataFile();
    cout << "IPK diberbarui" << endl;

}

void bubbleSort(){
    for (int i = 0; i < jumlah_data - 1; i++)
    {
        for (int j = i+1; j < jumlah_data; j++)
        {
            if (data[j]->nim < data[i]->nim)
            {
                swap(data[i] , data[j]);
            }
            
        }
    }
    
}

int partisi(int awal, int akhir){
    int pivot;
    // try {
        pivot = stoi(data[akhir]->nim);
    // } catch (...) {
    //     cerr << "Error: NIM pada indeks " << akhir << " tidak valid." << endl;
    //     return awal; // atau tangani error dengan cara lain
    // }
    int i = awal;
    for (int j = i; j < akhir; j++)
    {
        // try {
            if (stoi(data[j]->nim) <= pivot) {
                swap(data[j], data[i]);
                i++;
            }
        // } catch (...) {
        //     cerr << "Error: NIM pada indeks " << j << " tidak valid." << endl;
        //     // Anda dapat memilih untuk melanjutkan atau menghentikan sorting
        // }
    }
    swap(data[akhir], data[i]);
    return i;
    
}

void QuickSort(int awal, int akhir){
    if (awal < akhir){
        int ip = partisi(awal, akhir);
        QuickSort(awal, ip-1);
        QuickSort(ip+1, akhir);
    }
}

int binarySearch(){
    QuickSort(0, jumlah_data - 1);
    int awal = 0, akhir = jumlah_data - 1;
    string cariNim;
    cout << "NIM yang ingin dicari: "; cin >> cariNim;
    while (awal <= akhir)
    {
        int tengah = (awal+akhir)/2;
        if(cariNim == data[tengah]->nim)
        return tengah;
        else {
            if (cariNim < data[tengah]->nim)
            akhir = tengah - 1;
            else
            awal = tengah + 1;
        }
    }
    return - 1;
    
}
void cariByNIM(){
    if (jumlah_data == 0)
    {
        cout << "Tidak ada data" << endl;
        return;
    }
    int found = binarySearch();
    if (found == - 1)
    {
        cout << "Mahasiswa Tidak Ditemukan" << endl;
    }
    else {
    cout << "Mahasiswa Ditemukan!" << endl;
        cout << "NIM: " << data[found]->nim << endl;
        cout << "Nama: " << data[found]->nama << endl;
        cout << "Jurusan: " << data[found]->jurusan << endl;
        cout << "Tahun Masuk: " << data[found]->th_masuk << endl;
        cout << "IPK: " << data[found]->ipk << endl;
    }
}

void cariByJurusan(){
    if (jumlah_data == 0)
    {
        cout << "Tidak ada data" << endl;
    }
    string cariJurusan;
    cin.ignore();
    cout << "Masukkan jurusan yang ingin dicari: "; getline(cin, cariJurusan);
    string jurusanInputLower = cariJurusan;
    transform(jurusanInputLower.begin(), jurusanInputLower.end(),
              jurusanInputLower.begin(), ::tolower);
    bool found = false;
    for (int i = 0; i < jumlah_data; i++)
    {
        string jurusanDataLower = data[i]->jurusan;
        transform(jurusanDataLower.begin(), jurusanDataLower.end(),
                  jurusanDataLower.begin(), ::tolower);
        if (jurusanInputLower == jurusanDataLower)
        {
            cout << "Mahasiswa Ditemukan!" << endl;
            cout << "====================" << endl;
            cout << "NIM: " << data[i]->nim << endl;
            cout << "Nama: " << data[i]->nama << endl;
            cout << "Jurusan: " << data[i]->jurusan << endl;
            cout << "Tahun Masuk: " << data[i]->th_masuk << endl;
            cout << "IPK: " << data[i]->ipk << endl;
            found = true;
        }
    }
    if(!found)
    cout << cariJurusan << "Tidak ada dalam data mahasiswa!" << endl;
}
void hapusData(){
    if (jumlah_data == 0)
    {
        cout << "Tidak ada data" << endl;
        return;
    }
    string hapusNim;
    cout << "Masukkan NIM yang ingin dihapus: "; cin >> hapusNim;
    for (int i = 0; i < jumlah_data; i++)
    {
        if (hapusNim == data[i]->nim)
        {
            delete data[i];
            for (int j = i; j < jumlah_data - 1; j++) {
                data[j] = data[j + 1]; 
            }
            jumlah_data--;
            cout << "Mahasiswa dengan NIM " << hapusNim << " berhasil dihapus!" << endl;
            inputDataFile();
            return;
        }
        else
        cout << "NIM yang anda masukkan tidak ada dalam data" << endl;
    }
}
void tampilData() {
    if (jumlah_data == 0)
    {
        cout << "Tidak ada data" << endl;
        return;
    } else{
        bubbleSort();
    cout << "\nData Mahasiswa " << endl;
    for (int i = 0; i < jumlah_data; i++)
    {
        cout << "NIM: " << data[i]->nim << endl;
        cout << "Nama: " << data[i]->nama << endl;
        cout << "Jurusan: " << data[i]->jurusan << endl;
        cout << "Tahun Masuk: " << data[i]->th_masuk << endl;
        cout << "IPK: " << data[i]->ipk << endl;
        cout << "===============================" << endl;
    }
    cout << "Data Mahasiswa ditampilkan sorting ascending berdasarkan nim" << endl;
    }
}
void menu(){
    int menu, n;
    bool lanjut = true;
    while (lanjut) {
    system("cls");
    cout << "==============================" << endl;
    cout << "|             MENU           |" << endl;
    cout << "------------------------------" << endl;
    cout << "|1. Input Data Mahasiswa     |" << endl;
    cout << "|2. Lihat Data Mahasiswa     |" << endl;
    cout << "|3. Cari Mahasiswa By NIM    |" << endl;
    cout << "|4. Cari Mahasiswa By Jurusan|" << endl;
    cout << "|5. Update IPK               |" << endl;
    cout << "|6. Hapus Data Mahasiswa     |" << endl;
    cout << "|7. Exit Program             |" << endl;
    cout << "==============================" << endl;
    cout << "Pilih Menu: "; cin >> menu;
    switch (menu)
    {
    case 1:
        inputData();
        break;
    case 2:
        tampilData();
    break;
    case 3:
        cariByNIM();
    break;
    case 4:
        cariByJurusan();
    break;
    case 5:
        updateData();
    break;
    case 6:
        hapusData();
    break;
    case 7:
        cout << "terimakasih telah menggunakan program smartcampus++" << endl;
        exit(1);
    default:
        cout << "Menu tidak tersedia" << endl;
    break;
    }
    system("pause");
}
}
int main(){
    bacaData();
    menu();
    inputDataFile();
    for (int i = 0; i < jumlah_data; i++)
    {
        delete data[i];
    }
    return 0;
}
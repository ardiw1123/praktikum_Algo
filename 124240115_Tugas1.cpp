#include <iostream>
#include <cstdlib>
#include <cctype>
#include <algorithm>
using namespace std;

struct mahasiswa {
    string nama, nim;
    float ipk;
};
mahasiswa data[10]{
    {"Budi", "124240001", 3.5}, 
    {"Andi", "124240002", 3.6}, 
    {"Caca", "124240003", 3.7}, 
    {"Dedi", "124240004", 3.8}, 
    {"Euis", "124240005", 3.9}, 
    {"Feri", "124240006", 3.4}, 
    {"Gina", "124240007", 3.3}, 
    {"Hadi", "124240008", 3.2}, 
    {"Ika", "124240009", 3.1}, 
    {"Joko", "124240010", 3}, 
};
void tampilData(){
    for (int i=0; i<10; i++){
        cout << "Nama: " << data[i].nama << "," << " NIM: " << data[i].nim << "," << "IPK: " << data[i].ipk << endl;
    }
}
void cariNim(){
int i; bool found; string x;
  cout << "Masukkan NIM yang anda cari : "; cin >> x;
  i=0; found=false;
  while ((i<10) && (!found))
  { if (data[i].nim==x)
       found = true;
    else
       i = i + 1;
  }
  if(found)
    cout << "Nama: " << data[i].nama << "," << "  NIM: " << data[i].nim << "," << "  IPK: " << data[i].ipk << endl;
  else
     cout << x <<" tidak terdapat pada data"<< endl;
  cout << " "<< endl;
}
string toLowerCase(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}
void cariNama(){
int i,j,t; bool found; string x;
  cout << "Masukkan nama mahasiswa: "; cin >> x;
  string lowerInput = toLowerCase(x);
  i=0;  j=10;  found=false;  
  while ((!found) & (i <= j))
  { t = (i + j) / 2;     
    string lowerNama = toLowerCase(data[i].nama);
    if (lowerInput == lowerNama)
	found=true;       
    else
	if (x < data[i].nama)
	   j = t - 1;    
	else
	   i = t + 1;    
  }
  if(found)
    cout << "Nama: " << data[i].nama << "," << "  NIM: " << data[i].nim << "," << "  IPK: " << data[i].ipk << endl;
  else
     cout << x <<" tidak terdapat dalam data"<< endl;

}
void sortAsc(mahasiswa data[], int awal, int akhir){
    int low = awal, high = akhir;
    float pivot = data[(awal + akhir) / 2].ipk;
    int temp;
    do {
        while (data[low].ipk < pivot)
            low++;
        while (data[high].ipk > pivot)
            high--;
        if (low <= high) {
            swap(data[low], data[high]);
            low++;
            high--;

        }
    } while (low <= high);
    if (awal < high)
        sortAsc(data, awal, high);
    if (low < akhir)
        sortAsc(data, low, akhir);
}
void tampilAsc(mahasiswa data[]){
    cout << "Data Mahasiswa: " << endl;
    for (int i = 0; i<10; i++) {
    cout << "Nama: " << data[i].nama << "," << "  NIM: " << data[i].nim << "," << "  IPK: " << data[i].ipk << endl;
    }
    cout << "Mahasiswa telah diurutkan Ascending berdasarkan IPK" << endl;
}
void sortDesc(mahasiswa data[], int n){
    n = 10;
    for( int i=0; i<n-1; i++){
        for(int j=i+1; j<n; j++){
            if(data[i].ipk < data[j].ipk){
              swap(data[i],data[j]);    // Tukar posisi
            }   
        }
      }      
    cout << "Data Mahasiswa: " << endl;
    for (int i = 0; i<10; i++) {
    cout << "Nama: " << data[i].nama << "," << "  NIM: " << data[i].nim << "," << "  IPK: " << data[i].ipk << endl;
    }
    cout << "Mahasiswa telah diurutkan Descending berdasarkan IPK" << endl;
}
void menu(){
    int menu, n;
    bool lanjut = true;
    while (lanjut) {
    system("cls");
    cout << "==============================" << endl;
    cout << "|             MENU           |" << endl;
    cout << "------------------------------" << endl;
    cout << "|1. Tampilkan Data Mahasiswa |" << endl;
    cout << "|2. Cari Berdasarkan NIM     |" << endl;
    cout << "|3. Cari Berdasarkan Nama    |" << endl;
    cout << "|4. Sort IPK Mahasiswa (ASC) |" << endl;
    cout << "|5. Sort IPK Mahasiswa (DESC)|" << endl;
    cout << "|6. Exit                     |" << endl;
    cout << "==============================" << endl;
    cout << endl;
    cout << "Pilih Menu: "; cin >> menu;
    switch (menu)
    {
    case 1:
        tampilData();
        break;
    case 2:
        cariNim();
    break;
    case 3:
        cariNama();
    break;
    case 4: 
        sortAsc(data, 0, 9);
        tampilAsc(data);
    break;
    case 5:
        sortDesc(data, n);
    break;
    case 6:
        cout << "Thank You!";
        exit(0);
    default:
    cout << "Pilihan Tidak Tersedia!" << endl;
    break;
    }
    char pilihan;
        cout << "\nApakah Anda ingin kembali ke menu? (y/n): ";
        cin >> pilihan;
        if (pilihan != 'y' && pilihan != 'Y') {
            lanjut = false;
            cout << "Thank you!\n";
}
}
}
int main(){
    menu();
}
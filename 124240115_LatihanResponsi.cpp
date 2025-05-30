#include <iostream>
#include <cstring>
using namespace std;

struct Video {
    string judul;
    string status;
    int durasi;
    Video *left, *right = nullptr;
};
string status[3] = {"tersedia", "sedang diputar", "dalam antrian"};

Video *root = nullptr;

struct playlist {
    Video *video;
    playlist *next;
};

playlist *depan = nullptr, *belakang = nullptr;

struct Riwayat {
    Video *video;
    Riwayat *next;
};
Riwayat *top, *bottom = nullptr;

enum ActionType { TAMBAH_VIDEO, HAPUS_VIDEO, TAMBAH_PLAYLIST, TONTON_VIDEO };

struct ActionHistory {
    ActionType type;
    Video* video;
    string previousStatus;
    Video* relatedVideo; // Untuk menyimpan video terkait (misal: video sebelumnya di playlist)
    ActionHistory* next;
};

ActionHistory* actionTop = nullptr;

void pushAction(ActionType type, Video* video, string prevStatus = "", Video* related = nullptr) {
    ActionHistory* newAction = new ActionHistory;
    newAction->type = type;
    newAction->video = video;
    newAction->previousStatus = prevStatus;
    newAction->relatedVideo = related;
    newAction->next = actionTop;
    actionTop = newAction;
}

void clearActionHistory() {
    while (actionTop != nullptr) {
        ActionHistory* temp = actionTop;
        actionTop = actionTop->next;
        delete temp;
    }
}
void insertVideo(Video *&root, string judul, int durasi) {
    if (root == nullptr) {
        root = new Video;
        root->judul = judul;
        root->status = status[0];
        root->durasi = durasi;
        root->left = root->right = nullptr;
        pushAction(TAMBAH_VIDEO, root);
    }else if(root->judul > judul) {
            insertVideo(root->left, judul, durasi);
    }else if (root->judul < judul) {
            insertVideo(root->right, judul, durasi);
    } else {
        cout << "Video dengan judul " << judul << " sudah ada.\n";
    }
}

// Fungsi untuk menampilkan video (in-order traversal)
void tampilSemuaVideo(Video *root) {
    if (root == nullptr) return;
    
    tampilSemuaVideo(root->left);
    cout << root->judul << "\t" << root->status << "\t" << root->durasi << " menit\n";
    tampilSemuaVideo(root->right);
}

// Fungsi untuk menampilkan + opsi pencarian
void tampilVideo(Video *root) {
    if (root == nullptr) {
        cout << "Belum ada video tersimpan.\n";
        return;
    }

    // Tampilkan semua video sekaligus
    cout << "-------------------------------------\n";
    cout << "DAFTAR VIDEO:\n";
    cout << "Judul\t\tStatus\t\tDurasi\n";
    cout << "-------------------------------------\n";
    tampilSemuaVideo(root);
    cout << "-------------------------------------\n";

    // Opsi pencarian
    char pilihan;
    cout << "Apakah ingin mencari video tertentu? (y/n): ";
    cin >> pilihan;
    
    if (pilihan == 'y' || pilihan == 'Y') {
        string judul;
        cout << "Masukkan judul video: ";
        cin.ignore();
        getline(cin, judul);

        Video *current = root;
        bool ditemukan = false;
        
        while (current != nullptr && !ditemukan) {
            if (current->judul == judul) {
                cout << "\nVideo ditemukan:\n";
                cout << "Judul: " << current->judul << endl;
                cout << "Status: " << current->status << endl;
                cout << "Durasi: " << current->durasi << " menit\n";
                ditemukan = true;
            } 
            else if (judul < current->judul) {
                current = current->left;
            } 
            else {
                current = current->right;
            }
        }

        if (!ditemukan) {
            cout << "Video dengan judul \"" << judul << "\" tidak ditemukan.\n";
        }
    }
}

bool playlistKosong() {
    return depan == nullptr;
}

Video* cariVideo(Video* node, const string& judul) {
    if (node == nullptr || node->judul == judul) {
        return node;
    }
    if (judul < node->judul) {
        return cariVideo(node->left, judul);
    }
    return cariVideo(node->right, judul);
}

void tambahPlaylist(Video *video) {
    if (!video) {
        cout << "Video tidak ditemukan.\n";
        return;
    }
    playlist *baru = new playlist;
    baru->video = video;
    pushAction(TAMBAH_PLAYLIST, video, video->status); // Simpan aksi penambahan ke playlist
    baru->video->status = status[2]; // Set status video ke "dalam antrian"
    baru->next = nullptr;
    if(depan == nullptr) {
        depan = belakang = baru;
    } else {
        belakang->next = baru;
        belakang = baru;
    }
}
void simpanRiwayat(Video *video) {
    Riwayat *baru = new Riwayat;
    baru->video = video;
    baru->next = nullptr;
    if(top == nullptr) {
        top = bottom = baru;
    } else {
        Riwayat *temp = top;
        while(temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = baru; // Tambahkan ke akhir riwayat
    }
}

void playVideo() {
    if (playlistKosong()) {
        cout << "Playlist kosong, tidak ada video yang bisa ditonton.\n";
        return;
    }
    Video *videoDiputar = depan->video;
    pushAction(TONTON_VIDEO, videoDiputar, videoDiputar->status, depan->next ? depan->next->video : nullptr);
    videoDiputar->status = status[1]; // Set status video ke "sedang diputar"
    cout << "Memutar video: " << videoDiputar->judul << "\n";
    cout << "Durasi: " << videoDiputar->durasi << " menit\n";
    cout << "Status: " << videoDiputar->status << "\n";
    simpanRiwayat(videoDiputar); // Simpan video yang diputar ke riwayat
    playlist *temp = depan;
    depan = depan->next; // Hapus video dari playlist
    temp->video->status = status[0]; // Set status video ke "tersedia"
}

void tampilRiwayat() {
    if (top == nullptr) {
        cout << "Riwayat tonton masih kosong.\n";
        return;
    }
    cout << "-------------------------------------\n";
    cout << "RIWAYAT VIDEO YANG DITONTON:\n";
    cout << "Judul\t\tStatus\t\tDurasi\n";
    cout << "-------------------------------------\n";
    Riwayat *temp = top;
    while (temp != nullptr) {
        cout << temp->video->judul << "\t" << temp->video->status << "\t" << temp->video->durasi << " menit\n";
        temp = temp->next;
    }
    cout << "-------------------------------------\n";
}

void tampilkanPlaylist() {
    if (playlistKosong()) {
        cout << "Playlist kosong.\n";
        return;
    }
    cout << "-------------------------------------\n";
    cout << "PLAYLIST VIDEO:\n";
    cout << "Judul\t\tStatus\t\tDurasi\n";
    cout << "-------------------------------------\n";
    playlist *temp = depan;
    while (temp != nullptr) {
        cout << temp->video->judul << "\t" << temp->video->status << "\t" << temp->video->durasi << " menit\n";
        temp = temp->next;
    }
    cout << "-------------------------------------\n";
}

void hapusVideo(Video *&root, string &judul) {
    if (root == nullptr) {
        cout << "Video tidak ditemukan.\n";
        return;
    }

    if (judul < root->judul) {
        hapusVideo(root->left, judul);
    } 
    else if (judul > root->judul) {
        hapusVideo(root->right, judul);
    } 
    else {
        // Node ditemukan
        pushAction(HAPUS_VIDEO, root, root->status); // Simpan aksi penghapusan
        if (root->status == status[1] || root->status == status[2]) {
            char pilihan;
            cout << "Video \"" << root->judul << "\" sedang dalam antrian/diputar. Yakin ingin hapus? (y/n): ";
            cin >> pilihan;
            if (tolower(pilihan) != 'y') {
                cout << "Penghapusan dibatalkan.\n";
                return;
            }
        }
        // Penanganan penghapusan node
        if (root->left == nullptr) {
            Video *temp = root->right;
            delete root;
            root = temp;
        } 
        else if (root->right == nullptr) {
            Video *temp = root->left;
            delete root;
            root = temp;
        } 
        else {
            // Node dengan dua anak
            Video *temp = root->right;
            while (temp->left != nullptr) {
                temp = temp->left;
            }
            // Salin data
            root->judul = temp->judul;
            root->durasi = temp->durasi;
            root->status = temp->status;
            // Hapus node pengganti
            hapusVideo(root->right, temp->judul);
        }
        cout << "Video berhasil dihapus.\n";
    }
}

void undoLastAction() {
    if (actionTop == nullptr) {
        cout << "Tidak ada aksi yang bisa di-undo.\n";
        return;
    }

    ActionHistory* lastAction = actionTop;
    actionTop = actionTop->next;

    switch (lastAction->type) {
        case TAMBAH_VIDEO: {
            // Undo penambahan video = hapus video
            string judul = lastAction->video->judul;
            hapusVideo(root, judul);
            cout << "Berhasil membatalkan penambahan video " << judul << endl;
            break;
        }
        case HAPUS_VIDEO: {
            // Undo penghapusan video = tambahkan kembali
            insertVideo(root, lastAction->video->judul, lastAction->video->durasi);
            Video* v = cariVideo(root, lastAction->video->judul);
            if (v) v->status = lastAction->previousStatus;
            cout << "Berhasil mengembalikan video " << lastAction->video->judul << endl;
            break;
        }
        case TAMBAH_PLAYLIST: {
            // Undo penambahan ke playlist = hapus dari playlist
            playlist* prev = nullptr;
            playlist* curr = depan;
            while (curr != nullptr && curr->video != lastAction->video) {
                prev = curr;
                curr = curr->next;
            }
            if (curr) {
                if (prev) prev->next = curr->next;
                else depan = curr->next;
                if (curr == belakang) belakang = prev;
                curr->video->status = lastAction->previousStatus;
                delete curr;
                cout << "Berhasil membatalkan penambahan " << lastAction->video->judul << " ke playlist\n";
            }
            break;
        }
        case TONTON_VIDEO: {
            // Undo pemutaran video = kembalikan ke playlist
            playlist* baru = new playlist;
            baru->video = lastAction->video;
            baru->next = depan;
            depan = baru;
            if (belakang == nullptr) belakang = depan;
            
            // Hapus dari riwayat
            Riwayat* prev = nullptr;
            Riwayat* curr = top;
            while (curr != nullptr && curr->video != lastAction->video) {
                prev = curr;
                curr = curr->next;
            }
            if (curr) {
                if (prev) prev->next = curr->next;
                else top = curr->next;
                if (curr == bottom) bottom = prev;
                delete curr;
            }
            
            lastAction->video->status = lastAction->previousStatus;
            cout << "Berhasil membatalkan pemutaran " << lastAction->video->judul << endl;
            break;
        }
    }

    delete lastAction;
}

void menu(){
    int menu;
    do{
    system("cls"); 
    cout << "=============================\n";
    cout << "||          Menu           ||\n";
    cout << "-----------------------------\n";
    cout << "||1. Tambah Video          ||\n";
    cout << "||2. Tampilkan Video       ||\n";
    cout << "||3. Tambah Ke Playlist    ||\n";
    cout << "||4. Putar Video           ||\n";
    cout << "||5. Undo Terakhir         ||\n";
    cout << "||6. Hapus Video           ||\n";
    cout << "||7. Riwayat Tonton        ||\n";
    cout << "||8. Tampilkan Playlist    ||\n";
    cout << "||9. Keluar                ||\n";
    cout << "=============================\n";
    cout << "Pilih menu: "; cin >> menu;
    cin.ignore();
    switch (menu)
    {
    case 1: {
        string judul, status;
        int durasi;
        cout << "Masukkan Judul Video: "; getline(cin, judul);
        cout << "Masukkan Durasi Video (dalam menit): "; cin >> durasi;
        cin.ignore();
        insertVideo(root, judul, durasi);
        break;
    }
    case 2:
        tampilVideo(root);
        break;
    case 3: {
        cout << "Masukkan judul video yang ingin ditambahkan ke playlist: ";
        string judul;
        getline(cin, judul);
        Video *video = cariVideo(root, judul);
        if(video){
            tambahPlaylist(video);
            cout << "Video ditambahkan ke playlist.\n";
        } else {
            cout << "Video dengan judul \"" << judul << "\" tidak ditemukan.\n";
        }
        break;
    }
    case 4:
        playVideo();
        break;
    case 5:
        undoLastAction();
        break;
    case 6:{
        cout << "Masukkan judul video yang ingin dihapus: ";
        string judul;
        getline(cin, judul);
        hapusVideo(root, judul);
        break;
    }
    case 7:
        tampilRiwayat();
        break;
    case 8:
        tampilkanPlaylist();
        break;
    default:
        cout << "Pilihan tidak tersedia. Silakan coba lagi.\n";
        break;
    }
     cout << "Press any key to continue...\n";
        cin.get();
    } while(menu != 9);
}
int main(){
    menu();
    clearActionHistory(); // Clear action history 
    return 0;
}

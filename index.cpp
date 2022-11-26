// Bismillah
#include<iostream>
#include<cstdio>
#include<fstream>
#include<sstream>
#include<string>
#include<cstdlib>
#include<conio.h>
#include<windows.h>
#include<mysql.h>

using namespace std;

int qstate;
MYSQL* conn;
MYSQL_ROW row;
MYSQL_RES* res;

class db_koneksi

{
public:
    static void ConnectionFunction()
    {
        conn = mysql_init(0);
        if (conn)
        {
            cout << "Database Terhubung" << endl;
            // getch();
            system("cls");
        }
        else
            cout << "Database gagal terhubung" << mysql_errno(conn) << endl; // mysqlerrno mengembalikan code yang salah, mysqlerror mengembalikan teks yang salah
        conn = mysql_real_connect(conn, "localhost", "root", "", "kaizendesa", 0, NULL, 0);
        if (conn)
        {
            cout << "Database terhubung ke mysql" << conn << endl;
            // getch();
            system("cls");
        }
        else
            cout << "Database gagal terhubung!" << mysql_errno(conn) << endl;
    }
};

// Menambahkan Fungsi selamar darang, tinggal dipanggil sebelum proses CRUD, atau bisa dicustom.
void selamatdatang() {
    cout << "Selamat Datang di Aplikasi Kaizen Desa Durian Runtuh" << endl << endl;
    cout << "Menu :" << endl;
}

// Menambahkan Fungsi Menu
void TambahPengaduan();
void EditPengaduan();
void HapusPengaduan();
void LihatPengaduan();

int main()
{

    db_koneksi::ConnectionFunction();

    // Variabel
    int pilihanmenu;
    char keluar;
    int nomor = 1;
    int cari = 0;

    selamatdatang();
    for (int i = 0; i < 1; i++) {

        cari = nomor;
        cout << cari << ". Ajukan Pengaduan" << endl;
        cari += nomor;
        cout << cari << ". Edit Pengaduan" << endl;
        cari += nomor;
        cout << cari << ". Hapus Pengaduan" << endl;
        cari += nomor;
        cout << cari << ". List Pengaduan" << endl;
        cari += nomor;
        cout << cari << ". Exit" << endl;
        cout <<""<<endl;
        cout << "Silahkan pilih nomor 1 - 5 : ";
    }
    cin >> pilihanmenu;

    switch (pilihanmenu)
    {
    case 1:
        TambahPengaduan();
        break;
    case 2:
        EditPengaduan();
        break;
    case 3:
        HapusPengaduan();
        break;
    case 4:
        LihatPengaduan();
        break;
    case 5:
        keluarprogram:
        cout << "Apakah anda ingin keluar? (y/N): ";
        cin >> keluar;
        if (keluar == 'y' || keluar == 'Y') {
            return 0;
        }else if (keluar == 'n' || keluar == 'N') {
            system("cls");
            main();
        }else {
            cout << "Silahkan masukkan huruf dengan perintah yang sesuai" << endl;
            goto keluarprogram;
        }
        break;
    default:
        cout << "Pilih nomor 1 - 5 lalu tekan enter ";
        getch();
        system("cls");
        main();
        break;
    }
    return 0;
}

void TambahPengaduan() {

    // Menampilkan menu baru
    system("cls");

    // Variables
    string nik = "";
    string nama = "";
    string no_telepon = "";
    string kel_bidang = "";
    string isi_peng = "";
    char pilihan;
    // Variables End
    cout <<"\t============================\n"<<endl;
    cout <<"\tFORM TAMBAH PENGADUAN DESA\n"<<endl;
    cout <<"\t============================\n"<<endl;

    cin.ignore(1, '\n');
    cout << "Masukan NIK : ";
    getline(cin, nik);
    cout << "Masukan Nama : ";
    getline(cin, nama);
    cout << "Keluhan Nomor Telepon : ";
    getline(cin, no_telepon);
    cout << "Masukan Bidang Keluhan : ";
    getline(cin, kel_bidang);
    cout << "Masukan Isi Pengaduan : ";
    getline(cin, isi_peng);


    string insert_query = "insert into kaizen (nik, nama, no_telepon, kel_bidang, isi_peng) values ('"+nik+"','"+nama+"','"+no_telepon+"','"+kel_bidang+"', '"+isi_peng+"')";

    const char* q = insert_query.c_str(); // c_str converts string to constant char and this is required

    qstate = mysql_query(conn, q);

    if (!qstate)
    {
        cout << endl << "Pengajuan Anda Berhasil di Ajukan." << endl;
    }
    else
    {
        cout << "Silahkan Isi Form Pengajuan Dengan Benar." << mysql_errno(conn) << endl;
    }

    // Exit Code
    cout << "Tekan 'm' untuk kembali ke menu, Tekan 'a' untuk mengisi lagi, Tekan 'q' untuk keluar: ";
    cin >> pilihan;
    if (pilihan == 'm' || pilihan == 'M')
    {
        main();
    }
    else if (pilihan == 'a')
    {
        TambahPengaduan();
    }
    else
    {
        exit(0);
    }
}

void EditPengaduan() {

    system("cls");

    // Variables
    string nik = "";
    string nama = "";
    string no_telepon = "";
    string kel_bidang = "";
    string isi_peng = "";
    string items[50];
    char pilihan;
    int id;
    bool HaveException = false;
    bool NotInDatabase = false;
    int indexForId = 0;

    // Store Variables
    string storeid = "";
    string storenik = "";
    string storenama = "";
    string storeno_telepon = "";
    string storekel_bidang = "";
    string storeisi_peng = "";
    // Variables End
    cout <<"\t============================\n"<<endl;
    cout <<"\tFORM EDIT PENGADUAN DESA\n"<<endl;
    cout <<"\t============================\n"<<endl;
    qstate = mysql_query(conn, "select * from kaizen");
    if (!qstate)
    {
        res = mysql_store_result(conn);
        cout << ("--------------------------------------------------------\n") <<endl;
        printf("| %-10s | %-15s | %-20s |\n", "ID", "NIK", "NAMA");
        while ((row = mysql_fetch_row(res)))
        {
            printf("| %-10s | %-15s | %-20s |\n", row[0], row[1], row[2]);
            items[indexForId] = row[0];
            indexForId++;
        }
        printf("---------------------------------------------------------\n");
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

    try
    {
        cout << endl;
        cout << "Silahkan pilih ID: ";
        cin >> id;
        cout << endl;
    }
    catch (exception e)
    {
        cout << "Please Enter a valid NUMBER." << endl;
        HaveException = true;
        goto ExitMenu;
    }

    if (HaveException == false)
    {
        stringstream streamid;
        string strid;
        streamid << id;
        streamid >> strid;

        for (int i = 0; i < indexForId; i++)
        {
            if (strid != items[i])
            {
                NotInDatabase = true;
            }else
            {
                NotInDatabase = false;
                break;
            }
        }

        if (NotInDatabase == false)
        {
            string findbyid_query = "select * from kaizen where id = '"+strid+"'";
            const char* qi = findbyid_query.c_str();
            qstate = mysql_query(conn, qi);

            if (!qstate)
            {
                res = mysql_store_result(conn);
                while (row = mysql_fetch_row(res))
                {
                    cout << "ID: " << row[0] << "\nNIK: "
                         << row[1] << "\nNAMA: " << row[2] << "\nNO TELEPON: " << row[3] << "\nBIDANG PENGADUAN: " << row[4] << "\nISI PENGADUAN: " << row[5] << endl << endl;

                    storeid = row[0];
                    storenik = row[1];
                    storenama = row[2];
                    storeno_telepon = row[3];
                    storekel_bidang = row[4];
                    storeisi_peng = row[5];
                }
            }
            else
            {
                cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            }

            cin.ignore(1, '\n');
            string defaultString = "N";
            cout << "Masukkan NIK ( Masukkan huruf ( " << defaultString << " ) jika tidak dirubah ): ";
            getline(cin, nik);
            if (nik == defaultString)
            {
                nik = storenik;
            }
            cout << "Masukkan NAMA ( Masukkan huruf " << defaultString << "  jika tidak dirubah ): ";
            getline(cin, nama);
            if (nama == defaultString)
            {
                nama = storenama;
            }
            cout << "Masukkan No TELEPON ( Masukkan huruf " << defaultString << "  jika tidak dirubah ): ";
            getline(cin, no_telepon);
            if (no_telepon == defaultString)
            {
                no_telepon = storeno_telepon;
            }
            cout << "Masukkan BIDANG KELUHAN ( Masukkan huruf " << defaultString << "  jika tidak dirubah ): ";
            getline(cin, kel_bidang);
            if (kel_bidang == defaultString)
            {
                kel_bidang = storekel_bidang;
            }
            cout << "Masukkan ISI PENGADUAN ( Masukkan huruf " << defaultString << "  jika tidak dirubah ): ";
            getline(cin, isi_peng);
            if (isi_peng == defaultString)
            {
                isi_peng = storeisi_peng;
            }


            string update_query = "update kaizen set nik = '"+nik+"', nama = '"+nama+"', no_telepon = '"+no_telepon+"', kel_bidang = '"+kel_bidang+"', isi_peng = '"+isi_peng+"' where id = '"+strid+"'";
            const char* qu = update_query.c_str();
            qstate = mysql_query(conn, qu);

            if (!qstate)
            {
                cout << endl << "Successfully Saved In Database." << endl;
            }
            else
            {
                cout << "Failed To Update!" << mysql_errno(conn) << endl;
            }

        }
        else
        {
            cout << "ID tidak ada di database" << endl;
        }
    }

    ExitMenu:
    cout << "Masukkan huruf 'm' untuk kembali ke menu atau huruf random untuk keluar : ";
    cin >> pilihan;
    if (pilihan == 'm' || pilihan == 'M')
    {
        main();
    }
    else if (pilihan == 'e' || pilihan == 'E')
    {
        EditPengaduan();
    }
    else
    {
        exit(0);
    }
}

void HapusPengaduan() {
    system("cls");

    // Variables
    char pilihan;
    int itemId;
    string items[5000];
    int indexForId = 0;
    bool HaveException = false, NotInDatabase = false;
    // Variables End

    selamatdatang();
    qstate = mysql_query(conn, "select * from kaizen");
    if (!qstate)
    {
        res = mysql_store_result(conn);
        printf("--------------------------------------------------\n");
        printf("| %-10s | %-15s | %-15s |\n", "ID", "NIK", "NAMA");
        printf("--------------------------------------------------\n");
        while ((row = mysql_fetch_row(res)))
        {
            printf("| %-10s | %-15s | %-15s |\n", row[0], row[1], row[2]);
            items[indexForId] = row[0];
            indexForId++;
        }
        printf("--------------------------------------------------\n");
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

    try
    {
        cout << endl;
        cout << "Enter Item ID: ";
        cin >> itemId;
        cout << endl;
    }
    catch (exception e)
    {
        cout << "Please Enter a valid NUMBER." << endl;
        HaveException = true;
        goto ExitMenu;
    }

    if (HaveException == false)
    {
        stringstream streamid;
        string strid;
        streamid << itemId;
        streamid >> strid;

        for (int i = 0; i < indexForId; i++)
        {
            if (strid != items[i])
            {
                NotInDatabase = true;
            }else
            {
                NotInDatabase = false;
                break;
            }
        }

        if (NotInDatabase == false)
        {
            string delete_query = "delete from kaizen where id = '"+strid+"'";
            const char* qd = delete_query.c_str();
            qstate = mysql_query(conn, qd);

            if (!qstate)
            {
                cout << "Successfully Deleted." << endl;
            }
            else
            {
                cout << "Failed To Delete!" << mysql_errno(conn) << endl;
            }

        }
        else
        {
            cout << "Item Not Found in database." << endl;
        }
    }

    // Exit Code
    ExitMenu:
    cout << "Masukkan huruf 'm' untuk kembali ke menu atau huruf random untuk keluar : ";
    cin >> pilihan;
    if (pilihan == 'm' || pilihan == 'M')
    {
        main();
    }
    else if (pilihan == 'd' || pilihan == 'D')
    {
        HapusPengaduan();
    }
    else
    {
        exit(0);
    }
}

void LihatPengaduan() {
    system("cls");

    // Variables
    char pilihan;
    string input;
    // Variables End

    selamatdatang();
    qstate = mysql_query(conn, "select * from kaizen");
    if (!qstate)
    {
        res = mysql_store_result(conn);
        printf("-------------------------------------------------------------------------------------------------------------\n");
        printf("| %-15s | %-15s | %-15s | %-15s | %-30s |\n", "NIK", "NAMA", "NO TELEPON", "BIDANG PENGADUAN", "ISI PENGADUAN");
        printf("-------------------------------------------------------------------------------------------------------------\n");
        while ((row = mysql_fetch_row(res)))
        {
            printf("| %-15s | %-15s | %-15s | %-16s | %-30s |\n", row[1], row[2], row[3], row[4], row[5], row[6], row[7]);
        }
        printf("-------------------------------------------------------------------------------------------------------------\n");
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

    ExitMenu:
    cout << "Masukkan huruf 'm' untuk kembali ke menu atau huruf random untuk keluar : ";
    cin >> pilihan;
    if (pilihan == 'm' || pilihan == 'M')
    {
        main();
    }
    else
    {
        exit(0);
    }
}

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct SimpulMahasiswa MNode;
typedef struct SimpulMataKuliah MKNode;

struct SimpulMahasiswa{
    int nrp;
    char nama[100];
    MNode *next;
    MNode *prev;
    MKNode *nextMK;
};


struct SimpulMataKuliah{
    int id;
    char namaMatkul[100];
    int nilai;
    MKNode *next;
};

MNode *Mhead = NULL;
MNode *Mtail = NULL;
MNode *Mbaru;

MKNode *MKhead = NULL;
MKNode *MKtail = NULL;
MKNode *MKbaru;

void cleanStdin(){
    int c;
    while(c != '\n' && c != EOF){ c = getchar();}
}

void allocateNodeM(int _nrp, char _nama[]){
    Mbaru = (MNode* ) malloc(sizeof(MNode));

    if(Mbaru == NULL){
        printf("Galat!!. Alokasi Node M Gagal!");
        exit(1);
    }else{
        Mbaru->nrp   = _nrp;
        strcpy(Mbaru->nama, _nama);
        Mbaru->next = NULL;
        Mbaru->prev = NULL;
    }
}

void allocateNodeMK(int _id, char _namaMatkul[]){
    MKbaru = (MKNode* ) malloc(sizeof(MKNode));

    if(MKbaru == NULL){
        printf("Galat!!. Alokasi Node MK Gagal!");
        exit(1);
    }else{
        MKbaru->id = _id;
        strcpy(MKbaru->namaMatkul, _namaMatkul);
        MKbaru->next = NULL;
    }
}

void printLinks(int menu){
    if(menu == 1){
        MNode *PM = Mhead;

        printf("\nNRP\t\tNama\n");
        while(PM != NULL){
            printf("%d\t%s\n", PM->nrp, PM->nama);
            PM = PM->next;
        }
    }else if(menu == 2){
        MKNode *PMK = MKhead;

        printf("\nID\tMata Kuliah\n");
        while(PMK != NULL){
            printf("%d\t%s\n", PMK->id, PMK->namaMatkul);
            PMK = PMK->next;
        }
    }

}

void firstInsert(int menu){
    if(menu == 1){
        if(Mhead == NULL){
            Mhead = Mtail = Mbaru;
        }else{
            Mbaru->next = Mhead;
            Mhead->prev = Mbaru;
            Mhead = Mbaru;
        }
    }else if(menu == 2){
        if(MKhead == NULL){
            MKhead = MKtail = MKbaru;
        }else{
            MKbaru->next = MKhead;
            MKhead = MKbaru;
        }
    }
}

void lastInsert(int menu){
    if(menu == 1){
        Mbaru->prev = Mtail;
        Mtail->next = Mbaru;
        Mtail = Mbaru;
    }else if(menu == 2){
        MKNode *MKtail = MKhead;
        while(MKtail->next != NULL){
            MKtail = MKtail->next;
        }
        MKtail->next = MKbaru;
    }

}

void insertBefore(int menu, int target){
    if(menu == 1){
        MNode *Mbefore = Mhead;

        if(Mhead->nrp == target){
            firstInsert(menu);
        }else{
            while(Mbefore != NULL && Mbefore->nrp != target){
                Mbefore = Mbefore->next;
            }

            if(Mbefore == NULL){
                printf("Simpul tidak ada");
            }else{
                Mbaru->prev = Mbefore->prev;
                Mbaru->next = Mbefore;
                Mbefore->prev->next = Mbaru;
                Mbefore->prev = Mbaru;
            }
        }
    }else if(menu == 2){
        MKNode *MKbefore = MKhead;

        if(MKhead->id == target){
            firstInsert(menu);
        }else{
            MKNode *MKbefore = MKhead;
            while(MKbefore->next->id != target){
                MKbefore = MKbefore->next;
            }
            MKbaru->next = MKbefore->next;
            MKbefore->next = MKbaru;
        }
    }
}


void insertLinks(int menu){
    if(menu == 1){
        MNode *Mbefore = Mhead;

        if(Mhead == NULL){
            Mhead = Mtail = Mbaru;
        }else if(Mhead->nrp > Mbaru->nrp){
            firstInsert(menu);
        }else{
            MNode *Mbefore = Mhead;

            while(Mbefore != NULL && Mbefore->nrp < Mbaru->nrp){
                Mbefore = Mbefore->next;
            }

            if(Mbefore == NULL){
                lastInsert(menu);
            }else if(Mbefore->nrp == Mbaru->nrp){
                printf("Duplicate Mahasiswa");
            }else{
                insertBefore(menu, Mbefore->nrp);
            }
        }
    }else if(menu == 2){
        MKNode *MKbefore = MKhead;

        if(MKhead == NULL){
            MKhead = MKtail = MKbaru;
        }else if(MKhead->id > MKbaru->id){
            firstInsert(menu);
        }else{
            MKNode *MKbefore = MKhead;

            while(MKbefore != NULL && MKbefore->id < MKbaru->id){
                MKbefore = MKbefore->next;
            }

            if(MKbefore == NULL){
                lastInsert(menu);
            }else if(MKbefore->id == MKbaru->id){
                printf("Duplicate Mata Kuliah");
            }else{
                insertBefore(menu, MKbefore->id);
            }
        }
    }
}

void freeNodeM(MNode *p){
    free(p);
    p = NULL;
}

void freeNodeMK(MKNode *p){
    free(p);
    p = NULL;
}

void firstDelete(int menu){
    if(menu == 1){
        MNode *Mdelete = Mhead;
        Mhead->next->prev=NULL;
        Mhead = Mdelete->next;
        freeNodeM(Mdelete);
    }else if(menu == 2){
        MKNode *MKdelete = MKhead;
        MKhead = MKdelete->next;
        freeNodeMK(MKdelete);
    }
}

void lastDelete(int menu){
    if(menu == 1){
        MNode *Mdelete = Mtail;
        Mtail->prev->next = NULL;
        Mdelete->prev = Mtail;
        freeNodeM(Mdelete);
    }else if(menu == 2){
        MKNode *MKdelete, *MKbefore;
        MKdelete = MKbefore = MKhead;

        while(MKdelete->next != NULL){
            MKbefore = MKdelete;
            MKdelete = MKdelete->next;
        }

        MKbefore->next= NULL;
        freeNodeMK(MKdelete);
    }

}

void deleteLinks(int menu, int target){
    if(menu == 1){
        MNode *Mdelete, *Mbefore;
        Mdelete = Mbefore = Mhead;

        if(Mdelete == NULL){
            printf("Data Kosong\n");
        }else if (Mdelete->nrp == target){
            firstDelete(menu);
        }else{
            while (Mdelete != NULL && Mdelete->nrp != target){
                Mbefore = Mdelete;
                Mdelete = Mdelete->next;
            }

            if (Mdelete == NULL)
                printf("Data tidak ada\n");
            else{
                Mbefore->next = Mdelete->next;
                freeNodeM(Mdelete);
            }
        }
    }else if(menu == 2){
        MKNode *MKdelete, *MKbefore;
        MKdelete = MKbefore = MKhead;

        if(MKdelete == NULL){
            printf("Data Kosong\n");
        }else if (MKdelete->id == target){
            firstDelete(menu);
        }else{
            while (MKdelete != NULL && MKdelete->id != target){
                MKbefore = MKdelete;
                MKdelete = MKdelete->next;
            }

            if (MKdelete == NULL)
                printf("Data tidak ada\n");
            else{
                MKbefore->next = MKdelete->next;
                freeNodeMK(MKdelete);
            }
        }
    }
}


void MatkulToMahasiswa(int _nrp){
    MNode *Mselect, *Mbefore;
    Mselect = Mbefore = Mhead;

    MKNode *MKselect, *MKbefore;
    MKselect = MKbefore = MKhead;

    MKNode *newMKhead = NULL, *newMKtail = NULL;

    int i, _countMatkul, _selectID;

    if(Mselect == NULL){
        printf("Data mahasiswa tidak ditemukan\n");
    }else{
        while (Mselect->nrp != _nrp){
            Mbefore = Mselect;
            Mselect = Mselect->next;
        }

        printf("Nama Mahasiswa : %s\n", Mselect->nama);
        printLinks(2);
        printf("Masukan jumlah mata kuliah yang akan dipilih : ");
        scanf("%d", &_countMatkul);

        for(i=1; i<=_countMatkul; i++){
            printf("Masukan ID Mata Kuliah ke-%d yang dipilih : ", i);
            scanf("%d", &_selectID);

            if(MKselect == NULL){
                printf("Data mata kuliah tidak ditemukan\n");
            }else{
                while(MKselect->id != _selectID){
                    MKbefore = MKselect;
                    MKselect = MKselect->next;
                    //Menemukan data Matkul
                }

            // Sisip awal ke mata kuliah mahasiswa;
            // * MKselect berisi mata kuliah yang diselect ( baru )* //
            printf("%d %s\n", MKselect->id, MKselect->namaMatkul);

                if(Mselect->nextMK == NULL){
                    //Jika Mahasiswa masih belum punya matkul, maka sisip awal.
                    newMKhead = Mselect->nextMK;
                    newMKtail = Mselect->nextMK;
                    Mselect->nextMK = MKselect;
                    /*if(Mselect->nextMK != NULL){
                        printf("Sudah diisi %d %s\n", Mselect->nextMK->id, Mselect->nextMK->namaMatkul);
                    }else{
                        printf("Masih NULL\n");
                    }*/

                }else{
                    //Jika mahasiswa sudah punya matkul dan ingin menambahkan ulang maka, sisip akhir.
                    newMKtail = newMKhead = Mselect->nextMK;
                    while(newMKtail->next != NULL){
                        newMKtail = newMKtail->next;
                    }
                    MKselect->next = NULL;
                    newMKtail->next = MKselect;
                    //printf("Sudah diisi %d %s\n", MKselect->id, MKselect->namaMatkul);
                }
            }
        }
    }
}

void printAllDataMahasiswa(){

    MNode *PM = Mhead;
    MKNode *cek = PM->nextMK;

    printf("\nNRP\t\tNama\n");
    while(PM != NULL){
        printf("%d\t%s\n", PM->nrp, PM->nama);
        /*Anjayyyy*/
        while(PM->nextMK != NULL){
            //loop hasil pilih matkul mahasiswa
            printf("%d\t%s\n", PM->nextMK->id, PM->nextMK->namaMatkul);
            PM->nextMK = PM->nextMK->next;
        }
        /*Stuck*/
        if(cek == NULL){
            printf("Mahasiswa belum memilih matkul\n");
        }
        PM = PM->next;
    }
}



int main(){
    int menu, _nrp, _id, countMhs, countMK, i;
    char _nama[100], _namaMatkul[100], repeat = 'y';

    int qMhs = 1, qMk = 2;

    printf("======================== Program Pemilihan SKS Mahasiswa =======================\n\n");
    printf("\t1. Masukan Data Mahasiswa\n");
    printf("\t2. Masukan Daftar Mata Kuliah\n");
    printf("\t3. Masukan Mata Kuliah Mahasiswa\n");
    printf("\t4. Tampilkan Data SKS Mahasiswa\n");
    printf("\t5. Hapus Mahasiswa\n");
    printf("\t6. Hapus Mata Kuliah\n");

    while(repeat == 'y' || repeat == 'Y'){
        printf("\nPilih : ");
        scanf("%d", &menu);

        switch(menu){
            case 1:
                printf("Masukan banyak mahasiswa : ");
                scanf("%d", &countMhs);

                for(i=1; i<=countMhs; i++){
                    printf("Masukan NRP Mahasiswa-%d : ", i);
                    scanf("%d", &_nrp);
                    printf("Masukan Nama Mahasiswa-%d : ", i);
                    cleanStdin();
                    gets(_nama);
                    allocateNodeM(_nrp, _nama);
                    insertLinks(menu);
                    printf("\n");
                }

                printLinks(qMhs);
                break;
            case 2:
                printf("Masukan banyak mata kuliah : ");
                scanf("%d", &countMK);

                for(i=1; i<=countMK; i++){
                    printf("Masukan ID Mata Kuliah-%d : ", i);
                    scanf("%d", &_id);
                    printf("Masukan Nama Mata kuliah-%d : ", i);
                    cleanStdin();
                    gets(_namaMatkul);
                    allocateNodeMK(_id, _namaMatkul);
                    insertLinks(menu);
                    printf("\n");
                }
                printLinks(qMk);
                break;
            case 3:
                printf("Masukan NRP Mahasiswa : ");
                scanf("%d", &_nrp);
                MatkulToMahasiswa(_nrp);
                cleanStdin();
                break;
            case 4:
                printAllDataMahasiswa();
                break;
            case 5:
                printf("Masukan NRP Mahasiswa yang dihapus : ");
                scanf("%d", &_nrp);
                deleteLinks(qMhs, _nrp);
                printLinks(qMhs);
                break;
            case 6:
                printf("Masukan ID Mata Kuliah yang dihapus : ");
                scanf("%d", &_id);
                deleteLinks(qMk, _nrp);
                printLinks(qMk);
                printLinks(qMk);
                break;
            default:
                printf("Error! Out of Range menu");
                break;
        }


        printf("\nRepeat? (Y\N) : ");
        scanf("%c", &repeat);
    }

}

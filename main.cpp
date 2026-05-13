#include <iostream>
#include <cstring>
using namespace std;

// Object Node
struct Node {
    int nomor_urut;
    char nama[50];
    int prioritas;
    struct Node *next;
    struct Node *prev;
};

// Global variabel
int counter_urut = 0;
Node *head = NULL;
Node *tail = NULL;

int isEmpty()
{
    if(head == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// Fungsi untuk mendaftarkan nasabah baru ke dalam antrean
void enqueue(char *nama, int prioritas)
{
    Node *new_node = new Node();

    counter_urut++;
    new_node->nomor_urut = counter_urut;
    strcpy(new_node->nama, nama);
    new_node->prioritas = prioritas;
    new_node->next = NULL;
    new_node->prev = NULL;

    if(isEmpty())
    {
        head = new_node;
        tail = new_node;
        head->next = head;
        head->prev = head;
    }
    else if(prioritas == 1)
    {
        Node *current = head;
        Node *lastPriority = NULL;

        do {
            if(current->prioritas == 1){
                lastPriority = current;
            }

            current = current->next;
        } while (current != head);

        if(lastPriority == NULL)
        {
            new_node->next = head;
            new_node->prev = tail;
            head->prev = new_node;
            tail->next = new_node;

            head = new_node;
        }
        else if(lastPriority == tail)
        {
            new_node->next = head;
            new_node->prev = tail;
            head->prev = new_node;
            tail->next = new_node;

            tail = new_node;
        }
        else
        {
            Node *after_last_priority = lastPriority->next;

            new_node->next = after_last_priority;
            new_node->prev = lastPriority;
            lastPriority->next = new_node;
            after_last_priority->prev = new_node;
        }
    }
    else
    {
        new_node->next = head;
        new_node->prev = tail;
        tail->next = new_node;
        head->prev = new_node;

        tail = new_node;
    }

    printf("Nasabah %s berhasil ditambahkan ke dalam antrean, dengan nomor urut %d\n", nama, new_node->nomor_urut);
}

// Fungsi untuk memanggil nasabah berikutnya dari antrian (dari depan/head)
void dequeue()
{
    if(isEmpty()){
        printf("Antrian Kosong. Tidak ada nasabah yang akan dipanggil\n");
    }
    else{
        printf("\n>>>> Memanggil Nasabah <<<<\n");
        printf("No Urut : %d\n", head->nomor_urut);
        printf("Nama    : %s\n", head->nama);
        printf("Status  : %s\n", head->prioritas ? "Prioritas" : "Reguler");
        printf("Silakan menuju ke teller yang telah di tunjukkan.\n");

        if(head == tail){
            delete head;
            head = NULL;
            tail = NULL;
        }
        else{
            Node *temp = head;
            head = head->next;
            head->prev = tail;
            tail->next = head;
            delete temp;
        }
    }
}

// Fungsi untuk memanggil semua antrian nasabah
void displayAll()
{
    if(isEmpty()){
        printf("Antrian kosong, tidak ada nasabah yang terdaftar.\n");
    }
    else{
        Node *current = head;
        int posisi = 1;
        printf("\n%-5s %-10s %-25s %-10s\n", "Antri", "No.Urut", "Nama Nasabah", "Status");
        printf("----------------------------------------------------------------\n");

        do{
            printf("\n%-5d %-10d %-25s %-10s\n", posisi++, current->nomor_urut, current->nama, current->prioritas ? "Prioritas":"Reguler");
            current = current->next;
        }while(current != head);
    }
}

// Fungsi untuk menghapus semua antrian nasabah
void deleteAll()
{
    if(isEmpty()){
        printf("Antrian kosong, tidak ada nasabah yang dapat dihapus !\n");
    }
    else{
        tail->next = NULL;

        Node *current = head;
        while(current != NULL){
            Node *temp = current;
            current = current->next;
            delete temp;
        }

        head = NULL;
        tail = NULL;

        counter_urut = 0;
        printf("Semua data antrian nasabah berhasil dihapus !\n");
    }
}

// Program Utama
int main()
{
    int choice;
    char nama[50];
    
    while(choice != 0){
        printf("\nProgram Antrian Nasabah Bank dengan Linked List\n");
        printf("=======================================================\n");
        printf("1. Daftarkan nasabah reguler\n");
        printf("2. Daftarkan nasabah prioritas\n");
        printf("3. Panggil Nasabah berikutnya\n");
        printf("4. Tampilkan Semua Antrian Nasabah\n");
        printf("5. Hapus Semua Antrian Nasabah\n");
        printf("0. Keluar\n");
        printf("=======================================================\n");
        printf("> ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                printf("Masukkan nama nasabah: ");
                scanf(" %[^\n]", nama);
                enqueue(nama, 0);
                break;
            case 2:
                printf("Masukkan nama nasabah: ");
                scanf(" %[^\n]", nama);
                enqueue(nama, 1);
                break;
            case 3:
                dequeue();
                continue;
            case 4:
                displayAll();
                break;
            case 5:
                deleteAll();
                break;
            case 0:
                printf("Terima kasih!");
                break;
        }
    }

    return 0;
}
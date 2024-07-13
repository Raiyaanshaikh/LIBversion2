#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h> 

typedef struct
{ 
    int id;
    char title[50];
    char author[50];
}Book;
void addbook();
void displayBooks();
void modifyBook();
void deleteBook();

int main() 
{
    system("color 7A");
    int choice;

    {
        
        

    
        printf("\n*** Library Management System ***\n");
        printf("1. Add Book\n");
        printf("2. Display Books\n");
        printf("3. Modify Book\n");
        printf("4. Delete Book\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1: addBook(); break;
            case 2: displayBooks(); break;
            case 3: modifyBook(); break;
            case 4: deleteBook(); break;
            case 5: exit;
                    break;
            default: printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}


void addBook() {
    FILE *file = fopen("library.dat", "ab");
    if (file == NULL) {
        printf("Error opening file");
        return;
    }

    Book newBook;
    printf("Enter Book ID: ");
    scanf("%d", &newBook.id);
    getchar(); // Consume newline
    printf("Enter Book Title: ");
    fgets(newBook.title, sizeof(newBook.title), stdin);
    strtok(newBook.title, "\n"); // Remove newline character
    printf("Enter Book Author: ");
    fgets(newBook.author, sizeof(newBook.author), stdin);
    strtok(newBook.author, "\n"); // Remove newline character

    fwrite(&newBook, sizeof(Book), 1, file);
    fclose(file);

    printf("Book added successfully.\n");
}

void displayBooks() {
    FILE *file = fopen("library.dat", "rb");
    if (file == NULL) {
        printf("Error opening file");
        return;
    }

    Book book;
    printf("\n*** List of Books ***\n");
    while (fread(&book, sizeof(Book), 1, file)) {
        printf("ID: %d\n", book.id);
        printf("Title: %s\n", book.title);
        printf("Author: %s\n", book.author);
        printf("\n");
    }

    fclose(file);
}

void modifyBook() {
    FILE *file = fopen("library.dat", "r+b");
    if (file == NULL) {
        printf("Error opening file");
        return;
    }

    int id;
    Book book;
    printf("Enter Book ID to modify: ");
    scanf("%d", &id);
    getchar(); // Consume newline

    while (fread(&book, sizeof(Book), 1, file)) {
        if (book.id == id) {
            fseek(file, -sizeof(Book), SEEK_CUR);
            printf("Enter new Book Title: ");
            fgets(book.title, sizeof(book.title), stdin);
            strtok(book.title, "\n"); // Remove newline character
            printf("Enter new Book Author: ");
            fgets(book.author, sizeof(book.author), stdin);
            strtok(book.author, "\n"); // Remove newline character
            fwrite(&book, sizeof(Book), 1, file);
            printf("Book modified successfully.\n");
            break;
        }
    }

    fclose(file);
}

void deleteBook() {
    FILE *file = fopen("library.dat", "rb");
    FILE *tempFile = fopen("temp.dat", "wb");
    if (file == NULL || tempFile == NULL) {
        printf("Error opening file");
        return;
    }

    int id;
    Book book;
    printf("Enter Book ID to delete: ");
    scanf("%d", &id);
    getchar(); // Consume newline

    while (fread(&book, sizeof(Book), 1, file)) {
        if (book.id != id) {
            fwrite(&book, sizeof(Book), 1, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);
    remove("library.dat");
    rename("temp.dat", "library.dat");

    printf("Book deleted successfully.\n");
}



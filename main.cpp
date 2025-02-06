#include <stdio.h>
#include<conio.h>
#include<stdlib.h>
#include <string.h>
#include <time.h>


#define MAX_BOOKS 100
#define MAX_TITLE_LENGTH 100
#define MAX_AUTHOR_LENGTH 50

#define MAX_USERS 50
#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define MAX_BORROWED_BOOKS 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    int is_admin;
} User;

User users[MAX_USERS];
int num_users = 0;


typedef struct {
    int book_id;
    char title[MAX_TITLE_LENGTH];
    char author[MAX_AUTHOR_LENGTH];
    int is_available; 
    int quantity; 
} Book;

Book library[MAX_BOOKS];
int num_books = 0; 


typedef struct {
    int book_id;
    char title[MAX_TITLE_LENGTH];
} BorrowedBook;

BorrowedBook borrowed_books[MAX_USERS][MAX_BORROWED_BOOKS];
int num_borrowed_books[MAX_USERS];

char loggedInUser[MAX_USERNAME_LENGTH];
char userLoggedIn[MAX_USERNAME_LENGTH];

void registerUser();
int loginUser();
void saveUsers();
void loadUsers();
void removeUsers();
void addBook();
void deleteBook();
void searchBook();
void listBooks();
void updateBook();
void borrowBook();
void returnBook();
void sortBooks();
void saveLibrary();
void loadLibrary();
void delay(int number_of_seconds);
void inputPassword(char password[]);


int main() {

    loadLibrary(); 
    loadUsers();

    int is_admin = -1;
    int choice;

    while (1) {
        if (is_admin == -1) {
        	printf("\n\t\t********************************\n");
   			printf("\t\t    LIBRARY MANAGEMENT SYSTEM");
			printf("\n\t\t********************************\n\n");
            // Register/Login/Exit Menu
            printf("\n1. Register\n2. Login\n3. Exit\nEnter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    registerUser();
                    delay(3);
					system("cls");
                    break;
                case 2:
                    is_admin = loginUser();
                    delay(3);
                    system("cls");
                    break;
                case 3:
                    printf("Exiting program...\n");
                    return 0;
                default:
                    printf("Invalid choice. Please enter a number between 1 and 3.\n");
            }
        } else if (is_admin == 1) {
            // Admin Menu
            printf("\n\t    ***********************\n");
            printf("\t         WELCOME ADMIN");
            printf("\n\t    ***********************\n\n");
            printf("1. Add Book\n");
            printf("2. Delete Book\n");
            printf("3. Search Book\n");
            printf("4. List All Books\n");
            printf("5. Update Book\n");
            printf("6. Sort Books\n");
            printf("7. Remove User\n");
            printf("8. Logout\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    addBook();
                    break;
                case 2:
                    deleteBook();
                    break;
                case 3:
                    searchBook();
                    break;
                case 4:
                    listBooks();
                    break;
                case 5:
                    updateBook();
                    break;
                case 6:
                    sortBooks();
                    break;
                case 7:
                    removeUsers();
                    break;
                case 8:
                    printf("Logging out...\n");
                    delay(3);
                    system("cls");
                    is_admin = -1;
                    break;
                default:
                    printf("Invalid choice. Please enter a number between 1 and 10.\n");
            }
        } else if (is_admin == 0) {
            // User Menu
            printf("\n\t    *************************\n");
            printf("\t         WELCOME %s",loggedInUser);
            printf("\n\t    *************************\n\n");
            printf("1. Search Book\n");
            printf("2. List All Books\n");
            printf("3. Borrow Book\n");
            printf("4. Return Book\n");
            printf("5. Logout\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    searchBook();
                    break;
                case 2:
                    listBooks();
                    break;
                case 3:
                    borrowBook();
                    break;
                case 4:
                    returnBook();
                    break;
                case 5:
                    printf("Logging out...\n");
                    delay(3);
                    system("cls");
                    is_admin = -1;
                    break;
                default:
                    printf("Invalid choice. Please enter a number between 1 and 5.\n");
            }
        }
    }

    return 0;
}


void registerUser() {
    printf("\n\n\t********************************\n");
    printf("\t\tUSER REGISTRATION");
    printf("\n\t********************************\n\n");

    if (num_users >= MAX_USERS) {
        printf("Maximum number of users reached.\n");
        return;
    }

    User newUser;

    printf("Enter username: ");
    scanf("%s", newUser.username);
	if(strcmp(newUser.username,"admin") == 0 ){
		printf("Username already taken. Please choose another.\n");
        return;
	}
    for (int i = 0; i < num_users; ++i) {
		if (strcmp(users[i].username, newUser.username) == 0) {
            printf("Username already taken. Please choose another.\n");
            return;
        }
    }

    printf("Enter password: ");
    scanf("%s", newUser.password);

    newUser.is_admin = 0;

    users[num_users++] = newUser;

    printf("User registered successfully.\n");
    saveUsers();
}


int loginUser() {
    printf("\n\n\t********************************\n");
    printf("\t\tUSER LOGIN");
    printf("\n\t********************************\n\n");

    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
	inputPassword(password);
    strcpy(userLoggedIn, username);
    if (strcmp("admin", username) == 0 && strcmp("admin123", password) == 0) {
    	printf("Login successful!\n");
       	return 1;
    }
    for (int i = 0; i < num_users; ++i) {
        if (strcmp(users[i].username, username) == 0 &&
            strcmp(users[i].password, password) == 0) {
	        printf("Login successful!\n");
	for(int j = 0; j<MAX_USERNAME_LENGTH; j++){
		if(username[j]>=97 && username[j]<=122)
            loggedInUser[j] = username[j]-32;
		else
			loggedInUser[j] = username[j];
		}
			return users[i].is_admin;
        }
    }

    printf("Invalid username or password.\n");
    return -1;
}


void saveUsers() {
    FILE *file = fopen("user_data.txt", "w");
    if (file == NULL) {
        return;
    }

    for (int i = 0; i < num_users; ++i) {
        fprintf(file, "%s\n%s\n%d\n", users[i].username, users[i].password, users[i].is_admin);
    }

    fclose(file);
}


void loadUsers() {
    FILE *file = fopen("user_data.txt", "r");
    if (file == NULL) {
        return;
    }

    num_users = 0;
    while (fscanf(file, "%s\n%s\n%d\n", users[num_users].username, users[num_users].password, &users[num_users].is_admin) != EOF) {
        num_users++;
    }

    fclose(file);
}


void removeUsers() {
    printf("\n\n\t********************************\n");
    printf("\t\tREMOVE USER SECTION");
    printf("\n\t********************************\n\n");

    if (num_users == 0) {
        printf("No users to remove.\n");
        return;
    }

    printf("\nList of Users:\n");
   	printf("%-10s %-20s %-20s %-10s\n", "ID", "Username", "Password", "Is_Amdin");
    printf("-------------------------------------------------------------------\n");

    for (int i = 0; i < num_users; ++i) {
            printf("%-10d %-20s %-20s %-10d\n", 
            i+1, 
            users[i].username, 
            users[i].password, 
            users[i].is_admin);
        
    }

    int id;
    printf("Enter the ID of the user you want to remove: ");
    scanf("%d", &id);

    if (id < 0 || id > num_users) {
        printf("Invalid user ID.\n");
        return;
    }

    char confirm;
    printf("Are you sure you want to remove user \"%s\"? (y/n): ", users[id - 1].username);
    scanf(" %c", &confirm);

    if (confirm == 'y' || confirm == 'Y') {
        printf("User \"%s\" removed successfully.\n", users[id - 1].username);
        for (int i = id - 1; i < num_users - 1; ++i) {
            users[i] = users[i + 1];
        }

        num_users--; 

        saveUsers();
    } else {
        printf("User removal cancelled.\n");
    }
}


void addBook() {
    printf("\n\n\t********************************\n");
    printf("\t\tADD BOOK SECTION");
    printf("\n\t********************************\n\n");

    if (num_books == MAX_BOOKS) {
        printf("Sorry, the library is full.\n");
        return;
    }

    Book newBook;

    printf("Enter book ID: ");
    scanf("%d", &newBook.book_id);

    for (int i = 0; i < num_books; ++i) {
        if (library[i].book_id == newBook.book_id) {
            printf("Book ID already exists.\n");
            return;
        }
    }

    printf("Enter title of the book: ");
    getchar(); 
    fgets(newBook.title, MAX_TITLE_LENGTH, stdin);
    newBook.title[strlen(newBook.title) - 1] = '\0'; 

    printf("Enter author of the book: ");
    fgets(newBook.author, MAX_AUTHOR_LENGTH, stdin);
    newBook.author[strlen(newBook.author) - 1] = '\0'; 

    printf("Enter quantity of the book: ");
    scanf("%d", &newBook.quantity);
    newBook.is_available = newBook.quantity > 0 ? 1 : 0; 

    library[num_books++] = newBook;

    printf("Book added successfully.\n");
    saveLibrary();
}



void deleteBook() {
    printf("\n\n\t********************************\n");
    printf("\t\tDELETE BOOK SECTION");
    printf("\n\t********************************\n\n");

	printf("%-10s %-30s %-20s %-15s %-10s\n", "Book ID", "Title", "Author", "Quantity","Available");
    printf("----------------------------------------------------------------------------------------\n");

    if (num_books == 0) {
        printf("No books in the library to delete.\n");
        return;
    }
    for (int i = 0; i < num_books; ++i) {
           printf("%-10d %-30s %-20s %-15d %-10s\n", 
            library[i].book_id, 
            library[i].title, 
            library[i].author, 
            library[i].quantity,
            library[i].is_available? "Yes" : "No");
    }
    int id;
    printf("Enter the ID of the book you want to delete: ");
    scanf("%d", &id);

    int found = 0;
    for (int i = 0; i < num_books; ++i) {
        if (library[i].book_id == id) {
            found = 1;
            
            for (int j = i; j < num_books - 1; ++j) {
                library[j] = library[j + 1];
            }
            num_books--;

            printf("Book with ID %d deleted successfully.\n", id);
            break;
        }
    }

    if (!found) {
        printf("Book with ID %d not found in the library.\n", id);
    }

    saveLibrary();
}



void searchBook() {
    printf("\n\n\t********************************\n");
    printf("\t\tSEARCH BOOK SECTION");
    printf("\n\t********************************\n\n");

    if (num_books == 0) {
        printf("No books available in the library.\n");
        return;
    }

    char search_input[MAX_TITLE_LENGTH];
    printf("Search Books: ");
    getchar(); 
    fgets(search_input, MAX_TITLE_LENGTH, stdin);
    search_input[strlen(search_input) - 1] = '\0';

    int found = 0;
    printf("\nSEARCH RESULT:\n\n");
   	printf("%-10s %-30s %-20s %-15s %-10s\n", "Book ID", "Title", "Author", "Quantity","Available");
    printf("----------------------------------------------------------------------------------------\n");
	for (int i = 0; i < num_books; ++i) {
        if (strncasecmp(library[i].title, search_input, strlen(search_input)) == 0) {
            printf("%-10d %-30s %-20s %-15d %-10s\n", 
            	library[i].book_id, 
           		library[i].title, 
           		library[i].author, 
            	library[i].quantity,
            	library[i].is_available? "Yes" : "No");
            found = 1;
        }
    }

    if (!found) {
        printf("No books found matching '%s'.\n", search_input);
    }
}



void listBooks() {
    printf("\n\n\t********************************\n");
    printf("\t\tLIST BOOKS SECTION");
    printf("\n\t********************************\n\n");

    if (num_books == 0) {
        printf("No books available in the library.\n");
        return;
    }

	printf("%-10s %-30s %-20s %-15s %-10s\n", "Book ID", "Title", "Author", "Quantity","Available");
    printf("----------------------------------------------------------------------------------------\n");
    
    for (int i = 0; i < num_books; ++i) {
        printf("%-10d %-30s %-20s %-15d %-10s\n", 
    		library[i].book_id, 
        	library[i].title, 
        	library[i].author, 
       		library[i].quantity,
        	library[i].is_available? "Yes" : "No");
    }
}



void updateBook() {
    printf("\n\n\t********************************\n");
    printf("\t\tUPDATE BOOK SECTION");
    printf("\n\t********************************\n\n");

    if (num_books == 0) {
        printf("No books in the library to update.\n");
        return;
    }

    int id;
    printf("Enter the ID of the book you want to update: ");
    scanf("%d", &id);

    int found = 0;
    for (int i = 0; i < num_books; ++i) {
        if (library[i].book_id == id) {
            found = 1;

            printf("Current Title: %s\n", library[i].title);
            printf("Enter new title (or press Enter to keep it unchanged): ");
            getchar(); 
            char new_title[MAX_TITLE_LENGTH];
            fgets(new_title, MAX_TITLE_LENGTH, stdin);
            if (new_title[0] != '\n') {
                new_title[strlen(new_title) - 1] = '\0'; 
                strcpy(library[i].title, new_title);
            }

            printf("Current Author: %s\n", library[i].author);
            printf("Enter new author (or press Enter to keep it unchanged): ");
            char new_author[MAX_AUTHOR_LENGTH];
            fgets(new_author, MAX_AUTHOR_LENGTH, stdin);
            if (new_author[0] != '\n') {
                new_author[strlen(new_author) - 1] = '\0';
                strcpy(library[i].author, new_author);
            }

            printf("Current Quantity: %d\n", library[i].quantity);
            printf("Enter new quantity (or press Enter to keep it unchanged): ");
            char new_quantity_str[10];
            fgets(new_quantity_str, 10, stdin);
            if (new_quantity_str[0] != '\n') {
                int new_quantity = atoi(new_quantity_str);
                library[i].quantity = new_quantity;
                library[i].is_available = (new_quantity > 0) ? 1 : 0; 
            }

            printf("Book updated successfully.\n");
            saveLibrary();
            break;
        }
    }

    if (!found) {
        printf("Book with ID %d not found in the library.\n", id);
    }
}


void borrowBook() {
    printf("\n\n\t********************************\n");
    printf("\t\tBORROW BOOK SECTION");
    printf("\n\t********************************\n\n");

    if (num_books == 0) {
        printf("No books available to borrow.\n");
        return;
    }

    printf("Available Books:\n");
    printf("%-10s %-30s %-20s %-15s %-10s\n", "Book ID", "Title", "Author", "Quantity","Available");
    printf("------------------------------------------------------------------------------------\n");
    for (int i = 0; i < num_books; ++i) {
        if (library[i].is_available == 1 && library[i].quantity > 0) {
           printf("%-10d %-30s %-20s %-15d %-10s\n", 
            library[i].book_id, 
            library[i].title, 
            library[i].author, 
            library[i].quantity,
            library[i].is_available? "Yes" : "No");
    
        }
    }

    int id;
    printf("Enter the ID of the book you want to borrow: ");
    scanf("%d", &id);

    int user_index = -1;
    for (int i = 0; i < num_users; ++i) {
        if (strcmp(users[i].username, userLoggedIn) == 0) {
            user_index = i;
            break;
        }
    }

    if (user_index == -1) {
        printf("User not found.\n");
        return;
    }

    for (int i = 0; i < num_borrowed_books[user_index]; ++i) {
        if (borrowed_books[user_index][i].book_id == id) {
            printf("You have already borrowed this book.\n");
            return;
        }
    }

    int found = 0;
    for (int i = 0; i < num_books; ++i) {
        if (library[i].book_id == id && library[i].is_available == 1 && library[i].quantity > 0) {
            found = 1;
            library[i].quantity--;
            if (library[i].quantity == 0) {
                library[i].is_available = 0;
            }

            borrowed_books[user_index][num_borrowed_books[user_index]].book_id = library[i].book_id;
            strcpy(borrowed_books[user_index][num_borrowed_books[user_index]].title, library[i].title);
            num_borrowed_books[user_index]++;

            printf("Book borrowed successfully!\n");
            saveLibrary();
            return;
        }
    }

    if (!found) {
        printf("Book with ID %d not found or unavailable.\n", id);
    }
}


void returnBook() {
    printf("\n\n\t********************************\n");
    printf("\t\tRETURN BOOK SECTION");
    printf("\n\t********************************\n\n");

    int user_index = -1;
    for (int i = 0; i < num_users; ++i) {
        if (strcmp(users[i].username, userLoggedIn) == 0) {
            user_index = i;
            break;
        }
    }

    if (user_index == -1) {
        printf("User not found.\n");
        return;
    }

    if (num_borrowed_books[user_index] == 0) {
        printf("You haven't borrowed any books.\n");
        return;
    }

    printf("Books you've borrowed:\n");
    printf("%-15s %-30s\n", "Book ID", "Title");
    printf("-----------------------------------------\n");

    for (int i = 0; i < num_borrowed_books[user_index]; ++i) {
        printf("%-15d %-30s\n", borrowed_books[user_index][i].book_id, borrowed_books[user_index][i].title);
    }

    int book_id;
    printf("Enter the ID of the book you want to return: ");
    scanf("%d", &book_id);

    int found = 0;

    for (int i = 0; i < num_borrowed_books[user_index]; ++i) {
        if (borrowed_books[user_index][i].book_id == book_id) {
            found = 1;

            for (int j = 0; j < num_books; ++j) {
                if (library[j].book_id == book_id) {
                    library[j].quantity++;
                    library[j].is_available = 1;
                    printf("Book '%s' returned successfully.\n", borrowed_books[user_index][i].title);

                    for (int k = i; k < num_borrowed_books[user_index] - 1; ++k) {
                        borrowed_books[user_index][k] = borrowed_books[user_index][k + 1];
                    }
                    num_borrowed_books[user_index]--;
                    break;
                }
            }
            break;
        }
    }

    if (!found) {
        printf("Book with ID %d is not in your borrowed list.\n", book_id);
    }

    saveLibrary(); 
}


void sortBooks() {
    printf("\n\n\t********************************\n");
    printf("\t\tSORT BOOK SECTION");
    printf("\n\t********************************\n\n");

    if (num_books == 0) {
        printf("No books available to sort.\n");
        return;
    }

    int choice;
    printf("Choose Sorting Type:\n");
    printf("1. Sort by ID\n");
    printf("2. Sort by Title\n");
    printf("3. Sort by Author\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    Book temp;

    for (int i = 0; i < num_books - 1; i++) {
        for (int j = 0; j < num_books - i - 1; j++) {
            int swap = 0;

            // Sorting by ID
            if (choice == 1) {
                if (library[j].book_id > library[j + 1].book_id) {
                    swap = 1;
                }
            }
            // Sorting by Title
            else if (choice == 2) {
                if (strcasecmp(library[j].title, library[j + 1].title) > 0) {
                    swap = 1;
                }
            }
            // Sorting by Author
            else if (choice == 3) {
                if (strcasecmp(library[j].author, library[j + 1].author) > 0) {
                    swap = 1;
                }
            }
            
            if (swap) {
                temp = library[j];
                library[j] = library[j + 1];
                library[j + 1] = temp;
            }
        }
    }

    if (choice < 1 || choice > 3) {
        printf("\nInvalid choice! Please select a valid option.\n");
        return;
    }

    printf("\nSorted list of books:\n");
    printf("%-10s %-30s %-20s %-15s %-10s\n", "Book ID", "Title", "Author", "Quantity","Available");
    printf("------------------------------------------------------------------------------------\n");
    for (int i = 0; i < num_books; ++i) {
            printf("%-10d %-30s %-20s %-15d %-10s\n", 
            library[i].book_id, 
            library[i].title, 
            library[i].author, 
            library[i].quantity,
            library[i].is_available? "Yes" : "No");
        }
}


void saveLibrary() {
    FILE *file = fopen("library_data.txt", "w");
    if (file == NULL) {
        return;
    }

    for (int i = 0; i < num_books; ++i) {
        fprintf(file, "%d\n%s\n%s\n%d\n%d\n", library[i].book_id, library[i].title, library[i].author, library[i].is_available, library[i].quantity);
    }

    fclose(file);
}


void loadLibrary() {
    FILE *file = fopen("library_data.txt", "r");
    if (file == NULL) {
        return;
    }

    num_books = 0;
    while (fscanf(file, "%d\n", &library[num_books].book_id) != EOF) {
        fgets(library[num_books].title, MAX_TITLE_LENGTH, file);
        library[num_books].title[strlen(library[num_books].title) - 1] = '\0'; 

        fgets(library[num_books].author, MAX_AUTHOR_LENGTH, file);
        library[num_books].author[strlen(library[num_books].author) - 1] = '\0'; 

        fscanf(file, "%d\n%d\n", &library[num_books].is_available, &library[num_books].quantity);
        num_books++;
    }

    fclose(file);
}


void delay(int number_of_seconds)
{
    int milli_seconds = 1000 * number_of_seconds;
    clock_t start_time = clock();
    while (clock() < start_time + milli_seconds)
        ;
}


void inputPassword(char password[]) {
    char ch;
    int i = 0;
    while (1) {
        ch = getch(); // Get each character without echoing it
        if (ch == '\r') { // Enter key pressed
            password[i] = '\0';
            printf("\n"); // Move to the next line
            break;
        } else if (ch == '\b') { // Backspace handling
            if (i > 0) {
                i--;
                printf("\b \b"); // Erase the asterisk
            }
        } else if (i < MAX_PASSWORD_LENGTH - 1) {
            password[i] = ch;
            i++;
            printf("*"); // Print asterisk
        }
    }
}

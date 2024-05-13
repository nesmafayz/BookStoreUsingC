#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#define librarySize 100

int booksIDs[librarySize] = {0};
char titles[librarySize][50] = {"Harry Potter", "Oliver Twist", "Invisible man", "Moby Dick", " War and Peace"};
char authors[librarySize][50] = {"J.K.Rolling", "Charles Dicknes", "Ralph Ellison", "Herman Melville", "Leo Tolstoy"};
char category[librarySize][50] = {"Adventure","Drama", "Horror", "Fiction", "Poet"};
int quantity[librarySize] = {5,10,15,20,25};
int price[librarySize] = {10,20,30,40,50};
bool status[librarySize] = {true, false, true, false, true};
int id, choice, numOfBooks = 5,numOfCategory = 5;



void mainMenu()
{
    printf("\t\t\t\t\tWelcome To Our Store:\n");
    printf("\t\t\t\t==================================\n\n\n");
    printf("choose an option:\n");
    printf("=================\n\n");
    printf("1- Add new book\n");
    printf("2- Add new category\n");
    printf("3- Move a book\n");
    printf("4- sell a book\n");
    printf("5- Display all books\n");
    printf("6- Exit\n\n");
    printf("Your Choice: ");

}

void viewBookDetails(int *id, char *title, char *author,char *category, bool status, int *quantity, int *price)
{
    const char *bookStatus = (status == true) ? "Available" : "Not available";
    printf("\nBOOK DETAILS:\n");
    printf("=============\n");
    printf("ID    : %d\n", id);
    printf("Title : %s\n", title);
    printf("Author: %s\n", author);
    printf("Category: %s\n", category);
    printf("Status: %s\n", bookStatus);
    printf("Quantity: %d\n", quantity);
    printf("Price: %d\n", price);
    printf("==========================\n\n");
}


void displayAllBooks()
{
    for (int i = 0; i < numOfBooks; i++)
    {
        viewBookDetails(booksIDs[i], titles[i], authors[i],category[i], status[i], quantity[i], price[i]);
    }
}




void addNewBook()
{
    if (numOfBooks == librarySize)
    {
        printf("\n\nThere is no free space!\n\n");
        return;
    }
    else
    {
        char newTitle[50], newAuthor[50];
        printf("Enter new book title: ");
        scanf("%s", newTitle);
        printf("Enter new book author name: ");
        scanf("%s", newAuthor);

        int validTitle = 1, validAuthor = 1;

        for (int i = 0; newTitle[i] != '\0'; i++)
        {
            if (!isalpha(newTitle[i]))
            {
                validTitle = 0;
                break;
            }
        }

        for (int i = 0; newAuthor[i] != '\0'; i++)
        {
            if (!isalpha(newAuthor[i]))
            {
                validAuthor = 0;
                break;
            }
        }

        if (validTitle && validAuthor)
        {
            strcpy(titles[numOfBooks], newTitle);
            strcpy(authors[numOfBooks], newAuthor);
            status[numOfBooks] = true;
            booksIDs[numOfBooks] = numOfBooks + 1;
            numOfBooks++;
            printf("\n\nBook is added successfully!\n\n");
        }
        else
        {
            printf("Please enter only alphabetic characters for the title and author name.\n");
        }
    }
}

void addNewCategory()
{


    char newCategory[50];

    if (numOfCategory == librarySize)
    {
        printf("\n\nThere is no space for a new Category!\n\n");
        return;
    }

    printf("Enter new category: ");
    scanf("%s", newCategory);

    int validCategory = 1;
    for (int i = 0; newCategory[i] != '\0'; i++)
    {
        if (!isalpha(newCategory[i]))
        {
            validCategory = 0;
            break;
        }
    }

    if (validCategory)
    {
        strcpy(category[numOfCategory], newCategory);
        numOfCategory++;
        printf("\nCategory IS ADDED SUCCESSFULLY!\n\n");
    }
    else
    {
        printf("Please enter only alphabetic characters.\n");
    }
}

int search(int id)
{
    for (int i = 0; i < numOfBooks; i++)
    {
        if (booksIDs[i] == id)
        {
            viewBookDetails(booksIDs[i], titles[i], authors[i],category[i], status[i], quantity[i],price);
            return i;
        }
    }
    return -1;
}


void moveBook()
{
    int id, targetCategoryId;
    printf("Enter the ID of the book you want to move: ");
    scanf("%d", &id);

    if (id >= 0 && id < numOfBooks) {
        int bookIndex = search(id);
        if (bookIndex != -1)
        {
            printf("Enter the ID of the target category: ");
            scanf("%d", &targetCategoryId);

            if (targetCategoryId < 0 || targetCategoryId >= numOfCategory)
            {
                printf("Invalid category ID!\n");
            }
            else
            {
                printf("Moving book '%s' to category '%s'\n", titles[bookIndex], category[targetCategoryId]);
                strcpy(category[bookIndex], category[targetCategoryId]);
                printf("Book has been moved successfully!\n");
            }
        } else {
            printf("Book not found!\n");
        }
    } else {
        printf("Invalid book ID!\n");
    }
}


void sellBook()
{
    int id, choice, quantityToSell;
    bool flag = true;
    printf("Enter the id of the book you want to sell: ");
    if (id >= 0 && id < numOfBooks) {
    scanf("%d", &id);

    int searchResult = search(id);

    if (searchResult != -1)
    {
        printf("Enter the quantity you want to sell: ");

        scanf("%d", &quantityToSell);


        if (quantityToSell > 0 && quantityToSell <= quantity[searchResult])
        {
            printf("Are you sure you want to sell %d copies of book '%s'?\n", quantityToSell, titles[searchResult]);
            printf("Enter 1 to continue, 0 to stop: ");
            scanf("%d", &choice);

            if (choice == 1)
            {
                quantity[searchResult] -= quantityToSell;
                printf("\n%d copies of book '%s' sold successfully!\n", quantityToSell, titles[searchResult]);
                printf("Remaining quantity: %d\n\n", quantity[searchResult]);
            }
        }
        else {
            printf("\nSorry! Out Of Stock\n\n");
        }
        }else
        {
            printf("Invalid ID!\n");
        }
    }

}




void Exit()
{

    printf("\n\nBye Bye!\n");
    exit(0);
}

int main()
{
    while(1)
    {
        for (int i = 0; i < numOfBooks; i++)
        {
            booksIDs[i] = i + 1;
        }
        bool flag = true;
        while (flag)
        {
            mainMenu();
            scanf("%d", &choice);
            switch (choice)
            {
            case 1:
                system("cls");
                printf(" \t\t\t your choose to add a new book \n");
                printf("\t\t==========================================\n");
                addNewBook();
                printf("press any button to back to the  Menu...");
                getch();
                system("cls");
                break;

            case 2:
                system("cls");
                printf(" \t\t\t your choose to add a new category \n");
                printf("\t\t=============================================\n");
                addNewCategory();
                printf("press any button to back to the  Menu...");
                getch();
                system("cls");
                break;

            case 3:
                system("cls");
                printf(" \t\t\t your choose to move a book from category to another\n");
                printf("\t\t===============================================================\n");
                moveBook();
                printf("press any button to back to the Menu...");
                getch();
                system("cls");
                break;

            case 4:
                system("cls");
                printf(" \t\t\t your choose to sell a book \n");
                printf("\t\t========================================\n");
                sellBook();
                printf("press any button to back to the Menu...");
                getch();
                system("cls");
                break;

            case 5:
                system("cls");
                printf(" \t\t\t your choose to Display All your book details \n");
                printf("\t\t=========================================================\n");
                displayAllBooks();
                printf("press any button to back to the Menu...");
                getch();
                system("cls");
                break;

            case 6:
                Exit();
                break;

            }
        }
    }

    return 0;
}


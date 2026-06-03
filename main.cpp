#include <iostream>
#include <limits>
#include "src/adapters/InMemoryLibraryRepository.cpp"
#include "src/application/BorrowBookService.cpp"
#include "src/infrastructure/ConsoleUi.cpp"

int main() {
    Library library;
    InMemoryLibraryRepository inMemoryLibraryRepository(library);
    BorrowBookService borrowBookService(library, inMemoryLibraryRepository);
    ConsoleUI consoleUI(library, inMemoryLibraryRepository);


    //    Example Book

    Book book1;
    book1.bookID = 1;
    book1.bookName = "The Old Man and the Sea";
    book1.bookAuthor = "Ernest Hemingway";
    inMemoryLibraryRepository.newBook(book1);

    Book book2;
    book2.bookID = 2;
    book2.bookName = "Antifragile";
    book2.bookAuthor = "Nassim Nicholas Taleb";
    inMemoryLibraryRepository.newBook(book2);


    Book book3;
    book3.bookID = 3;
    book3.bookName = "The Art of War";
    book3.bookAuthor = "Sun Tzu";
    inMemoryLibraryRepository.newBook(book3);


    //    Example User

    Patron p1;
    p1.patronName = "Ali";
    p1.patronId = 1;

    Patron p2;
    p2.patronName = "Sara";
    p2.patronId = 2;

    Patron p3;
    p3.patronName = "Mina";
    p3.patronId = 3;


    while (true) {
        std::cout << "________________________" << std::endl;
        std::cout << "1.Add book to library" << std::endl;
        std::cout << "2.Add patron" << std::endl;
        std::cout << "3.Show All Book" << std::endl;
        std::cout << "4.Show All Patron" << std::endl;
        std::cout << "5.Borrow book" << std::endl;
        std::cout << "6.Show all borrowed books" << std::endl;
        std::cout << "7.Exit" << std::endl;

        short choice;
        std::cout << "choice:";
        std::cin >> choice;

        try {
            switch (choice) {

                case 1: {
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    Book newBook;
                    std::string bookIdStr;

                    std::cout << "enter book name:";
                    std::getline(std::cin, newBook.bookName);

                    std::cout << "enter book author:";
                    std::getline(std::cin, newBook.bookAuthor);

                    std::cout << "enter book code[generate=g]:";
                    std::cin >> bookIdStr;

                    if (bookIdStr == "g") {
                        newBook.bookID = consoleUI.generateBookId();
                    } else {
                        try {
                            newBook.bookID = std::stoi(bookIdStr);


                        } catch (std::exception &exception) {
                            std::cerr << exception.what() << "\n";
                            break;
                        }
                    }


                    inMemoryLibraryRepository.newBook(newBook);

                    std::cout << "##### successfully #####";
                    std::cout << std::endl;
                    std::cout << std::endl;


                    break;
                }

                case 2: {
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::string patronIdStr;


                    Patron newPatron;

                    std::cout << "enter patron name:";
                    std::cin >> newPatron.patronName;

                    std::cout << "enter patron id[generate:g]:";
                    std::cin >> patronIdStr;

                    if (patronIdStr == "g") {
                        newPatron.patronId = consoleUI.generatePatronId();
                    } else {
                        try {
                            newPatron.patronId = std::stoi(patronIdStr);


                        } catch (std::exception &exception) {
                            std::cerr << exception.what() << "\n";
                            break;
                        }
                    }


                    inMemoryLibraryRepository.newPatron(newPatron);
                    break;
                }

                case 3:
                    consoleUI.printAllBook();
                    break;

                case 4:
                    consoleUI.printAllPatron();
                    break;
                case 5: {
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    int patronId, bookId;

                    std::cout << "enter patron id:";
                    std::cin >> patronId;

                    std::cout << "enter book id:";
                    std::cin >> bookId;

                    std::cout << std::endl;

                    try {
                        borrowBookService.borrowBook(patronId, bookId);

                    } catch (std::exception &exception) {
                        std::cerr << exception.what() << std::endl;
                    }
                    break;
                }

                case 6:

                    try {
                        consoleUI.printAllBorrowed();

                    } catch (std::exception &exception) {
                        std::cerr << exception.what() << std::endl;
                    }

                    break;

                case 7:
                    return 0;

                default:
                    throw std::runtime_error("number not range");
            }

        } catch (std::string &errorText) {
            std::cout << errorText << std::endl;
        } catch (std::exception &exception) {
            std::cerr << exception.what() << std::endl;
        } catch (...) {
            std::cerr << "other error" << std::endl;
        }


    }

}
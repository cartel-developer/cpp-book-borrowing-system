#include <string>
#include <algorithm>
#include <iostream>
#include <vector>
#include <limits>


// Entities

struct Book {
    int bookID{-1};
    std::string bookName;
    std::string bookAuthor;
};

struct Patron {
    int patronId{-1};
    std::string patronName;

};

struct BookPatronItem {
    int patronId{-1};
    int bookId{-1};
};

struct Library {

    std::vector<Book> allBooks;
    std::vector<Patron> allPatrons;
    std::vector<BookPatronItem> patronBorrowedBooks;

};

// UseCase

class LibraryRepository {

public:

    virtual void newBook(Book newBook) = 0;

    virtual void newPatron(Patron patron) = 0;

    virtual Patron getPatron(int patronId) const = 0;

    virtual Book getBook(int bookId) const = 0;

    virtual bool isPatronExist(int patronId) const = 0;

    virtual bool isBookExist(int bookId) const = 0;

    virtual ~LibraryRepository() = default;


};

//Adapters

class InMemoryLibraryRepository : public LibraryRepository {

    Library &library;

public:

    InMemoryLibraryRepository(Library &lib) : library(lib) {}


    void newBook(Book newBook) override {
        bool repeatBookId = std::any_of(library.allBooks.begin(), library.allBooks.end(), [&](const Book &book) {
            return book.bookID == newBook.bookID;
        });

        if (repeatBookId) {
            throw std::runtime_error("error:declared book id");
        } else {
            library.allBooks.push_back(newBook);
        }

    }

    void newPatron(Patron newPatron) override {

        bool repeatPatronId = std::any_of(library.allPatrons.begin(), library.allPatrons.end(),
                                          [&](const Patron &patron) {
                                              return patron.patronId == newPatron.patronId;
                                          });

        if (repeatPatronId) {
            throw std::runtime_error("error:declared patron id");
        } else {
            library.allPatrons.emplace_back(newPatron);
        }

    }


    Patron getPatron(int patronId) const override {
        auto patron = std::find_if(library.allPatrons.begin(), library.allPatrons.end(), [&](const Patron &patron) {
            return patron.patronId == patronId;
        });
        if (patron == library.allPatrons.end()) {
            throw std::runtime_error("patron not found");
        }
        return *patron;
    }


    Book getBook(int bookId) const override {
        auto book = std::find_if(library.allBooks.begin(), library.allBooks.end(), [&](const Book &book) {
            return book.bookID == bookId;
        });

        if (book == library.allBooks.end())
            throw std::runtime_error("book not found");

        return *book;
    }

    bool isPatronExist(int patronId) const override {
        return std::any_of(library.allPatrons.begin(), library.allPatrons.end(), [&](const Patron &patron) {
            return patron.patronId == patronId;
        });
    }

    bool isBookExist(int bookID) const override {
        return std::any_of(library.allBooks.begin(), library.allBooks.end(), [&](const Book &book) {
            return book.bookID == bookID;
        });
    }


};

class BorrowBookService {


private:
    Library &library;
    LibraryRepository &libraryRepository;

public:

    BorrowBookService(Library &library, LibraryRepository &libRepository) : library(library),
                                                                            libraryRepository(libRepository) {}

    void borrowBook(int patronId, int bookId) {
        BookPatronItem connect;
        connect.bookId = bookId;
        connect.patronId = patronId;

        if (isBorrowedBook(bookId)) {
            std::cerr << "book borrowed!" << std::endl;
            return;
        } else if (!libraryRepository.isPatronExist(patronId)) {
            std::cerr << "patron not found!" << std::endl;
            return;
        } else if (!libraryRepository.isBookExist(bookId)) {
            std::cerr << "book not found!" << std::endl;
            return;
        }

        library.patronBorrowedBooks.emplace_back(connect);
        std::cout << "##### Successfully #####" << std::endl;

    }

    bool isBorrowedBook(int bookId) {
        auto begin = library.patronBorrowedBooks.begin();
        auto end = library.patronBorrowedBooks.end();

        return std::any_of(begin, end, [&](const BookPatronItem &bookPatronItem) {
            return bookPatronItem.bookId == bookId;
        });
    }
};

// FrameWork

class ConsoleUI {
private:
    Library &library;
    LibraryRepository &libraryRepository;

public:
    ConsoleUI(Library &lib, LibraryRepository &libraryRepository) : library(lib),
                                                                    libraryRepository(libraryRepository) {}

    void printAllBook() {

        std::cout << "Book List:";

        if (library.allBooks.empty()) {
            std::cout << "empty!" << std::endl;
            return;
        }

        for (const Book &book:library.allBooks) {
            std::cout << std::endl << "[" << book.bookID << "] " << book.bookName << "-" << book.bookAuthor;
        }
        std::cout << std::endl;
    }

    void printAllBorrowed() {


        std::cout << "Borrow List:";

        bool error = false;


        if (library.patronBorrowedBooks.empty()) {
            std::cerr << "Borrowed empty!" << std::endl;
            error = true;
        } else if (library.allBooks.empty()) {
            std::cerr << "book empty!" << std::endl;
            error = true;
        } else if (library.allPatrons.empty()) {
            std::cerr << "patron empty!" << std::endl;
            error = true;
        }

        if (error)
            return;

        for (const BookPatronItem &bookPatronItem:library.patronBorrowedBooks) {
            auto patron = libraryRepository.getPatron(bookPatronItem.patronId);
            auto book = libraryRepository.getBook(bookPatronItem.bookId);
            std::cout << "[" << patron.patronId << "]" << patron.patronName << " -> " << "[" << book.bookID << "]"
                      << book.bookName << "-" << book.bookAuthor << std::endl;
        }

        std::cout << std::endl;
    }


    void printAllPatron() {
        std::cout << "Patron List:";

        if (library.allPatrons.empty()) {
            std::cout << "empty!" << std::endl;
            return;
        }
        std::cout << std::endl;

        for (const Patron &patron:library.allPatrons) {
            std::cout << std::endl << "[" << patron.patronId << "] " << patron.patronName;
        }
        std::cout << std::endl;
    }

    int generateBookId() const {
        int maxId = 0;
        for (const Book &book:library.allBooks) {
            if (book.bookID > maxId)
                maxId = book.bookID;

        }
        return maxId + 1;
    };

    int generatePatronId() const {
        int maxId = 0;
        for (const Patron &patron:library.allPatrons) {
            if (patron.patronId > maxId)
                maxId = patron.patronId;

        }
        return maxId + 1;
    };
};


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

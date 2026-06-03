#pragma once
#include <iostream>
#include "entities/Library.hpp"
#include "entities/LibraryRepository.hpp"


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

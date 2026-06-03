#include <iostream>
#include <algorithm>
#include "entities/Library.hpp"
#include "entities/LibraryRepository.hpp"

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

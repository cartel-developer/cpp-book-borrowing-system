
#include "entities/LibraryRepository.hpp"
#include "entities/Library.hpp"
#include <algorithm>

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

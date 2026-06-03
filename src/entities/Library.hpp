#pragma once
#include <vector>
#include "Book.hpp"
#include "Patron.hpp"
#include "BookPatronItem.hpp"

struct Library {
    std::vector<Book> allBooks;
    std::vector<Patron> allPatrons;
    std::vector<BookPatronItem> patronBorrowedBooks;
};
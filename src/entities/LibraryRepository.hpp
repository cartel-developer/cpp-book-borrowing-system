#pragma once

#include "entities/Book.hpp"
#include "entities/Patron.hpp"

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
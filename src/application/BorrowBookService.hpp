#pragma once

#include <iostream>
#include <algorithm>
#include "entities/Library.hpp"
#include "entities/LibraryRepository.hpp"

class BorrowBookService {

private:
    Library &library;
    LibraryRepository &libraryRepository;

public:
    BorrowBookService(Library &library, LibraryRepository &libRepository);
    void borrowBook(int patronId, int bookId);
    bool isBorrowedBook(int bookId);
};
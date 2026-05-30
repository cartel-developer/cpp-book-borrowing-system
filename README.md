# Library Management System

A simple console-based library management system written in C++.

This project manages:
- books
- patrons
- borrowing records

It is designed with a cleaner structure by separating:
- entities
- repository layer
- service layer
- console UI

---

## Features

- Add a new book
- Add a new patron
- Show all books
- Show all patrons
- Borrow a book
- Show all borrowed books
- Auto-generate IDs for books and patrons
- Prevent duplicate IDs
- Validate missing books or patrons before borrowing

---

## Project Structure

The code is organized into several logical parts:

### Entities
Basic data models:
- `Book`
- `Patron`
- `BookPatronItem`
- `Library`

### Repository
Abstract data-access layer:
- `LibraryRepository`

Concrete implementation:
- `InMemoryLibraryRepository`

### Service
Application logic:
- `BorrowBookService`

### UI
Console interaction and display:
- `ConsoleUI`

---

## Technologies Used

- C++
- STL (`vector`, `algorithm`, `string`, `iostream`, `limits`)

---

## How to Build

Compile using `g++`:
```bash
g++ -std=c++17 library.cpp -o library_app

# Library Management System (C++)

A simple **Library Management System** written in **C++**, designed to manage books and patrons in a small library.  
The project is structured using **Clean Architecture principles** to keep the code modular, maintainable, and easy to extend.

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

## Architecture

This project follows a simplified **Clean Architecture** structure.  
The goal is to separate business logic from frameworks, UI, and infrastructure.

Main layers:

- **Entities**  
  Core domain objects such as books and patrons.

- **Use Cases / Application Logic**  
  Handles operations like borrowing books and managing records.

- **Adapters**  
  Connects the application logic with external layers (CLI, controllers, etc.).

- **Infrastructure**  
  Handles persistence and implementation details such as data storage.

Example structure:
src
├── adapters
├── application
├── entities
└── infrastructure


## Requirements

- C++17 or newer
- CMake (version 3.17 or newer)
- A C++ compiler (GCC, Clang, or MSVC)

## Build and Run

### 1. Clone the repository
```bash
git clone https://github.com/cartel-developer/cpp-book-borrowing-system.git
cd library-management-system
```

### 2.Create a build directory
```bash
mkdir build
cd build
```

### 3. Generate build files with CMake
```bash
cmake ..
```

### 4.Build the project
```bash
cmake --build .
```

### 5. Run the program
After building, run the generated executable:
```bash
./Library
```

## Purpose of the Project

This project was created as a **practice implementation of Clean Architecture in C++**, demonstrating how to organize a software project while keeping domain logic independent from infrastructure and external frameworks.

## Possible Future Improvements

* **Persistent Storage:** Implement file-based or database storage (e.g., SQLite) to save data between sessions.
* **Return Functionality:** Add the ability for patrons to return borrowed books.
* **Search Engine:** Add search functionality to find books by title/author or patrons by name/ID.
* **Unit Testing:** Implement a testing suite (using GTest or Catch2) to ensure the stability of the core business logic.
* **API Interface:** Expose the library services through a REST API to allow for web or mobile frontend integration.



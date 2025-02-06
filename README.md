# Library Management System

## Overview
This project is a **Library Management System** written in C and a completely console based project, designed for managing books, users, and borrowing operations in a library. It includes functionality for both **admin users** and **regular users** to perform various operations efficiently.

## Features
### Admin Features
- Add new books to the library.
- Delete books from the library.
- Update book information (title, author, quantity).
- View the list of all books.
- Sort books by specific criteria.
- Search for books by title.
- Remove users from the system.

### User Features
- Register as a new user.
- Login with credentials.
- Search for books by title.
- View all available books.
- Borrow books from the library.
- Return borrowed books.

### Common Features
- Persistent storage of user and book data using file handling.
- Role-based access control for admins and users.

## File Structure
- `user_data.txt`: Stores registered users' data.
- `library_data.txt`: Stores library books' data.

## Requirements
- GCC Compiler
- Basic knowledge of C
- Operating system that supports `conio.h` (e.g., Windows)

## How to Run
1. Clone or download the project files.
2. Compile the source code using a GCC compiler:
   ```bash
   gcc library_management_system.c -o library_management_system
## Code Highlights

### Data Structures
- **User**: Stores user details (username, password, role).
- **Book**: Stores book details (ID, title, author, quantity, availability).
- **BorrowedBook**: Tracks books borrowed by users.

### File Handling
- All user and library data are saved in files for persistence.

### Error Handling
- Validates user input.
- Ensures unique usernames and book IDs.

## Future Improvements
- Implement fine calculations for late book returns.
- Add functionality to track borrow history.
- Improve the user interface for better usability.
- Support multi-threading for better performance.

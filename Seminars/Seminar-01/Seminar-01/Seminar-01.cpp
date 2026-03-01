#include <iostream>
#pragma warning(disable:4996)

namespace Constants {
	const int MAX_TITLE_LENGTH = 64;
	const int MAX_NAME_LENGTH = 32;
	const size_t MAX_BOOK_COUNT = 10;
}

enum class Status {
	Available,
	Borrowed,
	Reserved
};

struct Book {
	char title[Constants::MAX_TITLE_LENGTH + 1];
	char author[Constants::MAX_NAME_LENGTH + 1];
	int publicationYear;
	Status status;
};

struct Library {
	char name[Constants::MAX_NAME_LENGTH + 1];
	Book books[Constants::MAX_BOOK_COUNT];
	size_t bookCount;
};

void addBook(Library& library, const char* title, const char* author, int publicationYear) {
	if (!title || !author) {
		std::cout << "Invalid title or author!";
		return;
	}

	if (library.bookCount < Constants::MAX_BOOK_COUNT) {
		Book book{};

		strncpy(book.title, title, Constants::MAX_TITLE_LENGTH);
		book.title[Constants::MAX_TITLE_LENGTH] = '\0';
		strncpy(book.author, author, Constants::MAX_NAME_LENGTH);
		book.author[Constants::MAX_NAME_LENGTH] = '\0';

		book.publicationYear = publicationYear;
		book.status = Status::Available;

		library.books[library.bookCount] = book;
		library.bookCount++;

		std::cout << "Successfully added a book to the library." << std::endl;
	}
	else {
		std::cout << "Library is full. Cannot add any more books." << std::endl;
	}
}

void borrowBook(Book& book) {
	if (book.status == Status::Available) {
		book.status = Status::Borrowed;
	}
	else {
		std::cout << "The book is not available." << std::endl;
	}
}

void reserveBook(Book& book) {
	if (book.status == Status::Available) {
		book.status = Status::Reserved;
	}
	else {
		std::cout << "The book is not available." << std::endl;
	}
}

const char* getStatus(const Book& book) {
	switch (book.status) {
	case Status::Borrowed: return "borrowed";
	case Status::Reserved: return "reserved";
	default: return "available";
	}
}

void printLibrary(const Library& library) {
	for (size_t i = 0; i < library.bookCount; i++) {
		std::cout << "Book \"" << library.books[i].title << "\" by " << library.books[i].author << " is " << getStatus(library.books[i]) << "." << std::endl;
	}
}

void sortBooks(const Library& library, Book sorted[Constants::MAX_BOOK_COUNT])
{
	for (size_t i = 0; i < library.bookCount - 1; i++)
	{
		size_t minIndex = i;

		for (size_t j = i + 1; j < library.bookCount; j++)
		{
			if (strcmp(sorted[j].title, sorted[minIndex].title) < 0) {
				minIndex = j;
			}
		}

		if (minIndex != i) {
			Book temp = sorted[i];
			sorted[i] = sorted[minIndex];
			sorted[minIndex] = temp;
		}
	}
}

void printLibraryAlphabetically(const Library& library) {
	Book sorted[Constants::MAX_BOOK_COUNT];

	for (size_t i = 0; i < library.bookCount; i++) {
		sorted[i] = library.books[i];
	}

	sortBooks(library, sorted);

	for (size_t i = 0; i < library.bookCount; i++) {
		std::cout << "Book \"" << sorted[i].title << "\" by " << sorted[i].author << " is " << getStatus(sorted[i]) << "." << std::endl;
	}
}

int main()
{
	Library library{};
	strncpy(library.name, "Lib1", Constants::MAX_NAME_LENGTH);
	library.name[Constants::MAX_NAME_LENGTH] = '\0';
	library.bookCount = 0;

	addBook(library, "Book1", "Author1", 2020);
	addBook(library, "A", "Author1", 2020);
	printLibrary(library);
	printLibraryAlphabetically(library);
}
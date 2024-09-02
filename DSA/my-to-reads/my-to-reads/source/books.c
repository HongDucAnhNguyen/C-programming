#include "../headers/books.h"


void print_book_info(const Book* current_book) {
	// Define the width of the box
	const int width = 30;

	// Print the top border of the box
	printf("%.*s\n", width, "******************************");

	// Print each line with proper alignment
	printf("** %-27s **\n", "Title: ");
	printf("** %-27s **\n", current_book->title);
	printf("** %-27s **\n", "Pages: ");
	printf("** %-27d **\n", current_book->pages);
	printf("** %-27s **\n", "Progress: ");
	printf("** %-27s **\n", current_book->progress);

	// Print the bottom border of the box
	printf("%.*s\n", width, "******************************");
}

void add_book(const char* title, const char* progress, int pages, Book** first_book, int* collection_len) {
	// Allocate memory for the new book node
	Book* temp_ptr = (Book*)malloc(sizeof(Book));

	if (temp_ptr == NULL) {
		fprintf(stderr, "Memory allocation failed.\n");
		exit(EXIT_FAILURE);
	}




	//clear out mem buffer
	memset(temp_ptr, 0, sizeof(Book));


	// why this function? --> buffer overflow resistant
	strncpy_s(temp_ptr->title, sizeof(temp_ptr->title), title, BOOK_TITLE_MAX_CHAR_EXCLUDING_NULL_TERMINATOR);
	strncpy_s(temp_ptr->progress, sizeof(temp_ptr->progress), progress, BOOK_PROGRESS_MAX_CHAR_EXCLUDING_NULL_TERMINATOR);
	temp_ptr->pages = pages;
	temp_ptr->next = NULL;

	if (!*first_book) {




		*first_book = temp_ptr;
		printf("\nfirst book added!\n\n");



	}
	else {
		Book* current_book = *first_book;
		while (current_book->next != NULL) {
			current_book = current_book->next;
		}
		current_book->next = temp_ptr;
	}





	//add book to collection and update length
	*collection_len += 1;

}

void display_collection(Book* first_book) {

	Book* current_book = first_book;
	if (!first_book) {
		printf("collection is empty, add a book\n");
		return;
	}
	while (current_book != NULL) {
		print_book_info(current_book);
		current_book = current_book->next;
	}

}

void clean_up(Book* first_book) {

	Book* current = first_book;
	while (current != NULL) {
		Book* temp_ptr = current;
		current = current->next;

		free(temp_ptr);
	}


	printf("\nexitting application...successfully cleaned up resources\n");
}

void search_book(const char* search_keyword, Book* first_book)
{


	if (!search_keyword) {
		printf("please provide a valid search keyword\n");
		return;
	}


	Book* current_book = first_book;


	char pages_keyword_str[4];



	while (current_book != NULL) {
		// Convert the integer to a string
		snprintf(pages_keyword_str, sizeof(pages_keyword_str), "%d", current_book->pages);
		if (strcmp(search_keyword, current_book->title) == 0 || strcmp(search_keyword, pages_keyword_str) == 0) {
			printf("Search results:\n");
			print_book_info(current_book);
			return;
		}

		current_book = current_book->next;
	}

}

void remove_book(const char* remove_keyword, Book** first_book, int* collection_len)
{
	if (!remove_keyword) {
		printf("please provide a valid look up keyword to specify which book to remove\n");
		return;
	}

	Book* current_book = *first_book;
	Book* previous = NULL;


	char pages_keyword_str[4];



	while (current_book != NULL) {
		// Convert the integer to a string
		snprintf(pages_keyword_str, sizeof(pages_keyword_str), "%d", current_book->pages);
		if (strcmp(remove_keyword, current_book->title) == 0 || strcmp(remove_keyword, pages_keyword_str) == 0) {

			//if first book was targetted, this means previous should be null
			if (previous == NULL) {
				//reassign first book ptr
				*first_book = current_book->next;
			}

			else {
				previous->next = current_book->next;
			}




			printf("Book %s being removed, reallocating resources\n", current_book->title);
			free(current_book);
			printf("removed book successfully\n");
			*collection_len -= 1;
			return;
		}

		previous = current_book;
		current_book = current_book->next;
	}

	printf("No matching books found, no books removed\n");
}



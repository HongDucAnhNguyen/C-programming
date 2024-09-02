#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BOOK_PROGRESS_MAX_CHAR_INCLUDING_NULL_TERMINATOR 64
#define BOOK_PROGRESS_MAX_CHAR_INCLUDING_NULL_TERMINATOR 20

#define BOOK_TITLE_MAX_CHAR_EXCLUDING_NULL_TERMINATOR (BOOK_PROGRESS_MAX_CHAR_INCLUDING_NULL_TERMINATOR - 1)
#define BOOK_PROGRESS_MAX_CHAR_EXCLUDING_NULL_TERMINATOR (BOOK_PROGRESS_MAX_CHAR_INCLUDING_NULL_TERMINATOR - 1)

typedef struct book {
	char title[BOOK_PROGRESS_MAX_CHAR_INCLUDING_NULL_TERMINATOR];
	char progress[BOOK_PROGRESS_MAX_CHAR_INCLUDING_NULL_TERMINATOR];
	int pages;
	struct book* next;



}Book;

//appends a new book to the list
void add_book(const char* title, const char* progress, int pages, Book** first_book,
	int* collection_len);

void display_collection(Book* first_book);

void print_book_info(const Book* current_book);


void clean_up(Book* first_book);


void search_book(const char* search_keyword, Book* first_book);

void remove_book(const char* remove_keyword, Book** first_book, int* collection_len);

void sort_by_character(Book* first_book);
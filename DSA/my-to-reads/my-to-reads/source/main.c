#include "../headers/books.h"

void print_banner() {
	printf("  _______          _____                _ \n");
	printf(" |__   __|        |  __ \\              | |\n");
	printf("    | | ___ ______| |__) |___  __ _  __| |\n");
	printf("    | |/ _ \\______|  _  // _ \\/ _` |/ _` |\n");
	printf("    | | (_) |     | | \\ \\  __/ (_| | (_| |\n");
	printf("    |_|\\___/      |_|  \\_\\___|\\__,_|\\__,_|\n");
	printf("                                          \n");
	printf("                                          \n");
}

void print_welcome_message() {
	printf("****************************************\n");
	printf("*                                      *\n");
	printf("*         Welcome back!                *\n");
	printf("*         Your to-reads currently      *\n");
	printf("*                                      *\n");
	printf("****************************************\n");
}

int main() {
	Book* first_book = NULL;
	int collection_len = 0;
	//to keep track of the current number of books in collection
	print_banner();
	print_welcome_message();
	add_book("The Clear Quran", "not started", 416,
		(&first_book), &collection_len);
	add_book("Meditations", "not started", 523,
		&first_book, &collection_len);
	add_book("Mastery", "not started", 356,
		&first_book, &collection_len);

	display_collection(first_book);


	search_book("Mastery", first_book);
	remove_book("Mastery", &first_book, &collection_len);


	printf("you have: %d book(s)\n", collection_len);



	clean_up(first_book);
	return 0;
}
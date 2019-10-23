#ifndef ADMIN_H__
#define ADMIN_H__

typedef struct books{
	int bookNo;
	char bookName[40];
	char bookAut[40];
	int bookPrice;
	int leaNum;
}books;

int loadBook(const char *path);
int addBoToP(books s);
int saveBook(const char *path);
void addBook(books *pb);
int delBook(books *pb);
int findBookByNo();
int findBookByNa();
void finBookMenu();
void scanAdmin();
void showBook(books *pb);
void listBook();
int adminLog(int id,char *pcode);
void adminMenu();
void showAdminMenu(int adID);
void adminMenu();
void bookFunMenu();

typedef struct readers{
	int readerID;
	char readerCode[20];
	char readerName[40];
	int readerPhone;
	int readerMoney;
}readers;
void readFunMenu();
int loadReader(const char *path);
int saveReader(const char *path);
void showReader(readers *pr);
int findReaderByNa();
int findReaderById();
void modiReader();
void listReader();
#endif

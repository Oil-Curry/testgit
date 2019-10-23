#include<stdio.h>
#include<stdlib.h>
#include"sAdmin.h"
#include"admin.h"
#include"reader.h"


int adIndex=0;
int boIndex=0;
int reIndex=0;
extern admins *pAds;
extern books *pBos;
extern readers *pRes;

void choseLog(){
	int opt=0;
	printf("欢迎来到图书管理系统\n");
	printf("——————————————————————————————————\n");
	printf("请选择登陆方式\n");
	printf("[0]超级管理员\n");
	printf("[1]普通管理员\n");
	printf("[2]读者\n");
	printf("[3]退出程序\n");
	printf("——————————————————————————————————\n");

	scanf("%d",&opt);

	switch(opt){
		case 0:
		supScan();
		break;
		case 1:
		scanAdmin();
		break;
		case 2:
		readerLog();
		break;
		case 3:
		free(pAds);
		free(pBos);
		free(pRes);
		exit(0);

		default:
		printf("无此选项\n");
		return;
	}
}


int main(){
	loadAdmin("admin.txt");
	loadBook("book.txt");
	loadReader("reader.txt");
	while(1){
    	choseLog();
	}


	return 0;
}

#include"admin.h"
#include"sAdmin.h"
#include"reader.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

extern int reIndex;
extern int boIndex;
extern readers reader;
extern readers *pRes;
extern books *pBos;
int idInLog=-1;//登陆用户的位置

int readerLog(){
	printf("请输入用户名\n");
	int id=0;
	scanf("%d",&id);
	printf("请输入密码\n");
	char code[]={};
	scanf("%s",code);
	for(int i=0;i<reIndex;i++){
		if(pRes[i].readerID==id){
			if(strcmp(pRes[i].readerCode,code)==0){
				idInLog=i;
				readerMenu(i);
				return 0;
			}else{
				printf("登陆失败\n");
			    break;
			}
		}
	}
	printf("无此用户\n");
	return -1;
}


void changeIm(){
	if(idInLog==-1){
		printf("请正常登陆\n");
		return;
	}
	int opt=0;
	while(1){
	printf("您的个人信息是：\n");
	showReader(pRes+idInLog);
	printf("——————————————————————————————————\n");
	printf("请选择要修改的内容\n");
	printf("[1]密码\n");
	printf("[2]姓名\n");
	printf("[3]联系方式\n");
	printf("[4]返回\n");
	printf("——————————————————————————————————\n");
	scanf("%d",&opt);
		switch(opt){
			case 1:
			printf("请输入新的密码\n");
			char code[20]={};
			scanf("%s",code);
			strcpy(pRes[idInLog].readerCode,code);
			break;
			case 2:
			printf("请输入新的姓名\n");
			char name[40]={};
			scanf("%s",name);
			strcpy(pRes[idInLog].readerName,name);	
			break;
			case 3:
			printf("请输入新的联系方式\n");
			int phone=0;
			scanf("%d",&phone);
			pRes[idInLog].readerPhone=phone;
			case 4:
			saveReader("reader.txt");
			printf("已保存\n");
			return;
			default:
			printf("无效操作\n");
			break;
		}
	}
}

void findBookByM(){
	printf("请输入要查找图书的部分书名\n");
	char name[40]={};
	scanf("%s",name);
	int len=strlen(name);
	if(boIndex==0){
		printf("暂无图书\n");
		return;
	}
	for(int i=0;i<boIndex;i++){
		if(strncmp(pBos[i].bookName,name,len)==0){
			showBook(pBos+i);
			return;
		}
	}
	printf("没有找到\n");
}

void readerFindBook(){
	printf("——————————————————————————————————\n");
	printf("请选择查找方式\n");
	printf("[1]精确查找\n");
	printf("[2]模糊查找\n");
	printf("——————————————————————————————————\n");
	int opt=0;
	scanf("%d",&opt);
	switch(opt){
		case 1:
		findBookByNa();
		break;
		case 2:
		findBookByM();
		break;
		default:
		printf("无此操作\n");
		break;
	}
}

int findBookT(int id){
	for(int i=0;i<boIndex;i++){
		if(pBos[i].bookNo==id){
			return i;
		}
	}
	return -1;
}
void borrowBook(){
	printf("请注意，借书需要2元\n");
	printf("请选择要借的图书编号\n");
	int id=0;
	scanf("%d",&id);
	int boId=findBookT(id);
	if(boId==-1){
		printf("无此书\n");
		return;
	}
	showBook(pBos+boId);
	if(pRes[idInLog].readerMoney>=2){
	    pRes[idInLog].readerMoney-=2;
	}else{
		printf("余额不足\n");
		return;
	}
	pBos[boId].leaNum++;
}

void showReaderMenu(int id){
	printf("——————————————————————————————————\n");
	printf("欢迎光临，%s\n",pRes[id].readerName);
	printf("——————————————————————————————————\n");
	printf("请选择服务\n");
	printf("[1]修改个人信息\n");
	printf("[2]察看全部图书\n");
	printf("[3]查找图书\n");
	printf("[4]借阅图书\n");
	printf("[5]退出\n");
	printf("——————————————————————————————————\n");
}

void readerMenu(int id){
	int opt=0;
	while(1){
		showReaderMenu(id);
    	scanf("%d",&opt);
		switch(opt){
			case 1:
			changeIm();
			break;
			case 2:
			listBook();
			break;
			case 3:
			readerFindBook();
			break;
			case 4:
			borrowBook();
			break;
			case 5:
			saveBook("book.txt");
			printf("已保存\n");
			return;
			default:
			printf("无效操作\n");
			break;
		}
	}
}

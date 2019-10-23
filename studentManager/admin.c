#include"sAdmin.h"
#include"admin.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

extern int adIndex;//管理员的总量
extern admins *pt;//储存管理员的动态内存
books book={};
books *pBos=NULL;    

int loadBook(const char *path){        //读取文件到book，再添加到动态内存
    FILE *fp=fopen(path,"r");
	if(fp==NULL){
		return -1;
	}
	while(fread(&book,sizeof(books),1,fp)>0){
		addBoToP(book);
	}
	fclose(fp);
	return 0;
}

int boCnt=50;       //图书总数
extern int boIndex;  //有多少本书
int addBoToP(books s){
	if(pBos==NULL){
		pBos=calloc(boCnt,sizeof(books));   //申请动态内存
		if(pBos==NULL){
			return -1;
		}
	}
    if(boIndex >= boCnt){
		pBos=realloc(pBos,2*boCnt*sizeof(books));  //扩容图书列表
		boCnt=2*boCnt;
		if(pBos==NULL){
		}
	}
	pBos[boIndex]=s;       //将图书信息添加至动态内存
    boIndex++;
}

int saveBook(const char *path){                     //把动态内存中的内容写到文件中
	FILE *fp=fopen(path,"w");
	if(fp==NULL){
		return -1;
	}
	fwrite(pBos,sizeof(books),boIndex,fp);
	fclose(fp);
	return 0;
}

void addBook(books *pb){
	int bookNoUp=1;
	if(boIndex==0){
		book.bookNo=bookNoUp;
	}else{
		for(int j=0;j<boIndex;j++){
		    for(int i=0;i<=boIndex;i++){
				if(pBos[i].bookNo==bookNoUp){
			        bookNoUp+=1;
					continue;
				}
				book.bookNo=bookNoUp;//生成图书编号
		    }
		}
	}
	printf("请输入图书名字\n");
	scanf("%s",pb->bookName);
	printf("请输入图书作者\n");
	scanf("%s",pb->bookAut);
	printf("请输入图书价格\n");
	scanf("%d",&pb->bookPrice);
	book.leaNum=0;
}

int delBook(books *pb){
	printf("请输入要删除的图书编号\n");
	int no=0;
	scanf("%d",&no);
	for(int i=0;i<boIndex;i++){
		if(pBos[i].bookNo==no){
			pBos[i]=pBos[boIndex-1];
		}
	}
	--boIndex;
}

void modiBook(){                 //修改管理员信息
	printf("请输入要修改的图书编号\n");
	int id=0;
	scanf("%d",&id);
	int BoNo=0;
	for(int i=0;i<boIndex;i++){
		if(pBos[i].bookNo==id){
			BoNo=i;
		}
		if(i==boIndex){
			BoNo=-1;
		}
	}
	if(BoNo==-1){
		printf("查无此书\n");
	}
	showBook(pBos+BoNo);
	printf("——————————————————————————————————\n");
	printf("请选择要修改的信息\n");
	printf("[1]书名\n");
	printf("[2]作者\n");
	printf("[3]价格\n");
	printf("——————————————————————————————————\n");
	int opt=0;
	scanf("%d",&opt);
	switch(opt){
		case 1:
		printf("请输入新的书名\n");
		char name[40]={};
		scanf("%s",name);
		strcpy(pBos[BoNo].bookName,name);
		break;
		case 2:
		printf("请输入新的作者\n");
		char aut[40]={};
		scanf("%s",aut);
		strcpy(pBos[BoNo].bookAut,aut);
		break;
        case 3:
		printf("请输入新的价格\n");
		int price=0;
		scanf("%d",&price);
		pBos[BoNo].bookPrice=price;
		break;
        default:
		printf("无效操作\n");
		break;
	}
	
}

void findBookMenu(){
    printf("选择查找方式\n");
	printf("[1]按编号查找\n");
	printf("[2]按书名查找\n");
	int opt=0;
	scanf("%d",&opt);
	switch(opt){
		case 1:
		findBookByNo();
		break;
		case 2:
		findBookByNa();
		break;
		default:
		printf("无此操作\n");
		return;
	}
}

int findBookByNo(){  //按图书编号查找
    printf("请输入要查找的编号\n");
	int id=0;
	scanf("%d",&id);
	if(boIndex==0){
		return -1;
	}
	for(int i=0;i<boIndex;i++){
		if(pBos[i].bookNo==id){
			showBook(pBos+i);
			return 0;
		}
	}
	printf("查无此书\n");
}
int findBookByNa(){  //按图书名字查找
    printf("请输入要查找的书名\n");
	char name[40]={};
    scanf("%s",name);
	if(boIndex==0){
		return -1;
	}
	for(int i=0;i<boIndex;i++){
		if(strcmp(pBos[i].bookName,name)==0){
			showBook(pBos+i);
			return 0;
		}
	}
	printf("查无此书\n");
}

void showBook(books *pb){   //显示一本书的信息
	printf(" %d   %s   %s  %d  %d\n",pb->bookNo,pb->bookName,pb->bookAut,pb->bookPrice,pb->leaNum);
}

void listBook(){
	printf("%d\n",boIndex);
	if(boIndex==0){
		printf("暂无图书\n");
	}else{
		printf("编号  书名   作者 价格 热度\n");
		for(int i=0;i<boIndex;i++){
			showBook(pBos+i);
		}
	}
}

void scanAdmin(){
	int id=0;
	char code[20]={};
	printf("请输入用户名\n");
	scanf("%d",&id);
	printf("请输入密码\n");
	scanf("%s",code);
    adminLog(id,code);
}
extern admins *pAds;
int adminLog(int id,char *pcode){        //验证用户名和密码
	for(int i=0;i<adIndex;i++){
		if(pAds[i].adminID==id){
			if(strcmp(pAds[i].adminCode,pcode)==0){
				showAdminMenu(i);
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

void showAdminMenu(int adID){
	printf("——————————————————————————————————\n");
	printf("您好，管理员%s\n",pAds[adID].adminName);
	printf("——————————————————————————————————\n");
	printf("请选择操作\n");
	printf("[1]图书功能\n");
	printf("[2]读者功能\n");
	printf("——————————————————————————————————\n");
	adminMenu();
}

void adminMenu(){          //选择操作图书还是读者
	int opt=0;
	scanf("%d",&opt);
	switch(opt){
		case 1:
		bookFunMenu();
		break;
		case 2:
		readFunMenu();
		break;
		default:
		printf("无效操作\n");
		return;
	}
}



void bookFunMenu(){
	while(1){
		printf("——————————————————————————————————\n");
	    printf("请选择操作\n");
		printf("[1]添加图书\n");
		printf("[2]删除图书\n");
		printf("[3]修改图书信息\n");
		printf("[4]查找图书\n");
		printf("[5]列出全部图书\n");
		printf("[6]保存并退出\n");
		printf("——————————————————————————————————\n");
		int opt=0;
		scanf("%d",&opt);
		switch(opt){
			case 1:
			addBook(&book);
			addBoToP(book);
			break;
     		case 2:
			delBook(&book);
			break;
			case 3:
			modiBook();
			break;
			case 4:
			findBookMenu();
			break;
			case 5:
			listBook();
			break;
			case 6:
			saveBook("book.txt");
			printf("已保存\n");
			return;
		}
	}
}

readers reader={};
extern int reIndex;    //有多少读者
readers *pRes=NULL;
int reCnt=20;          //读者总数

int addReToP(readers s){
	if(pRes==NULL){
		pRes=calloc(reCnt,sizeof(readers));   //申请动态内存
		if(pRes==NULL){
			return -1;
		}
	}
    if(reIndex >= reCnt){
		pRes=realloc(pRes,2*reCnt*sizeof(readers));  //扩容读者列表
		reCnt=2*reCnt;
		if(pRes==NULL){
		}
	}
	pRes[reIndex]=s;       //将读者信息添加至动态内存
    reIndex++;
}

int loadReader(const char *path){        //读取文件到reader，再添加到动态内存
    FILE *fp=fopen(path,"r");
	if(fp==NULL){
		return -1;
	}
	while(fread(&reader,sizeof(readers),1,fp)>0){
		addReToP(reader);
	}
	fclose(fp);
	return 0;
}
void addReader(readers *pr){
	int readIdUp=1;
	if(reIndex==0){
		reader.readerID=readIdUp;
	}else{
		for(int j=0;j<reIndex;j++){
		    for(int i=0;i<=reIndex;i++){
				if(pRes[i].readerID==readIdUp){
			        readIdUp+=1;
					continue;
				}
				reader.readerID=readIdUp;//生成读者编号
		    }
		}
	}
	printf("请输入读者密码");
	scanf("%s",pr->readerCode);
	printf("请输入读者姓名\n");
	scanf("%s",pr->readerName);
	printf("请输入读者联系方式\n");
	scanf("%d",&pr->readerPhone);
	printf("请输入读者余额\n");
	scanf("%d",&pr->readerMoney);
}

int saveReader(const char *path){                     //把动态内存中的内容写到文件中
	FILE *fp=fopen(path,"w");
	if(fp==NULL){
		return -1;
	}
	fwrite(pRes,sizeof(readers),reIndex,fp);
	fclose(fp);
	return 0;
}

int delReader(){
	printf("请输入要删除的读者编号\n");
	int no=0;
	scanf("%d",&no);
	for(int i=0;i<reIndex;i++){
		if(pRes[i].readerID==no){
			pRes[i]=pRes[reIndex-1];
		}
	}
	--reIndex;
}

void modiReader(){                 //修改读者信息
	printf("请输入读者用户名\n");
	int id=0;
	scanf("%d",&id);
	int reId=0;
	for(int i=0;i<reIndex;i++){
		if(pRes[i].readerID==id){
			reId=i;
		}
		if(i==reIndex){
			reId=-1;
		}
	}
	if(reId==-1){
		printf("查无此人\n");
	}
	showReader(pRes+reId);
	printf("——————————————————————————————————\n");
	printf("请选择要修改的信息\n");
	printf("[1]密码\n");
	printf("[2]姓名\n");
	printf("[3]联系方式\n");
	printf("[4]余额\n");
	printf("——————————————————————————————————\n");
	int opt=0;
	scanf("%d",&opt);
	switch(opt){
		case 1:
		printf("请输入新的密码\n");
		char code[20]={};
		scanf("%s",code);
		strcpy(pRes[reId].readerCode,code);
		break;
		case 2:
		printf("请输入新的姓名\n");
		char name[40]={};
		scanf("%s",name);
		strcpy(pRes[reId].readerName,name);
		break;
        case 3:
		printf("请输入新的联系方式\n");
		int phone=0;
		scanf("%d",&phone);
		pRes[reId].readerPhone=phone;
		break;
		case 4:
		printf("请输入新的余额");
		int money;
		scanf("%d",&money);
		pRes[reId].readerMoney=money;
		break;
        default:
		printf("无效操作\n");
		break;
	}
	
}

void findReaderMenu(){
printf("选择查找方式\n");
	printf("[1]按用户名查找\n");
	printf("[2]按姓名查找\n");
	int opt=0;
	scanf("%d",&opt);
	switch(opt){
		case 1:
		findReaderById();
		break;
		case 2:
		findReaderByNa();
		break;
		default:
		printf("无此操作\n");
		return;
	}
}

int findReaderById(){  //按读者用户名查找
    printf("请输入要查找的用户名\n");
	int id=0;
	scanf("%d",&id);
	if(reIndex==0){
		return -1;
	}
	for(int i=0;i<reIndex;i++){
		if(pRes[i].readerID==id){
			showReader(pRes+i);
			return 0;
		}
	}
	printf("查无此人\n");
}
int findReaderByNa(){  //按读者姓名查找
    printf("请输入要查找的姓名\n");
	char name[40]={};
	scanf("%s",name);
	if(reIndex==0){
		return -1;
	}
	for(int i=0;i<reIndex;i++){
		if(strcmp(pRes[i].readerName,name)==0){
			showReader(pRes+i);
			return 0;
		}
	}
	printf("查无此人\n");
}

void showReader(readers *pr){   //显示一名读者的信息
	printf("%d       %s  %s  %d   %d\n",pr->readerID,pr->readerCode,pr->readerName,pr->readerPhone,pr->readerMoney);
}

void listReader(){
	printf("%d\n",reIndex);
	if(reIndex==0){
		printf("暂无读者\n");
	}else{
		printf("用户名  密码  姓名   联系方式   余额\n");
		for(int i=0;i<reIndex;i++){
			showReader(pRes+i);
		}
	}
}

void readFunMenu(){
	while(1){
		printf("——————————————————————————————————\n");
	    printf("请选择操作\n");
		printf("[1]添加读者\n");
		printf("[2]删除读者\n");
		printf("[3]修改读者信息\n");
		printf("[4]查找读者\n");
		printf("[5]列出全部读者\n");
		printf("[6]保存并退出\n");
		printf("——————————————————————————————————\n");
		int opt=0;
		scanf("%d",&opt);
		switch(opt){
			case 1:
			addReader(&reader);
			addReToP(reader);
			break;
			case 2:
			delReader();
			break;
			case 3:
			modiReader();
			break;
			case 4:
			findReaderMenu();
			break;
			case 5:
			listReader();
			break;
			case 6:
			saveReader("reader.txt");
			printf("已保存\n");
			return;
		}
	}
}

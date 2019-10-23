#include"sAdmin.h"
#include<string.h>
#include<stdio.h>
#include<stdlib.h>

admins admin={};  //保存管理员

supAdmin supOne={"hero","123456789"};

void supScan(){     //输入用户名密码
	char id[10];
	char code[10];
	printf("请输入用户名\n");
	scanf("%s",id);
	printf("请输入密码\n");
	scanf("%s",code);
	supLog(id,code);
}

void supLog(char *pid,char *pcode){       //是否登陆成功
    if(strcmp(supOne.sAdminID,pid)==0&&strcmp(supOne.sAdminCode,pcode)==0){
		sAdminMenu();
	}else{
		printf("登陆失败\n");
		supScan();
	}
}




admins *pAds=NULL;  //extern admins *pAds;
int adCnt=10;       //管理员总数
extern int adIndex;      //有多少个管理员
int addAdToP(admins s){
	if(pAds==NULL){
		pAds=calloc(adCnt,sizeof(admins));   //申请动态内存
		if(pAds==NULL){
			return -1;
		}
	}
    if(adIndex >= adCnt){
		pAds=realloc(pAds,2*adCnt*sizeof(admins));  //扩容管理员列表
		adCnt=2*adCnt;
		if(pAds==NULL){
			return -1;
		}
	}
	pAds[adIndex]=s;       //将管理员信息添加至动态内存
    adIndex++;
}

int loadAdmin(const char *path){                          //读取文件到admin，再添加到动态内存
    FILE *fp=fopen(path,"r");
	if(fp==NULL){
		return -1;
	}
	while(fread(&admin,sizeof(admins),1,fp)>0){
		addAdToP(admin);
	}
	fclose(fp);
	return 0;
}

int saveAdmin(const char *path){                     //把动态内存中的内容写到文件中
	FILE *fp=fopen(path,"w");
	if(fp==NULL){
		return -1;
	}
	fwrite(pAds,sizeof(admins),adIndex,fp);
	fclose(fp);
	return 0;
}

int adminIdUp=100;            //管理员的用户名
char adminDe[20]={"123456"};   //管理员默认密码

void addAdmin(admins *ad){//scanAdmin
    if(adIndex==0){
		admin.adminID=adminIdUp+1;
	}else{
		for(int j=0;j<=adIndex;j++){
			for(int i=0;i<=adIndex;i++){
				if(pAds[i].adminID==(adminIdUp+1)){  
					adminIdUp+=1;
					continue;
				}
				admin.adminID=adminIdUp+1;   //生成管理员用户名
			}
		}
	}
	strcpy(admin.adminCode,adminDe);
	printf("请输入管理员姓名\n");
	scanf("%s",ad->adminName);
	printf("请输入管理员年龄\n");
	scanf("%d",&ad->adminAge); 
}

int del(admins *pa,int id){            //删除管理员信息   pads[i]=pads[adinex-1]; adindex--;
    for(int i=0;i<adIndex;i++){
	    if(pAds[i].adminID==id){
			for(int j=i;j<adIndex;j++){  
				pAds[j]=pAds[j+1];
			}
		}
	}
	--adIndex;
}

int delAdmin(admins *pa){
	if(pAds==NULL){
		return -1;
	}
	int id=0;
	printf("请输入要删除的管理员用户名\n");
    scanf("%d",&id);
    del(pAds,id);
}

int findAdminById(admins *pa,int id){          //按id查找管理员，返回位置
	for(int i=0;i<adIndex;i++){
		if((pAds[i].adminID==id)){
			return i;
		}
	}
	return -1;
}
int findAdmin(){       //查找管理员
	printf("请输入要查找的管理员用户名\n");
	int id=0;
	scanf("%d",&id);
	int adID=findAdminById(pAds,id);
	showAdmin(pAds+adID);
}

void modiAdmin(){                 //修改管理员信息
	printf("请输入管理员用户名\n");
	int id=0;
	scanf("%d",&id);
	int adID=findAdminById(pAds,id);
	if(adID==-1){
		printf("查无此人\n");
	}
	showAdmin(pAds+adID);
	printf("——————————————————————————————————\n");
	printf("请选择要修改的信息\n");
	printf("[1]密码\n");
	printf("[2]姓名\n");
	printf("[3]年龄\n");
	printf("——————————————————————————————————\n");
	int opt=0;
	scanf("%d",&opt);
	switch(opt){
		case 1:
		printf("请输入新的密码\n");
		char code[20]={};
		scanf("%s",code);
		strcpy(pAds[adID].adminCode,code);
		break;
		case 2:
		printf("请输入新的姓名\n");
		char name[10]={};
		scanf("%s",name);
		strcpy(pAds[adID].adminName,name);
		break;
        case 3:
		printf("请输入新的年龄\n");
		int age=0;
		scanf("%d",&age);
		pAds[adID].adminAge=age;
		break;
        default:
		printf("无效操作\n");
		break;
	}
	
}

void showAdmin(admins *pa){       //显示一名管理员的信息
	printf(" %d %s %s %d\n",pa->adminID,pa->adminCode,pa->adminName,pa->adminAge);
}

void listAdmin(){
	if(adIndex==0){
		printf("暂无管理员\n");
	}else{
		printf("用户名  密码  姓名 年龄\n");
		for(int i=0;i<adIndex;i++){
			showAdmin(pAds+i);
		}
	}
}

void showAdMenu(){
	printf("——————————————————————————————————\n");
	printf("请选择操作\n");
	printf("[1]添加管理员\n");
	printf("[2]删除管理员\n");
	printf("[3]修改管理员信息\n");
	printf("[4]列出所有管理员\n");
	printf("[5]查找管理员\n");
	printf("[6]保存并退出\n");
	printf("——————————————————————————————————\n");
}

void sAdminMenu(){	
	printf("——————————————————————————————————\n");
	printf("您好，超级管理员\n");
	while(1){
		showAdMenu();
		int opt=0;
		scanf("%d",&opt);
		switch(opt){
			case 1:
			addAdmin(&admin);
			addAdToP(admin);
			break;
			case 2:
			delAdmin(pAds);
			break;
			case 3:
			modiAdmin();
			break;
			case 4:
			listAdmin();
			break;
			case 5:
			findAdmin();
			break;
			case 6:
			saveAdmin("admin.txt");
			printf("已保存\n");
			return;
			default:
			printf("无此操作，请重新选择\n");
			break;
		}
	}
}

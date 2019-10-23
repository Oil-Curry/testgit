#ifndef SADMIN_H__
#define SADMIN_H__

typedef struct supAdmin{
	char sAdminID[10];
	char sAdminCode[20];
}supAdmin;

typedef struct admins{
	int adminID;
	char adminCode[20];
	char adminName[10];
	int adminAge;
}admins;


void supScan();
void supLog(char *id,char *code);
void sAdminMenu();
int loadAdmin(const char *path);
int saveAdmin(const char *path);
int addAdToP(admins s);
void addAdmin(admins *ad);
int del(admins *pa,int id);
int delAdmin(admins *pa);
void showAdmin(admins *pa);
void showAdMenu();
int findAdminById(admins *pa,int id);
int findAdmin();
void modiAdmin();

#endif

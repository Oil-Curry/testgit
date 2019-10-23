#include<iostream>
#include<vector>
#include<typeinfo>
#include<cstdio>
using namespace std;

class Card{
	public:
	static int cardId;//生成卡号
	int id;          //卡号
	string name; //姓名
	int ident;      //身份证号
	string code;      //密码
	double money;//余额

	Card(string name="",int ident=0,string code="0"):name(name),ident(ident),code(code){
		money=0;
		id=cardId++;
		cout << "*您的卡号是：" << id << "*" << endl;
	}
	void setCode(string code1){ //修改密码
		code=code1;
	}
	double getMoney(){
		return money;
	}
	int getId(){
		return id;
	}
	string getCode(){
		return code;
	}
	void saveMoney(double moneyAdd){
		if(moneyAdd>=0){
			money=money+moneyAdd;
		}else{
			cout << "！不能存入负数 ！" <<endl;
		}
	}
	void transIn(double moneyIn){ //转入
		money=money+moneyIn;
	}
	virtual void drawMoney(double moneySub)=0;
};

int Card::cardId=201901;

class ZGCard:public Card{  //中国银行卡
	public:
	ZGCard(string name="",int ident=0,string code="0"):Card(name,ident,code){
		money=0;
		id=cardId;
	}
	void drawMoney(double moneySub){
		if(money<moneySub){
			cout << "！余额不足 ！" << endl;
			return;
		}
		money=money-moneySub;
	}
};

class ZSCard:public Card{  //招商银行卡
	public:
	ZSCard(string name="",int ident=0,string code="0"):Card(name,ident,code){
		money=0;
		id=cardId;
	}
	void drawMoney(double moneySub){
/*		if(moneySub<0){
			cout << "！不能取出负数 ！" << endl;
			return;
		}
		if(money<(moneySub+1)){
			cout << "！余额不足 ！" << endl;
			return;
		}
		money=money-moneySub-1;*/
		if(money<moneySub){
			cout << "！余额不足 ！" << endl;
			return;
		}
		money=money-moneySub;
	}
};

class NYCard:public Card{ //农业银行卡
	public:
	NYCard(string name="",int ident=0,string code="0"):Card(name,ident,code){
		money=0;
		id=cardId;
	}
	void drawMoney(double moneySub){
	/*	if(moneySub<0){
			cout << "！不能取出负数 ！" << endl;
			return;
		}
		if(moneySub<=1000){
			moneySub+=1;
		}else{
			money+=1+(moneySub-1000)/100;
		}*/
		if(money<moneySub){
			cout << "！余额不足 ！" << endl;
			return;
		}
		money=money-moneySub;
	}
};
/*
*/
class Bank{
	int bankNo;
	vector<Card*> cards; //必须是基类的指针或引用
	static int nyNum;
	public:
	void bankChoseMenu(){
		cout << "银行管理系统" <<endl;
		cout << "1.中国银行" <<endl;
		cout << "2.招商银行" <<endl;
		cout << "3.农业银行" <<endl;
		cout << "4.退出" <<endl;
	}
	void bankMenu(){
		switch(bankNo){
			case 1:
			cout << "中国银行网上系统" << endl;
			break;
			case 2:
			cout << "招商银行网上系统" << endl;
			break;
			case 3:
			cout << "农业银行网上系统" << endl;
			break;
			default:
			cout << "！未知银行 ！" << endl;
		}
		cout << "1.开户" << endl;
		cout << "2.登录" << endl;
		cout << "3.重新选择银行" << endl;
	}
	void clientMenu(){
		cout << "1.查看余额" << endl;
		cout << "2.修改密码" << endl;
		cout << "3.存钱" << endl;
		cout << "4.取钱" << endl;
		cout << "5.转账" << endl;
		cout << "6.退出" << endl;
		cout << "——————————" <<endl;
	}
	void run(){
		while(1){
			bankChoseMenu();
			int opt=0;
			cin >> opt;
			switch(opt){
				case 1:
				bankNo=1;  //中国银行
				reAndLo();
				break;
				case 2:
				bankNo=2;  //招商银行
				reAndLo();
				break;
				case 3:
				bankNo=3;  //农业银行
				reAndLo();
				break;
				case 4:  //退出
				return;
				default:
				cout << "无效操作" <<endl;
				fflush(stdin);
				break;
			}
		}
	}
	void reAndLo(){  //开户和登录
		while(1){
			bankMenu();
			int opt=0;
			cin >> opt;
			switch(opt){
				case 1:  //开户(注册)
				registerCard();
				break;
				case 2:  //登录
				Login();
				break;
				case 3:
				return;
				default:
				cout << "无效操作" <<endl;
				break;
			}
		}
	}
	void registerCard(){ //注册
		string code;
		string name;
		int ident;
		cout<<"请输入姓名：";
		cin >> name;
		cout<<"请输入身份证号码：";
		cin>> ident;
		cout<<"请输入密码：";
		cin>>code;
		if(bankNo==1){
			regZG(name,ident,code);
			cout << "*中国银行卡开户成功*" <<endl;
		}else if(bankNo==2){
			regZS(name,ident,code);
			cout << "*招商银行卡开户成功*" <<endl;
		}else if(bankNo==3){
			regNY(name,ident,code);
			cout << "*农业银行卡开户成功*" <<endl;
		}else{
			cout<<"！出错 ！"<<endl;
		}
	}
	void regZG(string name,int ident,string code){
		Card* c=new ZGCard(name,ident,code);
		cards.push_back(c);
	}
	void regZS(string name,int ident,string code){
		Card* c=new ZSCard(name,ident,code);
		cards.push_back(c);
	}
	void regNY(string name,int ident,string code){
		Card* c=new NYCard(name,ident,code);
		cards.push_back(c);
	}
	void Login(){
		int id;
		string code;
		cout<<"请输入账号：";
		cin>>id;
		cout<<"请输入密码：";
		cin>>code;
	//	vector<Card*>::iterator it = cards.begin();
		for(int i=0;i<cards.size();i++){
			if(cards[i]->getId()==id || cards[i]->getCode()==code){
				choseOpt(cards[i]);
				return;
			}
		}
		cout<<"！登录失败 ！"<<endl;
	}
	void choseOpt(Card* c){
		double money=0;
		string code;
		while(1){
			cout << "——————————" <<endl;
			cout << "*欢迎，" << c->name << "*" <<endl;
			clientMenu();
			cout << "input：";
			int opt=0;
			cin>>opt;
			switch(opt){
				case 1: //查看余额
				cout << "您的余额为：" << c->getMoney() <<endl;
				break;
				case 2:  //修改密码
				cout << "请输入新的密码：";
				cin>>code;
				c->setCode(code);
				cout << "*密码修改成功*" << endl;
				break;
				case 3:  //存钱
				cout << "请输入要存的金额：";
				cin>>money;
				c->saveMoney(money);
				break;
				case 4:  //取钱
				bankDrawMoney(c);
				break;
				case 5:  //转账
				transMoney(c);
				break;
				case 6:			
				return;
				default:
				cout << "无效操作" <<endl;
				break;
			}
		}
	}
	void bankDrawMoney(Card* c){
		double money=0;
		double more=0;
		cout << "请输入要取的金额：" << endl;
		cin>>money;
		if(money<0){
			cout << "！不能取出负数 ！" << endl;
			return;
		}
		if(bankNo==1 && typeid(*c)!=typeid(ZGCard)){
			for(int i=money;i>=0;i-100){
				more++;
			}
			c->drawMoney(money+more);
			cout << "*取出" << money << "元，支付手续费" << more << "元*" << endl;
			return;
		}else if(bankNo==1){
			more=0;
			c->drawMoney(money);
			cout << "*取出" << money << "元，支付手续费" << more << "元*" << endl;
		}else if(bankNo==2){
			more=1;
			c->drawMoney(money+more);
			cout << "*取出" << money << "元，支付手续费" << more << "元*" << endl;
		}else if(bankNo==3){
			if(money<=1000){
				more=1;
			}else{
				more=1+(money-1000)/100;
			}
			c->drawMoney(money+more);
			cout << "*取出" << money << "元，支付手续费" << more << "元*" << endl;
		}
	}
	void transMoney(Card* c){ //转账
		int id;
		double money;
		double more=0;
		cout << "请输入要转入的账号：" << endl;
		cin>>id;
		cout << "请输入要转入的金额：" << endl;
		cin>>money;
		int i=0;
	/*	vector<Card*>::iterator it = cards.begin();
		for(;it != cards.end(); it++){
			if((*it)->getId()==id){
				break;
			}
		}
		if(it==cards.end()){
			cout << "！无此用户 ！" << endl;
			return;
		}*/
		for(;i<cards.size();i++){
			if(cards[i]->getId()==id){
				break;
			}
		}
		if(cards[i]->getId()==c->getId()){
			cout << "！不能转账给自己。 ！"<< endl;
			return;
		}
		if(i==cards.size()){
			cout << "！无此用户 ！" << endl;
			return;
		}
		if(bankNo==1){
			if(typeid(cards[i])!=typeid(ZGCard)){
				more=money*0.02;
			}
			else{
				more=5;
			}
		}else if(bankNo==2){
			more=money*0.02;
		}else if(bankNo==3){
			more=0;
			nyNum++;
			if(nyNum>3){
				more=money*0.01;
			}
		}
		if(c->getMoney()<(money+more)){
			cout << "！余额不足 ！" << endl;
			return;
		}
		c->drawMoney(money+more);
		cards[i]->transIn(money);
		cout << "*已转账" << money << "元，收取手续费" << more << "元。*" << endl;
	}

	~Bank(){
		for(int i=0;i<cards.size();i++){
			delete cards[i];
		}
	}
};
int Bank::nyNum=0;

int main(){
	Bank b;
	b.run();


	return 0;
}

#include<iostream>
#include<vector>
using namespace std;

class Stu{
	static int makeId;
	int id;
	string name;
	int score;
	public:
	Stu(string name="",int score=0):name(name),score(score){
		id=makeId++;
	}
	int getId(){
		return id;
	}
	string getName(){
		return name;
	}
	int getScore(){
		return score;
	}
};

int Stu::makeId=20190101;

class Grade{
	static int makeNo;
	int no;
	vector<Stu> stus;
	public:
	Grade(){
		no=makeNo++;
	}
	int getNo(){
		return no;
	}
	void addStu(string name,int score){
		stus.push_back(Stu(name,score));
	}
	friend ostream& operator<<(ostream& os,Grade& g){
		if(g.stus.empty()==1){
			os << g.no << "班无学生。" << endl;
			return os;
		}
		os << g.no << "班：" << endl;
		for(int i=0;i<(g.stus).size();i++){
			os << " 学号：" << g.stus[i].getId() <<" 姓名：" << g.stus[i].getName() << " 成绩：" << g.stus[i].getScore() << endl;
		}
		return os;
	}
};

int Grade::makeNo=101;

class Manager{
	vector<Grade> grades;
	public:
	Manager(){
	}
	void menu(){
		cout << "欢迎来到学校管理系统" <<endl;
		cout << "————————————————————————————————" << endl;
		cout << "[1]显示学生" <<endl;
		cout << "[2]显示班级" <<endl;
		cout << "[3]添加班级" <<endl;
		cout << "[4]添加学生" <<endl;
		cout << "[5]删除班级" <<endl;		
		cout << "[0]退出" <<endl;
		cout << "————————————————————————————————" << endl;
		cout << "请输入指令：";
	}
	void run(){
		while(1){
			menu();
			int opt=0;
			cin>>opt;
			switch(opt){
				case 1:
				listStu();
				break;
				case 2:
				listGrade();				
				break;
				case 3:
				addGrade();
				break;
				case 5:
				deleteGrade();
				break;
				case 4:
				addStudent();
				break;
				case 0:
				return;
				default:
				break;
			}
		}
	}
	void addGrade(){  //添加班级
		grades.push_back(Grade());
		cout << "班级添加成功！" <<endl;
	}
	void listGrade(){  //列出所有班级
		if(grades.empty()==1){
			cout << "没有班级。" <<endl;
			return;
		}
		cout << "目前有以下班级：" << endl;
		for(int i=0;i<grades.size();i++){
			cout << grades[i].getNo() << "班" << endl;
		}
	}
	void deleteGrade(){
		cout<<"请输入要删除的班级号：";
		int index;
		cin>>index;
		vector<Grade>::iterator it = grades.begin();
		for(;it != grades.end(); it++){
			if((*it).getNo() == index){
				grades.erase(it);
				cout << "删除成功！" <<endl;
				return;
			}
		}
		cout <<"无此班级！"<<endl;
	}
	void addStudent(){   //添加学生
		cout<<"请选择班级：";
		int no;
		string name;
		int score;
		cin>>no;
	/*	vector<Grade>::iterator it = grades.begin();
		for(;it != grades.end(); it++){
			if((*it).getNo() == no){
				
				return;
			}
		}*/
		for(int i=0;i<grades.size();i++){
			if(grades[i].getNo()==no){
				cout<<"请输入学生姓名：";
				cin>>name;
				cout<<"请输入学生成绩：";
				cin>>score;
				grades[i].addStu(name,score);
				cout<<"添加成功！"<<endl;
				return;
			}
		}
		cout << "无此班级！"<<endl;
	}
	void listStu(){  //列出所有学生
		for(int i=0;i<grades.size();i++){
			cout << grades[i] <<endl;
		}
	}

};

int main(){
	Manager man;
	man.run();

	return 0;
}

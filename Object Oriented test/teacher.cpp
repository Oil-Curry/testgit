#include<iostream>
using namespace std;

class Teacher{
	int no;
	string name;
	int age;
	int salary;
	public:
	Teacher(){
		no=age=salary=0;
		name="无输入";
	}
	Teacher(int no,string name,int age,int salary):no(no),name(name),age(age),salary(salary){
	}
	int getNo(){
		return no;
	}
	string getName(){
		return name;
	}
	int getAge(){
		return age;
	}
	int getSalary(){
		return salary;
	}
	void setNo(int no1){
		no=no1;
	}
	void setName(string name1){
		name=name1;
	}
	void setAge(int age1){
		age=age1;
	}
	void setSalary(int salary1){
		salary=salary1;
	}
	void show(){
		cout << "编号：" << no << " 姓名：" << name << " 年龄：" << age << " 工资：" << salary << endl;
	}
};

class TeacherManager{
	int cnt;   //总量
	int index; //现有
	Teacher *pt;
	public:
	TeacherManager(int cnt):cnt(cnt){
		index=0;
		pt=new Teacher[cnt];
	}
	void addTea(Teacher &t){
		if(index==cnt){
			cout<<"failed"<<endl;
			return;
		}
		pt[index]=t;
		index+=1;
	}
	void addTea(int no,string name,int age,int salary){
		if(index==cnt){
			cout<<"failed"<<endl;
			return;
		}
		pt[index]=Teacher(no,name,age,salary);
	//	pt[index].setNo(no);
		index+=1;
	}
	void delTea(int no){
		for(int i=0;i<index;i++){
			if((pt[index]).getNo()==no){
			}
		}
	}
	void findTea(int no){
		for(int i=0;i<index;i++){
			if((pt[index]).getNo()==no){
				(pt[index]).show();
			}
		}
	}
	void listTea(){
		for(int i=0;i<index;i++){
			(pt[i]).show();
		}
	}

	void del(){
		delete[] pt;
	}

};


int main(){
	Teacher tea(114,"钟门怒",39,50000);
	tea.show();
	TeacherManager manager(10);
	manager.addTea(tea);
	manager.addTea(514,"曹操",27,39000);
	manager.listTea();

	manager.del();

	return 0;
}

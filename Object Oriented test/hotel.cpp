#include<iostream>
using namespace std;

class Guest{
	string name;
	public:
	Guest(string name=""){
		this->name=name;
	}
	string getName(){
		return name;
	}
	void setName(string name){
		this->name=name;
	}
};

class Room{
	int id;
	Guest *g;
	public:
	Room(){
		id=0;
		g=NULL;
	}
	Room(int id){
		this->id=id;
		g=NULL;
	}
	Room(const Room& r){
		id=r.id;
		if(r.g!=NULL){
			g=new Guest(*r.g);
		}else{
			g=NULL;
		}
	}
	void setId(int id){
		this->id=id;
	}
	int getId(){
		return id;
	}
	bool isEmpty(){
		return g==NULL;
	}
	Guest* getGuest(){
		return g;
	}
	void setGuest(const Guest& g){
		this->g=new Guest(g);
	}
	void out(){
		if(g!=NULL){
			delete g;
			g=NULL;
		}
	}
	~Room(){
		out();
	}
};

class Hotel{
	size_t layer;
	size_t count;
	Room* rooms;
	public:
	Hotel(size_t layer=3,size_t count=5){
		this->layer=layer;
		this->count=count;
		rooms=new Room[layer*count];
		for(int i=0;i<layer;i++){
			for(int j=0;j<count;j++){
				rooms[i*count+j].setId((i+1)*100+j+1);
			}
		}
	}
	~Hotel(){
		if(rooms!=NULL){
			delete[] rooms;
			rooms=NULL;
		}
	}
	Room* getRoomById(int id){
		for(int i=0;i<layer;i++){
			for(int j=0;j<count;j++){
				if(rooms[i*count+j].getId()==id){
					return &rooms[i*count+j];
				}
			}
		}
		return NULL;
	}
	friend ostream& operator<<(ostream& os,Hotel &h){
		for(int i=0;i<h.layer;i++){
			for(int j=0;j<h.count;j++){
				os<<h.rooms[i*h.count+j].getId()<<"\t";
			}
			os<<endl;
			for(int j=0;j<h.count;j++){
				if(h.rooms[i*h.count+j].isEmpty()){
					os<<"   "<<"\t";
				}else{
					os<<h.rooms[i*h.count+j].getGuest()->getName();
				}
			}
			os<<endl;
		}
		return os;
	}
};

class HotelManager{
	Hotel hotel;
	public:
	HotelManager(size_t layer,size_t count):hotel(layer,count){
	}
	void menu(){
		cout<<"欢迎来到酒店管理系统"<<endl;
		cout<<"——————————————————————————"<<endl;
		cout<<"请选择操作："<<endl;
		cout<<"[1]显示所有房间"<<endl;
		cout<<"[2]入住"<<endl;
		cout<<"[3]退房"<<endl;
		cout<<"[4]退出系统"<<endl;
		cout<<"——————————————————————————"<<endl;
	}
	void run(){
		while(1){
			menu();
			int opt=0;
			cin>>opt;
			switch(opt){
				case 1:
				list();
				break;
				case 2:
				in();
				break;
				case 3:
				out();
				break;
				case 4:
				return;
				default:
				cout<<"无效操作"<<endl;
				continue;
			}
		}
	}
	void list(){
		cout << hotel;
	}
	void in(){
		cout<<"请输入房间号：";
		int id=0;
		cin>>id;
		Room* room=hotel.getRoomById(id);
		if(room==NULL){
			cout<<id<<"号房间不存在。"<<endl;
			return;			
		}
		if(!room->isEmpty()){
			cout<<id<<"号房间已有人。"<<endl;
			return;
		}
		cout<<"请输入姓名：";
		string name;
		cin>>name;
		room->setGuest(Guest(name));
	}
	void out(){
		int id=0;
		cout<<"请输入房间号：";
		Room* room=hotel.getRoomById(id);
		if(room==NULL){
			cout<<id<<"号房间不存在。"<<endl;
			return;			
		}
		if(room->isEmpty()){
			cout<<id<<"号房间无人。"<<endl;
			return;
		}
		string name=room->getGuest()->getName();
		room->out();
		cout<<name<<"退房成功。"<<endl;
	}
};

int main(){
	HotelManager hm(4,6);
	hm.run();

	return 0;
}

#include<iostream>
using namespace std;

class List{
	class Node{
		public:
		int data;
		Node* next;
		Node(int data,Node *next):data(data),next(next){
		}
	};
	Node* head;
	Node* getPrevNode(size_t index){
		Node* node=head;
		--index;
		while(index!=0){
			if(node==NULL){
				return NULL;
			}
			--index;
			node=node->next;
		}
		return node;
	}

	public:
	List(){
		head=NULL;
	}
	bool isEmpty(){
		return head==NULL;
	}
	size_t size(){
		Node* node=head;
		size_t cnt=0;
		while(node!=NULL){
			cnt++;
			node=node->next;
		}
		return cnt;
	}
	void clear(){
		Node* node=head;
		while(node!=NULL){
			Node*next=node->next;
			delete node;
			node=next;
		}
		node=NULL;
	}
	~List(){
		clear();
	}
	void pushFront(int data){
		head=new Node(data,head);
	}
	friend ostream& operator<<(ostream& os,const List& list){
		Node* node=list.head;
		while(node!=NULL){
			os<<node->data<<" ";
			node=node->next;
		}
		return os<<endl;
	}
	void pushBack(int data){
		Node** node=&head;
		while(*node!=NULL){
			node=&(*node)->next;
		}
		*node=new Node(data,NULL);
	}
	bool insert(size_t index,int data){
		if(index==0){
			pushFront(data);
			return true;
		}
		Node* prevNode=getPrevNode(index);
		if(prevNode==NULL){
			return false;
		}
		prevNode->next=new Node(data,prevNode->next);
		return true;
	}
	bool remove(size_t index){
		if(index==0){
			Node* node=head->next;
			delete head;
			head=node;
			return true;
		}
		Node* prevNode=getPrevNode(index);
		if(prevNode==NULL||prevNode->next==NULL){
			return false;
		}
		Node* node=prevNode->next;
		prevNode->next=node->next;
		delete node;
		return true;
	}
	int& operator[](size_t index){
		Node* node=head;
		for(size_t i=0;i<index;i++){
			node=node->next;
		}
		return node->data;
	}
	const int& operator[](size_t index)const{
		return const_cast<List&>(*this)[index];
	}
	List& reverse(){
		if(head==NULL||head->next==NULL){
			return *this;
		}
		Node* prev=head;
		Node* curr=head->next;
		while(curr!=NULL){
			Node* next=curr->next;
			curr->next=prev;
			prev=curr;
			curr=next;
		}
		head->next=NULL;
		head=prev;
		return *this;
	}
	List(const List& list){
		Node* node=list.head;
		Node** pnode=&head;
		while(node!=NULL){
			*pnode=new Node(node->data,NULL);
			node=node->next;
			pnode=&(*pnode)->next;
		}
	}
	List& operator=(const List& list){
		if(&list!=this){
			List l(list);
			Node* t=head;
			head=l.head;
			l.head=t;
		}
		return *this;
	}
};

int main(){
	List l;
	l.pushFront(7);
	l.pushFront(5);
	l.pushFront(4);
	l.pushFront(6);
	l.pushFront(9);
	cout << l;
	l.pushBack(50);
	cout << l;
	cout << l.reverse();
	l.insert(5,55);
	cout << l;
	l.remove(5);
	cout << l;


	return 0;
}

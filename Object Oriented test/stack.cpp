#include<iostream>
using namespace std;

class Stack{
	int *vect;
	size_t size; //zhongliang
	size_t index;//dangqiangeshu
	public:
	Stack(int size){
		this->size=size;
		vect=new int;
		index=0;
	}
	bool isFull(Stack &stack){
		return stack.size==stack.index;
	}
	bool isEmpty(Stack &stack){
		return stack.index==0;
	}
	void push(Stack &stack,int data){
		stack.vect[stack.index]=data;
		stack.index++;
	}
	int pop(Stack &stack){
		return stack.vect[--stack.index];
	}
	void show(Stack &stack){
		for(int i=0;i<index;i++){
			cout<<stack.vect[i]<<endl;
		}
	}
	void des(){
		delete vect;
	}
};



int main(){
	Stack stack(5);
	stack.push(stack,4);
	stack.push(stack,3);
	stack.show(stack);
	cout<<stack.pop(stack)<<endl;
	cout<<stack.pop(stack)<<endl;
	stack.des();


	return 0;
}

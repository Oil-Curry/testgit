#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"get_keyboard.h"

int board[7][8]={     //1墙 2箱子 3目的地 4老鼠
    {0,1,1,1,1,1,1,0},
	{0,1,0,0,0,0,1,1},
	{1,3,0,1,1,2,0,1},
	{1,0,3,3,2,0,0,1},
	{1,0,0,1,2,0,0,1},
	{1,0,0,4,0,1,1,1},
	{1,1,1,1,1,0,0,0},
};


int board2[7][8]={     //地图的备份
    {0,1,1,1,1,1,1,0},
	{0,1,0,0,0,0,1,1},
	{1,3,0,1,1,2,0,1},
	{1,0,3,3,2,0,0,1},
	{1,0,0,1,2,0,0,1},
	{1,0,0,4,0,1,1,1},
	{1,1,1,1,1,0,0,0},
};

void enter(int a[][8],size_t len){   //重置地图
	for(int i=0;i<len;i++){
		for(int j=0;j<8;j++){
			a[i][j]=board2[i][j];
		}
	}
}
int mapprint(int a[][8],size_t len){   //真正在使用的地图打印
	for(int i=0;i<len;i++){
		for(int j=0;j<8;j++){
			if((i==2&&j==1)||(i==3&&j==2)||(i==3&&j==3)){
				if(a[i][j]==2){
					printf("Y");
					continue;
				}else if(a[i][j]==4){
					printf("m");
					continue;
				}
			}
			if(a[i][j]==0){
				printf(" ");
			}else if(a[i][j]==1){
				printf("#");
			}else if(a[i][j]==2){
				printf("&");
			}else if(a[i][j]==3){
				printf("@");
			}else if(a[i][j]==4){
				printf("$");
			}
			
		}
		printf("\n");
	}
}
char map(int a){          //数字转化为字符
	char out=' ';
	if(a==0){
		out=' ';
	}else if(a==1){
		out='#';
	}else if(a==2){
		out='&';
	}else if(a==3){
		out='@';
	}else if(a==4){
		out='$';
	}

	return out;
}
char achieve(int a[][8],size_t len){
	if(a[2][1]==2){
		return 'Y';
	}
}

int print(int a[][8],size_t len){   //打印地图
	for(int i=0;i<len;i++){
		for(int j=0;j<8;j++){
			printf("%c",map(board[i][j]));
		}
		printf("\n");
	}
}

int where(int *pi,int *pj){    //老鼠在哪
	for(int i=0;i<7;i++){
		for(int j=0;j<8;j++){
			if(board[i][j]==4){
				*pi=i;
				*pj=j;
			}
		}
	}
}


int destin(int a[][8],size_t len,int i,int j){   //保留目的地	
	if((i==2&&j==1)||(i==3&&j==2)||(i==3&&j==3)){
		a[i][j]=3;
	}else{
		a[i][j]=0;
	}
}

int vect(int a[][8],size_t len,int *num){
	if(a[2][1]==2&&a[3][2]==2&&a[3][3]==2){
		
		printf("\n");
		printf("恭喜你，过关了！");
		printf("\n");
		*num=1;
	}
}


int main(){
	int i=0,j=0;
	printf("按任意方向键开始\n");

	while(1){
		where(&i,&j);              //老鼠在哪  
		int key=get_keyboard();
		system("clear");      
		switch(key){
			case KEY_UP:    //上
			if(board[i-1][j]==1){     //墙
				break;
			}
			if(board[i-1][j]==2&&board[i-2][j]!=1&&board[i-2][j]!=2){   //如果下一个是箱子，且下下个不是墙，下下个不是箱子
				board[i-2][j]=2;
			}else if(board[i-1][j]==2&&(board[i-2][j]==1||board[i-2][j]==2)){  //如果下一个是箱子，但下下个是墙或箱子
				break;
			}
			board[i-1][j]=4;      //走
			destin(board,7,i,j);     //离开目的地
			break;
			case KEY_DOWN:   //下
			if(board[i+1][j]==1){
				break;
			}
			if(board[i+1][j]==2&&board[i+2][j]!=1&&board[i+2][j]!=2){   //如果下一个是箱子，且下下个不是墙，下下个不是箱子
				board[i+2][j]=2;
			}else if(board[i+1][j]==2&&(board[i+2][j]==1||board[i+2][j]==2)){
				break;
			}
			board[i+1][j]=4;
			destin(board,7,i,j);
			break;
			case KEY_RIGHT:   //右
			if(board[i][j+1]==1){
				break;
			}
			if(board[i][j+1]==2&&board[i][j+2]!=1&&board[i][j+2]!=2){   //如果下一个是箱子，且下下个不是墙，下下个不是箱子
				board[i][j+2]=2;
			}else if(board[i][j+1]==2&&(board[i][j+2]==1||board[i][j+2]==2)){
				break;
			}
			board[i][j+1]=4;
			destin(board,7,i,j);
			break;
			case KEY_LEFT:   //左
			if(board[i][j-1]==1){
				break;
			}
			if(board[i][j-1]==2&&board[i][j-2]!=1&&board[i][j-2]!=2){   //如果下一个是箱子，且下下个不是墙，下下个不是箱子
				board[i][j-2]=2;
			}else if(board[i][j-1]==2&&(board[i][j-2]==1||board[i][j-2]==2)){
				break;
			}
			board[i][j-1]=4;
			destin(board,7,i,j);
			break;
			case KEY_ENTER:     //重置地图
			enter(board,7);
			break;
		}
	    mapprint(board,7);             //输入地图
		int num=0;
		vect(board,7,&num);
		if(num==1){
			break;
		}
		
	}

}

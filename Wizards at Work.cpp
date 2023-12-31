

#include<iostream>
#include<conio.h>	
#include<dos.h> 	
#include<windows.h>	
#include<time.h>	

#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70 

using namespace std; 

 
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); 
COORD CursorPosition; 

int oppoY[3];
int oppoX[3];
int oppo[3];
char car[4][4] = { ' ', '^','^',' ', 
					'0','�','�','0', 
					' ','|','|',' ',
					'0','�','�','0' }; 
					
int carPos = WIN_WIDTH/2; 
int score = 0; 

void gotoxy(int x, int y)
{
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}
void setcursor(bool visible, DWORD size)
 {
	if(size == 0)
		size = 20;	
	
	CONSOLE_CURSOR_INFO lpCursor;	
	lpCursor.bVisible = visible;  
	lpCursor.dwSize = size;   
	SetConsoleCursorInfo(console,&lpCursor); 
}
void drawBorder()
{  
	for(int i=0; i<SCREEN_HEIGHT; i++)
	{
		for(int j=0; j<17; j++)
		{
			gotoxy(0+j,i);
			 cout<<"=|";
			gotoxy(WIN_WIDTH-j,i); 
			 cout<<"|=";
		}
	} 

}
void genOppo(int ind)
{	
   oppoX[ind] = 18 + rand()%(33);  
}
void drawOppo(int ind)
{
	if( oppo[ind] == true )
	{
		gotoxy(oppoX[ind], oppoY[ind]);   cout<<"0==0";  
		gotoxy(oppoX[ind], oppoY[ind]+1); cout<<" == "; 
		gotoxy(oppoX[ind], oppoY[ind]+2); cout<<"0==0"; 
		gotoxy(oppoX[ind], oppoY[ind]+3); cout<<" ** ";  
	} 
}
void eraseOppo(int ind)
{
	if( oppo[ind] == true )
	{
		gotoxy(oppoX[ind], oppoY[ind]);   cout<<"    ";  
		gotoxy(oppoX[ind], oppoY[ind]+1); cout<<"    "; 
		gotoxy(oppoX[ind], oppoY[ind]+2); cout<<"    "; 
		gotoxy(oppoX[ind], oppoY[ind]+3); cout<<"    "; 
	} 
}
void resetOppo(int ind)
{
	eraseOppo(ind);
	oppoY[ind] = 1;
	genOppo(ind);
}

void drawCar()
{
	for(int i=0; i<4; i++)            					
	{
		for(int j=0; j<4; j++)      
	{
			gotoxy(j+carPos, i+22); 
			cout<<car[i][j];       
		}
	}
}
void eraseCar()
{
	for(int i=0; i<4; i++)
	{
		for(int j=0; j<4; j++) 
		{
			gotoxy(j+carPos, i+22); 
			cout<<" ";
		}
	}
}
 
int collision()
{
	if( oppoY[0]+4 >= 23 )
	{
		if( oppoX[0] + 4 - carPos >= 0 && oppoX[0] + 4 - carPos < 9  )
		{
			return 1;
		}
	}
	return 0;
} 
void gameover()
{
	system("cls");
	cout<<endl;
	cout<<"\t\t--------------------------"<<endl;
	cout<<"\t\t-------- Game Over -------"<<endl;
	cout<<"\t\t--------------------------"<<endl<<endl;
	cout<<"\t\tPress any key to go back to menu.";
	getch();
}
void updateScore()
{
	gotoxy(WIN_WIDTH + 7, 5); 
	cout<<"Score: "<<score<<endl;
}

void instructions(){
	
	system("cls");
	cout<<"Instructions";
	cout<<"\n----------------";
	cout<<"\n Avoid Cars by moving left or right. ";
	cout<<"\n\n Press 'a' to move left";
	cout<<"\n Press 'd' to move right";
	cout<<"\n Press 'escape' to exit";
	cout<<"\n\nPress any key to go back to menu";
	getch();
}

void play()
{
	carPos = -1 + WIN_WIDTH/2;
	score = 0;
	oppo[0] = 1; 
	oppo[1] = 0; 
	oppoY[0] = oppoY[1] = 1; 
	  
	system("cls"); 
	drawBorder();  
	updateScore(); 
	genOppo(0); 
	genOppo(1); 
	
	gotoxy(WIN_WIDTH + 3, 2);cout<<"Car Racing Game";
	gotoxy(WIN_WIDTH + 6, 4);cout<<"----------";
	gotoxy(WIN_WIDTH + 6, 6);cout<<"----------";
	gotoxy(WIN_WIDTH + 7, 12);cout<<"Control ";
	gotoxy(WIN_WIDTH + 7, 13);cout<<"-------- ";
	gotoxy(WIN_WIDTH + 2, 14);cout<<" A Key - Left";
	gotoxy(WIN_WIDTH + 2, 15);cout<<" D Key - Right"; 
	
	gotoxy(22, 5);cout<<"Press any key to start";
	getch();
	gotoxy(22, 5);cout<<"                      ";
	
	while(1)
	{
		if(kbhit())   
		{
			char ch = getch();
			if( ch=='a' || ch=='A' )
			{
				if( carPos > 18 )   
					carPos -= 4;
			}
			if( ch=='d' || ch=='D' )
			{
				if( carPos < 50 )  
					carPos += 4;                                   
			} 
			if(ch==27) 
			{
				break;
			}
		} 
		
		drawCar(); 
		drawOppo(0); 
		drawOppo(1); 
		if( collision() == 1  )
		{
			gameover();
			return;
		} 
		Sleep(40); 
		eraseCar(); 
		eraseOppo(0); 
		eraseOppo(1);   
		
		if( oppoY[0] == 10 )
			if( oppo[1] == 0 ) 
				oppo[1] = 1;
		
		if( oppo[0] == 1 )
			oppoY[0] += 1;
		
		if( oppo[1] == 1 )
			oppoY[1] += 1;
		 
		if( oppoY[0] > SCREEN_HEIGHT-4 )
		{
			resetOppo(0);
			score++;
			updateScore();
		}
		if( oppoY[1] > SCREEN_HEIGHT-4 )
		{
			resetOppo(1);
			score++;
			updateScore();
		}
	}
}

int main()
{
	system("color  F1");
	
	setcursor(0,0); 
	srand(time(0)); 
	 
	do{
		system("cls");
		gotoxy(10,5); cout<<" -------------------------- "; 
		gotoxy(10,6); cout<<" |     Car Racing Game    | "; 
		gotoxy(10,7); cout<<" -------------------------- ";
		gotoxy(10,9); cout<<"1. Start Game";
		gotoxy(10,10); cout<<"2. Instructions";	 
		gotoxy(10,11); cout<<"3. Quit";
		gotoxy(10,13); cout<<"Select option: ";
		char option = getche();
		
		if( option=='1') play();
		else if( option=='2') instructions();
		else if( option=='3') exit(0);
		
	}while(1);
	
	return 0;
}

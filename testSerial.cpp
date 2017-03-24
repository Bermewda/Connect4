//#include <tchar.h>
#include "SerialClass.h"	// Library described above
//#include <string>
#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<time.h>
#include<stdlib.h>
int c=3; //connect4
int v=14;   //player1
int s=13;   //player2

void gotoxy(int x, int y);
void setcursor(bool visible);
void setcolor(int fg,int bg);
char cursor(int x, int y);

void howto();
void home();
void table();
void player1_win();
void player2_win();
void win();
void lose();

void draw_choose1(int x, int y);
void draw_choose2(int x, int y);
void draw_coin1(int x, int y);
void draw_coin2(int x, int y);
void score1(int x);
void score2(int x);
void scorecom(int x);
void scoreplayer (int x);
void computer();
void playerplay();
void computerplay();
void player();
void player1();
void player2();

void check_coin1(int i, int j);
void check_coin2(int i, int j);
void check_coin3(int i, int j);
void check_coin4(int i, int j);
void check_vertical1(int i,int j);
void check_horizon1(int i,int j);
void check_diagonal1(int i,int j);
void check_vertical2(int i,int j);
void check_horizon2(int i,int j);
void check_diagonal2(int i,int j);
void check_vertical3(int i,int j);
void check_horizon3(int i,int j);
void check_diagonal3(int i,int j);
void check_vertical4(int i,int j);
void check_horizon4(int i,int j);
void check_diagonal4(int i,int j);
void clear();

int point1=0,point2=0;
int vs=0;
int row1=1,row2=1;
char ch='.';
char status='.';
int x,y;
int a,b;
int yrow[6]={21,18,15,12,9,6};
int xcolumn[7]={26,30,34,38,42,46,50};
int i1=0,i2=0,i3=0,i4=0,i5=0,i6=0,i7=0;
int	check1=0, check5=0,	check2=0, check6=0,	check3=0, check7=0,	check4=0, check8=0;

Serial* SP = new Serial(L"\\\\.\\COM20");    // adjust as needed
char incomingData[256] = "";			// don't forget to pre-allocate memory
int dataLength = 255;
int readResult = 0;
// application reads from the specified serial port and reports the collected data
int main()
{
	clear();
	setcursor(0);
	setcolor(0,0);
	int i=30,play=0,u=1;
	home();
	while(incomingData[0]!='7'|| SP->IsConnected())
	{	readResult = SP->ReadData(incomingData,dataLength);
	    incomingData[readResult] = 0;
		if(incomingData[0]=='7'){Beep(500,50);exit(0);}
		else if(incomingData[0]=='1' && u>0){Beep(700,50);u--;}
		else if(incomingData[0]=='2' && u<3){Beep(700,50);u++;}
		if(u==1)
			{	
			gotoxy(i,15);setcolor(0,15); printf("1 PLAYER");
			gotoxy(i+15,15);setcolor(15,0);printf("2 PLAYER");
			if(incomingData[0]=='3'){Beep(2000,50);play=1;}
			}	
		else if(u==2)
			{
			gotoxy(i,15);setcolor(15,0); printf("1 PLAYER");
			gotoxy(i+15,15);setcolor(0,15);printf("2 PLAYER");setcolor(15,0);
			if(incomingData[0]=='3'){Beep(2000,50);play=2;}
			}	
	if(play==1){Sleep(50);system("cls");howto();Sleep(5000);system("cls");computer();}
	else if(play==2){Sleep(50);system("cls");howto();Sleep(5000);system("cls");player();}
	}
	
}
void computer()
{
	clear();
	table();
	scoreplayer(point1);	
	scorecom(point2);
	x=21,y=2;
	draw_choose1(x,y);

			while(SP->IsConnected() && point1!=3 || point2!=3)
		{
		readResult = SP->ReadData(incomingData,dataLength);
	      incomingData[readResult] = 0;
		
		if(vs==0)
		{
			
			playerplay();	
		}
		else if(vs==1)
		{	
			
			computerplay();	
		}
		if(point1==3)	{Sleep(50);system("cls");point1=0; point2=0;win();}
		else if(point2==3)	{Sleep(50);system("cls");point1=0; point2=0;lose();}
		}	
	
	
			
}
void player()
{	
	clear();
	table();
	score1(point1);
	score2(point2);
	x=21,y=2;
	a=21,b=3;
	draw_choose1(x,y);
	draw_choose2(a,b);
			while(SP->IsConnected())
		{
		readResult = SP->ReadData(incomingData,dataLength);
	      incomingData[readResult] = 0;

		if(vs==0)
		{
			player1();
			
		}	
		else if(vs==1)
		{
			player2();	
		}

		if(point1==3)	{Sleep(50);system("cls");point1=0; point2=0;player1_win();}
		else if(point2==3)	{Sleep(50);system("cls");point1=0; point2=0;player2_win();}	
		}
	
				
}
void playerplay()
{
			if(incomingData[0]=='7')exit(0);
		   else if(incomingData[0]=='1' && x>=24) {Beep(700,50);scoreplayer(point1);scorecom(point2);for(int i=0;i<4;i++)draw_choose1(--x,y);if(row1>1)row1--;}
		   else if(incomingData[0]=='2' && x<=44) {Beep(700,50);scoreplayer(point1);scorecom(point2);for(int i=0;i<4;i++)draw_choose1(++x,y);if(row1<7)row1++;}
		   else if(incomingData[0]=='3') {Beep(2000,50);scoreplayer(point1);scorecom(point2);draw_choose1(x,y);status='S';}
	
	if(status=='S')
		{
			switch(row1)
			{
		
			case 1 : if(cursor(xcolumn[0],yrow[i1])!='O' && cursor(xcolumn[0],yrow[i1])!='X' && i1<6) 
			{draw_coin1(xcolumn[0],yrow[i1]); check_coin3(0,i1); i1++; status='.';vs++;}break;
			
			case 2 : if(cursor(xcolumn[1],yrow[i2])!='O' && cursor(xcolumn[1],yrow[i2])!='X' && i2<6) 
			{draw_coin1(xcolumn[1],yrow[i2]); check_coin3(1,i2); i2++; status='.';vs++;} break;
			
			case 3 : if(cursor(xcolumn[2],yrow[i3])!='O' && cursor(xcolumn[2],yrow[i3])!='X' && i3<6) 
			{draw_coin1(xcolumn[2],yrow[i3]); check_coin3(2,i3); i3++; status='.';vs++;} break;
			
			case 4 : if(cursor(xcolumn[3],yrow[i4])!='O' && cursor(xcolumn[3],yrow[i4])!='X' && i4<6) 
			{draw_coin1(xcolumn[3],yrow[i4]); check_coin3(3,i4); i4++; status='.';vs++;} break;
			
			case 5 : if(cursor(xcolumn[4],yrow[i5])!='O' && cursor(xcolumn[4],yrow[i5])!='X' && i5<6) 
			{draw_coin1(xcolumn[4],yrow[i5]); check_coin3(4,i5); i5++; status='.';vs++;} break;
			
			case 6 : if(cursor(xcolumn[5],yrow[i6])!='O' && cursor(xcolumn[5],yrow[i6])!='X' && i6<6) 
			{draw_coin1(xcolumn[5],yrow[i6]); check_coin3(5,i6); i6++; status='.';vs++;} break;
			
			case 7 : if(cursor(xcolumn[6],yrow[i7])!='O' && cursor(xcolumn[6],yrow[i7])!='X' && i7<6) 
			{draw_coin1(xcolumn[6],yrow[i7]); check_coin3(6,i7); i7++; status='.';vs++;} break;
			
			}
			if(i1==6 && i2==6 && i3==6 && i4==6 && i5==6 && i6==6 && i7==6)
			{
				Sleep(50);system("cls");computer();
			}
		
		}
		

}

int com;
void computerplay()
{
		
		for(int i=1;i<7;i++)
		{
			for(int j=0;j<6;j++)
			{
			if(cursor(xcolumn[i],yrow[j])=='O')
			{
				srand(time(NULL));
				com = (rand()%(i))+1;
			}
			continue;
			}
		}
	
		switch(com+1)
		{		
		case 1 : if(cursor(xcolumn[0],yrow[i1])!='O' && cursor(xcolumn[0],yrow[i1])!='X' && i1<6) 
		{draw_coin2(xcolumn[0],yrow[i1]); check_coin4(0,i1); i1++; status='.';vs--;} break;
			
		case 2 : if(cursor(xcolumn[1],yrow[i2])!='O' && cursor(xcolumn[1],yrow[i2])!='X' && i2<6) 
		{draw_coin2(xcolumn[1],yrow[i2]); check_coin4(1,i2); i2++; status='.';vs--;} break;
			
		case 3 : if(cursor(xcolumn[2],yrow[i3])!='O' && cursor(xcolumn[2],yrow[i3])!='X' && i3<6) 
		{draw_coin2(xcolumn[2],yrow[i3]); check_coin4(2,i3); i3++; status='.';vs--;} break;
		
		case 4 : if(cursor(xcolumn[3],yrow[i4])!='O' && cursor(xcolumn[3],yrow[i4])!='X' && i4<6) 
		{draw_coin2(xcolumn[3],yrow[i4]); check_coin4(3,i4); i4++; status='.';vs--;} break;
		
		case 5 : if(cursor(xcolumn[4],yrow[i5])!='O' && cursor(xcolumn[4],yrow[i5])!='X' && i5<6) 
		{draw_coin2(xcolumn[4],yrow[i5]); check_coin4(4,i5); i5++; status='.';vs--;} break;
		
		case 6 : if(cursor(xcolumn[5],yrow[i6])!='O' && cursor(xcolumn[5],yrow[i6])!='X' && i6<6) 
		{draw_coin2(xcolumn[5],yrow[i6]); check_coin4(5,i6); i6++; status='.';vs--;} break;
		
		case 7 : if(cursor(xcolumn[6],yrow[i7])!='O' && cursor(xcolumn[6],yrow[i7])!='X' && i7<6) 
		{draw_coin2(xcolumn[6],yrow[i7]); check_coin4(6,i7); i7++; status='.';vs--;} break;
		
		}
	

	
		if(i1==6 && i2==6 && i3==6 && i4==6 && i5==6 && i6==6 && i7==6)
			{
				Sleep(50);system("cls");computer();
			}
		
		
}
void player1()
{
			if(incomingData[0]=='7')exit(0);	
		   else if(incomingData[0]=='1' && x>=24) {Beep(700,50);score1(point1);score2(point2);for(int i=0;i<4;i++)draw_choose1(--x,y);if(row1>1)row1--;}
		   else if(incomingData[0]=='2'&& x<=44) {Beep(700,50);score1(point1);score2(point2);for(int i=0;i<4;i++)draw_choose1(++x,y);if(row1<7)row1++;}
		   else if(incomingData[0]=='3') {Beep(2000,50);score1(point1);score2(point2);draw_choose1(x,y);status='S';}
		 
	if(status=='S')
		{
			switch(row1)
			{
		
			case 1 : if(cursor(xcolumn[0],yrow[i1])!='O' && cursor(xcolumn[0],yrow[i1])!='X') 
			{draw_coin1(xcolumn[0],yrow[i1]); check_coin1(0,i1); i1++; status='.';vs++;}break;
			
			case 2 : if(cursor(xcolumn[1],yrow[i2])!='O' && cursor(xcolumn[1],yrow[i2])!='X') 
			{draw_coin1(xcolumn[1],yrow[i2]); check_coin1(1,i2); i2++; status='.';vs++;} break;
			
			case 3 : if(cursor(xcolumn[2],yrow[i3])!='O' && cursor(xcolumn[2],yrow[i3])!='X') 
			{draw_coin1(xcolumn[2],yrow[i3]); check_coin1(2,i3); i3++; status='.';vs++;} break;
			
			case 4 : if(cursor(xcolumn[3],yrow[i4])!='O' && cursor(xcolumn[3],yrow[i4])!='X') 
			{draw_coin1(xcolumn[3],yrow[i4]); check_coin1(3,i4); i4++; status='.';vs++;} break;
			
			case 5 : if(cursor(xcolumn[4],yrow[i5])!='O' && cursor(xcolumn[4],yrow[i5])!='X') 
			{draw_coin1(xcolumn[4],yrow[i5]); check_coin1(4,i5); i5++; status='.';vs++;} break;
			
			case 6 : if(cursor(xcolumn[5],yrow[i6])!='O' && cursor(xcolumn[5],yrow[i6])!='X') 
			{draw_coin1(xcolumn[5],yrow[i6]); check_coin1(5,i6); i6++; status='.';vs++;} break;
			
			case 7 : if(cursor(xcolumn[6],yrow[i7])!='O' && cursor(xcolumn[6],yrow[i7])!='X') 
			{draw_coin1(xcolumn[6],yrow[i7]); check_coin1(6,i7); i7++; status='.';vs++;} break;
			
			}
			if(i1==6 && i2==6 && i3==6 && i4==6 && i5==6 && i6==6 && i7==6)
			{
				Sleep(50);system("cls");player();
			}	
		}
}
void player2()
{	
			if(incomingData[0]=='7')exit(0);	
		   else if(incomingData[0]=='4' && a>=24) {Beep(700,50);score1(point1);score2(point2);for(int i=0;i<4;i++)draw_choose2(--a,b);if(row2>1)row2--;}
		   else if(incomingData[0]=='5' && a<=44) {Beep(700,50);score1(point1);score2(point2);for(int i=0;i<4;i++)draw_choose2(++a,b);if(row2<7)row2++;}
		   else if(incomingData[0]=='6') {Beep(2000,50);score1(point1);score2(point2);draw_choose2(a,b);status='K';}
		
	if(status=='K')
		{
			switch(row2)
			{
				
			case 1 : if(cursor(xcolumn[0],yrow[i1])!='O' && cursor(xcolumn[0],yrow[i1])!='X') 
			{draw_coin2(xcolumn[0],yrow[i1]); check_coin2(0,i1); i1++; status='.';vs--;} break;
			
			case 2 : if(cursor(xcolumn[1],yrow[i2])!='O' && cursor(xcolumn[1],yrow[i2])!='X') 
			{draw_coin2(xcolumn[1],yrow[i2]); check_coin2(1,i2); i2++; status='.';vs--;} break;
			
			case 3 : if(cursor(xcolumn[2],yrow[i3])!='O' && cursor(xcolumn[2],yrow[i3])!='X') 
			{draw_coin2(xcolumn[2],yrow[i3]); check_coin2(2,i3); i3++; status='.';vs--;} break;
			
			case 4 : if(cursor(xcolumn[3],yrow[i4])!='O' && cursor(xcolumn[3],yrow[i4])!='X') 
			{draw_coin2(xcolumn[3],yrow[i4]); check_coin2(3,i4); i4++; status='.';vs--;} break;
			
			case 5 : if(cursor(xcolumn[4],yrow[i5])!='O' && cursor(xcolumn[4],yrow[i5])!='X') 
			{draw_coin2(xcolumn[4],yrow[i5]); check_coin2(4,i5); i5++; status='.';vs--;} break;
			
			case 6 : if(cursor(xcolumn[5],yrow[i6])!='O' && cursor(xcolumn[5],yrow[i6])!='X') 
			{draw_coin2(xcolumn[5],yrow[i6]); check_coin2(5,i6); i6++; status='.';vs--;} break;
			
			case 7 : if(cursor(xcolumn[6],yrow[i7])!='O' && cursor(xcolumn[6],yrow[i7])!='X') 
			{draw_coin2(xcolumn[6],yrow[i7]); check_coin2(6,i7); i7++; status='.';vs--;} break;
			
			}
			if(i1==6 && i2==6 && i3==6 && i4==6 && i5==6 && i6==6 && i7==6)
			{
				Sleep(50);system("cls");player();
			}	
		}
	
}
void check_coin1(int i, int j)
{
	check_vertical1(i,j);
	check_horizon1(i,j);
	check_diagonal1(i,j);
}
void check_coin2(int i, int j)
{
	check_vertical2(i,j);
	check_horizon2(i,j);
	check_diagonal2(i,j);
}
void check_coin3(int i, int j)
{
	check_vertical3(i,j);
	check_horizon3(i,j);
	check_diagonal3(i,j);
}
void check_coin4(int i, int j)
{
	check_vertical4(i,j);
	check_horizon4(i,j);
	check_diagonal4(i,j);
}
void check_vertical1(int i,int j)
{
	int check1=0;
	for(int a=j;a>=0;a--){if(cursor(xcolumn[i],yrow[a])=='O' && check1<4)check1++;else break;}
	//check
	if(check1==4)
	{Sleep(1000);system("cls");vs=1;point1++;player();}
//	gotoxy(1,1); printf("%d",check1);
	
}
void check_horizon1(int i,int j)
{
	int check2=0;
	for(int b=i;b>=0;b--){if(cursor(xcolumn[b],yrow[j])=='O' && check2<4)check2++;else break;}
	for(int b=i+1;b<7;b++){if(cursor(xcolumn[b],yrow[j])=='O' && check2<4)check2++;else break;}
	//check
	if(check2==4)
	{Sleep(1000);system("cls");vs=1;point1++;player();}
//	gotoxy(1,2); printf("%d",check2);
		
}
void check_diagonal1(int i,int j)
{
	int check3=0;
	int check4=0;
	//right 
	for(int a=0;a<=j;a++)
	{	if(cursor(xcolumn[i-a],yrow[j-a])=='O'&& check3<4)check3++;else break;}
	for(int a=1;i+a<6;a++)
	{	if(cursor(xcolumn[i+a],yrow[j+a])=='O'&& check3<4)check3++;else break;}

	//left
	for(int b=j;b>=0;b--)
	{	if(cursor(xcolumn[i+b],yrow[j-b])=='O'&& check4<4)check4++;else break;}
	for(int b=1;j+b<7;b++)
	{	if(cursor(xcolumn[i-b],yrow[j+b])=='O'&& check4<4)check4++;else break;}
	
	//check
	if(check3==4)
	{Sleep(1000);system("cls");vs=1;point1++;player();}
	else if(check4==4)
	{Sleep(1000);system("cls");vs=1;point1++;player();}
//	gotoxy(1,3); printf("%d",check3);
//	gotoxy(1,4); printf("%d",check4);
}
void check_vertical2(int i,int j)
{
	int check5=0;
	for(int a=j;a>=0;a--){if(cursor(xcolumn[i],yrow[a])=='X' && check5<4)check5++;else break;}
	//check
	if(check5==4)
	{Sleep(1000);system("cls");vs=0;point2++;player();}
//	gotoxy(1,5); printf("%d",check5);

		
}
void check_horizon2(int i,int j)
{
	int check6=0;
	for(int b=i;b>=0;b--){if(cursor(xcolumn[b],yrow[j])=='X' && check6<4)check6++;else break;}
	for(int b=i+1;b<7;b++){if(cursor(xcolumn[b],yrow[j])=='X' && check6<4)check6++;else break;}
	//check
	if(check6==4)
	{Sleep(1000);system("cls");vs=0;point2++;player();}
//	gotoxy(1,6); printf("%d",check6);
	
}
void check_diagonal2(int i,int j)
{
	int check7=0;
	int check8=0;
	//right 
	for(int a=0;a<=j;a++)
	{	if(cursor(xcolumn[i-a],yrow[j-a])=='X'&& check7<4)check7++;else break;}
	for(int a=1;i+a<6;a++)
	{	if(cursor(xcolumn[i+a],yrow[j+a])=='X'&& check7<4)check7++;else break;}


	//left
	for(int b=j;b>=0;b--)
	{	if(cursor(xcolumn[i+b],yrow[j-b])=='X'&& check8<4)check8++;else break;}
	for(int b=1;j+b<7;b++)
	{	if(cursor(xcolumn[i-b],yrow[j+b])=='X'&& check8<4)check8++;else break;}

	//check
	if(check7==4)
	{Sleep(1000);system("cls");vs=0;point2++;player();}

	//check
	else if(check8==4)
	{Sleep(1000);system("cls");vs=0;point2++;player();}
//	gotoxy(1,7); printf("%d",check7);
//	gotoxy(1,8); printf("%d",check8);

}
void check_vertical3(int i,int j)
{
	int check1=0;
	for(int a=j;a>=0;a--){if(cursor(xcolumn[i],yrow[a])=='O' && check1<4)check1++;else break;}
	//check
	if(check1==4)
	{Sleep(1000);system("cls");vs=1;point1++;computer();}
	//gotoxy(1,1); printf("%d",check1);
}
void check_horizon3(int i,int j)
{
	int check2=0;
	for(int b=i;b>=0;b--){if(cursor(xcolumn[b],yrow[j])=='O' && check2<4)check2++;else break;}
	for(int b=i+1;b<7;b++){if(cursor(xcolumn[b],yrow[j])=='O' && check2<4)check2++;else break;}
	//check
	if(check2==4)
	{Sleep(1000);system("cls");vs=1;point1++;computer();}
	//gotoxy(1,2); printf("%d",check2);
		
}
void check_diagonal3(int i,int j)
{
	int check3=0;
	int check4=0;
	//right 
	for(int a=0;a<=j;a++)
	{	if(cursor(xcolumn[i-a],yrow[j-a])=='O'&& check3<4)check3++;else break;}
	for(int a=1;i+a<6;a++)
	{	if(cursor(xcolumn[i+a],yrow[j+a])=='O'&& check3<4)check3++;else break;}

	//left
	for(int b=j;b>=0;b--)
	{	if(cursor(xcolumn[i+b],yrow[j-b])=='O'&& check4<4)check4++;else break;}
	for(int b=1;j+b<7;b++)
	{	if(cursor(xcolumn[i-b],yrow[j+b])=='O'&& check4<4)check4++;else break;}
	
	//check
	if(check3==4)
	{Sleep(1000);system("cls");vs=1;point1++;computer();}
	else if(check4==4)
	{Sleep(1000);system("cls");vs=1;point1++;computer();}
	/*gotoxy(1,3); printf("%d",check3);
	gotoxy(1,4); printf("%d",check4);*/
}
void check_vertical4(int i,int j)
{
	int check5=0;
	for(int a=j;a>=0;a--){if(cursor(xcolumn[i],yrow[a])=='X' && check5<4)check5++;else break;}
	//check
	if(check5==4)
	{Sleep(1000);system("cls");vs=0;point2++;computer();}
	//gotoxy(1,5); printf("%d",check5);

		
}
void check_horizon4(int i,int j)
{
	int check6=0;
	for(int b=i;b>=0;b--){if(cursor(xcolumn[b],yrow[j])=='X' && check6<4)check6++;else break;}
	for(int b=i+1;b<7;b++){if(cursor(xcolumn[b],yrow[j])=='X' && check6<4)check6++;else break;}
	//check
	if(check6==4)
	{Sleep(1000);system("cls");vs=0;point2++;computer();}
	//gotoxy(1,6); printf("%d",check6);
	
}
void check_diagonal4(int i,int j)
{
	int check7=0;
	int check8=0;
	//right 
	for(int a=0;a<=j;a++)
	{	if(cursor(xcolumn[i-a],yrow[j-a])=='X'&& check7<4)check7++;else break;}
	for(int a=1;i+a<6;a++)
	{	if(cursor(xcolumn[i+a],yrow[j+a])=='X'&& check7<4)check7++;else break;}


	//left
	for(int b=j;b>=0;b--)
	{	if(cursor(xcolumn[i+b],yrow[j-b])=='X'&& check8<4)check8++;else break;}
	for(int b=1;j+b<7;b++)
	{	if(cursor(xcolumn[i-b],yrow[j+b])=='X'&& check8<4)check8++;else break;}

	//check
	if(check7==4)
	{Sleep(1000);system("cls");vs=0;point2++;computer();}

	//check
	else if(check8==4)
	{Sleep(1000);system("cls");vs=0;point2++;computer();}
	/*gotoxy(1,7); printf("%d",check7);
	gotoxy(1,8); printf("%d",check8);*/

}
void clear()
{
	check1=0; check5=0;
	check2=0; check6=0;
	check3=0; check7=0;
	check4=0; check8=0;	
	i1=0; i5=0;
	i2=0; i6=0;
	i3=0; i7=0;
	i4=0;
	row1=1; row2=1;
	int u=1;
}
void home()
{
	//connect4
printf("\n\n\n");
setcolor(0,0); printf("   ");setcolor(c,c); printf("_______");setcolor(0,0); printf("  ");setcolor(c,c); printf("_______");setcolor(0,0); printf("  ");setcolor(c,c); printf("___");setcolor(0,0); printf("   ");setcolor(c,c); printf("__");setcolor(0,0); printf("  ");setcolor(c,c); printf("___");setcolor(0,0); printf("   ");setcolor(c,c); printf("__");setcolor(0,0); printf("  ");setcolor(c,c); printf("_______");setcolor(0,0); printf("  ");setcolor(c,c); printf("_______");setcolor(0,0); printf("  ");setcolor(c,c); printf("________");setcolor(0,0); printf("  ");setcolor(c,c); printf("__");setcolor(0,0); printf("    ");setcolor(c,c); printf("__\n"); 
setcolor(0,0); printf("   ");setcolor(c,c); printf("__");setcolor(0,0); printf("       ");setcolor(c,c); printf("__");setcolor(0,0); printf("   ");setcolor(c,c); printf("__");setcolor(0,0); printf("  ");setcolor(c,c); printf("____");setcolor(0,0); printf("  ");setcolor(c,c); printf("__");setcolor(0,0); printf("  ");setcolor(c,c); printf("____");setcolor(0,0); printf("  ");setcolor(c,c); printf("__");setcolor(0,0); printf("  ");setcolor(c,c); printf("__");setcolor(0,0); printf("       ");setcolor(c,c); printf("__");setcolor(0,0); printf("          ");setcolor(c,c); printf("__");setcolor(0,0); printf("     ");setcolor(c,c); printf("__");setcolor(0,0); printf("    ");setcolor(c,c); printf("__\n");
setcolor(0,0); printf("   ");setcolor(c,c); printf("__");setcolor(0,0); printf("       ");setcolor(c,c); printf("__");setcolor(0,0); printf("   ");setcolor(c,c); printf("__");setcolor(0,0); printf("  ");setcolor(c,c); printf("__");setcolor(0,0); printf(" ");setcolor(c,c); printf("__");setcolor(0,0); printf(" ");setcolor(c,c); printf("__");setcolor(0,0); printf("  ");setcolor(c,c); printf("__");setcolor(0,0); printf(" ");setcolor(c,c); printf("__");setcolor(0,0); printf(" ");setcolor(c,c); printf("__");setcolor(0,0); printf("  ");setcolor(c,c); printf("____");setcolor(0,0); printf("     ");setcolor(c,c); printf("__");setcolor(0,0); printf("          ");setcolor(c,c); printf("__");setcolor(0,0); printf("     ");setcolor(c,c); printf("________\n");
setcolor(0,0); printf("   ");setcolor(c,c); printf("__");setcolor(0,0); printf("       ");setcolor(c,c); printf("__");setcolor(0,0); printf("   ");setcolor(c,c); printf("__");setcolor(0,0); printf("  ");setcolor(c,c); printf("__");setcolor(0,0); printf("  ");setcolor(c,c); printf("____");setcolor(0,0); printf("  ");setcolor(c,c); printf("__");setcolor(0,0); printf("  ");setcolor(c,c); printf("____");setcolor(0,0); printf("  ");setcolor(c,c); printf("__");setcolor(0,0); printf("       ");setcolor(c,c); printf("__");setcolor(0,0); printf("          ");setcolor(c,c); printf("__");setcolor(0,0); printf("           ");setcolor(c,c); printf("__\n");
setcolor(0,0); printf("   ");setcolor(c,c); printf("_______");setcolor(0,0); printf("  ");setcolor(c,c); printf("_______");setcolor(0,0); printf("  ");setcolor(c,c); printf("__");setcolor(0,0); printf("   ");setcolor(c,c); printf("___");setcolor(0,0); printf("  ");setcolor(c,c); printf("__");setcolor(0,0); printf("   ");setcolor(c,c); printf("___");setcolor(0,0); printf("  ");setcolor(c,c); printf("_______");setcolor(0,0); printf("  ");setcolor(c,c); printf("_______");setcolor(0,0); printf("     ");setcolor(c,c); printf("__");setcolor(0,0); printf("           ");setcolor(c,c); printf("__\n\n\n");
setcolor(15,0);             
printf("................................................................................\n\n");
int i=30;
	gotoxy(i,15);setcolor(0,15); printf("1 PLAYER");
	gotoxy(i+15,15);setcolor(15,0);printf("2 PLAYER");
gotoxy(1,26);setcolor(15,3); printf("\t\t\t\t\t\t\t\t    Exit : Red ");setcolor(0,0);
	
}
void table()
{
	int i=24;
setcolor(15,0);
gotoxy(i+1,4);printf("___ ___ ___ ___ ___ ___ ___ ");
gotoxy(i,5);printf("|   |   |   |   |   |   |   |");
gotoxy(i,6);printf("|   |   |   |   |   |   |   |");
gotoxy(i,7);printf("|___|___|___|___|___|___|___|");
gotoxy(i,8);printf("|   |   |   |   |   |   |   |");
gotoxy(i,9);printf("|   |   |   |   |   |   |   |");
gotoxy(i,10);printf("|___|___|___|___|___|___|___|");
gotoxy(i,11);printf("|   |   |   |   |   |   |   |");
gotoxy(i,12);printf("|   |   |   |   |   |   |   |");
gotoxy(i,13);printf("|___|___|___|___|___|___|___|");
gotoxy(i,14);printf("|   |   |   |   |   |   |   |");
gotoxy(i,15);printf("|   |   |   |   |   |   |   |");
gotoxy(i,16);printf("|___|___|___|___|___|___|___|");
gotoxy(i,17);printf("|   |   |   |   |   |   |   |");
gotoxy(i,18);printf("|   |   |   |   |   |   |   |");
gotoxy(i,19);printf("|___|___|___|___|___|___|___|");
gotoxy(i,20);printf("|   |   |   |   |   |   |   |");
gotoxy(i,21);printf("|   |   |   |   |   |   |   |");
gotoxy(i,22);printf("|___|___|___|___|___|___|___|");		
gotoxy(1,26);setcolor(15,3); printf("\t\t\t\t\t\t\t\t    Exit : Red ");setcolor(0,0);
}
void gotoxy(int x, int y)
{
	COORD c = {x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}
void setcursor(bool visible)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console,&lpCursor);
}
void setcolor(int fg,int bg)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole,bg*16+fg);
}
char cursor(int x, int y)
{
	HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
	char buf[2]; COORD c = {x,y}; DWORD num_read;
	if(!ReadConsoleOutputCharacter(hStd,(LPTSTR)buf,1,c,(LPDWORD)&num_read))
	return '\0';
	else return buf[0];
}
void draw_choose1(int x, int y)
{
	gotoxy(x,y);
	setcolor(0,0); printf("    ");
	setcolor(v,v); printf("   ");
	setcolor(0,0); printf("    ");
}
void draw_choose2(int x, int y)
{
	gotoxy(x,y);
	setcolor(0,0); printf("    ");
	setcolor(s,s); printf("   ");	
	setcolor(0,0); printf("    ");
}
void draw_coin1(int x, int y)
{	
gotoxy(x,y);setcolor(v,0);	
printf("O");}
void draw_coin2(int x, int y)
{	
gotoxy(x,y);setcolor(s,0);	
printf("X");}
void score1(int x)
{
    gotoxy(1,23);
	setcolor(14,0);
    printf("PLAYER 1 = %d",x);
}
void score2(int x)
{
    gotoxy(65,23);
	setcolor(13,0);
    printf("PLAYER 2 = %d",x);
}
void scoreplayer(int x)
{
    gotoxy(1,23);
	setcolor(14,0);
    printf("PLAYER = %d",x);
}
void scorecom(int x)
{
    gotoxy(65,23);
	setcolor(13,0);
    printf("COMPUTER = %d",x);
}
void player1_win()
{	
  //  player
printf("\n\n");
setcolor(0,0); printf("\t     ");setcolor(v,v); printf("_______");setcolor(0,0); printf("  ");setcolor(v,v); printf("__");setcolor(0,0); printf("    ");setcolor(v,v); printf("_______");setcolor(0,0); printf("  ");setcolor(v,v); printf("__");setcolor(0,0); printf("    ");setcolor(v,v); printf("__");setcolor(0,0); printf("  ");setcolor(v,v); printf("______");setcolor(0,0); printf("  ");setcolor(v,v); printf("_______");setcolor(0,0); printf("   ");setcolor(v,v); printf("__\n");         
setcolor(0,0); printf("\t     ");setcolor(v,v); printf("__");setcolor(0,0); printf("   ");setcolor(v,v); printf("__");setcolor(0,0); printf("  ");setcolor(v,v); printf("__");setcolor(0,0); printf("    ");setcolor(v,v); printf("__");setcolor(0,0); printf("   ");setcolor(v,v); printf("__");setcolor(0,0); printf("   ");setcolor(v,v); printf("__");setcolor(0,0); printf("  ");setcolor(v,v); printf("__");setcolor(0,0); printf("   ");setcolor(v,v); printf("__");setcolor(0,0); printf("      ");setcolor(v,v); printf("__");setcolor(0,0); printf("   ");setcolor(v,v); printf("__");setcolor(0,0); printf("   ");setcolor(v,v); printf("__\n");
setcolor(0,0); printf("\t     ");setcolor(v,v); printf("_______");setcolor(0,0); printf("  ");setcolor(v,v); printf("__");setcolor(0,0); printf("    ");setcolor(v,v); printf("_______");setcolor(0,0); printf("    ");setcolor(v,v); printf("____");setcolor(0,0); printf("    ");setcolor(v,v); printf("____");setcolor(0,0); printf("    ");setcolor(v,v); printf("_______");setcolor(0,0); printf("   ");setcolor(v,v); printf("__\n");
setcolor(0,0); printf("\t     ");setcolor(v,v); printf("__");setcolor(0,0); printf("       ");setcolor(v,v); printf("__");setcolor(0,0); printf("    ");setcolor(v,v); printf("__");setcolor(0,0); printf("   ");setcolor(v,v); printf("__");setcolor(0,0); printf("     ");setcolor(v,v); printf("__");setcolor(0,0); printf("     ");setcolor(v,v); printf("__");setcolor(0,0); printf("      ");setcolor(v,v); printf("__");setcolor(0,0); printf(" ");setcolor(v,v); printf("__");setcolor(0,0); printf("     ");setcolor(v,v); printf("__\n");
setcolor(0,0); printf("\t     ");setcolor(v,v); printf("__");setcolor(0,0); printf("       ");setcolor(v,v); printf("____");setcolor(0,0); printf("  ");setcolor(v,v); printf("__");setcolor(0,0); printf("   ");setcolor(v,v); printf("__");setcolor(0,0); printf("     ");setcolor(v,v); printf("__");setcolor(0,0); printf("     ");setcolor(v,v); printf("______");setcolor(0,0); printf("  ");setcolor(v,v); printf("__");setcolor(0,0); printf("  ");setcolor(v,v); printf("__");setcolor(0,0); printf("    ");setcolor(v,v); printf("__\n\n"); 


	// win!
setcolor(0,0); printf("\t\t\t");setcolor(12,12); printf("__");setcolor(0,0); printf("      ");setcolor(12,12); printf("__");setcolor(0,0); printf("  ");setcolor(12,12); printf("______");setcolor(0,0); printf("  ");setcolor(12,12); printf("___");setcolor(0,0); printf("    ");setcolor(12,12); printf("__");setcolor(0,0); printf("   ");setcolor(12,12); printf("__\n");
setcolor(0,0); printf("\t\t\t");setcolor(12,12); printf("__");setcolor(0,0); printf("      ");setcolor(12,12); printf("__");setcolor(0,0); printf("    ");setcolor(12,12); printf("__");setcolor(0,0); printf("    ");setcolor(12,12); printf("____");setcolor(0,0); printf("   ");setcolor(12,12); printf("__");setcolor(0,0); printf("   ");setcolor(12,12); printf("__\n");
setcolor(0,0); printf("\t\t\t");setcolor(12,12); printf("__");setcolor(0,0); printf("      ");setcolor(12,12); printf("__");setcolor(0,0); printf("    ");setcolor(12,12); printf("__");setcolor(0,0); printf("    ");setcolor(12,12); printf("__");setcolor(0,0); printf(" ");setcolor(12,12); printf("__");setcolor(0,0); printf("  ");setcolor(12,12); printf("__");setcolor(0,0); printf("   ");setcolor(12,12); printf("__\n");
setcolor(0,0); printf("\t\t\t");setcolor(12,12); printf("__");setcolor(0,0); printf("  ");setcolor(12,12); printf("__");setcolor(0,0); printf("  ");setcolor(12,12); printf("__");setcolor(0,0); printf("    ");setcolor(12,12); printf("__");setcolor(0,0); printf("    ");setcolor(12,12); printf("__");setcolor(0,0); printf("  ");setcolor(12,12); printf("__");setcolor(0,0); printf(" ");setcolor(12,12); printf("__");setcolor(0,0); printf("   ");setcolor(12,12); printf("__\n");
setcolor(0,0); printf("\t\t\t");setcolor(12,12); printf("__");setcolor(0,0); printf(" ");setcolor(12,12); printf("____");setcolor(0,0); printf(" ");setcolor(12,12); printf("__");setcolor(0,0); printf("    ");setcolor(12,12); printf("__");setcolor(0,0); printf("    ");setcolor(12,12); printf("__");setcolor(0,0); printf("   ");setcolor(12,12); printf("____");setcolor(0,0); printf("     \n");
setcolor(0,0); printf("\t\t\t");setcolor(0,0); printf(" ");setcolor(12,12); printf("___");setcolor(0,0); printf("  ");setcolor(12,12); printf("___");setcolor(0,0); printf("   ");setcolor(12,12); printf("______");setcolor(0,0); printf("  ");setcolor(12,12); printf("__");setcolor(0,0); printf("    ");setcolor(12,12); printf("___");setcolor(0,0); printf("   ");setcolor(12,12); printf("__\n\n");
setcolor(15,0);             
printf("................................................................................\n\n");
	int u=1,i=30,play=0;
	gotoxy(i,18);setcolor(0,15); printf("PLAY AGAIN?");
	gotoxy(i+15,18);setcolor(15,0);printf("BACK");
	gotoxy(1,26);setcolor(15,3); printf("\t\t\t\t\t\t\t\t    Exit : Red ");setcolor(0,0);
	while(SP->IsConnected())
	{
	readResult = SP->ReadData(incomingData,dataLength);
	incomingData[readResult] = 0;
	if(incomingData[0] =='7'){Beep(500,50);exit(0);}
	else if(incomingData[0] =='1' && u>0){Beep(700,50);u--;}	
	else if(incomingData[0] =='2' && u<3){Beep(700,50);u++;}
		if(u==1)
			{	
			gotoxy(i,18);setcolor(0,15); printf("PLAY AGAIN?");
			gotoxy(i+15,18);setcolor(15,0);printf("BACK");
			if(incomingData[0] =='3'){Beep(2000,50);play=1;}
			}	
		else if(u==2)
			{
			gotoxy(i,18);setcolor(15,0); printf("PLAY AGAIN?");
			gotoxy(i+15,18);setcolor(0,15);printf("BACK");setcolor(15,0);
			if(incomingData[0] =='3'){Beep(2000,50);play=2;}
			}
	if(play==1){Sleep(50);system("cls");player();}
	else if(play==2){Sleep(50);system("cls");main();} 	
	}
}
void player2_win()
{
	// player 2
printf("\n\n");
setcolor(0,0); printf("\t     ");setcolor(s,s); printf("_______");setcolor(0,0); printf("  ");setcolor(s,s); printf("__");setcolor(0,0); printf("    ");setcolor(s,s); printf("_______");setcolor(0,0); printf("  ");setcolor(s,s); printf("__");setcolor(0,0); printf("    ");setcolor(s,s); printf("__");setcolor(0,0); printf("  ");setcolor(s,s); printf("______");setcolor(0,0); printf("  ");setcolor(s,s); printf("_______");setcolor(0,0); printf("   ");setcolor(s,s); printf("______\n");
setcolor(0,0); printf("\t     ");setcolor(s,s); printf("__");setcolor(0,0); printf("   ");setcolor(s,s); printf("__");setcolor(0,0); printf("  ");setcolor(s,s); printf("__");setcolor(0,0); printf("    ");setcolor(s,s); printf("__");setcolor(0,0); printf("   ");setcolor(s,s); printf("__");setcolor(0,0); printf("   ");setcolor(s,s); printf("__");setcolor(0,0); printf("  ");setcolor(s,s); printf("__");setcolor(0,0); printf("   ");setcolor(s,s); printf("__");setcolor(0,0); printf("      ");setcolor(s,s); printf("__");setcolor(0,0); printf("   ");setcolor(s,s); printf("__");setcolor(0,0); printf("   ");setcolor(0,0); printf("    ");setcolor(s,s); printf("__\n");
setcolor(0,0); printf("\t     ");setcolor(s,s); printf("_______");setcolor(0,0); printf("  ");setcolor(s,s); printf("__");setcolor(0,0); printf("    ");setcolor(s,s); printf("_______");setcolor(0,0); printf("    ");setcolor(s,s); printf("____");setcolor(0,0); printf("    ");setcolor(s,s); printf("____");setcolor(0,0); printf("    ");setcolor(s,s); printf("_______");setcolor(0,0); printf("   ");setcolor(s,s); printf("______\n");
setcolor(0,0); printf("\t     ");setcolor(s,s); printf("__");setcolor(0,0); printf("       ");setcolor(s,s); printf("__");setcolor(0,0); printf("    ");setcolor(s,s); printf("__");setcolor(0,0); printf("   ");setcolor(s,s); printf("__");setcolor(0,0); printf("     ");setcolor(s,s); printf("__");setcolor(0,0); printf("     ");setcolor(s,s); printf("__");setcolor(0,0); printf("      ");setcolor(s,s); printf("__");setcolor(0,0); printf(" ");setcolor(s,s); printf("__");setcolor(0,0); printf("     ");setcolor(s,s); printf("__\n");
setcolor(0,0); printf("\t     ");setcolor(s,s); printf("__");setcolor(0,0); printf("       ");setcolor(s,s); printf("____");setcolor(0,0); printf("  ");setcolor(s,s); printf("__");setcolor(0,0); printf("   ");setcolor(s,s); printf("__");setcolor(0,0); printf("     ");setcolor(s,s); printf("__");setcolor(0,0); printf("     ");setcolor(s,s); printf("______");setcolor(0,0); printf("  ");setcolor(s,s); printf("__");setcolor(0,0); printf("  ");setcolor(s,s); printf("__");setcolor(0,0); printf("    ");setcolor(s,s); printf("______\n\n"); 

	// win!
setcolor(0,0); printf("\t\t\t");setcolor(12,12); printf("__");setcolor(0,0); printf("      ");setcolor(12,12); printf("__");setcolor(0,0); printf("  ");setcolor(12,12); printf("______");setcolor(0,0); printf("  ");setcolor(12,12); printf("___");setcolor(0,0); printf("    ");setcolor(12,12); printf("__");setcolor(0,0); printf("   ");setcolor(12,12); printf("__\n");
setcolor(0,0); printf("\t\t\t");setcolor(12,12); printf("__");setcolor(0,0); printf("      ");setcolor(12,12); printf("__");setcolor(0,0); printf("    ");setcolor(12,12); printf("__");setcolor(0,0); printf("    ");setcolor(12,12); printf("____");setcolor(0,0); printf("   ");setcolor(12,12); printf("__");setcolor(0,0); printf("   ");setcolor(12,12); printf("__\n");
setcolor(0,0); printf("\t\t\t");setcolor(12,12); printf("__");setcolor(0,0); printf("      ");setcolor(12,12); printf("__");setcolor(0,0); printf("    ");setcolor(12,12); printf("__");setcolor(0,0); printf("    ");setcolor(12,12); printf("__");setcolor(0,0); printf(" ");setcolor(12,12); printf("__");setcolor(0,0); printf("  ");setcolor(12,12); printf("__");setcolor(0,0); printf("   ");setcolor(12,12); printf("__\n");
setcolor(0,0); printf("\t\t\t");setcolor(12,12); printf("__");setcolor(0,0); printf("  ");setcolor(12,12); printf("__");setcolor(0,0); printf("  ");setcolor(12,12); printf("__");setcolor(0,0); printf("    ");setcolor(12,12); printf("__");setcolor(0,0); printf("    ");setcolor(12,12); printf("__");setcolor(0,0); printf("  ");setcolor(12,12); printf("__");setcolor(0,0); printf(" ");setcolor(12,12); printf("__");setcolor(0,0); printf("   ");setcolor(12,12); printf("__\n");
setcolor(0,0); printf("\t\t\t");setcolor(12,12); printf("__");setcolor(0,0); printf(" ");setcolor(12,12); printf("____");setcolor(0,0); printf(" ");setcolor(12,12); printf("__");setcolor(0,0); printf("    ");setcolor(12,12); printf("__");setcolor(0,0); printf("    ");setcolor(12,12); printf("__");setcolor(0,0); printf("   ");setcolor(12,12); printf("____");setcolor(0,0); printf("     \n");
setcolor(0,0); printf("\t\t\t");setcolor(0,0); printf(" ");setcolor(12,12); printf("___");setcolor(0,0); printf("  ");setcolor(12,12); printf("___");setcolor(0,0); printf("   ");setcolor(12,12); printf("______");setcolor(0,0); printf("  ");setcolor(12,12); printf("__");setcolor(0,0); printf("    ");setcolor(12,12); printf("___");setcolor(0,0); printf("   ");setcolor(12,12); printf("__\n\n"); 
setcolor(15,0);
printf("................................................................................\n\n");                                                                                                                                                                      
	int u=1,i=30,play=0;
	gotoxy(i,18);setcolor(0,15); printf("PLAY AGAIN?");
	gotoxy(i+15,18);setcolor(15,0);printf("BACK");
	gotoxy(1,26);setcolor(15,3); printf("\t\t\t\t\t\t\t\t    Exit : Red ");setcolor(0,0);
	while(SP->IsConnected())
	{
	readResult = SP->ReadData(incomingData,dataLength);
	incomingData[readResult] = 0;
	if(incomingData[0] =='7'){Beep(500,50);exit(0);}
	else if(incomingData[0] =='1' && u>0){Beep(700,50);u--;}
	else if(incomingData[0] =='2' && u<3){Beep(700,50);u++;}
		if(u==1)
			{	
			gotoxy(i,18);setcolor(0,15); printf("PLAY AGAIN?");
			gotoxy(i+15,18);setcolor(15,0);printf("BACK");
			if(incomingData[0] =='3'){Beep(2000,50);play=1;}
			}	
		else if(u==2)
			{
			gotoxy(i,18);setcolor(15,0); printf("PLAY AGAIN?");
			gotoxy(i+15,18);setcolor(0,15);printf("BACK");setcolor(15,0);
			if(incomingData[0] =='3'){Beep(2000,50);play=2;}
			}
	if(play==1){Sleep(50);system("cls");player();}
	else if(play==2){Sleep(50);system("cls");main();} 	
	}
}
void win()
{
	printf("\n\n\n\n");
// you win! 
setcolor(0,0); printf("  ");setcolor(12,12); printf("__");setcolor(0,0); printf("      ");setcolor(12,12); printf("__");setcolor(0,0); printf("  ");setcolor(12,12); printf("________");setcolor(0,0); printf("  ");setcolor(12,12); printf("__");setcolor(0,0); printf("    ");setcolor(12,12); printf("__");setcolor(0,0); printf("\t");setcolor(12,12); printf("__");setcolor(0,0); printf("         ");setcolor(12,12); printf("__");setcolor(0,0); printf("  ");setcolor(12,12); printf("______");setcolor(0,0); printf("  ");setcolor(12,12); printf("___");setcolor(0,0); printf("     ");setcolor(12,12); printf("__");setcolor(0,0); printf("   ");setcolor(12,12); printf("__\n");
setcolor(0,0); printf("   ");setcolor(12,12); printf("__");setcolor(0,0); printf("    ");setcolor(12,12); printf("__");setcolor(0,0); printf("   ");setcolor(12,12); printf("__");setcolor(0,0); printf("    ");setcolor(12,12); printf("__");setcolor(0,0); printf("  ");setcolor(12,12); printf("__");setcolor(0,0); printf("    ");setcolor(12,12); printf("__");setcolor(0,0); printf("\t");setcolor(12,12); printf("__");setcolor(0,0); printf("         ");setcolor(12,12); printf("__");setcolor(0,0); printf("    ");setcolor(12,12); printf("__");setcolor(0,0); printf("    ");setcolor(12,12); printf("____");setcolor(0,0); printf("    ");setcolor(12,12); printf("__");setcolor(0,0); printf("   ");setcolor(12,12); printf("__\n");
setcolor(0,0); printf("    ");setcolor(12,12); printf("__");setcolor(0,0); printf("  ");setcolor(12,12); printf("__");setcolor(0,0); printf("    ");setcolor(12,12); printf("__");setcolor(0,0); printf("    ");setcolor(12,12); printf("__");setcolor(0,0); printf("  ");setcolor(12,12); printf("__");setcolor(0,0); printf("    ");setcolor(12,12); printf("__");setcolor(0,0); printf("\t");setcolor(12,12); printf("__");setcolor(0,0); printf("         ");setcolor(12,12); printf("__");setcolor(0,0); printf("    ");setcolor(12,12); printf("__");setcolor(0,0); printf("    ");setcolor(12,12); printf("__");setcolor(0,0); printf(" ");setcolor(12,12); printf("__");setcolor(0,0); printf("   ");setcolor(12,12); printf("__");setcolor(0,0); printf("   ");setcolor(12,12); printf("__\n");
setcolor(0,0); printf("     ");setcolor(12,12); printf("____");setcolor(0,0); printf("     ");setcolor(12,12); printf("__");setcolor(0,0); printf("    ");setcolor(12,12); printf("__");setcolor(0,0); printf("  ");setcolor(12,12); printf("__");setcolor(0,0); printf("    ");setcolor(12,12); printf("__");setcolor(0,0); printf("\t");setcolor(12,12); printf("__");setcolor(0,0); printf("         ");setcolor(12,12); printf("__");setcolor(0,0); printf("    ");setcolor(12,12); printf("__");setcolor(0,0); printf("    ");setcolor(12,12); printf("__");setcolor(0,0); printf("  ");setcolor(12,12); printf("__");setcolor(0,0); printf("  ");setcolor(12,12); printf("__");setcolor(0,0); printf("   ");setcolor(12,12); printf("__\n"); 
setcolor(0,0); printf("      ");setcolor(12,12); printf("__");setcolor(0,0); printf("      ");setcolor(12,12); printf("__");setcolor(0,0); printf("    ");setcolor(12,12); printf("__");setcolor(0,0); printf("  ");setcolor(12,12); printf("__");setcolor(0,0); printf("    ");setcolor(12,12); printf("__");setcolor(0,0); printf("\t");setcolor(0,0); printf(" ");setcolor(12,12); printf("__");setcolor(0,0); printf("  ");setcolor(12,12); printf("___");setcolor(0,0); printf("  ");setcolor(12,12); printf("__");setcolor(0,0); printf("     ");setcolor(12,12); printf("__");setcolor(0,0); printf("    ");setcolor(12,12); printf("__");setcolor(0,0); printf("   ");setcolor(12,12); printf("__");setcolor(0,0); printf(" ");setcolor(12,12); printf("__");setcolor(0,0); printf("   ");setcolor(12,12); printf("__\n");
setcolor(0,0); printf("      ");setcolor(12,12); printf("__");setcolor(0,0); printf("      ");setcolor(12,12); printf("__");setcolor(0,0); printf("    ");setcolor(12,12); printf("__");setcolor(0,0); printf("  ");setcolor(12,12); printf("__");setcolor(0,0); printf("    ");setcolor(12,12); printf("__");setcolor(0,0); printf("\t");setcolor(0,0); printf("  ");setcolor(12,12); printf("____");setcolor(0,0); printf(" ");setcolor(12,12); printf("____");setcolor(0,0); printf("      ");setcolor(12,12); printf("__");setcolor(0,0); printf("    ");setcolor(12,12); printf("__");setcolor(0,0); printf("    ");setcolor(12,12); printf("____\n");
setcolor(0,0); printf("      ");setcolor(12,12); printf("__");setcolor(0,0); printf("      ");setcolor(12,12); printf("________");setcolor(0,0); printf("  ");setcolor(12,12); printf("________");setcolor(0,0); printf("\t");setcolor(0,0); printf("   ");setcolor(12,12); printf("__");setcolor(0,0); printf("   ");setcolor(12,12); printf("__");setcolor(0,0); printf("     ");setcolor(12,12); printf("______");setcolor(0,0); printf("  ");setcolor(12,12); printf("__");setcolor(0,0); printf("     ");setcolor(12,12); printf("___");setcolor(0,0); printf("   ");setcolor(12,12); printf("__\n"); 
setcolor(15,0);
printf("................................................................................\n\n");                                                                                                                                                                      
	int u=1,i=30,play=0;
	gotoxy(i,15);setcolor(0,15); printf("PLAY AGAIN?");
	gotoxy(i+15,15);setcolor(15,0);printf("BACK");
	gotoxy(1,26);setcolor(15,3); printf("\t\t\t\t\t\t\t\t    Exit : Red ");setcolor(0,0);
	while(SP->IsConnected())
	{
	readResult = SP->ReadData(incomingData,dataLength);
	incomingData[readResult] = 0;
	if(incomingData[0] =='7'){Beep(500,50);exit(0);}
	else if(incomingData[0] =='1' && u>0){Beep(700,50);u--;}
	else if(incomingData[0] =='2' && u<3){Beep(700,50);u++;}
		if(u==1)
			{	
			gotoxy(i,15);setcolor(0,15); printf("PLAY AGAIN?");
			gotoxy(i+15,15);setcolor(15,0);printf("BACK");
			if(incomingData[0] =='3'){Beep(2000,50);play=1;}
			}	
		else if(u==2)
			{
			gotoxy(i,15);setcolor(15,0); printf("PLAY AGAIN?");
			gotoxy(i+15,15);setcolor(0,15);printf("BACK");setcolor(15,0);
			if(incomingData[0] =='3'){Beep(2000,50);play=2;}
			}
	if(play==1){Sleep(50);system("cls");computer();}
	else if(play==2){Sleep(50);system("cls");main();} 	
	}
}
void lose()
{
  printf("\n\n\n\n");
// you lose! 
setcolor(0,0); printf(" ");setcolor(9,9); printf("__");setcolor(0,0); printf("      ");setcolor(9,9); printf("__");setcolor(0,0); printf("  ");setcolor(9,9); printf("________");setcolor(0,0); printf("  ");setcolor(9,9); printf("__");setcolor(0,0); printf("    ");setcolor(9,9); printf("__");setcolor(0,0); printf("\t");setcolor(9,9); printf("__");setcolor(0,0); printf("        ");setcolor(9,9); printf("________");setcolor(0,0); printf("  ");setcolor(9,9); printf("________");setcolor(0,0); printf("  ");setcolor(9,9); printf("________");setcolor(0,0); printf("   ");setcolor(9,9); printf("__\n");
setcolor(0,0); printf("  ");setcolor(9,9); printf("__");setcolor(0,0); printf("    ");setcolor(9,9); printf("__");setcolor(0,0); printf("   ");setcolor(9,9); printf("__");setcolor(0,0); printf("    ");setcolor(9,9); printf("__");setcolor(0,0); printf("  ");setcolor(9,9); printf("__");setcolor(0,0); printf("    ");setcolor(9,9); printf("__");setcolor(0,0); printf("\t");setcolor(9,9); printf("__");setcolor(0,0); printf("        ");setcolor(9,9); printf("__");setcolor(0,0); printf("    ");setcolor(9,9); printf("__");setcolor(0,0); printf("  ");setcolor(9,9); printf("__");setcolor(0,0); printf("        ");setcolor(9,9); printf("__");setcolor(0,0); printf("         ");setcolor(9,9); printf("__\n");
setcolor(0,0); printf("   ");setcolor(9,9); printf("__");setcolor(0,0); printf("  ");setcolor(9,9); printf("__");setcolor(0,0); printf("    ");setcolor(9,9); printf("__");setcolor(0,0); printf("    ");setcolor(9,9); printf("__");setcolor(0,0); printf("  ");setcolor(9,9); printf("__");setcolor(0,0); printf("    ");setcolor(9,9); printf("__");setcolor(0,0); printf("\t");setcolor(9,9); printf("__");setcolor(0,0); printf("        ");setcolor(9,9); printf("__");setcolor(0,0); printf("    ");setcolor(9,9); printf("__");setcolor(0,0); printf("  ");setcolor(9,9); printf("__");setcolor(0,0); printf("        ");setcolor(9,9); printf("__");setcolor(0,0); printf("         ");setcolor(9,9); printf("__\n");
setcolor(0,0); printf("    ");setcolor(9,9); printf("____");setcolor(0,0); printf("     ");setcolor(9,9); printf("__");setcolor(0,0); printf("    ");setcolor(9,9); printf("__");setcolor(0,0); printf("  ");setcolor(9,9); printf("__");setcolor(0,0); printf("    ");setcolor(9,9); printf("__");setcolor(0,0); printf("\t");setcolor(9,9); printf("__");setcolor(0,0); printf("        ");setcolor(9,9); printf("__");setcolor(0,0); printf("    ");setcolor(9,9); printf("__");setcolor(0,0); printf("  ");setcolor(9,9); printf("________");setcolor(0,0); printf("  ");setcolor(9,9); printf("______");
setcolor(0,0); printf("     ");setcolor(9,9); printf("__\n");
setcolor(0,0); printf("     ");setcolor(9,9); printf("__");setcolor(0,0); printf("      ");setcolor(9,9); printf("__");setcolor(0,0); printf("    ");setcolor(9,9); printf("__");setcolor(0,0); printf("  ");setcolor(9,9); printf("__");setcolor(0,0); printf("    ");setcolor(9,9); printf("__");setcolor(0,0); printf("\t");setcolor(9,9); printf("__");setcolor(0,0); printf("        ");setcolor(9,9); printf("__");setcolor(0,0); printf("    ");setcolor(9,9); printf("__");setcolor(0,0); printf("        ");setcolor(9,9); printf("__");setcolor(0,0); printf("  ");setcolor(9,9); printf("__");
setcolor(0,0); printf("         ");setcolor(9,9); printf("__\n");
setcolor(0,0); printf("     ");setcolor(9,9); printf("__");setcolor(0,0); printf("      ");setcolor(9,9); printf("__");setcolor(0,0); printf("    ");setcolor(9,9); printf("__");setcolor(0,0); printf("  ");setcolor(9,9); printf("__");setcolor(0,0); printf("    ");setcolor(9,9); printf("__");setcolor(0,0); printf("\t");setcolor(9,9); printf("__");setcolor(0,0); printf("        ");setcolor(9,9); printf("__");setcolor(0,0); printf("    ");setcolor(9,9); printf("__");setcolor(0,0); printf("        ");setcolor(9,9); printf("__");setcolor(0,0); printf("  ");setcolor(9,9); printf("__\n");
setcolor(0,0); printf("     ");setcolor(9,9); printf("__");setcolor(0,0); printf("      ");setcolor(9,9); printf("________");setcolor(0,0); printf("  ");setcolor(9,9); printf("________");setcolor(0,0); printf("\t");setcolor(9,9); printf("________");setcolor(0,0); printf("  ");setcolor(9,9); printf("________");setcolor(0,0); printf("  ");setcolor(9,9); printf("________");setcolor(0,0); printf("  ");setcolor(9,9); printf("________");setcolor(0,0); printf("   ");setcolor(9,9); printf("__\n");
setcolor(15,0);
printf("................................................................................\n\n");                                                                                                                                                                      
	int u=1,i=30,play=0;
	gotoxy(i,15);setcolor(0,15); printf("PLAY AGAIN?");
	gotoxy(i+15,15);setcolor(15,0);printf("BACK");
	gotoxy(1,26);setcolor(15,3); printf("\t\t\t\t\t\t\t\t    Exit : Red ");setcolor(0,0);
	while(SP->IsConnected())
	{
	readResult = SP->ReadData(incomingData,dataLength);
	incomingData[readResult] = 0;
	if(incomingData[0] =='7'){Beep(500,50);exit(0);}
	else if(incomingData[0] =='1' && u>0){Beep(700,50);u--;}	
	else if(incomingData[0] =='2' && u<3){Beep(700,50);u++;}
		if(u==1)
			{	
			gotoxy(i,15);setcolor(0,15); printf("PLAY AGAIN?");
			gotoxy(i+15,15);setcolor(15,0);printf("BACK");
			if(incomingData[0] =='3'){Beep(2000,50);play=1;}
			}	
		else if(u==2)
			{
			gotoxy(i,15);setcolor(15,0); printf("PLAY AGAIN?");
			gotoxy(i+15,15);setcolor(0,15);printf("BACK");setcolor(15,0);
			if(incomingData[0] =='3'){Beep(2000,50);play=2;}
			}
	if(play==1){Sleep(50);system("cls");computer();}
	else if(play==2){Sleep(50);system("cls");main();} 	
	}
}
void howto()
{
	gotoxy(35,3); printf("HOW TO PLAY");
	gotoxy(10,5); printf("PLAYER 1 : press button white to move");
	gotoxy(21,6); printf("press button green (between white) to drop coin");
	gotoxy(30,7); printf("(Player VS Computer)");
	gotoxy(10,9); printf("PLAYER 2 : press button blue to move");
	gotoxy(21,10); printf("press button green (between blue) to drop coin");
	gotoxy(21,12); printf("The first to form a horizontal , vertical,");
	gotoxy(21,13); printf("or diagonal line of four is the winner");
	gotoxy(35,17); printf("Made by");
	gotoxy(25,18); printf("Phunyawee  Rodpoon  59010874");
	
	gotoxy(1,26);setcolor(15,3); printf("\t\t\t\t\t\t\t\t    Exit : Red ");setcolor(0,0);
}
#include <stdio.h>
#include <malloc.h>
#include <stdint.h>
#include <ncurses.h>
#include <unistd.h>
#include <stdbool.h>



void pion(int x,int y, char znak){
mvaddch (y, x+1,znak); 
mvaddch (y, x+3,znak);
}

void poziom(int x,int y,char znak){

while(x<=5){
mvaddch (y, x,znak); 
x+=2;
}

}


void grid(int x,int y){

while(y<=5){
if(y%2)pion(x,y,'|');
else {
poziom(x,y,'-');
pion(x,y,'+');
}
y++;
}

}


int main(int argc, char *arg[])
{
initscr (); // inicjujemy okno
grid(1,1);
refresh ();
int tab[3][3];

noecho ();
cbreak ();
keypad (stdscr, TRUE);
bool petla = TRUE;
int y, x;
while (petla) {

getyx( curscr, y, x);
switch ( getch () ) {

case KEY_UP:
if(y==1)move(y+4,x);
else move(y-2,x);
break;

case KEY_DOWN:
if(y==5)move(y-4,x);
else move(y+2,x);
break;

case KEY_RIGHT:
if(x==5)move(y,x-4);
else move(y,x+2);
break;

case KEY_LEFT:
if(x==1)move(y,x+4);
else move(y,x-2);
break;

case (int)'1':
addch('X');
tab[y%3][x%3]='X';
mvprintw(6,0,"X: %d  Y: %d",x%3,y%3);
move(y,x);
break;

case (int)'0':
addch('O');
tab[y%3][x%3]='O';
mvprintw(6,0,"X: %d  Y: %d",x%3,y%3);
move(y,x);
break;


case 27: // ESCAPE
petla = FALSE;

}

int win=0;
for(int i=0;i<3;i++){
if(tab[i][0]==tab[i][1] && tab[i][1]==tab[i][2])win=tab[i][0];
if(tab[0][i]==tab[1][i] && tab[1][i]==tab[2][i])win=tab[0][i];
}
if(tab[0][0]==tab[1][1] && tab[1][1]==tab[2][2])win=tab[0][0];
if(tab[1][2]==tab[0][0] && tab[0][0]==tab[2][1])win=tab[0][0];

if(win){mvprintw(0,0,"Wygrywa %c",(char)win);move(y,x);}








refresh (); // odświeża ekran w każdej iteracji
}



endwin (); // zamykamy okno ncurses



	
return 0;
}


#include <stdio.h>
#include <unistd.h>
#include "gfx4.h"

//Peach Coordinates (x,y,width,height,color)
//(the one pixel boxes may need to be made into 2x2 to see them)

void draw( int x, int y, int height, int width, int color[]);


int main(){

	gfx_open(400,400, "hello");

	int position = 200;
	double xRatio=(140/30);
	double yRatio=(60/15);
	int dp[3] = {255,50,200}; //1
	int lp[3] = {255,115,180};//2
	int y[3] = {255,255,0}; //3
	int s[3] = {255,180,150}; //4
	int b[3] = {0,0,255};//5
	int r[3] = {255,0,0};//6
	int w[3] = {255,255,255};//7
	int event;
	char c;

	while(1) { 
   		
      		c = gfx_wait();
		gfx_clear();
		
		switch(c){

	      		case 'q':  break;
			case '1':

				draw(xPosition+0*(xRatio),yPosition-(1*yRatio),1*yRatio,14*xRatio,dp); // Draws the dress
				draw(xPosition+0*(xRatio),yPosition-(3*yRatio),2*yRatio,15*xRatio,lp);
				draw(xPosition+2*(xRatio),yPosition-(5*yRatio),2*yRatio,13*xRatio,lp);
				draw(xPosition+2*(xRatio),yPosition-(6*yRatio),1*yRatio,2*xRatio,dp);
				draw(xPosition+3*(xRatio),yPosition-(10*yRatio),4*yRatio,2*xRatio,dp);
				draw(xPosition+5*(xRatio),yPosition-(9*yRatio),2*yRatio,2*xRatio,lp);
				draw(xPosition+4*(xRatio),yPosition-(7*yRatio),2*yRatio,9*xRatio,lp);
				draw(xPosition+13*(xRatio),yPosition-(7*yRatio),2*yRatio,1*xRatio,dp);

				draw(xPosition+5*(xRatio),yPosition-(13*yRatio),3*yRatio,1*xRatio,s); // Draws the gloves and arms
				draw(xPosition+6*(xRatio),yPosition-(13*yRatio),2*yRatio,1*xRatio,s);
				draw(xPosition+7*(xRatio),yPosition-(11*yRatio),1*yRatio,1*xRatio,w);
				draw(xPosition+6*(xRatio),yPosition-(10*yRatio),1*yRatio,3*xRatio,w);
				draw(xPosition+8*(xRatio),yPosition-(9*yRatio),1*yRatio,2*xRatio,w);
				draw(xPosition+9*(xRatio),yPosition-(8*yRatio),1*yRatio,1*xRatio,w);
				draw(xPosition+11*(xRatio),yPosition-(9*yRatio),2*yRatio,1*xRatio,w);
				draw(xPosition+12*(xRatio),yPosition-(12*yRatio),4*yRatio,1*xRatio,w);
				draw(xPosition+13*(xRatio),yPosition-(13*yRatio),1*yRatio,2*xRatio,s);
				draw(xPosition+13*(xRatio),yPosition-(12*yRatio),2*yRatio,1*xRatio,s);

				draw(xPosition+8*(xRatio),yPosition-(14*yRatio),3*yRatio,3*xRatio,lp); // Draws the chest ornament
				draw(xPosition+9*(xRatio),yPosition-(14*yRatio),2*yRatio,2*xRatio,y);
				draw(xPosition+10*(xRatio),yPosition-(14*yRatio),1*yRatio,1*xRatio,b);

				draw(xPosition+3*(xRatio),yPosition-(16*yRatio),2*yRatio,12*xRatio,lp); // Draws the top of the dress 
				draw(xPosition+9*(xRatio),yPosition-(17*yRatio),1*yRatio,2*xRatio,dp);

				draw(xPosition+1*(xRatio),yPosition-(14*yRatio),3*yRatio,3*xRatio,y); // Draws the hair
				draw(xPosition+0*(xRatio),yPosition-(17*yRatio),3*yRatio,2*xRatio,y);
				draw(xPosition+1*(xRatio),yPosition-(18*yRatio),1*yRatio,5*xRatio,y);
				draw(xPosition+0*(xRatio),yPosition-(19*yRatio),1*yRatio,5*xRatio,y);
				draw(xPosition+2*(xRatio),yPosition-(22*yRatio),3*yRatio,2*xRatio,y);
				draw(xPosition+2*(xRatio),yPosition-(25*yRatio),3*yRatio,5*xRatio,y);
				draw(xPosition+4*(xRatio),yPosition-(26*yRatio),2*yRatio,4*xRatio,y);
				draw(xPosition+5*(xRatio),yPosition-(27*yRatio),3*yRatio,9*xRatio,y);
				draw(xPosition+14*(xRatio),yPosition-(26*yRatio),3*yRatio,1*xRatio,y);
				draw(xPosition+10*(xRatio),yPosition-(24*yRatio),1*yRatio,2*xRatio,y);
				draw(xPosition+13*(xRatio),yPosition-(18*yRatio),1*yRatio,1*xRatio,y);
				draw(xPosition+1*(xRatio),yPosition-(22*yRatio),3*yRatio,1*xRatio,y);
				draw(xPosition+0*(xRatio),yPosition-(18*yRatio),1*yRatio,1*xRatio,y);

				draw(xPosition+8*(xRatio),yPosition-(30*yRatio),2*yRatio,5*xRatio,y); // Draws the crown 
				draw(xPosition+8*(xRatio),yPosition-(29*yRatio),1*yRatio,1*xRatio,b);
				draw(xPosition+10*(xRatio),yPosition-(29*yRatio),1*yRatio,1*xRatio,r);
				draw(xPosition+12*(xRatio),yPosition-(29*yRatio),1*yRatio,1*xRatio,b);

				draw(xPosition+5*(xRatio),yPosition-(21*yRatio),2*yRatio,1*xRatio,s); // Draws the face
				draw(xPosition+5*(xRatio),yPosition-(19*yRatio),1*yRatio,1*xRatio,b);
				draw(xPosition+6*(xRatio),yPosition-(19*yRatio),1*yRatio,1*xRatio,s);
				draw(xPosition+7*(xRatio),yPosition-(22*yRatio),5*yRatio,2*xRatio,s);
				draw(xPosition+9*(xRatio),yPosition-(23*yRatio),1*yRatio,1*xRatio,s); // these two lines draw the eyebrows
				draw(xPosition+12*(xRatio),yPosition-(23*yRatio),1*yRatio,1*xRatio,s);
				draw(xPosition+10*(xRatio),yPosition-(22*yRatio),2*yRatio,2*xRatio,s);
				draw(xPosition+9*(xRatio),yPosition-(20*yRatio),3*yRatio,3*xRatio,s);
				draw(xPosition+12*(xRatio),yPosition-(20*yRatio),2*yRatio,1*xRatio,s);
				draw(xPosition+13*(xRatio),yPosition-(22*yRatio),3*yRatio,1*xRatio,s);
				draw(xPosition+10*(xRatio),yPosition-(19*yRatio),1*yRatio,2*xRatio,r);
				break;
			
			case '2':
				draw(xPosition+1*(xRatio),yPosition-(1*yRatio),1*yRatio,14*xRatio,dp); // Draws the dress
				draw(xPosition+1*(xRatio),yPosition-(3*yRatio),2*yRatio,14*xRatio,lp);
				draw(xPosition+2*(xRatio),yPosition-(5*yRatio),2*yRatio,12*xRatio,lp);
				draw(xPosition+2*(xRatio),yPosition-(6*yRatio),1*yRatio,2*xRatio,dp);
				draw(xPosition+3*(xRatio),yPosition-(10*yRatio),4*yRatio,2*xRatio,dp);
				draw(xPosition+5*(xRatio),yPosition-(9*yRatio),2*yRatio,2*xRatio,lp);
				draw(xPosition+4*(xRatio),yPosition-(7*yRatio),2*yRatio,9*xRatio,lp);
				draw(xPosition+13*(xRatio),yPosition-(7*yRatio),2*yRatio,1*xRatio,dp);

				draw(xPosition+5*(xRatio),yPosition-(13*yRatio),3*yRatio,1*xRatio,s); // Draws the gloves and arms
				draw(xPosition+6*(xRatio),yPosition-(13*yRatio),2*yRatio,1*xRatio,s);
				draw(xPosition+7*(xRatio),yPosition-(11*yRatio),1*yRatio,1*xRatio,w);
				draw(xPosition+6*(xRatio),yPosition-(10*yRatio),1*yRatio,3*xRatio,w);
				draw(xPosition+8*(xRatio),yPosition-(9*yRatio),1*yRatio,2*xRatio,w);
				draw(xPosition+9*(xRatio),yPosition-(8*yRatio),1*yRatio,1*xRatio,w);
				draw(xPosition+11*(xRatio),yPosition-(9*yRatio),2*yRatio,1*xRatio,w);
				draw(xPosition+12*(xRatio),yPosition-(12*yRatio),4*yRatio,1*xRatio,w);
				draw(xPosition+13*(xRatio),yPosition-(13*yRatio),1*yRatio,2*xRatio,s);
				draw(xPosition+13*(xRatio),yPosition-(12*yRatio),2*yRatio,1*xRatio,s);

				draw(xPosition+8*(xRatio),yPosition-(14*yRatio),3*yRatio,3*xRatio,lp); // Draws the chest ornament
				draw(xPosition+9*(xRatio),yPosition-(14*yRatio),2*yRatio,2*xRatio,y);
				draw(xPosition+10*(xRatio),yPosition-(14*yRatio),1*yRatio,1*xRatio,b);

				draw(xPosition+3*(xRatio),yPosition-(16*yRatio),2*yRatio,12*xRatio,lp); // Draws the top of the dress 
				draw(xPosition+9*(xRatio),yPosition-(17*yRatio),1*yRatio,2*xRatio,dp);

				draw(xPosition+2*(xRatio),yPosition-(14*yRatio),3*yRatio,2*xRatio,y); // Draws the hair
				draw(xPosition+1*(xRatio),yPosition-(17*yRatio),3*yRatio,1*xRatio,y);
				draw(xPosition+1*(xRatio),yPosition-(18*yRatio),1*yRatio,5*xRatio,y);
				draw(xPosition+1*(xRatio),yPosition-(19*yRatio),1*yRatio,5*xRatio,y);
				draw(xPosition+2*(xRatio),yPosition-(22*yRatio),3*yRatio,2*xRatio,y);
				draw(xPosition+2*(xRatio),yPosition-(25*yRatio),3*yRatio,5*xRatio,y);
				draw(xPosition+4*(xRatio),yPosition-(26*yRatio),2*yRatio,4*xRatio,y);
				draw(xPosition+5*(xRatio),yPosition-(27*yRatio),3*yRatio,9*xRatio,y);
				draw(xPosition+14*(xRatio),yPosition-(26*yRatio),3*yRatio,1*xRatio,y);
				draw(xPosition+10*(xRatio),yPosition-(24*yRatio),1*yRatio,2*xRatio,y);
				draw(xPosition+13*(xRatio),yPosition-(18*yRatio),1*yRatio,1*xRatio,y);
				draw(xPosition+1*(xRatio),yPosition-(22*yRatio),3*yRatio,1*xRatio,y);

				draw(xPosition+8*(xRatio),yPosition-(30*yRatio),2*yRatio,5*xRatio,y); // Draws the crown 
				draw(xPosition+8*(xRatio),yPosition-(29*yRatio),1*yRatio,1*xRatio,b);
				draw(xPosition+10*(xRatio),yPosition-(29*yRatio),1*yRatio,1*xRatio,r);
				draw(xPosition+12*(xRatio),yPosition-(29*yRatio),1*yRatio,1*xRatio,b);

				draw(xPosition+5*(xRatio),yPosition-(21*yRatio),2*yRatio,1*xRatio,s); // Draws the face
				draw(xPosition+5*(xRatio),yPosition-(19*yRatio),1*yRatio,1*xRatio,b);
				draw(xPosition+6*(xRatio),yPosition-(19*yRatio),1*yRatio,1*xRatio,s);
				draw(xPosition+7*(xRatio),yPosition-(22*yRatio),5*yRatio,2*xRatio,s);
				draw(xPosition+9*(xRatio),yPosition-(23*yRatio),1*yRatio,1*xRatio,s); // these two lines draw the eyebrows
				draw(xPosition+12*(xRatio),yPosition-(23*yRatio),1*yRatio,1*xRatio,s);
				draw(xPosition+10*(xRatio),yPosition-(22*yRatio),2*yRatio,2*xRatio,s);
				draw(xPosition+9*(xRatio),yPosition-(20*yRatio),3*yRatio,3*xRatio,s);
				draw(xPosition+12*(xRatio),yPosition-(20*yRatio),2*yRatio,1*xRatio,s);
				draw(xPosition+13*(xRatio),yPosition-(22*yRatio),3*yRatio,1*xRatio,s);
				draw(xPosition+10*(xRatio),yPosition-(19*yRatio),1*yRatio,2*xRatio,r);
				break;
			}
		}
	usleep(10000);
}


void draw( int x, int y, int height, int width, int color[]){

	char c;
	gfx_color(color[0], color[1], color[2]);
	gfx_fill_rectangle( x, y, width, height );

}

/*
0 1 1 14 dp // Draws the dress
0 3 2 15 lp
2 5 2 13 lp
2 6 1 2 dp
3 10 4 2 dp
5 9 2 2 lp
4 7 2 9 lp
13 7 2 1 dp
5 13 3 1 s // Draws gloves and arms
6 13 2 1 s
7 11 1 1 w
6 10 1 3 w
8 9 1 2 w
9 8 1 1 w
11 9 2 1 w
12 12 4 1 w
13 13 1 2 s
13 12 2 1 s
8 14 3 3 lp //Draws chest ornament
9 14 2 2 y
10 14 1 1 b
3 16 2 12 lp // Draws top of Dress
9 17 1 2 dp
1 14 3 3 y //Draws the hair
0 17 3 2 y
1 18 1 5 y
0 19 1 5 y
2 22 3 2 y
2 25 3 5 y
4 26 2 4 y
5 27 3 9 y
14 26 3 1 y
10 24 1 2 y
13 18 1 1 y
8 30 2 5 y // Draws the crown
8 29 1 1 b
10 29 1 1 r
12 29 1 1 b
5 21 2 1 s // Draws the face
5 19 1 1 b
6 19 1 1 s
7 22 5 2 s
9 23 1 1 s// Next 2 draw eyebrows
12 23 1 1 s
10 22 2 2 s
9 20 3 3 s
12 20 2 1 s
13 22 3 1 s
10 19 1 2 r
*/

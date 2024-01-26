# include "iGraphics.h"
#include<windows.h>
# include <bits/stdc++.h>
using namespace std;

int pic_x, pic_y, shooter_x, shooter_y, bullet_x=-1, bullet_y=-1;
int game=0;
int height = 750, width = 1122;
int score = 0;
int life = 2;
int blastX, blastY;
/*
	function iDraw() is called again and again by the system.
*/

//https://www.pngwing.com/en/free-png-bjnet
// game window 300-840, 50-550
struct enemy{
    int row = 0, col = 0;
    int x=-1, y=-1;
    int mood = 1;
    int sht = 0;

};
enemy shooters[50];

void showScore() {
    //char x[] = to_string(score);
    char x[15];
    int ind = 0;
    int tmp = score;
    if(tmp==0) {
        x[ind] = 0+'0';
        x[ind+1] = '\0';
    }
    else {
        while(tmp>0) {
            x[ind++] = (tmp%10) + '0';
            tmp /= 10;
        }
        x[ind] = '\0';
        strrev(x);
        //cout << x << endl;
    }

    iText(10,400, "SCORE: ", GLUT_BITMAP_9_BY_15);
    iText(70, 400, x, GLUT_BITMAP_9_BY_15);
}

void showLife() {
    if(life==2) {
        iShowBMP(301, 2, "images\\main_shtr.bmp");
        iShowBMP(351, 2, "images\\main_shtr.bmp");
    }
    else if(life==1) {
        iShowBMP(301, 2, "images\\main_shtr.bmp");
    }
}

void enemyShoot() {
    srand(time(NULL));
    int n = rand() % (24);
    for(int i=0;i<24;i++) {
        shooters[i].sht = 1;
    }

}


void blast(){
    blastX = -1;
    blastX = -1;
}

bool chek(int x, int y) {
    if(x!=-1 && y!=-1) return true;
    return false;
}

void initEnemy() {
    for(int i=0;i<24;i++) {
        shooters[i].row = i/6;
        shooters[i].col = i%6;
        shooters[i].x = 210 + (shooters[i].col * 45);
        shooters[i].y = 700 - (shooters[i].row * 45);
    }
}

void enemyChange() {
    if(game!=1) return;
    for(int i=0;i<24;i++) {
        if(shooters[i].x!=-1 && shooters[i].y!=-1) {
            if(shooters[i].mood==1) {

                int mx = 850 - (5-shooters[i].col) * 45;
                int my = 55 + (5-shooters[i].row) * 45;
                //cout << mx << " " << my << endl;
                if(shooters[i].x + 65 < mx) {
                    shooters[i].x += 65;
                }
                else {
                    if(shooters[i].y - 65 > my) {
                        shooters[i].y -= 65;
                        shooters[i].mood = 0;
                    }

                }
            }
            else {
                int mx = 210 + (shooters[i].col * 45);
                int my = 55 + ((5-shooters[i].row) * 45);
                //cout << mx << " " << my << endl;
                if(shooters[i].x - 65 > mx) {
                    shooters[i].x -= 65;
                    //shooters[i].mood = 0;
                }
                else {
                     if(shooters[i].y-65 > my) {
                        shooters[i].y -= 65;
                        shooters[i].mood = 1;
                     }

                    //shooters[i].y -= 65;
                    //shooters[i].mood = 1;
                }

            }
        }
        //shooters[i].level = i/6;
        // 300 + ((i%6)*45);

        //shooters[i].y = 500 - (shooters[i].level * 45);
    }

}
void bulletChange() {
    if(game!=1) return;
    if(bullet_x!=-1 && bullet_y!=-1) {

        if(bullet_y+10<height) {
            bullet_y += 10;
        }
        else {
            bullet_x = -1;
            bullet_y = -1;
        }

        // checking bullet hit;
        for(int i=0;i<24;i++) {
            if(chek(shooters[i].x,shooters[i].y) && chek(bullet_x, bullet_y)) {
                if(bullet_x >= shooters[i].x && bullet_x<=shooters[i].x+22) {
                    if(bullet_y >= shooters[i].y && bullet_y <= shooters[i].y+22) {
                        blastX = shooters[i].x;
                        blastY = shooters[i].y;
                        bullet_x = -1;
                        bullet_y = -1;
                        shooters[i].x = -1;
                        shooters[i].y = -1;
                        score += 10;
                        //return;

                        PlaySound("sounds\\invaderkilled\\invaderkilled.wav",NULL,SND_ASYNC);
                    }
                }
            }
        }

    }

}

void shoot(int x, int y) {
    bullet_x = x+20;
    bullet_y = y+50;

}


void gameOn() {
        showScore();
        showLife();
        iShowBMP(shooter_x, shooter_y, "images\\main_shtr.bmp");
        iSetColor(0, 255, 0);
        iLine(300, 50, 400, 50);
        iPoint(410, 50); iPoint(420, 50); iPoint(430, 50);
        iLine(440, 50, 650, 50);
        iPoint(660, 50); iPoint(670, 50); iPoint(680, 50);
        iLine(690, 50, 840, 50);
        //iShowBMP(560, 300, "enemy\\enemy4.bmp");
        //iShowBMP(660, 300, "enemy\\enemy2.bmp");
        if(bullet_x!=-1 && bullet_y!=-1) {
            iSetColor(256, 256, 256);
            iLine(bullet_x, bullet_y-10, bullet_x, bullet_y);
        }

        for(int i=0;i<24;i++) {
            if(shooters[i].x!=-1 && shooters[i].y!=-1)
                iShowBMP(shooters[i].x,shooters[i].y, "images\\enemy\\enemy2F.bmp");
        }

        //
        if(blastX !=-1 && blastY != -1) {
            iShowBMP(blastX+5, blastY+5, "images\\enemy\\invertedexp_.bmp");
        }



}



void iDraw()
{
	//place your drawing codes here
	iClear();
    if(game!=0) {
        gameOn();
    }
    else {
        iClear();
        iShowBMP(pic_x, pic_y, "images\\background1.bmp");
        iSetColor(0, 255, 0);
        iText(500, 100, "<< START >>", GLUT_BITMAP_HELVETICA_18);
        //iShowBMP(50, 50, "enemy\\invertedexp_.bmp");
    }

}

void chang() {
            if(shooter_x>820) {
                shooter_x = 300;
            }
            else {
                shooter_x += 10;
            }
}
/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
	//place your codes here
	if((mx>=500 && mx<=600) && (my>=100 && my<=150)) {
            //cout << "Dhukse" << endl;
            //state = 1;
            //iDraw();
            //cout << state << endl;
            //cout << state << endl;
    }
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{

	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		//place your codes here

		if((mx>=500 && mx<=600)) {

            game = 1;


            //cout << state << endl;
		}
		else {
		    //state = 0;

		}

	}
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
	    if((mx>=40 && mx<=100) && (my>=40 && my<=100)) {

            game = 1;
            //iDraw();

            //cout << state << endl;
        }
        //pic_x -= 10;
		//pic_y -= 10;
		//place your codes here
	}
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{
    if(key == 'r') {

        game = 1;

	}
	if(key == 'x')
	{
		//do something with 'x'
		exit(0);
	}
	if(key == ' ') {
        if(bullet_y==-1 && bullet_x==-1) {
                shoot(shooter_x, shooter_y);
                PlaySound("sounds\\shoot\\shoot.wav", NULL, SND_ASYNC);
        }

	}
	if(key == 27) {
        game = 0;
	}
	//place your codes for other keys here
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyboard(unsigned char key)
{

    if(key == GLUT_KEY_RIGHT) {
        if(shooter_x<=800) {
            shooter_x += 15;
        }
    }
    if(key == GLUT_KEY_LEFT) {
        if(shooter_x>=301) {
            shooter_x -= 15;
        }
    }
	//place your codes for other keys here
}

int main()
{
	//place your own initialization codes here.

	pic_x = 0;
	pic_y = 0;
	shooter_x = 550, shooter_y = 55;
    game = 0;
    initEnemy();
    blastX = -1, blastY = -1;
    iSetTimer(10,bulletChange);
    iSetTimer(1100,enemyChange);
    iSetTimer(500,blast);
	iInitialize(width, height, "Space Invaders");

	return 0;
}

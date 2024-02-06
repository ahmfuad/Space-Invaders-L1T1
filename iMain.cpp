# include "iGraphics.h"
#include <bits/stdc++.h>
using namespace std;

int x = 300, y = 300, r = 20;
bool soundStatus = 0;
int game = 0, settings = 0;
int shooterX = 180, shooterY = 57;
int bulletX, bulletY;
int enemyState = 1;
int ovr = 0;
int score = 0;
int life = 2;
int lightX = -1, lightY = -1;
int GG = 0;
/*
	function iDraw() is called again and again by the system.

*/

int grid[20][20]; 

struct enemy {
	int row = -1, col = -1; 
} enemy[50];

void settingsOn() {
	settings = 1;
	game = 0;
}

void resume() {
	iResumeTimer(0);
	iResumeTimer(1);
	iResumeTimer(2);
	iResumeTimer(3);
}
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
	iSetColor(255, 255, 255);
    //iText(10,400, "SCORE: ", GLUT_BITMAP_9_BY_15);
    iText(48, 30, x,  GLUT_BITMAP_TIMES_ROMAN_24);
}

void initEnemy() {
	int cnt = 0;
	for(int i=1;i<=12;i++) {
		for(int j=1;j<=16;j++) {
			grid[i][j] = -1;
			//enemy[cnt].row = i, enemy[cnt].col = j;
			//cnt++;
		}
	}
	for(int i=1;i<=4;i++) {
		for(int j=1;j<=6;j++) {
			grid[i][j] = 1;
			enemy[cnt].row = i, enemy[cnt].col = j;
			cnt++;
		}
	}
}
void enemyChange() {
	int fl = 0;
	if(enemyState == 0) {
		for(int i=0; i<24; i++) {
			if(enemy[i].row == -1 or enemy[i].col == -1) continue;
			int exCol = 1 + (i%6); 
			//grid[enemy[i].row][enemy[i].col] = 0;
			if(enemy[i].col - 1 < exCol) {
				enemy[i].row += 1;
				fl = 1;
			}
			else {
				enemy[i].col -= 1;
				
			}
			//grid[enemy[i].row][enemy[i].col] = 1;
		}
		for(int i=1;i<=12;i++) {
			for(int j=1;j<=16;j++) {
				grid[i][j] = 0;
			}
		}
		for(int i=0;i<24;i++) {
			grid[enemy[i].row][enemy[i].col] = 1;
		}
	
	
		if(fl) enemyState ^= 1;
	}
	else {
		for(int i=0; i<24; i++) {
			//grid[enemy[i].row][enemy[i].col] = 0;
			if(enemy[i].row == -1 or enemy[i].col == -1) continue;
			int exCol = 11 + (i%6); 
			if(enemy[i].col + 1 >= exCol) {
				if(enemy[i].row + 1 > 12) {
					ovr = 1;
					break;
				}
				enemy[i].row += 1;
				fl = 1;
			}
			else {
				enemy[i].col += 1;
			}
			//grid[enemy[i].row][enemy[i].col] = 1;
		}

		for(int i=1;i<=12;i++) {
			for(int j=1;j<=16;j++) {
				grid[i][j] = 0;
			}
		}
		for(int i=0;i<24;i++) {
			grid[enemy[i].row][enemy[i].col] = 1;
		}
	
	
		if(fl) enemyState ^= 1;
	}
}
void showEnemy() {

	for(int i=1;i<=12;i++) {
		for(int j=1;j<=16;j++) {
			if(grid[i][j]==1) {
				//cout << i << " " << j << endl;
				int x = 180 + ((j-1) * 50);
				int y = 680 - ((i-1) * 45);
				//if(i%2==0) {
					iShowBMP2(x, y, "images\\spv3.bmp", 0);
				//}
				//else 
					//iShowBMP2(x, y, "images\\enemyF1.bmp", 0);
			}
		}
	}
}

void gameOn() {
	game = 1;
}

void changeSound() {
	soundStatus ^= 1;
	if(soundStatus == 1) {
		PlaySound("sounds\\bck2.wav", NULL, SND_LOOP | SND_ASYNC); 
	}
	else {
		PlaySound(nullptr, nullptr, 0);
	}
}



void lChange() {
	// lightY -= 20;

	// if(lightY < 0) {
	// 	lightX = -1, lightY = -1;
	// }
	if(lightX != -1 or lightY != -1) {
		//cout << lightX << " " << lightY << endl;
		if(lightY - 20 >= 0) {
			lightY -= 20;
			resume();
			if(lightX +15 >= shooterX and lightX <= shooterX + 40 and lightY >= 20 and lightY <= 67) {
				lightX = -1; lightY = -1;
				cout << life << endl;
				life--;
				ovr = 1;
				if(life <= 0) {
					GG = 1;
					iPauseTimer(0);
					iPauseTimer(1);
					iPauseTimer(2);
					iPauseTimer(3);
					//iPauseTimer(4);
				}
				
			}
		}
		else {
			lightX = -1, lightY = -1;
		}
	}
}

void showL() {
	//assert(lightX != -1);
	if(lightY != -1) {
		iShowBMP2(lightX, lightY, "images\\ligh.bmp", 0);
		//cout << " " << endl;
	}
		
}

void bulletChange() {
	//cout << "lgh " << lightX << " lgy " << lightY << endl; 
	if(bulletX != -1 && bulletY != 1) {
		iResumeTimer(0);
		if(bulletY + 15 <= 719) {
			bulletY += 15;
		}
		else {
			bulletX = -1, bulletY = -1;
		}


		for(int i=0; i< 24; i++) {
			int x = 180 + ((enemy[i].col-1) * 50);
			int y = 680 - ((enemy[i].row-1) * 45);
			if(bulletX >= x and bulletX<=x+50 and bulletY >= y and bulletY<=y+45 and (enemy[i].row != -1 and enemy[i].col != -1)) {
				bulletX = -1, bulletY = -1;
				grid[enemy[i].row][enemy[i].col] = 0;
				//grid[enemy[i].row]
				enemy[i].col = -1, enemy[i].row = -1;
				score += 10;
			}
		}
	}
	else iResumeTimer(0);
}

void shoot() {
	resume();
	//if(bulletX == -1 and bulletY == -1) {
		if(lightX == -1 and lightY == -1) {
			//iPauseTimer(2);
			lightX = shooterX;/*rand() % (850-180) + 180;*/ 
			lightY = 600;
		}
		resume();
		//cout << lightX << ' ' << lightY << endl;
	//}
	
}
int en = 0;


void gameOnn() {
	if(bulletX!=-1 && bulletY!=-1) {
        iSetColor(255, 211, 94);
		iShowBMP2(bulletX, bulletY-10, "images\\shot.bmp", 0);
        //iLine(bulletX, bulletY-10, bulletX, bulletY);
    }
}
void blast(){
	if(ovr==1) {
		cout << "THINGS" << endl;
		iShowBMP2(shooterX, shooterY, "images\\blast.bmp", 0);
		ovr = -1;
	}
}
void iDraw() {
	//place your drawing codes here
	iClear();
	// iSetColor(20, 200, 200);
	// iFilledCircle(x, y, r);
	// //iFilledRectangle(10, 30, 20, 20);
	// iSetColor(20, 200, 0);
	// iText(40, 40, "Hi, I am iGraphics");
	
	if(game==0) {
		if(settings == 0){
			iShowBMP(2, 40,"images\\finBckk.bmp");
		}
		else {
			if(soundStatus == 1) {
				iShowBMP(2, 40, "images\\settings1.bmp");
			}
			else {
				iShowBMP(2, 40, "images\\settings2.bmp");
			}
		}
	}
	else {

		iShowBMP(0, 0, "images\\backcheck45.bmp");
		if(GG!=1)
			iShowBMP2(shooterX, shooterY, "images\\main_shtr.bmp", 0);


		if(life==2) {
			iShowBMP2(20, 65, "images\\main_shtr.bmp", 0);
			iShowBMP2(60, 65, "images\\main_shtr.bmp", 0);
		}
		else if(life==1) {
			iShowBMP2(20, 65,  "images\\main_shtr.bmp", 0);
		}
		else {
			//GG = 1;
			iShowBMP2(387, 100, "images\\gameover.bmp", 0);

		}
		//iShowBMP2(250, 550, "images\\enemy1.bmp", 0);
		gameOnn();
		showEnemy();
		//char x[10];
		//fprintf(stdin, x, "%d", score);
		//iText(41, 26, x);
		showScore();
		//lChange();
		showL();
		blast();
		if(GG!=1) resume();
		//cout << lightX << " " << lightY << endl;
	}
}

/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
	*/
void iMouseMove(int mx, int my) {
	//printf("x = %d, y= %d\n",mx,my);
	//place your codes here
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	 (mx, my)  is the position where the mouse pointer is.
	*/
void iMouse(int button, int state, int mx, int my) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		//place your codes here
		printf("x = %d, y= %d\n",mx,my);
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		//place your codes here
		x -= 10;
		y -= 10;
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx >= 403 && mx<=623 && my>=213 && my<=277 && settings != 1 && game == 0) {
		//place your codes here
		game = 1;
		GG=0;
		life = 2;
		score = 0;
		initEnemy();
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx >= 537 && mx <= 689 && my >= 136 && my <= 193 && game == 0) {
		//place your codes here
		settingsOn();
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx >= 443 && mx <= 565 && my >= 63 && my <= 118 && game == 0) {
		//place your codes here
		exit(0);
	}
	if(settings == 1 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if(mx >= 951 && mx <= 1013 && my >= 603 && my <= 660) {
			game = 0; 
			settings = 0; 
		}
		if(mx >=577 && mx<=625 && my>=172 && my<=223) {
			changeSound();
			game = 0;
		}
	}
	if(game==1 && mx >= 962 && mx <= 1014 && my >= 659 && my <= 706) {
		game = 0;
	}
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
	*/
void iKeyboard(unsigned char key) {
	
	if(key == 27 ) {
		game = 0;
	}
	if(key == ' ' and GG!=1) {
		
		if(bulletX == -1 && bulletY == -1) {
			//shoot(shooterX, shooterY);
			bulletX = shooterX + 20, bulletY = shooterY + 50;
			iPauseTimer(0);
			//bulletChange();
			//PlaySound("sounds\\shoot.wav", NULL, SND_ASYNC);
    	}
	}
	if(GG==1 and (key=='M' or key=='m')) {
		game = 0;
		GG = 0;
		score = 0;
		life = 2;
		initEnemy();
		resume();
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
void iSpecialKeyboard(unsigned char key) {

	if (key == GLUT_KEY_END) {
		exit(0);
	}

	if(game==1) {
		if(key == GLUT_KEY_RIGHT and shooterX <= 850) {
			shooterX += 10;
		}
		if(key == GLUT_KEY_LEFT and shooterX >= 180) {
			shooterX -= 10;
		}
	}
	//place your codes for other keys here
}


int main() {
	//place your own initialization codes here.
	//char sound[17] = ;
	srand(time(NULL)); 
	bulletX = -1, bulletY = -1;
	initEnemy();
	iSetTimer(2500, shoot);
	iSetTimer(17, bulletChange);
	iSetTimer(20, lChange);
	iSetTimer(997, enemyChange);
	
	
	
	
	
	
	changeSound();
	iInitialize(1024, 719, "Space Invaders");

	
	
	
	return 0;
}
// mx 180 - 850 (shooter range)
// my 57




#include "iGraphics.h"
#include <bits/stdc++.h>
using namespace std;

int x = 300, y = 300, r = 20;
bool soundStatus = 0;
int game = 0, settings = 0;
int shooterX = 180, shooterY = 57, avatar = 0;
int bulletX, bulletY;
int enemyState = 1;
int ovr = 0;
int score = 0;
int life = 2;
int lightX = -1, lightY = -1;
int GG = 0, paused = 0;
int win = 0, winner = 0, scoreDekha = 0;
int allscore[10] = {0};
int allScoreCount = 0;
int boss = 0, boss_x = -1, boss_y = -1, bossLife = 2;
int bossBulletX = -1, bossBulletY = -1, bosBulletXChange = -1;
int enemyCount = 24;
char shtr[][50] = {"images\\main_shtr.bmp", "images\\main_shtr2.bmp"}; 
char bck[][50] = {"images\\finalBCK1.bmp", "images\\finalBCK2.bmp"}; 

vector<int> fx;
vector<int> v;
/*
	function iDraw() is called again and again by the system.

*/

int grid[50][50];

int tonum(char *x) {
	int i=0;
	while(x[i]!='\0') i++;
	int num = 0;
	int pw = 1;
	i--;
	while(i>=0) {
		num += (x[i]-'0')*pw;
		pw *= 10;
		i--;
	}
	return num;
}

struct enemy
{
	int row = -1, col = -1;
} enemy[50];

void settingsOn()
{
	settings = 1;
	game = 0;
}

void resume()
{
	iResumeTimer(0);
	iResumeTimer(1);
	iResumeTimer(2);
	iResumeTimer(3);
	iResumeTimer(4);
}

void pause()
{
	iPauseTimer(0);
	iPauseTimer(1);
	iPauseTimer(2);
	iPauseTimer(3);
	iPauseTimer(4);
}
void showScore()
{
	// char x[] = to_string(score);
	char x[15];
	int ind = 0;
	int tmp = score;
	if (tmp == 0)
	{
		x[ind] = 0 + '0';
		x[ind + 1] = '\0';
	}
	else
	{
		while (tmp > 0)
		{
			x[ind++] = (tmp % 10) + '0';
			tmp /= 10;
		}
		x[ind] = '\0';
		strrev(x);
		// cout << x << endl;
	}
	iSetColor(255, 255, 255);
	// iText(10,400, "SCORE: ", GLUT_BITMAP_9_BY_15);
	iText(48, 30, x, GLUT_BITMAP_TIMES_ROMAN_24);
}


void initboss() {
	if(game==1 and boss_x==-1 and boss_y==-1) {
		boss = 1;
		boss_y = 640;
		boss_x = 1020;
		bossLife = 2;
	}
}

void bossChange() {
	if(game==1 and boss_x!=-1 and boss_y!=-1) {
		if(boss==1) {
			if(boss_x - 5 <= 0) {
				boss_x=-1, boss_y=-1;
				boss = 0;
			}
			else boss_x -= 5;
			srand(time(NULL));
			// int xf = 1 + rand() % 512;
			if(boss_x <= shooterX and boss_x + 125 >= shooterX and bossBulletX==-1 and bossBulletY==-1) {
				//cout << "bosser guli" << endl;
				bossBulletX = boss_x;
				bossBulletY = boss_y;
				//bosBulletXChange = 
			}
		}
	}
}

void initEnemy()
{
	int cnt = 0;
	shooterX = 180 + 365, shooterY - 57;
	for (int i = 1; i <= 40; i++)
	{
		for (int j = 1; j <= 16; j++)
		{
			grid[i][j] = -1;
			// enemy[cnt].row = i, enemy[cnt].col = j;
			// cnt++;
		}
	}
	for (int i = 1; i <= 4; i++)
	{
		for (int j = 1; j <= 6; j++)
		{
			grid[i][j] = 1;
			enemy[cnt].row = i, enemy[cnt].col = j;
			cnt++;
		}
	}
}

bool checkAscend() {
	for(int i=0; i<=24; i++) {
		//int column = enemy[i].col;
		int row = enemy[i].row;
		int y = 680 - ((row - 1) * 45);
		if(enemy[i].row!=-1 and enemy[i].col!=-1 and y<=57) {
			//cout << "paisi reee" << endl;
			return true;
		}
	}
	return false;
}


void enemyChange()
{
	int fl = 0;
	

	if (enemyState == 0)
	{
		for (int i = 0; i < 24; i++)
		{
			if (enemy[i].row == -1 or enemy[i].col == -1)
				continue;
			int exCol = 1 + (i % 6);
			// grid[enemy[i].row][enemy[i].col] = 0;
			if (enemy[i].col - 1 < exCol)
			{
				enemy[i].row += 1;
				fl = 1;
			}
			else
			{
				enemy[i].col -= 1;
			}
			// grid[enemy[i].row][enemy[i].col] = 1;
		}
		for (int i = 1; i <= 40; i++)
		{
			for (int j = 1; j <= 16; j++)
			{
				grid[i][j] = 0;
			}
		}
		for (int i = 0; i < 24; i++)
		{
			grid[enemy[i].row][enemy[i].col] = 1;
		}

		if (fl)
			enemyState ^= 1;
	}
	else
	{
		for (int i = 0; i < 24; i++)
		{
			// grid[enemy[i].row][enemy[i].col] = 0;
			if (enemy[i].row == -1 or enemy[i].col == -1)
				continue;
			int exCol = 11 + (i % 6);
			if (enemy[i].col + 1 >= exCol)
			{
				if (enemy[i].row + 1 > 25)
				{
					ovr = 1;
					break;
				}
				enemy[i].row += 1;
				fl = 1;
			}
			else
			{
				enemy[i].col += 1;
			}
			// grid[enemy[i].row][enemy[i].col] = 1;
		}

		for (int i = 1; i <= 50; i++)
		{
			for (int j = 1; j <= 16; j++)
			{
				grid[i][j] = 0;
			}
		}
		for (int i = 0; i < 24; i++)
		{
			grid[enemy[i].row][enemy[i].col] = 1;
		}

		if (fl)
			enemyState ^= 1;
	}
}

void showEnemy()
{

	for (int i = 1; i <= 50; i++)
	{
		for (int j = 1; j <= 16; j++)
		{
			if (grid[i][j] == 1)
			{
				// cout << i << " " << j << endl;
				int x = 180 + ((j - 1) * 50);
				int y = 680 - ((i - 1) * 45);
				// if(i%2==0) {
				iShowBMP2(x, y, "images\\spv3.bmp", 0);
				//}
				// else
				// iShowBMP2(x, y, "images\\enemyF1.bmp", 0);
			}
		}
	}
}

void gameOn()
{
	game = 1;
}
void saveS(int score)
{
	FILE *xp = fopen("scores.txt", "a");
	char x[15];
	int ind = 0;
	int tmp = score;
	if (tmp == 0)
	{
		x[ind] = 0 + '0';
		x[ind + 1] = '\0';
	}
	else
	{
		while (tmp > 0)
		{
			x[ind++] = (tmp % 10) + '0';
			tmp /= 10;
		}
		x[ind] = '\0';
		strrev(x);
		// cout << x << endl;
	}
	//cout << "THIS" << endl;
	fprintf(xp, "%s\n", x);
	fclose(xp);
}


void changeSound()
{
	soundStatus ^= 1;
	if (soundStatus == 1)
	{
		PlaySound("sounds\\bck2.wav", NULL, SND_LOOP | SND_ASYNC);
	}
	else
	{
		PlaySound(nullptr, nullptr, 0);
	}
}

void lChange()
{
	// lightY -= 20;

	// if(lightY < 0) {
	// 	lightX = -1, lightY = -1;
	// }
	if(bossBulletX!=-1 and bossBulletY != -1) {
		//bossBulletX += 10;
		bossBulletY -= 10;
		
		if (bossBulletX + 15 >= shooterX and bossBulletX <= shooterX + 40 and bossBulletY >= 20 and bossBulletY <= 67)
			{
				bossBulletX = -1;
				bossBulletY = -1;
				cout << life << endl;
				life--;
				ovr = 1;
				if (life <= 0)
				{
					GG = 1;
					//cout << "DHUKSE" << endl;
					if(soundStatus == 1) PlaySound("sounds\\bck2.wav", NULL, SND_LOOP | SND_ASYNC);

					iPauseTimer(0);
					iPauseTimer(1);
					iPauseTimer(2);
					iPauseTimer(3);
					saveS(score);
				}
			}
		if(bossBulletY < -1) {
			bossBulletX = -1;
			bossBulletY = -1;
		}
	}


	if (lightX != -1 or lightY != -1)
	{
		// cout << lightX << " " << lightY << endl;
		if (lightY - 20 >= 0)
		{
			lightY -= 20;
			resume();
			if (lightX + 15 >= shooterX and lightX <= shooterX + 40 and lightY >= 20 and lightY <= 67)
			{
				lightX = -1;
				lightY = -1;
				cout << life << endl;
				life--;
				ovr = 1;
				if (life <= 0)
				{
					GG = 1;
					cout << "DHUKSE" << endl;
					if(soundStatus == 1) PlaySound("sounds\\bck2.wav", NULL, SND_LOOP | SND_ASYNC);

					iPauseTimer(0);
					iPauseTimer(1);
					iPauseTimer(2);
					iPauseTimer(3);
					saveS(score);
					// FILE *xp = fopen("scores.txt", "a");
					// char x[15];
					// int ind = 0;
					// int tmp = score;
					// if (tmp == 0)
					// {
					// 	x[ind] = 0 + '0';
					// 	x[ind + 1] = '\0';
					// }
					// else
					// {
					// 	while (tmp > 0)
					// 	{
					// 		x[ind++] = (tmp % 10) + '0';
					// 		tmp /= 10;
					// 	}
					// 	x[ind] = '\0';
					// 	strrev(x);
					// 	// cout << x << endl;
					// }
					// cout << "THIS" << endl;
					// fprintf(xp, "%s\n", x);
					// fclose(xp);
					// iPauseTimer(4);
				}
			}
		}
		else
		{
			lightX = -1, lightY = -1;
		}
	}
}

void showL()
{
	// assert(lightX != -1);
	if (lightY != -1)
	{
		iShowBMP2(lightX, lightY, "images\\ligh.bmp", 0);
		// cout << " " << endl;
	}
}


void bulletChange()
{
	// cout << "lgh " << lightX << " lgy " << lightY << endl;
	
	if (bulletX != -1 && bulletY != 1)
	{
		iResumeTimer(0);
		if (bulletY + 15 <= 719)
		{
			bulletY += 15;
		}
		else
		{
			bulletX = -1, bulletY = -1;
		}

		for (int i = 0; i < 24; i++)
		{
			int x = 180 + ((enemy[i].col - 1) * 50);
			int y = 680 - ((enemy[i].row - 1) * 45);
			if (bulletX >= x and bulletX <= x + 50 and bulletY >= y and bulletY <= y + 45 and (enemy[i].row != -1 and enemy[i].col != -1))
			{
				bulletX = -1, bulletY = -1;
				grid[enemy[i].row][enemy[i].col] = 0;
				// grid[enemy[i].row]
				enemy[i].col = -1, enemy[i].row = -1;
				score += 10;
				enemyCount --;
				if (enemyCount == 0)
				{
					winner = 1;
					saveS(score);
					iPauseTimer(0);
					iPauseTimer(1);
					iPauseTimer(2);
					iPauseTimer(3);
				}
			}

			if(bulletX >= boss_x and bulletX <= boss_x+125 and bulletY >= boss_y and boss_x!=-1 and boss_y != -1) {
				bulletX = -1, bulletY = -1;
				bossLife --;
				
				if(bossLife == 0) {
					if(soundStatus==1) PlaySound("sounds\\explosion.wav", NULL, SND_ASYNC);
					boss = 0, boss_x = -1, boss_y = -1;
					score += 50;
				}
			}
		}
	}
	else
		iResumeTimer(0);
}

void shoot()
{
	resume();
	if (game == 0)
		return;
	// if(bulletX == -1 and bulletY == -1) {
	if (lightX == -1 and lightY == -1)
	{
		// iPauseTimer(2);
		lightX = shooterX; /*rand() % (850-180) + 180;*/
		lightY = 600;
	}
	resume();
	// cout << lightX << ' ' << lightY << endl;
	//}
}
void showScores()
{
	int y = 210;
	//cout << fx.size() << endl;
	if(fx.size()==0) {
		iSetColor(255, 0, 0);
		for(int i=0; i<5; i++) {
			iText(478, y, "N/A", GLUT_BITMAP_TIMES_ROMAN_24);
		y -= 35;
		//iText(478, y, "N/A", GLUT_BITMAP_TIMES_ROMAN_24);
		}
		return;
	}
	sort(fx.rbegin(),fx.rend());
	iSetColor(255, 0, 0);
	for(int i=0; i<5; i++) {
		//cout << fx[i] << endl;
		if(i>=fx.size()) {
			iText(478, y, "N/A", GLUT_BITMAP_TIMES_ROMAN_24);
		}
		else {
			char nm[30]={};
			int tmp = fx[i];
			int x = 0;
			while(tmp>0) {
				nm[x++] = (char)((tmp%10) + '0');
				tmp /= 10;
			}
			nm[x] = '\0';
			strrev(nm);
			//cout << nm << endl;
			iText(475, y, nm, GLUT_BITMAP_TIMES_ROMAN_24);
		}
		y -= 35;
		//iText(478, y, "N/A", GLUT_BITMAP_TIMES_ROMAN_24);
	}
	// for (int i = 0; i < 5; i++)
	// {
	// 	// cout << i << endl;

	// 	// string s = i;
	// 	// char *x = s.data();
	// 	// char x[20];
	// 	// strcpy(x, s);
	// 	iSetColor(255, 0, 0);
	// 	// char idx[15];

	// 	// idx = ;
	// 	// iText(458, y, idx, GLUT_BITMAP_TIMES_ROMAN_24);
	// 	if (fx[i][0] == '\0')
	// 	{
	// 		iText(478, y, "N/A", GLUT_BITMAP_TIMES_ROMAN_24);
	// 	}
	// 	else
	// 		iText(475, y, fx[i], GLUT_BITMAP_TIMES_ROMAN_24);
	// 	y -= 35;
	// 	// GLUT_BITMAP_TIMES_ROMAN_24
	// }
}

int en = 0;

void shot()
{
	if (bulletX != -1 && bulletY != -1)
	{
		iSetColor(255, 211, 94);
		iShowBMP2(bulletX, bulletY - 10, "images\\shot.bmp", 0);
		// iLine(bulletX, bulletY-10, bulletX, bulletY);
	}
}
void blast()
{
	if (ovr == 1)
	{
		cout << "THINGS" << endl;
		iShowBMP2(shooterX, shooterY, "images\\blast.bmp", 0);
		ovr = -1;
	}
}
void iDraw()
{
	// place your drawing codes here
	iClear();
	// iSetColor(20, 200, 200);
	// iFilledCircle(x, y, r);
	// //iFilledRectangle(10, 30, 20, 20);
	// iSetColor(20, 200, 0);
	// iText(40, 40, "Hi, I am iGraphics");

	if (game == 0)
	{
		// cout << score << endl;
		// cout << soundStatus << endl;
		if (settings == 0 and scoreDekha == 1)
		{
			// if(scoreDekha==1) {
			iShowBMP(2, 40, "images\\highscore.bmp");
			showScores();
		}
		else if (settings == 0)
		{
			iShowBMP(2, 40, bck[avatar]);
		}
		else
		{
			if (soundStatus == 1)
			{
				iShowBMP(2, 40, "images\\settings1.bmp");
			}
			else
			{
				iShowBMP(2, 40, "images\\settings2.bmp");
			}
		}
	}
	else
	{
		if (winner == 1)
		{
			iShowBMP(0, 0, "images\\backcheck45.bmp");
			iShowBMP2(387, 100, "images\\winner.bmp", 255);
			showScore();
			pause();
			return;
		}

		iShowBMP(0, 0, "images\\backcheck45.bmp");
		showEnemy();
		if(checkAscend()) {
			// GG = 1;
			// //cout << "DHUKSE" << endl;
			// if(soundStatus == 1) PlaySound("sounds\\bck2.wav", NULL, SND_LOOP | SND_ASYNC);

			// iPauseTimer(0);
			// iPauseTimer(1);
			// iPauseTimer(2);
			// iPauseTimer(3);
			// saveS(score);
			if(GG!=1 and ovr!=1) {
				saveS(score);
			}
			life = 0;
			GG = 1;
			iPauseTimer(0);
			iPauseTimer(1);
			iPauseTimer(2);
			iPauseTimer(3);
		}
		if (GG != 1)
			iShowBMP2(shooterX, shooterY, shtr[avatar], 255);

		if (life == 2)
		{
			iShowBMP2(20, 65, shtr[avatar], 255);
			iShowBMP2(60, 65, shtr[avatar], 255);
		}
		else if (life == 1)
		{
			iShowBMP2(20, 65, shtr[avatar], 0);
		}
		else
		{
			// GG = 1;
			iShowBMP2(387, 100, "images\\gameover.bmp", 0);
		}
		// iShowBMP2(250, 550, "images\\enemy1.bmp", 0);
		if (paused == 1)
		{
			iShowBMP2(387, 100, "images\\pausedFinal.bmp", 255);
			pause();
		}
		else
		{
			resume();
		}
		shot();
		
		// char x[10];
		// fprintf(stdin, x, "%d", score);
		// iText(41, 26, x);
		showScore();
		// lChange();
		showL();
		blast();

		if (paused != 1)
		{
			if (GG != 1)
			{
				resume();
			}
			else
			{
				pause();
			}
		}
		if(boss==1) {
			iShowBMP2(boss_x, boss_y, "images\\UFO3.bmp", 0);
		}
		if(bossBulletX != -1 and bossBulletY !=-1) {
			iShowBMP2(bossBulletX, bossBulletY, "images\\blast.bmp", 0);
		}
		// if(GG!=1 and paused!=1) resume();
		// cout << lightX << " " << lightY << endl;
	}
}

/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
	*/
void iMouseMove(int mx, int my)
{
	// printf("x = %d, y= %d\n",mx,my);
	// place your codes here
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	 (mx, my)  is the position where the mouse pointer is.
	*/
void iMouse(int button, int state, int mx, int my)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		// place your codes here
		printf("x = %d, y= %d\n", mx, my);
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		// place your codes here
		x -= 10;
		y -= 10;
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx >= 403 && mx <= 623 && my >= 213 && my <= 277 && settings != 1 && game == 0 && scoreDekha != 1)
	{
		// place your codes here
		PlaySound(nullptr, nullptr, 0);
		game = 1;
		GG = 0;
		life = 2;
		score = 0;
		enemyCount = 24;
		boss_x = -1, boss_y = -1;
		initEnemy();
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx <= 136 && mx >=  60 && my >= 56 && my <= 139 && settings != 1 && game == 0 && scoreDekha != 1)
	{
		// place your codes here
		avatar = 1;
		//cout << avatar << endl;
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx <= 231 && mx >= 156 && my >= 53 && my <= 136 && settings != 1 && game == 0 && scoreDekha != 1)
	{
		// place your codes here
		
		avatar = 0;
		//cout << avatar << endl;
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx >= 537 && mx <= 689 && my >= 136 && my <= 193 && game == 0 && scoreDekha != 1)
	{
		// place your codes here
		settingsOn();
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx >= 443 && mx <= 565 && my >= 63 && my <= 118 && game == 0 && scoreDekha != 1 && settings!=1)
	{
		// place your codes here
		exit(0);
	}
	if (settings == 1 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (mx >= 951 && mx <= 1013 && my >= 603 && my <= 660)
		{
			game = 0;
			settings = 0;
		}
		if (mx >= 577 && mx <= 625 && my >= 172 && my <= 223)
		{
			changeSound();
			game = 0;
		}
		if(mx >=410 && mx <= 623 && my >= 75 && my <= 136) {
			fclose(fopen("scores.txt", "w"));
			soundStatus = 1;
		}
	}
	if (game == 1 && mx >= 962 && mx <= 1014 && my >= 659 && my <= 706)
	{
		game = 0;
	}
	if (game == 0 && mx >= 305 && mx <= 483 && my >= 137 && my <= 195 && button == GLUT_LEFT_BUTTON)
	{
		scoreDekha = 1;
		FILE *scores = fopen("scores.txt", "r");
		fx.clear();
		if (!scores)
		{
			cout << "NAI" << endl;
		}
		else
		{
			fclose(scores);
			allScoreCount = 0;
			char ss[30];
			FILE *sF = fopen("scores.txt", "r");
			if(sF) {
				while (fscanf(sF, "%s\n", ss) > 0)
				{
					// cout << ss << endl;
					//int s = tonum(ss);
					//cout << s << endl;
					//if(ss==EOF) break;
					fx.push_back(tonum(ss));
					
					//strcpy(fx[allScoreCount++], ss);
				}

				for(auto i: fx) {
					cout << i << " ";
				}
				cout << endl;
				
			}
			fclose(scores);
		}
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx >= 969 && mx <= 1003 && my >= 621 && my <= 652 && game == 0 and scoreDekha == 1)
	{
		scoreDekha = 0;
	}
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
	*/
void iKeyboard(unsigned char key)
{

	if (key == 27)
	{
		game = 0;
	}
	if (key == ' ' and GG != 1 and paused != 1)
	{
		//char ass[10]="12\0";
		//cout << tonum(ass) << endl;
		if (bulletX == -1 && bulletY == -1)
		{
			// shoot(shooterX, shooterY);
			bulletX = shooterX + 20, bulletY = shooterY + 50;
			iPauseTimer(0);
			// bulletChange();
			if(soundStatus==1) PlaySound("sounds\\shoot.wav", NULL, SND_ASYNC);
		}
	}
	if (GG == 1 and (key == 'M' or key == 'm'))
	{
		// changeSound();
		game = 0;
		GG = 0;
		score = 0;
		life = 2;
		if (soundStatus == 1)
		{

			PlaySound("sounds\\bck2.wav", NULL, SND_LOOP | SND_ASYNC);
		}
		initEnemy();
		resume();
		iPauseTimer(0);
	}
	if (key == 'p')
	{
		// changeSound();
		cout << soundStatus << endl;
		if (soundStatus == 1)
		{

			PlaySound("sounds\\bck2.wav", NULL, SND_LOOP | SND_ASYNC);
		}
		paused = 1;
	}

	if (key == 'r' and game == 1 and paused == 1)
	{
		// changeSound();
		PlaySound(nullptr, nullptr, 0);
		paused = 0;
	}
	if (key == 'r' and game == 1 and winner == 1)
	{
		winner = 0;
		game = 0;
	}

	// place your codes for other keys here
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

	if (key == GLUT_KEY_END)
	{
		exit(0);
	}

	if (game == 1)
	{
		if (key == GLUT_KEY_RIGHT and shooterX <= 850 and paused != 1)
		{
			shooterX += 10;
		}
		if (key == GLUT_KEY_LEFT and shooterX >= 180 and paused != 1)
		{
			shooterX -= 10;
		}
	}
	// place your codes for other keys here
}

int main()
{
	// place your own initialization codes here.
	// char sound[17] = ;
	srand(time(NULL));
	bulletX = -1, bulletY = -1;
	shooterX = 180 + 365, shooterY = 57;
	initEnemy();
	iSetTimer(5500, shoot);
	iSetTimer(17, bulletChange);
	iSetTimer(20, lChange);
	iSetTimer(977, enemyChange);
	iSetTimer(60, bossChange);
	iSetTimer(17000, initboss);
	
	changeSound();
	// PlaySound("sounds\\bck2.wav", NULL, SND_LOOP | SND_ASYNC);
	iInitialize(1024, 719, "Space Invaders");
	
	return 0;
}

// mx 180 - 850 (shooter range)
// my 57

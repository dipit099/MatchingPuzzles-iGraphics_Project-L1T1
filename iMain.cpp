#define _CRT_SECURE_NO_WARNINGS
#include "iGraphics.h"
#include<stdio.h>
#include<time.h>
#include<stdlib.h>

void location_change();
void coordinates();
void check_pic();
struct pic
{
	int x;
	int y;
};
struct correct_pic
{
	int x;
	int y;
};
bool music = true;
int scene = -1;
int openx = 0, openy = 560;
bool correct = true;
int moves = 0;
char initial[5][20] = { "0.bmp", "2.bmp", "10.bmp", "3.bmp", "settings.bmp" };
char picture[25][20] = { "main_01.bmp", "main_02.bmp", "main_03.bmp", "main_04.bmp", "main_05.bmp",
"main_06.bmp", "main_07.bmp", "main_08.bmp", "main_09.bmp", "main_10.bmp",
"main_11.bmp", "main_12.bmp", "main_13.bmp", "main_14.bmp", "main_15.bmp",
"main_16.bmp", "main_17.bmp", "main_18.bmp", "main_19.bmp", "main_20.bmp",
"main_21.bmp", "main_22.bmp", "main_23.bmp", "main_24.bmp", "main_25.bmp" };
char arr[100], str[10];
int index = 0, run = 1;
struct pic pic[25];
struct correct_pic correct_pic[25];
clock_t start;
int color1 = 1, color2 = 0, color3 = 1, color4 = 0;

void iDraw()
{
	iClear();

	if (scene == -1)
	{
		iShowBMP(0, 0, initial[2]);
		iShowBMP2(300, 400, initial[0], 0);
		iShowBMP2(300, 300, initial[1], 0);
		iShowBMP2(300, 200, initial[3], 0);
		iShowBMP2(300, 90, initial[4], 0);

		iSetColor(255, 255, 255);
		//iText(300, 600, "Welcome to Matching Puzzle!", GLUT_BITMAP_TIMES_ROMAN_24);
		//iShowBMP2(300, 600, "title.bmp", 16777215);

	}
	else if (scene == 1)
	{
		iShowBMP(0, 0, "set2.bmp");
		iSetColor(255, 255, 0);
		iText(30, 300 - 50, "INSTRUCTIONS :", GLUT_BITMAP_TIMES_ROMAN_24);
		iSetColor(0, 255, 0);
		iText(600, 280, "Match this !", GLUT_BITMAP_TIMES_ROMAN_24);
		iShowBMP(430, 330, "target.bmp");
		iSetColor(255, 192, 203);
		iText(30, 250 - 50, "Use Left click to move a picture.  The picture you click will be swapped", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(30, 220 - 50, "with the blank purple pic.", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(30, 170 - 50, "You have \"30 SECONDS \" time to match it! Best of luck.", GLUT_BITMAP_TIMES_ROMAN_24);
		iSetColor(255, 255, 255);
		iText(30, 100 - 50, "Press 1 to mute sound and 2 to unmute.", GLUT_BITMAP_TIMES_ROMAN_24);
		iShowBMP2(100, 400, "33.bmp", 0);
		iShowBMP2(650, 50, "back.bmp", 0);

	}
	else if (scene == 100)	//entry
	{
		iShowBMP(0, 0, "100.bmp");
		iSetColor(0, 0, 0);
		iShowBMP2(300, 200, "enter.bmp", 0);

		iSetColor(255, 255, 255);
		iFilledRectangle(300, 500, 300, 60);

		iSetColor(0, 255, 0);

		iText(375, 450, "YOUR NAME", GLUT_BITMAP_TIMES_ROMAN_24);
		iShowBMP2(0, 50, "back2.bmp", 0);

		iSetColor(0, 0, 0);
		iText(395, 520, arr, GLUT_BITMAP_TIMES_ROMAN_24);
		iText(395 + 11 * index, 520, "_", GLUT_BITMAP_TIMES_ROMAN_24);

	}

	else if (scene == 3)			//leaderboard
	{
		iShowBMP(0, 0, "board1.bmp");

		iShowBMP(0, 150, "board.bmp");
		iShowBMP2(650, 50, "33.bmp", 0); //changing
		iShowBMP2(0, 50, "back.bmp", 0);
		iShowBMP(0, 600, "board2.bmp");
		iSetColor(0, 255, 0);
		int y_co = 240;
		iText(350, 250, "NAME", GLUT_BITMAP_TIMES_ROMAN_24);
		iLine(350, y_co, 420, y_co);
		iText(500, 250, "MOVES", GLUT_BITMAP_TIMES_ROMAN_24);
		iLine(500, y_co, 590, y_co);
		iSetColor(255, 192, 203);

		FILE *ifp = fopen("score.txt", "r");
		if (ifp == NULL)	printf("Cant open ifp");
		else
		{
			for (int i = 0; i < 3; i++)
			{
				char name[150];
				char point[10];
				int v;
				fgets(name, 200, ifp);
				fgets(point, 8, ifp);

				iText(350, 200 - i * 50, name, GLUT_BITMAP_TIMES_ROMAN_24);
				iText(520, 200 - i * 50, point, GLUT_BITMAP_TIMES_ROMAN_24);
			}
			fclose(ifp);
		}

	}
	else if (scene == -3)	//settings
	{
		iShowBMP(0, 0, "set.bmp");

		iSetColor(0, 0, 0);
		iFilledRectangle(60, 80, 140, 50);
		iShowBMP2(0, 50, "back.bmp", 0);

		iFilledRectangle(100, 400, 200, 50);
		iFilledRectangle(100, 300, 200, 50);
		iSetColor(0, 0, 0);
		iText(40, 600, "In Easy Mode, you will be able to see your target image in the side window.", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(40, 550, "Otherwise the picture will not be shown. ", GLUT_BITMAP_TIMES_ROMAN_24);
		iSetColor(0, 255, 0);
		iText(140, 415, "Easy Mode", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(160, 315, "Music", GLUT_BITMAP_TIMES_ROMAN_24);

		iSetColor(255, 0, 0);
		if (color1 == 0)		iSetColor(0, 0, 0);
		iFilledCircle(520, 420, 30, 100);

		iSetColor(0, 0, 0);
		if (color2 == 1)		iSetColor(255, 0, 0);
		iFilledCircle(720, 420, 30, 100);

		iSetColor(255, 0, 0);
		if (color3 == 0)		iSetColor(0, 0, 0);
		iFilledCircle(520, 320, 30, 100);

		iSetColor(0, 0, 0);
		if (color4 == 1)		iSetColor(255, 0, 0);
		iFilledCircle(720, 320, 30, 100);



		iSetColor(0, 255, 0);
		iText(500, 410, "ON", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(700, 410, "OFF", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(500, 310, "ON", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(700, 310, "OFF", GLUT_BITMAP_TIMES_ROMAN_24);
	}
	else if (scene == 20)		//if u lose
	{
		iShowBMP(0, 0, "fail.bmp");
		if (music)
		{
			PlaySound("lose.wav", NULL, SND_ASYNC);
			music = false;
		}

		iSetColor(0, 255, 0);

		iText(600, 110, "Match this !", GLUT_BITMAP_TIMES_ROMAN_24);
		iShowBMP(430, 160, "target.bmp");

		iSetColor(255, 0, 0);
		iText(100, 600, "Time up ! You have Lost :) Wanna Try Again? ", GLUT_BITMAP_TIMES_ROMAN_24);
		iShowBMP2(100, 400, "play_again.bmp", 0);
		iShowBMP2(100, 50, "home.bmp", 0);
	}

	else if (scene == 10)			//if u win
	{
		if (music)
		{
			PlaySound("win.wav", NULL, SND_ASYNC);
			music = false;
		}
		iShowBMP(0, 0, "fail.bmp");

		iShowBMP2(320, 150, "play_again.bmp", 0);
		iShowBMP2(320, 50, "home.bmp", 0);


		iSetColor(255, 192, 203);

		iText(30, 580, "Total no of moves needed :", GLUT_BITMAP_TIMES_ROMAN_24);

		iText(315, 580, str, GLUT_BITMAP_TIMES_ROMAN_24);

		iSetColor(0, 255, 0);
		iText(300, 650, "You have Wonnnnnnnnnnn !", GLUT_BITMAP_TIMES_ROMAN_24);
		iSetColor(173, 216, 230);
		iText(720, 80, "Press 0 to quit", GLUT_BITMAP_TIMES_ROMAN_24);
		iSetColor(255, 192, 203);

		iText(30, 500, "LEADERBOARD:", GLUT_BITMAP_TIMES_ROMAN_24);
		iSetColor(255, 255, 255);

		int d_y = 500;
		iText(310, d_y, "NAME", GLUT_BITMAP_TIMES_ROMAN_24);
		iLine(310, d_y - 10, 370, d_y - 10);
		iText(500, d_y, "MOVES", GLUT_BITMAP_TIMES_ROMAN_24);
		iLine(500, d_y - 10, 590, d_y - 10);

		iSetColor(255, 255, 0);
		//lets update		
		if (run == 1)
		{
			FILE *ifp1 = fopen("score.txt", "r");
			FILE *ofp2 = fopen("out.txt", "w");
			int mind = 0;
			//comparing
			char id[150];
			while (fgets(id, 100, ifp1))
			{

				char point[10];
				fgets(point, 8, ifp1);
				int v = atoi(point);

				if (moves<v && mind == 0)
				{
					fputs(arr, ofp2);
					fprintf(ofp2, "\n");
					fputs(str, ofp2);
					fprintf(ofp2, "\n");
					fputs(id, ofp2);
					fputs(point, ofp2);
					mind++;

				}
				else
				{
					fputs(id, ofp2);
					fputs(point, ofp2);
				}

			}
			fclose(ifp1);
			fclose(ofp2);
			FILE *ofp1 = fopen("score.txt", "w");
			FILE *ifp2 = fopen("out.txt", "r");

			char temp[200];
			while (fgets(temp, 150, ifp2))
			{
				fputs(temp, ofp1);
			}
			fclose(ifp2);
			fclose(ofp1);
			run++;
		}

		//show file
		FILE *ifp = fopen("score.txt", "r");
		if (ifp == NULL)	printf("Cant open ifp");
		else
		{
			for (int i = 0; i < 3; i++)
			{
				char name[200];
				char point[10];
				fgets(name, 200, ifp);
				fgets(point, 8, ifp);

				iText(310, 450 - i * 50, name, GLUT_BITMAP_TIMES_ROMAN_24);
				iText(520, 450 - i * 50, point, GLUT_BITMAP_TIMES_ROMAN_24);
			}
		}
		fclose(ifp);


	}

	else if (scene == 0)		// main game
	{

		if (color1 == 1)
		{
			iShowBMP(715, 550, "marker.bmp");
			iText(740, 525, "Easy mode", GLUT_BITMAP_TIMES_ROMAN_24);
		}
		else
		{
			iText(740, 530, "Hard mode", GLUT_BITMAP_TIMES_ROMAN_24);
		}
		iSetColor(144, 238, 144);
		clock_t end = clock();
		double time_diff = (start - end) / CLOCKS_PER_SEC;
		char str2[10];
		sprintf(str2, "%.2lf", time_diff);
		if (time_diff < 1){
			scene = 20;
		}
		iText(730, 450, "TIME :", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(810, 450, str2, GLUT_BITMAP_TIMES_ROMAN_24);

		iSetColor(149, 33, 246);
		iFilledRectangle(0, 0, 700, 700);
		iSetColor(255, 255, 255);
		iText(740, 330, "MOVES ->", GLUT_BITMAP_TIMES_ROMAN_24);
		sprintf(str, "%i", moves);
		iSetColor(255, 0, 0);
		iText(780, 300, str, GLUT_BITMAP_TIMES_ROMAN_24);


		iSetColor(255, 255, 0);


		int count = 1;
		for (int i = 0; i<5; i++)
		{
			for (int j = 0; j<5; j++)
			{
				if (i == 0 && j == 0)    continue;
				else
				{
					iShowBMP(pic[count].x, pic[count].y, picture[count]);
					count++;
				}
			}
		}
		check_pic();
		if (correct == true)
		{
			scene = 10;

		}

	}


}

void iMouseMove(int mx, int my){
	//place your codes here
}
void iMouse(int button, int state, int mx, int my)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (scene == -1)		//intro
		{
			if (mx >= 300 && mx <= 600 && my >= 400 && my <= 520)
			{
				scene = 100;    //name				
			}
			else if (mx >= 300 && mx <= 600 && my >= 300 && my <= 420)
			{
				scene = 1;  //instructions
			}
			else if (mx >= 300 && mx <= 600 && my >= 200 && my <= 320)
			{
				scene = 3;   //leaderboard
			}
			else if (mx >= 300 && mx <= 600 && my >= 80 && my <= 80 + 126)
			{
				scene = -3;   //settings
			}
		}
		else if (scene == 1)
		{
			if (mx >= 100 && mx <= 100 + 250 && my >= 400 && my <= 500)
			{
				scene = 100;
			}
			else if (mx >= 650 && mx <= 900 && my >= 50 && my <= 150)
			{
				scene = -1;

			}
		}
		else if (scene == 0)
		{
			PlaySound("click.wav", NULL, SND_ASYNC);
			moves++;
			int tempx = (mx / 140) * 140;
			int tempy = (my / 140) * 140;
			for (int i = 1; i<25; i++)
			{
				if (pic[i].x == tempx && pic[i].y == tempy)
				{
					pic[i].x = openx;
					pic[i].y = openy;
					openx = tempx;
					openy = tempy;
					break;
				}

			}
		}

		else if (scene == 20)       //if u lose
		{
			if (mx >= 100 && mx <= 350 && my >= 400 && my <= 500)
			{

				scene = 100;
				//music = true;
			}
			else if (mx >= 100 && mx <= 350 && my >= 50 && my <= 150)
			{
				scene = -1;
			}
		}
		else if (scene == 3)		//leaderboard
		{
			if (mx >= 650 && mx <= 900 && my >= 50 && my <= 150)
			{
				scene = 100;
			}

			else if (mx >= 0 && mx <= 250 && my >= 50 && my <= 150)
			{
				scene = -1;
			}
		}
		else if (scene == 100)		//enter name
		{
			if (mx >= 200 && mx <= 500 && my >= 200 && my <= 320)
			{
				music = true;
				run = 1;
				coordinates();
				location_change();
				openx = 0, openy = 560;
				moves = 0;
				PlaySound(0, 0, 0);
				start = clock() + 31000;
				scene = 0;
			}
			else if (mx >= 0 && mx <= 250 && my >= 50 && my <= 150)
			{
				scene = -1;
			}

		}
		else if (scene == -3)
		{

			if (mx >= 0 && mx <= 250 && my >= 50 && my <= 150)
			{
				scene = -1;
			}
			int r = 40;
			if (mx >= 520 - r && mx <= 520 + r && my >= 420 - r && my <= 420 + r)
			{
				color1 = 1;
				color2 = 0;
			}
			else if (mx >= 720 - r && mx <= 720 + r && my >= 420 - r && my <= 420 + r)
			{
				color1 = 0;
				color2 = 1;
			}
			if (mx >= 520 - r && mx <= 520 + r && my >= 320 - r && my <= 320 + r)
			{
				color3 = 1;
				color4 = 0;
				PlaySound("bg_music.wav", NULL, SND_ASYNC);
			}
			else if (mx >= 720 - r && mx <= 720 + r && my >= 320 - r && my <= 320 + r)
			{
				color3 = 0;
				color4 = 1;
				PlaySound(0, 0, 0);
			}

		}
		else if (scene == 10)
		{
			if (mx >= 320 && mx <= 320 + 250 && my >= 160 && my <= 260)
			{
				scene = 100;
			}
			if (mx >= 320 && mx <= 320 + 250 && my >= 50 && my <= 150)
			{
				scene = -1;
			}
		}
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
	}
}



void iKeyboard(unsigned char key) {
	if (key == '0'){
		exit(0);
	}
	if (scene != 100)
	{
		if (key == '1'){
			PlaySound(0, 0, 0);
		}
		if (key == '2'){
			PlaySound("bg_music.wav", NULL, SND_ASYNC);
		}
	}

	else if (scene == 100)
	{
		if (key != '\b')
		{
			arr[index] = key;
			index++;
			arr[index] = '\0';
		}
		else
		{
			if (index > 0)
			{
				index--;
				arr[index] = '\0';

			}
			else
			{
				index = 0;
			}
		}
	}


}
void iSpecialKeyboard(unsigned char key) {
	if (key == GLUT_KEY_END) {
		//exit(0);
	}
}

void location_change()
{
	int a = 2, b = 25;
	int box[6];
	srand(time(NULL));

	for (int i = 0; i<6; i++)
	{
		box[i] = rand() % (b - a) + a;
	label:
		for (int j = 0; j<i; j++)
		{
			if (box[i] == box[j])
			{
				box[i] = rand() % (b - a) + a;
				goto label;
			}
		}
		printf("%d\n", box[i]);
	}
	for (int i = 0; i<6; i = i + 2)
	{
		pic[box[i]].x = correct_pic[box[i + 1]].x;
		pic[box[i]].y = correct_pic[box[i + 1]].y;
		//printf("%d got %d's coordinates\n",box[i],box[i+1]);
		pic[box[i + 1]].x = correct_pic[box[i]].x;
		pic[box[i + 1]].y = correct_pic[box[i]].y;

	}

}
void coordinates()
{
	int n = 0;
	for (int i = 0; i<5; i++)
	{
		for (int j = 0; j<5; j++)
		{
			pic[n].x = 0 + j * 140;		//storing real addresses
			pic[n].y = 560 - i * 140;
			correct_pic[n].x = pic[n].x;	//storing real addresses
			correct_pic[n].y = pic[n].y;
			n++;

		}
	}
}
void check_pic()
{
	int n = 1;
	correct = true;
	for (int i = 0; i<5; i++)
	{
		for (int j = 0; j<5; j++)
		{
			if (i == 0 && j == 0)    continue;
			else
			{
				if (pic[n].x != correct_pic[n].x)
				{
					correct = false;
					break;
				}
				if (pic[n].y != correct_pic[n].y)
				{
					correct = false;
					break;
				}
				n++;
			}

		}
	}
}
int main()
{
	coordinates();
	PlaySound("bg_music.wav", NULL, SND_ASYNC);
	iInitialize(900, 700, "Matching puzzles");
	return 0;
}


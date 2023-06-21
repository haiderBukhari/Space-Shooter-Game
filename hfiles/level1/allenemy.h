#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string.h>
using namespace sf;
using namespace std;

#if !defined(ALLENEMY_H)
#define ALLENEMY_H

class Enemies
{
private:
	int x = 340;
	int y = 557;

public:
	int arras[14] = {13};
	bool arrs1[14] = {false};
	bool arrs2[14] = {false};
	Texture enemys;
	int count[14] = {0};
	int arra[14] = {0};
	
	Texture tex2, enemyy[14];
	Sprite sprite2, enemy[14], enemy2[14];
	int speed;
	///////////////////////////////////////////////////////////
	Enemies()
	{
		// Cloud Computing
		// tex2.loadFromFile("./img/dragon2.png");
		// sprite2.setTexture(tex2);
		// sprite2.setScale(sf::Vector2f(0.5f, 0.5f));
		// sprite2.setPosition(sf::Vector2f(200, 0));
		// float xx = 3981, yy = 5591;
	}
	void enemies()
	{
		// for (int i = 0; i < 14; i++)
		// {
		// 	enemyy[i].loadFromFile("./img/enemy_1.png");
		// 	enemy[i].setTexture(enemyy[i]);
		// 	enemy[i].setScale(sf::Vector2f(0.5f, 0.5f));
		// }
	}
	virtual void reset(float xx, float yy, int xx_pos) = 0;
	virtual bool move_downward(int **array, float xx = 0, float yy = 0) = 0;
	virtual bool check_enemy(int **array) = 0;
	virtual void move_left_and_right() = 0;
	
	virtual void specify_values(int **array) = 0;
	virtual void check_array(int **array) = 0;
	virtual void check_enemy(int **array, int j, int i)=0;
	virtual void bombs(int alph) = 0;
};

class Dragon : public Enemies
{
private:
Texture texture, texture1, texture2, beam1, setlight;
public:
	bool dragon_show = false;
	int pos_x = 0;
	int count = 685;
	float a, b, a1, b0, a2, b2;
	int counts = 0;
	Sprite sprites, beam[10], sprites1, sprites2, light[4];
	
	Dragon()
	{
		beam1.loadFromFile("./explosion.png");
		texture.loadFromFile("./img/dragon2.png");
		sprites.setTexture(texture);
		sprites.setScale(sf::Vector2f(0.5f, 0.5f));
		sprites.setPosition(sf::Vector2f(200, 0));
		

		for(int i=0; i<5; i++){
			beam[i].setTexture(beam1);
			beam[i].setScale(0.16f, 0.16f);
			beam[i].setPosition(320,190+30*i);
		}
		for(int i=5; i<10; i++){
			beam[i].setTexture(beam1);
			beam[i].setScale(0.16f, 0.16f);
			beam[i].setPosition(350,190+30*(i-5));
		}
		
		texture1.loadFromFile("img/enemy_2.png");
		sprites1.setTexture(texture1);
		sprites1.setScale(0.5f, 0.5f);
		sprites1.setPosition(150, 240);

		texture2.loadFromFile("img/enemy_2.png");
		sprites2.setTexture(texture2);
		sprites2.setScale(0.5f, 0.5f);
		sprites2.setPosition(600, 240);

		
		setlight.loadFromFile("img/PNG/Lasers/laserRed09.png");
		light[0].setTexture(setlight);
		light[0].setScale(0.7f, 0.7f);
		light[0].setPosition(165, 295);
		light[1].setTexture(setlight);
		light[1].setScale(0.7f, 0.7f);
		light[1].setPosition(600, 295);
	}
	void reset(float xx, float yy, int xx_pos)
	{
		light[0].setPosition(165, 295);
		light[1].setPosition(600, 295);
		pos_x = xx_pos;
		count = 160;
		for(int i=0; i<5; i++){
			beam[i].setPosition(320,190+30*i);
		}
		for(int i=5; i<10; i++){
			beam[i].setPosition(350,190+30*(i-5));
		}
		dragon_show = true;
		a = 7628 - 3997;
		float b1 = 7628 - xx;
		a = (a - b1)/3000;
		b = (3997-xx)/3475.652173913;

		a1 = 7628-1902;
		b1 = 7628-xx;
		a1 = (a1-b1)/2430;
		b0 = (1902-xx)/1953;

		a2 = 7628-6483;
		b1 = 7628-xx;
		a2 = (a2-b1)/1446.02;
		b2 = (6483-xx)/2637.39;
	}
	bool move_downward(int **array, float xx = 0, float yy = 0){
		if(count<884){
			if(xx<1902){
				light[0].move(-1*b0, 1.2);
			}
			else{
				light[0].move(a1, 1.2);
			}
			if(xx<6483){
				light[1].move(-1*b2, 1.2);
			}
			else{
				light[1].move(a2, 1.2);
			}
			if(xx<=3997){
				for(int i=0; i<10; i++){
					beam[i].move(-1*b, 1.2);
				}
			}
			else{
				for(int i=0; i<10; i++){
					beam[i].move(a, 1.2);
				}
			}
			// light[0].move((a+b), 1.4); 
			int((count++)/33.15);
		}
		else{
			dragon_show = false;
			return false;
		}
	}
	void specify_values(int **array){
		for(int j=1; j<=6; j++){
			array[j][5] = 13;
			array[j][6] = 13;
			array[j][7] = 13;
		}
		for(int j=0; j<=8; j++){
			array[j][8] = 13;
			array[j][9] = 13;
			array[j][11] = 13;
			array[j][12] = 13;
		}
		for(int j=1; j<=7; j++){
			array[j][10] = 13;
		}
		array[8][13] = 13;
		array[7][13] = 13;
	}
	
	bool check_enemy(int **array){
		if(count<684){
			for(int i=0; i<5; i++){
				if(array[(int((count)/33.15)+i)>20?20:(int((count)/33.15)+i)][pos_x]==11){
					count = 695;
					dragon_show = false;
					return false;
				}
				if(array[(int((count)/33.15)+i)>20?20:(int((count)/33.15)+i)][pos_x+1]==11){
					count = 695;
					dragon_show = false;
					return false;
				}
			}
			return !false;
		}
		return !false;
	}
	void check_array(int **array){}
	void check_enemy(int **array, int j, int i){}
	void bombs(int alph){}
	void move_left_and_right(){}
};
class main_invader:public Enemies
{
public:
	virtual void reset(float xx, float yy, int xx_pos) = 0;
	virtual bool move_downward(int **array, float xx = 0, float yy = 0) = 0;
	virtual bool check_enemy(int **array) = 0;
	virtual void move_left_and_right() = 0;
	
	virtual void specify_values(int **array) = 0;
	virtual void check_array(int **array) = 0;
	virtual void check_enemy(int **array, int j, int i)=0;
	virtual void bombs(int alph) = 0;
};

class aLpha_invaders:public main_invader{
public:
	float speed = 1; 
};
class beta_invaders:public main_invader{
public:
	float speed = 1.5;
};
class gamma_invaders:public main_invader{
public:
	float speed = 2;
};

class Invader : public aLpha_invaders
{
private:
public:
	void bombs(int alph)
	{
		if (alph == 1)
		{
			int beeta = 0;
			for (int i = 1; i <= 2; i++)
			{
				float alpha = i == 1 ? 0 : i == 2 ? 10
												  : 0;
				for (int j = 1; j <= 4; j++)
				{
					enemy2[beeta].setPosition((199.05 * alpha) / 5.10 + 15, 30.65 + 6 + 35);
					enemy[beeta].setPosition((199.05 * alpha) / 5.10, 30.65);
					alpha += 2.5;
					beeta++;
				}
			}
			enemy2[8].setPosition(sf::Vector2f((199.05) / 5.10 + 10 + 15, 30.65 * 3 + 55));
			enemy2[9].setPosition(sf::Vector2f((199.05 * 4) / 5.10 - 5 + 15, 30.65 * 3 + 10 + 35));
			enemy2[10].setPosition(sf::Vector2f((199.05 * 7) / 5.10 + 10 + 15, 30.65 * 3 + 10 + 35));
			enemy2[11].setPosition(sf::Vector2f((199.05 * 12) / 5.10 + 15, 30.65 * 3 + 10 + 35));
			enemy2[12].setPosition(sf::Vector2f((199.05 * 15) / 5.10 + 10 + 15, 30.65 * 3 + 10 + 35));
			enemy2[13].setPosition(sf::Vector2f((199.05 * 18) / 5.10 + 13 + 15, 30.65 * 3 + 10 + 35));

			enemy[8].setPosition(sf::Vector2f((199.05) / 5.10 + 10, 30.65 * 3));
			enemy[9].setPosition(sf::Vector2f((199.05 * 4) / 5.10 - 5, 30.65 * 3));
			enemy[10].setPosition(sf::Vector2f((199.05 * 7) / 5.10 + 10, 30.65 * 3));
			enemy[11].setPosition(sf::Vector2f((199.05 * 12) / 5.10, 30.65 * 3));
			enemy[12].setPosition(sf::Vector2f((199.05 * 15) / 5.10 + 10, 30.65 * 3));
			enemy[13].setPosition(sf::Vector2f((199.05 * 18) / 5.10 + 13, 30.65 * 3));
		}
		else if (alph == 2)
		{
			enemy2[0].setPosition(200, 230);
			enemy2[1].setPosition(270, 130);
			enemy2[2].setPosition(340, 70);
			enemy2[3].setPosition(410, 150);
			enemy2[4].setPosition(480, 230);
			enemy2[5].setPosition(410, 310);
			enemy2[6].setPosition(340, 390);
			enemy2[7].setPosition(270, 310);
			for (int i = 8; i < 14; i++)
			{
				enemy2[i].setPosition(-200, -200);
			}
		}
		else
		{
			enemy2[0].setPosition(250, 70);
			enemy2[5].setPosition(490, 70);

			enemy2[1].setPosition(310, 140);
			enemy2[6].setPosition(410, 140);

			enemy2[2].setPosition(350, 210);

			enemy2[3].setPosition(410, 280);
			enemy2[7].setPosition(310, 280);

			enemy2[4].setPosition(490, 350);
			enemy2[8].setPosition(250, 350);
		}
	}
	Invader()
	{
		enemys.loadFromFile("./img/enemy_1.png");
		for (int i = 0; i < 14; i++)
		{
			arra[i] = 13;
		}
		for (int i = 0; i < 14; i++)
		{
			enemy[i].setTexture(enemys);
			enemy[i].setScale(sf::Vector2f(0.5f, 0.5f));
			tex2.loadFromFile("./img/enemy_laser.png");
			enemy2[i].setTexture(tex2);
		}
	}
	void specify_values(int **array)
	{
		for (int i = 0; i < 14; i++)
		{
			arrs1[i] = false;
		}
		for (int i = 0; i < 14; i++)
		{
			arra[i] = 13;
		}
		array[3][0] = array[3][1] = array[3][3] = array[3][5] = array[3][6] = array[3][8] = array[3][10] = array[3][11] = array[3][13] = array[3][15] = array[3][17] = 13;

		array[4][0] = array[4][1] = array[4][3] = array[4][5] = array[4][6] = array[4][8] = array[4][10] = array[4][11] = array[4][13] = array[4][15] = array[4][17] = 13;

		array[5][2] = array[5][4] = array[5][5] = array[5][7] = array[5][12] = array[5][15] = array[5][18] = array[5][19] = 13;

		array[6][2] = array[6][4] = array[6][5] = array[6][7] = array[6][8] = array[6][12] = array[6][15] = array[6][18] = array[6][19] = 13;
	}
	void check_array(int **array)
	{
		array[3][0] = array[3][1] = array[4][0] = array[4][1] = arra[0];
		array[5][2] = array[6][2] = arra[1];
		array[3][3] = array[3][4] = array[4][3] = array[4][4] = arra[2];
		array[5][4] = array[5][5] = array[6][4] = array[6][5] = arra[3];
		array[5][6] = array[5][5] = array[4][6] = array[4][5] = array[3][6] = array[3][5] = arra[4];
		array[5][7] = array[5][8] = array[6][7] = array[6][8] = arra[5];
		array[3][8] = array[4][8] = arra[6];
		array[3][10] = array[3][11] = array[4][10] = array[4][11] = arra[7];
		array[5][12] = array[6][12] = arra[8];
		array[3][13] = array[4][13] = arra[9];
		array[5][15] = array[6][15] = arra[10];
		array[3][15] = array[4][15] = arra[11];
		array[5][18] = array[5][19] = array[6][18] = array[6][19] = arra[12];
		array[3][17] = array[4][17] = arra[13];
	}
	void check_enemy(int **array, int j, int i)
	{
		if ((j == 3 || j == 4) && (i == 0 || i == 1))
		{arrs1[0] = true;arra[0] = 0;array[3][0] = array[3][1] = array[4][0] = array[4][1] = 0;}
		if ((j == 5 || j == 6) && (i == 2))
		{arra[1] = 0;arrs1[8] = true;array[5][2] = array[6][2] = 0;}
		if ((j == 3 || j == 4) && (i == 3 || i == 4))
		{arra[2] = 0;arrs1[1] = true;array[3][3] = array[3][4] = array[4][3] = array[4][4] = 0;}
		if ((j == 5 || j == 6) && (i == 4 || i == 5))
		{arra[3] = 0;arrs1[9] = true;array[5][4] = array[5][5] = array[6][4] = array[6][5] = 0;}
		if ((j == 5 || j == 4) && (i == 6 || i == 5))
		{arra[4] = 0;arrs1[2] = true;array[5][6] = array[5][5] = array[4][6] = array[4][5] = array[3][6] = array[3][5] = 0;}
		if ((j == 5 || j == 6) && (i == 7 || i == 8))
		{arra[5] = 0;arrs1[10] = true;array[5][7] = array[5][8] = array[6][7] = array[6][8] = 0;}
		if ((j == 3 || j == 4) && (i == 8))
		{arra[6] = 0;arrs1[3] = true;array[3][8] = array[4][8] = 0;}
		if ((j == 3 || j == 4) && (i == 10 || i == 11))
		{arra[7] = 0;arrs1[4] = true;array[3][10] = array[3][11] = array[4][10] = array[4][11] = 0;}
		if ((j == 5 || j == 6) && (i == 12))
		{arra[8] = 0;arrs1[11] = true;array[5][12] = array[6][12] = 0;}
		if ((j == 3 || j == 4) && (i == 13))
		{arra[9] = 0;arrs1[5] = true;array[3][13] = array[4][13] = 0;}
		if ((j == 5 || j == 6) && (i == 15))
		{arra[10] = 0;arrs1[12] = true;array[5][15] = array[6][15] = 0;}
		if ((j == 3 || j == 4) && (i == 15))
		{arra[11] = 0;arrs1[6] = true;array[3][15] = array[4][15] = 0;}
		if ((j == 5 || j == 6) && (i == 18 || i == 19))
		{arra[12] = 0;arrs1[13] = true;array[5][18] = array[5][19] = array[6][18] = array[6][19] = 0;}
		if ((j == 3 || j == 4) && (i == 17))
		{arra[13] = 0;arrs1[7] = true;array[3][17] = array[4][17] = 0;}
	}
	void reset(float xx, float yy, int xx_pos){}
	bool move_downward(int **array, float xx = 0, float yy = 0){}
	bool check_enemy(int **array){}
	void move_left_and_right(){}
};
class alpha_inavder_triangle : public beta_invaders
{
public:
	alpha_inavder_triangle()
	{
		enemys.loadFromFile("./img/enemy_2.png");
		for (int i = 0; i < 9; i++)
		{
			arras[i] = 13;
			arra[i] = 13;
			enemy[i].setTexture(enemys);
			enemy[i].setScale(sf::Vector2f(0.5f, 0.5f));
			int beeta = 0;
		}
		enemy[0].setPosition(sf::Vector2f(200, 200));
		enemy[1].setPosition(sf::Vector2f(270, 120));
		enemy[2].setPosition(sf::Vector2f(340, 40));
		enemy[3].setPosition(sf::Vector2f(410, 120));
		enemy[4].setPosition(sf::Vector2f(480, 200));
		enemy[5].setPosition(sf::Vector2f(410, 280));
		enemy[6].setPosition(sf::Vector2f(340, 360));
		enemy[7].setPosition(sf::Vector2f(270, 280));
		enemy[8].setPosition(sf::Vector2f(-200, -200));
	}
	void specify_values(int **array)
	{
		array[14][9] = arras[6];
		array[2][9] = arras[2];
		array[11][7] = arras[7];
		array[7][8] = arras[1];
		array[11][11] = arras[5];
		array[6][11] = arras[3];
		array[9][5] = arras[0];
		array[9][6] = arras[0];
		array[8][12] = arras[4];
	}

	void check_enemy(int **array, int j, int i)
	{
		bool a = false;
		if (j == 14 && i == 9)
		{arras[6] = 0;a = true;arrs1[6] = true;}
		else if (j == 2 && i == 9)
		{arras[2] = 0;a = true;arrs1[2] = true;}
		else if (j == 11 && i == 7)
		{arras[7] = 0;a = true;arrs1[7] = true;}
		else if (j == 7 && i == 8)
		{arras[1] = 0;a = true;arrs1[1] = true;}
		else if (j == 11 && i == 11)
		{arras[5] = 0;a = true;arrs1[5] = true;}
		else if (j == 6 && i == 11)
		{arras[3] = 0;a = true;arrs1[3] = true;}
		else if (j == 9 && (i == 5 || i == 6))
		{arras[0] = 0;a = true;array[5][9] = 0, array[6][9] = 0;arrs1[0] = true;}
		else if (j == 8 && i == 12)
		{arras[4] = 0;a = true;arrs1[4] = true;}
		if (a){array[i][j] = 0;}
		return;
	}
	void check_array(int **array){}
	void bombs(int alph){}
	void reset(float xx, float yy, int xx_pos){}
	bool move_downward(int **array, float xx = 0, float yy = 0){}
	bool check_enemy(int **array){}
	void move_left_and_right(){}
};

class cross_invader : public gamma_invaders
{
public:
	cross_invader()
	{
		enemys.loadFromFile("./img/enemy_3.png");
		for (int i = 0; i < 9; i++)
		{
			arras[i] = 13;
			arrs1[i] = false;
			enemy[i].setTexture(enemys);
			enemy[i].setScale(sf::Vector2f(0.4f, 0.4f));
			int beeta = 0;
		}
		enemy[0].setPosition(250, 40);
		enemy[5].setPosition(490, 40);
		enemy[1].setPosition(310, 110);
		enemy[6].setPosition(410, 110);
		enemy[2].setPosition(350, 180);
		enemy[3].setPosition(410, 250);
		enemy[7].setPosition(310, 250);
		enemy[4].setPosition(490, 320);
		enemy[8].setPosition(250, 320);
	}
	void specify_values(int **array)
	{
		array[1][7] = arras[0];
		array[4][8] = arras[1];
		array[7][9] = arras[2];
		array[8][11] = arras[3];
		array[11][12] = arras[4], array[11][13] = arras[4];
		array[1][13] = arras[5];
		array[4][11] = arras[6];
		array[9][8] = arras[7];
		array[11][7] = arras[8];
	}

	void check_enemy(int **array, int i, int j)
	{
		bool a = false;
		if (j == 7 && i == 1)
		{arras[0] = 0;a = true;arrs1[0] = true;}
		else if (j == 8 && i == 4)
		{arras[1] = 0;a = true;arrs1[1] = true;}
		else if (j == 9 && i == 7)
		{arras[2] = 0;a = true;arrs1[2] = true;}
		else if (j == 11 && i == 8)
		{arras[3] = 0;a = true;arrs1[3] = true;}
		else if ((j == 12 || j == 13) && i == 11)
		{arras[4] = 0;a = true;arrs1[4] = true;array[13][12] = 0, array[11][12] = 0;}
		else if (j == 13 && i == 1)
		{arras[5] = 0;a = true;arrs1[5] = true;}
		else if (j == 11 && i == 4)
		{arras[6] = 0;a = true;arrs1[6] = true;}
		else if (j == 8 && i == 9)
		{arras[7] = 0;a = true;arrs1[7] = true;}
		else if (j == 7 && i == 11)
		{arras[8] = 0;a = true;arrs1[8] = true;}
		if (a){array[j][i] = 0;}
		return;
	}
	void check_array(int **array){}
	void bombs(int alph){}
	void reset(float xx, float yy, int xx_pos){}
	bool move_downward(int **array, float xx = 0, float yy = 0){}
	bool check_enemy(int **array){}
	void move_left_and_right(){}
};


class circle_enemy:public aLpha_invaders{
public:
	circle_enemy(){
		enemys.loadFromFile("./img/enemy_2.png");
		for (int i = 0; i < 9; i++)
		{
			arras[i] = 13;
			arra[i] = 13;
			enemy[i].setTexture(enemys);
			enemy[i].setScale(sf::Vector2f(0.5f, 0.5f));
			int beeta = 0;
		}
		enemy[0].setPosition(200, 200);
		enemy[1].setPosition(230, 90);
		enemy[2].setPosition(340, 40);
		enemy[3].setPosition(450, 90);
		enemy[4].setPosition(480, 200);
		enemy[5].setPosition(440, 300);
		enemy[6].setPosition(340, 360);
		enemy[7].setPosition(240, 300);
		enemy[8].setPosition(-200, -200);
	}
	void specify_values(int **array)
	{
		array[9][6] = arras[0];
		array[6][7] = arras[1], array[6][6] = arras[1];
		array[2][9] = arras[2];
		array[6][12] = arras[3];  
		array[8][12] = arras[4];
		array[12][11] = arras[5];
		array[14][9] = arras[6];
		array[12][7] = arras[7];
		// array[11][7] = arras[8];
	}
	void check_enemy(int **array, int j, int i)
	{
		bool a = false;
		if (j == 14 && i == 9)
		{arras[6] = 0;a = true;arrs1[6] = true;}
		else if (j == 2 && i == 9)
		{arras[2] = 0;a = true;arrs1[2] = true;}
		else if (j == 12 && i == 7)
		{arras[7] = 0;a = true;arrs1[7] = true;}
		else if (j == 6 && (i == 6||i==7))
		{arras[1] = 0;a = true;arrs1[1] = true;}
		else if (j == 12 && i == 11)
		{arras[5] = 0;a = true;arrs1[5] = true;}
		else if (j == 6 && i == 12)
		{arras[3] = 0;a = true;arrs1[3] = true;}
		else if (j == 9 && i==6)
		{arras[0] = 0;a = true;arrs1[0] = true;}
		else if (j == 8 && i == 12)
		{arras[4] = 0;a = true;arrs1[4] = true;}
		if (a){array[i][j] = 0;}
		return;
	}
	void check_array(int **array){}
	void bombs(int alph){}
	void reset(float xx, float yy, int xx_pos){}
	bool move_downward(int **array, float xx = 0, float yy = 0){}
	bool check_enemy(int **array){}
	void move_left_and_right(){}
};

class circle_filled_enemy:public gamma_invaders{
public:
	circle_filled_enemy(){
		enemys.loadFromFile("./img/enemy_2.png");
		for (int i = 0; i < 12; i++)
		{
			arras[i] = 13;
			arra[i] = 13;
			enemy[i].setTexture(enemys);
			enemy[i].setScale(sf::Vector2f(0.5f, 0.5f));
			int beeta = 0;
		}
		enemy[0].setPosition(200, 200);
		enemy[1].setPosition(230, 90);
		enemy[2].setPosition(340, 40);
		enemy[3].setPosition(450, 90);
		enemy[4].setPosition(480, 200);
		enemy[5].setPosition(440, 300);
		enemy[6].setPosition(340, 360);
		enemy[7].setPosition(240, 300);

		enemy[8].setPosition(290, 200);
		enemy[9].setPosition(380, 200);
		enemy[10].setPosition(340, 270);
		enemy[11].setPosition(340, 120);
	
	}
	void specify_values(int **array)
	{
		array[9][6] = arras[0];
		array[6][7] = arras[1], array[6][6] = arras[1];
		array[2][9] = arras[2];
		array[6][12] = arras[3];  
		array[8][12] = arras[4];
		array[12][11] = arras[5];
		array[14][9] = arras[6];
		array[12][7] = arras[7];
		array[9][8] = arras[8];
		array[9][10] = arras[9];
		array[7][9] = arras[10];
		array[11][9] = arras[11];
		// array[11][7] = arras[8];
	}
	void check_enemy(int **array, int j, int i)
	{
		bool a = false;
		if (j == 14 && i == 9)
		{arras[6] = 0;a = true;arrs1[6] = true;}
		else if (j == 2 && i == 9)
		{arras[2] = 0;a = true;arrs1[2] = true;}
		else if (j == 12 && i == 7)
		{arras[7] = 0;a = true;arrs1[7] = true;}
		else if (j == 6 && (i == 6||i==7))
		{arras[1] = 0;a = true;arrs1[1] = true;}
		else if (j == 12 && i == 11)
		{arras[5] = 0;a = true;arrs1[5] = true;}
		else if (j == 6 && i == 12)
		{arras[3] = 0;a = true;arrs1[3] = true;}
		else if (j == 9 && i==6)
		{arras[0] = 0;a = true;arrs1[0] = true;}
		else if (j == 8 && i == 12)
		{arras[4] = 0;a = true;arrs1[4] = true;}
		else if (j == 9 && i == 8)
		{arras[8] = 0;a = true;arrs1[8] = true;}
		else if (j == 9 && i == 10)
		{arras[9] = 0;a = true;arrs1[9] = true;}
		else if (j == 7 && i == 9)
		{arras[10] = 0;a = true;arrs1[10] = true;}
		else if (j == 11 && i == 9)
		{arras[11] = 0;a = true;arrs1[11] = true;}
		if (a){array[i][j] = 0;}
		return;
	}
	void check_array(int **array){}
	void bombs(int alph){}
	void reset(float xx, float yy, int xx_pos){}
	bool move_downward(int **array, float xx = 0, float yy = 0){}
	bool check_enemy(int **array){}
	void move_left_and_right(){}
};

class heart_enemy:public beta_invaders{
Texture enemyy;
public:
	heart_enemy(){
		enemyy.loadFromFile("./img/enemy_2.png");
		for (int i = 0; i < 9; i++)
		{
			arras[i] = 13;
			arra[i] = 13;
			enemy[i].setTexture(enemyy);
			enemy[i].setScale(sf::Vector2f(0.5f, 0.5f));
			int beeta = 0;
		}
		enemy[0].setPosition(200, 200);
		enemy[1].setPosition(270, 120);
		enemy[2].setPosition(340, 170);
		enemy[3].setPosition(410, 120);
		enemy[4].setPosition(480, 200);
		enemy[5].setPosition(410, 280);
		enemy[6].setPosition(340, 360);
		enemy[7].setPosition(270, 280);
		// enemy[8].setPosition(-200, -200);
	}
	void specify_values(int **array)
	{
		array[9][6] = arras[0];
		array[7][7] = arras[1];
		array[9][9] = arras[2];
		array[7][11] = arras[3];  
		array[9][13] = arras[4];
		array[11][11] = arras[5];
		array[14][9] = arras[6];
		array[12][7] = arras[7];
	}
	void check_enemy(int **array, int j, int i)
	{
		bool a = false;
		if (j == 14 && i == 9)
		{arras[6] = 0;a = true;arrs1[6] = true;}
		else if (j == 9 && i == 9)
		{arras[2] = 0;a = true;arrs1[2] = true;}
		else if (j == 12 && i == 7)
		{arras[7] = 0;a = true;arrs1[7] = true;}
		else if (j == 7 && i == 7)
		{arras[1] = 0;a = true;arrs1[1] = true;}
		else if (j == 11 && i == 11)
		{arras[5] = 0;a = true;arrs1[5] = true;}
		else if (j == 7 && i == 11)
		{arras[3] = 0;a = true;arrs1[3] = true;}
		else if (j == 9 && i==6)
		{arras[0] = 0;a = true;arrs1[0] = true;}
		else if (j == 9 && i == 13)
		{arras[4] = 0;a = true;arrs1[4] = true;}
		if (a){array[i][j] = 0;}
		return;
	}
	void check_array(int **array){}
	void bombs(int alph){}
	void reset(float xx, float yy, int xx_pos){}
	bool move_downward(int **array, float xx = 0, float yy = 0){}
	bool check_enemy(int **array){}
	void move_left_and_right(){}
};

class triangle_enemy:public gamma_invaders{
public:
	triangle_enemy(){
		enemys.loadFromFile("./img/enemy_2.png");
		for (int i = 0; i < 9; i++)
		{
			arras[i] = 13;
			arra[i] = 13;
			enemy[i].setTexture(enemys);
			enemy[i].setScale(sf::Vector2f(0.5f, 0.5f));
			int beeta = 0;
		}
		enemy[0].setPosition(200, 200);
		enemy[1].setPosition(270, 120);
		enemy[2].setPosition(340, 40);
		enemy[3].setPosition(410, 120);
		enemy[4].setPosition(480, 200);
		enemy[5].setPosition(550, 280);
		enemy[6].setPosition(410, 280);
		enemy[7].setPosition(276, 280);
		enemy[8].setPosition(140, 280);
	}
	void specify_values(int **array)
	{
		array[9][6] = arras[0];
		array[7][7] = arras[1];
		array[5][9] = arras[2];
		array[7][11] = arras[3];  
		array[9][13] = arras[4];
		array[12][4] = arras[5];
		array[13][11] = arras[6];
		array[12][7] = arras[7];
		array[12][14] = arras[8];
	}
	void check_enemy(int **array, int j, int i)
	{
		bool a = false;
		if (j == 13 && i == 11)
		{arras[6] = 0;a = true;arrs1[6] = true;}
		else if (j == 5 && i == 9)
		{arras[2] = 0;a = true;arrs1[2] = true;}
		else if (j == 12 && i == 7)
		{arras[7] = 0;a = true;arrs1[7] = true;}
		else if (j == 7 && i == 7)
		{arras[1] = 0;a = true;arrs1[1] = true;}
		else if (j == 12 && i == 4)
		{arras[5] = 0;a = true;arrs1[5] = true;}
		else if (j == 7 && i == 11)
		{arras[3] = 0;a = true;arrs1[3] = true;}
		else if (j == 9 && i==6)
		{arras[0] = 0;a = true;arrs1[0] = true;}
		else if (j == 9 && i == 13)
		{arras[4] = 0;a = true;arrs1[4] = true;}
		else if (j == 12 && i == 14)
		{arras[8] = 0;a = true;arrs1[8] = true;}
		if (a){array[i][j] = 0;}
		return;
	}
	void check_array(int **array){}
	void bombs(int alph){}
	void reset(float xx, float yy, int xx_pos){}
	bool move_downward(int **array, float xx = 0, float yy = 0){}
	bool check_enemy(int **array){}
	void move_left_and_right(){}
};

class triangle_filled_enemy:public aLpha_invaders{
public:
	triangle_filled_enemy(){
		enemys.loadFromFile("./img/enemy_2.png");
		for (int i = 0; i < 13; i++)
		{
			arras[i] = 13;
			arra[i] = 13;
			enemy[i].setTexture(enemys);
			enemy[i].setScale(sf::Vector2f(0.5f, 0.5f));
			int beeta = 0;
		}
		enemy[0].setPosition(200, 200);
		enemy[1].setPosition(270, 120);
		enemy[2].setPosition(340, 40);
		enemy[3].setPosition(410, 120);
		enemy[4].setPosition(480, 200);
		enemy[5].setPosition(550, 280);
		enemy[6].setPosition(410, 280);
		enemy[7].setPosition(276, 280);
		enemy[8].setPosition(140, 280);
		enemy[9].setPosition(293, 200);
		enemy[10].setPosition(386, 200);
		enemy[11].setPosition(340, 120);
	}
	void specify_values(int **array)
	{
		array[9][6] = arras[0];
		array[7][7] = arras[1];
		array[5][9] = arras[2];
		array[7][11] = arras[3];  
		array[9][13] = arras[4];
		array[12][4] = arras[5];
		array[13][11] = arras[6];
		array[12][7] = arras[7];
		array[12][14] = arras[8];
		array[9][8] = arras[9];
		array[9][10] = arras[10];
		array[7][9] = arras[11];
	}
	void check_enemy(int **array, int j, int i)
	{
		bool a = false;
		if (j == 13 && i == 11)
		{arras[6] = 0;a = true;arrs1[6] = true;}
		else if (j == 5 && i == 9)
		{arras[2] = 0;a = true;arrs1[2] = true;}
		else if (j == 12 && i == 7)
		{arras[7] = 0;a = true;arrs1[7] = true;}
		else if (j == 7 && i == 7)
		{arras[1] = 0;a = true;arrs1[1] = true;}
		else if (j == 12 && i == 4)
		{arras[5] = 0;a = true;arrs1[5] = true;}
		else if (j == 7 && i == 11)
		{arras[3] = 0;a = true;arrs1[3] = true;}
		else if (j == 9 && i==6)
		{arras[0] = 0;a = true;arrs1[0] = true;}
		else if (j == 9 && i == 13)
		{arras[4] = 0;a = true;arrs1[4] = true;}
		else if (j == 12 && i == 14)
		{arras[8] = 0;a = true;arrs1[8] = true;}
		else if (j == 9 && i == 8)
		{arras[9] = 0;a = true;arrs1[9] = true;}
		else if (j == 9 && i == 10)
		{arras[10] = 0;a = true;arrs1[10] = true;}
		else if (j == 7 && i == 9)
		{arras[11] = 0;a = true;arrs1[11] = true;}
		if (a){array[i][j] = 0;}
		return;
	}
	void check_array(int **array){}
	void bombs(int alph){}
	void reset(float xx, float yy, int xx_pos){}
	bool move_downward(int **array, float xx = 0, float yy = 0){}
	bool check_enemy(int **array){}
	void move_left_and_right(){}
};

class Monster:public Enemies{
public:
	bool monster_show = false;
	Texture monster1, beam1;
	Sprite monster, beam[10];
	int pos_x = 0;
	int count = 685;
	float a, b;
	int counts = 0;
	int first = 0;
	Monster(){
		monster1.loadFromFile("./img/monster1.png");
		beam1.loadFromFile("./explosion.png");
		monster.setTexture(monster1);
		for(int i=0; i<5; i++){
			beam[i].setTexture(beam1);
			beam[i].setScale(0.16f, 0.16f);
			beam[i].setPosition(350,260+30*i);
		}
		for(int i=5; i<10; i++){
			beam[i].setTexture(beam1);
			beam[i].setScale(0.16f, 0.16f);
			beam[i].setPosition(390, 260+30*(i-5));
		}
		monster.setScale(0.4f, 0.4f);
		monster.setPosition(250, 30);
	}
	void move_left_and_right(){
		counts++;
		if(counts<=600 && first==0){
			monster.move(+0.25, 0);
		}
		else if(counts>=600 && counts<=1800 && first==0){
			monster.move(-0.25, 0);
		}
		else if(first==0){
			first = 1;
			counts = 0;
		}
		else if(counts<=1200){
			monster.move(+0.25, 0);
		}
		else if(counts>=1200 && counts<=2400){
			monster.move(-0.25, 0);
		}
		else{
			counts = 0;
		}
	}
	void specify_values(int **array)
	{
		// 8 --- 11
		for(int i=6; i<=14; i++){
			for(int j=1;j<=9;j++){
				array[j][i] = 13;
			}
		}
	}
	void reset(float xx, float yy, int xx_pos){
		pos_x = xx_pos;
		count = 160;
		for(int i=0; i<5; i++){
			beam[i].setPosition(350,260+30*i);
		}
		for(int i=5; i<10; i++){
			beam[i].setPosition(390, 260+30*(i-5));
		}
		monster_show = true;
		a = 7628 - 3997;
		float b1 = 7628 - xx;
		a = (a - b1)/3631;
		b = (3917-xx)/3475.652173913;
	}
	bool move_downward(int **array, float xx = 0, float yy = 0){
		if(count<684){
			// cout<<yy<<endl;
			if(xx<=3997){
				for(int i=0; i<10; i++){
					beam[i].move(-1*b, 1);
				}
			}
			else{
				for(int i=0; i<10; i++){
					beam[i].move(a, 1);
				}
			}
			int((count++)/33.15);
		}
		else{
			monster_show = false;
			return false;
		}
	}
	bool check_enemy(int **array){
		if(count<684){
			for(int i=0; i<5; i++){
				if(array[(int((count)/33.15)+i)>20?20:(int((count)/33.15)+i)][pos_x]==11){
					count = 694;
					return false;
				}
				if(array[(int((count)/33.15)+i)>20?20:(int((count)/33.15)+i)][pos_x+1]==11){
					count = 694;
					return false;
				}
			}
			return !false;
		}
		return !false;
	}
	void check_array(int **array){}
	void check_enemy(int **array, int j, int i){}
	void bombs(int alph){}
};
class animation_level1
{
public:
	int count = 0;
	Texture enemyy[14];
	Sprite enemy[14];
	animation_level1()
	{
		// enemy[0].setPosition((199.05 * 7) / 5.10 + 10, 30.65 * 3);
		enemy[0].setPosition(0, 420);
		for (int i = 0; i < 14; i++)
		{
			enemyy[i].loadFromFile("./img/enemy_1.png");
			enemy[i].setTexture(enemyy[i]);
			enemy[i].setScale(sf::Vector2f(0.5f, 0.5f));
		}
	}
	void first_invader()
	{
	}
};
class Bullets{
public:
bool Bullet(int index, int **arrays, int nm, bool toproceed, int*count, bool *arrs2, Sprite*enemy,Sprite*enemy2)
	{
		int je = 0;
		if (nm == 1)
		{
			int return_rype = true;
			if (index == 0){je = 0;}
			if (index == 1){je = 3;}
			if (index == 2){je = 5;}
			if (index == 3){je = 7;}
			if (index == 4){je = 10;}
			if (index == 5){je = 13;}
			if (index == 6){je = 15;}
			if (index == 7){je = 17;}
			if (index == 8){je = 2;}
			if (index == 9){je = 4;}
			if (index == 10){je = 8;}
			if (index == 11){je = 12;}
			if (index == 12){je = 15;}
			if (index == 13){je = 18;}
			if (index < 8)
			{
				if (arrays[int(count[index] / 14.5)][je] == 11)
				{
					return_rype = false;
				}
				else{
					arrays[int(count[index] / 14.5)][je] = 2;
				}
			}
			else
			{
				if (arrays[int(count[index] / 12.5)][je] == 11)
				{
					return_rype = false;
				}
				else{
					arrays[int(count[index] / 12.5)][je] = 2;
				}
			}

			if (index < 8 ? count[index] > 290 : count[index] > 250 || !return_rype)
			{
				arrs2[index] = true;
				count[index] = 0;
				if (index < 8)
				{
					int beeta = 0;
					for (int i = 1; i <= 2; i++)
					{
						float alpha = i == 1 ? 0 : i == 2 ? 10: 0;
						for (int j = 1; j <= 4; j++)
						{
							if (beeta == index)
							{
								enemy2[beeta].setPosition(sf::Vector2f((199.05 * alpha) / 5.10 + 15, 30.65 + 6 + 35));
								enemy[beeta].setPosition(sf::Vector2f((199.05 * alpha) / 5.10, 30.65));
							}
							alpha += 2.5;
							beeta++;
						}
					}
				}
				else if (index == 8)
				{
					enemy2[8].setPosition(sf::Vector2f((199.05) / 5.10 + 10 + 15, 30.65 * 3 + 55));
				}
				else if (index == 9)
				{
					enemy2[9].setPosition(sf::Vector2f((199.05 * 4) / 5.10 - 5 + 15, 30.65 * 3 + 10 + 35));
				}
				else if (index == 10)
				{
					enemy2[10].setPosition(sf::Vector2f((199.05 * 7) / 5.10 + 10 + 15, 30.65 * 3 + 10 + 35));
				}
				else if (index == 11)
				{
					enemy2[11].setPosition(sf::Vector2f((199.05 * 12) / 5.10 + 15, 30.65 * 3 + 10 + 35));
				}
				else if (index == 12)
				{
					enemy2[12].setPosition(sf::Vector2f((199.05 * 15) / 5.10 + 10 + 15, 30.65 * 3 + 10 + 35));
				}
				else if (index == 13)
				{
					enemy2[13].setPosition(sf::Vector2f((199.05 * 18) / 5.10 + 13 + 15, 30.65 * 3 + 10 + 35));
				}
			}
			count[index]+=1;
			enemy2[index].move(sf::Vector2f(0, 2));
			if(!toproceed){return true;}
			return return_rype;
		}

		else if (nm == 2)
		{
			bool return_rype = true;
			int val = 0;
			je = 0;
			if (index == 0){je = 6;val = 14;}
			else if (index == 1){je = 8;val = 12;}
			else if (index == 2){je = 9;val = 11;}
			else if (index == 3){je = 11;val = 9;}
			else if (index == 4){je = 12;val = 8;}
			else if (index == 5){je = 11;val = 9;}
			else if (index == 6){je = 9;val = 11;}
			else if (index == 7){je = 7;val = 13;}
			if (arrays[int(count[index] / val)][je] == 11)
			{return_rype = false;}
			else{
			arrays[int(count[index] / val)][je] = 2;}

			if ((index == 0 || index == 4) && (int(count[0] / val) >= 20 || int(count[4] / val) >= 20) || (index == 1 || index == 3) && (int(count[1] / val)>= 20 || int(count[3] / val) >= 20) || index == 2 && int(count[2] / val) >= 20 || (index == 5 || index == 7) && (int(count[5] / val) >= 20 || int(count[7] / val) >= 20) || index == 6 && int(count[6] / val) >= 20)
			{
				arrs2[index] = true;
				count[index] = 0;
				if (0 == index)
				{
					enemy2[0].setPosition(sf::Vector2f(200, 200));
				}
				else if (1 == index)
				{
					enemy2[1].setPosition(sf::Vector2f(270, 150));
				}
				else if (2 == index)
				{
					enemy2[2].setPosition(sf::Vector2f(340, 70));
				}
				else if (3 == index)
				{
					enemy2[3].setPosition(sf::Vector2f(410, 150));
				}
				else if (4 == index)
				{
					enemy2[4].setPosition(sf::Vector2f(480, 230));
				}
				else if (5 == index)
				{
					enemy2[5].setPosition(sf::Vector2f(410, 310));
				}
				else if (6 == index)
				{
					enemy2[6].setPosition(sf::Vector2f(340, 390));
				}
				else if (7 == index)
				{
					enemy2[7].setPosition(sf::Vector2f(270, 310));
				}
			}
			count[index]+=1.5;
			enemy2[index].move(sf::Vector2f(0, 3));
			if(!toproceed){return true;}
			return return_rype;
		}
		else if(nm==3)
		{
			// cout << index << endl;
			bool return_rype = true;
			int val = 0;
			je = 0;
			if (index == 0)
			{je = 7;val = 14;}
			else if (index == 1)
			{je = 8;val = 12;}
			else if (index == 2)
			{je = 9;val = 10.5;}
			else if (index == 3)
			{je = 11;val = 9;}
			else if (index == 4)
			{je = 12;val = 7;}
			else if (index == 5)
			{je = 13;val = 14;}
			else if (index == 6)
			{je = 11;val = 12;}
			else if (index == 7)
			{je = 8;val = 9;}
			else if (index == 8)
			{je = 7;val = 6;}
			if (arrays[int(count[index] / val)][je] == 11)
			{
				return_rype = false;
			}
			arrays[int(count[index] / val)][je] = 2;
			if ((index == 0 && int(count[0] / 20) + 6 >= 20) || (index == 1 && int(count[1] / val) >= 20) || (index == 2 && int(count[2] / val) >= 20) || (index == 3 && int(count[3] / val) >= 20) || (index == 4 && int(count[4] / val) >= 20) || (index == 5 && int(count[5] / val) >= 20) || (index == 6 && int(count[6] / val) >= 20) || (index == 7 && int(count[7] / val) >= 20) || (index == 8 && int(count[8] / val) >= 20))
			{
				arrs2[index] = true;
				count[index] = 0;
				if (0 == index){enemy2[0].setPosition(250, 70);}
				else if (1 == index){enemy2[1].setPosition(310, 140);}
				else if (2 == index){enemy2[2].setPosition(350, 210);}
				else if (3 == index){enemy2[3].setPosition(410, 280);}
				else if (4 == index){enemy2[4].setPosition(490, 350);}
				else if (5 == index){enemy2[5].setPosition(490, 70);}
				else if (6 == index){enemy2[6].setPosition(410, 140);}
				else if (7 == index){enemy2[7].setPosition(310, 280);}
				else if (8 == index){enemy2[8].setPosition(250, 350);}
			}
			count[index]+=2;
			enemy2[index].move(sf::Vector2f(0, 4));
			if(!toproceed){return true;}
			return return_rype;
		}
		else if(nm==4 || nm==7)
		{
			bool return_rype = true;
			int val = 0;
			je = 0;
			if (index == 0)
			{je = 6;val = 14;}
			else if (index == 1)
			{je = 6;val = 14;}
			else if (index == 2)
			{je = 9;val = 11;}
			else if (index == 3)
			{je = 12;val = 8;}
			else if (index == 4)
			{je = 12;val = 8;}
			else if (index == 5)
			{je = 13;val = 7;}
			else if (index == 6)
			{je = 9;val = 11;}
			else if (index == 7)
			{je = 7;val = 13;}
			if(nm==7){
				if (index == 8)
				{je = 8;val = 12;}
				if (index == 9)
				{je = 10;val = 10;}
				if (index == 10)
				{je = 9;val = 11;}
				if (index == 11)
				{je = 9;val = 11;}
			}
			// else if (index == 8)
			// {je = 7;val = 6;}
			if (arrays[int(count[index] / val)][je] == 11)
			{
				return_rype = false;
			}
			arrays[int(count[index] / val)][je] = 2;
			if ((index == 0 && int(count[0] / val) >= 20) || (index == 1 && int(count[1] / val) >= 20) || (index == 2 && int(count[2] / val) >= 20) || (index == 3 && int(count[3] / val) >= 20) || (index == 4 && int(count[4] / val) >= 20) || (index == 5 && int(count[5] / val) >= 20) || (index == 6 && int(count[6] / val) >= 20) || (index == 7 && int(count[7] / val) >= 20) || (index == 8 && int(count[8] / val) >= 20) || (index == 9 && int(count[9] / val) >= 20) || (index == 10 && int(count[10] / val) >= 20) || (index == 11 && int(count[11] / val) >= 20))
			{
				arrs2[index] = true;
				count[index] = 0;
				if (0 == index){enemy2[0].setPosition(200, 230);}
				else if (1 == index){enemy2[1].setPosition(230, 120);}
				else if (2 == index){enemy2[2].setPosition(340, 70);}
				else if (3 == index){enemy2[3].setPosition(450, 120);}
				else if (4 == index){enemy2[4].setPosition(480, 230);}
				else if (5 == index){enemy2[5].setPosition(440, 330);}
				else if (6 == index){enemy2[6].setPosition(340, 390);}
				else if (7 == index){enemy2[7].setPosition(240, 330);}
				else if (8 == index){enemy2[8].setPosition(290, 200);}
				else if (9 == index){enemy2[9].setPosition(380, 200);}
				else if (10 == index){enemy2[10].setPosition(340, 270);}
				else if (11 == index){enemy2[11].setPosition(340, 120);}
				// else if (8 == index){enemy2[8].setPosition(250, 350);}
			}
			count[index]+=1;
			enemy2[index].move(sf::Vector2f(0, 2));
			// if(!toproceed){return true;}
			return return_rype;
		}
		else if(nm==5)
		{
			bool return_rype = true;
			int val = 0;
			je = 0;
			if (index == 0)
			{je = 6;val = 14;}
			else if (index == 1)
			{je = 7;val = 13;}
			else if (index == 2)
			{je = 9;val = 11;}
			else if (index == 3)
			{je = 11;val = 9;}
			else if (index == 4)
			{je = 13;val = 7;}
			else if (index == 5)
			{je = 11;val = 9;}
			else if (index == 6)
			{je = 9;val = 11;}
			else if (index == 7)
			{je = 7;val = 13;}
			else if (index == 8)
			{je = 7;val = 13;}
			if (arrays[int(count[index] / val)][je] == 11)
			{
				return_rype = false;
			}
			arrays[int(count[index] / val)][je] = 2;
			if ((index == 0 && int(count[0] / val) >= 20) || (index == 1 && int(count[1] / val) >= 20) || (index == 2 && int(count[2] / val) >= 20) || (index == 3 && int(count[3] / val) >= 20) || (index == 4 && int(count[4] / val) >= 20) || (index == 5 && int(count[5] / val) >= 20) || (index == 6 && int(count[6] / val) >= 20) || (index == 7 && int(count[7] / val) >= 20))
			{
				arrs2[index] = true;
				count[index] = 0;
				if (0 == index){enemy2[0].setPosition(200, 230);}
				else if (1 == index){enemy2[1].setPosition(270, 150);}
				else if (2 == index){enemy2[2].setPosition(340, 200);}
				else if (3 == index){enemy2[3].setPosition(410, 150);}
				else if (4 == index){enemy2[4].setPosition(480, 230);}
				else if (5 == index){enemy2[5].setPosition(410, 310);}
				else if (6 == index){enemy2[6].setPosition(340, 390);}
				else if (7 == index){enemy2[7].setPosition(270, 310);}
			}
			count[index]+=1.5;
			enemy2[index].move(sf::Vector2f(0, 3));
			// if(!toproceed){return true;}
			return return_rype;
		}
		else if(nm==6 || nm==8)
		{
			bool return_rype = true;
			int val = 0;
			je = 0;
			if (index == 0)
			{je = 6;val = 14;}
			else if (index == 1)
			{je = 7;val = 13;}
			else if (index == 2)
			{je = 9;val = 11;}
			else if (index == 3)
			{je = 11;val = 9;}
			else if (index == 4)
			{je = 13;val = 7;}
			else if (index == 5)
			{je = 4;val = 16;}
			else if (index == 6)
			{je = 11;val = 9;}
			else if (index == 7)
			{je = 7;val = 13;}
			else if (index == 8)
			{je = 14;val = 6;}
			else if (index == 9)
			{je = 8;val = 12;}
			else if (index == 10)
			{je = 10;val = 10;}
			else if (index == 11)
			{je = 9;val = 11;}
			if (arrays[int(count[index] / val)][je] == 11)
			{
				return_rype = false;
			}
			arrays[int(count[index] / val)][je] = 2;
			if ((index == 0 && int(count[0] / val) >= 20) || (index == 1 && int(count[1] / val) >= 20) || (index == 2 && int(count[2] / val) >= 20) || (index == 3 && int(count[3] / val) >= 20) || (index == 4 && int(count[4] / val) >= 20) || (index == 5 && int(count[5] / val) >= 20) || (index == 6 && int(count[6] / val) >= 20) || (index == 7 && int(count[7] / val) >= 20)|| (index == 8 && int(count[8] / val) >= 20)|| (index == 9 && int(count[9] / val) >= 20)|| (index == 10 && int(count[10] / val) >= 20)|| (index == 11 && int(count[11] / val) >= 20))
			{
				arrs2[index] = true;
				count[index] = 0;
				if (0 == index){enemy2[0].setPosition(200, 230);}
				else if (1 == index){enemy2[1].setPosition(270, 150);}
				else if (2 == index){enemy2[2].setPosition(340, 70);}
				else if (3 == index){enemy2[3].setPosition(410, 150);}
				else if (4 == index){enemy2[4].setPosition(480, 230);}
				else if (5 == index){enemy2[5].setPosition(550, 310);}
				else if (6 == index){enemy2[6].setPosition(410, 310);}
				else if (7 == index){enemy2[7].setPosition(276, 310);}
				else if (8 == index){enemy2[8].setPosition(140, 310);}
				else if (9 == index){enemy2[9].setPosition(293, 200);}
				else if (10 == index){enemy2[10].setPosition(386, 200);}
				else if (11 == index){enemy2[11].setPosition(340, 120);}
			}
			count[index]+=2;
			enemy2[index].move(sf::Vector2f(0, 4));
			// if(!toproceed){return true;}
			return return_rype;
		}
	}
};


#endif // ALLENEMY_H

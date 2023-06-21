#ifndef ADDON_H
#define ADDON_H

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string.h>

using namespace std;
using namespace sf;

class Addon
{
public:
	string image1 = "explosion.png";
	string image = "img/PNG/Lasers/laserGreen10.png";
public:
	Texture tex2, texs1;
	int value_x, value_y;
	Texture tex1, texs;
	Sprite powerup, danger;

	virtual void generate_location() = 0;
	virtual void generate() = 0;
	virtual bool check_memetup(int **arrays) = 0;
};

class Fire:public Addon{
public:
	Fire(){}
	void generate_location(){
		Addon::image = "explosion.png";
		Addon::image1 = "img/PNG/Lasers/laserGreen10.png";		
	}
	void generate(){
		Addon::image1 = "explosion.png";
		Addon::image = "img/PNG/Lasers/laserGreen10.png";
	}
	bool check_memetup(int **arrays){}
};

class fire
{
private:
	int keeptrack_true = -1, keeptrack_false = -1;
public:
	int value_x, value_y;
	Sprite sprite1[10], sprite2[10], sprite3[10], sprite4[10], sprite5[10],  sprite6[10],  sprite7[10];
	int valuex[10], valuey[10], currentlaser = 0;
	Texture tex1;
	bool laser_array[10] = {false};
	float valy = 5591;
	int counting[10] = {0};
	fire(float xx, float yy)
	{
		value_x = xx / 406.2, value_y = (yy - 499.999999993) / 278.4;
		srand(time(0));
		tex1.loadFromFile("img/PNG/Lasers/laserGreen10.png");
		
		for (int i = 0; i < 10; i++)
		{
			sprite1[i].setTexture(tex1);
			sprite1[i].setScale(0.75, 0.75);
			sprite2[i].setTexture(tex1);
			sprite2[i].setScale(0.75, 0.75);
			sprite3[i].setTexture(tex1);
			sprite3[i].setScale(0.75, 0.75);
			sprite4[i].setTexture(tex1);
			sprite4[i].setScale(0.75, 0.75);
			sprite5[i].setTexture(tex1);
			sprite5[i].setScale(0.75, 0.75);
			sprite6[i].setTexture(tex1);
			sprite6[i].setScale(0.75, 0.75);
			sprite7[i].setTexture(tex1);
			sprite7[i].setScale(0.75, 0.75);
		}
	}

	void settime(float xx, float yy)
	{
		if (currentlaser > 9)
		{
			currentlaser = 0;
		}
		valy = yy;
		counting[currentlaser] = 0;
		valuex[currentlaser] = xx / 406.2, valuey[currentlaser] = (yy - 499.999999993) / 278.4;
		sprite1[currentlaser].setPosition((xx / 9.800590) - 50 + 21, (yy / 10.037701975) - 57);
		sprite2[currentlaser].setPosition((xx / 9.800590) - 50 + 21, (yy / 10.037701975) - 57);
		sprite3[currentlaser].setPosition((xx / 9.800590) - 50 + 21, (yy / 10.037701975) - 57);
		sprite4[currentlaser].setPosition((xx / 9.800590) - 50 + 21, (yy / 10.037701975) - 57);
		sprite5[currentlaser].setPosition((xx / 9.800590) - 50 + 21, (yy / 10.037701975) - 57);
		sprite6[currentlaser].setPosition((xx / 9.800590) - 50 + 21, (yy / 10.037701975) - 57);
		sprite7[currentlaser].setPosition((xx / 9.800590) - 50 + 21, (yy / 10.037701975) - 57);
		laser_array[currentlaser] = true;
		currentlaser++;
	}
	bool move_it(int **arrays, int &xx_value, int &yy_value, bool alp, string image)
	{
		tex1.loadFromFile(image);
		float exp =image=="explosion.png"?1.75:0.75; 
		for (int i = 0; i < 10; i++)
		{
			sprite1[i].setScale(exp, exp);
			sprite2[i].setScale(exp, exp);
			sprite3[i].setScale(exp, exp);
			sprite4[i].setScale(exp, exp);
			sprite5[i].setScale(exp, exp);
			sprite6[i].setScale(exp, exp);
			sprite7[i].setScale(exp, exp);
		}
		bool returntype = false;
		// for short span I ma modifying laser_array;
		for (int i = 0; i < 10; i++)
		{
			if (laser_array[i] != false)
			{
				valuey[i] = (valy - counting[i] - 499.999999993) / 278.4;
				counting[i] += 9;
				if (valuey[i] < 0)
				{
					laser_array[i] = false;
					continue;
				}
				if (value_y <= 20 && value_x <= 21)
				{
					if(arrays[valuey[i]][valuex[i]]==13){returntype = true;}
					for(int j=0; j<7; j++){
						if(alp){
							if (arrays[valuey[i]][j==0?valuex[i]:j==1?valuex[i]-1:j==2?valuex[i]-3:j==3?valuex[i]+1:j==4?valuex[i]+3:j==5?valuex[i]-5:valuex[i]+5] == 13)
							{
								laser_array[i] = false;
								xx_value = valuey[i];
								yy_value = j==0?valuex[i]:j==1?valuex[i]-1:j==2?valuex[i]-3:j==3?valuex[i]+1:j==4?valuex[i]+3:j==5?valuex[i]-5:valuex[i]+5;
								returntype = true;
							}
						}
						else{
							if (arrays[valuey[i]][valuex[i]]==13)
							{
								laser_array[i] = false;
								xx_value = valuey[i];
								yy_value = valuex[i];
								returntype = true;
							}
						}
					}
					if(!alp)arrays[valuey[i]][valuex[i]] = 1;
					else{
						if(!(valuex[i]-1<0 || valuex[i]-1>19)){
							arrays[valuey[i]][valuex[i]-1] = 1;
						}
						else if(!(valuex[i]-3<0 || valuex[i]-3>19)){
							arrays[valuey[i]][valuex[i]-3] = 1;
						}
						else if(!(valuex[i]+1<0 || valuex[i]+1>19)){
							arrays[valuey[i]][valuex[i]+1] = 1;
						}
						else if(!(valuex[i]+3<0 || valuex[i]+3>19)){
							arrays[valuey[i]][valuex[i]+3] = 1;
						}
						else if(!(valuex[i]+5<0 || valuex[i]+5>19)){
							arrays[valuey[i]][valuex[i]+5] = 1;
						}
						else if(!(valuex[i]-5<0 || valuex[i]-5>19)){
							arrays[valuey[i]][valuex[i]-5] = 1;
						}
					}
				}
				sprite1[i].move(0, -1);
				sprite2[i].move(-0.15, -1);
				sprite3[i].move(-0.3, -1);
				sprite4[i].move(0.15, -1);
				sprite5[i].move(0.3, -1);
				sprite6[i].move(-0.45, -1);
				sprite7[i].move(0.45, -1);
			}
		}
		return returntype;
	}
	void generate_location(){}
	void generate(){}
	bool check_memetup(int **arrays){}
};

class Powerup:public Addon
{
private:
public:
	int count = 0;
	int initial = 0;
	int location = (rand()%710)+20;
	Powerup()
	{
		texs.loadFromFile("img/PNG/Power-ups/bolt_gold.png");
		powerup.setTexture(texs);
		// powerup.setScale(0.3, 0.3);
		powerup.setPosition(location, 0);
		// srand(time(0));
	}
	void change_power_up(){
		texs.loadFromFile(image);
		powerup.setTexture(texs);		
	}
	void generate_location(){
		count = 0;
		location = (rand()%710)+20;
		powerup.setPosition(location, 0);
	}
	void generate()
	{
		if(count>7695){count = 0, location = 0; return;}
		count++;
		powerup.move(0, 0.083);		
		return;
	}
	bool check_memetup(int **arrays){
		if(arrays[int(count/384.75)][int(location/36.5)]==11 || int(count/384.75)-1>0?arrays[int(count/384.75)-1][int(location/36.5)]==11:arrays[int(count/384.75)+1][int(location/36.5)==1]==11 || int(count/384.75)+1<19?arrays[int(count/384.75)+1][int(location/36.5)]==1:arrays[int(count/384.75)-1][int(location/36.5)]==1){
			return true;
		}
		return false;
	}
};

class Danger:public Addon
{
private:
public:
	int count = 0;
	int initial = 0;
	int location = (rand()%710)+20;
	Danger()
	{
		texs1.loadFromFile("img/danger.png");
		danger.setTexture(texs1);
		danger.setScale(0.23f, 0.23f);
		danger.setPosition(location, 0);
		// srand(time(0));
	}
	void generate_location(){
		count = 0;
		location = (rand()%710)+20;
		danger.setPosition(location, 0);
	}

	void generate()
	{
		if(count>7695){count = 0, location = 0; return;}
		count++;
		danger.move(0, 0.083);		
		return;
	}
	bool check_memetup(int **arrays){
		if(arrays[int(count/384.75)][int(location/36.5)]==11 || int(count/384.75)-1>0?arrays[int(count/384.75)-1][int(location/36.5)]==11:arrays[int(count/384.75)+1][int(location/36.5)+1]==11 || int(count/384.75)+1<20?arrays[int(count/384.75)+1][int(location/36.5)]==1:arrays[int(count/384.75)-1][int(location/36.5)]==1){
			generate();
			return true;
		}
		return false;
	}
};
#endif // ADDON_H

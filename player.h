// g++ main.cpp -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system && ./sfml-app
#include <SFML/Graphics.hpp>
# include "./hfiles/Addon.h"
# include "./hfiles/level1/allenemy.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string.h>
using namespace sf;
using namespace std;

class SpaceShip
{
private:
	Texture tex;
public:
	Addon *pu;
    Addon *da;
    Addon *Fires;
	Bullets *bullet;
	int x_pos = 9, y_pos = 20;
	float xx = 3981, yy = 5591, previous_xx, previous_yy, valy = 5591;
	int count = 0;
	Sprite sprite;
	float speed = 0.1;
	int x, y;
	void  perupftn(Clock &power_clock, bool &value, int &next_live, int **arrays, int &prev_live, int &lives){
		Fires->generate();
        while (power_clock.getElapsedTime().asSeconds() >= 5)
        {
            // Fires->generate_location();
			pu->generate_location();
            power_clock.restart();
        }
        pu->generate();
        value = pu->check_memetup(arrays);
        next_live = value;
		if(prev_live!=next_live && next_live!=false){	
			// Fires->generate();
			lives++;
        }
	}
	void dangerftn(Clock &danger_clock, bool &value1, int &next_live, int **arrays, int &prev_live, int &lives){
		while (danger_clock.getElapsedTime().asSeconds() >= 3)
        {
            da->generate_location();
            danger_clock.restart();
        }
        da->generate();
        value1 = da->check_memetup(arrays);
        next_live = value1;
		if(prev_live!=next_live && next_live!=false){
            lives--;
        }
	}
	void assign_addon(Addon *pup, Addon *dan, Addon *Fire){
		pu = pup, da = dan, Fires = Fire;
	}
	void assign_bullet(Bullets*bullet){
		this->bullet = bullet;
	}

	bool move_bullet(int index, int **arrays, int nm, bool toproceed, int*count, bool *arrs2, Sprite*enemy,Sprite*enemy2){
		return bullet->Bullet(index, arrays, nm, toproceed, count, arrs2, enemy, enemy2);
	}
	SpaceShip() {}
	SpaceShip(std::string png_path)
	{
		srand(time(0));
		tex.loadFromFile(png_path);
		sprite.setTexture(tex);
		x = 340;
		y = 557;
		sprite.setPosition(x, y);
		sprite.setScale(0.75, 0.75);
	}

	bool setcurrentposition(int **arrays, int num)
	{
		bool returntype = false;
		if(num==1){
			for(int i=0; i<4; i++){
				for(int j=0; j<20; j++){
					arrays[i][j] = arrays[i+3][j];
					arrays[i+3][j] = 0;
				}
			}
		}

		int a = 20 - y_pos;
		if(arrays[y_pos][x_pos]==13){returntype = true;}
		arrays[y_pos][x_pos] = 11;
		if (y_pos-1>0)
		{
			if(arrays[y_pos-1][x_pos]==13){returntype = true;}
			arrays[y_pos - 1][x_pos] = 11;
		}
		if (y_pos-2>0)
		{
			if(arrays[y_pos-2][x_pos]==13){returntype = true;}
			arrays[y_pos - 2][x_pos] = 11;
		}
		if (y_pos > 2)
		{
			// if(arrays[y_pos-3][x_pos]==13){return true;}
			// arrays[y_pos - 3][x_pos] = 11;
		}
			
		if (x_pos > 0)
		{
			if(arrays[y_pos][x_pos-1]==13){returntype = true;}
			arrays[y_pos][x_pos - 1] = 11;
			if (y_pos-1>0 && x_pos-1>0)
			{
				if(arrays[y_pos-1][x_pos-1]==13){returntype = true;}
				arrays[y_pos - 1][x_pos - 1] = 11;
			}
			if (y_pos-2>0 && x_pos-1>0)
			{
				if(arrays[y_pos-2][x_pos-1]==13){returntype = true;}
				arrays[y_pos - 2][x_pos - 1] = 11;
			}
			if (y_pos > 2)
			{
				// if(arrays[y_pos-3][x_pos-1]==13){return true;}
				// arrays[y_pos - 3][x_pos - 1] = 11;
			}
		}
		if (!(x_pos > 19))
		{
			if(arrays[y_pos][x_pos+1]==13){return true;}
			arrays[y_pos][x_pos + 1] = 11;
			if (y_pos-1>0 && x_pos+1<20)
			{
				if(arrays[y_pos-1][x_pos+1]==13){returntype = true;}
				arrays[y_pos - 1][x_pos + 1] = 11;
			}
			if (y_pos-2>0 && x_pos+1<20)
			{
				if(arrays[y_pos-2][x_pos+1]==13){returntype = true;}
				arrays[y_pos - 2][x_pos + 1] = 11;
			}
			if (y_pos > 2)
			{
				// if(arrays[y_pos-3][x_pos+1]==13){return true;}
				// arrays[y_pos - 3][x_pos + 1] = 11;
			}

		return returntype;
		}
		return false;
	}

	string move(std::string s, int **arrays)
	{
		string alpha = "";
		float delta_x = 0, delta_y = 0;
		if (s == "l")
		{
			delta_x-=1;
		}
		else if (s == "r")
		{
			delta_x+=1;
		}
		if (s == "u")
		{
			delta_y -=1;
		}
		else if (s == "d")
		{
			delta_y +=1;
		}
		previous_xx = xx, previous_yy = yy;
		xx += delta_x, yy += delta_y;
		// cout<<xx<<" "<<yy<<endl;
		if(s=="r"){
			if(xx<8135 && xx>8035 && yy<90){
				y_pos = 20;
				x_pos = 0;
				xx = 0, yy = 5590;
				delta_x = 0, delta_y = 0;
				sprite.setPosition(0 , (5592 / 10.037701975));
			}
		}
		else if(s=="l"){
			if(xx<10 && yy<5600 && yy>5550 ){
				y_pos = 0;
				x_pos = 18;
				xx = 8135, yy = 0;
				delta_x = 0, delta_y = 0;
				sprite.setPosition((xx / 9.800590) - 50 , 0);
			}
		}
		if(xx<=0 && yy<100){
			y_pos = 20;
			x_pos = 18;
			xx = 8136, yy = 5592;
			delta_x = 0, delta_y = 0;
			sprite.setPosition((xx / 9.800590) - 50 , (yy / 10.037701975));
		}
		else if(xx>7646 && yy>5580 && yy<5592){
			y_pos = 0;
			x_pos = 0;
			delta_x = 0, delta_y = 0;
			xx = 0, yy = 0;
			sprite.setPosition(0,0);
		}
		else if (xx < 0)
		{
			delta_x = 0, delta_y = 0;
			x_pos = 18;
			xx = 8135;
			sprite.setPosition((xx / 9.800590) - 50, (yy / 10.037701975));
			alpha = "left";
		}
		else if (xx > 8136)
		{
			delta_x = 0, delta_y = 0;
			x_pos = 0;
			xx = 0;
			sprite.setPosition((xx / 9.800590) - 50, (yy / 10.037701975));
			alpha = "right";
		}
		if (yy < 0)
		{
			y_pos = 20;
			delta_x = 0, delta_y = 0;
			sprite.setPosition((xx / 9.800590)-65 , (5592 / 10.037701975));
			xx = previous_xx, yy = 5590;
		}
		else if (yy > 5592)
		{
			y_pos = 0;
			delta_x = 0, delta_y = 0;
			sprite.setPosition((xx / 9.800590)-65 ,0);
			xx = previous_xx, yy = 0;
		}
		
		x_pos = xx / 406.2;
		y_pos = yy / 278.4;
		delta_x *= speed;
		delta_y *= speed;
		sprite.move(delta_x, delta_y);
		// cout<<xx<<" "<<yy<<endl;
		return alpha;
	}
	int get_xpos(){
		return x_pos;
	}
	float get_x()
	{
		return xx;
	}
	float get_y()
	{
		return yy;
	}
};

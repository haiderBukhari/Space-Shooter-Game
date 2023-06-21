#include <SFML/Graphics.hpp>
# include <iostream>
using namespace std;
class Menu
{
private:
public:
    Text text[4], texts, liveleft, lives,scores, score, lev[3], frequency, text1[14];
    sf::Font font;
    Sprite background, pic[5], level[3], imgs[3], imgs1[3]; // Game background sprite
    Texture bg_texture, pics[5], levels[3], img[3];
    // add menu attributes here
    Menu()
    {
        if (!font.loadFromFile("SF_Cartoonist_Hand_Bold.ttf"))
        {
            cout << "EXIT_FAILURE";
        }
        bg_texture.loadFromFile("img/background.png");
        background.setTexture(bg_texture);
        background.setScale(2.25, 1.35);
        for(int i=0; i<4; i++){
            text[i].setFont(font);
            texts.setFont(font);
            text[i].setCharacterSize(40);
            texts.setCharacterSize(26);
        }
        for(int i=0; i<14; i++){
            text1[i].setFont(font);
            text1[i].setPosition(100, 100);
            text1[i].setCharacterSize(22);
        }
        frequency.setFont(font);
        frequency.setCharacterSize(22);
        frequency.setPosition(790, 540);
        for(int i=0; i<3; i++){
            lev[i].setFont(font);
            lev[i].setCharacterSize(40);
            lev[i].setFillColor(Color::White);
            lev[i].setPosition(170,60);
        }
        lives.setCharacterSize(27);
        liveleft.setCharacterSize(29);
        liveleft.setFont(font);
        lives.setFont(font);
        score.setCharacterSize(27);
        scores.setCharacterSize(29);
        score.setFont(font);
        scores.setFont(font);
        lev[0].setString("Welcome to Level 1!\n\n\t Press Enter to proceed\n");
        lev[1].setString("Welcome to Level 2!\n\n\t Press Enter to proceed\n");
        lev[2].setString("Welcome to Level 3!\n\n\t Press Enter to proceed\n");
        liveleft.setString("Lives Left");
        scores.setString("Total Score");
        lives.setString(to_string(3));
        score.setString(to_string(0));

        liveleft.setFillColor(Color::White);
        liveleft.setPosition(810, 50);
        lives.setPosition(860, 95);
        scores.setPosition(810, 170);
        score.setPosition(860, 215);
        texts.setString("Enter your name: ");
        text[0].setString("Start a New Game (A)");
        texts.setFillColor(Color::White);
        texts.setPosition(20, 20);
        text[1].setString("Pause/Resume Game\n (Esc)        (B)");
        text[2].setString("Help (C)");
        text[3].setString("High Scores (D)");
        img[0].loadFromFile("img/1st.png");
        img[1].loadFromFile("img/2nd.png");
        img[2].loadFromFile("img/3rd.png");
        pics[0].loadFromFile("img/start.png");
        pics[1].loadFromFile("img/pause.png");
        pics[2].loadFromFile("img/help.png");
        pics[3].loadFromFile("img/highscore.png");
        levels[0].loadFromFile("img/level1.png");
        levels[1].loadFromFile("img/level2.png");
        levels[2].loadFromFile("img/level3.png");
        pic[0].setTexture(pics[0]);
        pic[1].setTexture(pics[1]);
        pic[2].setTexture(pics[2]);
        imgs[0].setTexture(img[0]);
        imgs[1].setTexture(img[1]);
        imgs[2].setTexture(img[2]);
        imgs1[0].setTexture(img[0]);
        imgs1[1].setTexture(img[1]);
        imgs1[2].setTexture(img[2]);
        pic[3].setTexture(pics[3]);
        level[0].setTexture(levels[0]);
        level[1].setTexture(levels[1]);
        level[2].setTexture(levels[2]);
        level[0].setPosition(300, 300);
        level[1].setPosition(300, 300);
        level[2].setPosition(300, 300);
        pic[0].setScale(0.7f, 0.7f);
        pic[1].setScale(0.7f, 0.7f);
        pic[2].setScale(0.7f, 0.7f);
        pic[3].setScale(0.7f, 0.7f);
        
        imgs[0].setScale(0.5f, 0.5f);
        imgs[1].setScale(0.5f, 0.5f);
        imgs[2].setScale(0.5f, 0.5f);
        imgs1[0].setScale(0.5f, 0.5f);
        imgs1[1].setScale(0.5f, 0.5f);
        imgs1[2].setScale(0.5f, 0.5f);
        
        imgs[0].setPosition(560,70*0+40);
        imgs[1].setPosition(560,80*1+40);
        imgs[2].setPosition(560,90*2+40);

        imgs1[0].setPosition(810,350);
        imgs1[1].setPosition(810,350);
        imgs1[2].setPosition(810,350);

        pic[0].setPosition(100, 40);
        text[0].setPosition(380,98);
        pic[1].setPosition(100, 180);
        text[1].setPosition(380,238);
        pic[2].setPosition(100, 320);
        text[2].setPosition(420,398);
        pic[3].setPosition(100, 460);
        text[3].setPosition(380,518);
        // constructors body
    }
};

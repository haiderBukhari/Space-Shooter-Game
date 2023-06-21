#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include "player.h"
#include "menu.h"
#include "./hfiles/level1/allenemy.h"
#include "./hfiles/Addon.h"
#include <cstdlib>

const char title[] = "OOP-Project, Spring-2023";
using namespace sf;

class Game
{
    Menu *menu;
public:
    Texture ta;
    Sprite la;
    Monster *monster = new Monster();
    float timer1 = 0;
    bool generate_powerup = true, danger_powerup = true;
    int to_move =true, to_move1 =false, pre = 0, level = 1, score = 0, lives = 3, points = 10;
    int **arrays = new int *[21];
    Sprite background; // Game background sprite
    Texture bg_texture;
    fire *fir;    
    Addon *pu = new Powerup();
    Addon *da = new Danger();
    Addon *Fires = new Fire();
    SpaceShip *p = new SpaceShip("img/player_ship.png"); // player
    int timer_set = 5;
    // Enemies *enemy = new Enemies();
    Enemies *inv = new Invader();
    Enemies *alpha_invader = new alpha_inavder_triangle();
    Enemies *cinvader = new cross_invader();
    Enemies *cenemy = new circle_enemy();
    Enemies *henemy = new heart_enemy();
    Enemies *tenemy = new triangle_enemy();
    Enemies *cfenemy = new circle_filled_enemy();
    Enemies * tfenemy = new triangle_filled_enemy();
    Dragon *dragon = new Dragon;
    Bullets *bullets = new Bullets();
    int xval, yval, number = 1;
    bool monster_appear = true, dragon_appear = false, shift = true, proceed = true, powershow = true, dangershow = true, torepeat = false, dragon_stop = false, monster_stop = true;
    int incre_pre = 100;
    int initial = 8, alpha = rand() % initial;
    animation_level1 *animation;
    int c_count = 0;
    int arre1[10] = {0};
    string arre2[10] = {};
    Game()
    {
        ta.loadFromFile("gradient.jpeg");
        la.setTexture(ta);
        la.setPosition(780, 0);
        menu = new Menu();
        srand(time(0));
        for (int i = 0; i < 21; i++)
        {
            arrays[i] = new int[21];
        }
        for (int i = 0; i < 20; i++)
        {
            for (int j = 0; j < 21; j++)
            {
                arrays[i][j] = 0;
            }
        }
        // enemy->enemies();
        if (monster_appear)
            monster->specify_values(arrays);
        if (dragon_appear)
            dragon->specify_values(arrays);
        number == 1 ? inv->specify_values(arrays) : number == 2 ? alpha_invader->specify_values(arrays): number == 3   ? cinvader->specify_values(arrays): number == 4   ? cenemy->specify_values(arrays): number == 5   ? henemy->specify_values(arrays):number==6? tenemy->specify_values(arrays):number==7?cfenemy->specify_values(arrays):tfenemy->specify_values(arrays);
        
        bg_texture.loadFromFile("img/background.png");
        background.setTexture(bg_texture);
        background.setScale(2.25, 1.35);
        fir = new fire(p->get_x(), p->get_y());
        inv->bombs(number);
        // p->assign_addon(pui, dan, firs);
    }
    int largest(string name){
        for(int i=0; i<3; i++){
            if(arre2[i] == name){
                return i+1;
            }
        }
        return -1;
    }
    void add_data(){
        for(int i=0; i<10; i++){
            arre2[i] = "";
            arre1[i] = 0;
        }
        string final_data;
        int count = 0;
        string arr[10];
        string nm = "";
        string data;
        ifstream read;
        read.open("Marks.txt", ios::app);
        int i = 0;
        while(getline(read , data)){
            arr[i] = data;
            i++;
        }
        for(int j=0; j<i; j++){
            bool move = true;
            int num = 0;
            for(int k=0; k<arr[j].length(); k++){
                if(arr[j][k]=='!'){break;}
                if(arr[j][k]=='.'){move = false; continue;}
                else if(move){arre2[j] += arr[j][k]; }
                else{
                    int num1 = static_cast<int>(arr[j][k])-48;
                    num = num*10 + num1;
                }
            }
            arre1[j] = num; 
        }
        
        ofstream write;
        write.open("Marks.txt");
        write<<"";
        write.close();

        count = i;        
        for(int k=0; k<count-1; k++){
            for(int j=0; j<count-k-1; j++){
                if(arre1[j]<arre1[j+1]){
                    int temp = arre1[j+1];
                    arre1[j+1] = arre1[j];
                    arre1[j] = temp;

                    string temp1 = arre2[j+1];
                    arre2[j+1] = arre2[j];
                    arre2[j] = temp1;
                }
            }
        }
        for(int i=0; i<count*2 && i<14; i++){
            if(i<count){
                menu->text1[i].setPosition(100,90*i+40);
                menu->text1[i].setString(arre2[i]);
            }
            else{
                menu->text1[i].setPosition(320,90*(i-count)+40);
                menu->text1[i].setString(to_string(arre1[i-count]));
            }
        } 
        ofstream write1;
        write1.open("Marks.txt");
        for(int j=0; j<count; j++){
            write1<<arre2[j]<<"."<<arre1[j]<<'!'<<endl;
        }
        write1.close();
        for(int i=0; i<count*2; i++){
            menu->text1[i].setFont(menu->font);
            menu->text1[i].setCharacterSize(32);
            menu->text1[i].setFillColor(Color::White);
            if(i<count){
                menu->text1[i].setPosition(100,70*i+40);
                menu->text1[i].setString(arre2[i]);
            }
            else{
                menu->text1[i].setPosition(450,70*(i-count)+40);
                menu->text1[i].setString(to_string(arre1[i-count]));
            }
        }
        c_count = count;
    }
    void start_game()
    {
        // add_data();
        string name;
        int score = 0, prev_live = 0, next_live = 0, prev_live1 = 0, next_live1 = 0;
        bool value, value1 = false;
        bool tomove = false;
        
        cout<<"////////////////////////////////////////////////////\n";
        cout<<"////////////Welcome to Space Shooter Game////////////\n";
        cout<<"////////////////////////////////////////////////////\n";
        cout<<endl<<"Enter Your Name: \n\t>>>";
        getline(cin, name);
        int valueso = largest(name);
        SoundBuffer buffer;
        if (!buffer.loadFromFile("song.ogg"))
        {
            cout << "error";
        }
        Sprite bk; // Game background sprite
        Texture bg;
        bg.loadFromFile("img/Help.png");
        bk.setTexture(bg);
        // bk.setScale(2.25, 1.35);
        Sound sound;
        sound.setBuffer(buffer);
        sound.setVolume(6);
        sound.play();
        srand(time(0));
        RenderWindow window(VideoMode(980, 780), title);
        window.clear(sf::Color::White);
        bool iscontinue = false;
        bool toshow = false;
        int alphas1 = -2;
        
        while (true)
        {
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    {
                        // return;
                    //     ofstream write;
                    //     write.open("Marks.txt",ios::app);
                    //     write<<score<<endl;
                    //     write.close();
                    //     window.close();
                    }
            }
            if((number==1 || number==4 || number==7) && alphas1==0){
                if (Keyboard::isKeyPressed(Keyboard::Enter))
                {
                    iscontinue = true;
                    alphas1++;
                }
            }
            window.clear();
            if (Keyboard::isKeyPressed(Keyboard::P))
            {
                while(true){
                    Event event;
                    while (window.pollEvent(event))
                    {
                        if (event.type == Event::Closed)
                        { 
                            break;
                        }
                        bg_texture.loadFromFile("img/game_over.jpg");
                        background.setTexture(bg_texture);
                        // background.setScale(2.25, 1.35);
                        window.clear();
                        window.draw(background);
                        window.display();
                    }
                    if(Keyboard::isKeyPressed(Keyboard::E)){return;}
                }
                return;
            }
            if (Keyboard::isKeyPressed(Keyboard::A))
            {
                monster_appear = false, dragon_appear = false;
                incre_pre = 100;
                iscontinue = true;
                score = 0, prev_live = 0, next_live = 0, prev_live1 = 0, next_live1 = 0;
                lives = 3;
                value, value1 = false;
                tomove = false;
                delete inv, alpha_invader, cinvader, cenemy, henemy, tenemy, cfenemy, tfenemy, fir, p, pu, da, Fires, bullets, monster;
                monster = new Monster();
                fire *fir;    
                pu = new Powerup();
                da = new Danger();
                Fires = new Fire();
                bullets = new Bullets();
                // enemy = new Enemies();
                // enemy->enemies();
                p = new SpaceShip("img/player_ship.png");
                fir = new fire(p->get_x(), p->get_y());
                inv = new Invader();
                alpha_invader = new alpha_inavder_triangle();
                cinvader = new cross_invader();
                cenemy = new circle_enemy();
                henemy = new heart_enemy();
                tenemy = new triangle_enemy();
                cfenemy = new circle_filled_enemy();
                tfenemy = new triangle_filled_enemy();
                inv->bombs(number);
                for(int i=0; i<20; i++){
                    for(int j=0; j<20; j++){
                        arrays[i][j] = 0;
                    }
                }
                p->assign_addon(pu, da, Fires);
                p->assign_bullet(bullets);

                while(alphas1==-2){
                    Event ev;
                    while (window.pollEvent(ev))
                    {
                        if (ev.type == Event::Closed)
                        {
                            break;
                        }
                    }
                    if (Keyboard::isKeyPressed(Keyboard::Escape))
                    {
                        break;
                    }
                    if(Keyboard::isKeyPressed(Keyboard::Enter)){
                        alphas1 = 1;
                    }
                    window.clear();
                    window.draw(background);
                    window.draw(la);    
                    window.draw(menu->level[0]);
                    window.draw(menu->lev[0]);
                    window.display();
                }
            }
            if (Keyboard::isKeyPressed(Keyboard::B))
            {
                iscontinue = true;
            }
            if (Keyboard::isKeyPressed(Keyboard::C))
            {
            while (true)
            {
                Event ev;
                while (window.pollEvent(ev))
                {
                    if (ev.type == Event::Closed)
                    {
                        break;
                    }
                }
                if (Keyboard::isKeyPressed(Keyboard::Escape))
                {
                    break;
                }
                window.clear();
                window.draw(bk);
                window.display();
            }
            }
            if (Keyboard::isKeyPressed(Keyboard::D))
            {
                add_data();
            while (true)
            {
                Event ev;
                while (window.pollEvent(ev))
                {
                    if (ev.type == Event::Closed)
                    {
                        break;
                    }
                }
                if (Keyboard::isKeyPressed(Keyboard::Escape))
                {
                    break;
                }
                window.clear();
                window.draw(background);
                for(int i=0; i<c_count*2; i++){
                    window.draw(menu->text1[i]);
                }
                window.draw(menu->imgs[0]);
                window.draw(menu->imgs[1]);
                window.draw(menu->imgs[2]);
                window.display();
            }
            }
            window.clear();
            window.draw(background);
            window.draw(la);
            if(alphas1!=0){
                window.draw(menu->text[0]);
                window.draw(menu->text[1]);
                window.draw(menu->text[2]);
                window.draw(menu->text[3]);
                window.draw(menu->pic[0]);
                window.draw(menu->pic[1]);
                window.draw(menu->pic[2]);
                window.draw(menu->pic[3]);
            }
            else{
                if(number==4){
                    window.draw(menu->level[1]);
                    window.draw(menu->lev[1]);
                }
                if(number==1){
                    window.draw(menu->level[0]);
                    window.draw(menu->lev[0]);
                }
                if(number==7){
                    window.draw(menu->level[2]);
                    window.draw(menu->lev[2]);
                }
            }
            window.display();

            float timer = 0;
            bool move = false;
            Clock clock, sec_clock, sec2_clock, sec0_clock, sec1_clock, clocked, power_clock, danger_clock, secclock, last_clock, monster_clock, secc_1lock, dragon_clock;
            bool a = false;
            while (iscontinue)
            {
                // if(rand()%10000==103 && !monster_appear){
                //     dragon_appear = true;
                //     dragon_stop = true;
                // }
                if(rand()%80000==200 && !dragon_appear){
                    monster_appear = true;
                    monster_stop = true;
                }
                if(rand()%80000==150 && !monster_appear){
                    dragon_appear = true;
                    dragon_stop = true;
                }
                if(incre_pre<=0){
                    if(monster_appear){score += 40;}
                    if(dragon_appear){score += 50;}
                    monster_appear = false;
                    monster_stop = false;
                    dragon_appear = false;
                    dragon_stop = false;
                }
                if(lives<=0){
                    ofstream enter;
                    enter.open("Marks.txt", ios::app);
                    enter<<name<<"."<<score<<"!\n";
                    enter.close();
                    // add_data();
                    iscontinue = false;
                }
                // if(monster_appear){
                //     string a = to_string(incre_pre);
                //     a+='%';
                //     menu->frequency.setString(a);
                //     window.draw(menu->frequency);
                // }
                // if(rand()%100000==103 && dragon_appear){
                //     dragon_appear = false;
                //     dragon_stop = false;
                // }
                // if(rand()%30000==200 && monster_appear){
                //     monster_appear = false;
                //     monster_stop = false;
                // }
                p->assign_addon(pu, da, Fires);
                p->assign_bullet(bullets);

                prev_live = value;
                value, value1 = false;
                if (generate_powerup)
                {
                    Fires->generate();
                    p->perupftn(power_clock, value, next_live, arrays,prev_live, lives);
                    // cout<<value<<endl;
                }
                else{
                    Fires->generate_location();
                }
                if (danger_powerup)
                {
                    prev_live = value1;
                    p->dangerftn(danger_clock, value1, next_live, arrays, prev_live, lives);
                }
                if (value)
                {
                    proceed = false;
                    generate_powerup = false;
                    torepeat = true;
                    powershow = false;
                }
                else
                {
                    proceed = true;
                }
                if (value1)
                {
                    danger_powerup = false;
                    torepeat = true;
                    dangershow = false;
                    value1 = false;
                    // menu->lives.setString(to_string(--lives));
                    // value1 = false;
                    // return;
                    // apply further implemetation
                }
                if (!generate_powerup)
                {
                    while (secclock.getElapsedTime().asSeconds() >= 5)
                    {
                        torepeat = false;
                        generate_powerup = true;
                        powershow = true;
                        secclock.restart();
                    }
                }
                if (!danger_powerup)
                {
                    while (secc_1lock.getElapsedTime().asSeconds() >= 5)
                    {
                        torepeat = false;
                        danger_powerup = true;
                        dangershow = true;
                        secc_1lock.restart();
                        score+=5;
                    }
                }
                if (monster_appear)
                {
                    while (monster_clock.getElapsedTime().asSeconds() >= 2)
                    {
                        monster->reset(p->get_x(), p->get_y(), p->get_xpos());
                        monster_clock.restart();
                        // prev_live1 =  monster->check_enemy(arrays);
                        tomove = true;
                    }
                }
                if (dragon_appear)
                {
                    while (dragon_clock.getElapsedTime().asSeconds() >= 2)
                    {
                        dragon->reset(p->get_x(), p->get_y(), p->get_xpos());
                        dragon_clock.restart();
                    }
                }
                while (sec_clock.getElapsedTime().asSeconds() >= 0.002)
                {
                    menu->score.setString(to_string(score));
                    if (monster_appear)
                        monster->move_left_and_right();
                    for (int i = 0; i < 21; i++)
                    {
                        for (int j = 0; j < 20; j++)
                        {
                            arrays[i][j] = 0;
                        }
                    }
                    if (monster_appear)
                        monster->move_downward(arrays, p->get_x(), p->get_y());
                    if (dragon_appear)
                        dragon->move_downward(arrays, p->get_x(), p->get_y());
                    
                    if(!dragon_appear && !monster_appear){
                        number == 1 ? inv->check_array(arrays) : number == 2 ? alpha_invader->specify_values(arrays): number == 3   ? cinvader->specify_values(arrays): number == 4   ? cenemy->specify_values(arrays): number == 5   ? henemy->specify_values(arrays): number==6?tenemy->specify_values(arrays):number==7?cfenemy->specify_values(arrays):tfenemy->specify_values(arrays);
                    }

                    int count = 0;
                    for (int i = 0; i < 10; i++)
                    {
                        if (fir->laser_array[i])
                        {
                            count++;
                            break;
                        }
                    }
                    if (count != 0)
                    {
                        if (monster_appear)
                            monster->specify_values(arrays);
                        if (dragon_appear)
                            dragon->specify_values(arrays);
                            
                        move = fir->move_it(arrays, xval, yval, torepeat, Fires->image);
                        if(move && (monster_appear || dragon_appear)){incre_pre-=10;}
                        if(!monster_appear && !dragon_appear){incre_pre = 100;}
                    }

                    if (move && !monster_appear && !dragon_appear)
                    {
                        number == 1 ? inv->check_enemy(arrays, xval, yval) : number == 2 ? alpha_invader->check_enemy(arrays, xval, yval): number == 3   ? cinvader->check_enemy(arrays, xval, yval): number == 4   ? cenemy->check_enemy(arrays, xval, yval): number == 5   ? henemy->check_enemy(arrays, xval, yval):number==6? tenemy->check_enemy(arrays, xval, yval):number==7?cfenemy->check_enemy(arrays, xval, yval):tfenemy->check_enemy(arrays, xval, yval);
                        score += level * points;
                        move = false;
                    }
                    sec_clock.restart();
                }
                
                float time = clock.getElapsedTime().asSeconds();
                clock.restart();
                int previous = timer;
                timer += time;
                Event e;
                while (sec1_clock.getElapsedTime().asSeconds() >= 0.01)
                {
                    if (pre != static_cast<int>(timer / timer_set))
                    {
                        inv->arrs2[alpha] = false;
                        inv->count[0] = 0;
                        alpha = rand() % initial;

                        while (number == 1 ? inv->arrs1[alpha] : number == 2 ? alpha_invader->arrs1[alpha]: number == 3   ? cinvader->arrs1[alpha]: number == 4   ? cenemy->arrs1[alpha]: number == 5   ? henemy->arrs1[alpha]:number==6?tenemy->arrs1[alpha]:number==7?cfenemy->arrs1[alpha]:tfenemy->arrs1[alpha])
                        {
                            alpha = rand() % initial;
                        }
                    }
                    pre = static_cast<int>(timer / timer_set);
                    prev_live = a;
                    if (monster_appear)
                        monster->specify_values(arrays);
                    if (dragon_appear)
                        dragon->specify_values(arrays);
                    a = p->setcurrentposition(arrays, number);
                    next_live = a;
                    if (a)
                    {
                        // if(prev_live!=next_live && next_live!=false){
                        // lives--;
                        // }
                        return;
                    }
                    if (!inv->arrs2[alpha])
                    {
                        prev_live = to_move;
                        to_move = p->move_bullet(alpha, arrays, number, proceed, inv->count, inv->arrs2, inv->enemy, inv->enemy2);
                        // to_move = bullets->Bullet(alpha, arrays, number, proceed, inv->count, inv->arrs2, inv->enemy, inv->enemy2);
                        next_live = to_move;
                        // cout<<"Youu losses"<<endl;
                        if (to_move == false)
                        {
                            inv->arrs2[alpha] = true;
                            if(prev_live!=next_live && next_live!=true && generate_powerup){
                                lives--;
                            }
                        }
                    }
                    // else{
                    // inv->count[alpha] = 0;
                    // }
                    sec1_clock.restart();
                }
                // while (sec2_clock.getElapsedTime().asSeconds() >= 0.3)
                // {
                // sec2_clock.restart();
                // }
                if (monster_appear)
                {
                    prev_live1 = to_move1;
                    to_move1 = monster->check_enemy(arrays);
                    next_live1 = to_move1;
                    if(!to_move1){
                        if(prev_live1!=next_live1 && next_live1!=true){
                            lives--;
                            tomove = false;
                        }
                    }
                }
                if (dragon_appear)
                {
                    to_move = dragon->check_enemy(arrays);
                }
                if (!to_move && dragon_appear)
                {
                    lives--;
                }
                while (window.pollEvent(e))
                {
                    if (e.type == Event::KeyPressed)
                    {
                        if (Keyboard::isKeyPressed(Keyboard::Space))
                        {
                            if (monster_appear)
                                monster->specify_values(arrays);
                            if (dragon_appear)
                                dragon->specify_values(arrays);
                            while (sec0_clock.getElapsedTime().asSeconds() >= 0.24)
                            {
                                fir->settime(p->get_x(), p->get_y());
                                move = fir->move_it(arrays, xval, yval, torepeat, Fires->image);
                                if(move && (monster_appear || dragon_appear)){incre_pre-=10;}
                                if(!monster_appear && !dragon_appear){incre_pre = 100;}
                                sec0_clock.restart();
                            }
                        }
                    }
                }
                // string movement;
                if (Keyboard::isKeyPressed(Keyboard::Escape))
                {
                    iscontinue = false;
                    continue;
                }
                if (Keyboard::isKeyPressed(Keyboard::Left))
                {
                    p->move("l", arrays);
                }
                if (Keyboard::isKeyPressed(Keyboard::Right))
                {
                    p->move("r", arrays);
                }
                if (Keyboard::isKeyPressed(Keyboard::Up))
                {
                    p->move("u", arrays);
                }
                if (Keyboard::isKeyPressed(Keyboard::Down))
                {
                    p->move("d", arrays);
                }
                window.clear();
                window.draw(background);
                window.draw(p->sprite); // setting player on screen
                for (int i = 0; i < 10; i++)
                {
                    if (fir->laser_array[i] != false)
                    {
                        window.draw(fir->sprite1[i]);
                        if (torepeat)
                        {
                            window.draw(fir->sprite2[i]);
                            window.draw(fir->sprite3[i]);
                            window.draw(fir->sprite4[i]);
                            window.draw(fir->sprite5[i]);
                            window.draw(fir->sprite6[i]);
                            window.draw(fir->sprite7[i]);
                        }
                    }
                }
                int count = 0, count1 = 0;
                for (int i = 0; i < 14; i++)
                {
                    if (inv->arrs1[i])
                    {
                        count++;
                    }
                }
                for (int i = 0; i < 8; i++)
                {
                    if (alpha_invader->arras[i] == 0)
                    {
                        count1++;
                    }
                }
                int counting = 0;
                if (number == 1 && !monster_appear && !dragon_appear)
                {
                    for (int i = 0; i < 14; i++)
                    {
                        if (!inv->arrs1[i])
                        {
                            window.draw(inv->enemy[i]);
                        }
                        else
                        {
                            counting++;
                        }
                    }
                }
                else if (number == 2 && !monster_appear && !dragon_appear)
                {
                    for (int i = 0; i < 8; i++)
                    {
                        if (alpha_invader->arras[i])
                        {
                            window.draw(alpha_invader->enemy[i]);
                        }
                        else
                        {
                            counting++;
                        }
                    }
                }
                else if (number == 3 && !monster_appear && !dragon_appear)
                {
                    for (int i = 0; i <= 8; i++)
                    {
                        if (cinvader->arras[i])
                        {
                            window.draw(cinvader->enemy[i]);
                        }
                        else
                        {
                            counting++;
                        }
                    }
                }
                else if (number == 4 && !monster_appear && !dragon_appear)
                {
                    for (int i = 0; i < 8; i++)
                    {
                        if (cenemy->arras[i])
                        {
                            window.draw(cenemy->enemy[i]);
                        }
                        else
                        {
                            counting++;
                        }
                    }
                }
                else if (number == 5 && !monster_appear && !dragon_appear)
                {
                    for (int i = 0; i < 8; i++)
                    {
                        if (henemy->arras[i])
                        {
                            window.draw(henemy->enemy[i]);
                        }
                        else
                        {
                            counting++;
                        }
                    }
                }
                else if(number==6 && !monster_appear && !dragon_appear)
                {
                    for (int i = 0; i < 9; i++)
                    {
                        if (i == 5 ? tenemy->arras[8] : i == 8 ? tenemy->arras[5]: tenemy->arras[i])
                        {
                            window.draw(tenemy->enemy[i]);
                        }
                        else
                        {
                            counting++;
                        }
                    }
                }
                else if(number==7 && !monster_appear && !dragon_appear){
                    for (int i = 0; i < 13; i++)
                    {
                        if (cfenemy->arras[i])
                        {
                            window.draw(cfenemy->enemy[i]);
                        }
                        else
                        {
                            counting++;
                        }
                    }
                }
                else if(number==8 &&  !monster_appear && !dragon_appear){
                    for (int i = 0; i < 12; i++)
                    {
                        if (i == 5 ? tfenemy->arras[8] : i == 8 ? tfenemy->arras[5]: tfenemy->arras[i])
                        {
                            window.draw(tfenemy->enemy[i]);
                        }
                        else
                        {
                            counting++;
                        }
                    }   
                }
                if ((counting == 14 && number == 1) || (counting == 8 && number == 2) || (counting == 9 && number == 3) || (counting == 8 && number == 4) || (counting == 8 && number == 5) || (counting == 9 && number == 6)|| (counting == 13 && number == 7)|| (counting == 12 && number == 8))
                {
                    for (int i = 0; i < 21; i++)
                    {
                        for (int j = 0; j < 20; j++)
                        {
                            arrays[i][j] = 0;
                        }
                    }
                    // Fires->generate_location();
                    if (number == 1)
                    {
                        level = 1;
                        timer_set = 3;
                        points = 20;
                        number = 2;
                        initial = 8;
                    }
                    else if (number == 2)
                    {
                        level = 1;
                        timer_set = 2;
                        points = 30;
                        number = 3;
                        initial = 9;
                    }
                    else if (number == 3)
                    {
                        level = 2;
                        timer_set = 5;
                        points = 10;
                        number = 4;
                        initial = 8;
                        alphas1 = 0;
                    }
                    else if (number == 4)
                    {
                        level = 2;
                        timer_set = 3;
                        points = 20;
                        number = 5;
                        initial = 8;
                    }
                    else if (number == 5)
                    {
                        level = 2;
                        timer_set = 2;
                        points = 30;
                        number = 6;
                        initial = 9;
                    }
                    else if (number == 6)
                    {
                        level = 3;
                        timer_set = 3;
                        points = 10;
                        number = 7;
                        initial = 13;
                        alphas1 = 0;
                    }
                    else if (number == 7)
                    {
                        level = 3;
                        timer_set = 2;
                        points = 20;
                        number = 8;
                        initial = 12;
                    }
                    else if (number == 8)
                    {
                        level = 1;
                        timer_set = 5;
                        points = 10;
                        number = 1;
                        initial = 14;
                        alphas1 = 0;
                    }

                    if (number == 4)
                    {
                        iscontinue = false;
                        toshow = true;
                        continue;
                    }
                    delete inv, alpha_invader, cinvader, cenemy, henemy, tenemy, cfenemy, tfenemy, fir, p, pu, da, Fires, monster;

                    p = new SpaceShip("img/player_ship.png");
                    fir = new fire(p->get_x(), p->get_y());
                    inv = new Invader();
                    alpha_invader = new alpha_inavder_triangle();
                    cinvader = new cross_invader();
                    cenemy = new circle_enemy();
                    henemy = new heart_enemy();
                    tenemy = new triangle_enemy();
                    cfenemy = new circle_filled_enemy();
                    tfenemy = new triangle_filled_enemy();
                    pu = new Powerup();
                    da = new Danger();
                    Fires = new Fire();
                    monster = new Monster();
                    inv->bombs(number);
                    if(number==4 || number==1){iscontinue = false;}
                }
                if (!inv->arrs2[alpha])
                {
                    window.draw(inv->enemy2[alpha]);
                }
                if (monster_appear)
                {
                    window.draw(monster->monster);
                    if ((monster->monster_show))
                    {
                        for (int i = 0; i < 10; i++)
                        {
                            window.draw(monster->beam[i]);
                        }
                    }
                }
                if (dragon_appear)
                {
                    window.draw(dragon->sprites);
                    window.draw(dragon->sprites1);
                    window.draw(dragon->sprites2);
                    if ((dragon->dragon_show))
                    {
                        window.draw(dragon->light[0]);
                        window.draw(dragon->light[1]);
                        for (int i = 0; i < 10; i++)
                        {
                            window.draw(dragon->beam[i]);
                        }
                    }
                }
                if (!move)
                {
                    // window.draw(enemy->sprite2);
                }
                if (powershow)
                {
                    window.draw(pu->powerup);
                }
                if (dangershow)
                {
                    window.draw(da->danger);
                }
                window.draw(la);
                if(monster_appear){
                    string a = "Monster Power Left\n\t  ";
                    a += to_string(incre_pre);
                    a +="%";
                    menu->frequency.setString(a);
                    window.draw(menu->frequency);
                }
                if(dragon_appear){
                    string a = "Dragon Power Left\n\t  ";
                    a += to_string(incre_pre);
                    a +="%";
                    menu->frequency.setString(a);
                    window.draw(menu->frequency);
                }
                window.draw(menu->liveleft);
                menu->lives.setString(to_string(lives));
                window.draw(menu->lives);
                window.draw(menu->scores);
                window.draw(menu->score);
                if(valueso==1){
                    window.draw(menu->imgs1[0]);
                }
                else if(valueso==2){
                    window.draw(menu->imgs1[1]);
                }
                else if(valueso==3){
                    window.draw(menu->imgs1[2]);
                }
                window.display(); // Displying all the sprites
            }
        }
    }
};

#include <SFML/Graphics.hpp> //includes SFML libraries
#include <SFML/Audio.hpp>
#include <iostream>

using namespace std;
using namespace sf; //for graphics

int main()
{
    RenderWindow window(VideoMode(800,600),"RIP AND TEAR UNTIL IT IS DONE", Style::Titlebar | Style::Close);  //creates a window on the screen that is 800 by 600
    window.setFramerateLimit(60); //sets the game loop to run 60 times per second

    // Invisible cursor for gun and crosshair
    window.setMouseCursorVisible(false);

    //Textures
    Texture gun,hair,shot,zombie,title,pist,shott,bac;
    hair.loadFromFile("a.png");
    gun.loadFromFile("s.png");
    shot.loadFromFile("shot.png");
    zombie.loadFromFile("aaa.png");
    title.loadFromFile("ttt.png");
    pist.loadFromFile("pist.png");
    shott.loadFromFile("shottt.png");
    bac.loadFromFile("back.png");

    //Sprites
    Sprite gunn,titl,pistt,ba;
    gunn.setTexture(gun);
    pistt.setTexture(pist);
    titl.setTexture(title);
    ba.setTexture(bac);
    ba.setPosition(-100,-800);
    gunn.setScale(1.3,1.3);
    titl.setPosition(0,0);
    pistt.setPosition(500,400);

    //Crosshair
    CircleShape r;
    r.setRadius(10);
    r.setOrigin(10,10);
    r.setTexture(&hair);
    r.setScale(2,2);

    //Sound Files
    SoundBuffer a,b,c,d,e,k;
    a.loadFromFile("gunsh.ogg");
    b.loadFromFile("gunre.ogg");
    c.loadFromFile("shotsh.ogg");
    d.loadFromFile("shotre.ogg");
    e.loadFromFile("empty.ogg");
    k.loadFromFile("DOOM.ogg");

    //Sounds
    Sound  f,g,h,i,j,l;
    f.setBuffer(a);
    g.setBuffer(b);
    h.setBuffer(c);
    i.setBuffer(d);
    j.setBuffer(e);
    l.setBuffer(k);

    //Vectors for the opponent,their sizes and deaths
    vector<RectangleShape> targets;
    vector<float> sizes;
    vector <bool> dead(targets.size(),false);

    //Font
    Font ffff;
    ffff.loadFromFile("fff.otf");


    //Time
    Clock target_clock;

    //Current Gun
    int cGun = 1;

    //Counters for animation
    int counter = 0;
    int counter2 = 0;
    int counter3 = 0;
    int counter4 = 0;

    //Ammo
    int bullets = 7;
    int shotbullets = 2;

    //Shoot and Reload
    bool shoot = false;
    bool reload = false;

    //Intro bool
    bool ee = true;

    //Ammo to Text(shottt is for pistol bullets and pissst is for shotgun bullets)
    Text shottt;
    shottt.setFont(ffff);
    shottt.setCharacterSize(70);
    shottt.setFillColor(Color::White);
    shottt.setPosition(700, 425);
    shottt.setString(to_string(bullets));

    Text pissst;
    pissst.setFont(ffff);
    pissst.setCharacterSize(70);
    pissst.setFillColor(Color::White);
    pissst.setPosition(700, 425);
    pissst.setString(to_string(shotbullets));


    //DOOM MUSIC on a loop
    l.play();
    l.setLoop(true);

    while (window.isOpen()&& !Keyboard::isKeyPressed(Keyboard::Escape) && Style::Titlebar | Style::Close)     //the main game loop, exits if someone closes the window
    {
        Event event; //creates an event object, events include mouse clicks, mouse movement, keyboard presses, etc..
        while (window.pollEvent(event)) //loop that checks for events
        {
            if (event.type == Event::Closed) //checks if window is closed
                window.close();
        }

        //Intro using the clock
        if (ee && target_clock.getElapsedTime().asSeconds() < 5)
        {
            counter4++;
            titl.setTextureRect(IntRect((counter4 / 7 % 20) * 800,0 , 800, 600));
            window.clear();
            window.draw(titl);
            window.display();
        }
        else
        {
            ee = false;


        //Checks gun equipment
        if (Keyboard::isKeyPressed(Keyboard::Num1))
        {
            pistt.setTexture(pist);
            cGun = 1;
            gunn.setTexture(gun);
        }
        else if (Keyboard::isKeyPressed(Keyboard::Num2))
        {

            pistt.setTexture(shott);
            cGun = 2;
            gunn.setTexture(shot);
        }

        //Killing of targets
        for (int i = 0; i < targets.size(); i++)
        {
            //This floatRect is used to act as a shotgun blast since it has more area of damage than pistol
            FloatRect shotblast(Mouse::getPosition(window).x - 75,Mouse::getPosition(window).y - 75,2 * 75,2 * 75);

            //Pistol
            if(!reload && shoot && cGun == 1 && targets[i].getGlobalBounds().contains(Mouse::getPosition(window).x,Mouse::getPosition(window).y)&& Mouse::isButtonPressed(Mouse::Left) && bullets+1 > 0 ){
            dead[i] = true;
            counter3 = 0;
            }

            //Shotgun
            if(!reload && shoot && cGun == 2 && targets[i].getGlobalBounds().intersects(shotblast) && Mouse::isButtonPressed(Mouse::Left) && shotbullets+1 > 0 ){
            dead[i] = true;
            counter3 = 0;
        }
        }

        //Pistol Firing + sound
        if (cGun == 1 && Mouse::isButtonPressed(Mouse::Left)&& bullets > 0 && !shoot && !reload)
        {
            f.play();
            shoot = true;
            counter = 0;
            bullets--;
        }

        //Empty gun sound when bullets == 0
        else if (cGun == 1 && Mouse::isButtonPressed(Mouse::Left) && bullets == 0 && !shoot ){
            j.play();
        }

        //ShotGun Firing + sound
        if (cGun == 2 && Mouse::isButtonPressed(Mouse::Left)&& shotbullets > 0 && !shoot && !reload)
        {
            h.play();
            shoot = true;
            counter = 0;
            shotbullets--;
        }
        //Empty gun sound when shotbullets == 0
         else if (cGun == 2 && Mouse::isButtonPressed(Mouse::Left) && shotbullets == 0 && !shoot){
            j.play();
        }

        //Animation for pistol and Shotgun since they share the same x and y
        if (shoot && counter / 7 < 5)
        {
            //Shake when shooting to add realism
            if (cGun == 1){
                //Small shake
                window.setPosition(Vector2i(550 + rand() % 25, 200 + rand() % 25));
            }
            else{
                //Big shake
                window.setPosition(Vector2i(550 + rand() % 50, 200 + rand() % 50));
            }

            gunn.setTextureRect(IntRect((counter / 7 % 7) * 802, 602, 802, 603));
            counter++;
        }
        else
        {
            shoot = false;
        }

        //Pistol reloading + sound
        if (cGun == 1 && Mouse::isButtonPressed(Mouse::Right) && !reload && bullets < 7)
        {
            g.play();
            reload = true;
            counter = 0;
            bullets = 7;
        }

        //ShotGun reloading + sound
        if (cGun == 2 && Mouse::isButtonPressed(Mouse::Right) && !reload && shotbullets < 2)
        {
            i.play();
            reload = true;
            counter = 0;
            shotbullets = 2;
        }

        //Reload Animation
        if (reload && counter / 7 < 18)
        {
            gunn.setTextureRect(IntRect((counter / 7 % 18) * 802, 1204, 802, 603));
            counter++;
        }
        else
        {
            reload = false;
        }

        //idle gun animation
        if (!Mouse::isButtonPressed(Mouse::Left) && !Mouse::isButtonPressed(Mouse::Right) && reload == false && shoot == false ){
           gunn.setTextureRect(IntRect(1 , 1, 802, 603));
           }
        //Setting position and size/scale for targets. Srand(time(NULL)) is used to maximize randomness
        if (target_clock.getElapsedTime().asSeconds() > rand() % 1 + 0.7) {
            target_clock.restart();
            srand(time(NULL));
            sizes.push_back(0.5);
            targets.push_back(RectangleShape());
            if ( rand() % 2 + 1 == 1){
            targets.back().setPosition(rand() % 495 + rand() % 70 - rand() % 99 + rand() % 90 - rand() % 50 + rand() % 20 ,50);
            } else {
            targets.back().setPosition(rand() % 400 + rand() % 80 - rand() % 90 + rand() % 120 - rand() % 60 + rand() % 70 - rand() % 360 ,50);
            }
            targets.back().setSize(Vector2f(30,50));

        }




        //Gun and crosshair position
        gunn.setPosition(Mouse::getPosition(window).x- 500,Mouse::getPosition(window).y-450);
        r.setPosition(Mouse::getPosition(window).x,Mouse::getPosition(window).y);

        window.clear();

        //Erasing of Targets and their sizes(and increasing sizes for realisim)(and animation)
        for (int i = 0; i < targets.size(); i++){
            targets[i].setTexture(&zombie);
            if (dead[i] == true && counter3 / 9 < 6)
            {
            targets[i].setTextureRect(IntRect((counter3 / 9 % 6) * 192, 200, 192, 200));
            counter3++;
            }
            else if (dead[i] == true && counter3 / 9 == 6){
            targets.erase(targets.begin()+ i);
            sizes.erase(sizes.begin() + i);
            dead.erase(dead.begin() + i);
            dead[i] = false;
            }
            else
            {
            dead[i] = false;
            targets[i].setTextureRect(IntRect((counter3 / 12 % 12) * 192, 0, 192, 200));
            counter3++;
            sizes[i] += 0.02;
            targets[i].setScale(sizes[i], sizes[i]);
            }

        }

        //Background
        window.draw(ba);

        //Drawing targets and size condition
        for(int i = 0; i < targets.size(); i++)
        {
            if(sizes[i] > 14){
               return 0;
            }

            window.draw(targets[targets.size()-1-i]);
        }

        //Counter increase for animation
        counter2++;
        counter++;

        //Ammo Update
        pissst.setString(to_string(bullets));
        shottt.setString(to_string(shotbullets));

        //Drawing
        window.draw(r);
        window.draw(gunn);
        window.draw(pistt);

        //Drawing ammo based on equipment
        if(cGun == 1){
         window.draw(pissst);
        }
        else{
        window.draw(shottt);
        }
        window.display();   //displays everything on the video card to the monitor
    }   //ends the game loop
    }
    return 0;
}

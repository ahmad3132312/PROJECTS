//█░░ █ █▄▄ █▀█ ▄▀█ █▀█ █▄█ █▀
//█▄▄ █ █▄█ █▀▄ █▀█ █▀▄ ░█░ ▄█

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <math.h>

using namespace std;
using namespace sf;
//░░█ █░█ █▀▄▀█ █▀█ █ █▄░█ █▀▀
//█▄█ █▄█ █░▀░█ █▀▀ █ █░▀█ █▄█

// X and Y position
float pX = 100.0f;
float pY = 175.0f;

// X and Y velocity
float vX = 4.0f;
float vY = 0.0f;
//Gravity
float gravity = 0.5f;
//Check if the knight is on ground
bool onG = false;
// JUMP BOOST OF -12
void StartJump() {
    if (onG) {
        vY = -12.0f;
        onG = false;
    }
}
// Updates to make a jump
void Update() {
    vY += gravity;
    pY += vY;
    pX += vX;

    if (pY > 175.0f) {
        pY = 175.0f;
        vY = 0.0f;
        onG = true;
    }

    if (pX < 10.0f || pX > 190.0f)
        vX *= -1.0f;
}
//█▀▀ █▀█ █░░ █░░ █ █▀ █ █▀█ █▄░█
//█▄▄ █▄█ █▄▄ █▄▄ █ ▄█ █ █▄█ █░▀█

// Checks Collision using intersects
bool CheckCollision(const Sprite& sprite1, const Sprite& sprite2) {
    return sprite1.getGlobalBounds().intersects(sprite2.getGlobalBounds());
}

int main() {
    //█░█░█ █ █▄░█ █▀▄ █▀█ █░█░█
    //▀▄▀▄▀ █ █░▀█ █▄▀ █▄█ ▀▄▀▄▀
    RenderWindow window(VideoMode(800, 600), "FINAL BYE");
    window.setFramerateLimit(60);

    //█░█ █▀▀ █▀▀ ▀█▀ █▀█ █▀█ █▀
    //▀▄▀ ██▄ █▄▄ ░█░ █▄█ █▀▄ ▄█
    vector<Sprite> targets;
    vector<bool> dead;

    //█▀ █▀█ █░█ █▄░█ █▀▄ █▄▄ █░█ █▀▀ █▀▀ █▀▀ █▀█
    //▄█ █▄█ █▄█ █░▀█ █▄▀ █▄█ █▄█ █▀░ █▀░ ██▄ █▀▄
    SoundBuffer kl, nm, bm, lm, pm;
    kl.loadFromFile("The Convenience Store _ Music.ogg");
    nm.loadFromFile("Super Ghoulsn Ghosts Music Haunted Graveyard Extended.ogg");
    bm.loadFromFile("Sword SFX 4.ogg");
    lm.loadFromFile("MONEY SOUND EFFECT !!.ogg");
    pm.loadFromFile("g.ogg");

    //█▀ █▀█ █░█ █▄░█ █▀▄
    //▄█ █▄█ █▄█ █░▀█ █▄▀
    Sound kll, nmm, bmm, lmm, pmm;
    kll.setBuffer(kl);
    nmm.setBuffer(nm);
    bmm.setBuffer(bm);
    lmm.setBuffer(lm);
    pmm.setBuffer(pm);

    //▀█▀ █▀▀ ▀▄▀ ▀█▀ █░█ █▀█ █▀▀ █▀
    //░█░ ██▄ █░█ ░█░ █▄█ █▀▄ ██▄ ▄█
    Texture b, g, k, p, Back, Kni, en;
    b.loadFromFile("jjjj.png");
    g.loadFromFile("op.png");
    k.loadFromFile("buy.png");
    p.loadFromFile("in.png");
    Back.loadFromFile("test_2.png");
    Kni.loadFromFile("spritesheet (10).png");
    en.loadFromFile("spritesheet (2).png");

    //█▀ █▀█ █▀█ █ ▀█▀ █▀▀ █▀
    //▄█ █▀▀ █▀▄ █ ░█░ ██▄ ▄█
    Sprite knight, a, l, kk, pp, background;
    a.setTexture(b);
    a.setPosition(50, 100);
    a.setScale(1.3, 1.3);
    l.setTexture(g);
    kk.setTexture(k);
    kk.setScale(0.4, 0.4);
    kk.setPosition(375, 50);
    pp.setTexture(p);
    pp.setPosition(100, 100);
    background.setPosition(0, -400);
    background.setTexture(Back);
    knight.setTexture(Kni);
    knight.setPosition(400, 300);

    //█▀▀ █░░ █▀█ █▀▀ █▄▀
    //█▄▄ █▄▄ █▄█ █▄▄ █░█
    Clock c, target_clock;

    //█▀▀ █▀█ █░█ █▄░█ ▀█▀ █▀▀ █▀█ █▀   █▀▀ █▀█ █▀█   ▄▀█ █▄░█ █ █▀▄▀█ ▄▀█ ▀█▀ █ █▀█ █▄░█
    //█▄▄ █▄█ █▄█ █░▀█ ░█░ ██▄ █▀▄ ▄█   █▀░ █▄█ █▀▄   █▀█ █░▀█ █ █░▀░█ █▀█ ░█░ █ █▄█ █░▀█

    // For Final game and ps2 intro
    int counter = 0;
    // For walking animation(knight)
    int counter2 = 0;
    // For Attaking animation(knight)
    int counter3 = 0;
    // For Blocking animation(knight)
    int counter4 = 0;
    // For idle animation(knight)
    int counter5 = 0;
    // For targets walking
    int counter6 = 0;
    // For targets attackig
    int counter7 = 0;


    //█▄▄ █▀█ █▀█ █░░
    //█▄█ █▄█ █▄█ █▄▄

    //For button on the start
    bool buy = false;
    //For start of game
    bool start = false;
    //For checking attack for knight
    bool ATTAK = false;
    //For checking blocking For kinght
    bool DEF = false;
    // To differentiate when the knight is pointing left or right
    bool left = false;
    //For checing attack for targets
    bool att = false;


    //Playing the store music(seting volume 100)
    kll.setVolume(100);
    kll.play();

    while (window.isOpen() && !Keyboard::isKeyPressed(Keyboard::Escape)) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        counter++;
        if (buy == false) {
            // Game 3d rotation animation
            a.setTextureRect(IntRect(counter / 5 % 37 * 211, 0, 211, 258));
            //Hover effect for button
            if (kk.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y)) {
                kk.setScale(0.43, 0.43);
            } else {
                kk.setScale(0.4, 0.4);
            }

            //Button pressed
            if (kk.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y) &&
                Mouse::isButtonPressed(Mouse::Left)) {
                //Pause the store music
                kll.pause();
                //Play the buy music
                lmm.play();
                buy = true;
                c.restart();
                counter = 0;
            }
        }

        if (c.getElapsedTime().asSeconds() < 1) {
            //PS2 Intro Animation
            pp.setTextureRect(IntRect(counter / 3 % 28 * 602, 0, 602, 340));
        }

        window.clear();

        if (buy == false) {
            //if you dont press the button it will continue to draw the store screen
            window.draw(l);
            window.draw(kk);
            window.draw(a);
        }

        if (buy == true && c.getElapsedTime().asSeconds() < 2) {
            //Play game music
            nmm.setVolume(100);
            nmm.play();
            //PS2 animation drawing
            window.draw(pp);
            start = true;
        }

        if (start == true && c.getElapsedTime().asSeconds() > 2) {
            //Background scrolling
            background.move(-4, 0);
            //Resets the position of background if image ends
            if (background.getPosition().x <= -2080) {
                background.setPosition(-700, -400);
            }
            //Ends game if you are at the back
            if (knight.getPosition().x <= -70) {
                return 0;
            }
            //Update for jump
            Update();

            //Scaling knight
            knight.setScale(2, 3);

            //Checks if knight is on ground if not moves him down
            if (!onG) {
                knight.move(0, vY);
            }

            //█▀▄▀█ █▀█ █░█ █▀▀ █▀▄▀█ █▀▀ █▄░█ ▀█▀
            //█░▀░█ █▄█ ▀▄▀ ██▄ █░▀░█ ██▄ █░▀█ ░█░
            counter2++;
            if (Keyboard::isKeyPressed(Keyboard::A) && !DEF && !ATTAK) {
                knight.move(-6, 0);
                knight.setTextureRect(IntRect((counter2 / 7 % 8) * 100, 165, 100, 55));
                left = true;
            }
            if (Keyboard::isKeyPressed(Keyboard::D) && !DEF && !ATTAK) {
                knight.move(6, 0);
                knight.setTextureRect(IntRect((counter2 / 7 % 8) * 100, 110, 100, 55));
                left = false;

            //▄▀█ ▀█▀ ▀█▀ ▄▀█ █▀▀ █▄▀
            //█▀█ ░█░ ░█░ █▀█ █▄▄ █░█
            } else if (Keyboard::isKeyPressed(Keyboard::J) && !ATTAK) {
                bmm.play();
                ATTAK = true;
                //Resets counter3 to loop
                counter3 = 0;

            //█▄▄ █░░ █▀█ █▀▀ █▄▀ █ █▄░█
            //█▄█ █▄▄ █▄█ █▄▄ █░█ █ █░▀█
            } else if (Keyboard::isKeyPressed(Keyboard::K) && !DEF) {
                pmm.play();
                DEF = true;
                //Resets counter4 to loop
                counter4 = 0;
            }
            //░░█ █░█ █▀▄▀█ █▀█
            //█▄█ █▄█ █░▀░█ █▀▀
            if (Keyboard::isKeyPressed(Keyboard::W) && !DEF && !ATTAK) {
                StartJump();
            }

            //▄▀█ ▀█▀ ▀█▀ ▄▀█ █▀▀ █▄▀   ▄▀█ █▄░█ █ █▀▄▀█ ▄▀█ ▀█▀ █ █▀█ █▄░█
            //█▀█ ░█░ ░█░ █▀█ █▄▄ █░█   █▀█ █░▀█ █ █░▀░█ █▀█ ░█░ █ █▄█ █░▀█

            //Same used in assignment 3
            if (ATTAK && counter3 / 7 < 6) {
                //Moves back because you cant move when attaking
                knight.move(-1, 0);
                counter3++;
                if (left == true && onG) {
                    knight.setTextureRect(IntRect((counter3 / 7 % 6) * 100, 385, 100, 55));
                }
                if (left == false && onG) {
                    knight.setTextureRect(IntRect((counter3 / 7 % 6) * 100, 330, 100, 55));
                }
                }
                else {
                    ATTAK = false;
                }

            //█▄▄ █░░ █▀█ █▀▀ █▄▀   ▄▀█ █▄░█ █ █▀▄▀█ ▄▀█ ▀█▀ █ █▀█ █▄░█
            //█▄█ █▄▄ █▄█ █▄▄ █░█   █▀█ █░▀█ █ █░▀░█ █▀█ ░█░ █ █▄█ █░▀█

            //Same used in assignment 3
            if (DEF && counter4 / 7 < 4) {
                //Moves back because you cant move when blocking
                knight.move(-1, 0);
                counter4++;
                if (left == true && onG) {
                    knight.setTextureRect(IntRect((counter4 / 7 % 4) * 100, 495, 100, 55));
                }
                if (left == false && onG) {
                    knight.setTextureRect(IntRect((counter4 / 7 % 4) * 100, 440, 100, 55));
                }
                }
                else {
                    DEF = false;
                }

            //█ █▀▄ █░░ █▀▀   ▄▀█ █▄░█ █ █▀▄▀█ ▄▀█ ▀█▀ █ █▀█ █▄░█
            //█ █▄▀ █▄▄ ██▄   █▀█ █░▀█ █ █░▀░█ █▀█ ░█░ █ █▄█ █░▀█
            if (!(Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::W)) && !DEF && !ATTAK) {
                //Moves back because you don't move
                knight.move(-4, 0);
                counter5++;
                if (left == true && onG) {
                    knight.setTextureRect(IntRect((counter5 / 7 % 8) * 100, 275, 100, 55));
                }
                if (left == false && onG) {
                    knight.setTextureRect(IntRect((counter5 / 7 % 8) * 100, 220, 100, 55));
                }
            }
            //Background scaling
            background.setScale(2, 2);

            //Drawing background and knight
            window.draw(background);
            window.draw(knight);

            //▀█▀ ▄▀█ █▀█ █▀▀ █▀▀ ▀█▀ █▀
            //░█░ █▀█ █▀▄ █▄█ ██▄ ░█░ ▄█

            //Creates a target every 2 sec
            if (target_clock.getElapsedTime().asSeconds() > 2) {
                target_clock.restart();
                targets.push_back(Sprite());
                targets.back().setTexture(en);
                targets.back().setPosition(600, 275);
                dead.push_back(false);
            }

            //Erases enemies
            for (int i = 0; i < targets.size(); i++) {
                if (dead[i] == true && counter7 / 2 == 16) {
                    targets.erase(targets.begin() + i);
                    dead.erase(dead.begin() + i);
                    dead[i] = false;
                }
            }

            for (int i = 0; i < targets.size(); i++) {

                //Detecting the player
                Vector2f direction = knight.getPosition() - targets[i].getPosition();
                float length = sqrt(direction.x * direction.x + direction.y * direction.y);
                if (length != 0) {
                    direction /= length;
                }

                //Speed of enemys
                float eS = 8.0f;

                //if the attack landed of=n an enemy dead[i] true
                if (ATTAK && length < 100 && dead[i] == false) {
                    dead[i] = true;
                    counter7 = 0;
                }
                //▀█▀ ▄▀█ █▀█ █▀▀ █▀▀ ▀█▀ █▀   ▄▀█ █▄░█ █ █▀▄▀█ ▄▀█ ▀█▀ █ █▀█ █▄░█
                //░█░ █▀█ █▀▄ █▄█ ██▄ ░█░ ▄█   █▀█ █░▀█ █ █░▀░█ █▀█ ░█░ █ █▄█ █░▀█


                //DEAD ANIMATIOn

                //does animation based on the placement of the target relative to the knight
                if (dead[i] == true && counter7 / 2 < 16) {
                    if (direction.x * eS > 1) {
                        targets[i].setTextureRect(IntRect((counter7 / 2 % 16) * 240, 960, 240, 240));
                        counter7++;
                    } else {
                        targets[i].setTextureRect(IntRect((counter7 / 2 % 16) * 240, 1200, 240, 240));
                        counter7++;
                    }
                } else {
                    dead[i] = false;
                    counter6++;
                    if (direction.x * eS > 1) {
                        //ATTAKING THE PLAYER
                        if (length < 100) {
                            counter7++;
                            att = true;
                            targets[i].setTextureRect(IntRect((counter7 / 7 % 12) * 240, 480, 240, 240));
                            //IF YOU DONT DEFEND THE ATTACK YOU WILL BE DEAD
                            if (att && counter7 / 7 == 12 && !DEF) {
                                return 0;
                            }
                        } else {
                            //WALKING ANIMATION
                            att = false;
                            targets[i].setTextureRect(IntRect((counter6 / 7 % 6) * 240, 0, 240, 240));
                        }
                    } else {
                        if (length < 100) {
                            //ATTAKING THE PLAYER
                            counter7++;
                            att = true;
                            targets[i].setTextureRect(IntRect((counter7 / 7 % 12) * 240, 720, 240, 240));
                             //IF YOU DONT DEFEND THE ATTACK YOU WILL BE DEAD
                            if (att && counter7 / 7 == 12 && !DEF) {
                                return 0;
                            }
                        } else {
                             //WALKING ANIMATION
                            att = false;
                            targets[i].setTextureRect(IntRect((counter6 / 7 % 6) * 240, 240, 240, 240));
                        }
                    }
                }
                //Moving the enemy based on tge position of the knight
                targets[i].move(direction.x * eS, 0);
                //Drawing the targets
                window.draw(targets[i]);
            }
        }

        window.display();
    }

    return 0;
}

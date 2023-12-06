// Title: SFML Doodle Jump
// Goal: To get acquinted with C++ and SFML
// Author: Ryan Rumana
// Copywrite use: Just don't claim it's yours
// Date Fist Compiled: September 4th, 2019
// Date Last Compiled: October 1st, 2019

// include statements
#include <iostream> 
#include <time.h>
#include <vector>
#include <algorithm>
#include <iterator>
#include <string>

// Additonal dependencies
#include <SFML/Graphics.hpp>

// Create structs, similar to a class but defaulted to public visibility
struct point{ 
	int x, y;
	bool broken = false;
	bool brown = false;
	int dy = 0;
};

struct movingObj{
	int x, y;
	int vY = 0;
};

// Public instance variables
std::vector<movingObj> bulletsObj;
std::vector<sf::Sprite> bulletsSprite;
bool firing = false;
bool right = true;
int score = 0;
std::string scoreString;
bool death;

int main()
{
	// Set the game time to 0 at the start of the program
	srand(time(0));

	// Create a render window in SFML
	sf::RenderWindow window(sf::VideoMode(1500, 2000), "Doodle Game");

	// Set framerate
	window.setFramerateLimit(60);

	// Create a SFML texture
	sf::Texture t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11;

	// Load the image onto their respective textures and add a failsafe method
	if (!t1.loadFromFile("images/bg.png")){
		std::cout << "Background Load failed" << std::endl;
		system("pause");}//for background

	if (!t2.loadFromFile("images/static_panel.png")) {
		std::cout << "Green Static Platform Load failed" << std::endl;
		system("pause");}//for platforms

	if (!t3.loadFromFile("images/doodle-right.png")) {
		std::cout << "Right Facing Doodle Load failed" << std::endl;
		system("pause");}//for doodle to the right

	if (!t4.loadFromFile("images/doodle-left.png")) {
		std::cout << "Left facing Doodle Load failed" << std::endl;
		system("pause");}//for doodle to the left

	if (!t5.loadFromFile("images/doodle-jump-right.png")) {
		std::cout << "Right Facing Jumping Doodle Load failed" << std::endl;
		system("pause");}//for doodle to the jumping right

	if (!t6.loadFromFile("images/doodle-jump-left.png")) {
		std::cout << "Left Facing Jumping Doodle Load failed" << std::endl;
		system("pause");}//for doodle to the jumping left

	if (!t7.loadFromFile("images/doodle-pow.png")) {
		std::cout << "Shooting Doodle Load failed" << std::endl;
		system("pause");}//for doodle shooting

	if (!t8.loadFromFile("images/bad_panel1.png")) {
		std::cout << "Brown Pannel Load failed" << std::endl;
		system("pause");}//for the bad pannel solid

	if (!t9.loadFromFile("images/bad_panel2.png")) {
		std::cout << "Broken Brown Pannel Load failed" << std::endl;
		system("pause");}//for the bad pannel broken

	if (!t10.loadFromFile("images/1jump_panel.png")) {
		std::cout << "White Pannel Load failed" << std::endl;
		system("pause");}//for the cloud pannel

	if (!t11.loadFromFile("images/shot.png")) {
		std::cout << "Bullet Load failed" << std::endl;
		system("pause");}//for shot 

	// Create a SFML sprite, set its texture to the previously made texture
	sf::Sprite sBackground(t1), sPlat(t2), sBrokenPlat1(t8), sBrokenPlat2(t9), sPers(t3), sPersFire(t7);

	// Set the scale for the textures to fit the window size
	sBackground.setScale(2.5, 2.86);
	sPlat.setScale(2.50, 2.50);
	sBrokenPlat1.setScale(2.50, 2.50);
	sBrokenPlat2.setScale(2.50, 2.50);
	sPers.setScale(0.50, 0.50);

	//  Create an instance of struct point
	point greenPlatStatic[15];

	// Create a for loop that will place platforms randomly, without placing them on top of each other (mostly)
	for (int i = 0; i < 15; i++) {
		greenPlatStatic[i].x = rand() % 1245;
		greenPlatStatic[i].y = rand() % 2000;
		for (int j = 0; j < 15; j++) {
			if (i == j)
				break;
			if ((greenPlatStatic[i].x - greenPlatStatic[j].x > -250 && greenPlatStatic[i].x - greenPlatStatic[j].x < 250) && //comparing the platofrm x values
				(greenPlatStatic[i].y - greenPlatStatic[j].y > -100 && greenPlatStatic[i].y - greenPlatStatic[j].y < 100)) { //comparing the platofrm y values
				greenPlatStatic[i].x = rand() % 1245;
				greenPlatStatic[i].y = rand() % 2000;
				j = 0;
				break;
			}
		}
	}

	// Allow starting points for position and acceleration
	int x = 750, y = 200, h = 1000;
	float dx = 0, dy = 0; 

	// Main game loop
	while (window.isOpen()) {

		// Create the SFML event that will controll all game events
		sf::Event event;

		// Handle all events
		while (window.pollEvent(event)) {

			// A switch of all of the detectable events and what actions to take when they are detected
			switch (event.type) {
			case sf::Event::Closed: window.close(); break;
			}
		}

		// Update the game
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			x += 15;
			right = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			x -= 15;
			right = false;
		}
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) firing = false;
		if (!firing) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				firing = true;
				movingObj temp;
				temp.x = sPers.getPosition().x + 50;
				temp.y = sPers.getPosition().y;
				temp.vY = -50;
				bulletsObj.push_back(temp);
				sf::Sprite tempS;
				bulletsSprite.push_back(tempS);
			}
		}

		if (x > 1678) x = 0;
		if (x < -178) x = 1322;

		// Setting/changing the y speed
		dy += 0.3;
		y += dy;
		if (y > 2000) {
			dy = 0;
			death = true;}

		// Move all bullets
		for (int i = 0; i < bulletsObj.size(); i++)
		{
			if (y > h)
				bulletsObj[i].y += bulletsObj[i].vY;
			if (y < h)
				bulletsObj[i].y += bulletsObj[i].vY - dy;
			if (bulletsObj[i].y < 0) {
				bulletsObj.erase(bulletsObj.begin());
				bulletsSprite.erase(bulletsSprite.begin());
			}
		}

		// Allowing the platforms to move dynamically
		for (int i = 0; i < 15; i++) {
			greenPlatStatic[i].y += greenPlatStatic[i].dy;
		}
		if (y < h)
			for (int i = 0; i < 15; i++) {
				y = h;
				greenPlatStatic[i].y -= dy;
				if (greenPlatStatic[i].y > 2000) {
					greenPlatStatic[i].y = rand() % 300 - 300;
					greenPlatStatic[i].x = rand() % 1245;
					greenPlatStatic[i].dy = 0;
					greenPlatStatic[i].broken = false;
					if (rand() % 10 == 1){
						greenPlatStatic[i].brown = true;}
					else
						greenPlatStatic[i].brown = false;
					for (int j = 0; j < 15; j++) {
						if (i == j)
							break;
						if ((greenPlatStatic[i].x - greenPlatStatic[j].x > -250 && greenPlatStatic[i].x - greenPlatStatic[j].x < 250) && //comparing the platofrm x values
							(greenPlatStatic[i].y - greenPlatStatic[j].y > -100 && greenPlatStatic[i].y - greenPlatStatic[j].y < 100)) { //comparing the platofrm y values
							greenPlatStatic[i].x = rand() % 1245;
							j = 0;
							break;
						}
					}
					score++;
					scoreString = std::to_string(score);
					std::cout << scoreString << std::endl;
				}
			}

		// Collision algorithm between player and platforms
		for (int i = 0; i < 15; i++)
			if ((x + 89 > greenPlatStatic[i].x) && (x < greenPlatStatic[i].x + 153) && (y + 178 > greenPlatStatic[i].y) && (y + 178 < greenPlatStatic[i].y + 21) && (dy > 0)) {
				if (greenPlatStatic[i].brown) {
					greenPlatStatic[i].broken = true;
					greenPlatStatic[i].dy = 15;

				}
				else
					dy = -20;
			}

		sPers.setPosition(x, y);

		sf::Text text;

		// select the font
		//text.setFont(); //using default font

		// set the string to display
		text.setString(scoreString);

		// set the character size
		text.setCharacterSize(24); // in pixels, not points!

		// set the color
		text.setFillColor(sf::Color::Black);

		// set the text style
		text.setStyle(sf::Text::Bold | sf::Text::Underlined);

		// Clear the window in preparation for drawing a new frame
		window.clear();

		// Draw each element of the new frame here
		window.draw(sBackground);

		for (int i = 0; i < 15; i++) {
			if (greenPlatStatic[i].brown) {
				if (greenPlatStatic[i].broken){
					sBrokenPlat2.setPosition(greenPlatStatic[i].x, greenPlatStatic[i].y);
					window.draw(sBrokenPlat2);}
				else {
					sBrokenPlat1.setPosition(greenPlatStatic[i].x, greenPlatStatic[i].y);
					window.draw(sBrokenPlat1);}
			}
			else {
				sPlat.setPosition(greenPlatStatic[i].x, greenPlatStatic[i].y);
				window.draw(sPlat);}
		}

		// Assign each bullet sprite the bullet texture t11
		for (sf::Sprite& x : bulletsSprite) {
			x.setTexture(t11);
			x.setScale(2.0, 2.0);
		}


		for (int i = 0; i < bulletsObj.size(); i++) {
			bulletsSprite[i].setPosition(bulletsObj[i].x, bulletsObj[i].y);
			window.draw(bulletsSprite[i]);
		}

		if (right) {
			sPers.setTexture(t3);
			sPers.setScale(0.50, 0.50);
			sPersFire.setPosition(x, y - 25);
		}
		else if (!right) {
			sPers.setTexture(t4);
			sPers.setScale(0.50, 0.50);
			sPersFire.setPosition(x + 50, y - 25);
		}
		if (firing) {
			sPersFire.setScale(0.50, 0.50);
			window.draw(sPersFire);
		}
		else
			window.draw(sPers);

		text.setPosition(10.f, 50.f);
		window.draw(text);

		// Tell the window to display the frame
		window.display();
	}

	return EXIT_SUCCESS;
}

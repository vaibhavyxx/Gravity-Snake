//add it on top for safety reasons
#define SFML_STATIC
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include "snake.h"
#include<conio.h>
#include<cstdlib>

using namespace std;
void wrapper();
int main()
{
	wrapper();
	if (_CrtDumpMemoryLeaks()) {
		cout << "Memory Leak detected!";
	}

}
void wrapper() {
	//clock
	sf::Clock deltaClock;
	sf::Clock* clock = &deltaClock;
	sf::Time deltaTime;
	sf::Time* timeSF = &deltaTime;

	bool targetLocked = false;
	//counts for scoring system
	int fairScore = 0;
	int goodScore = 0;
	int excellentScore = 0;
	int score = 0;
	int input = 0;
	int total = 0;
	float timeStep = 1.0f / 60.0f;
	bool running = true;
	//makes the physics world 
	b2Vec2 gravity(0.0f, -1.50f);
	b2World* world = new b2World(gravity);

	//bottom wall- ground
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -20.0f);
	b2Body* groundBody = world->CreateBody(&groundBodyDef);
	b2PolygonShape groundBox;
	groundBox.SetAsBox(25.0f, 5.0f);
	groundBody->CreateFixture(&groundBox, 0.0f);

	//roof wall
	b2BodyDef roofBodyDef;
	roofBodyDef.position.Set(0.0f, 20.0f);
	b2Body* roofBody = world->CreateBody(&roofBodyDef);
	b2PolygonShape roofBox;
	roofBox.SetAsBox(25.0f, 5.0f);
	roofBody->CreateFixture(&roofBox, 0.0f);
	
	//left wall
	b2BodyDef leftBodyDef;
	leftBodyDef.position.Set(-20.0f, 0.0f);
	b2Body* leftBody = world->CreateBody(&leftBodyDef);
	b2PolygonShape leftBox;
	leftBox.SetAsBox(5.0f, 25.0f);
	leftBody->CreateFixture(&leftBox, 0.0f);

	//right wall
	b2BodyDef rightBodyDef;
	rightBodyDef.position.Set(20.0f, 0.0f);
	b2Body* rightBody = world->CreateBody(&rightBodyDef);
	b2PolygonShape rightBox;
	rightBox.SetAsBox(5.0f, 25.0f);
	rightBody->CreateFixture(&rightBox, 0.0f);

	//make a snake
	b2BodyDef snakeBodyDef;
	snakeBodyDef.type = b2_dynamicBody;
	snakeBodyDef.position.Set(0.0f, 4.0f);
	b2Body* snakeBody = world->CreateBody(&snakeBodyDef);

	b2PolygonShape snakeShape;
	snakeShape.SetAsBox(1.0f, 1.0f);

	b2FixtureDef snakeFixureDef;
	snakeFixureDef.shape = &snakeShape;
	snakeFixureDef.density = 1.0f;
	snakeBody->CreateFixture(&snakeFixureDef);

	//for random 
	srand(time(NULL));

	//sets target for the snake
	b2Vec2 targetPos;
	moveTarget(&targetPos);

	//shows game instructions and prompts user to start the game
	string user;
	cout << "Let's play Gravity Snake!" << endl;
	cout << "Use WASD controls to apply forces to your snake.\n";
	cout << "Hit 2 targets to win!\n";
	cout << "If you hit a target within 2 units of its radius, you get 10 points (FAIR)\n" <<
		"20 points if you are within 1.5 units of its radius, (GOOD)\n" <<
		"50 points if you are within less than a unit of its radius (EXCELLENT)\n"
		<< "Hit SPACEBAR to confirm your shot!\n";
	cout << "Press ENTER to start.\n\n";
	getline(cin, user);

	//tracks user input to change snake's forces
	if (user.length() == 0) {
		do {
			//for precision based targets, makes user tap Spacebar
			if (_kbhit()) {
				input = _getch();
				if (input == 32) {
					targetLocked = true;
				}
				applyForces(input, snakeBody);
			}
			update(world, &running, clock, timeSF);
			display(&targetPos, snakeBody);

			//distance check and gives score based on your range
			//use spacebar to finalize your shot
			b2Vec2 difference = targetPos;
			difference -= snakeBody->GetPosition();
			float distanceSq = difference.LengthSquared();

			if (targetLocked && distanceSq < 2) {
				cout << "    (HIT)";
				if (distanceSq < 0.25) {
					score += 50;
					excellentScore++;
				}
				else if (distanceSq < 1 && distanceSq >= 0.25) {
					score += 20;
					goodScore++;
				}
				else if (distanceSq < 2 && distanceSq >= 1) {
					score += 10;
					fairScore++;
				}
				total++;
				moveTarget(&targetPos);
				targetLocked = false;
			}
		} while (total < 2);				
	}
	cout << "\nTotal Score: " << score << endl
		<< "Number of FAIR shots: " << fairScore << endl
		<< "Number of GOOD shots: " << goodScore << endl
		<< "Number of EXCELLENT shots: " << excellentScore <<endl
		<<"Total Time Taken: " << timeSF->asSeconds() <<" seconds";

	delete world;
}
#include "snake.h"
#define SFML_STATIC
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include<conio.h>
#include<cstdlib>
using namespace std;

void moveTarget(b2Vec2* target) {
	float randX = -5.0f + ((rand() % 1000) * 0.01f);
	float randY = -5.0f + ((rand() % 1000) * 0.01f);
	target->x = randX;
	target->y = randY;
}

//gives coordinates for plauer and target
void display(b2Vec2* target, b2Body* snake) {
	b2Vec2 snakePos = snake->GetPosition();
	printf("\nTarget: %.2f, %.2f ---> Snake: %.2f, %.2f", target->x, target->y, snakePos.x, snakePos.y);
}

void applyForces(int key, b2Body* snake) {
	//reads key presses and applies those forces to move
	key = toupper(key);
	if (key == 'W') {
		snake->ApplyForceToCenter(b2Vec2(0.0f, 200.0f), true);
	}
	if (key == 'S') {
		snake->ApplyForceToCenter(b2Vec2(0.0f, -200.0f), true);
	}
	if (key == 'A') {
		snake->ApplyForceToCenter(b2Vec2(-100.0f, 0.0f), true);
	}
	if (key == 'D') {
		snake->ApplyForceToCenter(b2Vec2(100.0f, 0.0f), true);
	}
}
//to make sure all the forces are working
void update(b2World* world, bool* running, sf::Clock* deltaClock, sf::Time* deltaTime) {
	*deltaTime = deltaClock->getElapsedTime();
	deltaClock->restart();
	world->Step(deltaTime->asSeconds(), 6, 2);
}

#pragma once
#define SFML_STATIC
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

void moveTarget(b2Vec2* target);
void applyForces(int key, b2Body* snake);
void update(b2World* world, bool* running, sf::Clock* clock, sf::Time* deltaTime);
void display(b2Vec2* target, b2Body* snake);

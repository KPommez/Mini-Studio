#pragma once

#include "Player.hpp"

using SharedPtrEntityVector_t = vector<shared_ptr<Entity>>;

class EntityManager {
public:
	void updateEntities(RenderWindow& window, float deltaTime);

	// Getters
	shared_ptr<Entity>		checkEntity(const Vector2f& playerPosition, float detectionRange);
	SharedPtrEntityVector_t	getEntities() const { return m_entities; }
	SharedPtrEntityVector_t	getEnnemies() const { return m_ennemies; }
	SharedPtrEntityVector_t	getNPC() const { return m_npc; }
	shared_ptr<Entity>		getObject(string type);

	// Add entities
	weak_ptr<Entity>		addEntity(shared_ptr<Entity> entitySharedPtr);
	weak_ptr<Entity>		addEnnemy(shared_ptr<Entity> entitySharedPtr);
	weak_ptr<Entity>		addNPC(shared_ptr<Entity> entitySharedPtr);
	// Remove entities
	void					removeEntity(shared_ptr<Entity> entitySharedPtr);
	void					deleteAllEnnemy();
	// Draw entities
	void					drawPlayer(RenderWindow& window);
	void					drawEntities(RenderWindow& window);

private:
	SharedPtrEntityVector_t	m_entities;
	SharedPtrEntityVector_t	m_ennemies;
	SharedPtrEntityVector_t m_npc;
};
#pragma once

#include "Player.hpp"

using SharedPtrEntityVector_t = std::vector<std::shared_ptr<Entity>>;

class EntityManager {
public:
	void updateEntities(sf::RenderWindow& window, float deltaTime);

	//GETTERS
	shared_ptr<Entity>								checkEntity(const Vector2f& playerPosition, float detectionRange);
	SharedPtrEntityVector_t							getEntities() const { return m_entities; }
	SharedPtrEntityVector_t							getEnnemies() const { return m_ennemies; }

	SharedPtrEntityVector_t							getNPC() const { return m_npc; }
	shared_ptr<Entity>								getObject(string type);
	

	//ADD REMOVE
	std::weak_ptr<Entity>			addEntity(std::shared_ptr<Entity> entitySharedPtr);
	std::weak_ptr<Entity>			addEnnemy(std::shared_ptr<Entity> entitySharedPtr);
	std::weak_ptr<Entity>			addNPC(std::shared_ptr<Entity> entitySharedPtr);
	
	void drawPlayer(RenderWindow& window);
	void drawEntities(RenderWindow& window);
	void							removeEntity(std::shared_ptr<Entity> entitySharedPtr);

	void                            deleteAllEnnemy();

private:

	SharedPtrEntityVector_t			m_entities;

	SharedPtrEntityVector_t			m_ennemies;
	SharedPtrEntityVector_t		    m_npc;

};
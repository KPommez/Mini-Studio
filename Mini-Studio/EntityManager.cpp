#include "EntityManager.hpp"

std::weak_ptr<Entity> EntityManager::addEntity(std::shared_ptr<Entity> entitySharedPtr)
{
	m_entities.push_back(entitySharedPtr);
	return entitySharedPtr;
}



std::weak_ptr<Entity> EntityManager::addEnnemy(std::shared_ptr<Entity> entitySharedPtr) {
	m_ennemies.push_back(entitySharedPtr);
	return entitySharedPtr;
}


std::weak_ptr<Entity> EntityManager::addNPC(std::shared_ptr<Entity> entitySharedPtr) {
	m_npc.push_back(entitySharedPtr);
	return entitySharedPtr;
}
//void EntityManager::removeEntity(std::shared_ptr<Entity> entitySharedPtr)
//{
//	auto iterator = std::find(m_entities.begin(), m_entities.end(), entitySharedPtr);
//	if (iterator != m_entities.end())
//	{
//		iterator->reset();
//	}
//}

shared_ptr<Entity> EntityManager::checkEntity(const sf::Vector2f& playerPosition, float detectionRange) {
	for (const auto& ent : m_entities) {
		if (ent->shape.getGlobalBounds().intersects(sf::FloatRect(
			playerPosition.x - detectionRange / 2,
			playerPosition.y - detectionRange / 2,
			detectionRange,
			detectionRange))) {
			cout << "Interact Entité : " << ent->type << endl;
			return ent;
		}
	}

	for (const auto& ent2 : m_npc) {
		if (ent2->shape.getGlobalBounds().intersects(sf::FloatRect(
			playerPosition.x - detectionRange / 2,
			playerPosition.y - detectionRange / 2,
			detectionRange,
			detectionRange))) {
			cout << "Interact NPC" << endl;
			return ent2;
		}
	}

	return nullptr;
}

shared_ptr<Entity> EntityManager::getObject(string type) {
	for (auto& object : m_entities) {
		if (object->type == type) {
			return object;
		}
	}
}

void EntityManager::removeEntity(std::shared_ptr<Entity> entitySharedPtr)
{
	if (entitySharedPtr)
	{
		auto enemyIterator = std::find(m_ennemies.begin(), m_ennemies.end(), entitySharedPtr);
		if (enemyIterator != m_ennemies.end())
		{
			m_ennemies.erase(enemyIterator);
		}

		auto entityIterator = std::find(m_entities.begin(), m_entities.end(), entitySharedPtr);
		if (entityIterator != m_entities.end())
		{
			m_entities.erase(entityIterator);
		}
	}
}



void EntityManager::deleteAllEnnemy()
{
	for (auto& enemy : m_ennemies) {
		enemy.reset();
	}
	m_ennemies.clear();
	for (auto& enemy : m_entities) {
		enemy.reset();
	}
	m_entities.clear();

	

	

	for (auto& enemy : m_npc) {
		enemy.reset();
	}
	m_npc.clear();

}
void EntityManager::drawEntities(RenderWindow& window) {
	for (auto& entity : m_entities)
	{
		entity->draw( window);
	}
	for (auto& enemy : m_ennemies)
	{

		enemy->draw(window);
	}
	for (auto& npc : m_npc)
	{
		npc->draw( window);
	}
}
void EntityManager::drawPlayer(RenderWindow& window) {

}
void EntityManager::updateEntities(sf::RenderWindow& window, float deltaTime)
{
	for (auto& entity : m_entities)
	{
		entity->update(deltaTime, window);
	}
	for (auto& enemy : m_ennemies)
	{

		enemy->update(deltaTime, window);
	}
	for (auto& npc : m_npc)
	{
		npc->update(deltaTime, window);
	}
	
	
}


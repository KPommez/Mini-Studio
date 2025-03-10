#include "Menu.hpp"

Button::Button(sf::Vector2f position_, ButtonID id_, sf::Color color_, sf::RectangleShape hitbox_, sf::Vector2f textureCoords_)
{
	this->position = position_;
	this->id = id_;
	this->color = color_;
	this->hitbox = hitbox_;
	this->hitbox.setOrigin({ this->hitbox.getSize().x / 2.f, this->hitbox.getSize().y / 2.f });
	this->hitbox.setPosition(this->position);
	this->hitbox.setFillColor(this->color);
	this->sprite = nullptr;
	this->textureCoords = textureCoords_;

}

Button::Button(sf::Vector2f position_, ButtonID id_, sf::Color color_, sf::RectangleShape hitbox_)
{
	this->position = position_;
	this->id = id_;
	this->color = color_;
	this->hitbox = hitbox_;
	this->hitbox.setOrigin({ this->hitbox.getSize().x / 2.f, this->hitbox.getSize().y / 2.f });
	this->hitbox.setPosition(this->position);
	this->hitbox.setFillColor(this->color);
	this->sprite = nullptr;
	this->textureCoords = { 0, 0 };

}

Button::~Button() {};

MenuManager::MenuManager() {
	smallButtons = { NOTHING, PLAY, QUIT };
	background = new Sprite;

	if (!loadTexture()) { cout << "Buttons texture failed" << endl; }
	openMenu();
}

void MenuManager::addBackground(sf::Texture& texture)
{
	background = new sf::Sprite;
	background->setTexture(texture);

	sf::FloatRect bounds = background->getLocalBounds();
	sf::Vector2u textureSize = background->getTexture()->getSize();
	background->setScale(
		float(1920) / textureSize.x,
		float(1080) / textureSize.y
	);

	background->setOrigin(bounds.width / 2.f, bounds.height / 2.f);
	background->setPosition(1920 / 2.f, 1080 / 2.f);
}

void MenuManager::openGame()
{
}

void MenuManager::openMenu()
{
	this->buttons.clear();

	addBackground(menuTexture);

	this->buttons.push_back(new Button(sf::Vector2f{ 1920 / 2,410 }, PLAY, sf::Color::Blue, sf::RectangleShape(sf::Vector2f(250, 75)), { 0, 2 }));
	this->buttons.push_back(new Button(sf::Vector2f{ 1920 / 2,515 }, SETTINGS, sf::Color::Magenta, sf::RectangleShape(sf::Vector2f(250, 75)), { 0, 0 }));
	this->buttons.push_back(new Button(sf::Vector2f{ 1920 / 2,620 }, QUIT, sf::Color::Yellow, sf::RectangleShape(sf::Vector2f(250, 75)), { 0, 1 }));

	setSprites();
}

void MenuManager::openOption()
{
	this->buttons.clear();
	addBackground(optionsTexture);
	setSprites();
}

void MenuManager::openVictory() {
}

void MenuManager::openLose(){
}


void MenuManager::drawButtons(sf::RenderWindow& window)
{
	if (background)
	{
		window.draw(*background);
	}

	for (Button* button : this->buttons)
	{
		if (button->getSprite() == nullptr) { window.draw(button->getHitbox()); continue; }
		button->getSprite()->setPosition(button->getposition());
		window.draw(*button->getSprite());
	}
}

void MenuManager::activateButtons(ButtonID id)
{
	switch (id)
	{
	case NOTHING: break;
	case PLAY: openGame(); break;
	case SETTINGS: openOption(); break;
	case QUIT: break;
	case BACK: openMenu(); break;
	}
}

ButtonID MenuManager::isMouseOnButton(sf::Vector2i mousePosition)
{
	for (Button* button : this->buttons)
	{
		if (button->getHitbox().getGlobalBounds().contains(mousePosition.x, mousePosition.y))
		{
			//std::cout << "Button clicked\n";
			return button->getId();
		}
	}
	return NOTHING;
}

bool MenuManager::loadTexture()
{
	if (!this->smallButtonsTexture.loadFromFile("assets/textures/SmallButtons.png")) return false;
	if (!this->bigButtonsTexture.loadFromFile("assets/textures/Buttons.png")) return false;

	if (!this->menuTexture.loadFromFile("assets/textures/MenuBackground.png")) return false;

	if (!this->victoryTexture.loadFromFile("assets/textures/VictoryBackground.png")) return false;
	if (!this->losingTexture.loadFromFile("assets/textures/LosingBackground.png")) return false;

	if (!this->optionsTexture.loadFromFile("assets/textures/OptionsBackground.png")) return false;
	if (!this->levelsSelectTexture.loadFromFile("assets/textures/SpaceBackground.png")) return false;
	this->setSprites();
	return true;
}

void MenuManager::setSprites()
{
	for (Button* adress : this->buttons)
	{
		if (adress->getSprite() != nullptr) continue;

		Sprite* sprite = nullptr;
		bool isSmall = false;

		for (ButtonID id : this->smallButtons)
		{
			if (adress->getId() == id)
			{
				isSmall = true;
				sprite = new sf::Sprite;
				sprite->setTexture(this->smallButtonsTexture);

				sprite->setScale({ smallButtonsTexture.getSize().x / adress->getHitbox().getSize().x / 1.5f, smallButtonsTexture.getSize().y / adress->getHitbox().getSize().y / 1.5f });
				sprite->setOrigin({
					adress->getHitbox().getOrigin().x / sprite->getScale().x,
					adress->getHitbox().getOrigin().y / sprite->getScale().y
					});

				sprite->setTextureRect(sf::IntRect(
					adress->getTextureCoords().x * 25,
					adress->getTextureCoords().y * 31,
					25,
					31));

				adress->setSprite(sprite);
			}
		}

		if (isSmall) continue;

		sprite = new sf::Sprite;
		sprite->setTexture(this->bigButtonsTexture);

		sprite->setScale({ bigButtonsTexture.getSize().x / .2f / adress->getHitbox().getSize().x, bigButtonsTexture.getSize().y / .42f / adress->getHitbox().getSize().y });
		sprite->setOrigin({
			adress->getHitbox().getOrigin().x / sprite->getScale().x,
			adress->getHitbox().getOrigin().y / sprite->getScale().y
			});

		sprite->setTextureRect(sf::IntRect(
			adress->getTextureCoords().x * 98,
			adress->getTextureCoords().y * 32,
			98,
			32));

		adress->setSprite(sprite);
	}
}

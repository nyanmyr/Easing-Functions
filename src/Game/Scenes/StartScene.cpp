#include <SFML/Graphics.hpp>

#include <optional>
#include <queue>

#include "../src/Game/Headers/GameManager.hpp"
#include "../src/Game/Headers/Scenes.hpp"

void startScene()
{

	// game state variables
	sf::Clock clock;
	std::queue<Entity> renderQueue;

	Component::Singleton::TexturesContainer loadedTextures{};

	Entity title = EntityMaker::text
	(
		Component::Text
		{
			.box = Asset::font(Asset::Font::MAIN),
			.string = "Linear",
			.size = 16,
			.color = sf::Color::White,
			.format = Enum::TextFormat::CENTER,
		},
		Component::ZIndex{ .index = static_cast<int>(Enum::Layer::TEXT) },
		Component::Position
		{
			.x = 0.0,
			.y = -30.0,
		}
	);

	Entity linearSlider = EntityMaker::staticObject
	(
		Component::Color{ .data = sf::Color::White },
		Component::ZIndex{ .index = static_cast<int>(Enum::Layer::MAIN) },
		Component::Texture{ .data = Enum::Texture::TEXTURE_PLACEHOLDER },
		Component::Position
		{
			.x = 0.0,
			.y = 0.0,
		},
		Component::Transform
		{
			.width = 160.0,
			.height = 1.0,
		},
		Component::OriginPoint{ .data = Enum::OriginPoint::CENTER }
		);

	Entity linearBox = EntityMaker::movingObject
	(
		Component::Color{ .data = sf::Color::Green },
		Component::ZIndex{ .index = static_cast<int>(Enum::Layer::MAIN) },
		Component::Texture{ .data = Enum::Texture::TEXTURE_PLACEHOLDER },
		Component::Position
		{
			.x = 0.0,
			.y = 0.0,
		},
		Component::Velocity
		{
			.minX = -300.0,
			.minY = -300.0,
			.maxX = 300.0,
			.maxY = 300.0,
		},
		Component::Transform
		{
			.width = 40.0,
			.height = 40.0,
		},
		Component::OriginPoint{ .data = Enum::OriginPoint::CENTER },
		Component::Acceleration
		{
			.x = 500.0,
			.y = 500.0,
		}
	);

	// onstart systems
	Start::setText();
	Start::setTextOrigin();

	Start::loadTextures(loadedTextures);
	Start::loadSprites(loadedTextures);
	Start::setSpriteOrigin();
	Start::setColor();

	while (Asset::window().isOpen())
	{
		DeltaTime dt = clock.restart().asSeconds();

		const auto& pixelPos = sf::Mouse::getPosition(Asset::window());
		const auto& worldPos = Asset::window().mapPixelToCoords(pixelPos);

		while (const std::optional event = Asset::window().pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				Asset::window().close();
			}
		}

		// update systems
		Update::move(dt);

		Asset::window().clear();
		// render systems
		Render::doZIndex(renderQueue);
		Render::render
		(
			Asset::window(),
			renderQueue
		);
		Asset::window().display();
	}
}
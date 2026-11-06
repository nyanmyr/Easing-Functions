#ifndef ENTITY_MAKER_HPP
#define ENTITY_MAKER_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include "../../Engine/Core.hpp"
#include "Scenes.hpp"
#include "Enums.hpp"
#include "Components.hpp"

namespace EntityMaker
{
	Entity movingObject
	(
		const Component::Color& color,
		const Component::ZIndex& zIndex,
		const Component::Texture& texture,
		const Component::Position& position,
		const Component::Velocity& velocity,
		const Component::Transform& transform,
		const Component::OriginPoint& originPoint,
		const Component::Progression& progression,
		const Component::Acceleration& acceleration,
		const Component::SliderMovement& sliderMovement
	);

	Entity staticObject
	(
		const Component::Color& color,
		const Component::ZIndex& zIndex,
		const Component::Texture& texture,
		const Component::Position& position,
		const Component::Transform& transform,
		const Component::OriginPoint& originPoint
	);

	Entity text
	(
		const Component::Text& text,
		const Component::ZIndex& zIndex,
		const Component::Position& position
	);
}

#endif
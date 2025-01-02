#pragma once

#include "pch.h"
#include "../ComponentManager.h"
#include "../data/DeltaTime.h"
#include <SFML/Graphics.hpp>
#include <map>
#include <utility>

namespace Light {

    // Configuration for the size of each sprite (width, height)
    struct SpriteSizeConfig {
        unsigned int spriteWidth;
        unsigned int spriteHeight;

        SpriteSizeConfig(unsigned int width, unsigned int height)
            : spriteWidth(width), spriteHeight(height) {
        }
    };

    // Configuration for the sprite atlas (rows, columns, and the texture)
    struct SpriteAtlasConfig {
        unsigned int numRows;
        unsigned int numCols;
        const sf::Texture& atlasTexture;

        SpriteAtlasConfig(const sf::Texture& texture, unsigned int rows=1, unsigned int cols=1)
            : numRows(rows), numCols(cols), atlasTexture(texture) {
        }
    };


    class SpriteComponent {
    public:
        // Constructor now accepts separate configuration objects
        SpriteComponent(const SpriteSizeConfig& sizeConfig, const SpriteAtlasConfig& atlasConfig, const DeltaTime& animConfig)
            : spriteWidth(sizeConfig.spriteWidth), spriteHeight(sizeConfig.spriteHeight),
            numRows(atlasConfig.numRows), numCols(atlasConfig.numCols),
            animationSpeed(animConfig), atlasTexture(atlasConfig.atlasTexture)
        {
        }

        virtual ~SpriteComponent() = default;

        virtual sf::Sprite getSprite(unsigned int row, unsigned int col) const = 0;

    protected:
        unsigned int spriteWidth, spriteHeight;
        unsigned int numRows, numCols;
        DeltaTime animationSpeed;
        const sf::Texture& atlasTexture;
    };

}

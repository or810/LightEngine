#pragma once

#include "pch.h"
#include "../SpriteComponent.h"
#include <SFML/Graphics.hpp>
#include <map>

namespace Light {

    class SFMLSpriteComponent : public SpriteComponent {
    public:
        // Constructor accepts the separate configuration components
        SFMLSpriteComponent(const SpriteAtlasConfig& atlasConfig, const SpriteSizeConfig& sizeConfig, const DeltaTime& animConfig)
            : SpriteComponent(sizeConfig, atlasConfig, animConfig)
        {
            preloadSprites();
        }

        SFMLSpriteComponent(const sf::Texture& texture, const SpriteSizeConfig& sizeConfig)
        : SFMLSpriteComponent(SpriteAtlasConfig(texture), sizeConfig, DeltaTime::zeroDeltaTime)
        {

        }

        // Override the getSprite method to return a preloaded sprite
        sf::Sprite getSprite(unsigned int row, unsigned int col) const override {
            auto key = std::make_pair(row, col);
            if (m_sprites.find(key) != m_sprites.end()) {
                return m_sprites.at(key); // Return preloaded sprite
            }
            else {
                // Handle error: sprite not found (shouldn't happen)
                return sf::Sprite();  // Return a default sprite
            }
        }

    private:
        // Preload all sub-sprites from the texture atlas
        void preloadSprites() {
            for (unsigned int row = 0; row < numRows; ++row) {
                for (unsigned int col = 0; col < numCols; ++col) {
                    sf::IntRect subRect(col * spriteWidth, row * spriteHeight, spriteWidth, spriteHeight);
                    sf::Sprite subSprite(atlasTexture, subRect);
                    m_sprites[{row, col}] = subSprite;  // Store the sprite in the map
                }
            }
        }

        std::map<std::pair<unsigned int, unsigned int>, sf::Sprite> m_sprites; // Map of preloaded sprites
    };

}
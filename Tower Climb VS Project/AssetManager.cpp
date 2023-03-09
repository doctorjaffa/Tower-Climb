#include "AssetManager.h"

std::map<std::string, sf::Texture> AssetManager::textures;
std::map<std::string, sf::SoundBuffer> AssetManager::soundBuffers;
std::map<std::string, sf::Font> AssetManager::fonts;

sf::Texture& AssetManager::RequestTexture(std::string textureName)
{
    // TODO: insert return statement here
    auto pairFound = textures.find(textureName);

    if (pairFound != textures.end())
    {
        //Found an existing texture - use it.
        return pairFound->second; //The value in the key-value pair.
    }
    else
    {
        sf::Texture& newTexture = textures[textureName];
        newTexture.loadFromFile(textureName);
        return newTexture;
    }
}

sf::SoundBuffer& AssetManager::RequestSoundBuffer(std::string soundBufferName)
{
    // TODO: insert return statement here
    auto pairFound = soundBuffers.find(soundBufferName);

    if (pairFound != soundBuffers.end())
    {
        //Found an existing sound buffer - use it.
        return pairFound->second; 
    }
    else
    {
        sf::SoundBuffer& newSoundBuffer = soundBuffers[soundBufferName];
        newSoundBuffer.loadFromFile(soundBufferName);
        return newSoundBuffer;
    }
}

sf::Font& AssetManager::RequestFont(std::string fontName)
{
    // TODO: insert return statement here
    auto pairFound = fonts.find(fontName);

    if (pairFound != fonts.end())
    {
        //Found an existing font - use it.
        return pairFound->second;
    }
    else
    {
        sf::Font& newFont = fonts[fontName];
        newFont.loadFromFile(fontName);
        return newFont;
    }
}

void AssetManager::DestroyAllAssets()
{
    textures.clear();
    soundBuffers.clear();
    fonts.clear();
}

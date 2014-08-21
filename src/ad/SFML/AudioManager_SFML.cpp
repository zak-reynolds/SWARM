#include "ad/SFML/AudioManager_SFML.h"
#include <iostream>

namespace ad {
namespace Sound {

AudioManager_SFML::AudioManager_SFML() { }
AudioManager_SFML::~AudioManager_SFML() { }

int AudioManager_SFML::Initialize() { return AD_NORMALCODE; }
void AudioManager_SFML::Update()
{
    // Clean up finished Sounds
    std::vector<std::vector<sf::Sound*>::iterator> cleanUpIterators;
    for (auto it = playingSounds.begin(); it != playingSounds.end(); ++it)
    {
        if ((*it)->getStatus() == sf::Sound::Status::Stopped)
        {
            delete *it;
            cleanUpIterators.push_back(it);
        }
    }
    while (!cleanUpIterators.empty())
    {
        playingSounds.erase(cleanUpIterators.back());
        cleanUpIterators.pop_back();
    }
}
void AudioManager_SFML::Destroy()
{
    // Clean up Sounds
    std::vector<std::vector<sf::Sound*>::iterator> cleanUpIterators;
    for (auto it = playingSounds.begin(); it != playingSounds.end(); ++it)
    {
        // it references a pointer to a Sound object, so delete *it
        delete *it;
        cleanUpIterators.push_back(it);
    }
    while (!cleanUpIterators.empty())
    {
        playingSounds.erase(cleanUpIterators.back());
        cleanUpIterators.pop_back();
    }
    // Clean up Music
    for (auto it = openedMusic.begin(); it != openedMusic.end(); ++it)
    {
        delete it->second;
    }
    loadedSoundBuffers.clear();
}

int AudioManager_SFML::PlaySound(std::string File)
{
    return PlaySound(File, 100, 1, false);
}
int AudioManager_SFML::PlaySound(std::string File, float Volume, float Pitch, bool Loop)
{
    if (LoadSound(File) != ERROR_FILENOTFOUND)
    {
        sf::Sound* sound = new sf::Sound();
        sound->setBuffer(loadedSoundBuffers[File]);
        sound->setVolume(Volume);
        sound->setPitch(Pitch);
        sound->setLoop(Loop);
        sound->play();
        playingSounds.push_back(sound);
        return AD_NORMALCODE;
    }
    return ERROR_FILENOTFOUND;
}
int AudioManager_SFML::LoadSound(std::string File)
{
    if (loadedSoundBuffers.find(File) == loadedSoundBuffers.end())
    {
        sf::SoundBuffer sb;
        if(!(sb.loadFromFile("Resources/Audio/" + File)))
        {
            std::cout << "Unable to load SoundBuffer '" << File << "'; file not found\n";
            return ERROR_FILENOTFOUND;
        }
        loadedSoundBuffers.insert(std::pair<std::string, sf::SoundBuffer>(File, sb));
    }
    else return ERROR_FILEALREADYLOADED;
    return AD_NORMALCODE;
}
int AudioManager_SFML::UnloadSound(std::string File)
{
    if (loadedSoundBuffers.find(File) == loadedSoundBuffers.end())
    {
        std::cout << "Unable to unload sound buffer; SoundBuffer '" << File << "' not loaded\n";
        return ERROR_UNLOAD_FILENOTLOADED;
    }
    loadedSoundBuffers.erase(File);
    return AD_NORMALCODE;
}

int AudioManager_SFML::PlayMusic(std::string File)
{
    // If music is not opened, open it
    if (openedMusic.find(File) == openedMusic.end())
    {
        sf::Music* music = new sf::Music();
        if (!music->openFromFile("Resources/Audio/" + File))
        {
            std::cout << "Unable to open music file '" << File << "'; file not found\n";
            return ERROR_FILENOTFOUND;
        }
        openedMusic.insert(std::pair<std::string, sf::Music*>(File, music));
    }
    openedMusic[File]->play();
    return AD_NORMALCODE;
}
int AudioManager_SFML::PauseMusic(std::string File)
{
    if (openedMusic.find(File) != openedMusic.end())
    {
        openedMusic[File]->pause();
    }
    return AD_NORMALCODE;
}
int AudioManager_SFML::StopMusic(std::string File)
{
    if (openedMusic.find(File) != openedMusic.end())
    {
        openedMusic[File]->stop();
        delete openedMusic[File];
        openedMusic.erase(File);
    }
    return AD_NORMALCODE;
}

int AudioManager_SFML::SetMusicPosition(std::string File, float PositionSecs)
{
    if (openedMusic.find(File) != openedMusic.end())
    {
        openedMusic[File]->setPlayingOffset(sf::seconds(PositionSecs));
    }
    return AD_NORMALCODE;
}
int AudioManager_SFML::SetMusicVolume(std::string File, float Volume)
{
    if (openedMusic.find(File) != openedMusic.end())
    {
        openedMusic[File]->setVolume(Volume);
    }
    return AD_NORMALCODE;
}
int AudioManager_SFML::SetMusicPitch(std::string File, float Pitch)
{
    if (openedMusic.find(File) != openedMusic.end())
    {
        openedMusic[File]->setPitch(Pitch);
    }
    return AD_NORMALCODE;
}
int AudioManager_SFML::SetMusicLoop(std::string File, bool Loop)
{
    if (openedMusic.find(File) != openedMusic.end())
    {
        openedMusic[File]->setLoop(Loop);
    }
    return AD_NORMALCODE;
}
float AudioManager_SFML::GetMusicPosition(std::string File)
{
    if (openedMusic.find(File) != openedMusic.end())
    {
        return openedMusic[File]->getPlayingOffset().asSeconds();
    }
    else return 0;
}

#ifdef AD_DEBUG
int AudioManager_SFML::GetNumSounds()
{
    return playingSounds.size();
}
int AudioManager_SFML::GetNumSoundBuffers()
{
    return loadedSoundBuffers.size();
}
#endif

} // namespace Sound
} // namespace ad

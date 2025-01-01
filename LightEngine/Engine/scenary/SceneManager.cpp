#include "pch.h"
#include "SceneManager.h"

void Light::SceneManager::remove(int index)
{
    m_scenes.erase(m_scenes.begin() + index);
}

void Light::SceneManager::remove(Scene* scene) {

    m_scenes.erase(std::remove(m_scenes.begin(), m_scenes.end(), scene), m_scenes.end());

}

void Light::SceneManager::push(Scene* scene)
{
    m_scenes.push_back(scene);
}

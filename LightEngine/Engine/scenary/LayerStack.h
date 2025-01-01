#pragma once
#include <vector>
#include "Layer.h"

class LayerStack
{
public:
	void update();
	void render();

private:
	std::vector<Layer> m_layers;
};


#pragma once

#include "Transform.hh"
#include "Renderer.hh"
#include "ID.hh"
#include <SDL/SDL.h>

#pragma once

// Sprite class that serves as part of the Model

struct Sprite {
	Transform transform;
	ObjectID objectID;
	void Draw() { R.Push(objectID, transform); };
};

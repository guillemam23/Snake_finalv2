
#include <iostream>

#pragma once

// Enum ID used to identify each Game Object in the Game

enum class ObjectID : int {

	CELL_EMPTY, // Cell IDs
	BACKGROUND, // Background IDs
	BUTTON_PLAY, BUTTON_EXIT, BUTTON1, BUTTON2, BUTTON3, //Buttons
	APPLE, SNAKE_HEAD, SNAKE_BODY,
	WALL, // Wall
	TEMP
};
inline std::ostream &operator<<(std::ostream &os, const ObjectID &id) { return os << int(id); };
inline std::istream &operator>>(std::istream &is, ObjectID &id) { return is >> reinterpret_cast<int&>(id); };

// Enum ID used to store each true type font for text rendering

enum class FontID : int {

	ARIAL,
	CANDY,
	FACTORY,
	MAX
};
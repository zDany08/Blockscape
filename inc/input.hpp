#ifndef INPUT_HPP
#define INPUT_HPP

#include <utils.hpp>
#include <player.hpp>

void onKeyPress(GLFWwindow*, int);

void onKeyRelease(GLFWwindow*, int);

void onCursorMove(GLFWwindow*, Camera*, int, int);

void onInput(GLFWwindow*, Camera*);

extern bool cursorEnabled;

void enableCursor(GLFWwindow*);

void disableCursor(GLFWwindow*);

void toggleCursor(GLFWwindow*);

#endif

#ifndef SDLGLRENDERER_H
#define SDLGLRENDERER_H

#include <SDL.h>
#include <SDL_opengles2.h>
#include <SDL_image.h>
#include <string>
#include "../math/vectors3D.h"

bool initOpenGL(GLuint shaderProgram, GLuint vbo);
void drawTriangleWithOpenGL(Vector3d v1, Vector3d v2, Vector3d v3, GLuint shaderProgram, GLuint vbo);
#endif /* SDLGLRENDERER_H */
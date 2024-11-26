#pragma once
#include <iostream>
#define LOG_FILE_LINE() \
    std::cout << "Файл: " << __FILE__ << ", строка: " << __LINE__ << std::endl;

#include "src/PRISM_math/vector3D.h"
#include "src/PRISM_math/matrix.h"
#include "src/PRISM_math/other.h"
#include "src/PRISM_math/math.h"

#include "src/PRISM_UI/button.h"
#include "src/PRISM_UI/joystick.h"

#include "src/PRISM_objects3D/AbstractCamera3D.h"
#include "src/PRISM_objects3D/AbstractObject3D.h"

#include "src/PRISM_rendering/zbuffer.h"
#include "src/PRISM_rendering/render.h"
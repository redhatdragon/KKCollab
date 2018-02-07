#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "../EnvInfo.h"

#include "IOFile.h"

#ifdef _WIN32
#include "WindowsKeyboardMouse.h"
//#include "WindowsGetPixel.h"
#elif defined(LINUX)
#elif defined(APPLE)
#endif

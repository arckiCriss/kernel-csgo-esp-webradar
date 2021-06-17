#pragma once
#include "CsgoProcess.h"
#include "overlay.h"
#include <cassert>
#include "json.hpp"
#include "vector.h"
#include "math.h"
#include "entity.h"
#include <fstream>
#include <sstream>
#include "definitions.h"
#include <iostream>
#include "easywsclient/easywsclient.hpp"

namespace ESP {

	void Run(FOverlay* overlay);
	void DrawPlayerBox(FOverlay* overlay, Vector position, Vector head, float height);
	void DrawHealthBar(FOverlay* overlay, Vector position, Vector head, float height, int health);
	void DrawPlayerDetails(FOverlay* overlay, Vector position, Vector head, float height, Entity entity);
	void DrawGrenadeHelper(FOverlay* overlay, Entity localplayer);
}

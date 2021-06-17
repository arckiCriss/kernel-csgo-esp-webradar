

#include "esp.h"



using json = nlohmann::json;

static std::map<std::string, Vector> W2SCache = {};

float screen_x, screen_y;

// lazy 
static std::map<int, int> grenadeIndexMap = {
	{45, 1},
	{ 43, 0 },
	{44, 2},
	{48, 3},
	{46, 3}
};

static std::map<int, std::string> throwStyle
{
	{0, "THROW"},
	{1, "RUN THROW"},
	{2, "JUMP THROW"},
	{3, "RUN & JUMP THROW"},
	{4, "Jump+Half throw"},
	{5, "RUN RIGHT"},
	{6, "RUN LEFT"}
};


std::string GetExeFileName()
{
	char buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	return std::string(buffer);
}

std::string GetExePath()
{
	std::string f = GetExeFileName();
	return f.substr(0, f.find_last_of("\\/"));
}

Vector GetBonPos(int base, int bone) {
	CsgoProcess* csgo_process = csgo_process->getInstance();
	int boneMatrix = csgo_process->RPM<int>(base + hazedumper::netvars::m_dwBoneMatrix + 616);

	Vector vBone;
	vBone.x = csgo_process->RPM<float>(boneMatrix + 0x30 * bone + 0xC);
	vBone.y = csgo_process->RPM<float>(boneMatrix + 0x30 * bone + 0x1C);
	vBone.z = csgo_process->RPM<float>(boneMatrix + 0x30 * bone + 0x2C);

	return vBone;
}

bool WorldToScreen(Vector vIn, Vector& vOut)
{
	CsgoProcess* csgo = csgo->getInstance();
	float vMatrix[16];
	for (int i = 0; i < 16; i++)
	{
		vMatrix[i] = csgo->RPM<float>(csgo->client_base + hazedumper::signatures::dwViewMatrix + sizeof(float) * i);
	}

	vOut.x = vMatrix[0] * vIn.x + vMatrix[1] * vIn.y + vMatrix[2] * vIn.z + vMatrix[3];
	vOut.y = vMatrix[4] * vIn.x + vMatrix[5] * vIn.y + vMatrix[6] * vIn.z + vMatrix[7];

	float w = vMatrix[12] * vIn.x + vMatrix[13] * vIn.y + vMatrix[14] * vIn.z + vMatrix[15];

	if (w < 0.01)
		return false;

	float invw = 1.0f / w;

	vOut.x *= invw;
	vOut.y *= invw;

	int width, height;

	width = screen_x;
	height = screen_y;

	float x = (float)width / 2;
	float y = (float)height / 2;

	x += 0.5 * vOut.x * (float)width + 0.5;
	y -= 0.5 * vOut.y * (float)height + 0.5;

	vOut.x = x;
	vOut.y = y;

	return true;
}

json weapon_map;

json j;


clock_t current_ticks, delta_ticks;
clock_t fps = 0;



void ESP::Run(FOverlay* overlay)
{

	CsgoProcess* csgo_process = csgo_process->getInstance();

	screen_x = GetSystemMetrics(SM_CXSCREEN);
	screen_y = GetSystemMetrics(SM_CYSCREEN);

	using easywsclient::WebSocket;
	WebSocket::pointer ws = NULL;
	INT rc;
	WSADATA wsaData;

	rc = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (rc) {
		printf("WSAStartup Failed.\n");
		return;
	}
	std::string local_url = "ws://localhost:6969";


	ws = WebSocket::from_url(local_url);
	assert(ws);

	puts("Connected.\n");

	int client_state = csgo_process->RPM<int>(csgo_process->engine_base + hazedumper::signatures::dwClientState);
	int n = 0;
	char c = 'o';
	char map_name[32];
	while (c != '\0') {
		c = csgo_process->RPM<char>(client_state + hazedumper::signatures::dwClientState_Map + n);
		map_name[n] = c;
		n++;
	}
	std::string map = std::string(map_name);
	std::string final_path = GetExePath() + "\\grenadeinfo\\" + map + ".json";
	std::cout << final_path << std::endl;
	std::ifstream fileToOpen(final_path);
	j = json::parse(fileToOpen);
	

	{
		weapon_map[1] = "DEAGLE";
		weapon_map[2] = "ELITE";
		weapon_map[3] = "FIVESEVEN";
		weapon_map[4] = "GLOCK";
		weapon_map[7] = "AK47";
		weapon_map[8] = "AUG";
		weapon_map[9] = "AWP";
		weapon_map[10] = "FAMAS";
		weapon_map[11] = "G3SG1";
		weapon_map[13] = "GALILAR";
		weapon_map[14] = "M249";
		weapon_map[16] = "M4A1";
		weapon_map[17] = "MAC10";
		weapon_map[19] = "P90";
		weapon_map[24] = "UMP45";
		weapon_map[25] = "XM1014";
		weapon_map[26] = "BIZON";
		weapon_map[27] = "MAG7";
		weapon_map[28] = "NEGEV";
		weapon_map[29] = "SAWEDOFF";
		weapon_map[30] = "TEC9";
		weapon_map[31] = "TASER";
		weapon_map[32] = "P2000";
		weapon_map[33] = "MP7";
		weapon_map[34] = "MP9";
		weapon_map[35] = "NOVA";
		weapon_map[36] = "P250";
		weapon_map[38] = "SCAR20";
		weapon_map[39] = "SG556";
		weapon_map[40] = "SSG08";
		weapon_map[42] = "KNIFE";
		weapon_map[43] = "FLASH";
		weapon_map[44] = "GRENADE";
		weapon_map[45] = "SMOKE";
		weapon_map[46] = "MOLOTOV";
		weapon_map[47] = "DECOY";
		weapon_map[48] = "INCGRENADE";
		weapon_map[49] = "C4";
		weapon_map[59] = "KNIFE";
		weapon_map[60] = "M4A1_S";
		weapon_map[61] = "USP";
		weapon_map[63] = "CZ75A";
		weapon_map[64] = "REVOLVER";
		weapon_map[500] = "KNIFE_BAYONET";
		weapon_map[503] = "KNIFE_CSS";
		weapon_map[505] = "KNIFE_FLIP";
		weapon_map[506] = "KNIFE_GUT";
		weapon_map[507] = "KNIFE_KARAMBIT";
		weapon_map[508] = "KNIFE_M9_BAYONET";
		weapon_map[509] = "KNIFE_TACTICAL";
		weapon_map[512] = "KNIFE_FALCHION";
		weapon_map[514] = "KNIFE_SURVIVAL_BOWIE";
		weapon_map[515] = "KNIFE_BUTTERFLY";
		weapon_map[516] = "KNIFE_PUSH";
		weapon_map[517] = "KNIFE_CORD";
		weapon_map[518] = "KNIFE_CANIS";
		weapon_map[519] = "KNIFE_URSUS";
		weapon_map[520] = "KNIFE_GYPSY_JACKKNIFE";
		weapon_map[521] = "KNIFE_OUTDOOR";
		weapon_map[522] = "KNIFE_STILETTO";
		weapon_map[523] = "KNIFE_WIDOWMAKER";
		weapon_map[525] = "KNIFE_SKELETON";
		weapon_map[526] = "AItemDefinitionIndex";
	}


	

	while (true) {
		overlay->begin_scene();

		overlay->clear_scene();


		json data;
		data["map_name"] = map;
		data["local_player"] = json();
		data["enemy_list"] = json::array();
		data["team_list"] = json::array();
		data["x_positions"] = json::array();
		data["y_positions"] = json::array();
		data["healths"] = json::array();
		data["last_places"] = json::array();
		data["local_x"] = 0;
		data["local_y"] = 0;
		data["local_ang_y"] = 0;





		ULONG l_player = csgo_process->RPM<ULONG>(csgo_process->client_base + hazedumper::signatures::dwLocalPlayer);

		if (l_player <= 0)
			continue;

		int my_team = csgo_process->RPM<int>(l_player + hazedumper::netvars::m_iTeamNum);
		json local_player;

		local_player["pos_x"] = csgo_process->RPM<float>(l_player + hazedumper::netvars::m_vecOrigin);
		local_player["pos_y"] = csgo_process->RPM<float>(l_player + hazedumper::netvars::m_vecOrigin + 0x04);
		local_player["angle_y"] = csgo_process->RPM<float>(l_player + 0xB384);

		data["local_player"] = local_player;

		for (int i = 0; i < 32; i++)
		{

			ULONG entity_base = csgo_process->RPM<ULONG>(csgo_process->client_base + hazedumper::signatures::dwEntityList + i * 0x10);
			if (entity_base == 0)
				continue;

			bool dormant = csgo_process->RPM<int>(entity_base + hazedumper::signatures::m_bDormant);

			if (dormant)
				continue;

			Entity entity = Entity(entity_base, i);


			if (!entity.isAlive())
				continue;

			if (entity.team != my_team) {

				Vector screenPosn;

				if (!WorldToScreen(entity.Position, screenPosn))
					continue;


				if (screenPosn.x <= 0 || screenPosn.y <= 0)
					continue;

				Vector vBone = Vector(0, 0, 0);
				Vector vBoneOut;


				vBone = GetBonPos(entity.base_address, 8);


				if (!WorldToScreen(vBone, vBoneOut))
					continue;

				float height = screenPosn.y - vBoneOut.y;
				DrawPlayerBox(overlay, screenPosn, vBoneOut, height);
				DrawPlayerDetails(overlay, screenPosn, vBoneOut, height, entity);
				DrawHealthBar(overlay, screenPosn, vBoneOut, height, entity.health);

				float rot_y_ang = csgo_process->RPM<float>(entity.base_address + 0xB384);

				json jentity;
				jentity["health"] = entity.health;
				jentity["name"] = entity.name;
				jentity["pos_x"] = entity.Position.x;
				jentity["pos_y"] = entity.Position.y;
				jentity["angle_y"] = rot_y_ang;
				jentity["is_defusing"] = entity.base_address;

				jentity["weapon"] = weapon_map.at(entity.weaponid).get<std::string>().c_str();
				jentity["last_place"] = entity.lastplace;
				jentity["worldscreen_x"] = screenPosn.x;
				jentity["worldscreen_y"] = screenPosn.y;
				data["enemy_list"].push_back(jentity);
			}

		}
		Entity lp = Entity(l_player, 0);
		DrawGrenadeHelper(overlay, lp);
		overlay->end_scene();
		ws->send(data.dump());
		ws->poll();
		data.clear();
		Sleep(1);

	}
	

	

}

void ESP::DrawPlayerBox(FOverlay* overlay, Vector position, Vector head, float height)
{
		overlay->draw_rectangle(head.x - height / 4,
		head.y - height / 6,
		position.x + height / 4,
		position.y, red_brush);

}

void ESP::DrawHealthBar(FOverlay* overlay, Vector position, Vector head, float height, int health)
{

	float black_box_left = position.x - height / 4;
	float black_box_top = position.y + 10;
	float black_box_right = position.x + height / 4;
	float black_box_bottom = position.y + 15;

	float bar_left = black_box_left + 1;
	float bar_top = black_box_top + 1;
	float bar_right = black_box_left + (height / 2 * health / 100);
	float bar_bottom = black_box_bottom - 1
		;
	overlay->draw_rectangle(black_box_left,
		black_box_top,
		black_box_right,
		black_box_bottom, Black_brush);


	if (health > 90) {
		overlay->draw_filled_rectangle(bar_left, bar_top, bar_right, bar_bottom, Green_brush);

	}
	else if (health > 65) {
		overlay->draw_filled_rectangle(bar_left, bar_top, bar_right, bar_bottom, YellowGreen_brush);

	}
	else if (health > 40) {
		overlay->draw_filled_rectangle(bar_left, bar_top, bar_right, bar_bottom, Yellow_brush);

	}
	else if (health > 20) {
		overlay->draw_filled_rectangle(bar_left, bar_top, bar_right, bar_bottom, Orange_brush);
	}
	else {
		overlay->draw_filled_rectangle(bar_left, bar_top, bar_right, bar_bottom, Red_brush);

	}

}

void ESP::DrawPlayerDetails(FOverlay* overlay, Vector position, Vector head, float height, Entity entity)
{

	if (entity.defusing)
		overlay->draw_text(head.x - height / 4,
			head.y - 70, White_brush, "DEFUSING");

	overlay->draw_text(head.x - height / 4,
		head.y - 50, White_brush,
		entity.name);


	overlay->draw_text(head.x - height / 4,
		head.y - 30, White_brush,
		weapon_map.at(entity.weaponid).get<std::string>().c_str());


}

void ESP::DrawGrenadeHelper(FOverlay* overlay, Entity localplayer)
{

	short weapon = localplayer.weaponid;

	if (grenadeIndexMap.find(weapon) == grenadeIndexMap.end())
		return;

	for (json info : j["infos"]) {

		if (grenadeIndexMap[weapon] != info["Type"])
			continue;

		json jpos = info["Position"];
		Vector Pos = Vector(jpos["X"].get<float>(), jpos["Y"].get<float>(), jpos["Z"].get<float>());
		Vector pos2d;
		float dist = cMath::GetDistance3D(localplayer.Position, Pos);
		if (dist < 400)
		{
			std::string spot = info["Name"].get<std::string>();

			if (WorldToScreen(Pos, pos2d)) {

				overlay->draw_text_with_bg(pos2d.x + 20, pos2d.y - 5, LawnGreen_brush, LessBlack_brush, spot.c_str());
				overlay->draw_filled_circle(pos2d.x, pos2d.y, 6, Black_brush);
				overlay->draw_filled_circle(pos2d.x, pos2d.y, 4, Yellow_brush);
			}


			dist = cMath::GetDistance3D(localplayer.Position, Pos);

			if (dist <= 5)
			{
				overlay->draw_filled_circle(pos2d.x, pos2d.y, 6, Black_brush);
				overlay->draw_filled_circle(pos2d.x, pos2d.y, 4, LawnGreen_brush);

				Vector infoVec;
				json jAngle = info["Angle"];
				Vector Angle = Vector(jAngle["X"].get<float>(), jAngle["Y"].get<float>(), 0);
				cMath::AngleVectors(Angle, &infoVec);

				infoVec = infoVec * 150 / infoVec.Length();
				infoVec = infoVec + Pos + Vector(0, 0, 64.5f);

				Vector posVec;

				if (!WorldToScreen(infoVec, posVec))
					continue;

				float crosshairDist = cMath::GetDistance3D(Vector(screen_x / 2, screen_y / 2, 0), posVec);
				overlay->draw_filled_circle(posVec.x, posVec.y, 4, LessBlack_brush);
				if (crosshairDist > 5) {
					overlay->draw_filled_circle(posVec.x, posVec.y, 3, Red_brush);
				}
				else {
					overlay->draw_filled_circle(posVec.x, posVec.y, 3, LawnGreen_brush);
				}

				overlay->draw_line(screen_x / 2, screen_y / 2, posVec.x, posVec.y);

				std::string style = throwStyle[info["Style"].get<int>()];
				overlay->draw_text_with_bg(posVec.x + 20, posVec.y - 5, LawnGreen_brush, LessBlack_brush, (info["Name"].get<std::string>() + " | " + style).c_str());

			}
		}
	}

}

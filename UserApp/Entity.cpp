#include "Entity.h"

Entity::Entity(ULONG base, int index)
{
	CsgoProcess* csgo_process = csgo_process->getInstance();
	base_address = base;
	team = csgo_process->RPM<ULONG>(base + hazedumper::netvars::m_iTeamNum);
	health = csgo_process->RPM<int>(base + hazedumper::netvars::m_iHealth);

	auto radar_base = csgo_process->RPM<ULONG>(csgo_process->client_base + hazedumper::signatures::dwRadarBase);
	radar_base = csgo_process->RPM<ULONG>(radar_base + 0x78);
	int n = 0;
	char c = 'o';

	while (c != '\0') {
		c = csgo_process->RPM<char>(radar_base + (0x174 * (index + 2)) + 0x18 + n);
		name[n] = c;
		n++;
	}


	Position.x = csgo_process->RPM<float>(base + hazedumper::netvars::m_vecOrigin);
	Position.y = csgo_process->RPM<float>(base + hazedumper::netvars::m_vecOrigin + 0x04);
	Position.z = csgo_process->RPM<float>(base + hazedumper::netvars::m_vecOrigin + 0x08);

	defusing = csgo_process->RPM<int>(base + 0x3930);
	int active_weapon = csgo_process->RPM<int>(base + hazedumper::netvars::m_hActiveWeapon);
	int weapon_base = csgo_process->RPM<int>(csgo_process->client_base + hazedumper::signatures::dwEntityList + ((active_weapon & 0xFFF) - 1) * 0x10);
	weaponid = csgo_process->RPM<short>(weapon_base + hazedumper::netvars::m_iItemDefinitionIndex);

	n = 0;
	c = 'o';
	while (c != '\0') {
		c = csgo_process->RPM<char>(base + hazedumper::netvars::m_szLastPlaceName + n);
		lastplace[n] = c;
		n++;
	}


}

bool Entity::isAlive()
{
	return health > 0 ? true : false;
}

#include <random>
#include "Settings.hpp"

namespace GOTHIC_NAMESPACE {
	auto Hook_oCAIArrow_CanThisCollideWith = Union::CreateHook(
		reinterpret_cast<void*>(zSwitch(0x00619550, 0x0063CA10, 0x00644C10, 0x006A1490)),
		&oCAIArrow::CanThisCollideWith_Hook,
		Union::HookType::Hook_Detours);

	std::mt19937 rng{ std::random_device{}() };
	std::uniform_real_distribution<float> dist(0.0, 1.0);


	float ComputeProbability(oCAIArrow* arrow, zCVob* vob) {
		oCNpc* hero = arrow->owner;
		oCNpc* victim = vob->CastTo<oCNpc>();

		int dexterity = hero->attribute[NPC_ATR_DEXTERITY];
		int protection = victim->protection[oEIndexDamage::oEDamageIndex_Point];

		if (dexterity < minDexterity || protection > maxProjectileProtection)
			return 0.0f;

		return 1 / (1 + expf(-0.012 * (0.5 * (dexterity - 300) - 2 * protection)));
	}

	bool CheckConditions(oCAIArrow* arrow, zCVob* vob) {
		if (arrow->owner != player)
			return false;
		if (arrow->ignoreVobList.IsInList(vob))
			return false;
		if (!vob->CastTo<oCNpc>())
			return false;
		if (ComputeProbability(arrow, vob) <= dist(rng))
			return false;

		return true;
	}

	void ExecPenetratingShot(oCAIArrow* arrow, oCNpc* npc) {
		arrow->AddIgnoreCDVob(npc);

		oCNpc::oSDamageDescriptor desc{};
		desc.pVobAttacker = arrow->owner;
		desc.pNpcAttacker = arrow->owner;
		desc.pVobHit = npc;
		desc.enuModeDamage = oETypeDamage::oEDamageType_Point;
		desc.enuModeWeapon = oETypeWeapon::oETypeWeapon_Range;
		for (int i = 0; i < oEDamageIndex_MAX; ++i) desc.aryDamage[i] = arrow->arrow->damage[i];
		desc.fDamageMultiplier = 1.0f;
		desc.pItemWeapon = arrow->arrow;

		npc->OnDamage(desc);
	}

	int oCAIArrow::CanThisCollideWith_Hook(zCVob* vob) {
		if (CheckConditions(this, vob)) {
			oCNpc* npc = vob->CastTo<oCNpc>();
			ExecPenetratingShot(this, npc);
			return 0;
		}

		return (this->*Hook_oCAIArrow_CanThisCollideWith)(vob);
	}
}

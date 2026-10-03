namespace GOTHIC_NAMESPACE {
	int oCAIArrow::CanThisCollideWith_Hook(zCVob* vob) {
		if (this->owner == player && !this->ignoreVobList.IsInList(vob)) {
			if (oCNpc* npc = vob->CastTo<oCNpc>()) {
				this->AddIgnoreCDVob(npc);

				oCNpc::oSDamageDescriptor desc{};
				desc.pVobAttacker = this->owner;
				desc.pNpcAttacker = this->owner;
				desc.pVobHit = npc;
				desc.enuModeDamage = oETypeDamage::oEDamageType_Point;
				desc.enuModeWeapon = oETypeWeapon::oETypeWeapon_Range;
				for (int i = 0; i < oEDamageIndex_MAX; ++i) desc.aryDamage[i] = this->arrow->damage[i];
				desc.fDamageMultiplier = 1.0f;
				desc.pItemWeapon = this->arrow;

				npc->OnDamage(desc);
				return 0;
			}
		}

		return (this->*Hook_oCAIArrow_CanThisCollideWith)(vob);
	}
}
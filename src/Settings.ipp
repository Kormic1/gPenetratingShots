#include "Settings.hpp"

namespace GOTHIC_NAMESPACE {
	void ReadSettingsFromIni() {
		minDexterity = zoptions->ReadInt(PLUGIN_NAME, "MinDexterity", 10);
		maxProjectileProtection = zoptions->ReadInt(PLUGIN_NAME, "MaxProjectileProtection", 9999);
	}
}

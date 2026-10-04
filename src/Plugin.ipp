// This file is included separately for each engine version

#include "Settings.hpp"

namespace GOTHIC_NAMESPACE
{

	void Game_Init()
	{
		ReadSettingsFromIni();
	}

	void Game_ApplySettings()
	{
		ReadSettingsFromIni();
	}

	void __fastcall oCGame_Init(oCGame* self, void* vtable);
	auto Hook_oCGame_Init = Union::CreateHook(SIGNATURE_OF(&oCGame::Init), &oCGame_Init, Union::HookType::Hook_Detours);
	void __fastcall oCGame_Init(oCGame* self, void* vtable)
	{
		Hook_oCGame_Init(self, vtable);
		Game_Init();
	}

	void __fastcall CGameManager_ApplySomeSettings(CGameManager* self, void* vtable);
	auto Hook_CGameManager_ApplySomeSettings = Union::CreateHook(SIGNATURE_OF(&CGameManager::ApplySomeSettings), &CGameManager_ApplySomeSettings, Union::HookType::Hook_Detours);
	void __fastcall CGameManager_ApplySomeSettings(CGameManager* self, void* vtable)
	{
		Hook_CGameManager_ApplySomeSettings(self, vtable);
		Game_ApplySettings();
	}
}

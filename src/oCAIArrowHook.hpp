#pragma once

namespace GOTHIC_NAMESPACE {
	auto Hook_oCAIArrow_CanThisCollideWith = Union::CreateHook(
		reinterpret_cast<void*>(zSwitch(0x0, 0x0, 0x0, 0x0063CA10)),
		&oCAIArrow::CanThisCollideWith_Hook,
		Union::HookType::Hook_Detours);
}

#include "oCAIArrowHook.ipp"
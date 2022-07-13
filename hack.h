#pragma once
//#ifndef __GAME_H__
#define __GAME_H__
#include "memory.h"
#include <vector>
#include <array>
#include <optional>
#include <functional>
#include <mutex>
#include <map>
#include <string_view>

#ifdef UNICODE
using String = std::basic_string<wchar_t>;
using StringView = std::basic_string_view<wchar_t>;
#else
using String = std::basic_string<char>;
using StringView = std::basic_string_view<char>;
#endif



void MainHack();


bool GetStatus();

namespace Features
{
	enum class Difficulty : std::uint32_t { AMATEUR, EASY = 3, NORMAL = 5, PROFESSIONAL = 6 };
	enum class TypewriterMode : std::uint32_t { LOAD, SAVE };

	struct Coordinates
	{
		float mX;
		float mY;
		float mZ;
	};

	bool Initialize();
	void Terminate();

	void SetMoney(std::uint32_t value);

	std::uint32_t GetMoney();

	void SetPoints(std::uint32_t value);

	std::uint32_t GetPoints();

	void SetPointsKill(std::uint32_t value);

	std::uint32_t GetPointsKill();

	void SetDifficulty(Difficulty value);

	Difficulty GetDifficulty();

	void OpenTypewriter(TypewriterMode mode);

	void OpenMerchant();

	void SkipRadioCutscenes(bool skip);

	bool IsRadioSkipEnabled();

	std::float_t GetTime();

	void SetTime(std::float_t value);

	// =========================================================================================

	// ============================== PLAYER HACK
	std::optional<Coordinates*> GetPlayerCoordinates();

	void SetHealth(std::uint16_t health);

	std::uint16_t GetHealth();

	void SetHealthLimit(std::uint16_t limit);

	std::uint16_t GetHealthLimit();

	bool IsAshleyPresent();

	void ToggleAshley(bool toggle);

	void ToggleInfiniteHealth(bool toggle);

	void ToggleInvincible(bool toggle);

	std::float_t GetSpeedPlayer();

	void SetSpeedPlayer(std::float_t value);

	void ToggleClipping(bool toggle);

	void ToggleStUpDown(bool toggle);

	void ToggleAshleyTeleport(bool toggle);

	// =========================================================================================

	// ============================== WAPON HACK

	void ToggleInfiniteAmmo(bool toggle);

	void ToggleAmmoNoReload(bool toggle);

	void ToggleBow(bool toggle);

	void ToggleInfiniteGrenade(bool toggle);

	void ToggleAutoMaxPRL(bool toggle);

	void ToggleFastTmp(bool toggle);

	bool IsFastTmpEnabled();

	void ToggleRapidFire(bool toggle);

	// =========================================================================================

	// ============================== ENEMIE HACK

	void ToggleFrezeeEnemie(bool toggle);

	void ToggleOneHitKill(bool toggle);
}

//#endif
#include "menu.h"
#include "settings.h"
#include "functions.h"
#include "imguipp.h"
#include "icons.h"
#include "TextEditor.h"

#include "hack.h"

void chON()
{
	ImGui::SameLine();
	ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 255, 0, 255)); // GREEN
	ImGui::Text("ON");
	ImGui::PopStyleColor();
}

void chOFF()
{
	ImGui::SameLine();
	ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(245, 66, 66, 255)); // RED
	ImGui::Text("OFF");
	ImGui::PopStyleColor();
}



extern ImFont* Consolas;
void Menu::Render()
{
	if (GetStatus())
	{
		if (Cheat::SpeedHack == 0.0f)
		{
			Cheat::SpeedHack = 1.0f;
		}
		else
		{
			Features::SetSpeedPlayer(Cheat::SpeedHack);
		}
	}

	ImGui::Columns(2);
	ImGui::SetColumnOffset(1, 230);

	{
		//Left side

		static ImVec4 active = imguipp::to_vec4(41, 40, 41, 255);
		static ImVec4 inactive = imguipp::to_vec4(31, 30, 31, 255);

		ImGui::PushStyleColor(ImGuiCol_Button, Settings::Tab == 1 ? active : inactive);
		if (ImGui::Button(ICON_FA_CODE " Main Menu", ImVec2(230 - 15, 41)))
			Settings::Tab = 1;

		ImGui::Spacing();
		ImGui::PushStyleColor(ImGuiCol_Button, Settings::Tab == 2 ? active : inactive);
		if (ImGui::Button(ICON_FA_USER " Player Menu", ImVec2(230 - 15, 41)))
			Settings::Tab = 2;

		ImGui::Spacing();
		ImGui::PushStyleColor(ImGuiCol_Button, Settings::Tab == 3 ? active : inactive);
		if (ImGui::Button(ICON_FA_CROSSHAIRS " Weapon Menu", ImVec2(230 - 15, 41)))
			Settings::Tab = 3;

		ImGui::Spacing();
		ImGui::PushStyleColor(ImGuiCol_Button, Settings::Tab == 4 ? active : inactive);
		if (ImGui::Button(ICON_FA_EYE " Enemie Menu", ImVec2(230 - 15, 41)))
			Settings::Tab = 4;

		ImGui::Spacing();
		ImGui::PushStyleColor(ImGuiCol_Button, Settings::Tab == 5 ? active : inactive);
		if (ImGui::Button(ICON_FA_GAMEPAD " Etc Menu", ImVec2(230 - 15, 41)))
			Settings::Tab = 5;

		ImGui::Spacing();
		ImGui::PushStyleColor(ImGuiCol_Button, Settings::Tab == 6 ? active : inactive);
		if (ImGui::Button(ICON_FA_BOOK " About", ImVec2(230 - 15, 41)))
			Settings::Tab = 6;

		ImGui::PopStyleColor(6);

		ImGui::SetCursorPosY(ImGui::GetWindowHeight() - 30);
		imguipp::center_text_ex("Rizki Kotet", 230, 1, false);
	}

	ImGui::NextColumn();

	//Right side
	{
		// Executor tab
		if (Settings::Tab == 1)
		{
			ImGui::Text("Set Difficulty Game");
			    const char* CharIDifficulty[] = { "Amature", "Easy", "Normal", "Profesional"};
			    if (ImGui::Combo("##Difficulty", &Cheat::ItmDifficulty, CharIDifficulty, IM_ARRAYSIZE(CharIDifficulty)))
			    {
			        switch (Cheat::ItmDifficulty)
			        {
			        case 0:
			            Features::SetDifficulty(Features::Difficulty::AMATEUR);
			            break;
			        case 1:
			            Features::SetDifficulty(Features::Difficulty::EASY);
			            break;
			        case 2:
			            Features::SetDifficulty(Features::Difficulty::NORMAL);
			            break;
			        case 3:
			            Features::SetDifficulty(Features::Difficulty::PROFESSIONAL);
			            break;
			        default:
			            //ErrorBox(hWnd, TEXT("Select a difficulty"));
			            break;
			        }
			    }
			    else
			    {
			        Features::Difficulty currDiff = Features::GetDifficulty();
			        switch (currDiff) //update difficulty combo box
			        {
			        case Features::Difficulty::AMATEUR:
			            if (Cheat::ItmDifficulty != 0)
			                Cheat::ItmDifficulty = 0;
			            break;
			        case Features::Difficulty::EASY:
			            if (Cheat::ItmDifficulty != 1)
			                Cheat::ItmDifficulty = 1;
			            break;
			        case Features::Difficulty::NORMAL:
			            if (Cheat::ItmDifficulty != 2)
			                Cheat::ItmDifficulty = 2;
			            break;
			        case Features::Difficulty::PROFESSIONAL:
			            if (Cheat::ItmDifficulty != 3)
			                Cheat::ItmDifficulty = 3;
			            break;
			        }
			    }

			    ImGui::Text("Set Money");
			    if (ImGui::InputInt("##Money", &Cheat::Money))
			    {
			        Features::SetMoney(Cheat::Money);
			    }
			    else
			    {
			        Cheat::Money = Features::GetMoney();
			    }

			    if (ImGui::Button(ICON_FA_SHOPPING_CART " Open Shop"))
			    {
			        Features::OpenMerchant();
			    }

			    if (ImGui::Button(ICON_FA_FOLDER_OPEN " Open Typewriter / Save Game"))
			    {
			        Features::OpenTypewriter(Features::TypewriterMode::SAVE);
			    }
		}

		// Dumper Tab
		if (Settings::Tab == 2)
		{
			ImGui::Selectable("Infinite Health", &Cheat::InfiniteHealth);
			if (Cheat::InfiniteHealth)
			{
				chON();
				Features::ToggleInfiniteHealth(Cheat::InfiniteHealth);
			}
			else
			{
				chOFF();
				Features::ToggleInfiniteHealth(Cheat::InfiniteHealth);
			}

			ImGui::Selectable("Invincible / God Mode", &Cheat::Invincible);
			if (Cheat::Invincible)
			{
				chON();
				Features::ToggleInvincible(Cheat::Invincible);
			}
			else
			{
				chOFF();
				Features::ToggleInvincible(Cheat::Invincible);
			}

			ImGui::Selectable("Wallkthrough Wall", &Cheat::WallHack);
			if (Cheat::WallHack)
			{
				chON();
				Features::ToggleClipping(Cheat::WallHack);
			}
			else
			{
				chOFF();
				Features::ToggleClipping(Cheat::WallHack);
			}

			ImGui::Selectable("Set Player Up And Down", &Cheat::SetUpDown);
			if (Cheat::SetUpDown)
			{
				chON();
				ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 248, 95, 255));
				ImGui::Text("  Turn on the Walkthrough Wall feature");
				ImGui::Text("  Set Player To UP : I");
				ImGui::Text("  Set Player To UP : K");
				ImGui::PopStyleColor();
				Features::ToggleStUpDown(Cheat::SetUpDown);
			}
			else
			{
				chOFF();
				Features::ToggleStUpDown(Cheat::SetUpDown);
			}

			
			if (ImGui::Button("ASHLEY PRESENT SET"))
			{
				Features::ToggleAshley(Cheat::AshleyPresent);
			}
			else
			{
				Cheat::AshleyPresent = !Features::IsAshleyPresent();
			}

			ImGui::SameLine();
			ImGui::Selectable("Status", Features::IsAshleyPresent());
			if (Features::IsAshleyPresent())
			{
				ImGui::SameLine();
				ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 255, 0, 255));
				ImGui::Text("Ashley Present");
				ImGui::PopStyleColor();
			}
			else
			{
				ImGui::SameLine();
				ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(245, 66, 66, 255)); // RED
				ImGui::Text("Ashley Not Present");
				ImGui::PopStyleColor();
			}
			ImGui::Selectable("Teleport Ashley", &Cheat::AshleyTeleport);
			if (Cheat::AshleyTeleport)
			{
				chON();
				ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 248, 95, 255));
				ImGui::Text("  Turn on the Walkthrough Wall feature");
				ImGui::Text("  Use HOME Hotkey To Teleport Ashley To The Main Player");
				ImGui::PopStyleColor();
				Features::ToggleAshleyTeleport(Cheat::AshleyTeleport);
			}
			else
			{
				chOFF();
				Features::ToggleAshleyTeleport(Cheat::AshleyTeleport);
			}

			
			ImGui::Text("Set Player Movement Speed");
			//Cheat::SpeedHack = Features::GetSpeedPlayer();
			ImGui::SliderFloat("##SpeedHack", &Cheat::SpeedHack, 1.0f, 10.0f, "Speed = %.1f");

		}	


		if (Settings::Tab == 3)
		{
			ImGui::Selectable("Unlimited Ammo Stack", &Cheat::UnlimitedAmmo);
			if (Cheat::UnlimitedAmmo)
			{
				chON();
				Features::ToggleInfiniteAmmo(Cheat::UnlimitedAmmo);
			}
			else
			{
				chOFF();
				Features::ToggleInfiniteAmmo(Cheat::UnlimitedAmmo);
			}

			ImGui::Selectable("No Reload", &Cheat::NoReload);
			if (Cheat::NoReload)
			{
				chON();
				Features::ToggleAmmoNoReload(Cheat::NoReload);
			}
			else
			{
				chOFF();
				Features::ToggleAmmoNoReload(Cheat::NoReload);
			}

			ImGui::Selectable("Infinite Grenade", &Cheat::InfiniteGrenade);
			if (Cheat::InfiniteGrenade)
			{
				chON();
				Features::ToggleInfiniteGrenade(Cheat::InfiniteGrenade);
			}
			else
			{
				chOFF();
				Features::ToggleInfiniteGrenade(Cheat::InfiniteGrenade);
			}

			ImGui::Selectable("Infinite Bow Gun", &Cheat::InfiniteBow);
			if (Cheat::InfiniteBow)
			{
				chON();
				Features::ToggleBow(Cheat::InfiniteBow);
			}
			else
			{
				chOFF();
				Features::ToggleBow(Cheat::InfiniteBow);
			}

			ImGui::Selectable("Always P.R.L 412 Charge", &Cheat::MaxPRL);
			if (Cheat::MaxPRL)
			{
				chON();
				Features::ToggleAutoMaxPRL(Cheat::MaxPRL);
			}
			else
			{
				chOFF();
				Features::ToggleAutoMaxPRL(Cheat::MaxPRL);
			}

			ImGui::Selectable("Fast TMP Fire", &Cheat::FastTMP);
			if (Cheat::FastTMP)
			{
				chON();
				Features::ToggleFastTmp(Cheat::FastTMP);
			}
			else
			{
				chOFF();
				Features::ToggleFastTmp(Cheat::FastTMP);
			}

			ImGui::Selectable("Rapid Fire Weapon", &Cheat::RapidFire);
			if (Cheat::RapidFire)
			{
				chON();
				Features::ToggleRapidFire(Cheat::RapidFire);
			}
			else
			{
				chOFF();
				Features::ToggleRapidFire(Cheat::RapidFire);
			}
		}


		if (Settings::Tab == 4)
		{
			ImGui::Selectable("One Hit Kill Mode", &Cheat::OneHitKill);
			if (Cheat::OneHitKill)
			{
				chON();
				Features::ToggleOneHitKill(Cheat::OneHitKill);
			}
			else
			{
				chOFF();
				Features::ToggleOneHitKill(Cheat::OneHitKill);
			}

			ImGui::Selectable("Motion Less Enemie", &Cheat::FrezeeEnemy);
			if (Cheat::FrezeeEnemy)
			{
				chON();
				Features::ToggleFrezeeEnemie(Cheat::FrezeeEnemy);
			}
			else
			{
				chOFF();
				Features::ToggleFrezeeEnemie(Cheat::FrezeeEnemy);
			}
		}


		if (Settings::Tab == 5)
		{
			ImGui::Text("Marchenaries");
			ImGui::Text("Set Points");
			if (ImGui::InputInt("##Points", &Cheat::Points))
			{
				Features::SetPoints(Cheat::Points);
			}
			else
			{
				Cheat::Money = Features::GetPoints();
			}
			ImGui::Text("Set Points Kill");
			if (ImGui::InputInt("##PointsKill", &Cheat::PointsKill))
			{
				Features::SetPointsKill(Cheat::PointsKill);
			}
			else
			{
				Cheat::Money = Features::GetPointsKill();
			}
			
			ImGui::Spacing();
			ImGui::Selectable("Frezee Time", &Cheat::Time);
			if (Cheat::Time)
			{
				chON();
				Features::SetTime(Cheat::FrezeeEnemy);
			}
			else
			{
				chOFF();
				Cheat::FrezeeEnemy = Features::GetTime();
			}
		}


		if (Settings::Tab == 6)
		{
			ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 248, 95, 255));
			ImGui::Text("Created By : Rizki Kotet");
			ImGui::Text("Copyright 2022 - RTA Code");
			ImGui::Spacing();
			ImGui::Text("Big Thanks To : Allah Swt");
			ImGui::Text("              : Cheat Engine ( Search Features )");
			ImGui::Text("              : GitHub ( Referens )");
			ImGui::Text("              : Visual Studio ( Build Program )");
			ImGui::PopStyleColor();
			ImGui::Spacing();
			if (ImGui::Button("DONAT ME"))
			{
				std::string base_URL = "https://sociabuzz.com/rizkikotet/tribe";
				ShellExecuteA(NULL, "open", base_URL.c_str(), NULL, NULL, SW_SHOWNORMAL);
			}
			ImGui::SameLine();
			if (ImGui::Button("YOUTUBE CHANEL"))
			{
				std::string base_URL = "https://www.youtube.com/channel/UCgBXH4Vd04E6tl40Ffbc_CA";
				ShellExecuteA(NULL, "open", base_URL.c_str(), NULL, NULL, SW_SHOWNORMAL);

			}
			ImGui::SameLine();
			if (ImGui::Button("TELEGRAM"))
			{
				std::string base_URL = "https://t.me/rizki_kotet";
				ShellExecuteA(NULL, "open", base_URL.c_str(), NULL, NULL, SW_SHOWNORMAL);
			}
		}
	}
}

void Menu::Theme()
{
	ImGuiStyle* style = &ImGui::GetStyle();

	style->WindowBorderSize = 0;
	style->WindowTitleAlign = ImVec2(0.5, 0.5);
	style->WindowMinSize = ImVec2(900, 430);

	style->FramePadding = ImVec2(8, 6);

	/*style->Colors[ImGuiCol_TitleBg] = ImColor(255, 101, 53, 255);
	style->Colors[ImGuiCol_TitleBgActive] = ImColor(255, 101, 53, 255);
	style->Colors[ImGuiCol_TitleBgCollapsed] = ImColor(0, 0, 0, 130);

	style->Colors[ImGuiCol_Button] = ImColor(31, 30, 31, 255);
	style->Colors[ImGuiCol_ButtonActive] = ImColor(41, 40, 41, 255);
	style->Colors[ImGuiCol_ButtonHovered] = ImColor(41, 40, 41, 255);

	style->Colors[ImGuiCol_Separator] = ImColor(70, 70, 70, 255);
	style->Colors[ImGuiCol_SeparatorActive] = ImColor(76, 76, 76, 255);
	style->Colors[ImGuiCol_SeparatorHovered] = ImColor(76, 76, 76, 255);

	style->Colors[ImGuiCol_FrameBg] = ImColor(37, 36, 37, 255);
	style->Colors[ImGuiCol_FrameBgActive] = ImColor(37, 36, 37, 255);
	style->Colors[ImGuiCol_FrameBgHovered] = ImColor(37, 36, 37, 255);

	style->Colors[ImGuiCol_Header] = ImColor(0, 0, 0, 0);
	style->Colors[ImGuiCol_HeaderActive] = ImColor(0, 0, 0, 0);
	style->Colors[ImGuiCol_HeaderHovered] = ImColor(46, 46, 46, 255);*/


	/*ImGuiStyle* style = &ImGui::GetStyle();*/

	//style->WindowPadding = ImVec2(15, 15);
	//style->WindowRounding = 5.0f;
	////style->FramePadding = ImVec2(5, 5);
	//style->FrameRounding = 4.0f;
	//style->ItemSpacing = ImVec2(12, 8);
	//style->ItemInnerSpacing = ImVec2(8, 6);
	//style->IndentSpacing = 25.0f;
	//style->ScrollbarSize = 15.0f;
	//style->ScrollbarRounding = 9.0f;
	//style->GrabMinSize = 5.0f;
	//style->GrabRounding = 3.0f;

	style->Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
	style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	//style->Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style->Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style->Colors[ImGuiCol_Border] = ImVec4(0.80f, 0.80f, 0.83f, 0.88f);
	style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
	style->Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	//style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
	style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	//style->Colors[ImGuiCol_ComboBg] = ImVec4(0.19f, 0.18f, 0.21f, 1.00f);
	style->Colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_Button] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	//style->Colors[ImGuiCol_Column] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	//style->Colors[ImGuiCol_ColumnHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	//style->Colors[ImGuiCol_ColumnActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_Tab] = ImVec4(0.40f, 0.39f, 0.38f, 0.16f);
	style->Colors[ImGuiCol_TabHovered] = ImVec4(0.40f, 0.39f, 0.38f, 0.39f);
	style->Colors[ImGuiCol_TabActive] = ImVec4(0.40f, 0.39f, 0.38f, 1.00f);
	style->Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
	//style->Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(1.00f, 0.98f, 0.95f, 0.73f);
}
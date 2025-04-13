#include "core/commands/Command.hpp"
#include "core/commands/IntCommand.hpp"
#include "core/commands/ListCommand.hpp"
#include "game/gta/Stats.hpp"
#include "game/gta/ScriptGlobal.hpp"
#include "game/gta/ScriptLocal.hpp"
#include "core/backend/ScriptMgr.hpp"

namespace YimMenu::Features
{
	namespace DiamondCasinoHeist
	{
		static IntCommand _DiamondCasinoHeistCut1{"diamondcasinoheistcut1", "Player 1", "Player 1 cut", std::nullopt, std::nullopt, 0};
		static IntCommand _DiamondCasinoHeistCut2{"diamondcasinoheistcut2", "Player 2", "Player 1 cut", std::nullopt, std::nullopt, 0};
		static IntCommand _DiamondCasinoHeistCut3{"diamondcasinoheistcut3", "Player 3", "Player 1 cut", std::nullopt, std::nullopt, 0};
		static IntCommand _DiamondCasinoHeistCut4{"diamondcasinoheistcut4", "Player 4", "Player 1 cut", std::nullopt, std::nullopt, 0};

		class SetCuts : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				ScriptGlobal(1966898 + 1497 + 736 + 92 + 1).SetValue<int>(_DiamondCasinoHeistCut1.GetState());
                ScriptGlobal(1966898 + 1497 + 736 + 92 + 2).SetValue<int>(_DiamondCasinoHeistCut2.GetState());
                ScriptGlobal(1966898 + 1497 + 736 + 92 + 3).SetValue<int>(_DiamondCasinoHeistCut3.GetState());
                ScriptGlobal(1966898 + 1497 + 736 + 92 + 4).SetValue<int>(_DiamondCasinoHeistCut4.GetState());
			}
		};

		class ForceReady : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				ScriptGlobal(1971261 + 1 + (1 * 68) + 8 + 1).SetValue<int>(1);
                ScriptGlobal(1971261 + 1 + (2 * 68) + 8 + 2).SetValue<int>(1); 
                ScriptGlobal(1971261 + 1 + (3 * 68) + 8 + 3).SetValue<int>(1);
			}
		};

		static std::vector<std::pair<int, const char*>> diamondCasinoHeistDifficulty = {
			{0, "Normal"},
			{1, "Hard"}
		};
		static ListCommand _DiamondCasinoHeistDifficulty{"diamondcasinoheistdifficulty", "Difficulty", "Heist difficulty", diamondCasinoHeistDifficulty, 0};

		static std::vector<std::pair<int, const char*>> diamondCasinoHeistPrimaryTarget = {
			{3, "Diamonds"},
			{1, "Gold"},
			{2, "Artwork"},
			{0, "Cash"}
		};
		static ListCommand _DiamondCasinoHeistPrimaryTarget{"diamondcasinoheistprimarytarget", "Primary Target", "Primary target", diamondCasinoHeistPrimaryTarget, 3};

		static std::vector<std::pair<int, const char*>> diamondCasinoHeistApproach = {
			{0, "Silent & Sneaky"},
			{1, "The Big Con"},
			{2, "Aggressive"}
		};
		static ListCommand _DiamondCasinoHeistApproach{"diamondcasinoheistapproach", "Approach", "Heist approach", diamondCasinoHeistApproach, 0};

		static std::vector<std::pair<int, const char*>> diamondCasinoHeistGunman = {
			{0, "Chester McCoy"},
			{1, "Gustavo Mota"},
			{2, "Patrick McReary"},
			{3, "Charlie Reed"},
			{4, "Karl Abolaji"},
			{5, "Remove Gunman"}
		};
		static ListCommand _DiamondCasinoHeistGunman{"diamondcasinoheistgunman", "Gunman", "Gunman", diamondCasinoHeistGunman, 0};

		static std::vector<std::pair<int, const char*>> diamondCasinoHeistWeapons = {
		    {0, "Weapon 1"},
			{1, "Weapon 2"}
		};
		static ListCommand _DiamondCasinoHeistWeapon{"diamondcasinoheistweapon", "Weapon", "Weapon", diamondCasinoHeistWeapons, 0};

		static std::vector<std::pair<int, const char*>> diamondCasinoHeistDriver = {
			{0, "Chester McCoy"},
			{1, "Eddie Toh"},
			{2, "Taliana Martinez"},
			{3, "Zach Nelson"},
			{4, "Karim Denz"},
			{5, "Remove Driver"}
		};
		static ListCommand _DiamondCasinoHeistDriver{"diamondcasinoheistdriver", "Driver", "Driver", diamondCasinoHeistDriver, 0};

		static std::vector<std::pair<int, const char*>> diamondCasinoHeistVehicles = {
			{0, "Vehicle 1"}, {1, "Vehicle 2"}, {2, "Vehicle 3"}, {3, "Vehicle 4"}
		};
		static ListCommand _DiamondCasinoHeistVehicle{"diamondcasinoheistvehicle", "Vehicle", "Vehicle", diamondCasinoHeistVehicles, 0};

		static std::vector<std::pair<int, const char*>> diamondCasinoHeistHacker = {
			{4, "Avi Schwartzman"},
		    {5, "Paige Harris"},
		    {2, "Christian Feltz"},
		    {3, "Yohan Blair"},
		    {1, "Rickie Lukens"},
		    {6, "Remove Hacker"}
		};
		static ListCommand _DiamondCasinoHeistHacker{"diamondcasinoheisthacker", "Hacker", "Hacker", diamondCasinoHeistHacker, 4};

		class Setup : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				Stats::SetInt("MPX_H3_COMPLETEDPOSIX", -1);
				Stats::SetInt("MPX_H3OPT_MASKS", 4);
				Stats::SetInt("MPX_H3OPT_WEAPS", _DiamondCasinoHeistWeapon.GetState());
				Stats::SetInt("MPX_H3OPT_VEHS", _DiamondCasinoHeistVehicle.GetState());
				Stats::SetInt("MPX_CAS_HEIST_FLOW", -1);
				Stats::SetInt("MPX_H3_LAST_APPROACH", 0);
				Stats::SetInt("MPX_H3OPT_APPROACH", _DiamondCasinoHeistApproach.GetState() + 1); // 1 = Silent & Sneaky, 2 = The Big Con, 3 = Aggressive

				switch (_DiamondCasinoHeistDifficulty.GetState())
				{
				case 0: Stats::SetInt("MPX_H3_HARD_APPROACH", 0); break;
				case 1: Stats::SetInt("MPX_H3_HARD_APPROACH", _DiamondCasinoHeistApproach.GetState() + 1); break;
				default: break;
				}
				
				Stats::SetInt("MPX_H3OPT_TARGET", _DiamondCasinoHeistPrimaryTarget.GetState());
				Stats::SetInt("MPX_H3OPT_POI", 1023);
				Stats::SetInt("MPX_H3OPT_ACCESSPOINTS", 2047);

				switch (_DiamondCasinoHeistGunman.GetState())
				{
				case 0: Stats::SetInt("MPX_H3OPT_CREWWEAP", 4); break;
				case 1: Stats::SetInt("MPX_H3OPT_CREWWEAP", 2); break;
				case 2: Stats::SetInt("MPX_H3OPT_CREWWEAP", 5); break;
				case 3: Stats::SetInt("MPX_H3OPT_CREWWEAP", 3); break;
				case 4: Stats::SetInt("MPX_H3OPT_CREWWEAP", 1); break;
				case 5: Stats::SetInt("MPX_H3OPT_CREWWEAP", 6); break;
				default: break;
				}

				switch (_DiamondCasinoHeistDriver.GetState())
				{
				case 0: Stats::SetInt("MPX_H3OPT_CREWDRIVER", 5); break;
				case 1: Stats::SetInt("MPX_H3OPT_CREWDRIVER", 3); break;
				case 2: Stats::SetInt("MPX_H3OPT_CREWDRIVER", 2); break;
				case 3: Stats::SetInt("MPX_H3OPT_CREWDRIVER", 4); break;
				case 4: Stats::SetInt("MPX_H3OPT_CREWDRIVER", 1); break;
				case 5: Stats::SetInt("MPX_H3OPT_CREWDRIVER", 6); break;
				default: break;
				}

				Stats::SetInt("MPX_H3OPT_CREWHACKER", _DiamondCasinoHeistHacker.GetState());
				Stats::SetInt("MPX_H3OPT_DISRUPTSHIP", 3); // Security Strength: 1 = Strong, 2 = Medium, 3 = Weak
				Stats::SetInt("MPX_H3OPT_BODYARMORLVL", -1);
				Stats::SetInt("MPX_H3OPT_KEYLEVELS", 2);   // 1 = Level1 Security Pass, 2 = Level2 Security Pass

				Stats::SetInt("MPX_H3OPT_BITSET0", rand() % (INT_MAX)); // Refresh board
				Stats::SetInt("MPX_H3OPT_BITSET1", rand() % (INT_MAX)); // Refresh board

                ScriptMgr::Yield(500ms);

				Stats::SetInt("MPX_H3OPT_BITSET0", -1); // Refresh board
				Stats::SetInt("MPX_H3OPT_BITSET1", -1); // Refresh board
			}
		};

		static IntCommand _DiamondCasinoHeistPotentialTake{"diamondcasinoheistpotentialtake", "Potential Take", "Updates potential take", std::nullopt, std::nullopt, 0};
		
		class SetPotentialTake : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				int primary_target = Stats::GetInt("MPX_H3OPT_TARGET");

				if (0 <= primary_target && primary_target <= 3)
				{
					switch (primary_target)
					{
					case 0: ScriptGlobal(262145 + 28347 + 0).SetValue<int>(_DiamondCasinoHeistPotentialTake.GetState()); break; // "Cash"
					case 1: ScriptGlobal(262145 + 28347 + 2).SetValue<int>(_DiamondCasinoHeistPotentialTake.GetState()); break; // "Gold"
					case 2: ScriptGlobal(262145 + 28347 + 1).SetValue<int>(_DiamondCasinoHeistPotentialTake.GetState()); break; // "Artwork"
					case 3: ScriptGlobal(262145 + 28347 + 3).SetValue<int>(_DiamondCasinoHeistPotentialTake.GetState()); break; // "Diamond"
					default: break;
					}
				}
			}
		};
		
		static IntCommand _DiamondCasinoHeistActualTake{"diamondcasinoheistactualtake", "Actual Take", "Updates actual take", std::nullopt, std::nullopt, 0};

		class SetActualTake : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				ScriptLocal("fm_mission_controller"_J, 20387 + 2686).SetValue<int>(_DiamondCasinoHeistActualTake.GetState());
			}
		};

		class SkipHacking : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				if (ScriptLocal("fm_mission_controller"_J, 53999).GetValue<int>() != 1)
					ScriptLocal("fm_mission_controller"_J, 53999).SetValue<int>(5); // Fingerprint
           
                if (ScriptLocal("fm_mission_controller"_J, 55065).GetValue<int>() != 1)
					ScriptLocal("fm_mission_controller"_J, 55065).SetValue<int>(5); // Keypad
			}
		};

		class SkipDrilling : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				ScriptLocal("fm_mission_controller"_J, 10547 + 7).SetValue<int>(ScriptLocal("fm_mission_controller"_J, 10547 + 37).GetValue<int>());
			}
		};

		class InstantFinish : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				Scripts::ForceScriptHost(Scripts::FindScriptThread("fm_mission_controller"_J));
				ScriptMgr::Yield(500ms);

				ScriptLocal("fm_mission_controller"_J, 20387 + 1740 + 1).SetValue<int>(80);
				ScriptLocal("fm_mission_controller"_J, 20387 + 2686).SetValue<int>(4443220);
				ScriptLocal("fm_mission_controller"_J, 20387 + 1062).SetValue<int>(5);
				ScriptLocal("fm_mission_controller"_J, 20387).SetValue<int>(12);
				ScriptLocal("fm_mission_controller"_J, 29006 + 1).SetValue<int>(99999);
				ScriptLocal("fm_mission_controller"_J, 32462 + 1 + 68).SetValue<int>(99999);
			}
		};

		static SetCuts _DiamondCasinoHeistSetCuts{"diamondcasinoheistsetcuts", "Set Cuts", "Sets heist cut"};
		static ForceReady _DiamondCasinoHeistForceReady{"diamondcasinoheistforceready", "Force Ready", "Forces all players to be ready"};
		static Setup _DiamondCasinoHeistSetup{"diamondcasinoheistsetup", "Setup", "Sets up diamond casino heist"};
		static SetPotentialTake _DiamondCasinoHeistSetPotentialTake{"diamondcasinoheistsetpotentialtake", "Set Potential Take", "Updates potential take"};
		static SetActualTake _DiamondCasinoHeistSetActualTake{"diamondcasinoheistsetactualtake", "Set Actual Take", "Updates actual take"};
		static SkipHacking _DiamondCasinoHeistSkipHacking{"diamondcasinoheistskiphacking", "Skip Hacking", "Skips hacking process"};
		static SkipDrilling _DiamondCasinoHeistSkipDrilling{"diamondcasinoheistskipdrilling", "Skip Drilling", "Skips drilling process"};
		static InstantFinish _DiamondCasinoHeistInstantFinish{"diamondcasinoheistinstantfinish", "Instant Finish", "Instantly passes the heist"};
	}
}
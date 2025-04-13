#include "core/commands/Command.hpp"
#include "core/commands/IntCommand.hpp"
#include "core/commands/ListCommand.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Natives.hpp"
#include "game/gta/Stats.hpp"
#include "game/gta/ScriptGlobal.hpp"
#include "game/gta/ScriptLocal.hpp"
#include "core/backend/ScriptMgr.hpp"

namespace YimMenu::Features
{
	namespace CayoPericoHeist
	{
		static IntCommand _CayoPericoHeistCut1{"cayopericoheistcut1", "Player 1", "Player 1 cut", std::nullopt, std::nullopt, 0};
		static IntCommand _CayoPericoHeistCut2{"cayopericoheistcut2", "Player 2", "Player 1 cut", std::nullopt, std::nullopt, 0};
		static IntCommand _CayoPericoHeistCut3{"cayopericoheistcut3", "Player 3", "Player 1 cut", std::nullopt, std::nullopt, 0};
		static IntCommand _CayoPericoHeistCut4{"cayopericoheistcut4", "Player 4", "Player 1 cut", std::nullopt, std::nullopt, 0};

		class SetCuts : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				ScriptGlobal(1973698 + 831 + 56 + 1).SetValue<int>(_CayoPericoHeistCut1.GetState());
                ScriptGlobal(1973698 + 831 + 56 + 2).SetValue<int>(_CayoPericoHeistCut2.GetState());
                ScriptGlobal(1973698 + 831 + 56 + 3).SetValue<int>(_CayoPericoHeistCut3.GetState());
				ScriptGlobal(1973698 + 831 + 56 + 4).SetValue<int>(_CayoPericoHeistCut4.GetState());
			}
		};

		class ForceReady : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				ScriptGlobal(1974810 + 1 + (1 * 27) + 8 + 1).SetValue<int>(1);
                ScriptGlobal(1974810 + 1 + (2 * 27) + 8 + 2).SetValue<int>(1);
                ScriptGlobal(1974810 + 1 + (3 * 27) + 8 + 3).SetValue<int>(1);
			}
		};

		static std::vector<std::pair<int, const char*>> cayoPericoHeistDifficulty = {
			{126823, "Normal"},
			{131055, "Hard"}
		};
		static ListCommand _CayoPericoHeistDifficulty{"cayopericoheistdifficulty", "Difficulty", "Heist difficulty", cayoPericoHeistDifficulty, 126823};

		static std::vector<std::pair<int, const char*>> cayoPericoHeistPrimaryTarget = {
			{5, "Panther Statue"},
			{3, "Pink Diamond"},
			{4, "Madrazo Files"},
			{2, "Bearer Bonds"},
			{1, "Ruby Necklace"},
			{0, "Sinsimito Tequila"}
		};
		static ListCommand _CayoPericoHeistPrimaryTarget{"cayopericoheistprimarytarget", "Primary Target", "Primary target", cayoPericoHeistPrimaryTarget, 5};

		static std::vector<std::pair<int, const char*>> cayoPericoHeistWeapon = {
			{1, "Aggressor"},
			{2, "Conspirator"},
			{3, "Crack Shot"},
			{4, "Saboteur"},
			{5, "Marksman"}
		};
		static ListCommand _CayoPericoHeistWeapon{"cayopericoheistweapon", "Weapon", "Weapon category", cayoPericoHeistWeapon, 2};

		class Setup : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				Stats::SetInt("MPX_H4CNF_TARGET", _CayoPericoHeistPrimaryTarget.GetState()); // Primary target
                Stats::SetInt("MPX_H4LOOT_CASH_I", 2359448);
                Stats::SetInt("MPX_H4LOOT_CASH_I_SCOPED", 2359448);
                Stats::SetInt("MPX_H4LOOT_CASH_C", 0);
                Stats::SetInt("MPX_H4LOOT_CASH_C_SCOPED", 0);
                Stats::SetInt("MPX_H4LOOT_COKE_I", 4901222);
                Stats::SetInt("MPX_H4LOOT_COKE_I_SCOPED", 4901222);
                Stats::SetInt("MPX_H4LOOT_COKE_C", 0);
                Stats::SetInt("MPX_H4LOOT_COKE_C_SCOPED", 0);
                Stats::SetInt("MPX_H4LOOT_GOLD_I", 0);
                Stats::SetInt("MPX_H4LOOT_GOLD_I_SCOPED", 0);
                Stats::SetInt("MPX_H4LOOT_GOLD_C", 255);
                Stats::SetInt("MPX_H4LOOT_GOLD_C_SCOPED", 255);
                Stats::SetInt("MPX_H4LOOT_WEED_I", 0);
                Stats::SetInt("MPX_H4LOOT_WEED_I_SCOPED", 0);
                Stats::SetInt("MPX_H4LOOT_WEED_C", 0);
                Stats::SetInt("MPX_H4LOOT_WEED_C_SCOPED", 0);
                Stats::SetInt("MPX_H4LOOT_PAINT", 127);
                Stats::SetInt("MPX_H4LOOT_PAINT_SCOPED", 127);
                Stats::SetInt("MPX_H4LOOT_CASH_V", 599431);
                Stats::SetInt("MPX_H4LOOT_COKE_V", 1198863);
                Stats::SetInt("MPX_H4LOOT_GOLD_V", 1598484);
                Stats::SetInt("MPX_H4LOOT_PAINT_V", 1198863);
				Stats::SetInt("MPX_H4LOOT_WEED_V", 0);
				Stats::SetInt("MPX_H4_PROGRESS", _CayoPericoHeistDifficulty.GetState()); // Difficulty
                Stats::SetInt("MPX_H4CNF_BS_GEN", 262143);
                Stats::SetInt("MPX_H4CNF_BS_ENTR", 63);
                Stats::SetInt("MPX_H4CNF_BS_ABIL", 63);
                Stats::SetInt("MPX_H4CNF_WEP_DISRP", 3);
                Stats::SetInt("MPX_H4CNF_ARM_DISRP", 3);
                Stats::SetInt("MPX_H4CNF_HEL_DISRP", 3);
                Stats::SetInt("MPX_H4CNF_APPROACH", -1);
                Stats::SetInt("MPX_H4CNF_BOLTCUT", 4424);
                Stats::SetInt("MPX_H4CNF_UNIFORM", 5256);
                Stats::SetInt("MPX_H4CNF_GRAPPEL", 5156);
                Stats::SetInt("MPX_H4_MISSIONS", -1);
				Stats::SetInt("MPX_H4CNF_WEAPONS", _CayoPericoHeistWeapon.GetState()); // Weapon
                Stats::SetInt("MPX_H4CNF_TROJAN", 5);
				Stats::SetInt("MPX_H4_PLAYTHROUGH_STATUS", 100);

                ScriptMgr::Yield(500ms);

                ScriptLocal("heist_island_planning"_J, 1566).SetValue<int>(2); // Reload Planning Screen
			}
		};

		static IntCommand _CayoPericoHeistPrimaryTargetValue{"cayopericoheistprimarytargetvalue", "Primary Target Value", "Updates primary target value", std::nullopt, std::nullopt, 0};

		class SetPrimaryTargetValue : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				int primary_target = Stats::GetInt("MPX_H4CNF_TARGET");

				if (0 <= primary_target && primary_target <= 5)
				{
					ScriptGlobal(262145 + 29496 + primary_target).SetValue<int>(_CayoPericoHeistPrimaryTargetValue.GetState());
				}
			}
		};

		static IntCommand _CayoPericoHeistSecondaryTakeValue{"cayopericoheistsecondarytakevalue", "Secondary Take Value", "Updates secondary take value", std::nullopt, std::nullopt, 0};

		class SetSecondaryTakeValue : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				ScriptLocal("fm_mission_controller_2020"_J, 56033 + 1518 + 53).SetValue<int>(_CayoPericoHeistSecondaryTakeValue.GetState());
			}
		};

		class SkipCooldown : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				Stats::SetInt("MPX_H4_TARGET_POSIX", 1);
				Stats::SetInt("MPX_H4_COOLDOWN", 1);
				Stats::SetInt("MPX_H4_COOLDOWN_HARD", 1);
			}
		};

		class SkipHacking : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				ScriptLocal("fm_mission_controller_2020"_J, 25388).SetValue<int>(5);
			}
		};

		class CutSewer : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				ScriptLocal("fm_mission_controller_2020"_J, 30212).SetValue<int>(6);
			}
		};

		class CutGlass : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				ScriptLocal("fm_mission_controller_2020"_J, 31451 + 3).SetValue<float>(100.0f);
			}
		};

		class TakePrimaryTarget : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				auto ped = Self::GetPed();

				if (!ped)
					return;

				auto pos     = ped.GetPosition();
				auto heading = ped.GetHeading();

				TASK::TASK_GO_STRAIGHT_TO_COORD(ped.GetHandle(), 5006.917, -5755.931, 15.484, 1.0, 3, 15, 5);
				ScriptLocal("fm_mission_controller_2020"_J, 31450).SetValue<int>(5);
				ScriptLocal("fm_mission_controller_2020"_J, 31451).SetValue<int>(3);

				ScriptMgr::Yield(4000ms);

                TASK::TASK_GO_STRAIGHT_TO_COORD(ped.GetHandle(), pos.x, pos.y, pos.z, 1.0, 3, heading, 5);
			}
		};

		class InstantFinish : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				Scripts::ForceScriptHost(Scripts::FindScriptThread("fm_mission_controller_2020"_J));
				ScriptMgr::Yield(500ms);

				ScriptLocal("fm_mission_controller_2020"_J, 52581).SetValue<int>(9);
				ScriptLocal("fm_mission_controller_2020"_J, 52581 + 1776 + 1).SetValue<int>(50);
			}
		};

		static SetCuts _CayoPericoHeistSetCuts{"cayopericoheistsetcuts", "Set Cuts", "Sets heist cut"};
		static ForceReady _CayoPericoHeistForceReady{"cayopericoheistforceready", "Force Ready", "Forces all players to be ready"};
		static Setup _CayoPericoHeistSetup{"cayopericoheistsetup", "Setup", "Sets up cayo perico heist"};
		static SetPrimaryTargetValue _CayoPericoHeistSetPrimaryTargetValue{"cayopericoheistsetprimarytargetvalue", "Set Primary Target Value", "Updates primary target value"};
		static SetSecondaryTakeValue _CayoPericoHeistSetSecondaryTakeValue{"cayopericoheistsetsecondarytakevalue", "Set Secondary Take Value", "Updates secondary take value"};
		static SkipCooldown _CayoPericoHeistSkipCooldown{"cayopericoheistskipcooldown", "Skip Cooldown", "Skips the cooldown between each Cayo Perico heist"};
		static SkipHacking _CayoPericoHeistSkipHacking{"cayopericoheistskiphacking", "Skip Hacking", "Skips hacking process"};
		static CutSewer _CayoPericoHeistCutSewer{"cayopericoheistcutsewer", "Cut Sewer", "Cuts the sewer"};
		static CutGlass _CayoPericoHeistCutGlass{"cayopericoheistcutglass", "Cut Glass", "Cuts the glass"};
		static TakePrimaryTarget _CayoPericoHeistTakePrimaryTarget{"cayopericoheisttakeprimarytarget", "Take Primary Target", "Takes primary target"};
		static InstantFinish _CayoPericoHeistInstantFinish{"cayopericoheistinstantfinish", "Instant Finish", "Instantly passes the heist"};
	}
}
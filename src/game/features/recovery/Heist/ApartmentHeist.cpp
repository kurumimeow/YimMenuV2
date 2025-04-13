#include "core/commands/IntCommand.hpp"
#include "core/commands/Command.hpp"
#include "game/gta/Stats.hpp"
#include "game/gta/ScriptGlobal.hpp"
#include "game/gta/ScriptLocal.hpp"
#include "core/backend/ScriptMgr.hpp"

namespace YimMenu::Features
{
	namespace ApartmentHeist
	{
		static IntCommand _ApartmentHeistCut1{"apartmentheistcut1", "Player 1", "Player 1 cut", std::nullopt, std::nullopt, 0};
		static IntCommand _ApartmentHeistCut2{"apartmentheistcut2", "Player 2", "Player 1 cut", std::nullopt, std::nullopt, 0};
		static IntCommand _ApartmentHeistCut3{"apartmentheistcut3", "Player 3", "Player 1 cut", std::nullopt, std::nullopt, 0};
		static IntCommand _ApartmentHeistCut4{"apartmentheistcut4", "Player 4", "Player 1 cut", std::nullopt, std::nullopt, 0};

		class SetCuts : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				ScriptGlobal(1929794 + 1 + 1).SetValue<int>(100 - (_ApartmentHeistCut1.GetState() + _ApartmentHeistCut2.GetState() + _ApartmentHeistCut3.GetState() + _ApartmentHeistCut4.GetState()));
				ScriptGlobal(1929794 + 1 + 2).SetValue<int>(_ApartmentHeistCut2.GetState());
				ScriptGlobal(1929794 + 1 + 3).SetValue<int>(_ApartmentHeistCut3.GetState());
				ScriptGlobal(1929794 + 1 + 4).SetValue<int>(_ApartmentHeistCut4.GetState());

				ScriptMgr::Yield(500ms);

				ScriptGlobal(1931762 + 3008 + 1).SetValue<int>(-1 * (ScriptGlobal(1929794 + 1 + 1).GetValue<int>() + ScriptGlobal(1929794 + 1 + 2).GetValue<int>() + ScriptGlobal(1929794 + 1 + 3).GetValue<int>() + ScriptGlobal(1929794 + 1 + 4).GetValue<int>() - 100));
				ScriptGlobal(1931762 + 3008 + 2).SetValue<int>(ScriptGlobal(1929794 + 1 + 2).GetValue<int>());
				ScriptGlobal(1931762 + 3008 + 3).SetValue<int>(ScriptGlobal(1929794 + 1 + 3).GetValue<int>());
				ScriptGlobal(1931762 + 3008 + 4).SetValue<int>(ScriptGlobal(1929794 + 1 + 4).GetValue<int>());
			}
		};

		class ForceReady : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				ScriptGlobal(2657994 + 1 + (1 * 467) + 269).SetValue<int>(6);
				ScriptGlobal(2657994 + 1 + (2 * 467) + 269).SetValue<int>(6);
				ScriptGlobal(2657994 + 1 + (3 * 467) + 269).SetValue<int>(6);
			}
		};

		class Setup : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				Stats::SetInt("MPX_HEIST_PLANNING_STAGE", -1);
			}
		};

		class SkipHacking : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				ScriptLocal("fm_mission_controller"_J, 12216 + 24).SetValue<int>(7);
				ScriptLocal("fm_mission_controller"_J, 10213).SetValue<int>(ScriptLocal("fm_mission_controller"_J, 10213).GetValue<int>() | (1 << 9));
			}
		};

		class SkipDrilling : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				ScriptLocal("fm_mission_controller"_J, 10507 + 11).SetValue<float>(100.0f);
			}
		};

		class InstantFinish : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				Scripts::ForceScriptHost(Scripts::FindScriptThread("fm_mission_controller"_J));
				ScriptMgr::Yield(500ms);

				ScriptLocal("fm_mission_controller"_J, 20387 + 1725 + 1).SetValue<int>(80);
				ScriptLocal("fm_mission_controller"_J, 20387).SetValue<int>(12);
				ScriptLocal("fm_mission_controller"_J, 29006 + 1).SetValue<int>(99999);
				ScriptLocal("fm_mission_controller"_J, 32462 + 1 + 68).SetValue<int>(99999);

				// TODO: find a way og getting current heist info so that InstantFinishPacific can be implemented here conditionally.
			}
		};

		class InstantFinishPacific : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				Scripts::ForceScriptHost(Scripts::FindScriptThread("fm_mission_controller"_J));
				ScriptMgr::Yield(500ms);

				ScriptLocal("fm_mission_controller"_J, 20387 + 2686).SetValue<int>(1875000);
				ScriptLocal("fm_mission_controller"_J, 20387 + 1062).SetValue<int>(5);
				ScriptLocal("fm_mission_controller"_J, 20387).SetValue<int>(12);
				ScriptLocal("fm_mission_controller"_J, 29006 + 1).SetValue<int>(99999);
				ScriptLocal("fm_mission_controller"_J, 32462 + 1 + 68).SetValue<int>(99999);
			}
		};

		static SetCuts _ApartmentHeistSetCuts{"apartmentheistsetcuts", "Set Cuts", "Sets heist cut"};
		static ForceReady _ApartmentHeistForceReady{"apartmentheistforceready", "Force Ready", "Forces all players to be ready"};
		static Setup _ApartmentHeistSetup{"apartmentheistsetup", "Setup", "Sets up current apartment heist"};
		static SkipHacking _ApartmentHeistSkipHacking{"apartmentheistskiphacking", "Skip Hacking", "Skips hacking process"};
		static SkipDrilling _ApartmentHeistSkipDrilling{"apartmentheistskipdrilling", "Skip Drilling", "Skips drilling process"};
		static InstantFinish _ApartmentHeistInstantFinish{"apartmentheistinstantfinish", "Instant Finish", "Instantly passes the heist"};
		static InstantFinishPacific _ApartmentHeistInstantFinishPacific{"apartmentheistinstantfinishpacific", "Instant Finish (Pacific)", "Instantly passes the heist"};
	}
}
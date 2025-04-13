#include "DiamondCasinoHeist.hpp"

namespace YimMenu::Submenus
{
	std::shared_ptr<TabItem> RenderDiamondCasinoHeistMenu()
	{
		auto tab = std::make_shared<TabItem>("Diamond Casino Heist");

		auto cuts = std::make_shared<Group>("Heist Cuts", 2);
		auto setups = std::make_shared<Group>("Heist Setups", 1);
		auto config = std::make_shared<Group>("");
		auto config_ = std::make_shared<Group>("");
		auto sep = std::make_shared<Group>("");
		auto misc = std::make_shared<Group>("Misc", 1);

		cuts->AddItem(std::make_shared<IntCommandItem>("diamondcasinoheistcut1"_J));
		cuts->AddItem(std::make_shared<IntCommandItem>("diamondcasinoheistcut3"_J));
		cuts->AddItem(std::make_shared<IntCommandItem>("diamondcasinoheistcut2"_J));
		cuts->AddItem(std::make_shared<IntCommandItem>("diamondcasinoheistcut4"_J));
		cuts->AddItem(std::make_shared<CommandItem>("diamondcasinoheistforceready"_J));
		cuts->AddItem(std::make_shared<CommandItem>("diamondcasinoheistsetcuts"_J));

		setups->AddItem(std::make_shared<ListCommandItem>("diamondcasinoheistdifficulty"_J));
		setups->AddItem(std::make_shared<ListCommandItem>("diamondcasinoheistprimarytarget"_J));
		setups->AddItem(std::make_shared<ListCommandItem>("diamondcasinoheistapproach"_J));

		config->AddItem(std::make_shared<ListCommandItem>("diamondcasinoheistgunman"_J));
		config->AddItem(std::make_shared<ImGuiItem>([] {
			ImGui::SameLine();
		}));
		config->AddItem(std::make_shared<ListCommandItem>("diamondcasinoheistweapon"_J));
		config->AddItem(std::make_shared<ListCommandItem>("diamondcasinoheistdriver"_J));
		config->AddItem(std::make_shared<ImGuiItem>([] {
			ImGui::SameLine();
		}));
		config->AddItem(std::make_shared<ListCommandItem>("diamondcasinoheistvehicle"_J));
		config->AddItem(std::make_shared<ListCommandItem>("diamondcasinoheisthacker"_J));

		config_->AddItem(std::make_shared<CommandItem>("diamondcasinoheistsetup"_J));

		sep->AddItem(std::make_shared<IntCommandItem>("diamondcasinoheistpotentialtake"_J));
		sep->AddItem(std::make_shared<ImGuiItem>([] {
			ImGui::SameLine();
		}));
		sep->AddItem(std::make_shared<CommandItem>("diamondcasinoheistsetpotentialtake"_J));
		sep->AddItem(std::make_shared<IntCommandItem>("diamondcasinoheistactualtake"_J));
		sep->AddItem(std::make_shared<ImGuiItem>([] {
			ImGui::SameLine();
		}));
		sep->AddItem(std::make_shared<CommandItem>("diamondcasinoheistsetactualtake"_J));

		misc->AddItem(std::make_shared<CommandItem>("diamondcasinoheistskiphacking"_J));
		misc->AddItem(std::make_shared<CommandItem>("diamondcasinoheistskipdrilling"_J));
		misc->AddItem(std::make_shared<CommandItem>("diamondcasinoheistinstantfinish"_J));

		tab->AddItem(cuts);
		tab->AddItem(setups);
		tab->AddItem(config);
		tab->AddItem(config_);
		tab->AddItem(sep);
		tab->AddItem(misc);

		return tab;
	}
}
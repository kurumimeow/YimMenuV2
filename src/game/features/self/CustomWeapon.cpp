#include "CustomWeapon.hpp"
#include "core/backend/FiberPool.hpp"
#include "core/backend/ScriptMgr.hpp"
#include "core/frontend/Notifications.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Object.hpp"
#include "game/gta/data/DecalTypes.hpp"
#include "types/script/Timer.hpp"

namespace YimMenu::Features
{
	void CustomWeapon::OnTick()
	{
		CustomWeapons selectedWeaponType = static_cast<CustomWeapons>(_CustomWeaponType.GetState());

		if (bool isGravityGunSelected = (selectedWeaponType == CustomWeapons::GRAVITY_GUN); _IsGravityGunEnabled.GetState() != isGravityGunSelected)
			_IsGravityGunEnabled.SetState(isGravityGunSelected);

		if (bool isVehicleGunSelected = (selectedWeaponType == CustomWeapons::VEHICLE_GUN); _IsVehicleGunEnabled.GetState() != isVehicleGunSelected)
			_IsVehicleGunEnabled.SetState(isVehicleGunSelected);

		if (bool isPaintGunSelected = (selectedWeaponType == CustomWeapons::PAINT_GUN); _IsPaintGunEnabled.GetState() != isPaintGunSelected)
			_IsPaintGunEnabled.SetState(isPaintGunSelected);

		for (const auto& control : attackControls)
			PAD::DISABLE_CONTROL_ACTION(0, static_cast<int>(control), true);

		Entity m_Entity{nullptr};
		bool isCustomWeaponActionAllowed = !_CustomWeaponEnabledOnWeaponOut.GetState() || WEAPON::IS_PED_ARMED(Self::GetPed().GetHandle(), 4 | 2);

		switch (selectedWeaponType)
		{
		case CustomWeapons::CAGE_GUN:
		{
			if (isCustomWeaponActionAllowed)
			{
				if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_AIM))
				{
					if (PAD::IS_DISABLED_CONTROL_JUST_RELEASED(0, (int)ControllerInputs::INPUT_ATTACK))
					{
						if (RayCast(m_Entity))
						{
							if (m_Entity.IsPed())
							{
								auto location = m_Entity.GetPosition();
								location.z -= 1.0f;

								Object::Create("prop_gold_cont_01"_J, location);
							}
							else
							{
								Notifications::Show("Custom Weapon", "Entity is not a ped.", NotificationType::Warning);
							}
						}
						else
						{
							Notifications::Show("Custom Weapon", "No entity found.", NotificationType::Warning);
						}
					}
				}
			}
			break;
		}
		case CustomWeapons::DELETE_GUN:
		{
			if (isCustomWeaponActionAllowed)
			{
				if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_AIM))
				{
					if (PAD::IS_DISABLED_CONTROL_JUST_RELEASED(0, (int)ControllerInputs::INPUT_ATTACK))
					{
						FiberPool::Push([=]() mutable {
							if (RayCast(m_Entity))
							{
								if (m_Entity.IsPed() && m_Entity.IsPlayer())
								{
									Notifications::Show("Custom Weapon", "Player entity cannot be deleted.", NotificationType::Warning);
								}
								else
								{
									auto location = m_Entity.GetPosition();
									auto distance = Self::GetPed().GetPosition().GetDistance(location);

									if (distance > 500)
									{
										Notifications::Show("Custom Weapon", "Entity is too far.", NotificationType::Warning);
									}
									else
									{
										if (m_Entity.RequestControl(300))
										{
											m_Entity.Delete();
										}
										else
										{
											Notifications::Show("Custom Weapon", "Failed to take control of entity.", NotificationType::Error);
										}
									}
								}
							}
							else
							{
								Notifications::Show("Custom Weapon", "No entity found.", NotificationType::Warning);
							}
						});
					}
				}
			}
			break;
		}
		case CustomWeapons::GRAVITY_GUN:
		{
			static std::vector<Entity> entities = {};
			static Vector3 location;
			static Vector3 entityPos;
			static float distance;
			static constexpr double multiplier = 3.0;
			static const int scroll = 0;

			auto ApplyVelocity = [](Entity entity) {
				if (entity.IsValid())
				{
					if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_WEAPON_WHEEL_NEXT))
						distance -= 5;
					if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_WEAPON_WHEEL_PREV))
						distance += 5;

					if (!entity.RequestControl(0))
						return;

					entity.SetCollision(false);

					entityPos = entity.GetPosition();

					Vector3 rot = CAM::GET_GAMEPLAY_CAM_ROT(2);
					float pitch = Math::DegToRad(rot.x); // vertical
					// float roll = rot.y;
					float yaw = Math::DegToRad(rot.z + 90); // horizontal

					Vector3 velocity;

					velocity.x = location.x + (distance * cos(pitch) * cos(yaw)) - entityPos.x;
					velocity.y = location.y + (distance * sin(yaw) * cos(pitch)) - entityPos.y;
					velocity.z = location.z + (distance * sin(pitch)) - entityPos.z;

					velocity.x *= (float)multiplier;
					velocity.y *= (float)multiplier;
					velocity.z *= (float)multiplier;

					entity.SetVelocity(velocity);
					entity.SetAlpha(105);
				}
			};

			FiberPool::Push([=]() mutable {
				if (isCustomWeaponActionAllowed && PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_AIM))
				{
					location = Self::GetPed().GetPosition();

					if (PAD::IS_DISABLED_CONTROL_JUST_PRESSED(0, (int)ControllerInputs::INPUT_ATTACK))
					{
						if (RayCast(m_Entity))
						{
							auto entityHandle = m_Entity.GetHandle();

							if (m_Entity.IsPed() && m_Entity.IsPlayer())
							{
								Notifications::Show("Custom Weapon", "Gravity gun cannot be applied on player entity.", NotificationType::Warning);
							}
							else
							{
								const auto tempDistance = m_Entity.GetPosition().GetDistance(location);

								if (entities.size() == 0)
								{
									distance = tempDistance;
								}

								if (tempDistance > 500)
								{
									Notifications::Show("Custom Weapon", "Entity is too far.", NotificationType::Warning);
								}
								else
								{
									if (m_Entity.RequestControl(0) && m_Entity.IsPed() && !PED::IS_PED_RAGDOLL(entityHandle))
									{
										TASK::SET_HIGH_FALL_TASK(entityHandle, 0, 0, 0);
									}
									Notifications::Show("Custom Weapon", "Entity set.", NotificationType::Success);

									entities.push_back(m_Entity);
								}
							}
						}
					}

					if (entities.size() > 0)
					{
						for (const auto& entity : entities)
						{
							ApplyVelocity(entity);
						}
					}
				}
				else if (entities.size() > 0)
				{
					for (Entity& entity : entities)
					{
						if (entity.RequestControl(0))
						{
							if (_GravityGunLaunchOnRelease.GetState())
							{
								distance += 100;
								ApplyVelocity(entity);
							}

							entity.SetCollision(true);
							entity.ResetAlpha();
						}
					}

					entities.clear();

					Notifications::Show("Custom Weapon", "Entity is released.", NotificationType::Success);
				}
			});
			break;
		}
		case CustomWeapons::STEAL_VEHICLE_GUN:
		{
			if (isCustomWeaponActionAllowed)
			{
				if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_AIM))
				{
					if (PAD::IS_DISABLED_CONTROL_JUST_RELEASED(0, (int)ControllerInputs::INPUT_ATTACK))
					{
						if (RayCast(m_Entity))
						{
							auto entityHandle = m_Entity.GetHandle();

							if (m_Entity.IsVehicle())
							{
								for (size_t i = 0; i < 8 && !m_Entity.As<Vehicle>().IsSeatFree(-1); i++)
								{
									const auto ped = VEHICLE::GET_PED_IN_VEHICLE_SEAT(entityHandle, -1, 0);
									TASK::CLEAR_PED_TASKS_IMMEDIATELY(ped);

									ScriptMgr::Yield(100ms);
								}

								Self::GetPed().SetInVehicle(m_Entity.As<Vehicle>(), -1);
							}
							else
							{
								Notifications::Show("Custom Weapon", "Invalid vehicle.", NotificationType::Warning);
							}
						}
						else
						{
							Notifications::Show("Custom Weapon", "No entity found.", NotificationType::Warning);
						}
					}
				}
			}
			break;
		}
		case CustomWeapons::REPAIR_GUN:
		{
			if (isCustomWeaponActionAllowed)
			{
				if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_AIM))
				{
					if (PAD::IS_DISABLED_CONTROL_JUST_RELEASED(0, (int)ControllerInputs::INPUT_ATTACK))
					{
						if (RayCast(m_Entity))
						{
							if (m_Entity.IsVehicle())
							{
								m_Entity.As<Vehicle>().Fix();
							}
							else
							{
								Notifications::Show("Custom Weapon", "Invalid vehicle.", NotificationType::Warning);
							}
						}
						else
						{
							Notifications::Show("Custom Weapon", "No entity found.", NotificationType::Warning);
						}
					}
				}
			}
			break;
		}
		case CustomWeapons::VEHICLE_GUN:
		{
			static TIMER vehicleGunTimer;

			if (isCustomWeaponActionAllowed)
			{
				if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_AIM))
				{
					if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_ATTACK) && vehicleGunTimer.HasTimePassed(100, true))
					{
						if (!_VehicleGunModel.GetString().length())
						{
							Notifications::Show("Custom Weapon", "No vehicle model name provided.", NotificationType::Error);
							return;
						}

						auto modelHash = Joaat(_VehicleGunModel.GetString());
						if (!STREAMING::IS_MODEL_IN_CDIMAGE(modelHash))
						{
							Notifications::Show("Custom Weapon", "Invalid vehicle model name provided.", NotificationType::Error);
						}
						else
						{
							Vector3 location = CAM::GET_GAMEPLAY_CAM_COORD();

							FiberPool::Push([location, modelHash]() {
								constexpr int rotation_order = 2;
								auto rot = CAM::GET_GAMEPLAY_CAM_ROT(rotation_order);

								float pitch = Math::DegToRad(rot.x); // vertical
								//float roll = rot.y;
								float yaw = Math::DegToRad(rot.z); // horizontal

								Vector3 forward{-sin(yaw) * cos(pitch), cos(yaw) * cos(pitch), sin(pitch)};
								Vector3 spawnLoc = location;

								spawnLoc.x += forward.x * 10.f;
								spawnLoc.y += forward.y * 10.f;
								spawnLoc.z += forward.z * 10.f;

								auto veh = Vehicle::Create(modelHash, spawnLoc, Self::GetPed().GetHeading(), false);

								Vector3 velocity{forward.x * 150.f, forward.y * 150.f, forward.z * 150.f};

								veh.SetRotation(rot, rotation_order);
								veh.SetVelocity(velocity);

								auto vehHandle = veh.GetHandle();
								ENTITY::SET_VEHICLE_AS_NO_LONGER_NEEDED(&vehHandle);
							});
						}

						vehicleGunTimer.Reset(true);
					}
				}
			}
			break;
		}
		case CustomWeapons::TELEPORT_GUN:
		{
			if (isCustomWeaponActionAllowed)
			{
				if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_AIM))
				{
					if (PAD::IS_DISABLED_CONTROL_JUST_RELEASED(0, (int)ControllerInputs::INPUT_ATTACK))
					{
						Vector3 coords;

						if (RayCast(coords))
						{
							Self::GetPed().TeleportTo(coords);
						}
						else
						{
							Notifications::Show("Custom Weapon", "Invalid teleport location.", NotificationType::Warning);
						}
					}
				}
			}
			break;
		}
		case CustomWeapons::PAINT_GUN:
		{
			static Vector3 paintGunColor;
			ImVec4 color;

			if (_PaintGunRainbowColorEnabled.GetState())
			{
				RainbowColor(paintGunColor, _PaintGunRainbowColorSpeed.GetState(), static_cast<RainbowColorStyle>(_PaintGunRainbowColorStyle.GetState()));
				color = ImVec4(paintGunColor.x / 255.0f, paintGunColor.y / 255.0f, paintGunColor.z / 255.0f, 1.0f);
			}
			else
			{
				color = _PaintGunColor.GetState();
			}

			if (isCustomWeaponActionAllowed)
			{
				if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_AIM))
				{
					if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_ATTACK))
					{
						Vector3 coords;

						FiberPool::Push([=]() mutable {
							if (RayCast(coords))
							{
								GRAPHICS::ADD_DECAL((int)DecalTypes::splatters_paint,
									coords.x,
									coords.y,
									coords.z,
									0,  //true
									0,  //true
									-1, //true
									0,
									1.f,
									0.f,  // always 0
									0.5f, //size x
									0.4f, //size y
									color.x,
									color.y,
									color.z,
									color.w,
									-1,
									true,
									false,
									false);
							}
							else
							{
								Notifications::Show("Custom Weapon", "Invalid paint location.", NotificationType::Warning);
							}
						});
					}
				}
			}
			break;
		}
		default: break;
		}
	}
}
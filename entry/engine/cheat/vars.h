namespace settings
{


	inline bool menu = true;
	///////////////////////////////////////

	// AIM //
	inline bool aimbot = true;
	inline int fov = 500;
	inline float smoothing = 1.1f;
	inline bool showfov = true;
	inline bool dynamic_aim = false;
	inline bool vischeck = false;


	// ESP //
	inline bool box = false;
	inline bool distance = false;
	inline bool health = false;
	inline bool headdot = false;
	inline bool name = false;
	inline bool normal_box = false;
	inline int playerDistance = 200;
	inline bool skeleton = false;
	inline bool streamproof = false;
	inline bool weapon = false;
	inline bool weapon_icon = false;
	inline bool health_shield = false;
	inline bool sheild = false;
	inline bool op = false;
	inline bool fov_changer = false;
	inline bool glow = false;
	inline int glowtype;

	// Weapon Glow
	inline bool weapon_glow = false;
	inline int weapon_glow_index = 2;


	// LOOT //
	inline int lootDistance = 20;


	// INPUT //
	inline int key = 0x02;


	// ESP SETTINGS
	inline bool BackPack = true;
	inline bool Energy = true;
	inline bool EnergyAmmo = true;
	inline bool Heavy = true;
	inline bool HeavyAmmo = true;
	inline bool Helmet = true;
	inline bool Icon = false;
	inline bool Knocked = true;
	inline bool Legendary = true;
	inline bool LightAmmo = true;
	inline bool LightWeapon = true;
	inline bool Medic = true;
	inline bool Shield = true;
	inline bool Shotgun = true;
	inline bool ShotgunAmmo = true;
	inline bool Sniper = true;
	inline bool SniperAmmo = true;
	inline bool Text = false;

	// RADAR //
	inline bool radar = true;

	///////////////////////////////////////

	inline float rgb[3] = { 255, 255, 255 };

	inline float fov_color[3] = { 1.0f, 1.0f, 1.0f };
	inline float target_color[3] = { 1.0f, 1.0f, 1.0f };

	inline float box_color[3] = { 0.0f, 1.0f, 0.0f };
	inline float skel_color[3] = { 0.0f, 1.0f, 0.0f };

	inline float name_color[3] = { 1.0f, 1.0f, 1.0f };
	inline float headdot_color[3] = { 1.0f, 1.0f, 1.0f };
	inline float distance_color[3] = { 1.0f, 1.0f, 1.0f };
	inline float operator_color[3] = { 1.0f, 1.0f, 1.0f };
	inline float weapon_color[3] = { 1.0f, 1.0f, 1.0f };
	inline float weapon_icon_color[3] = { 1.0f, 1.0f, 1.0f };

	inline float box_color_visible[3] = { 0.0f, 1.0f, 0.0f };
	inline float box_color_not_visible[3] = { 1.0f, 0.0f, 0.0f };
	inline float normal_box_color_visible[3] = { 0.0f, 1.0f, 0.0f };
	inline float normal_box_color_not_visible[3] = { 1.0f, 0.0f, 0.0f };
	inline float skel_color_visible[3] = { 0.0f, 1.0f, 1.0f };
	inline float skel_color_not_visible[3] = { 1.0f, 1.0f, 0.0f };
	inline float name_color_visible[3] = { 1.0f, 1.0f, 1.0f };
	inline float name_color_not_visible[3] = { 0.5f, 0.5f, 0.5f };
	inline float distance_color_visible[3] = { 1.0f, 1.0f, 1.0f };
	inline float distance_color_not_visible[3] = { 0.5f, 0.5f, 0.5f };
	inline float operator_color_visible[3] = { 1.0f, 1.0f, 1.0f };
	inline float operator_color_not_visible[3] = { 0.5f, 0.5f, 0.5f };
	inline float weapon_color_visible[3] = { 1.0f, 1.0f, 1.0f };
	inline float weapon_color_not_visible[3] = { 0.5f, 0.5f, 0.5f };
	inline float weapon_icon_color_visible[3] = { 1.0f, 1.0f, 1.0f };
	inline float weapon_icon_color_not_visible[3] = { 0.5f, 0.5f, 0.5f };


	inline float BackpackColor[4] = {
			 255.f,
			 255.f,
			 255.f,
			 255.f
	};
	inline float knockedShieldColor[4] = {
			 255.f,
			 255.f,
			 255.f,
			 255.f
	};
	inline float ShieldColor[4] = {
			 255.f,
			 255.f,
			 255.f,
			 255.f
	};
	inline float HelmetColor[4] = {
		  255.f,
		  255.f,
		  255.f,
		  255.f
	};
	inline float MedicaColor[4] = {
		   255.f,
		   255.f,
		   255.f,
		   255.f
	};
	inline float LightAmmoColor[4] = {
		 255.f,
		 255.f,
		 255.f,
		 255.f
	};
	inline float ShotGunAmmoColor[4] = {
		 255.f,
		 255.f,
		 255.f,
		 255.f
	};
	inline float SniperAmmoColor[4] = {
		255.f,
		255.f,
		255.f,
		255.f
	};
	inline float HeavyAmmoColor[4] = {
		255.f,
		255.f,
		255.f,
		255.f
	};
	inline float EnergyAmmoColor[4] = {
		255.f,
		255.f,
		255.f,
		255.f
	};
	inline float ShotGunColor[4] = {
	   255.f,
	   255.f,
	   255.f,
	   255.f
	};
	inline float LightWeaponColor[4] = {
	   255.f,
	   255.f,
	   255.f,
	   255.f
	};
	inline float SnipertWeaponColor[4] = {
   255.f,
   255.f,
   255.f,
   255.f
	};
	inline float LegendaryWeaponColor[4] = {
255.f,
255.f,
255.f,
255.f
	};
	inline float EnergyWeaponColor[4] = {
255.f,
255.f,
255.f,
255.f
	};
	inline float HeavyWeaponColor[4] = {
255.f,
255.f,
255.f,
255.f
	};

}
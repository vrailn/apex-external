#include "offsets.hpp"
#include <map>
#include <unordered_map>
#define M_PI 3.14159265358979323846



namespace WeaponIDs {
	inline int P2020 = 117;
	inline int RE45 = 87;
	inline int ALTERNATOR = 86;
	inline int R99 = 115;
	inline  int R301 = 0;
	inline  int SPITFIRE = 118;
	inline  int G7_SCOUT = 98;
	inline  int FLATLINE = 97;
	inline  int HEMLOCK = 99;
	inline   int PROWLER = 111;
	inline  int REPEATER_3030 = 124;
	inline   int RAMPAGE = 7;
	inline   int CAR = 125;
	inline  int HAVOC = 93;
	inline   int DEVOTION = 90;
	inline  int LSTAR = 102;
	inline   int TRIPLE_TAKE = 120;
	inline   int VOLT = 123;
	inline   int NEMESIS = 126;
	inline int MOZAMBIQUE = 106;
	inline  int PEACEKEEPER = 114;
	inline  int MASTIFF = 104;
	inline int EVA8 = 95;
	inline   int LONGBOW = 92;
	inline   int CHARGE_RIFLE = 89;
	inline   int SENTINEL = 2;
	inline   int WINGMAN = 121;
	inline   int BOCEK = 3;
	inline  int KRABER = 101;
	inline   int KNIFE = 186;
};

__forceinline uintptr_t get_ms() {
	static LARGE_INTEGER s_frequency;
	static BOOL s_use_qpc = QueryPerformanceFrequency(&s_frequency);
	if (s_use_qpc) {
		LARGE_INTEGER now;
		QueryPerformanceCounter(&now);
		return (1000LL * now.QuadPart) / s_frequency.QuadPart;
	}
	else {
		return GetTickCount64();
	}
}

struct vector3 {
public:
	float x, y, z;

	vector3(float x = 0, float y = 0, float z = 0)
		: x(x), y(y), z(z) {
	}

	inline bool operator==(const vector3& src) const
	{
		return (src.x == x) && (src.y == y) && (src.z == z);
	}

	inline bool operator!=(const vector3& src) const
	{
		return (src.x != x) || (src.y != y) || (src.z != z);
	}
	float Magnitude2D() {
		return std::sqrt(x * x + y * y);
	}
	float Magnitude() {
		return std::sqrt(x * x + y * y + z * z);
	}
	inline vector3 add(vector3 v)
	{
		return vector3(x + v.x, y + v.y, z + v.z);
	}
	inline vector3 sub(vector3 v)
	{
		return vector3(x - v.x, y - v.y, z - v.z);
	}
	inline vector3 mul(float v)
	{
		return vector3(x * v, y * v, z * v);
	}
	inline vector3& operator+=(const vector3& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	inline vector3& operator-=(const vector3& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	inline vector3 operator-(const vector3& ape) const
	{
		return { x - ape.x, y - ape.y, z - ape.z };
	}

	inline vector3 operator+(const vector3& ape) const
	{
		return { x + ape.x, y + ape.y, z + ape.z };
	}

	inline vector3 operator*(float ape) const
	{
		return { x * ape, y * ape, z * ape };
	}

	inline vector3 operator/(float ape) const
	{
		return { x / ape, y / ape, z / ape };
	}

	inline float length()
	{
		return sqrt((x * x) + (y * y) + (z * z));
	}

	inline float distance(vector3 ape)
	{
		return (*this - ape).length();
	}

	inline void clamp() {
		if (x > 180.0f) y = 180.0f;
		else if (y < -180.0f) y = -180.0f;

		if (x > 89.0f) x = 89.0f;
		else if (x < -89.0f) x = -89.0f;

		z = 0;
	}

	inline vector3 calc_angle(const vector3& src, const vector3& dst) {
		vector3 srca = { src.x, src.y, src.z };
		vector3 dsta = { dst.x, dst.y, dst.z };

		vector3 angle = vector3();
		vector3 delta = srca - dsta;

		double hyp = sqrtf((delta.x * delta.x) + (delta.y * delta.y));
		angle.x = (float)(atan(delta.z / hyp) * 57.295779513082f);
		angle.y = (float)(atan(delta.y / delta.x) * 57.295779513082f);
		if (delta.x >= 0.0) angle.y += 180.0f;

		return angle;
	}

	inline void normalize() {
		while (x > 89.0f)
			x -= 180.f;

		while (x < -89.0f)
			x += 180.f;

		while (y > 180.f)
			y -= 360.f;

		while (y < -180.f)
			y += 360.f;
	}

	inline bool is_zero() {
		return (x > -0.1f && x < 0.1f && y > -0.1f && y < 0.1f && z > -0.1f && z < 0.1f);
	}
};
class Vector2
{
public:
	Vector2() : x(0.f), y(0.f)
	{

	}

	Vector2(float _x, float _y) : x(_x), y(_y)
	{

	}
	~Vector2()
	{

	}

	float x;
	float y;
	bool IsEmpty()
	{
		if (x == 0 && y == 0)
			return true;
		else
			return false;
	}
	inline Vector2 operator+(int i) {
		return { x + i, y + i };
	}
	inline Vector2 operator-(Vector2 v) {
		return { x - v.x, y - v.y };
	}
	inline Vector2 flip() {
		return { y, x };
	}

};
struct FVector2D
{
	FVector2D() : X(), Y() {}
	FVector2D(double X, double Y) : X(X), Y(Y) {}

	FVector2D operator + (const FVector2D& other) const { return { this->X + other.X, this->Y + other.Y }; }
	FVector2D operator - (const FVector2D& other) const { return { this->X - other.X, this->Y - other.Y }; }
	FVector2D operator * (double offset) const { return { this->X * offset, this->Y * offset }; }
	FVector2D operator / (double offset) const { return { this->X / offset, this->Y / offset }; }

	FVector2D& operator *= (const double other) { this->X *= other; this->Y *= other; return *this; }
	FVector2D& operator /= (const double other) { this->X /= other; this->Y /= other; return *this; }

	FVector2D& operator = (const FVector2D& other) { this->X = other.X; this->Y = other.Y; return *this; }
	FVector2D& operator += (const FVector2D& other) { this->X += other.X; this->Y += other.Y; return *this; }
	FVector2D& operator -= (const FVector2D& other) { this->X -= other.X; this->Y -= other.Y; return *this; }
	FVector2D& operator *= (const FVector2D& other) { this->X *= other.X; this->Y *= other.Y; return *this; }
	FVector2D& operator /= (const FVector2D& other) { this->X /= other.X; this->Y /= other.Y; return *this; }

	operator bool() { return bool(this->X || this->Y); }
	friend bool operator == (const FVector2D& A, const FVector2D& B) { return A.X == B.X && A.Y == A.Y; }
	friend bool operator != (const FVector2D& A, const FVector2D& B) { return !(A == B); }

	double X, Y;
};

struct s_usercmd
{
	uintptr_t pVft;                // 0x00
	int32_t   m_iCmdNumber;        // 0x04
	int32_t   m_iTickCount;        // 0x08
	vector3 m_vecViewAngles;        // 0x0C
	vector3 m_vecAimDirection;      // 0x18
	float     m_flForwardmove;     // 0x24
	float     m_flSidemove;        // 0x28
	float     m_flUpmove;          // 0x2C
	int32_t   m_iButtons;          // 0x30
	uint8_t   m_bImpulse;          // 0x34
	uint8_t   Pad1[3];
	int32_t   m_iWeaponSelect;     // 0x38
	int32_t   m_iWeaponSubtype;    // 0x3C
	int32_t   m_iRandomSeed;       // 0x40
	int16_t   m_siMouseDx;         // 0x44
	int16_t   m_siMouseDy;         // 0x46
	bool      m_bHasBeenPredicted; // 0x48
	uint8_t   Pad2[27];
}; s_usercmd* g_pusercmd = nullptr;

enum cmd_buttons {
	in_attack = (1 << 0),
	in_jump = (1 << 1),
	in_duck = (1 << 2),
	in_forward = (1 << 3),
	in_back = (1 << 4),
	in_use = (1 << 5),
	in_cancel = (1 << 6),
	in_left = (1 << 7),
	in_right = (1 << 8),
	in_moveleft = (1 << 9),
	in_moveright = (1 << 10),
	in_attack2 = (1 << 11),
	in_run = (1 << 12),
	in_reload = (1 << 13),
	in_alt1 = (1 << 14),
	in_alt2 = (1 << 15),
	in_score = (1 << 16),
	in_speed = (1 << 17),
	in_walk = (1 << 18),
	in_zoom = (1 << 19),
	in_weapon1 = (1 << 20),
	in_weapon2 = (1 << 21),
	in_bullrush = (1 << 22),
	in_grenade1 = (1 << 23),
	in_grenade2 = (1 << 24),
	in_attack3 = (1 << 25)
};

struct s_globalvars {
	/*0x00*/double realtime;
	/*0x08*/int32_t framecount;
	/*0x0c*/float absoluteframetime;
	/*0x10*/float curtime;
	/*0x14*/float curtime2;
	/*0x18*/float curtime3;
	/*0x1c*/float curtime4;
	/*0x20*/float frametime;
	/*0x24*/float curtime5;
	/*0x28*/float curtime6;
	/*0x2c*/float zero;
	/*0x30*/float frametime2;
	/*0x34*/int32_t maxClients;
	/*0x38*/int32_t unk38;
	/*0x3c*/int32_t unk3C;
	/*0x40*/int32_t tickcount;
	/*0x44*/float interval_per_tick;
	/*0x48*/float interpolation_amount;
} g_pglobalvars;


struct s_matrix
{
	float matrix[16];
};

__forceinline s_matrix get_view_matrix() {
	auto view_render = ctx->read<uintptr_t>(ctx->m_base_address + off::viewRender);
	if (!view_render)
		return s_matrix{};

	auto pview_matrix = ctx->read<uintptr_t>(view_render + off::viewMatrix);
	if (pview_matrix != 0) {
		return ctx->read<s_matrix>(pview_matrix);
	}
	return s_matrix{};
}

vector3 world_to_screen(const struct vector3 pos) {
	vector3 to = vector3();
	auto m_vmatrix = get_view_matrix().matrix;

	float w = m_vmatrix[12] * pos.x + m_vmatrix[13] * pos.y + m_vmatrix[14] * pos.z + m_vmatrix[15];

	if (w < 0.01f) return vector3();

	to.x = m_vmatrix[0] * pos.x + m_vmatrix[1] * pos.y + m_vmatrix[2] * pos.z + m_vmatrix[3];
	to.y = m_vmatrix[4] * pos.x + m_vmatrix[5] * pos.y + m_vmatrix[6] * pos.z + m_vmatrix[7];

	float invw = 1.0f / w;
	to.x *= invw;
	to.y *= invw;

	float x = Width / 2;
	float y = Height / 2;

	x += 0.5f * to.x * Width + 0.5f;
	y -= 0.5f * to.y * Height + 0.5f;

	to.x = x;
	to.y = y;
	to.z = 0;

	return to;
}

enum weapon_ids
{
	MELEE = 18,

	SENTINEL = 1,
	CHARGE_RIFLE = 86,
	LONGBOW = 88,

	RE_45 = 85,
	P2020 = 101,
	R301 = 0,
	R99 = 100,
	ALTERNATOR = 84,

	CAR_MP = 107,
	RAMPAGE = 14,
	_30_30 = 106,
	WINGMAN = 104,
	PROWLER = 98,
	HEMLOK = 93,
	FLATLINE = 91,

	TRIPLE_TAKE = 103,
	DEVOTION = 87,
	HAVOC = 89,
	L_STAR = 95,

	MOSAMBIK = 97,
	PEACEKEEPER = 99,
	EVA_8_AUTO = 90,
	MASTIFF = 96,

	BOCEK = 2,

	KRABER = 94,
	G7_SCOUT = 92,
	VOLT = 105,
	SPITFIRE = 102
};

enum item_rarity { HEIRLOOM, LEGENDARY, EPIC, RARE, COMMON };

struct c_props {
	std::string item_name;
	item_rarity rarity;
};

std::map<uint32_t, c_props> item_map = {
	{ 1, { "Kraber", item_rarity::HEIRLOOM }},
	{ 2, { "Mastiff", item_rarity::COMMON }},
	{ 6, { "Mastiff Gold", item_rarity::LEGENDARY }},
	{ 7, { "LStar", item_rarity::COMMON }},
	{ 11, { "LStar Gold", item_rarity::LEGENDARY }},
	{ 12, { "Havoc", item_rarity::COMMON }},
	{ 16, { "Havoc Gold", item_rarity::LEGENDARY }},
	{ 17, { "Devotion", item_rarity::COMMON }},
	{ 21, { "Devotion Gold", item_rarity::LEGENDARY }},
	{ 22, { "Triple Take", item_rarity::COMMON }},
	{ 26, { "Triple Take Gold", item_rarity::LEGENDARY }},
	{ 27, { "Flatline", item_rarity::COMMON }},
	{ 31, { "Flatline Gold", item_rarity::LEGENDARY }},
	{ 32, { "Hemlock", item_rarity::COMMON }},
	{ 36, { "Hemlock Gold", item_rarity::LEGENDARY }},
	{ 37, { "G7 Scout", item_rarity::HEIRLOOM }},
	{ 41, { "G7 Scout Gold", item_rarity::LEGENDARY }},
	{ 42, { "Alternator", item_rarity::COMMON }},
	{ 46, { "Alternator", item_rarity::COMMON }},
	{ 47, { "R99", item_rarity::COMMON }},
	{ 51, { "R99 Gold", item_rarity::LEGENDARY }},
	{ 52, { "Prowler", item_rarity::COMMON }},
	{ 56, { "Prowler Gold", item_rarity::LEGENDARY }},
	{ 57, { "Volt", item_rarity::LEGENDARY }},
	{ 58, { "Longbow", item_rarity::COMMON }},
	{ 62, { "Longbow Gold", item_rarity::LEGENDARY }},
	{ 63, { "Charge Rifle", item_rarity::COMMON }},
	{ 67, { "Charge Rifle Gold", item_rarity::LEGENDARY }},
	{ 68, { "Spitfire", item_rarity::HEIRLOOM }},
	{ 73, { "R301", item_rarity::COMMON }},
	{ 69, { "R301 Gold", item_rarity::LEGENDARY }},
	{ 78, { "Eva-8 Auto", item_rarity::COMMON }},
	{ 74, { "Eva-8 Auto Gold", item_rarity::LEGENDARY }},
	{ 83, { "Peacekeeper", item_rarity::COMMON }},
	{ 79, { "Peacekeeper Gold", item_rarity::LEGENDARY }},
	{ 88, { "Mozambique", item_rarity::COMMON }},
	{ 84, { "Mozambique Gold", item_rarity::LEGENDARY }},
	{ 89, { "Wingman", item_rarity::COMMON }},
	{ 83, { "Wingman Gold", item_rarity::LEGENDARY }},
	{ 98, { "P2020", item_rarity::COMMON }},
	{ 94, { "P2020 Gold", item_rarity::LEGENDARY }},
	{ 103, { "RE45", item_rarity::COMMON }},
	{ 99, { "RE45 Gold", item_rarity::LEGENDARY }},
	{ 108, { "Sentinel", item_rarity::COMMON }},
	{ 104, { "Sentinel Gold", item_rarity::LEGENDARY }},
	{ 113, { "Bocek Bow", item_rarity::COMMON }},
	{ 109, { "Bocek Bow Gold", item_rarity::LEGENDARY }},
	{ 118, { "Repeater", item_rarity::COMMON }},
	{ 114, { "Repeater Gold", item_rarity::LEGENDARY }},
	{ 124, { "Light Ammo", item_rarity::COMMON }},
	{ 125, { "Energy Ammo", item_rarity::COMMON }},
	{ 126, { "Shotgun Ammo", item_rarity::COMMON }},
	{ 127, { "Heavy Ammo", item_rarity::COMMON }},
	{ 128, { "Sniper Ammo", item_rarity::COMMON }},
	{ 129, { "Arrow", item_rarity::COMMON }},
	{ 130, { "Rampage", item_rarity::COMMON }},
	{ 131, { "Rampage Gold", item_rarity::LEGENDARY }},
	{ 132, { "Car SMG", item_rarity::COMMON }},
	{ 133, { "Car SMG Gold", item_rarity::LEGENDARY }},
	{ 164, { "Ultimate Accelerant", item_rarity::RARE }},
	{ 165, { "Pheonix Kit", item_rarity::EPIC }},
	{ 166, { "Med Kit", item_rarity::RARE }},
	{ 167, { "Syringe", item_rarity::COMMON }},
	{ 168, { "Shield Battery", item_rarity::RARE }},
	{ 169, { "Shield Cell", item_rarity::COMMON }},
	{ 170, { "Helmet[L1]", item_rarity::COMMON }},
	{ 171, { "Helmet[L2]", item_rarity::RARE }},
	{ 172, { "Helmet[L3]", item_rarity::EPIC }},
	{ 173, { "Helmet[L4]", item_rarity::LEGENDARY }},
	{ 174, { "Body Armor[L1]", item_rarity::COMMON }},
	{ 175, { "Body Armor[L2]", item_rarity::RARE }},
	{ 176, { "Body Armor[L3]", item_rarity::EPIC }},
	{ 177, { "Body Armor[L4]", item_rarity::LEGENDARY }},
	{ 178, { "Body Armor[L5]", item_rarity::HEIRLOOM }},
	{ 179, { "Evo Body Armor[L1]", item_rarity::COMMON }},
	{ 180, { "Evo Body Armor[L2]", item_rarity::RARE }},
	{ 181, { "Evo Body Armor[L3]", item_rarity::EPIC }},
	{ 182, { "Evo Body Armor[L5]", item_rarity::HEIRLOOM }},
	{ 237, { "Heat Shield", item_rarity::HEIRLOOM }},
	{ 184, { "Knockdown Shield[L1]", item_rarity::COMMON }},
	{ 185, { "Knockdown Shield[L2]", item_rarity::RARE }},
	{ 186, { "Knockdown Shield[L3]", item_rarity::EPIC }},
	{ 187, { "Knockdown Shield[L4]", item_rarity::LEGENDARY }},
	{ 188, { "Backpack[L1]", item_rarity::COMMON }},
	{ 189, { "Backpack[L2]", item_rarity::RARE }},
	{ 190, { "Backpack[L3]", item_rarity::EPIC }},
	{ 191, { "Backpack[L4]", item_rarity::LEGENDARY }},
	{ 192, { "Thermite Grenade", item_rarity::COMMON }},
	{ 193, { "Frag Grenade", item_rarity::COMMON }},
	{ 194, { "Arc Star", item_rarity::COMMON }},
	{ 195, { "1x HCOG 'Classic'", item_rarity::COMMON }},
	{ 196, { "2x HCOG 'Bruiser'", item_rarity::RARE }},
	{ 197, { "1x Holo", item_rarity::COMMON }},
	{ 198, { "1x-2x Variable Holo", item_rarity::RARE }},
	{ 199, { "1x Digital Threat", item_rarity::LEGENDARY }},
	{ 200, { "3x HCOG 'Ranger'", item_rarity::EPIC }},
	{ 201, { "2x-4x Variable AOG", item_rarity::EPIC }},
	{ 202, { "6x Sniper", item_rarity::RARE }},
	{ 203, { "4x-8x Variable Sniper", item_rarity::EPIC }},
	{ 204, { "4x-10x Digital Sniper Threat", item_rarity::LEGENDARY }},
	{ 205, { "Barrel Stabilizer", item_rarity::COMMON }},
	{ 206, { "Barrel Stabilizer", item_rarity::RARE }},
	{ 207, { "Barrel Stabilizer", item_rarity::EPIC }},
	{ 209, { "Light Magazine[L1]", item_rarity::COMMON }},
	{ 210, { "Light Magazine[L2]", item_rarity::RARE }},
	{ 211, { "Light Magazine[L3]", item_rarity::EPIC }},
	{ 212, { "Light Magazine[L4]", item_rarity::LEGENDARY }},
	{ 213, { "Heavy Magazine[L1]", item_rarity::COMMON }},
	{ 214, { "Heavy Magazine[L2]", item_rarity::RARE }},
	{ 215, { "Heavy Magazine[L3]", item_rarity::EPIC }},
	{ 216, { "Heavy Magazine[L4]", item_rarity::LEGENDARY }},
	{ 217, { "Energy Magazine[L1]", item_rarity::COMMON }},
	{ 218, { "Energy Magazine[L2]", item_rarity::RARE }},
	{ 219, { "Energy Magazine[L3]", item_rarity::EPIC }},
	{ 220, { "Energy Magazine[L4]", item_rarity::LEGENDARY }},
	{ 221, { "Sniper Magazine[L1]", item_rarity::COMMON }},
	{ 222, { "Sniper Magazine[L2]", item_rarity::RARE }},
	{ 223, { "Sniper Magazine[L3]", item_rarity::EPIC }},
	{ 224, { "Sniper Magazine[L4]", item_rarity::LEGENDARY }},
	{ 225, { "Shotgun Bolt[L1]", item_rarity::COMMON }},
	{ 226, { "Shotgun Bolt[L2]", item_rarity::RARE }},
	{ 227, { "Shotgun Bolt[L3]", item_rarity::EPIC }},
	{ 228, { "Standard Stock[L1]", item_rarity::COMMON }},
	{ 229, { "Standard Stock[L2]", item_rarity::RARE }},
	{ 230, { "Standard Stock[L3]", item_rarity::EPIC }},
	{ 231, { "Sniper Stock[L1]", item_rarity::COMMON }},
	{ 232, { "Sniper Stock[L2]", item_rarity::RARE }},
	{ 233, { "Sniper Stock[L3]", item_rarity::EPIC }},
	{ 234, { "Turbocharger", item_rarity::LEGENDARY }},
	{ 238, { "Hammer Point", item_rarity::EPIC }},
	{ 237, { "Skull Piercer", item_rarity::LEGENDARY } },
	{ 245, { "Deadeye's Tempo", item_rarity::EPIC } },
	{ 246, { "Quickdraw Holster", item_rarity::EPIC } },
	{ 247, { "Shatter Caps", item_rarity::EPIC }},
	{ 248, { "Kinetic Feeder", item_rarity::EPIC } },
	{ 249, { "Boosted Loader", item_rarity::LEGENDARY }},
	{ 245, { "Mobile Respawn Beacon", item_rarity::RARE }},
	{ 246, { "Vault Key", item_rarity::HEIRLOOM }},
	{ 248, { "Treasure Pack", item_rarity::HEIRLOOM }},
	{ 249, { "Survival Doubler", item_rarity::HEIRLOOM }},
	{ 250, { "Survival Quadrupler", item_rarity::HEIRLOOM }},
	{ 251, { "Heat Shield", item_rarity::RARE }},
	{ 252, { "Mobile Respawn Beacon 2", item_rarity::RARE }},
	{ 253, { "Treasure Pack", item_rarity::HEIRLOOM }},
	{ 254, { "Vault Key", item_rarity::HEIRLOOM }}
};

std::map<uint32_t, std::string> weapon_map = {
	{ 1, { "kraber", item_rarity::HEIRLOOM }},
};

class c_weapon {
public:
	c_weapon() = default;
	c_weapon(uintptr_t pointer) {
		this->address = pointer;
	}

	inline bool valid() {
		return this->address != 0;
	}

	inline int weapon_id() {
		if (!this->address) return -1;
		return ctx->read<int>(this->address + off::weaponHandle);
	}

	inline int ammo_in_clip() {
		if (!this->address) return -1;
		return read<int>(this->address + off::weaponAmmo);
	}

	inline float bullet_speed() {
		if (!this->address) return 0.0f;
		return ctx->read<float>(this->address + off::projectileSpeed);
	}

	inline float bullet_gravity() {
		if (!this->address) return 0.0f;
		return ctx->read<float>(this->address + off::projectileScale);
	}

	
	inline std::string get_name() {
		if (!this->address) return ("none");
		for (const auto& [key, value] : weapon_map) {
			if (this->weapon_id() == key) {
				return value;
			}
		}
	}
private:
	uintptr_t address;
};

struct s_glow
{
	int8_t general, border, border_size, transparency;
};

struct s_visible_time
{
	float last_time_visible[100];
	bool last_visibility_state[100];
	uintptr_t last_check_time[100];
} inline last_visible;

struct s_box {
	s_box() = default;
	s_box(int x, int y, int w, int h) {
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
	}
	int x, y, w, h;
};

class c_player {

public:
	c_player() = default;
	c_player(DWORD_PTR pointer) {
		this->address = pointer;
		this->health = this->i_health();
		this->shield = this->i_shield();
		this->team = this->i_team();
		this->origin = this->vec_origin();
		this->bleed_out_state = ctx->read<int>(pointer + off::bleedoutState);
	}

	inline bool operator!=(const c_player& player) const {
		return (this->address != player.address);
	}

	inline uintptr_t get_address() {
		return this->address;
	}

	inline bool valid() {
		if (this->vec_origin() != vector3(0,0,0) && this->address != NULL && this->alive())
			return true;
		return false;
	}

	inline bool b_downed() {
		if (this->bleed_out_state < 1) {
			return true;
		}
		return false;
	}
	inline bool alive() {
		return read<int>(this->address + off::bleedoutState) == 0 && read<int>(this->address + off::lifeState) == 0;
	}
	int GetWeaponIndex()
	{
		uint64_t primary_weapons_latest = ctx->read<uint64_t>(this->address + off::weaponHandle) & 0xFFFF;
		uint64_t primary_weapons_list = ctx->read<uint64_t>(ctx->m_base_address + off::entityList + (primary_weapons_latest * 0x20));
		int weapon_index = ctx->read<int>(primary_weapons_list + off::weaponIndex); // weapon name0x1574 0x0769b4b8
		return weapon_index;
	}

	inline c_weapon weapon() {
		auto weapon_pointer = ctx->read<uintptr_t>(this->address + off::weaponHandle);
		weapon_pointer &= 0xffff;
		auto weapon_handle = ctx->read<uintptr_t>(ctx->m_base_address + off::entityList + (weapon_pointer << 5));
		return c_weapon(weapon_handle);
	}

	inline std::string s_name() {
	

		auto index = ctx->read<uintptr_t>(this->address + off::nameIndex);

		uintptr_t NameOffset = ctx->read<uintptr_t>(ctx->m_base_address + off::nameList + ((index - 1) * 24)); //NameList=0xd350450
		if (!NameOffset)
			return "AI";
		std::string PlayerName = readstring(NameOffset);
		return PlayerName;
	}

	std::string GetOperator()
	{
		if (!this->get_address()) return "";
		uintptr_t pMode_Name = read < uintptr_t >(this->get_address() + 0x0030);
		if (!pMode_Name) {
			return "";
		}
		auto ModelName = readstring(pMode_Name);

		static std::unordered_map<std::string, std::string> ModelNameMap = { {"dummie", "Dummie"}, {"ash", "Ash"}, {"ballistic", "Ballistic"}, {"bangalore", "Bangalore"}, {"bloodhound", "Bloodhound"}, {"catalyst", "Catalyst"}, {"caustic", "Caustic"}, {"conduit", "Conduit"}, {"crypto", "Crypto"}, {"fuse", "Fuse"}, {"gibraltar", "Gibraltar"}, {"horizon", "Horizon"}, {"nova", "Horizon"}, {"holo", "Mirage"}, {"mirage", "Mirage"}, {"lifeline", "Lifeline"}, {"loba", "Loba"}, {"madmaggie", "Mad Maggie"}, {"newcastle", "Newcastle"}, {"octane", "Octane"}, {"pathfinder", "Pathfinder"}, {"rampart", "Rampart"}, {"revenant", "Revenant"}, {"seer", "Seer"}, {"stim", "Octane"}, {"valkyrie", "Valkyrie"}, {"vantage", "Vantage"}, {"wattson", "Wattson"}, {"wraith", "Wraith"}, {"alter", "Alter"}, };

		std::string replacedName = ModelName;
		for (auto& entry : ModelNameMap) {
			if (ModelName.find(entry.first) != std::string::npos) {
				replacedName = entry.second;
				break;
			}
		}

		return replacedName;
	}

	inline int i_health() {
		this->health = ctx->read<int>(this->address + off::health);
		return this->health;
	}

	inline bool on_ground() {
		this->flags = ctx->read<uint32_t>(this->address + off::flags);
		return (this->flags & 0x1) != 0;
	}

	inline bool is_ducking() {
		this->flags = ctx->read<uint32_t>(this->address + off::flags);
		return (this->flags & 0x2) != 0;
	}

	inline int i_team() {
		this->team = ctx->read<int>(this->address + off::teamNumber);
		return this->team;
	}

	inline int i_shield() {
		this->shield = ctx->read<int>(this->address + off::shield);
		return this->shield;
	}

	inline int i_max_shield() {
		this->max_shield = ctx->read<int>(this->address + off::maxHealth);
		return this->max_shield;
	}

	inline int i_shield_type() {
		this->shield_type = ctx->read<int>(this->address + off::armorType);
		return this->shield_type;
	}
	

	inline int i_max_health() {
		this->max_health = i_health() + i_shield();
		return this->max_health;
	}


	inline vector3 mins() {// OFF_Collision_m_vecMins
		return ctx->read<vector3>(this->address + off::collisionVecMins);
	}

	inline vector3 maxs() {
		return ctx->read<vector3>(this->address + off::collisionVecMaxs);
	}

	inline int distance() {
		auto local_player = ctx->read<uintptr_t>(ctx->m_base_address + off::localPlayer);
		auto local_dist = ctx->read<vector3>(local_player + off::localOrigin);

		return (int)local_dist.distance(this->vec_origin());
	}

	inline vector3 vec_origin() const {
		return ctx->read<vector3>(this->address + off::localOrigin);
	}
	inline vector3 r_view_angles() {
		return ctx->read<vector3>(this->address + off::viewAngles);
	}

	inline vector3 camera_position() {
		return ctx->read<vector3>(this->address + off::cameraOrigin);
	}

	void SetViewAngles(Vector2 Angles)
	{
		ctx->write<Vector2>((uintptr_t)this + off::viewAngles, Angles);
	}

	inline vector3 bone_position(uint32_t id) {
		uintptr_t bone_array = ctx->read<uintptr_t>(this->address + off::bones);
		this->origin = this->vec_origin();

		vector3 bone = vector3();
		bone.x = ctx->read<float>(bone_array + 0xCC + (id * 0x30)) + this->origin.x;
		bone.y = ctx->read<float>(bone_array + 0xDC + (id * 0x30)) + this->origin.y;
		bone.z = ctx->read<float>(bone_array + 0xEC + (id * 0x30)) + this->origin.z;
		return bone;
	}


	inline bool visible(int index) {
		if (get_ms() >= (last_visible.last_check_time[index] + 10)) {
			float s_visible_time = ctx->read<float>(this->address + off::lastVisibleTime);
			last_visible.last_visibility_state[index] = s_visible_time > last_visible.last_time_visible[index] || s_visible_time < 0.f && last_visible.last_time_visible[index] > 0.f;
			last_visible.last_time_visible[index] = s_visible_time;
			last_visible.last_check_time[index] = get_ms();
		}
		return last_visible.last_visibility_state[index];
	}

	inline vector3 punch_angles() {
		return ctx->read<vector3>(this->address + off::punchAngles);
	}

	inline void view_angles(vector3 angles) {
		write<vector3>(this->address + off::viewAngles, angles);
	}

	inline vector3 velocity() const {
		return ctx->read<vector3>(this->address + off::absVelocity);
	}

private:
	DWORD_PTR address;
	int health;
	int shield;
	int max_shield;
	int shield_type;

	int max_health;
	int team;
	int bleed_out_state;
	int diving;
	vector3 origin;
	uint32_t flags;
};

__forceinline std::string class_signifier(DWORD_PTR entity) {
	auto class_pointer = ctx->read<uintptr_t>(entity + off::signifierName);
	
	return readstring(class_pointer);
}

inline std::string get_weapon_name(uint64_t playerEntity)
{
	uint64_t primary_weapons_latest = read<uint64_t>(playerEntity + off::weaponHandle) & 0xFFFF;
	uint64_t primary_weapons_list = read<uint64_t>(ctx->m_base_address + off::entityList + (primary_weapons_latest * 0x20));

	int weapon_index = read<int>(primary_weapons_list + off::weaponIndex);

	static const std::unordered_map<int, std::string> weapon_map = {
		{WeaponIDs::R301, "R301"},
		{WeaponIDs::BOCEK, "Bocek"},
		{WeaponIDs::HAVOC, "Havoc"},
		{WeaponIDs::DEVOTION, "Devotion"},
		{WeaponIDs::LSTAR, "L-Star"},
		{WeaponIDs::TRIPLE_TAKE, "Triple Take"},
		{WeaponIDs::VOLT, "Volt"},
		{WeaponIDs::NEMESIS, "Nemesis"},
		{WeaponIDs::FLATLINE, "Flatline"},
		{WeaponIDs::HEMLOCK, "Hemlock"},
		{WeaponIDs::REPEATER_3030, "30-30 Repeater"},
		{WeaponIDs::RAMPAGE, "Rampage"},
		{WeaponIDs::CAR, "C.A.R"},
		{WeaponIDs::P2020, "P2020"},
		{WeaponIDs::RE45, "RE45"},
		{WeaponIDs::ALTERNATOR, "Alternator"},
		{WeaponIDs::R99, "R99"},
		{WeaponIDs::SPITFIRE, "Spitfire"},
		{WeaponIDs::G7_SCOUT, "G7 Scout"},
		{WeaponIDs::MOZAMBIQUE, "Mozambique"},
		{WeaponIDs::EVA8, "EVA-8 Auto"},
		{WeaponIDs::PEACEKEEPER, "Peacekeeper"},
		{WeaponIDs::SENTINEL, "Sentinel"},
		{WeaponIDs::CHARGE_RIFLE, "Charge Rifle"},
		{WeaponIDs::LONGBOW, "Longbow"},
		{WeaponIDs::MASTIFF, "Mastiff"},
		{WeaponIDs::PROWLER, "Prowler"},
		{WeaponIDs::WINGMAN, "Wingman"},
		{WeaponIDs::KRABER, "Kraber"},
		{WeaponIDs::KNIFE, "Knife"}
	};

	auto it = weapon_map.find(weapon_index);
	if (it != weapon_map.end()) {
		return it->second;
	}

	return "None";
}

#pragma once

enum class BlendMode
{
	Alpha,
	Overlay,
	Lighten,
	Multply,
	Add,
	Addition,
	Darken,
	MAX
};

enum class UPDATE_ORDER
{
	NORMAL,
	CAMERA
};


enum class COLLISION_ORDER
{
	Background,
	Background_Object,
	Terrain,
	NPC,
	Potal,
	Wall,
	Tablet,
	//Elderbug,
	Knight,
	Wall_Actor,
	Prompt,
	Object,
	NotAttack_Object,
	Bench,
	Geo,
	Knight_Slash,
	Knight_Shadow,
	Knight_Shadow_Slash,
	Monster,
	Monster_Attack,
	FrontObject,
	TileMap,
	UI
};

enum class RENDERORDER
{
	Background,
	Background_Object,
	Terrain,

	Knight,
	Monster,
	Knight_Shadow,
	FrontObject,
	UI

};

//��������. ���ڰ� ���� ���� �ڷΰ���
enum class Z_ORDER
{
	UI_HeartPeice,

	UI_Pointer,

	UI_Border,

	UI,
	
	UI_BackBoard,

	TileMap,

	FrontObject ,

	Terrain ,

	Effect ,
	Knight_Shadow_Slash,

	Knight_Shadow,

	Knight_Slash,

	Geo,

	Knight,
	Monster,

	Back_Effect,

	NPC,

	Object,

	Small_Light = 30,

	Light,

	Dount_Light,

	Side_Dark,

	Back_Object,


	Background_Object = 40 ,

	Back_Back_Object = 100,

	Background = 200,


};

//���� ������
//0�� ��� ����? ��Ȳ�� ���� �ٱ� �� ����.

enum class PAGE_TYPE
{
	Charm,
	Inventory,
	Map,
};

// ������ �ε��� : ���� �������� 0���� �����Ѵ�.
// ���� ���� +1 �̾��ٰ� 0���� �ȴٸ� ���������� �̵��ȴ�.
// ���� ���� -1 �̾��ٰ� 0���� �ȴٸ� �������� �̵��ȴ�.
enum class CURRENT_PAGE_INDEX
{
	MIN = -2,
	SincePage = -1,
	CurrentPage = 0,
	NextPage = 1,
	MAX = 2
};

enum class CHAR_PAGE_ACTOR
{
	RightArrow = 50,
	LeftArrow = 51,
};

enum class MAP_PAGE_ACTOR
{
	RightArrow = 50,
	LeftArrow = 51,
};

enum class MONSTER_BOOK_PAGE_ACTOR
{
	RightArrow = 1,
	LeftArrow,
};

enum class MAP_LIST
{
	MAP_MIN = -1,
	DIRTMOUTH,
	CORSSROAD,
	MAP_MAX
};

enum class ITEM_LIST
{
	NONE = -2,
	SPELL_MIN = -1,
	Heart_Piece = 0,
	Soul_Piece,
	Dream_Nail,
	Nail,
	Spell_core,
	Spell_Fireball,
	Spell_Scream,
	Item_Geo,
	SPELL_MAX = 8,

	NORMAL_MIN = 9,

	Tram_Pass = 10,
	Lumafly_Lantern,
	Mapand_Quill,
	Collectors_Map,
	Hunters_Journal,
	Hunters_Mark,
	Delicate_Flower,
	Godtuner,
	Mask_Shard,
	Vessel_Fragment,
	Salubras_Blessing,
	Pale_Ore,

	NORMAL_MAX,

	Map_and_Quill,
	Rancid_Egg,
	Shade_Cloak,
	Witches_eye,
	Storeroom_key,
	Quill_combined,
	Monarch_Wings,
	Mender_key, 
	Acid_armour,
	Crystal_heart, 
	Rancid_egg,
	Area_map, 
	Treasure_map, 
	Mantis_Cloak,

	SELL_MIN = 39,
	Wanderers_Journal = 40,
	hallownest_seal,
	Kings_idol,
	arcane_egg,
	SELL_MAX = 44,
};


enum class ITEM_TYPE
{
	Spell_Item,
	Normal_Item,
	Sell_Item
};

enum class SHOP_ITEM
{
	Crosslaod_Map,

	Rancid_Egg,
	Acid_armour,

	MaskPiece,		// ��������
	Wayward_Compass, //��ħ��
	Mark_of_Pride,	//�縶��
	Dreamshield,	//��ȯ����
};

enum class SlideItemIndex
{
	Min = -1,
	First,
	Second,
	Third,
	Fourth,
	Fifth,
	Sixth
};

enum class NPC_TYPE
{
	Normal,
	Shop
};

enum class CHARM_SLOT
{
	None = -1 ,
	Wayward_Compass,	
	Gathering_Swarm,	
	Stalwart_Shell,		
	Soul_Catcher,		
	Shaman_Stone,		
	Soul_Eater,			
	Dashmaster,			
	Thorns_of_Agony,	
	Fury_of_the_Fallen,	
	Fragile_Heart,		
	Fragile_Greed		
	Fragile_Strength,	
	Spell_Twister,		
	Steady_Body,		
	Heavy_Blow,			
	Quick_Slash,		
	Longnail,			
	Mark_of_Pride,		
	Baldur_Shell,		
	Flukenest,			
	Defenders_Crest,	
	Glowing_Womb,		
	Quick_Focus,		
	Deep_Focus,			
	Lifeblood_Heart,	
	Lifeblood_Core,			
	Jonis_Blessing,			
	Grubsong,				
	Grubberflys_Elegy,		
	Hiveblood,				
	Spore_Shroom,			
	Sharp_Shadow,			
	Shape_of_Unn,			
	Nailmasters_Glory,		
	Dream_Wielder,			
	Kingsoul,				
							
	Sprintmaster,			
	Weaversong,				
	Dreamshield,			
	Grimmchild,				
							

};
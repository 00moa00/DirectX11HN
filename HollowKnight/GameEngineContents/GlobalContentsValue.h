#pragma once

enum class OBJECTORDER
{
	Background,
	Background_Object,
	Terrain,
	Knight,
	Geo,
	Knight_Slash,
	Knight_Shadow,
	Knight_Shadow_Slash,
	Monster,
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
	UI_Border,

	UI,

	TileMap,

	FrontObject,

	Terrain,

	Monster,

	Knight_Shadow_Slash,

	Knight_Shadow,

	Knight_Slash,

	Geo,

	Knight,

	Small_Light,

	Light,

	Dount_Light,

	Side_Dark,



	Background_Object ,

	Background = 200,


};
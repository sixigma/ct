#include "stdafx.h"
#include "etcItem.h"

HRESULT etcItem::init(string _name)
{
	itemName = _name;
	itemlist();
	return S_OK;
}

void etcItem::release()
{
}

void etcItem::update()
{
}

void etcItem::render()
{
}

void etcItem::itemlist()
{
	if (itemName == "Pendant")
	{
		itemCategory = Event;
		//퀘스트용 팬던트
		itemTip = "give to Marle";
	}
	if (itemName == "SpecialMeal")
	{
		// 이벤트용 피 다채워주는 음식
		itemCategory = Event;
	}

}

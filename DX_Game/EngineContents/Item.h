#pragma once

//	Ό³Έν:
class Item
{
public:
	Item();
	virtual ~Item();
	Item(const Item& _Other) = delete;
	Item(Item&& _Other) noexcept = delete;
	Item& operator=(const Item& _Other) = delete;
	Item& operator=(Item&& _Other) noexcept = delete;

protected:

private:

};


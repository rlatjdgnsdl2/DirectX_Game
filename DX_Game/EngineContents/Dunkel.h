#pragma once

//	Ό³Έν:
class Dunkel
{
public:
	Dunkel();
	virtual ~Dunkel();
	Dunkel(const Dunkel& _Other) = delete;
	Dunkel(Dunkel&& _Other) noexcept = delete;
	Dunkel& operator=(const Dunkel& _Other) = delete;
	Dunkel& operator=(Dunkel&& _Other) noexcept = delete;

protected:

private:

};


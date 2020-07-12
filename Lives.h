#pragma once
#include <random>
class Lives
{
public:
	bool is_close = false;
	int x = 1110;
	int y = 0;
	void draw();
	Lives(const int y);
};
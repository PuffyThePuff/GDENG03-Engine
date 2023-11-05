#pragma once
#include <string>
#include "imgui.h"

typedef std::string String;
class UIManager;

class AUIScreen
{
protected:
	typedef std::string String;

	AUIScreen(String name);
	~AUIScreen();

	String getName();
	virtual void drawUI() = 0;

	String name;

	friend class UIManager;
};


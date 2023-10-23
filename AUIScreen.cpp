#include "AUIScreen.h"

AUIScreen::AUIScreen(String name): name(this->name)
{
}

AUIScreen::~AUIScreen()
{
}

String AUIScreen::getName()
{
	return this->name;
}
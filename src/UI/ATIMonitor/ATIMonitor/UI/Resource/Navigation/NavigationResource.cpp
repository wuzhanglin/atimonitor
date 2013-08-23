#include "UIResource.h"

UIResource::UIResource()
{

}

UIResource::~UIResource()
{

}

UIResource* 
UIResource::get()
{
	static UIResource theOnlyOne;
	return &theOnlyOne;
}
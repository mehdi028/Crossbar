#include "InputLayout.h"

void InputLayout::Bind()
{
	GetpContext(gfx)->IASetInputLayout(pinputLayout.Get());
}

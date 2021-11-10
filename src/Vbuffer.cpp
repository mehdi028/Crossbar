#include "Vbuffer.h"
#include "..\Headers\Vbuffer.h"

void Vbuffer::Bind()
{
	Bindable::GetpContext(gfx)->IASetVertexBuffers(0u, 1u, pVbuffer.GetAddressOf(),&stride, nullptr);

}

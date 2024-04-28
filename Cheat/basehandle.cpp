#include "stdafx.h"

#include "basehandle.h"


IHandleEntity* CBaseHandle::Get() const
{
	return reinterpret_cast<IHandleEntity*>(g_Interfaces->EntityList->GetClientEntityFromHandle(*this));
}

bool CBaseHandle::operator <(const IHandleEntity* pEntity) const
{
	unsigned long otherIndex = (pEntity) ? pEntity->GetRefEHandle().m_Index : INVALID_EHANDLE_INDEX;
	return m_Index < otherIndex;
}

const CBaseHandle& CBaseHandle::Set(const IHandleEntity* pEntity)
{
	if (pEntity)
	{
		*this = pEntity->GetRefEHandle();
	}
	else
	{
		m_Index = INVALID_EHANDLE_INDEX;
	}

	return *this;
}
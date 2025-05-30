/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        mods/deathmatch/logic/packets/CElementRPCPacket.cpp
 *  PURPOSE:     Lua element RPC packet class
 *
 *  Multi Theft Auto is available from https://www.multitheftauto.com/
 *
 *****************************************************************************/

#include "StdInc.h"
#include "CElementRPCPacket.h"
#include "CElement.h"

bool CElementRPCPacket::Write(NetBitStreamInterface& BitStream) const
{
    // Write the action ID
    BitStream.Write(m_ucActionID);

    // Write the source element.
    BitStream.Write(m_pSourceElement->GetID());

    // Copy each byte from the bitstream we have to this one
    unsigned char ucTemp;
    int           iLength = m_BitStream.GetNumberOfBitsUsed();
    while (iLength > 8)
    {
        m_BitStream.Read(ucTemp);
        BitStream.Write(ucTemp);
        iLength -= 8;
    }
    if (iLength > 0)
    {
        m_BitStream.ReadBits(&ucTemp, iLength);
        BitStream.WriteBits(&ucTemp, iLength);
    }

    m_BitStream.ResetReadPointer();

    return true;
}

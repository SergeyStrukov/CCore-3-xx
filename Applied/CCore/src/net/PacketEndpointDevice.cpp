/* PacketEndpointDevice.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: Applied
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/net/PacketEndpointDevice.h>

namespace CCore {
namespace Net {

/* struct PacketEndpointDevice */

const Unid PacketEndpointDevice::TypeUnid={{0xB19A'C981,0x840D'60C6,0xB325'4F73,0xC3C6'A16D,0x4D20'24DC,0x4BCA'9672,0xEB7C'DA92,0x542A'2939}};

const Unid PacketEndpointDevice::InboundProc::TypeUnid={{0xE62F'AECF,0x5250'DBEE,0x1E57'17AD,0xC19A'9AF0,0x47F5'DD5B,0x1F83'A634,0xAD86'A468,0xC64F'3268}};

const Unid PacketEndpointDevice::ConnectionProc::TypeUnid={{0x794A'E752,0x1A58'A0FB,0x55FA'043A,0xDFE9'1415,0x2103'C2A3,0xDCAA'816B,0xA74C'F3CD,0xDEC1'96C2}};

/* struct PacketMultipointDevice */

const Unid PacketMultipointDevice::TypeUnid={{0x142C'D50C,0xC51E'A7D1,0x904D'1F15,0x37B9'67C4,0x566B'DCAD,0x9441'FD52,0x24C9'5A7B,0x9214'BA79}};

const Unid PacketMultipointDevice::InboundProc::TypeUnid={{0xBDDD'7D76,0x8CD6'4405,0xAF7F'B546,0x52F3'DB11,0xF675'2710,0x23CF'4CBA,0x59CB'8012,0xDFD7'6782}};

const Unid PacketMultipointDevice::ConnectionProc::TypeUnid={{0x3A25'F29E,0x9AEE'AFF5,0x7ED4'4364,0x8E63'59F6,0x4406'CF37,0xBEC4'D696,0xD75F'C7F2,0x17CE'C592}};

/* struct PortManager */

const Unid PortManager::TypeUnid={{0xAD06'337B,0x271A'4893,0x6A05'43A9,0xB2EE'11CA,0xCE02'9641,0x6AB9'32A5,0xC6D6'377E,0x3129'2D92}};

} // namespace Net
} // namespace CCore



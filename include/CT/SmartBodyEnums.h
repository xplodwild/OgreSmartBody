/****************************************************************
 * OgreSmartBody wrapper
 * Copyright (C) 2013 Guillaume Lesniak

 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 ****************************************************************/

#ifndef _CAKAOTWO_SMARTBODYENUMS_H_
#define _CAKAOTWO_SMARTBODYENUMS_H_

namespace CT { namespace SmartBodyEnums {

/**
 * Possible shapes of pawns
 */
enum PawnShape
{
	PAWNSHAPE_NULL,
	PAWNSHAPE_SPHERE,
	PAWNSHAPE_BOX,
	PAWNSHAPE_CAPSULE
};


}; };


#endif // _CAKAOTWO_SMARTBODYENUMS_H_

/***************************************************************************
 *   Copyright (C) 2006 by Adam Luchjenbroers,,,   *
 *   adam@luchjenbroers.com   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef ERRORHANDLING_H
#define ERRORHANDLING_H

#include <string>
 
/** Error is the root class for all error types. */
class Error : public std::exception {
public:
/**
    Provides a pointer to a string object containing a short text description of the error. This object is constructed to be a return variable, and the caller is expected to ensure that it is deleted after use.
	@return A short description of the error as a pointer to a string  
*/
  virtual std::string *toString() = 0;
  virtual ~Error() throw() {} ;
};

#endif


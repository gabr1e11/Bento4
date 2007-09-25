/*****************************************************************
|
|    AP4 - File Copier
|
|    Copyright 2002-2007 Gilles Boccon-Gibod & Julien Boeuf
|
|
|    This file is part of Bento4/AP4 (MP4 Atom Processing Library).
|
|    Unless you have obtained Bento4 under a difference license,
|    this version of Bento4 is Bento4|GPL.
|    Bento4|GPL is free software; you can redistribute it and/or modify
|    it under the terms of the GNU General Public License as published by
|    the Free Software Foundation; either version 2, or (at your option)
|    any later version.
|
|    Bento4|GPL is distributed in the hope that it will be useful,
|    but WITHOUT ANY WARRANTY; without even the implied warranty of
|    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
|    GNU General Public License for more details.
|
|    You should have received a copy of the GNU General Public License
|    along with Bento4|GPL; see the file COPYING.  If not, write to the
|    Free Software Foundation, 59 Temple Place - Suite 330, Boston, MA
|    02111-1307, USA.
|
 ****************************************************************/

/*----------------------------------------------------------------------
|   includes
+---------------------------------------------------------------------*/
#include "Ap4MoovAtom.h"
#include "Ap4FileCopier.h"
#include "Ap4Movie.h"
#include "Ap4File.h"
#include "Ap4FtypAtom.h"

/*----------------------------------------------------------------------
|   AP4_FileCopier::AP4_FileCopier
+---------------------------------------------------------------------*/
AP4_FileCopier::AP4_FileCopier(AP4_File& file) : m_File(file)
{
}

/*----------------------------------------------------------------------
|   AP4_FileCopier::~AP4_FileCopier
+---------------------------------------------------------------------*/
AP4_FileCopier::~AP4_FileCopier()
{
}

/*----------------------------------------------------------------------
|   AP4_FileCopier::Write
+---------------------------------------------------------------------*/
AP4_Result
AP4_FileCopier::Write(AP4_ByteStream& stream)
{
    // get the file type
    AP4_FtypAtom* file_type = m_File.GetFileType();

    // get the movie object
    AP4_Movie* movie = m_File.GetMovie();
    if (movie == NULL) return AP4_SUCCESS;

    // write the ftyp atom
    if (file_type) file_type->Write(stream);

    // write the moov atom
    movie->GetMoovAtom()->Write(stream);

    // write the other atoms
    for (AP4_List<AP4_Atom>::Item* item = m_File.GetOtherAtoms().FirstItem();
         item;
         item = item->GetNext()) {
        AP4_Atom* atom = item->GetData();
        atom->Write(stream);
    }

    return AP4_SUCCESS;
}
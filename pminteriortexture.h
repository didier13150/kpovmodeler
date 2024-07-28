//-*-C++-*-
/*
**************************************************************************
                                 description
                             --------------------
    copyright            : (C) 2003 by Leon Pennington
    email                : leon@leonscape.co.uk
**************************************************************************

**************************************************************************
*                                                                        *
*  This program is free software; you can redistribute it and/or modify  *
*  it under the terms of the GNU General Public License as published by  *
*  the Free Software Foundation; either version 2 of the License, or     *
*  (at your option) any later version.                                   *
*                                                                        *
**************************************************************************/


#ifndef PMINTERIORTEXTURE_H
#define PMINTERIORTEXTURE_H



#include "pmtexturebase.h"

/**
 * Class for povray interior textures
 */
class PMInteriorTexture : public PMTextureBase
{
   typedef PMTextureBase Base;
public:
   /**
    * Creates an PMInteriorTexture
    */
   PMInteriorTexture( PMPart* part );
   /**
    * Copy constructor
    */
   PMInteriorTexture( const PMInteriorTexture& t );
   /**
    * Deletes the object
    */
   virtual ~PMInteriorTexture();

   /** */
   virtual PMObject* copy() const override { return new PMInteriorTexture( *this ); }
   /** */
   virtual QString description() const override;

   /** */
   virtual PMMetaObject* metaObject() const override;
   /** */
   virtual void cleanUp() const override;

   /**
    * Returns a new @ref PMTextureEdit
    */
   virtual PMDialogEditBase* editWidget( QWidget* parent ) const override;
   /** */
   virtual QString pixmap() const override { return QString( "pminteriortexture" ); }

private:
   static PMMetaObject* s_pMetaObject;
};


#endif

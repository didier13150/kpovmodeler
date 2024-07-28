//-*-C++-*-
/*
**************************************************************************
                                 description
                             --------------------
    copyright            : (C) 2001-2002 by Luis Carvalho
    email                : lpassos@mail.telepac.pt
**************************************************************************

**************************************************************************
*                                                                        *
*  This program is free software; you can redistribute it and/or modify  *
*  it under the terms of the GNU General Public License as published by  *
*  the Free Software Foundation; either version 2 of the License, or     *
*  (at your option) any later version.                                   *
*                                                                        *
**************************************************************************/


#ifndef PMSKYSPHERE_H
#define PMSKYSPHERE_H



#include "pmtexturebase.h"

/**
 * Class for povray skyspheres
 */
class PMSkySphere : public PMTextureBase
{
   typedef PMTextureBase Base;
public:
   /**
    * Creates an PMSkySphere
    */
   PMSkySphere( PMPart* part );
   /**
    * Copy constructor
    */
   PMSkySphere( const PMSkySphere& s );
   /**
    * Deletes the object
    */
   virtual ~PMSkySphere();

   /** */
   virtual PMObject* copy() const override { return new PMSkySphere( *this ); }
   /** */
   virtual QString description() const override;

   /** */
   virtual PMMetaObject* metaObject() const override;
   /** */
   virtual void cleanUp() const override;

   /**
    * Returns a new @ref PMSkySphereEdit
    */
   virtual PMDialogEditBase* editWidget( QWidget* parent ) const override;
   /** */
   virtual QString pixmap() const override { return QString( "pmskysphere" ); }

private:
   /**
    * IDs for @ref PMMementoData
    */
//   enum PMSkySphereMementoID { };
   static PMMetaObject* s_pMetaObject;
};


#endif

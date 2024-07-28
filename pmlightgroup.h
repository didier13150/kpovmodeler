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


#ifndef PMLIGHTGROUP_H
#define PMLIGHTGROUP_H



#include "pmsolidobject.h"

/**
 * Class for povray light group objects.
 */

class PMLightGroup : public PMSolidObject
{
   typedef PMSolidObject Base;
public:
   /**
    * Creates an empty PMLightGroup object
    */
   PMLightGroup( PMPart* part );
   /**
    * Copy constructor
    */
   PMLightGroup( const PMLightGroup& lg );

   /**
    * deletes the PMLightGroup object
    */
   virtual ~PMLightGroup();

   /** */
   virtual PMObject* copy() const override { return new PMLightGroup( *this ); }
   /** */
   virtual QString description() const override;

   /** */
   virtual PMMetaObject* metaObject() const override;
   /** */
   virtual void cleanUp() const override;

   /** */
   virtual void serialize( QDomElement& e, QDomDocument& doc ) const override;
   /** */
   virtual void readAttributes( const PMXMLHelper& h ) override;

   /**
    * Returns a new @ref PMLightGroupEdit
    */
   virtual PMDialogEditBase* editWidget( QWidget* parent ) const override;
   /**
    * Returns the name of the pixmap that is displayed in the tree view
    * and dialog view
    */
   virtual QString pixmap() const override { return QString( "pmlightgroup" ); }

   /**
    * Returns the global lights flag
    */
   bool globalLights() const { return m_globalLights; }
   /**
    * Sets the global lights flag
    */
   void setGlobalLights( bool gl );

   /** */
   virtual void restoreMemento( PMMemento* s ) override;
private:
   /**
    * IDs for @ref PMMementoData
    */
   enum PMGlobalLightsMementoID { PMGlobalLightsID };

   bool m_globalLights;

   static PMMetaObject* s_pMetaObject;
};

#endif

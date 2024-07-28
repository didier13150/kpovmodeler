//-*-C++-*-
/*
**************************************************************************
                                 description
                             --------------------
    copyright            : (C) 2000-2002 by Andreas Zehender
    email                : zehender@kde.org
**************************************************************************

**************************************************************************
*                                                                        *
*  This program is free software; you can redistribute it and/or modify  *
*  it under the terms of the GNU General Public License as published by  *
*  the Free Software Foundation; either version 2 of the License, or     *
*  (at your option) any later version.                                   *
*                                                                        *
**************************************************************************/


#ifndef PMCSG_H
#define PMCSG_H



#include "pmsolidobject.h"

/**
 * Class for povray csg objects.
 */

class PMCSG : public PMSolidObject
{
   typedef PMSolidObject Base;
public:
   /**
    * The type of the csg object
    */
   enum PMCSGType { CSGUnion, CSGIntersection, CSGDifference, CSGMerge };
   /**
    * Creates an empty PMCSG union
    */
   PMCSG( PMPart* part );
   /**
    * Creates an empty PMCSG object with type t
    */
   PMCSG( PMPart* part, const PMCSGType t );
   /**
    * Copy constructor
    */
   PMCSG( const PMCSG& c );

   /**
    * deletes the PMCSG object
    */
   virtual ~PMCSG();

   /** */
   virtual PMObject* copy() const override { return new PMCSG( *this ); }
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
    * Returns a new @ref PMCSGEdit
    */
   virtual PMDialogEditBase* editWidget( QWidget* parent ) const override;
   /**
    * Returns the name of the pixmap that is displayed in the tree view
    * and dialog view
    */
   virtual QString pixmap() const override;

   /**
    * Returns the type of the csg
    */
   PMCSGType csgType() const { return m_type; }
   /**
    * Sets the type of the csg
    */
   void setCSGType( const PMCSGType t );

   /** */
   virtual void restoreMemento( PMMemento* s ) override;
private:
   /**
    * IDs for @ref PMMementoData
    */
   enum PMCSGMementoID { PMTypeID };
   PMCSGType m_type;

   static PMMetaObject* s_pMetaObject;
};

#endif

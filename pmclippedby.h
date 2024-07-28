//-*-C++-*-
/*
**************************************************************************
                                 description
                             --------------------
    copyright            : (C) 2002 by Andreas Zehender
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

#ifndef PMCLIPPEDBY_H
#define PMCLIPPEDBY_H



#include "pmcompositeobject.h"

/**
 * class for clipped_by povray statements
 */

class PMClippedBy : public PMCompositeObject
{
   typedef PMCompositeObject Base;
public:
   /**
    * Creates an empty PMClippedBy
    */
   PMClippedBy( PMPart* part );
   /**
    * Deletes the object
    */
   ~PMClippedBy();

   /** */
   virtual PMObject* copy() const override { return new PMClippedBy( *this ); }
   /** */
   virtual QString description() const override;

   /** */
   virtual PMMetaObject* metaObject() const override;
   /** */
   virtual void cleanUp() const override;

   /** */
   virtual bool dataChangeOnInsertRemove() const override { return true; }

   /** */
   virtual void serialize( QDomElement& e, QDomDocument& doc ) const override;
   /** */
   virtual void readAttributes( const PMXMLHelper& h ) override;

   /**
    * Returns a new @ref PMClippedByEdit
    */
   virtual PMDialogEditBase* editWidget( QWidget* parent ) const override;
   /**
    * Returns the name of the pixmap that is displayed in the tree view
    * and dialog view
    */
   virtual QString pixmap() const override { return QString( "pmclippedby" ); }

   /** */
   virtual void childRemoved( PMObject* ) override;
   /** */
   virtual void childAdded( PMObject* ) override;

   /**
    * Returns true if the object contains no child objects (except comments)
    */
   bool boundedBy() const;

private:
   enum PMClippedByMementoID { PMBoundedByID };
   static PMMetaObject* s_pMetaObject;
};

#endif

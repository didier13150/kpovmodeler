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


#ifndef PMBOX_H
#define PMBOX_H



#include "pmsolidobject.h"
#include "pmvector.h"

class PMViewStructure;

/**
 * Class for povray boxes.
 */

class PMBox : public PMSolidObject
{
   typedef PMSolidObject Base;
public:
   PMBox* objectCopy( PMObject* obj ) { return static_cast<PMBox*>(obj); }
   /**
    * Creates an empty PMBox
    */
   PMBox( PMPart* part );
   /**
    * Copy constructor
    */
   PMBox( const PMBox& b );
   /**
    * deletes the PMBox
    */
   virtual ~PMBox();

   /** */
   virtual PMObject* copy() const override { return new PMBox( *this ); }
   /** */
   virtual QString description() const override;

   /** */
   virtual PMMetaObject* metaObject() const override;

   /** */
   virtual void serialize( QDomElement& e, QDomDocument& doc ) const override;
   /** */
   virtual void readAttributes( const PMXMLHelper& h ) override;
   /**
    * Returns a new @ref PMBoxEdit
    */
   virtual PMDialogEditBase* editWidget( QWidget* parent ) const override;
   /**
    * Returns the name of the pixmap that is displayed in the tree view
    * and dialog view
    */
   virtual QString pixmap() const override { return QString( "pmbox" ); }

   /**
    * Returns Corner_1
    */
   PMVector corner1() const { return m_corner1; }
   /**
    * Sets Corner_1
    */
   void setCorner1( const PMVector& p );
   /**
    * Returns Corner_2
    */
   PMVector corner2() const { return m_corner2; }
   /**
    * Sets Corner_2
    */
   void setCorner2( const PMVector& p );

   /** */
   virtual void restoreMemento( PMMemento* s ) override;
   /** */
   virtual void controlPoints( PMControlPointList& list ) override;
   /** */
   virtual void controlPointsChanged( PMControlPointList& list ) override;
   /** */
   virtual void cleanUp() const override;

protected:
   /** */
   virtual bool isDefault() override;
   /** */
   virtual void createViewStructure() override;
   /** */
   virtual PMViewStructure* defaultViewStructure() const override;

private:  
   /**
    * IDs for @ref PMMementoData
    */
   enum PMBoxMementoID { PMCorner1ID, PMCorner2ID };
   PMVector m_corner1, m_corner2;

   /**
    * The default view structure. It can be shared between boxes
    */
   static PMViewStructure* s_pDefaultViewStructure;
   static PMMetaObject* s_pMetaObject;
};

#endif

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


#ifndef PMTRANSLATE_H
#define PMTRANSLATE_H



#include "pmobject.h"
#include "pmvector.h"

/**
 * Class for povray move commands.
 */

class PMTranslate : public PMObject
{
   typedef PMObject Base;
public:
   /**
    * Creates a move < 0, 0, 0 >
    */
   PMTranslate( PMPart* part );
   /**
    * Copy constructor
    */
   PMTranslate( const PMTranslate& t );
   /**
    * deletes the object
    */
   virtual ~PMTranslate();

   /** */
   virtual PMObject* copy() const override { return new PMTranslate( *this ); }
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
    * Returns a new @ref PMTranslateEdit
    */
   virtual PMDialogEditBase* editWidget( QWidget* parent ) const override;
   /** */
   virtual QString pixmap() const override { return QString( "pmtranslate" ); }

   /**
    * Returns the movement
    */
   PMVector translation() const { return m_move; }
   /**
    * Sets the movement
    */
   void setTranslation( const PMVector& p );

   /** */
   virtual void restoreMemento( PMMemento* s ) override;
   /** */
   virtual bool hasTransformationMatrix() const override { return true; }
   /** */
   virtual PMMatrix transformationMatrix() const override;

   /** */
   virtual void controlPoints( PMControlPointList& list ) override;
   /** */
   virtual void controlPointsChanged( PMControlPointList& list ) override;
private:
   /**
    * IDs for @ref PMMementoData
    */
   enum PMTranslateMementoID { PMTranslationID };
   PMVector m_move;

   static PMMetaObject* s_pMetaObject;
};

#endif

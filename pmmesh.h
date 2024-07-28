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


#ifndef PMMESH_H
#define PMMESH_H



#include "pmsolidobject.h"
#include "pmvector.h"
#include <QList>

class PMTriangle;

/**
 * Class for povray mesh objects.
 */
class PMMesh : public PMSolidObject
{
   typedef PMSolidObject Base;
public:
   /**
    * Creates an empty PMMesh object
    */
   PMMesh( PMPart* part );
   /**
    * Copy constructor
    */
   PMMesh( const PMMesh& m );

   /**
    * deletes the PMMesh object
    */
   virtual ~PMMesh();

   /** */
   virtual PMObject* copy() const override { return new PMMesh( *this ); }
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
    * Returns a new @ref PMMeshEdit
    */
   virtual PMDialogEditBase* editWidget( QWidget* parent ) const override;
   /**
    * Returns the name of the pixmap that is displayed in the tree view
    * and dialog view
    */
   virtual QString pixmap() const override { return QString( "pmmesh" ); }

   /**
    * Returns the hierarchy flag
    */
   bool hierarchy() const { return m_hierarchy; }
   /**
    * Sets the type of the csg
    */
   void setHierarchy( bool h );

   /**
    * Returns true if the inside vector is enabled
    */
   bool isInsideVectorEnabled() const { return m_enableInsideVector; }
   /**
    * Sets the inside vector flag
    */
   void enableInsideVector( bool eiv );

   /**
    * Returns the inside vector
    */
   PMVector insideVector() const { return m_insideVector; }
   /**
    * Sets the inside vector
    */
   void setInsideVector( const PMVector& iv );

   /** */
   virtual void createMemento() override;
   /** */
   virtual void restoreMemento( PMMemento* s ) override;
   /** */
   virtual void controlPoints( PMControlPointList& list ) override;
   /** */
   virtual void controlPointsChangedList( PMControlPointList& list, PMObjectList& objList ) override;

private:
   /**
    * IDs for @ref PMMementoData
    */
   enum PMMeshMementoID { PMHierarchyID, PMEnableInsideVectorID,
                          PMInsideVectorID };

   bool m_hierarchy;
   bool m_enableInsideVector;
   PMVector m_insideVector;

   static PMMetaObject* s_pMetaObject;

   /**
    * Point to point structure for changes with control points
    */
   struct pointToPoint {
      PMTriangle *object;
      int pointID;
      int listID;
   };

   /**
    * List of point to point structures
    */
   QList<pointToPoint> m_pointToPointList;
};

#endif

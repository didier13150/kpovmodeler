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

#ifndef PMDECLARE_H
#define PMDECLARE_H



#include "pmcompositeobject.h"
#include "pmsymboltable.h"

/**
 * Class for all povray declares
 */
class PMDeclare : public PMCompositeObject
{
   typedef PMCompositeObject Base;
public:
   /**
    * Constructor
    */
   PMDeclare( PMPart* part );
   /**
    * Copy constructor
    */
   PMDeclare( const PMDeclare& d );
   /**
    * Deletes the object
    */
   ~PMDeclare();

   /** */
   virtual PMObject* copy() const override { return new PMDeclare( *this ); }

   /** */
   virtual QString description() const override;
   /** */
   virtual QString pixmap() const override;

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
    * Returns a new @ref PMDeclareEdit
    */
   virtual PMDialogEditBase* editWidget( QWidget* parent ) const override;
   /**
    * Returns the id of the declare
    */
   virtual QString name() const override { return m_id; }
   /**
    * Returns the id of the declare
    */
   QString id() const { return m_id; }
   /**
    * Returns the declare type
    */
   QString declareType() const;
   /**
    * not visual in tree
    */
   bool declare_not_in_tree;
   /**
    * The declare is a function
    */
   bool is_a_function;
   //bool isAfunction() { return is_a_function; }
   /**
    * Sets the id of the object.
    */
   void setID( const QString& id );
   /** */
   virtual bool canHaveName() const override { return true; }

   /** */
   virtual void restoreMemento( PMMemento* s ) override;
   /**
    * Returns an iterator to the list of objects, that are linked to that
    * declare
    */
   const PMObjectList& linkedObjects() const
   {
      return m_linkedObjects;
   }
   /**
    * Adds the object to the list of linked objects
    */
   void addLinkedObject( PMObject* o );
   /**
    * Removes the object from the list of linked objects
    */
   void removeLinkedObject( PMObject* o );

   /** */
   virtual void childAdded( PMObject* o ) override;
   /** */
   virtual void childRemoved( PMObject* o ) override;

private:
   /**
    * Sets the declare type
    */
   void setDeclareType( PMMetaObject* o );
   /**
    * Recalculates the declaration type
    */
   void updateDeclareType();
   /**
    * IDs for @ref PMMementoData
    */
   enum PMDeclareMementoID { PMIDID };

   /**
    * id of the declare
    */
   QString m_id;
   /**
    * The linked objects
    */
   PMObjectList m_linkedObjects;
   /**
    * The declare type
    */
   PMMetaObject* m_pDeclareType;

   static PMMetaObject* s_pMetaObject;
};

#endif

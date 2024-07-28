/*
**************************************************************************
                                 description
                             --------------------
    copyright            : (C) 2003 by Andreas Zehender
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

#ifndef PMOPENGLSETTINGS_H
#define PMOPENGLSETTINGS_H



#include "pmsettingsdialog.h"

class QCheckBox;

/**
 * OpenGL configuration dialog page
 */
class PMOpenGLSettings : public PMSettingsDialogPage
{
   Q_OBJECT
public:
   /**
    * Default constructor
    */
   PMOpenGLSettings( QWidget* parent = 0 );
   /** */
   virtual void displaySettings() override;
   /** */
   virtual bool validateData() override;
   /** */
   virtual void applySettings() override;
   /** */
   virtual void displayDefaults() override;

private:
   QCheckBox* m_pDirect;
};


#endif

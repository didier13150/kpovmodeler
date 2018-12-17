/*
**************************************************************************
                                 description
                             --------------------
    copyright            : (C) 2000-2006 by Andreas Zehender
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

//
//#include <khelpmenu.h>
#include "ktoolbar.h"
#include "kedittoolbar.h"
#include "kstandardaction.h"
#include "pmshell.h"
#include "pmpart.h"
#include "pmsettingsdialog.h"
#include "pmdefaults.h"
#include "pmdockwidget.h"
#include "pmviewbase.h"
#include "pmunknownview.h"
#include "pmviewlayoutmanager.h"
#include "kactionmenu.h"
#include "kactioncollection.h"
#include <QAction>
#include <QStatusBar>
#include <QFileDialog>
#include <QMenu>
#include <QMenuBar>
#include <QTimer>
#include <QSettings>
#include <QStandardPaths>
#include <QMessageBox>
#include <QShowEvent>


//#include "pmviewfactory.h"

#define KPM_WITH_OBJECT_LIBRARY

//const int c_statusBarInfo = 0;
//const int c_statusBarControlPoints = 1;

PMShell::PMShell( const QUrl &url )
      : PMDockMainWindow( nullptr )
{
   setAttribute( Qt::WA_DeleteOnClose );
   statusBarLabel = new QLabel( this );
   currentUrl = nullptr;
   /***call pmpart with mainwidget***/
   m_pPart = new PMPart( this, this, true, this );
   m_pPart->setReadWrite(); // read-write mode
   m_viewNumber = 0;
   /***eticre view-hide Declare with name have "_" at first char***/
   show_list = false;

   QString ruleFile = QStandardPaths::locate( QStandardPaths::GenericDataLocation, QString( "kpovmodeler/kpovmodelershell.rc" ) );
   setXMLFile( ruleFile, false, false );

   setSize();
   setupActions();
   setupView();
   //KXmlGuiWindow::createGUI( ruleFile );
   this->createGUI(m_pPart);  // init shell gui + part

   //guiFactory()->addClient( m_pPart );
   m_pStatusBar = statusBar();
   m_pStatusBar->addWidget ( statusBarLabel, 1 );
   statusBarLabel->setText(" ");
   //m_pStatusBar->showMessage( " ", c_statusBarInfo, 1 );
   //m_pStatusBar->showMessage( "" , c_statusBarControlPoints );

   if( !url.isEmpty() )
   {
      openUrl( url );
      currentUrl = url;
   }

   setWindowTitle( url.toDisplayString() );

   connect( m_pPart, SIGNAL( modified() ), SLOT( slotModified() ) );

   connect( m_pPart, SIGNAL( controlPointMessage( const QString& ) ),
                       SLOT( slotControlPointMsg( const QString& ) ) );
}

PMShell::~PMShell()
{
    QSettings qset;
    qset.setValue( "mainwindow/size", this->size() );
    qset.setValue( "mainwindow/fullscreen", this->isFullScreen() );
    qDebug() << "pmshell desctructor";
    //delete m_pPart;
    qDebug() << "pmshell01";
    //m_pPart = nullptr;

}

void PMShell::setSize()
{
    QSettings qset;
    if ( qset.value( "mainwindow/fullscreen" ).toBool() )
       this->showFullScreen();
    else if ( qset.contains( "mainwindow/size" ) )
        this->resize( qset.value( "mainwindow/size" ).toSize() );
    else
        this->resize( 1024, 800 );
}

void PMShell::setupActions()
{
//   m_helpMenu = new KHelpMenu( this, PMFactory::aboutData(), true,
//                               actionCollection() );
    // file menu from standard .rc file merged with custom .rc file
   //KStandardAction::openNew( this, SLOT( slotFileNew() ), actionCollection() );
    //QMainWindow::menuBar()->clear();
    //QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    //openNewFile = QAction( "openNewFile" );
    //openNewFile = new QAction;
    //openNewFile->setText("New File");
    QAction* openNew = new QAction( "New" );
    connect( openNew, &QAction::triggered, this, &PMShell::slotFileNew );
    actionCollection()->addAction( "file_new", openNew );

   //KStandardAction::open( this, SLOT( slotFileOpen() ), actionCollection() );
   QAction* open = new QAction( "Open" );
   connect( open, &QAction::triggered, this, &PMShell::slotFileOpen );
   actionCollection()->addAction( "file_open", open );

   m_pRecent = KStandardAction::openRecent( this, SLOT( slotOpenRecent( const QUrl& ) ),
                                       actionCollection() );

   //KStandardAction::save( this, SLOT( slotFileSave() ), actionCollection() );
   QAction* save = new QAction( "Save" );
   connect( save, &QAction::triggered, this, &PMShell::slotFileSave );
   actionCollection()->addAction( "file_save", save );

   //KStandardAction::saveAs( this, SLOT( slotFileSaveAs() ), actionCollection() );
   QAction* saveAs = new QAction( "Save As" );
   connect( saveAs, &QAction::triggered, this, &PMShell::slotFileSaveAs );
   actionCollection()->addAction( "file_save_as", saveAs );

   //KStandardAction::revert( this, SLOT( () ), actionCollection() );
   QAction* revert = new QAction( "Revert" );
   connect( revert, &QAction::triggered, this, &PMShell::slotFileRevert );
   actionCollection()->addAction( "file_revert", revert );

   //KStandardAction::print( this, SLOT( slotFilePrint() ), actionCollection() );
   QAction* print = new QAction( "Print" );
   connect( print, &QAction::triggered, this, &PMShell::slotFilePrint );
   actionCollection()->addAction( "file_print", print );

   //KStandardAction::close( this, SLOT( slotFileClose() ), actionCollection() );
   QAction* close = new QAction( "Close" );
   connect( close, &QAction::triggered, this, &PMShell::slotFileClose );
   actionCollection()->addAction( "file_close", close );
   //KStandardAction::quit( this, SLOT( close() ), actionCollection() );
   QAction* quit = new QAction( "Quit", this );
   connect( quit, &QAction::triggered, this, &PMShell::shellClose );
   actionCollection()->addAction( "file_quit", quit );

   /***eticre add showlib***/
   m_pPathAction = actionCollection()->addAction( "options_show_lib" );
   m_pPathAction->setCheckable( true );
   m_pPathAction->setText( tr( "Show &List" ) );
   connect( m_pPathAction, SIGNAL( triggered() ), this, SLOT( slotShowList() ) );
   //m_pPathAction->setCheckedState( KGuiItem( tr( "Hide &List" ) ) );
   
   m_pPathAction = actionCollection()->addAction( "options_show_path" );
   m_pPathAction->setCheckable( true );
   m_pPathAction->setText( tr( "Show &Path" ) );
   connect( m_pPathAction, SIGNAL( triggered() ), this, SLOT( slotShowPath() ) );
   //m_pPathAction->setCheckedState( KGuiItem( tr( "Hide &Path" ) ) );

   m_pStatusbarAction = KStandardAction::showStatusbar( this, SLOT( slotShowStatusbar() ),
                                                   actionCollection() );

   KStandardAction::saveOptions( this, SLOT( saveOptions() ), actionCollection() );

   //KStandardAction::keyBindings( this, SLOT( slotConfigureKeys() ), actionCollection() );
   KStandardAction::configureToolbars( this, SLOT( slotConfigureToolbars() ), actionCollection() );
   KStandardAction::preferences( this, SLOT( slotSettings() ), actionCollection() );

   m_pNewTopViewAction = actionCollection()->addAction( "view_new_topview" );
   m_pNewTopViewAction->setText( tr( "New Top View" ) );
   connect( m_pNewTopViewAction, SIGNAL( triggered() ), this, SLOT( slotNewTopView() ) );

   m_pNewBottomViewAction = actionCollection()->addAction( "view_new_bottomview" );
   m_pNewBottomViewAction->setText( tr ( "New Bottom View" ) );
   connect( m_pNewBottomViewAction, SIGNAL( triggered() ), this, SLOT( slotNewBottomView() ) );
   m_pNewLeftViewAction = actionCollection()->addAction( "view_new_leftview" );
   m_pNewLeftViewAction->setText( tr( "New Left View" ) );
   connect( m_pNewLeftViewAction, SIGNAL( triggered() ), this, SLOT( slotNewLeftView() ) );
   m_pNewRightViewAction = actionCollection()->addAction( "view_new_rightview" );
   m_pNewRightViewAction->setText( tr( "New Right View" ) );
   connect( m_pNewRightViewAction, SIGNAL( triggered() ), this, SLOT( slotNewRightView() ) );
   m_pNewFrontViewAction = actionCollection()->addAction( "view_new_frontview" );
   m_pNewFrontViewAction->setText( tr( "New Front View" ) );
   connect( m_pNewFrontViewAction, SIGNAL( triggered() ), this, SLOT( slotNewRightView() ) );
   m_pNewBackViewAction = actionCollection()->addAction( "view_new_backview" );
   m_pNewBackViewAction->setText( tr( "New Back View" ) );
   connect( m_pNewBackViewAction, SIGNAL( triggered() ), this, SLOT( slotNewBackView() ) );
   m_pNewCameraViewAction = actionCollection()->addAction( "view_new_cameraview" );
   m_pNewCameraViewAction->setText( tr( "New Camera View" ) );
   connect( m_pNewCameraViewAction, SIGNAL( triggered() ), this, SLOT( slotNewCameraView() ) );
   m_pNewTreeViewAction = actionCollection()->addAction( "view_new_treeview" );
   m_pNewTreeViewAction->setText( tr( "New Object Tree" ) );
   connect( m_pNewTreeViewAction, SIGNAL( triggered() ), this, SLOT( slotNewTreeView() ) );
   m_pNewDialogViewAction = actionCollection()->addAction( "view_new_dialogview" );
   m_pNewDialogViewAction->setText( tr( "New Properties View" ) );
   connect( m_pNewDialogViewAction, SIGNAL( triggered() ), this, SLOT( slotNewDialogView() ) );

#ifdef KPM_WITH_OBJECT_LIBRARY
   m_pNewLibraryBrowserAction = actionCollection()->addAction( "view_new_librarybrowser" );
   m_pNewLibraryBrowserAction->setText( tr( "New Library Browser" ) );
   connect( m_pNewLibraryBrowserAction, SIGNAL( triggered() ), this, SLOT( slotNewLibraryBrowserView() ) );
#endif

   // Creating the view layouts menu
   m_pViewLayoutsAction = actionCollection()->add<KActionMenu>( "view_layouts_menu" );
   m_pViewLayoutsAction->setText( tr( "View Layouts" ) );
   QMenu* menu = m_pViewLayoutsAction->menu();
   connect( menu, SIGNAL( aboutToShow() ), SLOT( slotViewsMenuAboutToShow() ) );
   PMViewLayoutManager::theManager()->fillPopupMenu( menu );
   connect( menu, SIGNAL( triggered( QAction* ) ), SLOT( slotSelectedLayout( QAction* ) ) );

   m_pSaveViewLayoutAction = actionCollection()->addAction( "save_view_layout" );
   m_pSaveViewLayoutAction->setText( tr( "Save View Layout..." ) );
   connect( m_pSaveViewLayoutAction, SIGNAL( triggered() ), this, SLOT( slotSaveViewLayout() ) );
}

void PMShell::setupView()
{
   PMViewLayoutManager::theManager()->displayDefaultLayout( this );
}


PMDockWidget* PMShell::createView( const QString& t, PMViewOptions* o,
                                   bool initPosition )
{
   PMDockWidget* dock = nullptr;
   PMViewBase* contents = nullptr;

   PMViewTypeFactory* factory = PMViewFactory::theFactory()->viewFactory( t );

   m_viewNumber++;
   QString name = QString( "View (%1)" ).arg( m_viewNumber );

   if( factory )
   {
      QString desc;
      // Create the appropriate dock widget
      if( o )
         desc = factory->description( o );
      else
         desc = factory->description();

      dock = createDockWidget( QIcon::fromTheme( factory->iconName() ).pixmap( 16, 16), nullptr,
                               desc, desc );

      contents = factory->newInstance( dock, m_pPart );

      if( o ) contents->restoreViewConfig( o );
   }
   else
   {
      // unknown view type
      dock = createDockWidget( QIcon::fromTheme( "Unknown" ).pixmap( 16, 16), nullptr,
                               "Unknown", "Unknown" );
      contents = new PMUnknownView( t, dock );
   }

   dock->setWidget( contents );
   connect( dock, SIGNAL( headerCloseButtonClicked() ),
                  SLOT( slotDockWidgetClosed() ) );

   if( initPosition )
   {
      if( t == "librarybrowserview" )
          dock->resize( 800 , 600 );
      else
          dock->resize( 300 , 400 );

      dock->manualDock( nullptr, PMDockWidget::DockDesktop, 50,
                        mapToGlobal( QPoint( 50, 50 ) ) );
   }
   return dock;
}

void PMShell::slotNewGraphicalView( PMGLView::PMViewType t )
{
   PMGLViewOptions* o = new PMGLViewOptions( t );
   createView( "glview", o );
   delete o;
}

void PMShell::slotNewTopView()
{
   slotNewGraphicalView( PMGLView::PMViewNegY );
}

void PMShell::slotNewBottomView()
{
   slotNewGraphicalView( PMGLView::PMViewPosY );
}

void PMShell::slotNewLeftView()
{
   slotNewGraphicalView( PMGLView::PMViewPosX );
}

void PMShell::slotNewRightView()
{
   slotNewGraphicalView( PMGLView::PMViewNegX );
}

void PMShell::slotNewFrontView()
{
   slotNewGraphicalView( PMGLView::PMViewPosZ );
}

void PMShell::slotNewBackView()
{
   slotNewGraphicalView( PMGLView::PMViewNegZ );
}

void PMShell::slotNewCameraView()
{
   slotNewGraphicalView( PMGLView::PMViewCamera );
}

void PMShell::slotNewDialogView()
{
   createView( "dialogview" );
}

void PMShell::slotNewTreeView()
{
   createView( "treeview" );
}

void PMShell::slotNewLibraryBrowserView()
{
   createView( "librarybrowserview" );
}

void PMShell::slotDockWidgetClosed()
{
   QObject* o = sender();
   if( o && o->inherits( "PMDockWidget" ) )
   {
      if( !m_objectsToDelete.contains( o ) )
      {
         m_objectsToDelete.append( o );
         QTimer::singleShot( 0, this, SLOT( slotDeleteClosedObjects() ) );
      }
   }
}

void PMShell::slotDeleteClosedObjects()
{
	foreach(QObject* o, m_objectsToDelete) delete o;
   m_objectsToDelete.clear();
}

void PMShell::openUrl( const QUrl &url )
{
   m_pRecent->addUrl( url );

   if( !m_pPart->ismodified && m_pPart->url().isEmpty() )
   {
      m_pPart->openFileQt( url );
      setWindowTitle( m_pPart->url().toDisplayString() );
   }
   else
   {
      PMShell *shell = new PMShell();
      shell->show();
      shell->openUrl( url );
   }
}

void PMShell::slotOpenRecent( const QUrl &url )
{
   m_openRecentURL = url;
   QTimer::singleShot( 0, this, SLOT( slotOpenRecentTimer() ) );
}

void PMShell::slotOpenRecentTimer()
{
   openUrl( m_openRecentURL );
}

void PMShell::slotFileNew()
{
   if( !m_pPart->ismodified && m_pPart->url().isEmpty() )
   {
      m_pPart->newDocument();
      setWindowTitle();
   }
   else
   {
      PMShell *shell = new PMShell();
      shell->show();
   }
}

void PMShell::slotFileOpen()
{
   QUrl url = QFileDialog::getOpenFileUrl( this, "File",
      QUrl(), QString( "*.kpm|" ) +
     "Povray Modeler Files ( *.kpm )" +
     "\n*|" + "All Files" );

   if( !url.isEmpty() )
      openUrl( url );
}

void PMShell::slotFileSave()
{
    m_pPart->slotAboutToSave();

   if( m_pPart->ismodified )
   {
      if( !currentUrl.isEmpty() && m_pPart->isReadWrite() )
         m_pPart->saveFileQt( currentUrl );
      else
         saveAs();

      setWindowTitle( m_pPart->url().toDisplayString() );
   }
   else
      emit statusMsg( tr( "No changes need to be saved" ) );
}

void PMShell::slotFileSaveAs()
{
    m_pPart->slotAboutToSave();
    saveAs();
}

void PMShell::saveAs()
{
   QFileDialog dlg( this );
   dlg.setNameFilter( "kpov file (*.kpm)" );
   dlg.setAcceptMode( QFileDialog::AcceptSave );

   if( dlg.exec() )
   {
       currentUrl = dlg.selectedUrls().at( 0 );
       if( QFileInfo( currentUrl.path() ).completeSuffix().isEmpty() )
          currentUrl.setPath( currentUrl.path() + ".kpm" );

      if( m_pPart->saveFileQt( currentUrl ) )
          setWindowTitle( currentUrl.toDisplayString() );
       else
          QMessageBox::warning( this, "Error", tr( "Could not save the file." ) );

      /*if( overwriteURL( url )  )
      {
         m_pRecent->addUrl( url );
         if( m_pPart->saveAs( url ) )
            setWindowTitle( url.toDisplayString() );
         else
            QMessageBox::warning( this, "Error", tr( "Could not save the file." ) );
      }*/
   }
}

void PMShell::slotFileRevert()
{
   QUrl url = m_pPart->url();

   if( !url.isEmpty() )
      m_pPart->openFileQt( url );
//   else
//    slotFileNew();
}

void PMShell::slotFilePrint()
{
   //TODO
   //   m_pPart->slotPrint();
}

void PMShell::slotFileNewWindow()
{
   PMShell* shell = new PMShell;
   shell->show();
}

void PMShell::slotFileClose()
{
   if( m_pPart->closeUrl() )
   {
      m_pPart->closeDocument();
      m_pPart->newDocument();
      setWindowTitle();
   }
}

void PMShell::slotShowToolbar()
{

   if( toolBar()->isVisible () )
      toolBar()->hide();
   else
      toolBar()->show();
}

void PMShell::slotShowStatusbar()
{
   if( statusBar()->isVisible () )
      statusBar()->hide();
   else
      statusBar()->show();
}
/***eticre view-hide Declare with name have "_" at first char***/
/***eticre refresh show lib view hidden not_in_tree***/
void PMShell::slotShowList()
{
  if( m_pPathAction->isChecked() )
      m_pPathAction->setText( tr( "Hide &List" ) );
  else
      m_pPathAction->setText( tr( "Show &List" ) );

   m_pPart->refreshView();
}

void PMShell::slotShowPath()
{
    if( m_pPathAction->isChecked() )
        m_pPathAction->setText( tr( "Hide &Path" ) );
    else
        m_pPathAction->setText( tr( "Show &Path" ) );

   setWindowTitle( m_pPart->url().toDisplayString() );
}

/*void PMShell::slotConfigureKeys()
{
   KShortcutsDialog kd;
   kd.addCollection( m_pPart->actionCollection() );
   kd.addCollection( actionCollection() );
   kd.configure( true );
   //KShortcutsDialog::configure( actionCollection() );
}*/

void PMShell::slotSettings()
{
   PMSettingsDialog dlg( m_pPart );
   dlg.exec();
}

void PMShell::slotConfigureToolbars()
{
   KEditToolBar dlg( factory() );
   connect( &dlg, SIGNAL( newToolbarConfig() ),
            this, SLOT( slotNewToolbarConfig() ) );
   dlg.exec();
}

void PMShell::slotNewToolbarConfig()
{
   createGUI( nullptr );
   createShellGUI( false );
   createGUI( m_pPart );
}

void PMShell::updateGUI()
{
   createGUI( nullptr );
   createShellGUI( false );
   createGUI( m_pPart );
}

void PMShell::saveOptions()
{
   QSettings qset;
   qset.setValue( "Appearance/ShowStatusbar", m_pStatusbarAction->isChecked() );
   // eticre save recent file m_pRecent->saveEntries( "RecentFile" );

   if( m_pPart )
       m_pPart->saveConfig();

   //config.sync();
}

void PMShell::restoreOptions()
{
   QSettings qset;
   bool showStatusbar = qset.value( "ShowStatusbar", true ).value<bool>();

   m_pStatusbarAction->blockSignals( true );
   m_pStatusbarAction->setChecked( showStatusbar );
   m_pStatusbarAction->blockSignals( false );

   if( showStatusbar )
      statusBar()->show();
   else
      statusBar()->hide();

   // eticre save recent filem_pRecent->loadEntries( "RecentFile" );
}

void PMShell::setWindowTitle( const QString& caption )
{
   QString tmp;

   if( caption.isEmpty() )
      tmp = tr( "unknown" );
   else
   {
      if( !m_pPathAction->isChecked() )
         tmp = caption.right( caption.length() - caption.lastIndexOf( '/' ) - 1 );
      else
         tmp = caption;
   }

   QMainWindow::setWindowTitle( tmp );//, m_pPart->isModified() );
}

void PMShell::statusMsg( const QString& text )
{
   m_pStatusBar->showMessage( text, 5000 );
}

void PMShell::closeEvent( QCloseEvent *event )
{
    shellClose();
}

void PMShell::shellClose()
{
   queryClose();
   m_pPart->deleteContents();
   this->close();

}

bool PMShell::queryClose()
{
   //return m_pPart->closeUrl();
   if( m_pPart->ismodified )
   {
       int i = QMessageBox::question( this, "Save", tr("The document has been modified.\n"
                                                        "Do you want to save your changes?"),
                                       QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
       if( i == QMessageBox::Save )
       {
           saveAs();
           return true;
       }
       if( i == QMessageBox::Discard )
       {
           this->close();
           m_pPart->setModified( false );
           return true;
        }

       return false;
   }

   return true;
}

void PMShell::showEvent( QShowEvent* ){
   activateDock();
}

void PMShell::slotModified()
{
   setWindowTitle( m_pPart->url().toDisplayString() );
}

void PMShell::slotControlPointMsg( const QString& msg )
{
   if( msg.isEmpty() )
     statusBarLabel->setText( msg );
   else
     statusBarLabel->setText( QString( " " ) + msg + QString( " " ));
}

bool PMShell::overwriteURL( const QUrl& u )
{
   if( u.isLocalFile() )
   {
      QFileInfo info;
      QString name( u.path() );
      info.setFile( name );

      if( info.exists() )
      {
         QMessageBox m;
         m.setText( "Overwrite file" );
         m.setInformativeText( "A file with this name already exists.\nDo you want to overwrite it?" );
         m.setStandardButtons( QMessageBox::Save | QMessageBox::Cancel );
         if ( m.exec() == QMessageBox::Save )
             return( true );
      }
   }
   return ( false );
}

void PMShell::slotSelectedLayout( QAction* action )
{
   PMViewLayoutManager::theManager()->displayLayout( action->data().toInt(), this );
}

void PMShell::slotSaveViewLayout()
{
   PMSaveViewLayoutDialog dlg( this );
   dlg.show();
}

void PMShell::slotViewsMenuAboutToShow()
{
   QMenu* menu = m_pViewLayoutsAction->menu();

   PMViewLayoutManager::theManager()->fillPopupMenu( menu );
}



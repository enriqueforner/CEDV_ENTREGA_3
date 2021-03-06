#include "IntroState.h"
#include "PlayState.h"
#include "IntroScene.h"
template<> IntroState* Ogre::Singleton<IntroState>::msSingleton = 0;

IntroState::IntroState(){
    _root = Ogre::Root::getSingletonPtr();
    _sceneMgr = _root->createSceneManager(Ogre::ST_GENERIC, "SceneManager");
    _timesCreated = 0;
}

void
IntroState::enter ()
{
  
  _sceneMgr = _root->getSceneManager("SceneManager");
  _sceneMgr -> setAmbientLight(Ogre::ColourValue(1,1,1));
  _camera = _sceneMgr->createCamera("IntroCamera");
  _camera->setPosition(Ogre::Vector3(5,20,56));
  _camera->lookAt(Ogre::Vector3(0,0,0));
  _camera->setNearClipDistance(5);
  _camera->setFarClipDistance(10000);
  _viewport = _root->getAutoCreatedWindow()->addViewport(_camera);
  //_viewport->setBackgroundColour(Ogre::ColourValue(1.0, 1.0, 1.0));

  if (_timesCreated<1){
    loadCEGUI();
    _timesCreated++;
  }

  IntroScene* iS = new IntroScene(_sceneMgr);
  iS-> crearMenuInicioCEGUI();
  iS-> crearWorld();
  _exitGame = false;
}

void
IntroState::exit()
{
  _sceneMgr->clearScene();
  _root->getAutoCreatedWindow()->removeAllViewports();
}

void
IntroState::pause ()
{
}

void
IntroState::resume ()
{
}

bool
IntroState::frameStarted
(const Ogre::FrameEvent& evt) 
{
  return true;
}

bool
IntroState::frameEnded
(const Ogre::FrameEvent& evt)
{
  if (_exitGame)
    return false;
  
  return true;
}

void
IntroState::keyPressed
(const OIS::KeyEvent &e)
{
  if (e.key == OIS::KC_SPACE) {
    changeState(PlayState::getSingletonPtr());
  }
}

void
IntroState::keyReleased
(const OIS::KeyEvent &e )
{
  if (e.key == OIS::KC_ESCAPE) {
    _exitGame = true;
  }
}

void
IntroState::mouseMoved
(const OIS::MouseEvent &e)
{
   CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseMove(e.state.X.rel, e.state.Y.rel);  
}

void
IntroState::mousePressed
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
  CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(convertMouseButton(id)); 
}

void
IntroState::mouseReleased
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
  CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(convertMouseButton(id));
}

CEGUI::MouseButton IntroState::convertMouseButton(OIS::MouseButtonID id)
{
  CEGUI::MouseButton ceguiId;
  switch(id)
    {
    case OIS::MB_Left:
      ceguiId = CEGUI::LeftButton;
      break;
    case OIS::MB_Right:
      ceguiId = CEGUI::RightButton;
      break;
    case OIS::MB_Middle:
      ceguiId = CEGUI::MiddleButton;
      break;
    default:
      ceguiId = CEGUI::LeftButton;
    }
  return ceguiId;
}

bool IntroState::exitButtonC(const CEGUI::EventArgs& e){
    _exitGame = true;
    return true; 
}

IntroState*
IntroState::getSingletonPtr ()
{
return msSingleton;
}

IntroState&
IntroState::getSingleton ()
{ 
  assert(msSingleton);
  return *msSingleton;
}

void IntroState::loadCEGUI(){

  //CEGUI
  renderer = &CEGUI::OgreRenderer::bootstrapSystem();
  CEGUI::Scheme::setDefaultResourceGroup("Schemes");
  CEGUI::ImageManager::setImagesetDefaultResourceGroup("Imagesets");
  CEGUI::Font::setDefaultResourceGroup("Fonts");
  CEGUI::WindowManager::setDefaultResourceGroup("Layouts");
  CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
  //Para los botones
  CEGUI::SchemeManager::getSingleton().createFromFile("VanillaSkin.scheme");
  //Para el Raton
  CEGUI::SchemeManager::getSingleton().createFromFile("OgreTray.scheme");
  //Para nada de momento
  CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");
  
  CEGUI::System::getSingleton().getDefaultGUIContext().setDefaultFont("DejaVuSans-12");
  CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("OgreTrayImages/MouseArrow");
  
  _sheet = CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow","Ex1/Sheet");
  CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(_sheet);
  
}
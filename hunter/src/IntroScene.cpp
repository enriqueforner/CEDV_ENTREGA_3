
#include "IntroScene.h"
#include "IntroState.h"

IntroScene::IntroScene(Ogre::SceneManager* sceneManager){
  _sheet = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();
  _sceneManager = sceneManager;
}
IntroScene::~IntroScene(){

  
}

void IntroScene::crearMenuInicioCEGUI(){

	CEGUI::Window* vent = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("hunterMP.layout");
	vent->setPosition(CEGUI::UVector2(CEGUI::UDim(0.22f,0),CEGUI::UDim(0.18f,0)));
	_sheet -> addChild(vent);
	vent-> moveToFront();

}

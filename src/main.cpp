#include "game/Game.h"
#include "json/json.h"
#include "irrKlang/include/irrKlang.h"

using namespace irrklang;

int main() {

   // std::string name = "sysdefault:CARD=Headset";
  //  ISoundEngine *SoundEngine = createIrrKlangDevice(irrklang::ESOD_ALSA, ESEO_DEFAULT_OPTIONS, name.c_str());
   /*
    auto list = createSoundDeviceList();
    std::cout << list->getDeviceCount() << std::endl;

    std::cout << "id: "<< list->getDeviceID(0) << std::endl;
    std::cout << list->getDeviceDescription(0) << std::endl;
*/

//    if (!SoundEngine) {
  //      printf("Could not startup engine\n");
    //    return 0; // error starting up the engine
    //}


    //SoundEngine->play2D("res/sound/bell.wav", false);
    Game game;
    return 0;
}


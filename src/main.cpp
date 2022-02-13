#include "game/Game.h"
#include "json/json.h"

int main() {
    Json::Value root;

    std::string array[] = {
            "test",
            "lost",
            "omg"
    };

    root["result"]["name"] = "ok";
    root["result"]["version"] = 1.0;
    root["result"]["list"] = "lost";


    Json::StyledWriter styledWriter;

    std::string string = styledWriter.write(root);

    Json::Reader reader;

    Json::Value parsed;

    bool success = reader.parse(string, parsed, false);

    if (success)
        std::cout << parsed["result"]["name"] << std::endl;

    std::cout << styledWriter.write(root) << std::endl;
    Game game;
    return 0;
}


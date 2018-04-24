#include <iostream>
#include "asset_manager\header\AssetManager.h"
#include "game\header\Object.h"
#include "game\header\Application.h"

using namespace std;

namespace tests
{
	int run_application();
	int create_doodads();

	int run_application()
	{
		cout << "Test : run_application" << endl;
		game::Application app(800, 600, "Game Test");
		app.run();
		return 0;
	}

	int create_doodads()
	{
		cout << "Test : create_objects" << endl;
		game::Application app(800, 600, "Game Test", "assets/ResourceList.json");
		app.create_object("doodad.test");
		app.run();
		return 0;
	}
}
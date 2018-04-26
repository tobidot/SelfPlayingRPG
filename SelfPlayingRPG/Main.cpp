#include <iostream>
#include <Windows.h>
#include <boost/stacktrace.hpp>
#include <SFML/Graphics.hpp>
#include "visualization\header\Sprite.h"

#if DEBUG
namespace tests
{
	int draw_sprite();
	int draw_layer();
	int draw_visualizer();
	int draw_resources();
	int read_json();
	int load_resources();
	int run_application();
	int create_doodads();
	int novo_tree();
	int stringify();

	int run_application();
	int create_doodads();
}
#endif

void test()
{

}

void run()
{

}

int main()
{
	return tests::create_doodads();
}
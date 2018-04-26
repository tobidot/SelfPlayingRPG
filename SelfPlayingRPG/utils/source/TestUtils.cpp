#include <assert.h>
#include <iostream>
#include <Windows.h>
#include <SFML\Graphics\Rect.hpp>
#include "utils\header\NovoTree.h"
#include "utils\header\Bounds.h"
#include "utils\header\Point.h"
#include "utils\header\ToString.h"

using namespace utils;
using namespace std;

namespace tests
{
	int stringify();
	int novo_tree();
	static void clear();

	int novo_tree()
	{
		using NTree = NovoTree<Point<float>, 2>;
		cout << "Test : novo_tree" << endl;
		NTree::Bounds bounds (0.0f,0.0f,10.0f,10.0f);
		cout << "create tree with bounds "<< std::to_string(bounds) << endl;
		NTree::GET_POS_FUNCTION getPosFunc = [](const utils::Point<float> &p) {
			return utils::Point<float>(p); 
		};
		NTree tree(bounds, getPosFunc, nullptr, 3);
		cout << std::to_string(tree);


		cout << "insert (-5, -5) // not within bounds" << endl;
		tree.insert({ -5, -5 });
		cout << std::to_string(tree);
		assert(tree.has_children() == false);
		assert(tree.count_elements() == 0);

		cout << "insert (5, 5) // within bounds" << endl;
		tree.insert({ 5, 5 });
		cout << std::to_string(tree);
		assert(tree.has_children() == false);
		assert(tree.count_elements() == 1);

		cout << "insert (10, 5) and (20, 5) // within bounds" << endl;
		tree.insert({ 1, 6 });
		tree.insert({ 2, 8 });
		cout << std::to_string(tree);
		assert(tree.has_children() == true);
		cout << tree.count_elements();
		assert(tree.count_elements() == 3);

		std::srand(clock());
		while (getchar() != 'q')
		{
			clear();
			cout << "Elements per Child 1, Max Depth 3" << endl;

			auto p = Point<float>((std::rand() % 10), (std::rand() % 10) );
			cout << "insert " << std::to_string(p) << endl;
			tree.insert(p);
			cout << std::to_string(tree);
		}
		return 0;
	}

	int stringify()
	{
		cout << "Test : strinigfy" << endl;
		bool a = 1;
		int b =  2;
		long c = 3;
		Point<float> d(4.0f, 5.0f);
		Point<int> e(6, 7);
		std::shared_ptr<Point<int>> f = std::make_shared<Point<int>>(8, 9);
		std::weak_ptr<Point<int>> g = f;
		std::shared_ptr<Point<int>> h;
		std::weak_ptr<Point<int>> i;
		class {

		}anon;

		cout << "Bool : " << utils::to_debug_string(a) << endl;
		cout << "Int : " << utils::to_debug_string(b) << endl;
		cout << "Ptr : " << utils::to_debug_string(&b) << endl;
		cout << "Class : " << utils::to_debug_string(d) << endl;
		cout << "ClassPtr : " << utils::to_debug_string(&d) << endl;
		cout << "Shared : " << utils::to_debug_string(f) << endl;
		cout << "Weak : " << utils::to_debug_string(g) << endl;
		cout << "Shared_Null : " << utils::to_debug_string(h) << endl;
		cout << "Weak_Null : " << utils::to_debug_string(i) << endl;
		cout << "Anonym : " << utils::to_debug_string(anon) << endl;
		getchar();
		return 0;
	}

	static void clear() 
	{
		COORD topLeft = { 0, 0 };
		HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO screen;
		DWORD written;

		GetConsoleScreenBufferInfo(console, &screen);
		FillConsoleOutputCharacterA(
			console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
		);
		FillConsoleOutputAttribute(
			console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
			screen.dwSize.X * screen.dwSize.Y, topLeft, &written
		);
		SetConsoleCursorPosition(console, topLeft);
	}
}
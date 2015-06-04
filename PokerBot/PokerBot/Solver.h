#ifndef __SOLVER_H
#define __SOLVER_H

#include <string>

using namespace std;

class Solver {
public:

	Solver();

	void setTitle(string str);
	void solve();
private:

	string mTitle;
};

#endif
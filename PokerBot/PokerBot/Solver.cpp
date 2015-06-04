#include "Solver.h"

void Solver::setTitle(string str) {
	mTitle = str;
}

void Solver::solve() {
	while(true) {
		getScreenShot();
		parse();
		calculate();
		action();
	}
}

void Solver::getScreenShot() {

}

void Solver::parse() {

}

void Solver::calculate() {

}

void Solver::action() {

}
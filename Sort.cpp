#include "include/Sort.h"


bool IncreasingPerimeter(const Shape *a , const Shape *b){
	return a->perimeter() < b->perimeter();
}

bool DecreasingPerimeter(const Shape *a , const Shape *b){
	return a->perimeter() > b->perimeter();
}

bool IncreasingArea(const Shape *a , const Shape *b){
	return a->area() < b->area();
}

bool DecreasingArea(const Shape *a , const Shape *b){
	return a->area() > b->area();
}

bool IncreasingCompactness(const Shape *a, const Shape *b){
    return a->compactness() < b->compactness();
}

void Sort::sortByIncreasingPerimeter(std::list<Shape *> *shapeList){
	
	shapeList->sort(IncreasingPerimeter);
}

void Sort::sortByDecreasingPerimeter(std::list<Shape *> *shapeList){
	
	shapeList->sort(DecreasingPerimeter);
}

void Sort::sortByIncreasingArea(std::list<Shape *> *shapeList){
	
	shapeList->sort(IncreasingArea);
}

void Sort::sortByDecreasingArea(std::list<Shape *> *shapeList){
	
	shapeList->sort(DecreasingArea);
}

void Sort::sortByIncreasingCompactness(std::list<Shape *> *shapeList){

	shapeList->sort(IncreasingCompactness);
}



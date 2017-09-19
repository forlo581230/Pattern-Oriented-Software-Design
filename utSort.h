#ifndef EXP_H
#define EXP_H
#include "include/Shapes.h"
#include "include/Media.h"
#include "include/Sort.h"

using namespace std;

const double epsilon = 0.000001;
const vertex v1={0,0};
const vertex v2={12,0};
const vertex v3={0,12};

Circle cir(0,0,12);
Rectangle rect(0,0,12,12);
Triangle tri(v1,v2,v3);

TEST (Sort, sortByIncreasingPerimeter) {

	list<Shape *>shapes1;
	shapes1.push_back(&cir);
	shapes1.push_back(&rect);
	shapes1.push_back(&tri);
    Sort::sortByIncreasingPerimeter(&shapes1);

    double sort_ans[] = {tri.perimeter(), rect.perimeter(), cir.perimeter()};
    int index = 0;
    for(list<Shape *>::iterator it = shapes1.begin(); it != shapes1.end(); it++){
    
        ASSERT_NEAR(sort_ans[index++], (*it)->perimeter(), epsilon);

    }
}

TEST (Sort, sortByDecreasingPerimeter) {

	list<Shape *>shapes2;
	shapes2.push_back(&cir);
	shapes2.push_back(&rect);
	shapes2.push_back(&tri);
    Sort::sortByDecreasingPerimeter(&shapes2);

    double sort_ans[] = {cir.perimeter(), rect.perimeter(), tri.perimeter()};
    int index = 0;
    for(list<Shape *>::iterator it = shapes2.begin(); it != shapes2.end(); it++){
       
        ASSERT_NEAR(sort_ans[index++], (*it)->perimeter(), epsilon);
    }
}

TEST (Sort, sortByIncreasingArea) {

	list<Shape *>shapes3;
	shapes3.push_back(&cir);
	shapes3.push_back(&rect);
	shapes3.push_back(&tri);
    Sort::sortByIncreasingArea(&shapes3);

    double sort_ans[] = {tri.area(), rect.area(), cir.area()};
    int index = 0;
    for(list<Shape *>::iterator it = shapes3.begin(); it != shapes3.end(); it++){
    
        ASSERT_NEAR(sort_ans[index++], (*it)->area(), epsilon);
    }
}

TEST (Sort, sortByDecreasingArea) {

	list<Shape *>shapes4;
	shapes4.push_back(&cir);
	shapes4.push_back(&rect);
	shapes4.push_back(&tri);
    Sort::sortByDecreasingArea(&shapes4);

    double sort_ans[] = {cir.area(), rect.area(), tri.area()};
    int index = 0;
    for(list<Shape *>::iterator it = shapes4.begin(); it != shapes4.end(); it++){
    
        ASSERT_NEAR(sort_ans[index++], (*it)->area(), epsilon);
    }
}


TEST (Sort, sortByIncreasingCompactness) {

	list<Shape *>shapes5;
	shapes5.push_back(&cir);
	shapes5.push_back(&rect);
	shapes5.push_back(&tri);
    Sort::sortByIncreasingCompactness(&shapes5);
    
    double sort_ans[] = {tri.area()/tri.perimeter(), rect.area()/rect.perimeter(), cir.area()/cir.perimeter()};
    int index = 0;
    for(list<Shape *>::iterator it = shapes5.begin(); it != shapes5.end(); it++){
    
        ASSERT_NEAR(sort_ans[index++], (*it)->area() / (*it)->perimeter(), epsilon);
    }
}


#endif

#ifndef EXP_H
#define EXP_H
#include "include/Shapes.h"
#include "include/Media.h"
#include "include/Sort.h"

using namespace std;

const vertex v1={0,0};
const vertex v2={12,0};
const vertex v3={0,12};

Circle cir(0,0,12);
Rectangle rect(0,0,12,12);
Triangle tri(v1,v2,v3);

list<Shape *> init_data(){
    
    list<Shape *>shapes;
	shapes.push_back(&cir);
	shapes.push_back(&rect);
	shapes.push_back(&tri);

    return shapes;
}

TEST (Sort, sortByIncreasingPerimeter) {

    list<Shape *>shapes1 = init_data();
    Sort::sortByIncreasingPerimeter(&shapes1);

    Shape *sort_ans[3] ={&tri, &rect, &cir};
    int index = 0;
    for(list<Shape *>::iterator it = shapes1.begin(); it != shapes1.end(); it++){

        ASSERT_EQ(sort_ans[index++], (*it));
    }
}

TEST (Sort, sortByDecreasingPerimeter) {

    list<Shape *>shapes2 = init_data();
    Sort::sortByDecreasingPerimeter(&shapes2);

    Shape *sort_ans[3] = {&cir, &rect, &tri};
    int index = 0;
    for(list<Shape *>::iterator it = shapes2.begin(); it != shapes2.end(); it++){
       
        ASSERT_EQ(sort_ans[index++], (*it));
    }
}

TEST (Sort, sortByIncreasingArea) {

    list<Shape *>shapes3 = init_data();
    Sort::sortByIncreasingArea(&shapes3);

    Shape *sort_ans[3] = {&tri, &rect, &cir};
    int index = 0;
    for(list<Shape *>::iterator it = shapes3.begin(); it != shapes3.end(); it++){
    
        ASSERT_EQ(sort_ans[index++], (*it));
    }
}

TEST (Sort, sortByDecreasingArea) {

    list<Shape *>shapes4 = init_data();
    Sort::sortByDecreasingArea(&shapes4);

    Shape *sort_ans[3] = {&cir, &rect, &tri};
    int index = 0;
    for(list<Shape *>::iterator it = shapes4.begin(); it != shapes4.end(); it++){
    
        ASSERT_EQ(sort_ans[index++], (*it));
    }
}


TEST (Sort, sortByIncreasingCompactness) {

    list<Shape *>shapes5 = init_data();
    Sort::sortByIncreasingCompactness(&shapes5);
    
    Shape *sort_ans[3] = {&tri, &rect, &cir};
    int index = 0;
    for(list<Shape *>::iterator it = shapes5.begin(); it != shapes5.end(); it++){
    
        ASSERT_EQ(sort_ans[index++], (*it));
    }
}

#endif
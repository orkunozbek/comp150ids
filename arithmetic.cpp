// --------------------------------------------------------------
//
//                        arithmetic.cpp
//
//        Author: Noah Mendelsohn         
//   
//
//        Trivial implementations of the routines declared
//        in arithmetic.idl. These are for testing: they
//        just print messages.
//
//       Copyright: 2012 Noah Mendelsohn
//     
// --------------------------------------------------------------

// IMPORTANT! WE INCLUDE THE IDL FILE AS IT DEFINES THE INTERFACES
// TO THE FUNCTIONS WE'RE IMPLEMENTING. THIS MAKES SURE THE
// CODE HERE ACTUALLY MATCHES THE REMOTED INTERFACE

#include "arithmetic.idl"
#include <math.h>


int add(int x, int y) {
  return x+y;
}

int subtract(int x, int y) {
  return x-y;
}

int multiply(int x, int y) {
  return x*y;
}

int divide(int x, int y) {
  return x/y;
}

Student getStudent(int id){
  Student s;
  s.id = id;
  return s;
}

int studentAdd(Student s, Student t){
  return s.id + t.id;
}


int VertexAddXPos(Vertex x, Vertex y){
	return x.x + y.x;
}

int VertexAddYPos(Vertex x, Vertex y){
	return x.y + y.y;
}

Vertex createVertex(int x, int y){
	Vertex v;
	v.x = x;
	v.y = y;
	return v;
}

/*
Rectangle createRectangle(int x1, int y1, int x2, int y2){
	Rectangle r;
	Vertex v1; v1.x = x1; v1.y = y1;
	Vertex v2; v2.x = x2; v2.y = y2;
	r.corner1 = v1;
	r.corner2 = v2;
	return r;
}
*/

Rectangle createRectangle(Vertex x, Vertex y){
	Rectangle r1;
	r1.corner1 = x;
	r1.corner2 = y;
	return r1;
}

float rectangleCornerDistance(Rectangle r1){
	return sqrt(pow((r1.corner1.x - r1.corner2.x),2) + pow((r1.corner1.y - r1.corner2.y),2));
}

int retangleAdd(Rectangle r1, Rectangle r2){
	return r1.corner1.x + r2.corner1.x + r1.corner1.y + r1.corner1.y + r1.corner2.x + r2.corner2.x + r1.corner2.y + r2.corner2.y;
}





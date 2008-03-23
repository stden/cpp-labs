#include "StdAfx.h"
#include "MyMVT.h"

void MyMVT::linkPPP( Point *a, Point *b, Point *c ) {
	figure.lineAdd( a->a_, b->a_ );
	figure.lineAdd( b->a_, c->a_ );
	figure.lineAdd( c->a_, a->a_ );
}

void MyMVT::linkPP( Point *a, Point *b ) {
	figure.lineAdd( a->a_, b->a_ );
}

void MyMVT::linkPS( Point *a, Segment *b ) {
	figure.lineAdd( a->a_, b->a_ );
	figure.lineAdd( a->a_, b->b_ );
	figure.lineAdd( b->a_, b->b_ );
}

void MyMVT::linkSS( Segment *a, Segment *b ) {
	figure.lineAdd( a->a_, b->a_ );
	figure.lineAdd( a->b_, b->b_ );
	figure.lineAdd( a->a_, a->b_ );
	figure.lineAdd( b->a_, b->b_ );
}

/* void MyMVT::linkSSX( GFin *a, GFin *b ) {
	figure.lineAdd( a->a_, b->b_ );
	figure.lineAdd( a->b_, b->a_ );
	figure.lineAdd( a->a_, a->b_ );
	figure.lineAdd( b->a_, b->b_ );
} */

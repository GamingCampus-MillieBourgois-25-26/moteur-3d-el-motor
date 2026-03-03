#include "Shapes.hpp"

void PShape::Create(JPH::Ref<JPH::Shape> mShape) {
	mShape = JPH::Ref<JPH::Shape>(mShape);
}
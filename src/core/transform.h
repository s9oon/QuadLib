#pragma once

struct Vec2 {
	float x, y;
};

struct Transform {
	Vec2 position;
	float rotation;
	Transform(Vec2 position, float rotation) : position(position), rotation(rotation) {};
};
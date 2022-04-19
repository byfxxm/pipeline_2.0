#pragma once
#include "array_nd.h"

PIPELINE_API extern const int kAxesNum;

struct Code {
	enum class Id {
		kMove,
		kLine,
		kArc,
	};

	virtual ~Code() = default;

	Id id;
};

struct Move :public Code {
	Move() {
		id = Id::kMove;
	}

	ArrayNd<double, 1> end{ kAxesNum };
};

struct Line :public Code {
	Line() {
		id = Id::kMove;
	}

	ArrayNd<double, 1> end{ kAxesNum };
};

struct Arc :public Code {
	Arc() {
		id = Id::kArc;
	}

	ArrayNd<double, 1> end{ kAxesNum };
	ArrayNd<double, 1> center{ kAxesNum };
};
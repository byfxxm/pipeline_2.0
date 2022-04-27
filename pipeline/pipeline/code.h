#pragma once
#include "array_nd.h"
#include "pipeline.h"

namespace pipeline {
	PIPELINE_API extern const size_t kAxesNum;
	class AxesDouble : public ArrayNd<double, 1> {
	public:
		AxesDouble(size_t axes_num = kAxesNum) :ArrayNd<double, 1>(axes_num) {}
	};

	enum class CodeId {
		kMove,
		kLine,
		kArc,
	};

	class Code {
	public:
		Code(CodeId id) :id_(id) {}
		virtual ~Code() = default;
		auto& Id() {
			return id_;
		}

	private:
		CodeId id_;
	};

	class Move : public Code {
	public:
		Move(AxesDouble&& end) :Code(CodeId::kMove), end_(end) {}
		auto& End() {
			return end_;
		}

	private:
		AxesDouble end_;
	};

	class Line : public Code {
	public:
		Line(AxesDouble&& end) :Code(CodeId::kLine), end_(end) {}
		auto& End() {
			return end_;
		}

	private:
		AxesDouble end_;
	};

	class Arc : public Code {
	public:
		Arc(AxesDouble&& end, AxesDouble&& center) :Code(CodeId::kArc), end_(end), center_(center) {}
		auto& End() {
			return end_;
		}
		auto& Center() {
			return center_;
		}

	private:
		AxesDouble end_;
		AxesDouble center_;
	};
}
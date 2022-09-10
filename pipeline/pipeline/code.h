#pragma once
#include "array_nd.h"

namespace pipeline {
	PIPELINE_API extern size_t kAxesNum;

	class AxesDouble {
	public:
		AxesDouble(size_t axes_num = kAxesNum) : base_(axes_num) {}

		double& operator[](size_t index) {
			return base_[index];
		}

		byfxxm::ArrayNd<double, 1> base_;
	};

	enum class CodeId {
		kMove,
		kLine,
		kArc,
	};

	class Code {
	public:
		Code(CodeId id) : id_(id) {}
		virtual ~Code() = default;

		auto& Id() {
			return id_;
		}

	private:
		CodeId id_;
	};

	class Move : public Code {
	public:
		Move(AxesDouble&& end) : Code(CodeId::kMove), end_(std::move(end)) {}

		auto& End() {
			return end_;
		}

	private:
		AxesDouble end_;
	};

	class Line : public Code {
	public:
		Line(AxesDouble&& end) : Code(CodeId::kLine), end_(std::move(end)) {}

		auto& End() {
			return end_;
		}

	private:
		AxesDouble end_;
	};

	class Arc : public Code {
	public:
		Arc(AxesDouble&& end, AxesDouble&& center) : Code(CodeId::kArc), end_(std::move(end)), center_(std::move(center)) {}

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

#pragma once

namespace gworker {
	class GworkerImp;
	class GProcesserDerive :public gparser::GProcesser {
	public:
		GProcesserDerive(GworkerImp&);
		virtual void G0(size_t, gparser::Tag*, size_t) override;
		virtual void G1(size_t, gparser::Tag*, size_t) override;
		virtual void G2(size_t, gparser::Tag*, size_t) override;
		virtual void G3(size_t, gparser::Tag*, size_t) override;

	private:
		void Print(size_t, gparser::Tag*, size_t);
		pipeline::AxesDouble TagsToAxesDouble(gparser::Tag*, size_t);

	private:
		GworkerImp& gworker_;
	};
}
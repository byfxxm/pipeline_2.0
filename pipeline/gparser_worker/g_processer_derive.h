#pragma once

GWORKER_BEGIN
class GparserWorkerImp;
class GProcesserDerive : public gparser::GProcesser {
public:
	GProcesserDerive(GparserWorkerImp&);
	virtual void G0(size_t, gparser::Tag*, size_t) override;
	virtual void G1(size_t, gparser::Tag*, size_t) override;
	virtual void G2(size_t, gparser::Tag*, size_t) override;
	virtual void G3(size_t, gparser::Tag*, size_t) override;

private:
	void Print(size_t, gparser::Tag*, size_t);

private:
	GparserWorkerImp& gworker_;
};

GWORKER_END
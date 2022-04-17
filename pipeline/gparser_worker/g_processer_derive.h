#pragma once

class GProcesserDerive : public GProcesser {
public:
	virtual void G0(int, Tag*, int) override;
	virtual void G1(int, Tag*, int) override;
	virtual void G2(int, Tag*, int) override;
	virtual void G3(int, Tag*, int) override;
};
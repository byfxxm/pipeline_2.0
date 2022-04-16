#pragma once

class GparserWorker :public Worker {
public:
	virtual ~GparserWorker() override = default;
	virtual void Do(Code*) override;
};
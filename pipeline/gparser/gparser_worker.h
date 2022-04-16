#pragma once

class GparserWorker :public Worker {
public:
	virtual ~GparserWorker() override = default;
	virtual void Do(Code*) override;
	bool LoadFile(const char*);
	void UnloadFile();

private:
	std::ifstream fin_;
};
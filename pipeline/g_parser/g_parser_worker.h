#pragma once

class GParserWorker :public Worker {
public:
	virtual void Do(Code*) override;
};
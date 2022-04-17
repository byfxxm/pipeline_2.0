#pragma once

class GReader;
class GparserWorker :public Worker {
public:
	virtual ~GparserWorker() override = default;
	virtual void Do(Code*) override;
	bool LoadFile(const char*);
	void UnloadFile();
	void SetGProcesser(GProcesser*);

private:
	GReader* reader_{ nullptr };
	GProcesser* g_processer_{ nullptr };
};
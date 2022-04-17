#include "pch.h"
#include "gparser.h"
#include "gparser_worker.h"
#include "gparser_imp.h"

void GparserWorker::Do(Code*) {
	try {
		while (1) {
			auto line_op = reader_->NextLine();
			if (!line_op.has_value())
				break;

			auto line = line_op.value();
			for (const auto& it : line) {
				if (it.token == Token::kG) {
					switch ((int)it.value) {
					case 0:
						g_processer_ && (g_processer_->G0(line.data(), line.size()), 0);
						break;
					case 1:
						g_processer_ && (g_processer_->G1(line.data(), line.size()), 0);
						break;
					case 2:
						g_processer_ && (g_processer_->G2(line.data(), line.size()), 0);
						break;
					case 3:
						g_processer_ && (g_processer_->G3(line.data(), line.size()), 0);
						break;
					default:
						break;
					}
				}
			}
		}
	}
	catch (const char* err) {
		std::cout << err << std::endl;
	}

	Write(nullptr);
}

bool GparserWorker::LoadFile(const char* file) {
	std::filesystem::path path(file);
	if (!std::filesystem::is_regular_file(path))
		return false;

	delete reader_;
	reader_ = new GReader(path);
	return true;
}

void GparserWorker::UnloadFile() {
	delete reader_;
	reader_ = nullptr;
}

void GparserWorker::SetGProcesser(GProcesser* proc) {
	g_processer_ = proc;
}
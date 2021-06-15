#ifndef _SOJ_JUDGER_HEADER_
#define _SOJ_JUDGER_HEADER_

#include "env.h"
#include "run.h"
#include "config.h"
#include "utility.h"

namespace SOJ_JUDGER_NAMESPACE {

#define SOJ_CURRENT_CLASS Judger
	class Judger {
	private:
		int problemID;
		String main_path, work_path, data_path, result_path;
		int tot_time, max_memory, tot_score;

		String details;
		Config config;
	public:

		virtual void judge() {
		}

		void init(int argc, char * argv[], bool ismain = false) {
			main_path = SOJ_WORK_PATH;
			work_path = main_path + "/work";
			result_path = SOJ_RESULT_PATH;

			config.loadFromFile(work_path + "/submission.conf");
			problemID = config["problem_id"].getInt();
			data_path = (SOJ_DATA_PATH "/") + config["problem_id"].get();
			config.loadFromFile(data_path + "/problem.conf");

			if (ismain) {
				copyFile(data_path + "/require/*", work_path);

				if (config["use_builtin_judger"] == "on") {
					auto pt = SOJ_WORK_PATH "/builtin/judger/judger";
					config["judger"].set(pt);
				} else {
					config["judger"].set(data_path + "/judger");
				}
			} else {
				if (config.count("use_builtin_checker")) {
					auto pt = main_path + "/builtin/checker/";
					pt += config["use_builtin_checker"];
					config["checker"] = pt;
				} else {
					config["checker"] = data_path + "/chk";
				}
				config["validator"] = data_path + "/val";
			}
		}

	} ;
#undef SOJ_CURRENT_CLASS

}

#endif

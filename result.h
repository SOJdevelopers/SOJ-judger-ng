#ifndef _SOJ_JUDGER_RESULT_HEADER_
#define _SOJ_JUDGER_RESULT_HEADER_

#include "env.h"
#include "utility.h"
#include <cstdio>
#include <cmath>
#include <cassert>
#include <cstring>

namespace SOJ_JUDGER_NAMESPACE {

	const int RS_SPJ = 0x0010;
	const int RS_HACK = 0x0020;
	const int RS_AC = 0;
	const int RS_WA = 1;
	const int RS_RE = 2;
	const int RS_MLE = 3;
	const int RS_TLE = 4;
	const int RS_OLE = 5;
	const int RS_DGS = 6;
	const int RS_JGF = 7;

#define SOJ_CURRENT_CLASS Result
	class Result {
	private:
		int type, ust, usm;
	public:
		SOJ_GETSET(type, Type);
		SOJ_GETSET(ust, UsedTime);
		SOJ_GETSET(usm, UsedMemory);
		virtual void failedResult() {
			setType(RS_JGF);
			setUsedTime(-1);
			setUsedMemory(-1);
		}
		virtual bool loadFromFile(const String &) = 0;
	} ;
#undef SOJ_CURRENT_CLASS

#define SOJ_CURRENT_CLASS RunResult
	class RunResult : public Result {
	private:
		int exitcode;
	public:
		SOJ_GETSET(exitcode, ExitCode);

		virtual void failedResult() {
			Result::failedResult();
			setExitCode(-1);
		}

		virtual bool loadFromFile(const String & filename) {
			FILE * fres = fopen(filename.c_str(), "r");
			if (fres != NULL) {
				int t, ut, um, e;
				int cnt = fscanf(fres, "%d%d%d%d", &t, &ut, &um, &e);
				if (cnt == 4) {
					fclose(fres);
					setType(t);
					setUsedTime(ut);
					setUsedMemory(um);
					setExitCode(e);
					return true;
				}
			}
			failedResult();
			return false;
		}
	} ;
#undef SOJ_CURRENT_CLASS

#define SOJ_CURRENT_CLASS RunCheckerResult
	class RunCheckerResult : public RunResult {
	private:
		int scr;
		String info;
	public:
		SOJ_GETSET(scr, Score);
		SOJ_GETSET(info, Info);

		virtual void failedResult() {
			RunResult::failedResult();
			setScore(0);
			setInfo(IS_JUDGER_JGF);
		}
		virtual bool loadFromFile(const String & filename) {
			if (getType() != RS_AC) {
				setScore(0);
			} else {
				FILE * fres = fopen(filename.c_str(), "r");
				static char type[21];
				if (fres == NULL || fscanf(fres, "%20s", type) != 1) {
					failedResult();
					return false;
				}
				if (strcmp(type, "ok") == 0) {
					setScore(100);
				} else if (strcmp(type, "points") == 0) {
					double d;
					if (fscanf(fres, "%lf", &d) != 1) {
						failedResult();
						return false;
					} else {
						setScore((int) floor(100 * d + 0.5));
					}
				} else {
					setScore(0);
				}
				fclose(fres);
			}
			setInfo(filePreview(filename, 256));
			return true;
		}
	} ;
#undef SOJ_CURRENT_CLASS

#define SOJ_CURRENT_CLASS RunValidatorResult
	class RunValidatorResult : public RunResult {
	private:
		bool succeeded;
		String info;
	public:
		SOJ_GETSET(succeeded, Succeeded);
		SOJ_GETSET(info, Info);

		virtual bool loadFromFile(const String & filename) {
			fprintf(stderr, "???\n");
			assert(0);
		}
		virtual void failedResult() {
			RunResult::failedResult();
			setSucceeded(0);
			setInfo(IS_VAL_JGF);
		}
	} ;
#undef SOJ_CURRENT_CLASS

#define SOJ_CURRENT_CLASS RunCompilerResult
	class RunCompilerResult : public RunResult {
	private:
		bool succeeded;
		String info;
	public:
		SOJ_GETSET(succeeded, Succeeded);
		SOJ_GETSET(info, Info);

		virtual bool loadFromFile(const String & filename) {
			fprintf(stderr, "???\n");
			assert(0);
		}
		virtual void failedResult() {
			RunResult::failedResult();
			setSucceeded(0);
			setInfo(IS_COMP_FAILED);
		}
	} ;
#undef SOJ_CURRENT_CLASS

	struct RunSimpleInteractionResult {
		RunResult res;
		RunCheckerResult ires;
	} ;

}

#endif

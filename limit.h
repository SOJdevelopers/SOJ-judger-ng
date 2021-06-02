#ifndef _SOJ_JUDGER_LIMIT_HEADER_
#define _SOJ_JUDGER_LIMIT_HEADER_

#include "env.h"

namespace SOJ_JUDGER_NAMESPACE {
#define SOJ_CURRENT_CLASS RunLimit
	class RunLimit {
	private:
		int time;     // time limit (millisecond) (strict)
		int realtime; // time limit (millisecond)
		int memory;   // memory limit (KiB)
		int output;   // output limit (KiB)
	public:
		RunLimit() :
			time(0), realtime(0), memory(0), output(0) { }
		explicit RunLimit(int _t, int _m, int _o) :
			time(_t), realtime(0), memory(_m), output(_o) { }
		explicit RunLimit(int _t, int _rt, int _m, int _o) :
			time(_t), realtime(_rt), memory(_m), output(_o) { }
		SOJ_GETSET(time, Time);
		SOJ_GETSET(realtime, Realtime);
		SOJ_GETSET(memory, Memory);
		SOJ_GETSET(output, Output);
		const static RunLimit DEFAULT   ;
		const static RunLimit JUDGER    ;
		const static RunLimit CHECKER   ;
		const static RunLimit INTERACTOR;
		const static RunLimit VALIDATOR ;
		const static RunLimit MARKER    ;
		const static RunLimit COMPILER  ;
	} ;
#undef SOJ_CURRENT_CLASS
	const RunLimit RunLimit::DEFAULT    = RunLimit(1000, 1 << 18, 1 << 16);
	const RunLimit RunLimit::JUDGER     = RunLimit(600000, 1 << 20, 1 << 17);
	const RunLimit RunLimit::CHECKER    = RunLimit(5000, 1 << 18, 1 << 16);
	const RunLimit RunLimit::INTERACTOR = RunLimit(5000, 1 << 18, 1 << 16);
	const RunLimit RunLimit::VALIDATOR  = RunLimit(5000, 1 << 18, 1 << 16);
	const RunLimit RunLimit::MARKER     = RunLimit(5000, 1 << 18, 1 << 16);
	const RunLimit RunLimit::COMPILER   = RunLimit(15000, 1 << 19, 1 << 16);
}
#endif

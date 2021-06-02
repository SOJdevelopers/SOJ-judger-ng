#ifndef _SOJ_JUDGER_INFO_HEADER_
#define _SOJ_JUDGER_INFO_HEADER_

#include "env.h"

namespace SOJ_JUDGER_NAMESPACE {
#define SOJ_CURRENT_CLASS PointInfo
	class PointInfo {
	private:
		int num, scr, ust, usm;
		String status, in, out, res;
	public:
		PointInfo(int n, int sc, int ut, int um,
				  const String & st, const String & i,
				  const String & o, const String & r) :
			num(n), scr(sc), ust(ut), usm(um),
			status(st), in(i), out(o), res(r) {
			}
		void autoComplete() {
			if (status == IS_DEFAULT) {
				if (scr == 0) {
					status = IS_WRONGANSWER;
				} else if (scr == 100) {
					status = IS_ACCEPTED;
				} else {
					status = IS_ACCEPTABLE;
				}
			}
		}
		SOJ_GETSET(num, Number);
		SOJ_GETSET(scr, Score);
		SOJ_GETSET(ust, UsedTime);
		SOJ_GETSET(usm, UsedMemory);
		SOJ_GETSET(status, Status);
		SOJ_GETSET(in, Input);
		SOJ_GETSET(out, Output);
		SOJ_GETSET(res, Result);
	} ;
#undef SOJ_CURRENT_CLASS
#define SOJ_CURRENT_CLASS CustomTestInfo
	class CustomTestInfo  {
	private:
		int ust, usm;
		String status, extra, out;

	public:
		CustomTestInfo(int ut, int um, const String & s,
					   const String & e, const String & o) :
			ust(ut), usm(um), status(s), extra(e), out(o) {
			}
		SOJ_GETSET(ust, UsedTime);
		SOJ_GETSET(usm, UsedMemory);
		SOJ_GETSET(status, Status);
		SOJ_GETSET(extra, Extra);
		SOJ_GETSET(out, Output);
	} ;
#undef SOJ_CURRENT_CLASS

}
#endif

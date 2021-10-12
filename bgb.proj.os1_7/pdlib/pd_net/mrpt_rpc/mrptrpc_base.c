#include <pdlib.h>
#include <pdnet.h>

int MRPTRPC_Init()
{
	MRPT_DeclareTag("mrptrpc/integer", 0, 0, MRPT_CLASS_INTEGER);
	MRPT_DeclareTag("mrptrpc/boolean", MRPT_FLAG_FIXEDLENGTH,
		1, MRPT_CLASS_INTEGER);
	MRPT_DeclareTag("mrptrpc/string", 0, 0, MRPT_CLASS_STRING);
	MRPT_DeclareTag("mrptrpc/float", 0, 0, MRPT_CLASS_FLOAT);
	MRPT_DeclareTag("mrptrpc/data", 0, 0, MRPT_CLASS_RAW);
	MRPT_DeclareTag("mrptrpc/date", 0, 0, MRPT_CLASS_STRING);
	MRPT_DeclareTag("mrptrpc/symbol", 0, 0, MRPT_CLASS_STRING);
	MRPT_DeclareTag("mrptrpc/character", MRPT_FLAG_FIXEDLENGTH,
		2, MRPT_CLASS_INTEGER);

	MRPT_DeclareTag("mrptrpc/array", MRPT_FLAG_COMPOUND, 0, MRPT_CLASS_RAW);
	MRPT_DeclareTag("mrptrpc/values", MRPT_FLAG_COMPOUND, 0, MRPT_CLASS_RAW);
	MRPT_DeclareTag("mrptrpc/terminal", MRPT_FLAG_COMPOUND, 0, MRPT_CLASS_RAW);
	MRPT_DeclareTag("mrptrpc/struct", MRPT_FLAG_COMPOUND, 0, MRPT_CLASS_RAW);
	MRPT_DeclareTag("mrptrpc/member", MRPT_FLAG_COMPOUND, 0, MRPT_CLASS_RAW);
	MRPT_DeclareTag("mrptrpc/vector", MRPT_FLAG_COMPOUND, 0, MRPT_CLASS_RAW);
	MRPT_DeclareTag("mrptrpc/link", MRPT_FLAG_COMPOUND, 0, MRPT_CLASS_RAW);

	MRPT_DeclareTag("mrptrpc/call", MRPT_FLAG_COMPOUND, 0, MRPT_CLASS_RAW);
	MRPT_DeclareTag("mrptrpc/return", MRPT_FLAG_COMPOUND, 0, MRPT_CLASS_RAW);
	MRPT_DeclareTag("mrptrpc/error", MRPT_FLAG_COMPOUND, 0, MRPT_CLASS_RAW);
	MRPT_DeclareTag("mrptrpc/pass", MRPT_FLAG_COMPOUND, 0, MRPT_CLASS_RAW);
}

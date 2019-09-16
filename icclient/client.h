#ifndef ICCLIENT_H
#define ICCLIENT_H

#ifdef __cplusplus
extern "C" {
#endif

	bool icclient_init(const char *url);
	void icclient_cleanup();

#ifdef __cplusplus
}
#endif

#endif // ICCLIENT_H

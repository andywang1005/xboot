#ifndef __ETHERNET_H__
#define __ETHERNET_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <xboot.h>

struct ethernet_t
{
	char * name;

	int (*getbl)(struct ethernet_t * eth);

	void * priv;
};

struct ethernet_t * search_ethernet(const char * name);
struct ethernet_t * search_first_ethernet(void);
bool_t register_ethernet(struct device_t ** device, struct ethernet_t * eth);
bool_t unregister_ethernet(struct ethernet_t * eth);

#ifdef __cplusplus
}
#endif

#endif /* __ETHERNET_H__ */

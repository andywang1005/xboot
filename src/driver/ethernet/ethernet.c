/*
 * driver/ethernet/ethernet.c
 *
 * Copyright(c) 2007-2018 Jianjun Jiang <8192542@qq.com>
 * Official site: http://xboot.org
 * Mobile phone: +86-18665388956
 * QQ: 8192542
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#include <xboot.h>
#include <ethernet/ethernet.h>

struct ethernet_t * search_ethernet(const char * name)
{
	struct device_t * dev;

	dev = search_device(name, DEVICE_TYPE_ETHERNET);
	if(!dev)
		return NULL;
	return (struct ethernet_t *)dev->priv;
}

struct ethernet_t * search_first_ethernet(void)
{
	struct device_t * dev;

	dev = search_first_device(DEVICE_TYPE_ETHERNET);
	if(!dev)
		return NULL;
	return (struct ethernet_t *)dev->priv;
}

bool_t register_ethernet(struct device_t ** device, struct ethernet_t * eth)
{
	struct device_t * dev;

	if(!eth || !eth->name)
		return FALSE;

	dev = malloc(sizeof(struct device_t));
	if(!dev)
		return FALSE;

	dev->name = strdup(eth->name);
	dev->type = DEVICE_TYPE_ETHERNET;
	dev->priv = eth;
	dev->kobj = kobj_alloc_directory(dev->name);
/*	kobj_add_regular(dev->kobj, "width", ethernet_read_width, NULL, eth);
	kobj_add_regular(dev->kobj, "height", ethernet_read_height, NULL, eth);
	kobj_add_regular(dev->kobj, "pwidth", ethernet_read_pwidth, NULL, eth);
	kobj_add_regular(dev->kobj, "pheight", ethernet_read_pheight, NULL, eth);
	kobj_add_regular(dev->kobj, "bpp", ethernet_read_bpp, NULL, eth);
	kobj_add_regular(dev->kobj, "brightness", ethernet_read_brightness, ethernet_write_brightness, eth);
	kobj_add_regular(dev->kobj, "max_brightness", ethernet_read_max_brightness, NULL, eth);*/

	if(!register_device(dev))
	{
		kobj_remove_self(dev->kobj);
		free(dev->name);
		free(dev);
		return FALSE;
	}

	if(device)
		*device = dev;
	return TRUE;
}

bool_t unregister_ethernet(struct ethernet_t * eth)
{
	struct device_t * dev;
	struct ethernet_t * driver;

	if(!eth || !eth->name)
		return FALSE;

	dev = search_device(eth->name, DEVICE_TYPE_ETHERNET);
	if(!dev)
		return FALSE;

	if(!unregister_device(dev))
		return FALSE;

	driver = (struct ethernet_t *)(dev->driver);
	if(driver)
	{
/*		if(driver->setbl)
			driver->setbl(driver, 0);*/
	}

	kobj_remove_self(dev->kobj);
	free(dev->name);
	free(dev);

	return TRUE;
}

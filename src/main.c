/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

//#include <zephyr/zephyr.h>
#include <zephyr/device.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   4000

/* The devicetree node identifier for the "led0" alias. */
//#define LED0_NODE DT_ALIAS(led0)

/*
 * A build error on this line means your board is unsupported.
 * See the sample documentation for information on how to fix this.
 */
//static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

static const struct device *gpio_ct_dev = DEVICE_DT_GET(DT_NODELABEL(gpiob));

void main(void)
{
	int ret;

	if (!device_is_ready(gpio_ct_dev)) {
		return;
	}

	ret = gpio_pin_configure(gpio_ct_dev, 0, GPIO_OUTPUT_ACTIVE);

	while (1) {
		ret = gpio_pin_set_raw(gpio_ct_dev, 0, 1);
		if (ret < 0) {
			return;
		}
		k_msleep(SLEEP_TIME_MS);
		ret = gpio_pin_set_raw(gpio_ct_dev, 0, 0);
		if (ret < 0) {
			return;
		}
		k_msleep(SLEEP_TIME_MS);
	}
}

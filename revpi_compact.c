/*
 * revpi_compact.c - RevPi Compact specific handling
 *
 * Copyright (C) 2017 KUNBUS GmbH
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License (version 2) as
 * published by the Free Software Foundation.
 */

#include <linux/kthread.h>
#include "project.h"
#include "common_define.h"
#include "ModGateComMain.h"
#include "piControlMain.h"

int revpi_compact_poll(void *data)
{
	while (!kthread_should_stop()) {
		schedule();
	}

	return 0;
}

int revpi_compact_init(void)
{
	struct sched_param param;

	piDev_g.pIoThread = kthread_run(&revpi_compact_poll, NULL, "revpi_compact_poll");
	if (IS_ERR(piDev_g.pIoThread)) {
		pr_err("kthread_run(io) failed\n");
		return PTR_ERR(piDev_g.pIoThread);
	}
	param.sched_priority = RT_PRIO_BRIDGE;
	sched_setscheduler(piDev_g.pIoThread, SCHED_FIFO, &param);

	return 0;
}

void revpi_compact_fini(void)
{
	if (!IS_ERR_OR_NULL(piDev_g.pIoThread))
		kthread_stop(piDev_g.pIoThread);
}

/*
 * Copyright (C) 2017 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     examples
 * @{
 *
 * @file
 * @brief       Example for demonstrating SAUL and the SAUL registry
 *
 * @author      Hauke Petersen <hauke.petersen@fu-berlin.de>
 *
 * @}
 */

#include <stdio.h>
#include <stdlib.h>

#include "shell.h"
#include "shell_commands.h"
#include "saul.h"
#include "saul_reg.h"
#include "xtimer.h"

char stack[THREAD_STACKSIZE_MAIN];
static uint16_t thres = 1000;

static int check_periph(int argc, char **argv) {
    (void)argc;
    (void)argv;
    
    saul_reg_t *led0, *led1, *led2, *sensor;

    led0 = saul_reg_find_nth(0);
    led1 = saul_reg_find_nth(1);
    led2 = saul_reg_find_nth(2);
    if (led0 == NULL || led1 == NULL || led2 == NULL) {
        puts("Cannot find LED");
        return -ENODEV;
    }

    sensor = saul_reg_find_type(SAUL_SENSE_COLOR);
    if (sensor == NULL) {
        puts("Cannot find sensor");
        return -ENODEV;
    }

    puts("LED and SENSOR found!");
    return 0;
}

static int set_threshold(int argc, char **argv) {
    if (argc > 1)
        thres = atoi(argv[1]);

    return 0;
}

const shell_command_t shell_commands[] = {
    {"sensor-check", "Check LED and Light sensor", check_periph},
    {"set-threshold", "Set threshold to turn LED on/off", set_threshold},
    { NULL, NULL, NULL }
};

void *light_ops(void *arg)
{
    (void) arg;
    saul_reg_t *led0, *led1, *led2, *sensor;
    phydat_t res;

    led0 = saul_reg_find_nth(0);  /* Red */
    led1 = saul_reg_find_nth(1);  /* Green */
    led2 = saul_reg_find_nth(2);  /* Blue */
    sensor = saul_reg_find_type(SAUL_SENSE_COLOR);

    while (1) {
        int dim = saul_reg_read(sensor, &res);
        (void) dim;
        printf("R: %d\tG: %d\tB:%d\n", res.val[0], res.val[1], res.val[2]);

        phydat_t res_led;
        if (res.val[0] > thres)
            res_led.val[0] = 1;
        else
            res_led.val[0] = 0;
        saul_reg_write(led0, &res_led);

        if (res.val[1] > thres)
            res_led.val[0] = 1;
        else
            res_led.val[0] = 0;
        saul_reg_write(led1, &res_led);

        if (res.val[2] > thres)
            res_led.val[0] = 1;
        else
            res_led.val[0] = 0;
        saul_reg_write(led2, &res_led);

        xtimer_sleep(2);
    }

    return NULL;
}

int main(void)
{
    puts("Welcome to RIOT!\n");
    puts("Type `help` for help, type `saul` to see all SAUL devices\n");

    kernel_pid_t pid = thread_create(stack, sizeof(stack),
                                     THREAD_PRIORITY_MAIN - 1,
                                     THREAD_CREATE_STACKTEST,
                                     light_ops, NULL,
                                     "light_ops");
    (void) pid;

    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run(shell_commands, line_buf, SHELL_DEFAULT_BUFSIZE);

    return 0;
}

// vim:ts=4:sw=4:expandtab
#include "i3status.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <yajl/yajl_gen.h>
#include <yajl/yajl_version.h>


static char *apply_pomodoro_format(const char *fmt, char *outwalk, int pomo_minutes, int pomo_seconds) {
    const char *walk = fmt;

    for (; *walk != '\0'; walk++) {
        if (*walk != '%') {
            *(outwalk++) = *walk;
            continue;
        }
        if (BEGINS_WITH(walk + 1, "%")) {
            outwalk += sprintf(outwalk, "%s", pct_mark);
            walk += strlen("%");
        }
        if (BEGINS_WITH(walk + 1, "minutes")) {
            if (pomo_minutes < 10) outwalk += sprintf(outwalk, "0%d", pomo_minutes);
            else outwalk += sprintf(outwalk, "%d", pomo_minutes);
            walk += strlen("minutes");
        }
        if (BEGINS_WITH(walk + 1, "seconds")) {
            if (pomo_seconds < 10) outwalk += sprintf(outwalk, "0%d", pomo_seconds);
            else outwalk += sprintf(outwalk, "%d", pomo_seconds);
            walk += strlen("seconds");
        }
    }
    return outwalk;
}

void print_pomodoro(yajl_gen json_gen, char *buffer, const char *format, const char *format_pomo, const char *format_break) {

    bool colorful_output = true;
    char *outwalk = buffer;

    // TODO: put your path to pomodoro files here
    char *path = "/home/anton/programming/i3status/plugins/pomodoro/";

	// read mode
    char mode_filename[256];
    sprintf(mode_filename, "%smode", path);
	int mode = read_number_from_file(mode_filename);

    const char *selected_format = format_pomo;

    if (mode == 0) {
        selected_format = format;
    }
    else if (mode == 1) {
        selected_format = format_pomo;
        START_COLOR("color_degraded");
    }
    else if (mode == 2) {
        selected_format = format_break;
        START_COLOR("color_good");
    }

	// read minutes
    char minutes_filename[256];
    sprintf(minutes_filename, "%sminutes", path);
	int minutes = read_number_from_file(minutes_filename);

	// read seconds
    char seconds_filename[256];
    sprintf(seconds_filename, "%sseconds", path);
	int seconds = read_number_from_file(seconds_filename);

    //int minutes = 25, seconds = 0;

	// sprintf(buffer, "%d", percentage);
    outwalk = apply_pomodoro_format(selected_format, outwalk, minutes, seconds);

    if (colorful_output)
        END_COLOR;

    *outwalk = '\0';
    OUTPUT_FULL_TEXT(buffer);

    return;
}

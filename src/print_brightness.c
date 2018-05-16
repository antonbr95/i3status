// vim:ts=4:sw=4:expandtab
#include "i3status.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <yajl/yajl_gen.h>
#include <yajl/yajl_version.h>

/*
	read integer of max. 5 decimal digits
*/
int read_number_from_file(char * filename){
	
    FILE *f = fopen(filename, "r");
	char number_str[5];
	fgets(number_str, 5, f);
	return atoi(number_str);
}

static char *apply_brightness_format(const char *fmt, char *outwalk, int ibrightness) {
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
        if (BEGINS_WITH(walk + 1, "brightness")) {
            outwalk += sprintf(outwalk, "%d%s", ibrightness, pct_mark);
            walk += strlen("brightness");
        }
    }
    return outwalk;
}

void print_brightness(yajl_gen json_gen, char *buffer, const char *format) {
    char *outwalk = buffer;

    const char *selected_format = format;
    bool colorful_output = false;

    // TODO: put your path to brightness files here
    char *path = "/sys/class/backlight/intel_backlight/";

	// read current brightness
    char brightness_filename[256];
    sprintf(brightness_filename, "%sbrightness", path);
	int brightness = read_number_from_file(brightness_filename);

	// read max brightness
	int max_brightness = read_number_from_file("/sys/class/backlight/intel_backlight/max_brightness");

	// percentage
	int percentage = brightness * 100 / max_brightness;

	// sprintf(buffer, "%d", percentage);
    outwalk = apply_brightness_format(selected_format, outwalk, percentage);

    if (colorful_output)
        END_COLOR;

    *outwalk = '\0';
    OUTPUT_FULL_TEXT(buffer);

    return;
}

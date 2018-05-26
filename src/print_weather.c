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
void read_string_from_file(char * filename, char * out){
	
    FILE *f = fopen(filename, "r");
    char str[256];
    fgets(str, 256, f);
    fclose(f);
    sprintf(out, str);
}

static char *apply_weather_format(const char *fmt, char *outwalk, char * day, char * icon, 
                                  char * temperature, char * weather_string) {
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
        if (BEGINS_WITH(walk + 1, "day")) {
            outwalk += sprintf(outwalk, "%s", day);
            walk += strlen("day");
        }
        if (BEGINS_WITH(walk + 1, "icon")) {
            outwalk += sprintf(outwalk, "%s", icon);
            walk += strlen("icon");
        }
        if (BEGINS_WITH(walk + 1, "temperature")) {
            outwalk += sprintf(outwalk, "%s", temperature);
            walk += strlen("temperature");
        }
        if (BEGINS_WITH(walk + 1, "weather_string")) {
            outwalk += sprintf(outwalk, "%s", weather_string);
            walk += strlen("weather_string");
        }
    }
    return outwalk;
}

void print_weather(yajl_gen json_gen, char *buffer, const char *format) {
    char *outwalk = buffer;

    //printf("getting here\n");

    const char *selected_format = format;
    bool colorful_output = false;

    // TODO: put your path to brightness files here
    char *path = "/home/anton/programming/i3status/plugins/weather/";

	// read day
    char day_filename[256];
    sprintf(day_filename, "%sday", path);
    //printf("filename = %s\n", day_filename);
	char day[256];
    read_string_from_file(day_filename, day);
    //printf("getting day: %s\n", day);

	// read icon
    char icon_filename[256];
    sprintf(icon_filename, "%sicon", path);
    //printf("filename = %s\n", icon_filename);
	char icon[256];
    read_string_from_file(icon_filename, icon);

	// read temperature
    char temperature_filename[256];
    sprintf(temperature_filename, "%stemperature", path);
	char temperature[256];
    read_string_from_file(temperature_filename, temperature);

	// read temperature
    char weather_string_filename[256];
    sprintf(weather_string_filename, "%sweather_string", path);
	char weather_string[256];
    read_string_from_file(weather_string_filename, weather_string);

	// sprintf(buffer, "%d", percentage);
    outwalk = apply_weather_format(selected_format, outwalk, day, icon, temperature, weather_string);

    if (colorful_output)
        END_COLOR;

    *outwalk = '\0';
    OUTPUT_FULL_TEXT(buffer);

    return;
}

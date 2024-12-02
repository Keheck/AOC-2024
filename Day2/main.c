#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 32

int main() {
    FILE *reports_file = fopen("nuclear_reports.txt", "r");
    char report_line[MAX_LINE_LENGTH];

    if(!reports_file) {
        perror("Failed to open report file");
        return 1;
    }

    int safe_reports = 0;
    char report_value;
    char last_value = -1;
    char *value_string;
    char is_ascending = -1;
    char *end;

    while(1) {
        fgets(report_line, MAX_LINE_LENGTH, reports_file);
        if(feof(reports_file))
            break;

        value_string = strtok(report_line, " ");

        last_value = atoi(value_string);
        value_string = strtok(0, " ");
        report_value = atoi(value_string);

        is_ascending = report_value > last_value;

        if(abs(report_value - last_value) < 1 || abs(report_value - last_value) > 3) {
            continue;
        }

        while(value_string = strtok(0, " ")) {
            last_value = report_value;
            report_value = atoi(value_string);

            if(abs(report_value - last_value) < 1 || abs(report_value - last_value) > 3) {
                break;
            }

            if((is_ascending && report_value < last_value) || (!is_ascending && report_value > last_value)) {
                break;
            }
        }

        if(value_string == 0) {
            safe_reports++;
        }
    }

    printf("Safe values: %d\n", safe_reports);
    fclose(reports_file);
}
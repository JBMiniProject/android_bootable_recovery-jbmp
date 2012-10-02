#include <stdlib.h>
#include <stdio.h>

#include "common.h"
#include "roots.h"
#include "recovery_ui.h"

void show_battstat() {
    FILE* fs = fopen("/sys/class/power_supply/battery/status","r");
    char* bstat = calloc(13,sizeof(char));
    fgets(bstat, 13, fs);

    FILE* fc = fopen("/sys/class/power_supply/battery/capacity","r");
    char* bcap = calloc(4,sizeof(char));
    fgets(bcap, 4, fc);

    FILE* fv = fopen("/sys/class/power_supply/battery/batt_vol","r");
    char* bvol = calloc(4,sizeof(char));
    fgets(bvol, 4, fv);

    FILE* fh = fopen("/sys/class/power_supply/battery/health","r");
    char* bhealth = calloc(3,sizeof(char));
    fgets(bhealth, 25, fh);

    FILE* fte = fopen("/sys/class/power_supply/battery/technology","r");
    char* btec = calloc(4,sizeof(char));
    fgets(btec, 25, fte);

    FILE* ft = fopen("/sys/class/power_supply/battery/batt_temp","r");
    char* btemp = calloc(3,sizeof(char));
    fgets(btemp, 3, ft);

    btemp = strcat(btemp," C");
    bcap = strcat(bcap,"%");
    int caplen = strlen(bcap);
    if( bcap[caplen-1] == '\n' ) {
        bcap[caplen-1] = 0;
    }

    ui_print("\nBattery Status: ");
    ui_print("%s",bstat);
    ui_print("\nCharge Level: ");
    ui_print("%s",bcap);
    ui_print("\nVoltage: ");
    ui_print("%s mV",bvol);
    ui_print("\nHealth: ");
    ui_print("%s",bhealth);
    ui_print("\nTechnology: ");
    ui_print("%s",btec);
    ui_print("\nTemperature: ");
    ui_print("%s",btemp);

    fclose(fs);
    fclose(fc);
    fclose(fv);
    fclose(fh);
    fclose(fte);
    fclose(ft);
}

void show_extras_menu()
{
    static char* headers[] = { "Extras"
                               "",
                               NULL };

    char* items[] = { "Show Battery Status",
                      NULL };

    int chosen_item = -1;

    chosen_item = get_menu_selection(headers,items,1,chosen_item<0?0:chosen_item);

    switch (chosen_item) {
        case 0:
            show_battstat();
            break;
    }
}

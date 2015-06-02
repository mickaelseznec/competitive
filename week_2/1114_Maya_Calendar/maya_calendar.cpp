#include <iostream>
#include <cstdio>
#include <string>
#include <map>

using namespace std;

#define TZOLKIN     260
#define TZOLKIN_R   52
#define HAAB        365
#define HAAB_R      73
#define GCD         5
#define LCM         18980

#define LONG_COUNT_BEGIN    1152000
#define TZOLKIN_BEGIN       100
#define HAAB_BEGIN          43

map<string, int> tzolkin = {
    {"Imix", 1},
    {"Ik", 2},
    {"Akbal", 3},
    {"Kan", 4},
    {"Chikchan", 5},
    {"Kimi", 6},
    {"Manik", 7},
    {"Lamat", 8},
    {"Muluk", 9},
    {"Ok", 10},
    {"Chuen", 11},
    {"Eb", 12},
    {"Ben", 13},
    {"Ix", 14},
    {"Men", 15},
    {"Kib", 16},
    {"Kaban", 17},
    {"Etznab", 18},
    {"Kawak", 19},
    {"Ajaw", 20},
};

#ifdef DEBUG
string tzolkin_days_value[] = {
    "Imix",
    "Ik",
    "Akbal",
    "Kan",
    "Chikchan",
    "Kimi",
    "Manik",
    "Lamat",
    "Muluk",
    "Ok", 
    "Chuen", 
    "Eb", 
    "Ben", 
    "Ix", 
    "Men", 
    "Kib", 
    "Kaban", 
    "Etznab", 
    "Kawak", 
    "Ajaw", 
};
#endif

map<string, int> haab = { 
    {"Pohp", 20 * 0},
    {"Wo", 20 * 1},
    {"Sip", 20 * 2},
    {"Zotz", 20 * 3},
    {"Sek", 20 * 4},
    {"Xul", 20 * 5},
    {"Yaxkin", 20 * 6},
    {"Mol", 20 * 7},
    {"Chen", 20 * 8},
    {"Yax", 20 * 9},
    {"Sak", 20 * 10},
    {"Keh", 20 * 11},
    {"Mak", 20 * 12},
    {"Kankin", 20 * 13},
    {"Muan", 20 * 14},
    {"Pax", 20 * 15},
    {"Kayab", 20 * 16},
    {"Kumku", 20 * 17},
    {"Wayeb", 20 * 18},
};

#ifdef DEBUG
string haab_months_value[] = { 
    "Pohp",
    "Wo",
    "Sip",
    "Zotz",
    "Sek",
    "Xul",
    "Yaxkin",
    "Mol",
    "Chen",
    "Yax",
    "Sak", 
    "Keh", 
    "Mak", 
    "Kankin", 
    "Muan", 
    "Pax", 
    "Kayab", 
    "Kumku", 
    "Wayeb", 
};
#endif
struct long_count {
    int baktun;
    int katun;
    int tun;
    int winal;
    int kin;
};

static inline int long_count_to_days (long_count date) {
    return date.baktun * 144000 + date.katun * 7200 + date.tun * 360 + date.winal * 20 + date.kin;
}

static inline int tzolkin_convert (int number, string day) {
    int day_number = tzolkin[day];
    return day_number + (((number - day_number) * 2 * 20 + 780) % 260);
}

static inline long_count days_to_long_count (int days) {
    long_count date;
    date.kin = days % 20;
    date.winal = (days % 360) / 20;
    date.tun = (days % 7200) / 360;
    date.katun = (days % 144000) / 7200;
    date.baktun = days / 144000;
    return date;
}

static int calendars_to_date(int tzolkin_date, int haab_date) {
    tzolkin_date -= TZOLKIN_BEGIN;
    haab_date -= HAAB_BEGIN;
    /* Case of a non possible date*/
    if ((tzolkin_date - haab_date) % GCD != 0)
        return -1;
    else {
        return LONG_COUNT_BEGIN + haab_date + ((tzolkin_date - haab_date) * HAAB + 10 * LCM) % LCM ;
    }
}

#ifdef DEBUG
static void test_calendar() {
    for (int i = 0; i < LCM; ++i) {
        int tzolkin_date = tzolkin_convert((i%13)+1, tzolkin_days_value[i%20]);
        int haab_date = haab[haab_months_value[(int) (i%365)/20]] + ((i%365)%20)+1;
        printf("%d.%s %d.%s %d %d %d\n", (i%13)+1, tzolkin_days_value[i%13].c_str(), ((i%365)%20)+1, haab_months_value[(int) i%365/20].c_str(), tzolkin_date, haab_date, calendars_to_date(tzolkin_date, haab_date));
        if ( i + 1 != calendars_to_date(tzolkin_date, haab_date)) {
            cerr << "Error test calendar" << endl;
            return;
        }
    }
}
#endif

int main(void) {

    int tzolkin_number, haab_day;
    int cases;
    char tzolkin_day[20] , haab_month[20];

    int n = 0;
    cin >> cases;
    while (cases--) {
        scanf("%d.%s %d.%s", &tzolkin_number, tzolkin_day, &haab_day, haab_month);
        if (n > 0)
            printf("\n");

        if (calendars_to_date(tzolkin_convert(tzolkin_number, tzolkin_day), haab_day + haab[haab_month]) == -1) {
            printf("NO SOLUTION\n");
            continue;
        }

        long_count date;

        int k = 0;
        date = days_to_long_count(calendars_to_date(tzolkin_convert(tzolkin_number, tzolkin_day), haab_day + haab[haab_month]));
        while (date.baktun > 7) {
            k--;
            printf("%d.%d.%d.%d.%d\n", date.baktun, date.katun, date.tun, date.winal, date.kin);
            date = days_to_long_count(calendars_to_date(tzolkin_convert(tzolkin_number, tzolkin_day), haab_day + haab[haab_month]) + k * LCM);
        }

        k = 1;
        date = days_to_long_count(calendars_to_date(tzolkin_convert(tzolkin_number, tzolkin_day), haab_day + haab[haab_month]) + k * LCM);
        while (date.baktun < 10) {
            k++;
            printf("%d.%d.%d.%d.%d\n", date.baktun, date.katun, date.tun, date.winal, date.kin);
            date = days_to_long_count(calendars_to_date(tzolkin_convert(tzolkin_number, tzolkin_day), haab_day + haab[haab_month]) + k * LCM);
        }

        n++;
    }

    return 0;
}

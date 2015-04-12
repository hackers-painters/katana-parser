//
//  fragment.c
//  Katana
//
//  Created by QFish on 4/6/15.
//  Copyright (c) 2015 QFish. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/timeb.h>

#include "katana.h"

#define StopWatchBegin(begin) struct timeb t1; ftime(&t1);
#define StopWatchEnd(begin) struct timeb t2; ftime(&t2); printf("<" #begin "> costs %dms.\n", (t2.millitm - t1.millitm));

void help() {
    printf("Usage: fragment \"<fragment css string>\" <mode>.\n");
    printf("Mode: 0:Stylesheet\n");
    printf("      1:Rule\n");
    printf("      2:KeyframeRule\n");
    printf("      3:KeyframeKeyList\n");
    printf("      4:MediaList\n");
    printf("      5:Value\n");
    printf("      6:Selector\n");
    printf("      7:DeclarationList\n");
}

// export PKG_CONFIG_PATH=/usr/share/pkgconfig:/usr/lib/pkgconfig:/usr/local/lib/pkgconfig
// gcc examples/fragment.c `pkg-config --cflags --libs katana` -o fragment
// ./fragment "selector {property:value}" 0;

int main(int argc, const char * argv[]) {
    
    if (argc != 3) {
        help();
        exit(0);
    }
    
    const char * s = argv[1]; // "@import url(xxx);";
    int m = (const char)*argv[2] - '0';
    if ( m < 0 || m > 7 )
        help();
    StopWatchBegin(KatanaParseFile);
    KatanaOutput* output = katana_parse(s, strlen(s), m);
    StopWatchEnd(KatanaParseFile);
    katana_dump_output(output);
    katana_destroy_output(output);
    
//    printf("\n\nTest:\n");
//    test();
}

void test() {
    char * str = NULL;
    str = "(min-width: 992px) and (max-width: 1199px)";
    KatanaOutput * output_medialist = katana_parse(str, strlen(str), KatanaParserModeMediaList);
    str = "@import url(xxx.css)";
    KatanaOutput * output_rule_import = katana_parse(str, strlen(str), KatanaParserModeRule);
    str = "selector{a:b}";
    KatanaOutput * output_rule_style = katana_parse(str, strlen(str), KatanaParserModeRule);
    str = "1px #333 dash";
    KatanaOutput * output_value = katana_parse(str, strlen(str), KatanaParserModeValue);
    str = "tag .class #id";
    KatanaOutput * output_selectors = katana_parse(str, strlen(str), KatanaParserModeSelector);
    str = "key1: val1; key2: val2; key3: val3;";
    KatanaOutput * output_declarations = katana_parse(str, strlen(str), KatanaParserModeDeclarationList);
    
    katana_destroy_output(katana_dump_output(output_medialist));
    katana_destroy_output(katana_dump_output(output_rule_import));
    katana_destroy_output(katana_dump_output(output_rule_style));
    katana_destroy_output(katana_dump_output(output_value));
    katana_destroy_output(katana_dump_output(output_selectors));
    katana_destroy_output(katana_dump_output(output_declarations));
}

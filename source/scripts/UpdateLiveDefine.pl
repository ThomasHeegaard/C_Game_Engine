#!/usr/bin/perl

@FilesToScan = ("../modules/graphics/sprite.h",
                "../modules/graphics/texture_bank.h");

$OutFile = "../utils/live_define.c";

open (my $out, ">", $OutFile) or die "$OutFile could not be opened: $!";

print $out "//Created by script\n\n#include <string.h>\n#include <stdio.h>\n\n
int TranslateDefines(const char* value)
{
";

for my $filename (@FilesToScan)
{
    print "Opening $filename \n";
    open (my $file, "<", $filename) or die "$filename could not be opened: $!";
    @file = <$file>;
    for my $line (@file)
    {
        if($line =~ /.*#define (\S+).+(\d+).*/)
        {
            print "    found $1 -> $2\n";
            print $out "    if(strcmp(\"$1\", value) == 0)\n        return $2;\n";
        }
    }
    print "Closing $filename \n";
    close $file;
}
print $out "
    fprintf(stderr, \"No define found for %s returning 0\\n\", value);
    return 0;
}
";
print "\nDone\n";
close $out;
                

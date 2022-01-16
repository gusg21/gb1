#include <stdlib.h>
#include <stdio.h>
#include "gb.h"

void save_gb_map(tilemap_t map, const char* filename)
{
    FILE *outputFile = fopen(filename, "w+");

    const char* headerTemplate = "#ifndef MAP_H\n#define MAP_H\n\nconst uint8_t map_data[] = {\n";
    const char* headerTemplateEnd = "\n};\n\n#endif // MAP_H";
    
    fprintf(outputFile, "%s", headerTemplate);
    for (int i = 0; i < map.width * map.height; i++)
    {
        fprintf(outputFile, "0x%02X, ", map.data[i]);
    }
    fprintf(outputFile, "%s", headerTemplateEnd);

    fclose(outputFile);
}
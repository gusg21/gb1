import xml.etree.ElementTree as ET
import sys

def main():
    assert len(sys.argv) > 1, "Please specify a TMX map to convert to header."

    name = sys.argv[1].split(".")[0]

    root = ET.parse(sys.argv[1]).getroot()
    csv = root.find("layer").find("data").text
    csv.replace("\n", "")
    tiles = [int(x)-1 for x in csv.split(",")]
    hex_data_str = ""
    for tile in tiles:
        hex_data_str += "0x" + format(tile, '02x') + ", "
    
    
    c_src = '''// Auto-generated by tmxgb.py by Angus Goucher
#ifndef {}_H
#define {}_H
const int8_t {}_data[] = {{ {} }};
#endif // {}_H'''.format(
        name.upper(),
        name.upper(),
        name, 
        hex_data_str,
        name.upper())
    
    print(c_src)


if __name__ == "__main__":
    main()
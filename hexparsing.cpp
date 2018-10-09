#include <iftream>
#include <string>
#include <vector>

#include "hexparsing.h"

const unsigned short int fill_value = 0xFFFF;  //以全1初始化数据表

HexParsing::HexParsing()
{

}

HexParsing::HexParsing(string file_path_name, unsigned int origin_address,
                       unsigned int data_length)
    :file(file_path_name),
     addr(origin_address),
     len(data_length)
{
    //设置数据表大小，并全部初始化为1
    map.resize(data_length*1024, fill_value);
    error_code = 0;
}

bool HexParsing::Convert()
{
    char buf[139];
    iftream in_file(file);
    if(!in_file.is_open()) {
        error_code = FILE_OPEN_ERROR;
        return 0;
    }

    in_file.getline(buf, 139);
    while(!in_file.eof()) {
        
        
        in_file.getline(buf, 139);
    }
}

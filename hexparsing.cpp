#include <fstream>
#include <string>
#include <vector>

#include "hexparsing.h"

using namespace std;

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
    data_vec.resize(data_length*1024, fill_value);
    error_code = 0;
}

bool HexParsing::Convert()
{
    char buf[75];  //hex每一行的数据
    lineForm line_data;
    Addr addr_t; //32位地址

    ifstream in_file(file);
    if(!in_file.is_open()) {
        error_code = FILE_OPEN_ERROR;
        return false;
    }

    int line_number = 1;  //记录行数
    in_file.getline(buf, 50);
    while(!in_file.eof()) {
        if(buf[0] == ':') {
            //将文件字符数据转换为整型数据
            if(CharBuffer2HexData(buf, &line_data)) {
                //数据校验
                if(CheckData(&line_data)) {
                    if(line_data)
                } else {
                    error_code = FILE_LINE_CHECK_ERROR;
                    rec = line_number;
                    return false;
                }
            } else {
                error_code = FILE_LINE_CONVERT_ERROR;
                rec = line_number;
                return false;
            }
        } else {
            error_code = FILE_GETLINE_ERROR;
            rec = line_number;
            return false;
        }
        
        in_file.getline(buf, 139);
        line_number++;
    }
}

bool HexParsing::MappedData(pLineForm data)
{
    
}

bool HexParsing::CheckData(pLineForm data)
{
    int sum;
    sum += data->l_len * 2;
    sum = sum +  (data->l_addr & 0xFF) + ((data->l_addr >> 8) & 0xFF);
    sum += data->l_type;
    for (int i = 0; i < data->l_len; ++i) {
        sum = sum + (data->l_data[i] & 0x00FF) + ((data->l_data[i] >> 8) & 0x00FF);
    }

    sum = 0x100 - (sum & 0x00FF);
    if(sum == data->l_check) {
        return true;
    } else {
        return false;
    }
}

bool HexParsing::CharBuffer2HexData(char* buf, pLineForm data)
{
    data->l_len = Char2IntByte(buf[1], buf[2]) / 2;  //数据长度，按16位(2字节)长度计算
    unsigned short int len_t = data->l_len * 4 + 11;  //buf长度
    data->l_addr = Char2ShortInt(buf[3], buf[4], buf[5], buf[6]);  //地址
    data->l_type = Char2IntByte(buf[7], buf[8]);  //记录类型

    int j = 9;  //第10个值开始为数据
    // 转换数据
    for(int i = 0; i < data->l_len; ++i) {
        data->l_data[i] = Char2ShortInt(buf[j], buf[j+1], buf[j+2], buf[j+3]);
        j += 4;
    }
    // 转换校验值
    data->l_check = Char2IntByte(buf[j], buf[j+1]);

    if((j + 2) == len_t) {
        return true;  //转换的数据长度一致
    } else {
        return false;
    }
}

unsigned short int HexParsing::Char2ShortInt(char d_4, char d_3, char d_2, char d_1)
{
    return (Char2Int(d_4) << 12 | Char2Int(d_3) << 8 | Char2Int(d_2) << 4 | Char2Int(d_1));
}

unsigned short int HexParsing::Char2IntByte(char d_h, char d_l)
{
    return (Char2Int(d_h) << 4 | Char2Int(d_l));
}

unsigned short int HexParsing::Char2Int(char ch)
{
    unsigned short int t;
    switch(ch) {
    case '0':
        t = 0x0;
        break;
    case '1':
        t = 0x1;
        break;
    case '2':
        t = 0x2;
        break;
    case '3':
        t = 0x3;
        break;
    case '4':
        t = 0x4;
        break;
    case '5':
        t = 0x5;
        break;
    case '6':
        t = 0x6;
        break;
    case '7':
        t = 0x7;
        break;
    case '8':
        t = 0x8;
        break;
    case '9':
        t = 0x9;
        break;
    case 'A':
        t = 0xA;
        break;
    case 'B':
        t = 0xB;
        break;
    case 'C':
        t = 0xC;
        break;
    case 'D':
        t = 0xD;
        break;
    case 'E':
        t = 0xE;
        break;
    case 'F':
        t = 0xF;
        break;
    }
    return t;
}

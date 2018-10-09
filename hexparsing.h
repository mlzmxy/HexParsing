#ifndef HEXPARSING_H
#define HEXPARSING_H

class HexParsing
{
public:
    HexParsing();
    HexParsing(string file_path_name, unsigned int origin_address,
               unsigned int data_length);
    ~HexParsing();

    bool Convert();
    vector<unsigned short int> GetDataMap();
    string GetErrorMsg();
    
private:
    vector<unsigned short int> map;  //转换后的数据表
    string file;  //源文件
    unsigned int addr;  //起始地址
    unsigned int len;  //文件大小，单位为K
    unsigned int error_code;  //错误类型
};

#define FILE_OPEN_ERROR 0x01

#endif // HEXPARSING_H

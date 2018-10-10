#ifndef HEXPARSING_H
#define HEXPARSING_H

// HEX文件的行格式结构
typedef struct _LINE_DATA {
    unsigned short int l_len;      //数据长度
    unsigned short int l_addr;     //地址
    unsigned short int l_type;     //记录类型
    unsigned short int l_data[16]; //数据，最大长度为32个字节
    unsigned short int l_check;    //校验
}lineForm, *pLineForm;

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
    vector<unsigned short int> data_vec;  //转换后的数据序列
    string file;  //源文件
    unsigned int addr;  //起始地址
    unsigned int len;  //文件大小，单位为K
    unsigned int error_code;  //错误类型
    unsigned int error_rec;   //错误记录

    bool MappedData(pLineForm data);
    bool CheckData(pLineForm data);
    bool CharBuffer2HexData(char* buf, pLineForm data);
    unsigned short int Char2IntByte(char d_h, char d_l);
    unsigned short int Char2ShortInt(char d_4, char d_3, char d_2, char d_1);
    unsigned short int Char2Int(char ch);
};

typedef struct _ADDR {
    unsigned int addr_h:16;  //地址高位
    unsigned int addr_l:16;  //地址低位
}Addr;

#define FILE_OPEN_ERROR         0x01  //文件打开错误
#define FILE_GETLINE_ERROR      0x02  //文件读取行数据错误
#define FILE_LINE_CONVERT_ERROR 0x03  //文件行转换长度不一致
#define FILE_LINE_CHECK_ERROR   0x04  //文件行数据校验错误

#endif // HEXPARSING_H

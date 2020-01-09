//
//  CRC_Remender.h
//
//  Created by april on 2019/12/17.
//

#ifndef CRC_Remender_h
#define CRC_Remender_h

// 输入 10 进制 int 型数据，返回 2 进制字符串
// 10 进制数字前不能有 0，会被识别成 8 进制
// 返回 -1 失败
int crc_remainder_number(int original_num);

// 输入原始数据 和 校验位 10进制数据
// 返回 0 校验通过，-1 校验失败
int check_crc(int original_number, int remender);

#endif /* CRC_Remender_h */

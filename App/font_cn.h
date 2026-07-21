/*
 * ═══════════════════════════════════════════════════════════════
 *  中文字库 — 数据格式说明 & 添加新字必读警告
 * ═══════════════════════════════════════════════════════════════
 *
 * 数据结构: gFontCN_Big[n][32]  每字 32 字节
 *   前 16 bytes = 上半段 16 列（rows 0-7）
 *   后 16 bytes = 下半段 16 列（rows 8-15）
 *   每个 byte  = 一列 8 行, bit0=第1行(顶), bit7=第8行(底)
 *   Vertical column 格式（不是 alternating, 不是 left/right split）
 *
 * ⚠️⚠️⚠️  添加新汉字的四条戒律（已踩坑四次！）  ⚠️⚠️⚠️
 *
 * 1. 字体来源：必须从「文泉驿点阵宋体 11pt」(WenQuanYi Bitmap Song)
 *    wenquanyi_11pt.pcf 位图字库中提取，不要用其他尺寸的版本！
 *    已用「号」(index 20) 和「中」(index 3) 验证 11pt 版本完美匹配。
 *
 * 2. 格式验证：加新字前必须先用已知字符（「号」index 20
 *    或「中」index 3）验证 bit 顺序和 column 排布，
 *    确认 gFontCN_Big[n][32] 的格式正确再继续。
 *
 * 3. 纵向偏移：PCF 位图放入 16×16 格子时不许做居中处理。
 *    要用 row_off=0 (BDF 第1行 → 格子 row 0) 匹配现有字库。
 *
 * 4. 禁止自生成：直接从 PCF 文件 (.pcf) 经 pcf2bdf 转换后
 *    提取原始位图，不许用 PIL 或任何字体渲染引擎跑。
 *
 * 上述四条任意一条没做到 → 编出来字形不对 → 白等 3 轮 CI。
 * 不想再栽第五回的话，老老实实按步骤来。
 * ═══════════════════════════════════════════════════════════════
 */

#ifndef FONT_CN_H
#define FONT_CN_H
#include <stdint.h>

#define FONT_CN_WIDTH  16
#define FONT_CN_COUNT 120
#define FONT_CN_BASE 0x80

extern const uint8_t gFontCN_Big[120][32];

#define CN_C4E0A  ((char)(0x80 + 0))
#define CN_C4E0B  ((char)(0x80 + 1))
#define CN_C4E24  ((char)(0x80 + 2))
#define CN_C4E2D  ((char)(0x80 + 3))
#define CN_C4E3B  ((char)(0x80 + 4))
#define CN_C4F4E  ((char)(0x80 + 5))
#define CN_C4F60  ((char)(0x80 + 6))
#define CN_C4FE1  ((char)(0x80 + 7))
#define CN_C5168  ((char)(0x80 + 8))
#define CN_C5173  ((char)(0x80 + 9))
#define CN_C5178  ((char)(0x80 + 10))
#define CN_C5206  ((char)(0x80 + 11))
#define CN_C5229  ((char)(0x80 + 12))
#define CN_C5355  ((char)(0x80 + 13))
#define CN_C5382  ((char)(0x80 + 14))
#define CN_C538B  ((char)(0x80 + 15))
#define CN_C539F  ((char)(0x80 + 16))
#define CN_C53CC  ((char)(0x80 + 17))
#define CN_C53D1  ((char)(0x80 + 18))
#define CN_C53F3  ((char)(0x80 + 19))
#define CN_C53F7  ((char)(0x80 + 20))
#define CN_C540D  ((char)(0x80 + 21))
#define CN_C54CD  ((char)(0x80 + 22))
#define CN_C56DE  ((char)(0x80 + 23))
#define CN_C5766  ((char)(0x80 + 24))
#define CN_C589E  ((char)(0x80 + 25))
#define CN_C58F0  ((char)(0x80 + 26))
#define CN_C590D  ((char)(0x80 + 27))
#define CN_C5927  ((char)(0x80 + 28))
#define CN_C5B57  ((char)(0x80 + 29))
#define CN_C5BBD  ((char)(0x80 + 30))
#define CN_C5C04  ((char)(0x80 + 31))
#define CN_C5DE6  ((char)(0x80 + 32))
#define CN_C5E26  ((char)(0x80 + 33))
#define CN_C5E73  ((char)(0x80 + 34))
#define CN_C5F00  ((char)(0x80 + 35))
#define CN_C5F3A  ((char)(0x80 + 36))
#define CN_C606F  ((char)(0x80 + 37))
#define CN_C6237  ((char)(0x80 + 38))
#define CN_C6309  ((char)(0x80 + 39))
#define CN_C63A5  ((char)(0x80 + 40))
#define CN_C6536  ((char)(0x80 + 41))
#define CN_C653E  ((char)(0x80 + 42))
#define CN_C6587  ((char)(0x80 + 43))
#define CN_C65E0  ((char)(0x80 + 44))
#define CN_C6670  ((char)(0x80 + 45))
#define CN_C6700  ((char)(0x80 + 46))
#define CN_C6BB5  ((char)(0x80 + 47))
#define CN_C6BD4  ((char)(0x80 + 48))
#define CN_C6BD5  ((char)(0x80 + 49))
#define CN_C6CE2  ((char)(0x80 + 50))
#define CN_C6E05  ((char)(0x80 + 51))
#define CN_C70B9  ((char)(0x80 + 52))
#define CN_C7387  ((char)(0x80 + 53))
#define CN_C7528  ((char)(0x80 + 54))
#define CN_C7535  ((char)(0x80 + 55))
#define CN_C767E  ((char)(0x80 + 56))
#define CN_C7801  ((char)(0x80 + 57))
#define CN_C7981  ((char)(0x80 + 58))
#define CN_C79F0  ((char)(0x80 + 59))
#define CN_C7A84  ((char)(0x80 + 60))
#define CN_C7AD9  ((char)(0x80 + 61))
#define CN_C7ECF  ((char)(0x80 + 62))
#define CN_C7F57  ((char)(0x80 + 63))
#define CN_C8005  ((char)(0x80 + 64))
#define CN_C884C  ((char)(0x80 + 65))
#define CN_C89C6  ((char)(0x80 + 66))
#define CN_C89C9  ((char)(0x80 + 67))
#define CN_C89E3  ((char)(0x80 + 68))
#define CN_C8BA4  ((char)(0x80 + 69))
#define CN_C8D85  ((char)(0x80 + 70))
#define CN_C8DE8  ((char)(0x80 + 71))
#define CN_C8F93  ((char)(0x80 + 72))
#define CN_C8FF7  ((char)(0x80 + 73))
#define CN_C901A  ((char)(0x80 + 74))
#define CN_C9053  ((char)(0x80 + 75))
#define CN_C90E8  ((char)(0x80 + 76))
#define CN_C94C3  ((char)(0x80 + 77))
#define CN_C9501  ((char)(0x80 + 78))
#define CN_C9510  ((char)(0x80 + 79))
#define CN_C952E  ((char)(0x80 + 80))
#define CN_C963F  ((char)(0x80 + 81))
#define CN_C97F3  ((char)(0x80 + 82))
#define CN_C9891  ((char)(0x80 + 83))
#define CN_C9AD8  ((char)(0x80 + 84))
#define CN_C9ED8  ((char)(0x80 + 85))
#define CN_C56FE  ((char)(0x80 + 86))
#define CN_C6807  ((char)(0x80 + 87))
#define CN_C666E  ((char)(0x80 + 88))
#define CN_C5FEB  ((char)(0x80 + 89))
#define CN_C901F  ((char)(0x80 + 90))
#define CN_C675F  ((char)(0x80 + 91))
#define CN_C4EC5  ((char)(0x80 + 92))
#define CN_C529F  ((char)(0x80 + 93))
#define CN_C53BB  ((char)(0x80 + 94))
#define CN_C542C  ((char)(0x80 + 95))
#define CN_C5DEE  ((char)(0x80 + 96))
#define CN_C5F0F  ((char)(0x80 + 97))
#define CN_C624B  ((char)(0x80 + 98))
#define CN_C626B  ((char)(0x80 + 99))
#define CN_C62A5  ((char)(0x80 + 100))
#define CN_C63A7  ((char)(0x80 + 101))
#define CN_C63CF  ((char)(0x80 + 102))
#define CN_C673A  ((char)(0x80 + 103))
#define CN_C6A21  ((char)(0x80 + 104))
#define CN_C6E90  ((char)(0x80 + 105))
#define CN_C76D1  ((char)(0x80 + 106))
#define CN_C76D8  ((char)(0x80 + 107))
#define CN_C7B52  ((char)(0x80 + 108))
#define CN_C8B66  ((char)(0x80 + 109))
#define CN_C9664  ((char)(0x80 + 110))
#define CN_C9759  ((char)(0x80 + 111))
#define CN_C5FD7  ((char)(0x80 + 112))
#define CN_C9ED1  ((char)(0x80 + 113))
#define CN_C5BA2  ((char)(0x80 + 114))
#define CN_C5E1D  ((char)(0x80 + 115))
#define CN_C56FD  ((char)(0x80 + 116))
#define CN_C64CD  ((char)(0x80 + 117))
#define CN_C4F5C  ((char)(0x80 + 118))
#define CN_C65E5  ((char)(0x80 + 119))

#endif

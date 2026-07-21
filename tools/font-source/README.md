# 中文字库源字体

本目录存放 `font_cn.c` / `font_cn.h` 中文字库所用的源字体文件。

## 源文件

- `wenquanyi_11pt.pcf` — **文泉驿点阵宋体 11pt (15px)**
- 来源：Debian/Ubuntu 包 `xfonts-wqy`
- 已验证：用「号」(index 20) 和「中」(index 3) 数据对比确认 11pt 版本完美匹配

## 添加新汉字的正确流程

1. `pcf2bdf -o /tmp/char.bdf tools/font-source/wenquanyi_11pt.pcf`
2. 解析 BDF 中目标字符的 HEX 行数据
3. `cell_row = bdf_row_index + 0`（顶到 row 0，不要居中！）
4. `cell_col = bit_position + BBX_x`（不加额外偏移）
5. 每个 byte 代表一列 8 行，bit0=第一行(顶)，bit7=第八行(底)
6. 前 16 bytes = 上半段（rows 0-7），后 16 bytes = 下半段（rows 8-15）
7. 先拿「号」或「中」验证转换方法正确
8. 再生成新字数据

> ⚠️ 违反上述任何一条 = 白编 3 轮 CI，已经栽过四回了！

//
// Created by 12472 on 26-3-29.
//
/*
 * 字符串转化
 * 给出两个长度相同的字符串str1和str2
 * 每一次转化的时候，可以将str1中出现的所有相同字母变成其他任何小写英文字母
 * 只有在字符串str1能够通过上述方法顺利转化为字符串str2的时候才返回true
 * https://leetcode.cn/problems/string-transforms-into-another-string/description/
 * str1 = "cacbba"，str2 = "abaccb"
 * 变换过程为 cacbba -> cactta -> cbcttb -> abattb -> abaccb
变换了4次
*/
/*
 * Utils for string.
 *
 * Author: Wu Bingzheng
 *
 */

#ifndef _OHC_STRING_H
#define _OHC_STRING_H

#include <stdio.h>
#include <string.h>

#define bit_set(num, set) num |= 1L << (set)
#define bit_clear(num, set) num &= ~(1L << (set))
#define bit_mask(num) ((1L << (num)) - 1)

static inline int char2hex(char c) // 字符串转为整形，为什么这么做，暂不知道
{
	if(c >= '0' && c <= '9')
		return c - '0';
	c &= 0xdf;
	if(c >= 'A' && c <= 'F')
		return c - 'A' + 10;
	return -1;
}

static inline int numlen(long n) // 数字显示长度
{
	int len = 0;
	if(n == 0) return 1;
	while(n) {
		len++;
		n /= 10;
	}
	return len;
}

static inline char *strwhite(char *str) // char * str + size_t 指针偏移
{
	return str + strcspn(str, "\t\n "); // strcspn 返回str中首次出现"\t\n "字符的位置
}
static inline char *strnonwhite(char *str)
{
	return str + strspn(str, "\t\n "); // strspn 返回str中首次没有出现"\t\n "字符的位置
}

/* return 0~63. return 0 if n=0 or n=1 both. */
static inline int bit_highest(uint64_t n) // 返回二进制最高位？
{
	long index;
	__asm__ ( // 内嵌汇编
		"bsrq %1, %0"
		:"=r"(index)
		:"m"(n)
	);

	return index;
}

typedef struct {
	char	*base;
	size_t	len;
} string_t;
#define STRING_INIT(s) {s, sizeof(s) - 1}

static inline char *strshow(string_t *str)
{
	if(str->base == NULL) {
		return "-";
	}
	str->base[str->len] = '\0';
	return str->base;
}

#endif

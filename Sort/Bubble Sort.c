#include "Bubble Sort.h"
/**
******************************************************************************
* @file    Bubble Sort.c
* @author  Jason
* @date    2018/10/18
* @brief   排序相关算法
******************************************************************************
*/
/*************************************************
Function: bubble_sort
Description: 冒泡排序算法
Input: 	arr[]排序数据 len 排序长度
Output: 无
Return: 无
Others: 无
*************************************************/
void bubble_sort(uint8_t arr[], uint16_t len) 
{
    uint16_t i, j, temp;
    for (i = 0; i < len - 1; i++)
	{
        for (j = 0; j < len - 1 - i; j++)
		{
            if (arr[j] > arr[j + 1]) 
			{
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
		}
	}
}

/*************************************************
Function: swap
Description: 交换数据
Input: 	a交换数据1 b交换数据2
Output: 无
Return: 无
Others: 无
*************************************************/
void swap(uint8_t *a,uint8_t *b) //交換兩個變數
{
    uint8_t temp;
	temp = *a;
    *a = *b;
    *b = temp;
}
/*************************************************
Function: selection_sort
Description: 选择排序
Input: 	a交换数据1 b交换数据2
Output: 无
Return: 无
Others: 无
*************************************************/
void selection_sort(uint8_t arr[], uint16_t len) 
{
    uint16_t i,j;
 
    for (i = 0 ; i < len - 1 ; i++) 
    {
        uint16_t min = i;
        for (j = i + 1; j < len; j++)     //走訪未排序的元素
            if (arr[j] < arr[min])    //找到目前最小值
                min = j;    //紀錄最小值
           swap(&arr[min], &arr[i]);    //做交換
    }
}






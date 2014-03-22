/*
 * =====================================================================================
 *
 *       Filename:  mbr_reader.c
 *       Description:  读取磁盘MBR的小程序
 *        Version:  1.0
 *        Created:  2013年06月06日 18时04分17秒
 *       Revision:  none
 *       Compiler:  clang
 *         Author:  sim szm
 *         Email :  xianszm007@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#include <unistd.h>
#include <fcntl.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define SECTION_SIZE 512 	// 扇区大小
#define PARTITION_SIZE 16 	// 分区表项大小
#define PARTITION_START 446 	// 分区表项在MBR中的偏移

typedef struct _partition_info{
	unsigned char active_flag; 		// 活动分区标记，0x00表示非活动, 0x80表示活动
	unsigned char start_CHS[3]; 		// 起始磁头号，扇区号，柱面号。其中磁头号1字节，扇区号2字节的低6位，柱面号2字节的高2位+3字节
	unsigned char partition_type; 		// 分区类型
	unsigned char end_CHS[3]; 		// 结束磁头号，含义同起始磁头号
	unsigned int  start_sector; 	 	// 逻辑起始扇区号
	unsigned int  number_of_sectors; 	// 所占用扇区数
}partition_info;

void print_partition_info(partition_info *part_info){
	printf("分区活动标记： %02hhX\n", part_info->active_flag);
	printf("分区起始磁头、扇区、柱面号（未分割）：");
	printf("%02hhX%02hhX%02hhX\n", part_info->start_CHS[0], part_info->start_CHS[1], part_info->start_CHS[2]);
	printf("分区类型：     %02hhX\n", part_info->partition_type);
	printf("分区结束磁头、扇区、柱面号（未分割）：");
	printf("%02hhX%02hhX%02hhX\n", part_info->end_CHS[0], part_info->end_CHS[1], part_info->end_CHS[2]);
	printf("逻辑起始扇区号：%u\n", part_info->start_sector);
	printf("所占扇区数量：  %u\n", part_info->number_of_sectors);
}

int main(int argc, char *argv[]){
	int 		disk_fd;
	size_t 		read_count;
	unsigned char 	mbr_data[SECTION_SIZE];
	
	disk_fd = open("/dev/sda", O_RDONLY);
	if (disk_fd == -1) {
		printf("What the fuck? Open '/dev/sda' error. Please run it as root.\n");
		return EXIT_FAILURE;
	}
	read_count = read(disk_fd, mbr_data, SECTION_SIZE);
	if (read_count != SECTION_SIZE) {
		printf("Read '/dev/sda'error.\n");
		return EXIT_FAILURE;
	}
	
	close(disk_fd);
	
	printf("MBR 十六进制数据:\n");
	int i;
	for (i = 0; i < SECTION_SIZE; i++) {
		printf("%02hhX ", mbr_data[i]);
		if ((i+1) % 32 == 0) {
			printf("\n");
		}
	}
	
	printf("\n分区表项 1：\n\n");
	print_partition_info((partition_info *) (mbr_data + PARTITION_START + PARTITION_SIZE * 0));
	printf("\n分区表项 2：\n\n");
	print_partition_info((partition_info *)(mbr_data + PARTITION_START + PARTITION_SIZE * 1));
	printf("\n分区表项 3：\n\n");
	print_partition_info((partition_info *)(mbr_data + PARTITION_START + PARTITION_SIZE * 2));
	printf("\n分区表项 4：\n\n");
	print_partition_info((partition_info *)(mbr_data + PARTITION_START + PARTITION_SIZE * 3));

	return 0;
}

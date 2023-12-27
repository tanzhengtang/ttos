#include<stdio.h>
#include<string.h>
//补充mbr末尾部分以达到512字节。注意最后2字节为0x55AA.
int main(int argc, char *argv[]){
    if(argc == 1){
            return 1;
    }
    FILE* file = fopen(argv[1],"a");
    if(file == NULL || fseek(file,0,SEEK_END) != 0){
            perror("file error");
            fclose(file);
            return 1;
    }
    if(ftell(file) > 510){
            printf("file larger");
    }
    else{
            char zeros[510 - ftell(file)];
            memset(zeros, 0, sizeof(zeros));
            fwrite(zeros, sizeof(char), sizeof(zeros), file);
            char dt[2] = {0x55,0xAA};
            fseek(file,0,SEEK_END);
            fwrite(dt, sizeof(char), sizeof(dt), file);
    }
	fclose(file);
	return 0;
}

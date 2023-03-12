#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

DIR *src;
DIR *dst;
int n, in, out;
char buf[1024];


int DirCopy(char *srcpath, char *destpath)
{
	DIR *sdp = NULL;
	DIR *ddp = NULL ;
	struct dirent *entry;
	struct stat statBuf;

	char save_src[1024];
	char save_dst[1024];
	char tempsrc[1024];
	char tempdest[1024];
	memset(tempsrc, 0, sizeof(tempsrc));
	memset(tempdest, 0, sizeof(tempdest));
	memset(&statBuf, 0, sizeof(statBuf));


	strcpy(tempdest, destpath);
	strcpy(tempsrc, srcpath);

	if((sdp = opendir(tempsrc)) == NULL){

		perror("error");
		return -1;
	}
	if((ddp = opendir(tempdest)) == NULL){

		perror("error");
		return -1;
	}


	while( (entry = readdir(sdp)) != NULL )
	{

		lstat(entry->d_name, &statBuf);
		if(strcmp(entry->d_name, ".") && strcmp(entry->d_name, "..")){			

			memset(save_src,0,sizeof(save_src));
			memset(save_dst,0,sizeof(save_dst));

			strcat(save_src, tempsrc);
			strcat(save_src, "/");
			strcat(save_src, entry->d_name);
			strcat(save_dst, tempdest);
			strcat(save_dst, "/");
			strcat(save_dst, entry->d_name);

			if(S_ISDIR(statBuf.st_mode)){
				mkdir(save_dst,0777);
				chdir(entry->d_name);
				DirCopy(save_src,save_dst);
				chdir(tempsrc);

			}
			else if(S_ISREG(statBuf.st_mode)){
				if((in = open(save_src, O_RDONLY)) < 0) { 
					printf("error\n");
					return -1;

				}

				if((out = open(save_dst, O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR)) < 0) { 
					printf("error\n");
					return -1;
				}

				while((n=read(in, buf, sizeof(buf)))>0) 
					write(out, buf, n);
			}

			close(out);
			close(in);
		}
	}
	chdir(srcpath);
	closedir(sdp);
	closedir(ddp);
}


int main(int argc, char **argv){

	struct stat type1;
	struct stat type2;

	lstat(argv[1], &type1);
	lstat(argv[2], &type2);

	if(argc < 3){
		write(2, "copy src dst\n", 25);
		printf("\n");
		return -1;
	}

		if(S_ISREG(type1.st_mode) && S_ISREG(type2.st_mode)){

			if((in = open(argv[1], O_RDONLY)) < 0) { 
				perror(argv[1]);
				return -1;
			}

			if((out = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR)) < 0) { 
				perror(argv[2]);
				return -1;
			}


			while((n=read(in, buf, sizeof(buf)))>0) 
				write(out, buf, n);

			close(out);
			close(in);


			return 0;
		}

		if(S_ISDIR(type1.st_mode) && S_ISREG(type2.st_mode))
			perror("error");
		closedir(src);




		if(S_ISREG(type1.st_mode) && S_ISDIR(type2.st_mode)){

			if((in = open(argv[1], O_RDONLY)) < 0) { 

				perror(argv[1]);
				return -1;
			}

			chdir(argv[2]);

			if((out = open(argv[1], O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR)) < 0) { 
				return -1;
			}

			while((n=read(in, buf, sizeof(buf)))>0) 
				write(out, buf, n);

			close(out);
			close(in);
			closedir(dst);

		}

		if(S_ISDIR(type1.st_mode) && S_ISDIR(type2.st_mode)){

			DirCopy(argv[1], argv[2]);
		}
	}
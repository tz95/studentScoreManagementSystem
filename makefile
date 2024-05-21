# 编译器和编译选项
CC = gcc
CFLAGS = -g -Wall -Iinclude

# 可执行文件名
TARGET = sms

# 源文件和头文件目录
SRC_DIR = sourceFile
OBJ_DIR = objs
INCLUDE_DIR = include

# 获取源文件列表
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# 默认目标
all: $(TARGET)

# 链接可执行文件
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# 编译每个源文件
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# 清除生成的文件
clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET)

# 运行目标（如果需要）
run: $(TARGET)
	./$(TARGET)

# 调试目标
debug: $(TARGET)
	gdb ./$(TARGET)

.PHONY: all clean run debug
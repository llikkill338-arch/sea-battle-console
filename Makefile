# ============================================================================
# Makefile для Морской бой — Консольный Бой
# Компиляция через MinGW (g++)
# ============================================================================

CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 -O2 -static

TARGET = SeaBattle.exe
SRC_DIR = src
BUILD_DIR = build

SOURCES = $(SRC_DIR)/main.cpp \
          $(SRC_DIR)/utils.cpp \
          $(SRC_DIR)/graphics.cpp \
          $(SRC_DIR)/game_logic.cpp \
          $(SRC_DIR)/bot_ai.cpp \
          $(SRC_DIR)/screens.cpp

OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))

all: $(BUILD_DIR) $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

rebuild: clean all

.PHONY: all clean rebuild

# Name des Outputs
TARGET = main

# Compiler und Flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Ihpp

# Quellcode-Dateien
SRCS = $(wildcard implementation/*.cpp)

# Build-Regel
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

# Aufräumen
.PHONY: clean
clean:
	rm -f $(TARGET)

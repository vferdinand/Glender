# Name des Outputs
TARGET = main

# Compiler und Flags
CXX = g++
CXXFLAGS = -std=c++17 -g -Wall -Wextra -MMD -MP -Ihpp -I/usr/include/eigen3

# Quellcode, Objektdateien und Abhängigkeiten
SRCS = $(wildcard implementation/*.cpp)
OBJS = $(SRCS:implementation/%.cpp=build/%.o)
DEPS = $(OBJS:.o=.d)

# Ziel: Programm
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

# Ziel: Objektdateien
build/%.o: implementation/%.cpp | build
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Verzeichnis für Objektdateien
build:
	mkdir -p build

# Aufräumen
.PHONY: clean
clean:
	rm -rf build $(TARGET)

# Automatisch erstellte Header-Abhängigkeiten einbinden
-include $(DEPS)
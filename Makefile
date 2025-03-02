# Variáveis
CXX = g++
CXXFLAGS = -std=c++17
LDFLAGS = -ltbb
SRC_DIR = src/stl-parallel
SRC = $(wildcard $(SRC_DIR)/*.cpp)
BUILD_DIR = build
TARGET = $(BUILD_DIR)/reduce.out

# Regra padrão: compilar e executar
reduce: $(TARGET)
	@echo "reduce.out compiled"

# Regra de compilação
$(TARGET): $(SRC)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# Regra de limpeza
clean:
	@rm -rf $(BUILD_DIR)

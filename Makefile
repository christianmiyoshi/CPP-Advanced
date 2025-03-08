# Variáveis
CXX = g++
CXXFLAGS = -std=c++20
LDFLAGS = -ltbb
SRC_DIR = src/stl-parallel
SRC = $(wildcard $(SRC_DIR)/*.cpp)
BUILD_DIR = build
TARGET = $(BUILD_DIR)/reduce.out

# Regra padrão: compilar e executar
reduce: $(TARGET)
	@echo "reduce.out compiled"

vector: $(BUILD_DIR)/vector.out	
	@echo "vector compiled"

reference: src/pointer_references/reference.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $(BUILD_DIR)/reference.out $(LDFLAGS)


string-view: src/string/string-view.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $(BUILD_DIR)/string-view.out $(LDFLAGS)
	./$(BUILD_DIR)/string-view.out

raw-pointer: src/pointer_references/raw-pointer.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $(BUILD_DIR)/raw-pointer.out $(LDFLAGS)
	./$(BUILD_DIR)/raw-pointer.out

smart-pointer: src/pointer_references/smart-pointer.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $(BUILD_DIR)/smart-pointer.out $(LDFLAGS)
	./$(BUILD_DIR)/smart-pointer.out

constructor: src/pointer_references/constructor.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $(BUILD_DIR)/constructor.out $(LDFLAGS)
	./$(BUILD_DIR)/constructor.out

$(BUILD_DIR)/vector.out: src/data-structure/vector.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)
	

# Regra de compilação
$(TARGET): $(SRC)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# Regra de limpeza
clean:
	@rm -rf $(BUILD_DIR)
